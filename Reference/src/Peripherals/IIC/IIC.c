#include "iic.h"


//IIC0�ṹ��,I2C1�ṹ
static XIicPs IIC[2];

//IICͨ���򿪱�־
static u16 IIC_CHAN_STAT = 0x0;



/***********************************************************************
	[��	       ��	]��λIICоƬ
	[��            ��	]��
	[��    ��    ֵ	]�������
***********************************************************************/
s32 Reset_ExpIIC(void)
{

	return SUCCESS;
}

/***********************************************************************
	[��	       ��	]IIC0,1��ʼ��
	[��            ��	]��
	[��    ��    ֵ	]�������
***********************************************************************/
s32 IIC_Init(void)
{
	int Status;
	XIicPs_Config *Config0, *Config1;

	//�ṹ������
	Config0 = XIicPs_LookupConfig(DEV_IIC0);
	if (NULL == Config0)
		return FAILURE;

	Config1 = XIicPs_LookupConfig(DEV_IIC1);
	if (NULL == Config1)
		return FAILURE;

	//�ṹ���ʼ��
	Status = XIicPs_CfgInitialize(&IIC[0], Config0, Config0->BaseAddress);
	if (Status != SUCCESS)
		return FAILURE;

	Status = XIicPs_CfgInitialize(&IIC[1], Config1, Config1->BaseAddress);
	if (Status != SUCCESS)
		return FAILURE;

	//Ӳ���Լ�
	Status = XIicPs_SelfTest(&IIC[0]);
	if (Status != SUCCESS)
		return FAILURE;

	Status = XIicPs_SelfTest(&IIC[1]);
	if (Status != SUCCESS)
		return FAILURE;

	//����IIC����
	Status = XIicPs_SetSClk(&IIC[0], IIC0_SCLK_RATE);
	if (Status != SUCCESS)
		return FAILURE;

	Status = XIicPs_SetSClk(&IIC[1], IIC1_SCLK_RATE);
	if (Status != SUCCESS)
		return FAILURE;

#if 1
	//��λiic��չ
	Status = Reset_ExpIIC();
	if (Status != SUCCESS){
		return FAILURE;
	}
#endif

	return SUCCESS;
}

/***********************************************************************
	[��	       ��	]IIC��ѯ����
	[��            ��	]MsgPtr:��Ϣָ��, ByteCount:��Ϣ����, SlaveAddr:�ӻ���ַ, iicx:iic�ṹָ��
	[��    ��    ֵ	]�������
***********************************************************************/
s32 My_Write(u8 *MsgPtr, s32 ByteCount, u16 SlaveAddr, XIicPs* iicx)
{
	u8 timeout = 3;

	if(XIicPs_MasterSendPolled(iicx, MsgPtr, ByteCount, SlaveAddr))	//����ʧ��ֱ�ӷ���
		return FAILURE;
	while (XIicPs_BusIsBusy(iicx))
	{
		if(TimeOutMS(&timeout))
		return FAILURE;
	};	//���߱��ͷŴ��������

	return SUCCESS;
}

/***********************************************************************
	[��	       ��	]IIC��ѯ����
	[��            ��	]MsgPtr:��Ϣָ��, ByteCount:��Ϣ����, SlaveAddr:�ӻ���ַ, iicx:iic�ṹָ��
	[��    ��    ֵ	]�������
***********************************************************************/
s32 My_Read(u8 *MsgPtr, s32 ByteCount, u16 SlaveAddr, XIicPs* iicx)
{
	u8 timeout = 3;

	if(XIicPs_MasterRecvPolled(iicx, MsgPtr, ByteCount, SlaveAddr))	//����ʧ��ֱ�ӷ���
		return FAILURE;
	while (XIicPs_BusIsBusy(iicx))
	{
		if(TimeOutMS(&timeout))
			return FAILURE;
	};	//���߱��ͷŴ��������

	return SUCCESS;
}

/***********************************************************************
	[��	       ��	]ѡ��iicͨ��
	[��            ��	]Chan:ͨ����
	[��    ��    ֵ	]�������
***********************************************************************/
s32 Select_IIC(IIC_Chan Chan)
{
	s32 Status = FAILURE;

	u16 CMD = 0x1 << Chan;
	u8 CMD0 = (CMD >> 0) & 0xff;
	//u8 CMD1 = (CMD >> 8) & 0xff;

	//�жϸ�ͨ���Ƿ��Ѿ���
	if(CMD == IIC_CHAN_STAT)//ͨ���Ѵ�
		return SUCCESS;

	Status = My_Write(&CMD0, 1, TCA0_ADDR, &IIC[1]);		//����TCA9548A_0ͨ��
	if(Status == FAILURE)							//����ʧ��ֱ�ӷ���
		return FAILURE;

	//���԰�ֻ��һ��IIC��չоƬ
/*
	Status = My_Write(&CMD1, 1, TCA1_ADDR, &IIC1);		//����TCA9548A_1ͨ��
	if(Status == XST_FAILURE)							//����ʧ��ֱ�ӷ���
		return XST_FAILURE;
*/
	IIC_CHAN_STAT = 0x0;								//��λ
	IIC_CHAN_STAT = CMD;								//��λͨ��MASK


	return SUCCESS;
}

/***********************************************************************
	[��	       ��	]ͨ��д����IICͨ��
	[��            ��	]MsgPtr:��Ϣָ��, ByteCount:��Ϣ����, SlaveAddr:�ӻ���ַ, Chan:ͨ��
	[��    ��    ֵ	]�������
***********************************************************************/
s32 IIC_Write(u8 *MsgPtr, s32 ByteCount, u16 SlaveAddr, IIC_Chan Chan)
{
	s32 Status = FAILURE;
	u8 timeout = 3;


	if(PSIIC == Chan)
	{
		if(XIicPs_MasterSendPolled(&IIC[0], MsgPtr, ByteCount, SlaveAddr))	//����ʧ��ֱ�ӷ���
			return FAILURE;

		while(XIicPs_BusIsBusy(&IIC[0]))
		{
			if(TimeOutMS(&timeout))
				return FAILURE;
		};	//���߱��ͷŴ��������
	}
	else
	{
		Status = Select_IIC(Chan);
		if(Status == FAILURE)
			return FAILURE;

		if(XIicPs_MasterSendPolled(&IIC[1], MsgPtr, ByteCount, SlaveAddr))	//����ʧ��ֱ�ӷ���
			return FAILURE;

		while(XIicPs_BusIsBusy(&IIC[1]))
		{
			if(TimeOutMS(&timeout))
				return FAILURE;
		};	//���߱��ͷŴ��������
	}

	return SUCCESS;
}

/***********************************************************************
	[��	       ��	]ͨ�ö�����IICͨ��
	[��            ��	]MsgPtr:��Ϣָ��, ByteCount:��Ϣ����, SlaveAddr:�ӻ���ַ, Chan:ͨ��
	[��    ��    ֵ	]�������
***********************************************************************/
s32 IIC_Read(u8 *MsgPtr, s32 ByteCount, u16 SlaveAddr, IIC_Chan Chan)
{
	s32 Status = FAILURE;
	u8 timeout = 3;

	if(PSIIC == Chan)
	{
		if(XIicPs_MasterRecvPolled(&IIC[0], MsgPtr, ByteCount, SlaveAddr))	//����ʧ��ֱ�ӷ���
			return FAILURE;
		while (XIicPs_BusIsBusy(&IIC[0]))
		{
			if(TimeOutMS(&timeout))
				return FAILURE;
		};	//���߱��ͷŴ��������
	}
	else
	{
		Status = Select_IIC(Chan);
		if(Status == FAILURE)
			return FAILURE;

		if(XIicPs_MasterRecvPolled(&IIC[1], MsgPtr, ByteCount, SlaveAddr))	//����ʧ��ֱ�ӷ���
			return FAILURE;
		while (XIicPs_BusIsBusy(&IIC[1]))
		{
			if(TimeOutMS(&timeout))
				return FAILURE;
		};	//���߱��ͷŴ��������
	}

	return SUCCESS;
}






