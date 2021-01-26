








#ifndef _CPLD_H
#define _CPLD_H




#include "Spi.h"


#define  WOPT				(0x1)
#define  ROPT				(0x0)

#define  CPLD_SPI			(SPI0)
#define  SHARKDELAY			(5)				//us
#define  ONDELAY			(0)				//ms


#define  Reveru16(U)	((U) = ((((U) >> 8) & 0x00ff) | (((U) << 8) & 0xff00)))


//CPLD�Ĵ���
enum {
	ERROR_NUM 		= 0x01,

	ENABLE_LV1 		= 0x02,  //����A-F ��һ����/�µ�
	ENABLE_LV2 		= 0x03,	 //����10����Դ
	ENABLE_LV3 		= 0x04,	 //����A-F �ڶ�����/�µ�

	CHA_ON_DELAY 	= 0x05,
	CHB_ON_DELAY 	= 0x06,
	CHC_ON_DELAY 	= 0x07,
	CHD_ON_DELAY 	= 0x08,
	CHE_ON_DELAY 	= 0x09,
	CHF_ON_DELAY 	= 0x0A,
	CH1_ON_DELAY 	= 0x0B,
	CH2_ON_DELAY 	= 0x0C,
	CH3_ON_DELAY 	= 0x0D,
	CH4_ON_DELAY 	= 0x0E,

	CHA_ERROR_DELAY = 0x0F,
	CHB_ERROR_DELAY = 0x10,
	CHC_ERROR_DELAY = 0x11,
	CHD_ERROR_DELAY = 0x12,
	CHE_ERROR_DELAY = 0x13,
	CHF_ERROR_DELAY = 0x14,
	CH1_ERROR_DELAY = 0x15,
	CH2_ERROR_DELAY = 0x16,
	CH3_ERROR_DELAY = 0x17,
	CH4_ERROR_DELAY = 0x18,

	POWER_ON 		= 0x19,
};


//cpld���ݽṹ
typedef union {
	struct {				//			 Data		RW  Addr
		u32 Addr:	 7;		//��λ��ʼ________________ _ _______
		u32 RW:		 1;
		u32 Data:   16;
	};
	u8  Bytes[3];
}Cpld_Xfer;

////////////////////////////////////////////////

void Delayms(u16 ms);

s32 Switch(u16 Mask);

s32 Cpld_Transfer(Cpld_Xfer *Xfer, u16 *Rdata);

//�����ж�����ʱ��
s32 Cpld_SetShark(u8 id, u16 delayus);

//���õ�����Դ�ϵ�ʱ��
s32 Cpld_SetDelay(u8 id, u16 delayms);

//��ʼ��CPLD
s32 Cpld_Init(u8 bid);





#endif

