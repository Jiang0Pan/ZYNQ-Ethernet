


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
//static Sample_Data  * Sample_ptr = (Sample_Data *)SAMPLE_DATA_ADD;			//��������
/***********************************************************************
	[��	       ��	]��ʱ���жϻص�����
	[��            ��	]CallBackRef:�ص���������
	[��    ��    ֵ	]�����Ƿ�ɹ�
***********************************************************************/
static void TimerIntrHandler(void *CallBackRef)
{
	//����жϱ�־
	u16 i = 0x0, j = 0x0;

    XScuTimer *TimerPtr = (XScuTimer *) CallBackRef;
    XScuTimer_ClearInterruptStatus(TimerPtr);
    ////////////////////////////////////////////////

    if(OpenFLAG) 																//���ݿ���
    {
    	for(i = 0; i < 2; i++)
    	{
			for(j = 0; j < DPS_NUM/2; j++)										// 0 ~ 7
			{
				if(LADDER_MODE == dps_ptr->Dsp[(i*8)+j].Open.Mode)
				{
					if(dps_info.DBMsg[i].UseMask >> j)							//�Ѿ��ϵ�(��ʹ��)
						continue;

					DpsCount[i][j] += DpsCount[i][j];							//�������Լ�
					if(dps_ptr->Dsp[(i*8)+j].Open.STime == DpsCount[i][j])		//��ʼ�ϵ�
					{
						OpenFLAG = 0x2;
						SetValue[i][j] += dps_ptr->Dsp[(i*8)+j].Open.Step;
						if(SetValue[i][j] >= dps_ptr->Dsp[(i*8)+j].SetValue)    //��Դ�ѵ���Ŀ���ѹ
						{
							SetValue[i][j] = dps_ptr->Dsp[(i*8)+j].SetValue;
							dps_info.DBMsg[i].UseMask |= (0x1 << j);			//��־��λ
						}

						if(i < (DPS_NUM/2 - 2))
							DpsX_UpdateV(SetValue[i][j]/1000.0, dps_info.DBMsg[i].DpsAddr[j], dps_info.DBMsg[i].Chan);
						else
							Set_AD5694(SetValue[i][j]/1000.0, (i*2)+j-6, dps_info.AD5694_SlaveAddr, dps_info.DBMsg[i].Chan);
					}
					else if((dps_ptr->Dsp[(i*8)+j].Open.Keep == DpsCount[i][j]) && (OpenFLAG == 0x2))	//����ʱ�䵽��
					{
						SetValue[i][j] += dps_ptr->Dsp[(i*8)+j].Open.Step;		//�Ӳ���ֵ
						if(SetValue[i][j] >= dps_ptr->Dsp[(i*8)+j].SetValue)
						{
							SetValue[i][j] = dps_ptr->Dsp[(i*8)+j].SetValue;	//��Դ�ѵ���Ŀ���ѹ
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
    	   (dps_info.DBMsg[1].UseMask == dps_info.DBMsg[1].OpenMask))			//ȫ���ϵ����
    	{
    		OpenFLAG = 0x0;
    	}
    }

    if(CloseFLAG)																//���ݹص�
    {
    	for(i = 0; i < 2; i++)
    	{
			for(j = 0; j < DPS_NUM/2; j++)										// 0 ~ 7
			{
				if(LADDER_MODE == dps_ptr->Dsp[(i*8)+j].Close.Mode)				//����ģʽ
				{
					if((dps_info.DBMsg[i].CloseMask >> j)&0x1)					//�Ѿ�ȡ��ʹ��
						continue;

					DpsCount[i][j] += DpsCount[i][j];							//�������Լ�
					if(dps_ptr->Dsp[(i*8)+j].Close.STime == DpsCount[i][j])
					{
						CloseFLAG = 0x2;
						SetValue[i][j] -= dps_ptr->Dsp[(i*8)+j].Close.Step;
						if(SetValue[i][j] <= 0)									//��Դ��ѹ��Ϊ0
						{
							SetValue[i][j] = 0;
							dps_info.DBMsg[i].CloseMask |= 0x1 << j;
						}

						if(i < (DPS_NUM/2 - 2))
							DpsX_UpdateV(SetValue[i][j]/1000.0, dps_info.DBMsg[i].DpsAddr[j], dps_info.DBMsg[i].Chan);
						else
							Set_AD5694(SetValue[i][j]/1000.0, (i*2)+j-6, dps_info.AD5694_SlaveAddr, dps_info.DBMsg[i].Chan);
					}
					else if((dps_ptr->Dsp[(i*8)+j].Close.Keep == DpsCount[i][j]) && (CloseFLAG == 0x2))	//����ʱ�䵽��
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
    	   (dps_info.DBMsg[1].UseMask == dps_info.DBMsg[1].CloseMask))		//ȫ���µ����
    	{
    		CloseFLAG = 0x0;
    	}
    }
}

/***********************************************************************
	[��	       ��	]��ʱ����ʼ��
	[��            ��	]Load_Value:����ֵ
	[��    ��    ֵ	]�����Ƿ�ɹ�
***********************************************************************/
s32 Timer_Init(u32 Load_Value)
{
	s32 Status = 0;
    XScuTimer_Config *TMRConfigPtr = NULL;

    //˽�ж�ʱ����ʼ��
    TMRConfigPtr = XScuTimer_LookupConfig(XPAR_XSCUTIMER_0_DEVICE_ID);
    Status = XScuTimer_CfgInitialize(&Timer, TMRConfigPtr, TMRConfigPtr->BaseAddr);
    if(Status != SUCCESS)
       	return FAILURE;

    //���ؼ������ڣ�˽�ж�ʱ����ʱ��ΪCPU��һ�룬Ϊ333MHZ,
    //�������1S,����ֵΪ1sx(333x1000x1000)(1/s)-1=0x13D92D3F
    XScuTimer_LoadTimer(&Timer, Load_Value);

    //�Զ�װ��
    XScuTimer_EnableAutoReload(&Timer);

    //��ʱ���жϳ�ʼ��
    Status = XScuGic_Connect(&XPS_XScuGic, XPAR_SCUTIMER_INTR,
    						(Xil_ExceptionHandler)TimerIntrHandler,
    						(void *)&Timer);
    if(Status != SUCCESS)
    	return FAILURE;

    XScuGic_Enable(&XPS_XScuGic, XPAR_SCUTIMER_INTR);  		//ʹ���жϿ�����
    XScuTimer_EnableInterrupt(&Timer);						//ʹ�ܶ�ʱ���ж�

    return SUCCESS;
}

/***********************************************************************
	[��	       ��	]�򿪶�ʱ��
	[��            ��	]��
	[��    ��    ֵ	]��
***********************************************************************/
void Timer_Start(void) { XScuTimer_Start(&Timer); }

/***********************************************************************
	[��	       ��	]�رն�ʱ��
	[��            ��	]��
	[��    ��    ֵ	]��
***********************************************************************/
void Timer_Stop(void) { XScuTimer_Stop(&Timer); }











