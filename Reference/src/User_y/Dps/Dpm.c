



#include "dpm.h"


/***********************************************************************
	[��	       ��	]�������У׼ֵ
	[��            ��	]��
	[��    ��    ֵ	]У׼ֵ
***********************************************************************/
u16 Dpm_Gain_Count(void)
{
	return ((u16)((DPM_SCALE/DPM_VSHUNT_FS) * DPM_ADC_RES));
}

/***********************************************************************
	[��	       ��	]����Ĵ���ֵ EQ_N0:��ʽ1(�޷���),EQ_N1:��ʽ2(�з���),оƬ�ֲ�
	[��            ��	]Regval:�Ĵ���,EQ_N:��ʽ���
	[��    ��    ֵ	]�����Ĵ�����ֵ
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
	[��	       ��	]ת��DPM Vbus(VOUT)
	[��            ��	]dpm:dpm����,iicx:iic���
	[��    ��    ֵ	]��õ�ѹֵ
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
	[��	       ��	]ת��DPM VSHUNT(���������ѹ)
	[��            ��	]dpm:dpm����,iicx:iic���
	[��    ��    ֵ	]��õ�ѹֵ
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
	[��	       ��	]ת��DPM �������(mA)
	[��            ��	]dpm:dpm����,iicx:iic���
	[��    ��    ֵ	]��õ���ֵ
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
	[��	       ��	]ת��DPM����(v.mA)
	[��            ��	]dpm:dpm����,iicx:iic���
	[��    ��    ֵ	]��ù���
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
	[��	       ��	]DPM�¶�(��)
	[��            ��	]dpm:dpm����,iicx:iic���
	[��    ��    ֵ	]���dpm�¶�ֵ
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
	[��	       ��	]ת��DPM����ֵ����(mA)
	[��            ��	]dpm:dpm����,iicx:iic���
	[��    ��    ֵ	]��õ���ֵ
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
	[��	       ��	]ת��DPM��С��ֵ����(mA)
	[��            ��	]dpm:dpm����,iicx:iic���
	[��    ��    ֵ	]��õ���ֵ
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
	[��	       ��	]����DPM
	[��            ��	]dpm:dpm����,iicx:iic���
	[��    ��    ֵ	]���ý��
***********************************************************************/
s32 Dpm_Init(Dpm_Info *dpm, IIC_Chan Chan)
{
	s32 Status  = FAILURE;
	u8 value[4]  = {0x0, 0x0, 0x0, 0x0};

	u32 data = 0;

	//��λ�豸
	Status = SMBus_Code(dpm->DpmAddr, DPM_RESTORE_DEFAULT_LL, Chan);
	if(Status == FAILURE)
		return FAILURE;

	//��ȡ�汾��Ϣ
	Status = SMBus_Read((u8*)&(dpm->ChipVer), 2, dpm->DpmAddr, DPM_IC_DEVICE_REV, Chan);
	if(Status == FAILURE)
		return FAILURE;

	//���ù���ģʽ
	value[0] = 0x80;
	Status = SMBus_Write(value, 1, dpm->DpmAddr, DPM_OPERATION, Chan);
	if(Status == FAILURE)
		return FAILURE;

	//����ADCģʽ
	value[0] = 0x00 | 0x1 << 3 | 0x10 << 0;
	Status = SMBus_Write(value, 1, dpm->DpmAddr, DPM_SET_DPM_MODE, Chan);
	if(Status == FAILURE)
		return FAILURE;

	//����ADC,���õ�������Ƶ�ʡ�ʱ��
	value[0] = 0x00 | 0xB << 3 | 0x0 << 0;
	value[1] = 0x00;
	Status = SMBus_Write(value, 2, dpm->DpmAddr, DPM_CONFIG_ICHANNEL, Chan);
	if(Status == FAILURE)
		return FAILURE;

	//���õ���У׼����
	data = Dpm_Gain_Count();
	value[0] = data & 0xff;
	value[1] = (data >> 8) & 0xff;
	Status = SMBus_Write(value, 2, dpm->DpmAddr, DPM_IOUT_CAL_GAIN, Chan);
	if(Status == FAILURE)
		return FAILURE;

	//����ADC,���õ�ѹ����Ƶ�ʡ�ʱ��
	value[0] = 0x00 | 0xB << 3 | 0x0 << 0;
	value[1] = 0x00;
	Status = SMBus_Write(value, 2, dpm->DpmAddr, DPM_CONFIG_VCHANNEL, Chan);
	if(Status == FAILURE)
		return FAILURE;

	//ʹ�ܷ�ֵ�������
	value[0] = 0x00 | 0x1;
	Status = SMBus_Write(value, 1, dpm->DpmAddr, DPM_CONFIG_PEAK_DET, Chan);
	if(Status == FAILURE)
		return FAILURE;

	//���������ѹ��ֵ(��ѹ)Ĭ��
	data = 0x0;
	data |= (~(0x1 << 9)) | (DPM_MAX_VBUS << 6) | 0x3f;
	value[0] = data & 0xff;
	value[1] = (data >> 8) & 0xff;
	Status = SMBus_Write(value, 2, dpm->DpmAddr, DPM_VOUT_OV_THRESHOLD_SET, Chan);
	if(Status == FAILURE)
		return FAILURE;

	//���������ѹ��ֵ(Ƿѹ)50%
	value[0] = 0x20;
	Status = SMBus_Write(value, 1, dpm->DpmAddr, DPM_VOUT_UV_THRESHOLD_SET, Chan);
	if(Status == FAILURE)
		return FAILURE;

	//�������������ֵ
	value[0] = 0x3f;
	value[1] = 0x0;
	Status = SMBus_Write(value, 2, dpm->DpmAddr, DPM_IOUT_OC_THRESHOLD_SET, Chan);
	if(Status == FAILURE)
		return FAILURE;

#if 1
	//���Vout������Ϣ
	value[0] = 0x3 << 5;
	Status = SMBus_Write(value, 1, dpm->DpmAddr, DPM_CLEAR_FAULTS, Chan);
	if(Status == FAILURE)
		return FAILURE;

	//����¶Ⱦ�����Ϣ
	value[0] = 0x1 << 6;
	Status = SMBus_Write(value, 1, dpm->DpmAddr, DPM_STATUS_TEMPERATURE, Chan);
	if(Status == FAILURE)
		return FAILURE;

	//������Ͼ���
	value[0] = (0x1 << 1) | (0x1 << 5) | (0x1 << 6) | (0x1 << 7);
	Status = SMBus_Write(value, 1, dpm->DpmAddr, DPM_STATUS_CML, Chan);
	if(Status == FAILURE)
		return FAILURE;

	//������Ͼ���
	value[0] = (0x1 << 1) | (0x1 << 2) | (0xf << 3) | (0x1 << 7);
	Status = SMBus_Write(value, 1, dpm->DpmAddr, DPM_STATUS_BYTE, Chan);
	if(Status == FAILURE)
		return FAILURE;

	//������Ͼ���
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


















































