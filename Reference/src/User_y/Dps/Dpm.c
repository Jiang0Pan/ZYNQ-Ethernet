



#include "dpm.h"


/***********************************************************************
	[功	       能	]计算电流校准值
	[参            数	]无
	[返    回    值	]校准值
***********************************************************************/
u16 Dpm_Gain_Count(void)
{
	return ((u16)((DPM_SCALE/DPM_VSHUNT_FS) * DPM_ADC_RES));
}

/***********************************************************************
	[功	       能	]计算寄存器值 EQ_N0:公式1(无符号),EQ_N1:公式2(有符号),芯片手册
	[参            数	]Regval:寄存器,EQ_N:公式编号
	[返    回    值	]计算后寄存器的值
***********************************************************************/
int Dpm_Reg_Val(u16 Regval, u8 EQ_N)
{
	int val = 0;
	u8 bitn = 0;
	for(bitn = 0; bitn <= 14; bitn++)
	{
		val +=  ((Regval >> bitn) & 0x1) * (0x1 << bitn);
	}
	if(EQ_N > 1)
		val -= ((Regval >> 15) & 0x1) * (0x1 << 15);
	else
		val += ((Regval >> 15) & 0x1) * (0x1 << 15);

	return val;
}

/***********************************************************************
	[功	       能	]转换DPM Vbus(VOUT)
	[参            数	]dpm:dpm参数,iicx:iic编号
	[返    回    值	]测得电压值
***********************************************************************/
float Dpm_VBus(Dpm_Info *dpm, IIC_Chan Chan)
{
	u16 Regval = 0x0;
	u8 buf[2] = {0x0, 0x0};
	s32 Status = FAILURE;
	float vbus = 0.0;

	Status = SMBus_Read(buf, 2, dpm->DpmAddr, DPM_READ_VOUT, Chan);
	if(Status == FAILURE)
		return -1;

	Regval |= buf[1];
	Regval = (Regval << 8) & buf[0];

	int val = Dpm_Reg_Val(Regval, 1);

	if(dpm->ChipVer > 0)
		vbus = val * (DPM_VBUSLSB_12);
	else
		vbus = val * (DPM_VBUSLSB_60);

	return vbus;
}

/***********************************************************************
	[功	       能	]转换DPM VSHUNT(分流电阻电压)
	[参            数	]dpm:dpm参数,iicx:iic编号
	[返    回    值	]测得电压值
***********************************************************************/
float Dpm_VShunt(Dpm_Info *dpm, IIC_Chan Chan)
{
	u16 Regval = 0x0;
	u8 buf[2] = {0x0, 0x0};
	s32 Status = FAILURE;
	float vshunt = 0.0;

	Status = SMBus_Read(buf, 2, dpm->DpmAddr, DPM_READ_VSHUNT_OUT, Chan);
	if(Status == FAILURE)
		return -1;

	Regval |= buf[1];
	Regval = (Regval << 8) & buf[0];

	int val = Dpm_Reg_Val(Regval, 2);

	vshunt = val * DPM_VSHUNTLSB;

	return vshunt;
}

/***********************************************************************
	[功	       能	]转换DPM 输出电流(mA)
	[参            数	]dpm:dpm参数,iicx:iic编号
	[返    回    值	]测得电流值
***********************************************************************/
float Dpm_IOUT(Dpm_Info *dpm, IIC_Chan Chan)
{
	u16 Regval = 0x0;
	u8 buf[2] = {0x0, 0x0};
	s32 Status = FAILURE;
	float iout = 0.0;

	Status = SMBus_Read(buf, 2, dpm->DpmAddr, DPM_READ_IOUT, Chan);
	if(Status == FAILURE)
		return -1;

	Regval |= buf[1];
	Regval = (Regval << 8) & buf[0];

	int val = Dpm_Reg_Val(Regval, 2);

	iout = val * DPM_CURRENTLSB;

	return iout;
}

/***********************************************************************
	[功	       能	]转换DPM功率(v.mA)
	[参            数	]dpm:dpm参数,iicx:iic编号
	[返    回    值	]测得功率
***********************************************************************/
float Dpm_POUT(Dpm_Info *dpm, IIC_Chan Chan)
{
	u16 Regval = 0x0;
	u8 buf[2] = {0x0, 0x0};
	s32 Status = FAILURE;
	float pout = 0.0;

	Status = SMBus_Read(buf, 2, dpm->DpmAddr, DPM_READ_POUT, Chan);
	if(Status == FAILURE)
		return -1;

	Regval |= buf[1];
	Regval = (Regval << 8) & buf[0];

	int val = Dpm_Reg_Val(Regval, 2);

	if(dpm->ChipVer > 0)
		pout = val * (DPM_VBUSLSB_12*DPM_CURRENTLSB) * 40000;
	else
		pout = val * (DPM_VBUSLSB_60*DPM_CURRENTLSB) * 40000;

	return pout;
}

/***********************************************************************
	[功	       能	]DPM温度(℃)
	[参            数	]dpm:dpm参数,iicx:iic编号
	[返    回    值	]测得dpm温度值
***********************************************************************/
float Dpm_TEMP(Dpm_Info *dpm, IIC_Chan Chan)
{
	u16 Regval = 0x0;
	u8 buf[2] = {0x0, 0x0};
	s32 Status = FAILURE;
	float temp = 0.0;

	Status = SMBus_Read(buf, 2, dpm->DpmAddr, DPM_READ_TEMPERATURE_1, Chan);
	if(Status == FAILURE)
		return -1;

	Regval |= buf[1];
	Regval = (Regval << 8) & buf[0];

	int val = Dpm_Reg_Val(Regval, 2);

	temp = val * 0.016;

	return temp;
}

/***********************************************************************
	[功	       能	]转换DPM最大峰值电流(mA)
	[参            数	]dpm:dpm参数,iicx:iic编号
	[返    回    值	]测得电流值
***********************************************************************/
float Dpm_Max_IOUT(Dpm_Info *dpm, IIC_Chan Chan)
{
	u16 Regval = 0x0;
	u8 buf[2] = {0x0, 0x0};
	s32 Status = FAILURE;
	float maxiout = 0.0;

	Status = SMBus_Read(buf, 2, dpm->DpmAddr, DPM_READ_PEAK_MAX_IOUT, Chan);
	if(Status == FAILURE)
		return -1;

	Regval |= buf[1];
	Regval = (Regval << 8) & buf[0];


	return maxiout;
}

/***********************************************************************
	[功	       能	]转换DPM最小峰值电流(mA)
	[参            数	]dpm:dpm参数,iicx:iic编号
	[返    回    值	]测得电流值
***********************************************************************/
float Dpm_Min_IOUT(Dpm_Info *dpm, IIC_Chan Chan)
{
	u16 Regval = 0x0;
	u8 buf[2] = {0x0, 0x0};
	s32 Status = FAILURE;
	float miniout = 0.0;

	Status = SMBus_Read(buf, 2, dpm->DpmAddr, DPM_READ_PEAK_MIN_IOUT, Chan);
	if(Status == FAILURE)
		return -1;

	Regval |= buf[1];
	Regval = (Regval << 8) & buf[0];

	return miniout;
}

/***********************************************************************
	[功	       能	]配置DPM
	[参            数	]dpm:dpm参数,iicx:iic编号
	[返    回    值	]配置结果
***********************************************************************/
s32 Dpm_Init(Dpm_Info *dpm, IIC_Chan Chan)
{
	s32 Status  = FAILURE;
	u8 value[4]  = {0x0, 0x0, 0x0, 0x0};

	u32 data = 0;

	//复位设备
	Status = SMBus_Code(dpm->DpmAddr, DPM_RESTORE_DEFAULT_LL, Chan);
	if(Status == FAILURE)
		return FAILURE;

	//读取版本信息
	Status = SMBus_Read((u8*)&(dpm->ChipVer), 2, dpm->DpmAddr, DPM_IC_DEVICE_REV, Chan);
	if(Status == FAILURE)
		return FAILURE;

	//设置工作模式
	value[0] = 0x80;
	Status = SMBus_Write(value, 1, dpm->DpmAddr, DPM_OPERATION, Chan);
	if(Status == FAILURE)
		return FAILURE;

	//设置ADC模式
	value[0] = 0x00 | 0x1 << 3 | 0x10 << 0;
	Status = SMBus_Write(value, 1, dpm->DpmAddr, DPM_SET_DPM_MODE, Chan);
	if(Status == FAILURE)
		return FAILURE;

	//配置ADC,设置电流采样频率、时间
	value[0] = 0x00 | 0xB << 3 | 0x0 << 0;
	value[1] = 0x00;
	Status = SMBus_Write(value, 2, dpm->DpmAddr, DPM_CONFIG_ICHANNEL, Chan);
	if(Status == FAILURE)
		return FAILURE;

	//设置电流校准参数
	data = Dpm_Gain_Count();
	value[0] = data & 0xff;
	value[1] = (data >> 8) & 0xff;
	Status = SMBus_Write(value, 2, dpm->DpmAddr, DPM_IOUT_CAL_GAIN, Chan);
	if(Status == FAILURE)
		return FAILURE;

	//配置ADC,设置电压采样频率、时间
	value[0] = 0x00 | 0xB << 3 | 0x0 << 0;
	value[1] = 0x00;
	Status = SMBus_Write(value, 2, dpm->DpmAddr, DPM_CONFIG_VCHANNEL, Chan);
	if(Status == FAILURE)
		return FAILURE;

	//使能峰值电流检测
	value[0] = 0x00 | 0x1;
	Status = SMBus_Write(value, 1, dpm->DpmAddr, DPM_CONFIG_PEAK_DET, Chan);
	if(Status == FAILURE)
		return FAILURE;

	//配置输出电压阈值(过压)默认
	data = 0x0;
	data |= (~(0x1 << 9)) | (DPM_MAX_VBUS << 6) | 0x3f;
	value[0] = data & 0xff;
	value[1] = (data >> 8) & 0xff;
	Status = SMBus_Write(value, 2, dpm->DpmAddr, DPM_VOUT_OV_THRESHOLD_SET, Chan);
	if(Status == FAILURE)
		return FAILURE;

	//配置输出电压阈值(欠压)50%
	value[0] = 0x20;
	Status = SMBus_Write(value, 1, dpm->DpmAddr, DPM_VOUT_UV_THRESHOLD_SET, Chan);
	if(Status == FAILURE)
		return FAILURE;

	//配置输出电流阈值
	value[0] = 0x3f;
	value[1] = 0x0;
	Status = SMBus_Write(value, 2, dpm->DpmAddr, DPM_IOUT_OC_THRESHOLD_SET, Chan);
	if(Status == FAILURE)
		return FAILURE;

#if 1
	//清除Vout警告信息
	value[0] = 0x3 << 5;
	Status = SMBus_Write(value, 1, dpm->DpmAddr, DPM_CLEAR_FAULTS, Chan);
	if(Status == FAILURE)
		return FAILURE;

	//清除温度警告信息
	value[0] = 0x1 << 6;
	Status = SMBus_Write(value, 1, dpm->DpmAddr, DPM_STATUS_TEMPERATURE, Chan);
	if(Status == FAILURE)
		return FAILURE;

	//清除故障警告
	value[0] = (0x1 << 1) | (0x1 << 5) | (0x1 << 6) | (0x1 << 7);
	Status = SMBus_Write(value, 1, dpm->DpmAddr, DPM_STATUS_CML, Chan);
	if(Status == FAILURE)
		return FAILURE;

	//清除故障警告
	value[0] = (0x1 << 1) | (0x1 << 2) | (0xf << 3) | (0x1 << 7);
	Status = SMBus_Write(value, 1, dpm->DpmAddr, DPM_STATUS_BYTE, Chan);
	if(Status == FAILURE)
		return FAILURE;

	//清除故障警告
	data = 0x0;
	data |=  (0x1 << 15) | (0x1 << 14) | (0xf << 8);
	value[0] = 0x0;
	value[1] = (data >> 8) & 0xff;
	Status = SMBus_Write(value, 2, dpm->DpmAddr, DPM_STATUS_WORD, Chan);
	if(Status == FAILURE)
		return FAILURE;

#endif


	return SUCCESS;
}


















































