#include "iic.h"


//IIC0结构体,I2C1结构
static XIicPs IIC[2];

//IIC通道打开标志
static u16 IIC_CHAN_STAT = 0x0;



/***********************************************************************
	[功	       能	]复位IIC芯片
	[参            数	]无
	[返    回    值	]操作结果
***********************************************************************/
s32 Reset_ExpIIC(void)
{

	return SUCCESS;
}

/***********************************************************************
	[功	       能	]IIC0,1初始化
	[参            数	]无
	[返    回    值	]操作结果
***********************************************************************/
s32 IIC_Init(void)
{
	int Status;
	XIicPs_Config *Config0, *Config1;

	//结构体配置
	Config0 = XIicPs_LookupConfig(DEV_IIC0);
	if (NULL == Config0)
		return FAILURE;

	Config1 = XIicPs_LookupConfig(DEV_IIC1);
	if (NULL == Config1)
		return FAILURE;

	//结构体初始化
	Status = XIicPs_CfgInitialize(&IIC[0], Config0, Config0->BaseAddress);
	if (Status != SUCCESS)
		return FAILURE;

	Status = XIicPs_CfgInitialize(&IIC[1], Config1, Config1->BaseAddress);
	if (Status != SUCCESS)
		return FAILURE;

	//硬件自检
	Status = XIicPs_SelfTest(&IIC[0]);
	if (Status != SUCCESS)
		return FAILURE;

	Status = XIicPs_SelfTest(&IIC[1]);
	if (Status != SUCCESS)
		return FAILURE;

	//设置IIC速率
	Status = XIicPs_SetSClk(&IIC[0], IIC0_SCLK_RATE);
	if (Status != SUCCESS)
		return FAILURE;

	Status = XIicPs_SetSClk(&IIC[1], IIC1_SCLK_RATE);
	if (Status != SUCCESS)
		return FAILURE;

#if 1
	//复位iic扩展
	Status = Reset_ExpIIC();
	if (Status != SUCCESS){
		return FAILURE;
	}
#endif

	return SUCCESS;
}

/***********************************************************************
	[功	       能	]IIC轮询发送
	[参            数	]MsgPtr:消息指针, ByteCount:消息长度, SlaveAddr:从机地址, iicx:iic结构指针
	[返    回    值	]操作结果
***********************************************************************/
s32 My_Write(u8 *MsgPtr, s32 ByteCount, u16 SlaveAddr, XIicPs* iicx)
{
	u8 timeout = 3;

	if(XIicPs_MasterSendPolled(iicx, MsgPtr, ByteCount, SlaveAddr))	//发送失败直接返回
		return FAILURE;
	while (XIicPs_BusIsBusy(iicx))
	{
		if(TimeOutMS(&timeout))
		return FAILURE;
	};	//总线被释放代表发送完成

	return SUCCESS;
}

/***********************************************************************
	[功	       能	]IIC轮询接收
	[参            数	]MsgPtr:消息指针, ByteCount:消息长度, SlaveAddr:从机地址, iicx:iic结构指针
	[返    回    值	]操作结果
***********************************************************************/
s32 My_Read(u8 *MsgPtr, s32 ByteCount, u16 SlaveAddr, XIicPs* iicx)
{
	u8 timeout = 3;

	if(XIicPs_MasterRecvPolled(iicx, MsgPtr, ByteCount, SlaveAddr))	//发送失败直接返回
		return FAILURE;
	while (XIicPs_BusIsBusy(iicx))
	{
		if(TimeOutMS(&timeout))
			return FAILURE;
	};	//总线被释放代表发送完成

	return SUCCESS;
}

/***********************************************************************
	[功	       能	]选择iic通道
	[参            数	]Chan:通道号
	[返    回    值	]操作结果
***********************************************************************/
s32 Select_IIC(IIC_Chan Chan)
{
	s32 Status = FAILURE;

	u16 CMD = 0x1 << Chan;
	u8 CMD0 = (CMD >> 0) & 0xff;
	//u8 CMD1 = (CMD >> 8) & 0xff;

	//判断该通道是否已经打开
	if(CMD == IIC_CHAN_STAT)//通道已打开
		return SUCCESS;

	Status = My_Write(&CMD0, 1, TCA0_ADDR, &IIC[1]);		//设置TCA9548A_0通道
	if(Status == FAILURE)							//发送失败直接返回
		return FAILURE;

	//调试板只有一个IIC扩展芯片
/*
	Status = My_Write(&CMD1, 1, TCA1_ADDR, &IIC1);		//设置TCA9548A_1通道
	if(Status == XST_FAILURE)							//发送失败直接返回
		return XST_FAILURE;
*/
	IIC_CHAN_STAT = 0x0;								//清位
	IIC_CHAN_STAT = CMD;								//置位通道MASK


	return SUCCESS;
}

/***********************************************************************
	[功	       能	]通用写任意IIC通道
	[参            数	]MsgPtr:消息指针, ByteCount:消息长度, SlaveAddr:从机地址, Chan:通道
	[返    回    值	]操作结果
***********************************************************************/
s32 IIC_Write(u8 *MsgPtr, s32 ByteCount, u16 SlaveAddr, IIC_Chan Chan)
{
	s32 Status = FAILURE;
	u8 timeout = 3;


	if(PSIIC == Chan)
	{
		if(XIicPs_MasterSendPolled(&IIC[0], MsgPtr, ByteCount, SlaveAddr))	//发送失败直接返回
			return FAILURE;

		while(XIicPs_BusIsBusy(&IIC[0]))
		{
			if(TimeOutMS(&timeout))
				return FAILURE;
		};	//总线被释放代表发送完成
	}
	else
	{
		Status = Select_IIC(Chan);
		if(Status == FAILURE)
			return FAILURE;

		if(XIicPs_MasterSendPolled(&IIC[1], MsgPtr, ByteCount, SlaveAddr))	//发送失败直接返回
			return FAILURE;

		while(XIicPs_BusIsBusy(&IIC[1]))
		{
			if(TimeOutMS(&timeout))
				return FAILURE;
		};	//总线被释放代表发送完成
	}

	return SUCCESS;
}

/***********************************************************************
	[功	       能	]通用读任意IIC通道
	[参            数	]MsgPtr:消息指针, ByteCount:消息长度, SlaveAddr:从机地址, Chan:通道
	[返    回    值	]操作结果
***********************************************************************/
s32 IIC_Read(u8 *MsgPtr, s32 ByteCount, u16 SlaveAddr, IIC_Chan Chan)
{
	s32 Status = FAILURE;
	u8 timeout = 3;

	if(PSIIC == Chan)
	{
		if(XIicPs_MasterRecvPolled(&IIC[0], MsgPtr, ByteCount, SlaveAddr))	//发送失败直接返回
			return FAILURE;
		while (XIicPs_BusIsBusy(&IIC[0]))
		{
			if(TimeOutMS(&timeout))
				return FAILURE;
		};	//总线被释放代表发送完成
	}
	else
	{
		Status = Select_IIC(Chan);
		if(Status == FAILURE)
			return FAILURE;

		if(XIicPs_MasterRecvPolled(&IIC[1], MsgPtr, ByteCount, SlaveAddr))	//发送失败直接返回
			return FAILURE;
		while (XIicPs_BusIsBusy(&IIC[1]))
		{
			if(TimeOutMS(&timeout))
				return FAILURE;
		};	//总线被释放代表发送完成
	}

	return SUCCESS;
}






