#ifndef _IIC_H
#define _IIC_H



#include "xparameters.h"
#include "xiicps.h"
#include "error.h"



//IIC��ţ�IIC1������չ��IIC0��ps����eeprom
enum {
	DEV_IIC0 = XPAR_XIICPS_0_DEVICE_ID,
	DEV_IIC1 = XPAR_XIICPS_1_DEVICE_ID,
};

#define IIC0_SCLK_RATE		(100000) //100khz
#define IIC1_SCLK_RATE   	(100000) //100khz

#define TCA0_ADDR			(0x70)
#define TCA1_ADDR			(0x71)


typedef enum{
	IIC00 = 0x0,		//IIC00~IIC15Ϊ��չIIC
	IIC01 = 0x1,
	IIC02 = 0x2,
	IIC03 = 0x3,
	IIC04 = 0x4,
	IIC05 = 0x5,
	IIC06 = 0x6,
	IIC07 = 0x7,
	IIC08 = 0x8,
	IIC09 = 0x9,
	IIC10 = 0xA,
	IIC11 = 0xB,
	IIC12 = 0xC,
	IIC13 = 0xD,
	IIC14 = 0xE,
	IIC15 = 0xF,
	PSIIC,				//ps��IIC
}IIC_Chan;


#define IIC_REST_IO     (6)



//////////////////////////////////////////////////////

s32 Reset_ExpIIC(void);

s32 IIC_Init(void);

//IIC��ѯ����
s32 My_Write(u8 *MsgPtr, s32 ByteCount, u16 SlaveAddr, XIicPs* iicx);

//IIC��ѯ����
s32 My_Read (u8 *MsgPtr, s32 ByteCount, u16 SlaveAddr, XIicPs* iicx);

//ѡ��ͨ��
s32 Select_IIC(IIC_Chan Chan);

//дͨ��
s32 IIC_Write(u8 *MsgPtr, s32 ByteCount, u16 SlaveAddr, IIC_Chan Chan);

//��ͨ��
s32 IIC_Read (u8 *MsgPtr, s32 ByteCount, u16 SlaveAddr, IIC_Chan Chan);












#endif

