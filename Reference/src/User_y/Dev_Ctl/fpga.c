



#include "fpga.h"
#include "interrupt.h"
#include "ack.h"
#include "return_val.h"
#include "debug_config.h"

volatile u32 HP_STATUS = 0x0;


static void HP_IntrHanedler(void *arg)
{
	struct _Vec_Addr_ * Addr = (struct _Vec_Addr_ *)&(fpga_obj.Vec_Addr);
	if(*(Addr->MV_Flag))
	{
		u8 bid =  (*(Addr->MV_Flag))&0xf;		//读取返回板卡ID号

		xil_printf("Move Board:%d vector ok!\n", bid);

		//清除相关寄存器
		*(Addr->Serial)   = 0x0;				//清除选择板卡号及返回板卡号
		*(Addr->MV_Flag)  = 0x0;				//搬移OK清零
		HP_STATUS = 0x0;	 					//HP忙标志取消

		if (SEND_SUCCESS != Tcp_Ack()) {
			debug("Send Ack Failed In Beep Control In %s Files,%d Line\n",__FILE__,__LINE__);
			return;
		}
		xil_printf("---over---\n");
	}
}

/***********************************************************************
	[功	       能	]驱动板向量下发中断初始化
	[参            数	]无
	[返    回    值	]初始化是否成功
***********************************************************************/
s32 AXIHP_Init(void)
{
	s32 Status = XST_FAILURE;

	//注册driver0中断回调函数
	Status = XScuGic_Connect(&XPS_XScuGic, Driver_INT_ID,
							(Xil_ExceptionHandler)HP_IntrHanedler,
	                        (void *)NULL);
	if(Status != XST_SUCCESS)
		return XST_FAILURE;

	Mask_CPU1_IntrID(Driver_INT_ID);

	//设置中断类型
	IntrTypeSetup(Driver_INT_ID, RISING_EDGE_TYPE);

	//使能中断
	XScuGic_Enable(&XPS_XScuGic, Driver_INT_ID);

	return XST_SUCCESS;
}

s32 Fpga_WOpt(struct _REG_ * Cfg, u32 Addr, u32  Data)
{
	u8 timeout = WAITE_TIME;

	while(OK != (*(Cfg->WOpt_OK)&0x3))
	{
		if(TimeOutMS(&timeout))
			return (TIMEOUT);
	}

	*(Cfg->Opt_Addr) = Addr;
	*(Cfg->W_Data  ) = Data;
	*(Cfg->Data_Des) = 0x01;
	*(Cfg->Opt_RW  ) = W_OPT;
	*(Cfg->Trigger ) = 0x1;
	*(Cfg->Trigger ) = 0x0;

	return (SUCCESS);
}

s32 Fpga_ROpt(struct _REG_ * Cfg, u32 Addr, u32 *Rdata)
{
	u8 timeout = WAITE_TIME;

	while(OK != (*(Cfg->WOpt_OK)&0x3))
	{
		if(TimeOutMS(&timeout))
			return FAILURE;
	}

	*(Cfg->Opt_Addr) = Addr;
	*(Cfg->W_Data  ) = 0x0;
	*(Cfg->Data_Des) = 0x01;
	*(Cfg->Opt_RW  ) = R_OPT;
	*(Cfg->Trigger ) = 0x1;
	*(Cfg->Trigger ) = 0x0;

	timeout = WAITE_TIME;
	while(OK != (*(Cfg->R_Update)))
	{
		if(TimeOutMS(&timeout))
			return FAILURE;
	}

	*(Cfg->R_Update) = 0x0;
	*Rdata = *(Cfg->R_Data);

	return SUCCESS;
}

//读DDR数据
s32 DDR_ROpt(struct _REG_ * Cfg, u32 Addr, u32 *Rdata)
{
	return (Fpga_ROpt(Cfg, Addr, Rdata));
}

//写DDR数据
s32 DDR_WOpt(struct _REG_ * Cfg, u32 Addr, u32 Data)
{
	if(Fpga_WOpt(Cfg, Addr, Data))
		return FAILURE;
	return SUCCESS;
}

//配置执行周期
s32 DDR_Period(struct _REG_ * Cfg, u32 Period)
{
	if(Fpga_WOpt(Cfg, PERIOD, Period))
		return FAILURE;

	return SUCCESS;
}

//DDR测试
s32 Debug_DDR(struct _REG_ * Cfg)
{
	u32 Rdata = 0x0;
	if(Fpga_WOpt(Cfg, DDRDEBUG, TEST_VAL))
		return FAILURE;

	if(Fpga_ROpt(Cfg, DDRDEBUG, &Rdata))
		return FAILURE;

	if((TEST_VAL + 1) != Rdata)
		return FAILURE;

	return SUCCESS;
}

//写ddr参数(向量存放地址)
s32 DDR_WOpt_Arg(struct _REG_ * Cfg, u32 Waddr, u32 Wlen)
{
	if(Fpga_WOpt(Cfg, WSADDR, Waddr))
		return FAILURE;

	if(Fpga_WOpt(Cfg, WLENGTH, Wlen))
		return FAILURE;

	if(Fpga_WOpt(Cfg, WTIRG, 0x1))
		return FAILURE;

	return SUCCESS;
}

//读ddr参数(fpga读向量到RAM准备好)
s32 DDR_ROpt_Arg(struct _REG_ * Cfg, u32 Waddr, u32 Wlen)
{
	if(Fpga_WOpt(Cfg, RSADDR, Waddr))
		return FAILURE;

	if(Fpga_WOpt(Cfg, RLENGTH, Wlen))
		return FAILURE;

	if(Fpga_WOpt(Cfg, RTIRG, 0x1))
		return FAILURE;

	return SUCCESS;
}

//读校验和
s32 DDR_ROpt_Check(struct _REG_ * Cfg, u32 *Rdata)
{
	return (Fpga_ROpt(Cfg, CHECKSUM, Rdata));
}

//清校验和
s32 DDR_Clear_Check(struct _REG_ * Cfg)
{
	if(Fpga_WOpt(Cfg, CLRCHECK, 0x1))
		return FAILURE;
	return SUCCESS;
}

//向量执行标志
s32 DDR_ROpt_Vecflag(struct _REG_ * Cfg, u32 *Rdata)
{
	return (Fpga_ROpt(Cfg, EXEFLAG, Rdata));
}

//读取向量执行数量
s32 DDR_ROpt_Counter(struct _REG_ * Cfg, u32 *Rdata)
{
	return (Fpga_ROpt(Cfg, COUNTER, Rdata));
}

//IO调试寄存器
s32 Debug_IO(struct _REG_ * Cfg)
{
	u32 Rdata = 0x0;
	if(Fpga_WOpt(Cfg, IODEBUG, TEST_VAL))
		return FAILURE;

	if(Fpga_ROpt(Cfg, IODEBUG, &Rdata))
		return FAILURE;

	if((TEST_VAL + 1) != Rdata)
		return FAILURE;

	return SUCCESS;
}

//IO变化位置
s32 IO_Var_WOpt(struct _REG_ * Cfg, u16 IO, VaryPos pos, u32 value)
{
	u32 Reg = ((IO > 192) ? CHANVAR : IO64CFG) + (IO/8 * 64) + (32 * pos) + ((IO%8) *4);
	if(Fpga_WOpt(Cfg, Reg, value))
		return FAILURE;

	return SUCCESS;
}

//IO比较位置
s32 IO_Cmp_WOpt(struct _REG_ * Cfg, u16 IO, VaryPos pos, u32 value)
{
	if(Fpga_WOpt(Cfg, CHANCMP + (IO/8 * 64) + (32 * pos) + ((IO%8) *4) , value))
		return FAILURE;

	return SUCCESS;
}

s32 MV_Vector(Vector_Arg *Vec, u32 Size)
{
	u8 timeout = WAITE_TIME;							//超时时间

	HP_STATUS = 0x1;

	xil_printf("Move vector to board %d!\n", Vec->fpga_CS);

	//测试DDR是否OK
	Debug_DDR(&(fpga_obj.Driver[Vec->fpga_CS].Reg));

	//填充地址
	if(DDR_WOpt_Arg(&(fpga_obj.Driver[Vec->fpga_CS].Reg), Vec->lseek, Size/VEC_UNIT))
		return FAILURE;

	(fpga_obj.Driver[Vec->fpga_CS].VecSize) += (Size);	//每次向量大小累加

	//为保证向量搬移准确每次搬移都写测试值
	*(fpga_obj.Vec_Addr.Debug) = TEST_VAL;
	while(*(fpga_obj.Vec_Addr.Debug) != TEST_VAL+1)		//等待回应
	{
		if(TimeOutMS(&timeout))
			return FAILURE;
	}

	*(fpga_obj.Vec_Addr.MV_Flag) = 0x0;					//读取标志OK置0
	*(fpga_obj.Vec_Addr.Serial ) = 0x0;					//清除板卡编号
	*(fpga_obj.Vec_Addr.S_Addr ) = (u32)(Vec->Data);	//添加数据地址
	*(fpga_obj.Vec_Addr.D_Len  ) = Size;				//添加数据长度
	*(fpga_obj.Vec_Addr.Serial ) = (Vec->fpga_CS) > 0 ? (Vec->fpga_CS) : 1; //目标板卡号,PL编号从1开始
	*(fpga_obj.Vec_Addr.W_Trig ) = 0x1;					//触发PL

	return SUCCESS;
}

//读取所有数据
s32 Read_Back_isp(void)
{
	u8 i = 0x0, timeout = WAITE_TIME;
	u16 j = 0x0;
	u32 Mask = 0x0;
	u32 Line = 0x0;
	u32 Data = 0x0;

	memset(&All_isp, 0, sizeof(All_isp));

	for(i = 3; i < 5; i++)
	{
		while(1)
		{
			if(Fpga_ROpt(&(fpga_obj.Driver[i].Reg), SAVEDONE, &Data))		//数据保存OK
				return FAILURE;
			if(Data)
				return FAILURE;

			if(TimeOutMS(&timeout))									//超时
				return TIMEOUT;
		}
		for(j = 0; j < NUM_ISP; j++)
		{
			Mask = 0x0;
			Line = 0x0;
			Fpga_WOpt(&(fpga_obj.Driver[i].Reg), j, RAMADDR);
			Fpga_ROpt(&(fpga_obj.Driver[i].Reg), ERRORMASK, &Mask);
			if(!Mask)												//读完
				break;

			Fpga_ROpt(&(fpga_obj.Driver[i].Reg), ERRORADDR, &Line);
			if(!Line)
				break;

			All_isp.isp[i/4][j].Mask = Mask;
			All_isp.isp[i/4][j].Addr = Line;
		}

		Fpga_WOpt(&(fpga_obj.Driver[i].Reg), 0x1, INITBRAM);
	}
	return SUCCESS;
}

u32 Read_Vecflag(Sample_Data  *Sample)
{
	u16 i = 0;
	u32 Rdata = 0x0, ret = 0x0;
	for(i = 0; i < DRIV_BOARD_NUM; i++)
	{
		Rdata = 0x0;
		if(DDR_ROpt_Vecflag(&(fpga_obj.Driver[i].Reg), &Rdata))
		{
			Sample->AgeStatus |= 0x1 << (32+i);
			ret |= (0x1 << i);
		}
		else
		{
			if(0 == ((Rdata >> 1)&0x1))
				ret |= (0x1 << i);
		}
	}
	return ret;
}


