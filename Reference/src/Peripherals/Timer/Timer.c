


#include "timer.h"
#include "error.h"
#include "Gpio.h"
#include "memory_map.h"




static XScuTimer Timer;
extern XScuGic XPS_XScuGic;



u8 OpenFLAG  = 0x0;
u8 CloseFLAG = 0x0;
u8 LINEFLAG  = 0X0;
u32 DpsCount[2][DPS_NUM/2] = {{0}};
u16 SetValue[2][DPS_NUM/2] = {{0}};
static Dps_Arg      * dps_ptr    = (Dps_Arg     *)DPS_CFG_DATA_ADDR;
//static Sample_Data  * Sample_ptr = (Sample_Data *)SAMPLE_DATA_ADD;			//采样数据
/***********************************************************************
	[功	       能	]定时器中断回调函数
	[参            数	]CallBackRef:回调函数参数
	[返    回    值	]操作是否成功
***********************************************************************/
static void TimerIntrHandler(void *CallBackRef)
{
	//清除中断标志
	u16 i = 0x0, j = 0x0;

    XScuTimer *TimerPtr = (XScuTimer *) CallBackRef;
    XScuTimer_ClearInterruptStatus(TimerPtr);
    ////////////////////////////////////////////////

    if(OpenFLAG) 																//阶梯开电
    {
    	for(i = 0; i < 2; i++)
    	{
			for(j = 0; j < DPS_NUM/2; j++)										// 0 ~ 7
			{
				if(LADDER_MODE == dps_ptr->Dsp[(i*8)+j].Open.Mode)
				{
					if(dps_info.DBMsg[i].UseMask >> j)							//已经上电(已使用)
						continue;

					DpsCount[i][j] += DpsCount[i][j];							//计数器自加
					if(dps_ptr->Dsp[(i*8)+j].Open.STime == DpsCount[i][j])		//开始上电
					{
						OpenFLAG = 0x2;
						SetValue[i][j] += dps_ptr->Dsp[(i*8)+j].Open.Step;
						if(SetValue[i][j] >= dps_ptr->Dsp[(i*8)+j].SetValue)    //电源已到达目标电压
						{
							SetValue[i][j] = dps_ptr->Dsp[(i*8)+j].SetValue;
							dps_info.DBMsg[i].UseMask |= (0x1 << j);			//标志置位
						}

						if(i < (DPS_NUM/2 - 2))
							DpsX_UpdateV(SetValue[i][j]/1000.0, dps_info.DBMsg[i].DpsAddr[j], dps_info.DBMsg[i].Chan);
						else
							Set_AD5694(SetValue[i][j]/1000.0, (i*2)+j-6, dps_info.AD5694_SlaveAddr, dps_info.DBMsg[i].Chan);
					}
					else if((dps_ptr->Dsp[(i*8)+j].Open.Keep == DpsCount[i][j]) && (OpenFLAG == 0x2))	//保持时间到达
					{
						SetValue[i][j] += dps_ptr->Dsp[(i*8)+j].Open.Step;		//加步进值
						if(SetValue[i][j] >= dps_ptr->Dsp[(i*8)+j].SetValue)
						{
							SetValue[i][j] = dps_ptr->Dsp[(i*8)+j].SetValue;	//电源已到达目标电压
							dps_info.DBMsg[i].UseMask |= (0x1 << j);
						}

						if(i < (DPS_NUM/2 - 2))
							DpsX_UpdateV(SetValue[i][j]/1000.0, dps_info.DBMsg[i].DpsAddr[j], dps_info.DBMsg[i].Chan);
						else
							Set_AD5694(SetValue[i][j]/1000.0, (i*2)+j-6, dps_info.AD5694_SlaveAddr, dps_info.DBMsg[i].Chan);
					}
				}
			}
    	}
    	if((dps_info.DBMsg[0].UseMask == dps_info.DBMsg[0].OpenMask)&&
    	   (dps_info.DBMsg[1].UseMask == dps_info.DBMsg[1].OpenMask))			//全部上电完成
    	{
    		OpenFLAG = 0x0;
    	}
    }

    if(CloseFLAG)																//阶梯关电
    {
    	for(i = 0; i < 2; i++)
    	{
			for(j = 0; j < DPS_NUM/2; j++)										// 0 ~ 7
			{
				if(LADDER_MODE == dps_ptr->Dsp[(i*8)+j].Close.Mode)				//阶梯模式
				{
					if((dps_info.DBMsg[i].CloseMask >> j)&0x1)					//已经取消使用
						continue;

					DpsCount[i][j] += DpsCount[i][j];							//计数器自加
					if(dps_ptr->Dsp[(i*8)+j].Close.STime == DpsCount[i][j])
					{
						CloseFLAG = 0x2;
						SetValue[i][j] -= dps_ptr->Dsp[(i*8)+j].Close.Step;
						if(SetValue[i][j] <= 0)									//电源电压已为0
						{
							SetValue[i][j] = 0;
							dps_info.DBMsg[i].CloseMask |= 0x1 << j;
						}

						if(i < (DPS_NUM/2 - 2))
							DpsX_UpdateV(SetValue[i][j]/1000.0, dps_info.DBMsg[i].DpsAddr[j], dps_info.DBMsg[i].Chan);
						else
							Set_AD5694(SetValue[i][j]/1000.0, (i*2)+j-6, dps_info.AD5694_SlaveAddr, dps_info.DBMsg[i].Chan);
					}
					else if((dps_ptr->Dsp[(i*8)+j].Close.Keep == DpsCount[i][j]) && (CloseFLAG == 0x2))	//保持时间到达
					{
						SetValue[i][j] -= dps_ptr->Dsp[(i*8)+j].Close.Step;
						if(SetValue[i][j] <= 0)
						{
							SetValue[i][j] = 0;
							dps_info.DBMsg[i].CloseMask |= 0x1 << j;
						}
						if(i < (DPS_NUM/2 - 2))
							DpsX_UpdateV(SetValue[i][j]/1000.0, dps_info.DBMsg[i].DpsAddr[j], dps_info.DBMsg[i].Chan);
						else
							Set_AD5694(SetValue[i][j]/1000.0, (i*2)+j-6, dps_info.AD5694_SlaveAddr, dps_info.DBMsg[i].Chan);
					}
				}
			}
    	}
    	if((dps_info.DBMsg[0].UseMask == dps_info.DBMsg[0].CloseMask)&&
    	   (dps_info.DBMsg[1].UseMask == dps_info.DBMsg[1].CloseMask))		//全部下电完成
    	{
    		CloseFLAG = 0x0;
    	}
    }
}

/***********************************************************************
	[功	       能	]定时器初始化
	[参            数	]Load_Value:加载值
	[返    回    值	]操作是否成功
***********************************************************************/
s32 Timer_Init(u32 Load_Value)
{
	s32 Status = 0;
    XScuTimer_Config *TMRConfigPtr = NULL;

    //私有定时器初始化
    TMRConfigPtr = XScuTimer_LookupConfig(XPAR_XSCUTIMER_0_DEVICE_ID);
    Status = XScuTimer_CfgInitialize(&Timer, TMRConfigPtr, TMRConfigPtr->BaseAddr);
    if(Status != SUCCESS)
       	return FAILURE;

    //加载计数周期，私有定时器的时钟为CPU的一半，为333MHZ,
    //如果计数1S,加载值为1sx(333x1000x1000)(1/s)-1=0x13D92D3F
    XScuTimer_LoadTimer(&Timer, Load_Value);

    //自动装载
    XScuTimer_EnableAutoReload(&Timer);

    //定时器中断初始化
    Status = XScuGic_Connect(&XPS_XScuGic, XPAR_SCUTIMER_INTR,
    						(Xil_ExceptionHandler)TimerIntrHandler,
    						(void *)&Timer);
    if(Status != SUCCESS)
    	return FAILURE;

    XScuGic_Enable(&XPS_XScuGic, XPAR_SCUTIMER_INTR);  		//使能中断控制器
    XScuTimer_EnableInterrupt(&Timer);						//使能定时器中断

    return SUCCESS;
}

/***********************************************************************
	[功	       能	]打开定时器
	[参            数	]无
	[返    回    值	]无
***********************************************************************/
void Timer_Start(void) { XScuTimer_Start(&Timer); }

/***********************************************************************
	[功	       能	]关闭定时器
	[参            数	]无
	[返    回    值	]无
***********************************************************************/
void Timer_Stop(void) { XScuTimer_Stop(&Timer); }











