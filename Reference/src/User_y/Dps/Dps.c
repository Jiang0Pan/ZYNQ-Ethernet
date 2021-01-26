




#include "Dps.h"



/***********************************************************************
	[功	       能	]L11格式转浮点
	[参            数	]Data:L11格式数据
	[返    回    值	]浮点数据
***********************************************************************/
float L11_to_float(u16 Data)
{
	float base = 0.0;
	   u8 exp = 0;

	base = (Data & 0x0400) ? (-(float)(((~Data)&0x3ff)+1)) : ((float)(Data&0x3ff));
	exp  = (Data & 0x8000) ? (((~(Data>>11))&0xf)+1) : ((Data>>11)&0xf);

	return (base / (0x1 << exp));
}

/***********************************************************************
	[功	       能	]L16U格式转浮点
	[参            数	]Data:L16U格式数据
	[返    回    值	]浮点数据
***********************************************************************/
float L16U_to_float(u16 Data)
{
	float base = (float)Data;

	return (base / (0x1 << 19));
}

/***********************************************************************
	[功	       能	]L16S格式转浮点
	[参            数	]Data:L16S格式数据
	[返    回    值	]浮点数据
***********************************************************************/
float L16S_to_float(u16 Data)
{
	float base = 0.0;

	base = (Data & 0x8000) ? (-(float)(((~Data)&0x7fff)+1)) : ((float)(Data&0x7fff));

	return (base / (0x1 << 19));
}

/***********************************************************************
	[功	       能	]浮点转L11格式数据
	[参            数	]value:浮点数据
	[返    回    值	]L11格式数据
***********************************************************************/
u16 float_to_L11(float value)
{
	u16 Data = 0;
	u16 Base = 0;
	u8 i = (0x1 << 4)-1;
	while(i)
	{
		if((0x1 << 10) > (((value > 0) ? value : (-value)) * (0x1 << i)))
			break;
		i = i - 1;
	}

	Base = ((value > 0) ? value : (-value)) * (0x1 << i);

	if(value != 0)
	{
		Data |= 0x1<<15;
		Data |= ((~(i-1))&0xf)<<11;

		if(value < 0)
		{
			Data |= 0x1<<10;
			Data |= ((~Base)&0x3ff) + 1;
		}
		else
			Data |= (Base&0x3ff);
	}

	return Data;
}

/***********************************************************************
	[功	       能	]浮点转L16U格式数据
	[参            数	]value:浮点数据
	[返    回    值	]L16U格式数据
***********************************************************************/
u16 float_to_L16U(float value)
{
	u16 Data = (u16)(value * (0x1 << 19));
	return (Data);
}

//浮点转L16S
u16 float_to_L16S(float value)
{
	u16 Data = 0;
	if(value >= 0)
	{
		Data |= ((u16)(value * (0x1 << 19)))&0x7fff;
		Data &= ~(0x1 << 15);
	}
	else
	{
		Data |= ((~((u16)((-value) * (0x1 << 19))))&0x7fff) + 1;
		Data |= 0x1 << 15;
	}

	return (Data);
}

s32 DpsX_MaxFAIL_VIN(struct _DpsArg_ *Dpsx, u8 DpsAddr, IIC_Chan Chan)
{
	u16 data = 0, rdata = 0;
	u8 buf[L11_SIZE] = {0x0};
	u8 rbuf[L11_SIZE] = {0x0};
	data = float_to_L11(MAXFAIL_VIN);
	buf[0] = data&0xff;
	buf[1] = (data >> 8)&0xff;

	do{
		if(SMBus_Write(buf, L11_SIZE, DpsAddr, VIN_OV_FAULT_LIMIT, Chan))
			return FAILURE;

		if(SMBus_Read(rbuf, L11_SIZE, DpsAddr, VIN_OV_FAULT_LIMIT, Chan))
			return FAILURE;

		rdata  = rbuf[0] << 8;
		rdata |= rbuf[1] << 0;

	}while(rdata != data);

	return SUCCESS;
}

s32 DpsX_MinFAIL_VIN(struct _DpsArg_ *Dpsx, u8 DpsAddr, IIC_Chan Chan)
{
	u16 data = 0, rdata = 0;
	u8 buf[L11_SIZE] = {0x0};
	u8 rbuf[L11_SIZE] = {0x0};
	data = float_to_L11(MINFAIL_VIN);
	buf[0] = data&0xff;
	buf[1] = (data >> 8)&0xff;

	do{
		if(SMBus_Write(buf, L11_SIZE, DpsAddr, VIN_UV_FAULT_LIMIT, Chan))
			return FAILURE;

		if(SMBus_Read(rbuf, L11_SIZE, DpsAddr, VIN_UV_FAULT_LIMIT, Chan))
			return FAILURE;

		rdata  = rbuf[0] << 8;
		rdata |= rbuf[1] << 0;

	}while(rdata != data);

	return SUCCESS;
}

s32 DpsX_MaxWARN_VIN(struct _DpsArg_ *Dpsx, u8 DpsAddr, IIC_Chan Chan)
{
	u16 data = 0, rdata = 0;
	u8 buf[L11_SIZE] = {0x0};
	u8 rbuf[L11_SIZE] = {0x0};
	data = float_to_L11((Dpsx->InputMaxV)/1000.0);
	buf[0] = data&0xff;
	buf[1] = (data >> 8)&0xff;

	do{
		if(SMBus_Write(buf, L11_SIZE, DpsAddr, VIN_OV_WARN_LIMIT, Chan))
			return FAILURE;

		if(SMBus_Read(rbuf, L11_SIZE, DpsAddr, VIN_OV_WARN_LIMIT, Chan))
			return FAILURE;

		rdata  = rbuf[0] << 8;
		rdata |= rbuf[1] << 0;

	}while(rdata != data);

	return SUCCESS;
}

s32 DpsX_MinWARN_VIN(struct _DpsArg_ *Dpsx, u8 DpsAddr, IIC_Chan Chan)
{
	u16 data = 0, rdata = 0;
	u8 buf[L11_SIZE]  = {0x0};
	u8 rbuf[L11_SIZE] = {0x0};
	data = float_to_L11((Dpsx->InputMinV)/1000.0);
	buf[0] = data&0xff;
	buf[1] = (data >> 8)&0xff;

	do{
		if(SMBus_Write(buf, L11_SIZE, DpsAddr, VIN_UV_WARN_LIMIT, Chan))
			return FAILURE;

		if(SMBus_Read(rbuf, L11_SIZE, DpsAddr, VIN_UV_WARN_LIMIT, Chan))
			return FAILURE;

		rdata  = rbuf[0] << 8;
		rdata |= rbuf[1] << 0;

	}while(rdata != data);

	return SUCCESS;
}

s32 DpsX_Max_VOUT(struct _DpsArg_ *Dpsx, u8 DpsAddr, IIC_Chan Chan)
{
	u16 data = 0, rdata = 0;
	u8 buf[L16U_SIZE] = {0x0};
	u8 rbuf[L16U_SIZE] = {0x0};

	data = float_to_L16U(8192*5.5);
	buf[0] = data&0xff;
	buf[1] = (data >> 8)&0xff;

	do{
		if(SMBus_Write(buf, L16U_SIZE, DpsAddr, VOUT_MAX, Chan))
			return FAILURE;

		if(SMBus_Read(rbuf, L16U_SIZE, DpsAddr, VOUT_MAX, Chan))
			return FAILURE;

		rdata  = rbuf[0] << 8;
		rdata |= rbuf[1] << 0;

	}while(rdata != data);

	data = float_to_L11((Dpsx->DpsMaxV)/1000.0);
	buf[0] = data&0xff;
	buf[1] = (data >> 8)&0xff;

	do{
		if(SMBus_Write(buf, L11_SIZE, DpsAddr, VOUT_OV_FAULT_LIMIT, Chan))
			return FAILURE;

		if(SMBus_Read(rbuf, L11_SIZE, DpsAddr, VOUT_OV_FAULT_LIMIT, Chan))
			return FAILURE;

		rdata  = rbuf[0] << 8;
		rdata |= rbuf[1] << 0;

	}while(rdata != data);

	do{
		if(SMBus_Write(buf, L11_SIZE, DpsAddr, VOUT_OV_WARN_LIMIT, Chan))
			return FAILURE;

		if(SMBus_Read(rbuf, L11_SIZE, DpsAddr, VOUT_OV_WARN_LIMIT, Chan))
			return FAILURE;

		rdata  = rbuf[0] << 8;
		rdata |= rbuf[1] << 0;

	}while(rdata != data);

	return SUCCESS;
}

s32 DpsX_Min_VOUT(struct _DpsArg_ *Dpsx, u8 DpsAddr, IIC_Chan Chan)
{
	u16 data = 0, rdata = 0;
	u8 buf[L11_SIZE] = {0x0};
	u8 rbuf[L11_SIZE] = {0x0};

	data = float_to_L11((Dpsx->DpsMinV)/1000.0);
	buf[0] = data&0xff;
	buf[1] = (data >> 8)&0xff;

	do{
		if(SMBus_Write(buf, L11_SIZE, DpsAddr, VOUT_UV_FAULT_LIMIT, Chan))
			return FAILURE;

		if(SMBus_Read(rbuf, L11_SIZE, DpsAddr, VOUT_UV_FAULT_LIMIT, Chan))
			return FAILURE;

		rdata  = rbuf[0] << 8;
		rdata |= rbuf[1] << 0;

	}while(rdata != data);

	do{
		if(SMBus_Write(buf, L11_SIZE, DpsAddr, VOUT_UV_WARN_LIMIT, Chan))
			return FAILURE;

		if(SMBus_Read(rbuf, L11_SIZE, DpsAddr, VOUT_UV_WARN_LIMIT, Chan))
			return FAILURE;

		rdata  = rbuf[0] << 8;
		rdata |= rbuf[1] << 0;

	}while(rdata != data);

	return SUCCESS;
}

s32 DpsX_MaxMARG_VOUT(struct _DpsArg_ *Dpsx, u8 DpsAddr, IIC_Chan Chan)
{
	u16 data = 0, rdata = 0;
	u8 buf[L11_SIZE] = {0x0};
	u8 rbuf[L11_SIZE] = {0x0};

	data = float_to_L11(((Dpsx->SetValue)/1000.0)*1.03);
	buf[0] = data&0xff;
	buf[1] = (data >> 8)&0xff;

	do{
		if(SMBus_Write(buf, L11_SIZE, DpsAddr, VOUT_MARGIN_HIGH, Chan))
			return FAILURE;

		if(SMBus_Read(rbuf, L11_SIZE, DpsAddr, VOUT_MARGIN_HIGH, Chan))
			return FAILURE;

		rdata  = rbuf[0] << 8;
		rdata |= rbuf[1] << 0;

	}while(rdata != data);

	return SUCCESS;
}

s32 DpsX_MinMARG_VOUT(struct _DpsArg_ *Dpsx, u8 DpsAddr, IIC_Chan Chan)
{
	u16 data = 0, rdata = 0;
	u8 buf[L11_SIZE] = {0x0};
	u8 rbuf[L11_SIZE] = {0x0};

	data = float_to_L11((Dpsx->DpsMinV)/1000.0);
	buf[0] = data&0xff;
	buf[1] = (data >> 8)&0xff;

	do{
		if(SMBus_Write(buf, L11_SIZE, DpsAddr, VOUT_MARGIN_LOW, Chan))
			return FAILURE;

		if(SMBus_Read(rbuf, L11_SIZE, DpsAddr, VOUT_MARGIN_LOW, Chan))
			return FAILURE;

		rdata  = rbuf[0] << 8;
		rdata |= rbuf[1] << 0;

	}while(rdata != data);

	return SUCCESS;
}

s32 DpsX_Max_IOUT(struct _DpsArg_ *Dpsx, u8 DpsAddr, IIC_Chan Chan)
{
	u16 data = 0, rdata = 0;
	u8 buf[L11_SIZE]  = {0x0};
	u8 rbuf[L11_SIZE] = {0x0};
	data = float_to_L11((Dpsx->Protect_I)/1000.0);
	buf[0] = data&0xff;
	buf[1] = (data >> 8)&0xff;

	do{
		if(SMBus_Write(buf, L11_SIZE, DpsAddr, IOUT_OC_FAULT_LIMIT, Chan))
			return FAILURE;

		if(SMBus_Read(rbuf, L11_SIZE, DpsAddr, IOUT_OC_FAULT_LIMIT, Chan))
			return FAILURE;

		rdata  = rbuf[0] << 8;
		rdata |= rbuf[1] << 0;

	}while(rdata != data);

	data = 0xECE0;
	buf[0] = data&0xff;
	buf[1] = (data >> 8)&0xff;
	do{
		if(SMBus_Write(buf, L11_SIZE, DpsAddr, IOUT_UC_FAULT_LIMIT, Chan))
			return FAILURE;

		if(SMBus_Read(rbuf, L11_SIZE, DpsAddr, IOUT_UC_FAULT_LIMIT, Chan))
			return FAILURE;

		rdata  = rbuf[0] << 8;
		rdata |= rbuf[1] << 0;

	}while(rdata != data);

	return SUCCESS;
}

s32 DpsX_PG(struct _DpsArg_ *Dpsx, u8 DpsAddr, IIC_Chan Chan)
{
	u16 data = 0, rdata = 0;
	u8 buf[L11_SIZE]  = {0x0};
	u8 rbuf[L11_SIZE] = {0x0};
	data = float_to_L16U(((Dpsx->SetValue)/1000.0)*0.8);
	buf[0] = data&0xff;
	buf[1] = (data >> 8)&0xff;

	do{
		if(SMBus_Write(buf, L11_SIZE, DpsAddr, POWER_GOOD_ON, Chan))
			return FAILURE;

		if(SMBus_Read(rbuf, L11_SIZE, DpsAddr, POWER_GOOD_ON, Chan))
			return FAILURE;

		rdata  = rbuf[0] << 8;
		rdata |= rbuf[1] << 0;

	}while(rdata != data);

	return SUCCESS;
}

s32 DpsX_Warning_TEMP(struct _DpsArg_ *Dpsx, u8 DpsAddr, IIC_Chan Chan)
{
	u16 data = 0, rdata = 0;
	u8 buf[L11_SIZE]  = {0x0};
	u8 rbuf[L11_SIZE] = {0x0};
	data = float_to_L11(WARNING_TEMP);	//报警温度
	buf[0] = data&0xff;
	buf[1] = (data >> 8)&0xff;

	do{
		if(SMBus_Write(buf, L11_SIZE, DpsAddr, OT_WARN_LIMIT, Chan))
			return FAILURE;

		if(SMBus_Read(rbuf, L11_SIZE, DpsAddr, OT_WARN_LIMIT, Chan))
			return FAILURE;

		rdata  = rbuf[0] << 8;
		rdata |= rbuf[1] << 0;

	}while(rdata != data);

	return SUCCESS;
}

s32 DpsX_Fault_TEMP(struct _DpsArg_ *Dpsx, u8 DpsAddr, IIC_Chan Chan)
{
	u16 data = 0, rdata = 0;
	u8 buf[L11_SIZE]  = {0x0};
	u8 rbuf[L11_SIZE] = {0x0};
	data = float_to_L11(WARNING_TEMP);	//报警温度
	buf[0] = data&0xff;
	buf[1] = (data >> 8)&0xff;

	do{
		if(SMBus_Write(buf, L11_SIZE, DpsAddr, OT_FAULT_LIMIT, Chan))
			return FAILURE;

		if(SMBus_Read(rbuf, L11_SIZE, DpsAddr, OT_FAULT_LIMIT, Chan))
			return FAILURE;

		rdata  = rbuf[0] << 8;
		rdata |= rbuf[1] << 0;

	}while(rdata != data);

	return SUCCESS;
}

s32 DpsX_IOUT_GAIN(struct _DpsArg_ *Dpsx, u8 DpsAddr, IIC_Chan Chan)
{
	u16 data = 0, rdata = 0;
	u8 buf[L11_SIZE]  = {0x0};
	u8 rbuf[L11_SIZE] = {0x0};
	data = float_to_L11(IOUT_GAIN);//校准值
	buf[0] = data&0xff;
	buf[1] = (data >> 8)&0xff;

	do{
		if(SMBus_Write(buf, L11_SIZE, DpsAddr, IOUT_CAL_GAIN, Chan))
			return FAILURE;

		if(SMBus_Read(rbuf, L11_SIZE, DpsAddr, IOUT_CAL_GAIN, Chan))
			return FAILURE;

		rdata  = rbuf[0] << 8;
		rdata |= rbuf[1] << 0;

	}while(rdata != data);

	return SUCCESS;
}

s32 DpsX_IOUT_OFFSET(struct _DpsArg_ *Dpsx, u8 DpsAddr, IIC_Chan Chan)
{
	u16 data = 0, rdata = 0;
	u8 buf[L11_SIZE]  = {0x0};
	u8 rbuf[L11_SIZE] = {0x0};
	data = float_to_L16U(IOUT_OFFSET);//设置值
	buf[0] = data&0xff;
	buf[1] = (data >> 8)&0xff;

	do{
		if(SMBus_Write(buf, L16U_SIZE, DpsAddr, IOUT_CAL_OFFSET, Chan))
			return FAILURE;

		if(SMBus_Read(rbuf, L16U_SIZE, DpsAddr, IOUT_CAL_OFFSET, Chan))
			return FAILURE;

		rdata  = rbuf[0] << 8;
		rdata |= rbuf[1] << 0;

	}while(rdata != data);

	return SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////////////

//设置输出电压
s32 DpsX_VOUT(struct _DpsArg_ *Dpsx, u8 DpsAddr, IIC_Chan Chan)
{
	u16 data = 0, rdata = 0;
	u8 buf[L11_SIZE]  = {0x0};
	u8 rbuf[L11_SIZE] = {0x0};
	data = float_to_L16U((Dpsx->SetValue)/1000.0);
	buf[0] = data&0xff;
	buf[1] = (data >> 8)&0xff;

	do{
		if(SMBus_Write(buf, L11_SIZE, DpsAddr, VOUT_COMMAND, Chan))
			return FAILURE;

		if(SMBus_Read(rbuf, L11_SIZE, DpsAddr, VOUT_COMMAND, Chan))
			return FAILURE;

		rdata  = rbuf[0] << 8;
		rdata |= rbuf[1] << 0;

	}while(rdata != data);

	return SUCCESS;
}

//设置上电延时时间
s32 DpsX_On_Delay(struct _DpsArg_ *Dpsx, u8 DpsAddr, IIC_Chan Chan)
{
	u16 data = 0, rdata = 0;
	u8 buf[L11_SIZE]  = {0x0};
	u8 rbuf[L11_SIZE] = {0x0};
	data = float_to_L11(Dpsx->Open.STime);//开始上升延时时间
	buf[0] = data&0xff;
	buf[1] = (data >> 8)&0xff;

	do{
		if(SMBus_Write(buf, L11_SIZE, DpsAddr, TON_DELAY, Chan))
			return FAILURE;

		if(SMBus_Read(rbuf, L11_SIZE, DpsAddr, TON_DELAY, Chan))
			return FAILURE;

		rdata  = rbuf[0] << 8;
		rdata |= rbuf[1] << 0;

	}while(rdata != data);

	return SUCCESS;
}

//设置下电延时时间
s32 DpsX_Off_Delay(struct _DpsArg_ *Dpsx, u8 DpsAddr, IIC_Chan Chan)
{
	u16 data = 0, rdata = 0;
	u8 buf[L11_SIZE]  = {0x0};
	u8 rbuf[L11_SIZE] = {0x0};
	data = float_to_L11(Dpsx->Close.STime);//开始下降延时时间
	buf[0] = data&0xff;
	buf[1] = (data >> 8)&0xff;

	do{
		if(SMBus_Write(buf, L11_SIZE, DpsAddr, TOFF_DELAY, Chan))
			return FAILURE;

		if(SMBus_Read(rbuf, L11_SIZE, DpsAddr, TOFF_DELAY, Chan))
			return FAILURE;

		rdata  = rbuf[0] << 8;
		rdata |= rbuf[1] << 0;

	}while(rdata != data);

	return SUCCESS;
}

//设置上升时间
s32 DpsX_Rise_Time(struct _DpsArg_ *Dpsx, u8 DpsAddr, IIC_Chan Chan)
{
	u16 data = 0, rdata = 0;
	u8 buf[L11_SIZE]  = {0x0};
	u8 rbuf[L11_SIZE] = {0x0};
	data = float_to_L11(Dpsx->Open.Keep);//上升时间
	buf[0] = data&0xff;
	buf[1] = (data >> 8)&0xff;

	do{
		if(SMBus_Write(buf, L11_SIZE, DpsAddr, TON_RISE, Chan))
			return FAILURE;

		if(SMBus_Read(rbuf, L11_SIZE, DpsAddr, TON_RISE, Chan))
			return FAILURE;

		rdata  = rbuf[0] << 8;
		rdata |= rbuf[1] << 0;

	}while(rdata != data);

	return SUCCESS;
}

//设置下降时间
s32 DpsX_Drop_Time(struct _DpsArg_ *Dpsx, u8 DpsAddr, IIC_Chan Chan)
{
	u16 data = 0, rdata = 0;
	u8 buf[L11_SIZE]  = {0x0};
	u8 rbuf[L11_SIZE] = {0x0};

	data = float_to_L11(Dpsx->Close.Keep);//下降时间
	buf[0] = data&0xff;
	buf[1] = (data >> 8)&0xff;
	do{
		if(SMBus_Write(buf, L11_SIZE, DpsAddr, TOFF_FALL, Chan))
			return FAILURE;

		if(SMBus_Read(rbuf, L11_SIZE, DpsAddr, TOFF_FALL, Chan))
			return FAILURE;

		rdata  = rbuf[0] << 8;
		rdata |= rbuf[1] << 0;

	}while(rdata != data);

	return SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////
//读取电源输入电压(V)
float Dps_VIN(struct _DpsArg_ *Dpsx, u8 DpsAddr, IIC_Chan Chan)
{
	u16 Regval = 0x0;
	u8 buf[2] = {0x0, 0x0};
	s32 Status = FAILURE;
	float vin = 0.0;

	Status = SMBus_Read(buf, L11_SIZE, DpsAddr, READ_VIN, Chan);
	if(Status == FAILURE)
		return -1;

	Regval |= buf[1];
	Regval = (Regval << 8) & buf[0];

	vin = L11_to_float(Regval);

	return vin;
}

//读取电源输出电压(V)
float Dps_VOUT(struct _DpsArg_ *Dpsx, u8 DpsAddr, IIC_Chan Chan)
{
	u16 Regval = 0x0;
	u8 buf[2] = {0x0, 0x0};
	s32 Status = FAILURE;
	float vout = 0.0;

	Status = SMBus_Read(buf, L16U_SIZE, DpsAddr, READ_VOUT, Chan);
	if(Status == FAILURE)
		return -1;

	Regval |= buf[1];
	Regval = (Regval << 8) & buf[0];

	vout = L16U_to_float(Regval);

	return vout;
}

//读取电源输出电流(A)
float Dps_IOUT(struct _DpsArg_ *Dpsx, u8 DpsAddr, IIC_Chan Chan)
{
	u16 Regval = 0x0;
	u8 buf[2] = {0x0, 0x0};
	s32 Status = FAILURE;
	float iout = 0.0;

	Status = SMBus_Read(buf, L11_SIZE, DpsAddr, READ_IOUT, Chan);
	if(Status == FAILURE)
		return -1;

	Regval |= buf[1];
	Regval = (Regval << 8) & buf[0];

	iout = L11_to_float(Regval);

	return iout;
}

//读取电源芯片温度(℃)
float Dps_TEMP(struct _DpsArg_ *Dpsx, u8 DpsAddr, IIC_Chan Chan)
{
	u16 Regval = 0x0;
	u8 buf[2] = {0x0, 0x0};
	s32 Status = FAILURE;
	float temp = 0.0;

	Status = SMBus_Read(buf, L11_SIZE, DpsAddr, READ_INTERNAL_TEMP, Chan);
	if(Status == FAILURE)
		return -1;

	Regval |= buf[1];
	Regval = (Regval << 8) & buf[0];

	temp = L11_to_float(Regval);

	return temp;
}

//写Dps寄存器
s32 Dps_WCode(struct _DpsArg_ *Dpsx, u8 Code, u8 Data, u8 DpsAddr, IIC_Chan Chan)
{
	u8 rdata = 0;

	do{
		if(SMBus_Write(&Data, 1, DpsAddr, Code, Chan))
			return FAILURE;

		if(SMBus_Read(&rdata, 1, DpsAddr, Code, Chan))
			return FAILURE;

	}while(rdata != Data);

	return SUCCESS;
}

//读取电源芯片状态, 返回电源状态(高8警告,低8故障)
u16 Dps_Status(struct _DpsArg_ *Dpsx, u8 DpsAddr, IIC_Chan Chan)
{
	u8  Rec = 0x0;
	DpsSta Data = {.uData = 0x0};
	s32 Status = FAILURE;

	Status = SMBus_Read(&Rec, BYTE_SIZE, DpsAddr, STATUS_VOUT, Chan);
	if(Status == FAILURE)
		Data.bit00 = 0x1;
	Data.bit01 = (Rec >> 7)&0x1;
	Data.bit02 = (Rec >> 4)&0x1;
	Data.bit09 = (Rec >> 6)&0x1;
	Data.bit10 = (Rec >> 5)&0x1;
	Rec = 0x0;

	Status = SMBus_Read(&Rec, BYTE_SIZE, DpsAddr, STATUS_IOUT, Chan);
	if(Status == FAILURE)
		Data.bit00 = 0x1;
	Data.bit03 = (Rec >> 7)&0x1;
	Data.bit11 = (Rec >> 5)&0x1;

	Rec = 0x0;
	Status = SMBus_Read(&Rec, BYTE_SIZE, DpsAddr, STATUS_TEMPERATURE, Chan);
	if(Status == FAILURE)
		Data.bit00 = 0x1;
	Data.bit04 = (Rec >> 7)&0x1;
	Data.bit12 = (Rec >> 6)&0x1;

	Rec = 0x0;
	Status = SMBus_Read(&Rec, BYTE_SIZE, DpsAddr, STATUS_INPUT, Chan);
	if(Status == FAILURE)
		Data.bit00 = 0x1;
	Data.bit05 = (Rec >> 7)&0x1;
	Data.bit06 = (Rec >> 4)&0x1;
	Data.bit13 = (Rec >> 6)&0x1;
	Data.bit14 = (Rec >> 5)&0x1;

	return (Data.uData);
}

///////////////////////////////////////////////////////////////////////////
/***********************************************************************
	[功	       能	]配置电源
	[参            数	]dpsx:电源参数指针, iicx:IIC通道
	[返    回    值	]操作结果
***********************************************************************/
s32 Dps_Init(struct _DpsArg_ *Dpsx, u16 id, u8 ProtectEn, u8 DpsAddr, IIC_Chan Chan)
{
	u32 error = 0x0;
	u8 DACtab[DPS_NUM] = {0};
	DACtab[6]  = 0;
	DACtab[7]  = 1;
	DACtab[14] = 2;
	DACtab[15] = 3;

	if((id == 6) || (id == 7) || (id == 14) || (id == 15))
	{
		if(Set_AD5694(0, DACtab[id], dps_info.AD5694_SlaveAddr, Chan))	//设置DAC电源为0v
		{
			if(ProtectEn)	//保护使能
				goto ERROR;
		}
	}
	else
	{
		if(Dps_WCode(Dpsx, OPERATION, 0x04,  DpsAddr, Chan))
		{
			if(ProtectEn)		//保护使能
				goto ERROR;
		}

		if(Dps_WCode(Dpsx, ON_OFF_CONFIG, 0x17,  DpsAddr, Chan))
		{
			if(ProtectEn)		//保护使能
				goto ERROR;
		}

		if(Dps_WCode(Dpsx, CLEAR_FAULTS, 0x04,  DpsAddr, Chan))
		{
			if(ProtectEn)		//保护使能
				goto ERROR;
		}

		if(DpsX_Warning_TEMP(Dpsx, DpsAddr, Chan))
		{
			if(ProtectEn)		//保护使能
				goto ERROR;
		}

		if(DpsX_Fault_TEMP(Dpsx, DpsAddr, Chan))
		{
			if(ProtectEn)		//保护使能
				goto ERROR;
		}

		if(DpsX_IOUT_GAIN(Dpsx, DpsAddr, Chan))
		{
			if(ProtectEn)		//保护使能
				goto ERROR;
		}

		if(DpsX_IOUT_OFFSET(Dpsx, DpsAddr, Chan))
		{
			if(ProtectEn)		//保护使能
				goto ERROR;
		}

		if(DpsX_MaxFAIL_VIN(Dpsx, DpsAddr, Chan))
		{
			if(ProtectEn)		//保护使能
				goto ERROR;
		}

		if(DpsX_MinFAIL_VIN(Dpsx, DpsAddr, Chan))
		{
			if(ProtectEn)		//保护使能
				goto ERROR;
		}

		if(DpsX_MaxWARN_VIN(Dpsx, DpsAddr, Chan))
		{
			if(ProtectEn)		//保护使能
				goto ERROR;
		}

		if(DpsX_MinWARN_VIN(Dpsx, DpsAddr, Chan))
		{
			if(ProtectEn)		//保护使能
				goto ERROR;
		}

		if(DpsX_Max_VOUT(Dpsx,  DpsAddr, Chan))
		{
			if(ProtectEn)		//保护使能
				goto ERROR;
		}

		if(DpsX_Min_VOUT(Dpsx, DpsAddr, Chan))
		{
			if(ProtectEn)		//保护使能
				goto ERROR;
		}

		if(DpsX_MaxMARG_VOUT(Dpsx, DpsAddr, Chan))
		{
			if(ProtectEn)		//保护使能
				goto ERROR;
		}

		if(DpsX_MinMARG_VOUT(Dpsx, DpsAddr, Chan))
		{
			if(ProtectEn)		//保护使能
				return FAILURE;
		}

		if(DpsX_Max_IOUT(Dpsx, DpsAddr, Chan))
		{
			if(ProtectEn)		//保护使能
				goto ERROR;
		}

		if(DpsX_PG(Dpsx, DpsAddr, Chan))
		{
			if(ProtectEn)		//保护使能
				goto ERROR;
		}

		if(DpsX_UpdateV(0.0, DpsAddr, Chan))
		{
			if(ProtectEn)		//保护使能
				goto ERROR;
		}
	}

	return SUCCESS;

ERROR:

	error |= 0x1 << (id + 8);

	return error;
}

//组装电源信息
void Build_Dps_Info(u16 DpsVI[], u16 DpsVO[], u16 DpsIO[], u16 DpsTemp[], u16 DpsStat[])
{
	u16 id = 0, j = 0;

	Dps_Arg * Dps_ptr = (Dps_Arg * )DPS_CFG_DATA_ADDR;

	for(id = 0; id < ((DPS_NUM/2) - 2); id++, j++) {
		  DpsVI[id] =    Dps_VIN(&Dps_ptr->Dsp[id], dps_info.DBMsg[0].DpsAddr[j], dps_info.DBMsg[0].Chan)*1000;
		  DpsVO[id] =   Dps_VOUT(&Dps_ptr->Dsp[id], dps_info.DBMsg[0].DpsAddr[j], dps_info.DBMsg[0].Chan)*1000;
		  DpsIO[id] =   Dps_IOUT(&Dps_ptr->Dsp[id], dps_info.DBMsg[0].DpsAddr[j], dps_info.DBMsg[0].Chan)*1000;
		DpsTemp[id] =   Dps_TEMP(&Dps_ptr->Dsp[id], dps_info.DBMsg[0].DpsAddr[j], dps_info.DBMsg[0].Chan)*1000;
		DpsStat[id] = Dps_Status(&Dps_ptr->Dsp[id], dps_info.DBMsg[0].DpsAddr[j], dps_info.DBMsg[0].Chan)     ;
	}

	j = 0;
	for(id = DPS_NUM/2; id < (DPS_NUM - 2); id++, j++) {
		  DpsVI[id] =    Dps_VIN(&Dps_ptr->Dsp[id], dps_info.DBMsg[1].DpsAddr[j], dps_info.DBMsg[1].Chan)*1000;
		  DpsVO[id] =   Dps_VOUT(&Dps_ptr->Dsp[id], dps_info.DBMsg[1].DpsAddr[j], dps_info.DBMsg[1].Chan)*1000;
		  DpsIO[id] =   Dps_IOUT(&Dps_ptr->Dsp[id], dps_info.DBMsg[1].DpsAddr[j], dps_info.DBMsg[1].Chan)*1000;
		DpsTemp[id] =   Dps_TEMP(&Dps_ptr->Dsp[id], dps_info.DBMsg[1].DpsAddr[j], dps_info.DBMsg[1].Chan)*1000;
		DpsStat[id] = Dps_Status(&Dps_ptr->Dsp[id], dps_info.DBMsg[1].DpsAddr[j], dps_info.DBMsg[1].Chan)     ;
	}
}

//AD5694BRUZ(n_dac < 4)
s32 Set_AD5694(float Vo, u8 n_dac, u8 SlaveAddr, IIC_Chan Chan)
{
	u16 data = 0, rdata = 0;
	u8 Code  = 0x0;
	u8 buf[2]  = {0x0};
	u8 rbuf[2] = {0x0};

	Code = (u8)((0x3 << 4) | ((0x1 << n_dac) & 0xf));
	data = (u16)(((Vo)/AD5694_VREF)*0xfff);
	buf[0] = data&0xff;
	buf[1] = (data >> 8)&0xff;

	do{
		if(SMBus_Write(buf, 2, SlaveAddr, Code, Chan))
			return FAILURE;

		if(SMBus_Read(rbuf, 2, SlaveAddr, Code, Chan))
			return FAILURE;

		rdata  = rbuf[0] << 8;
		rdata |= rbuf[1] << 0;

	}while(rdata != data);

	return SUCCESS;
}

//设置步进电压
s32 DpsX_UpdateV(float Value, u8 DpsAddr, IIC_Chan Chan)
{
	u16 data = 0, rdata = 0;
	u8 buf[L11_SIZE]  = {0x0};
	u8 rbuf[L11_SIZE] = {0x0};
	data = float_to_L16U(Value);
	buf[0] = data&0xff;
	buf[1] = (data >> 8)&0xff;

	do{
		if(SMBus_Write(buf, L16U_SIZE, DpsAddr, VOUT_COMMAND, Chan))
			return FAILURE;

		if(SMBus_Read(rbuf, L16U_SIZE, DpsAddr, VOUT_COMMAND, Chan))
			return FAILURE;

		rdata  = rbuf[0] << 8;
		rdata |= rbuf[1] << 0;

	}while(rdata != data);

	return SUCCESS;
}


