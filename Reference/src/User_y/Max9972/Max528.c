



#include "max528.h"
#include "fpga_reg.h"


//Max528������
s32 Max528_WROpt(struct _REG_ * Cfg, Max528 *Tx, u32 *Rdata, u8 CS)
{
	u32 busy = 0x0;

	if(Fpga_ROpt(Cfg, MAX528BUSY + (0x1000 * ((CS > 0) ? 1 : 0)), &busy))
		return FAILURE;
	if(busy)
		return FAILURE;

	if(Fpga_WOpt(Cfg, MAX528TX + (0x1000 * ((CS > 0) ? 1 : 0)), Tx->TxDat))
		return FAILURE;

	if(NULL != Rdata)
		return Fpga_ROpt(Cfg, MAX528RX + (0x1000 * ((CS > 0) ? 1 : 0)), Rdata);

	return SUCCESS;
}

/***********************************************************************
	[��	       ��	]Max528��ʼ��
	[��            ��	]spix:spi���
	[��    ��    ֵ	]�Ƿ�ok
***********************************************************************/
s32 Max528_Init(struct _REG_ * Cfg)
{
	u16 ch = DAC0;

	Max528  NopData = {
		.Data = 0x00,
		.Addr = 0x00,
	};

	Max528 BuffMode = {
		.Data = 0xff,
		.Addr = 0x00,
	};

	Max528  DAC     = {
		.Data = (u8)(0),	//��������
		.Addr = 0x1 << ch,
	};

	if(Max528_WROpt(Cfg, &NopData, NULL, 0))	//����NOP
		return FAILURE;

	if(Max528_WROpt(Cfg, &BuffMode, NULL, 0)) 	//����BUffer mode ȫ����
		return FAILURE;

	if(Max528_WROpt(Cfg, &NopData, NULL, 1))	//����NOP
		return FAILURE;

	if(Max528_WROpt(Cfg, &BuffMode, NULL, 1)) 	//����BUffer mode ȫ����
		return FAILURE;

	for(ch = DAC0; ch <= DAC7; ch++)
	{
		DAC.Addr = 0x1 << ch;
		if(Max528_WROpt(Cfg, &DAC, NULL, 0)) 	//����528_0 DACĬ��ֵ
			return FAILURE;

		if(Max528_WROpt(Cfg, &DAC, NULL, 1)) 	//����528_0 DACĬ��ֵ
			return FAILURE;
	}

	return SUCCESS;
}

/***********************************************************************
	[��	       ��	]Max528����DAC
	[��            ��	]Vo:��ѹ, Chan:adcͨ��, CS:528���
	[��    ��    ֵ	]�Ƿ�ok
***********************************************************************/
s32 Max528_Set_DAC(struct _REG_ * Cfg, float Vo, DAC_Chan Chan, u8 CS)
{
	Max528  DAC = {
		.Data = (u8)((MAX528_DAC_LSB * Vo) + 0.5),	//��������
		.Addr = 0x1 << Chan,
	};

	u32 Rdata = 0x0;

	if(Max528_WROpt(Cfg, &DAC, &Rdata, CS)) 						//����DAC
		return FAILURE;

	return SUCCESS;
}


