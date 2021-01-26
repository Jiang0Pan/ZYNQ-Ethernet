


#ifndef _MAX528_H
#define _MAX528_H





#include "Spi.h"
#include "error.h"
#include "fpga.h"

#define MAX528_REF			(5.0)
#define MAX528_DAC_LSB		(MAX528_REF / 256)


//DAC通道
typedef enum {
	DAC0 = 0x0,
	DAC1 = 0x1,
	DAC2 = 0x2,
	DAC3 = 0x3,
	DAC4 = 0x4,
	DAC5 = 0x5,
	DAC6 = 0x6,
	DAC7 = 0x7,
}DAC_Chan;


//max528 DAC数据传输格式
typedef union {
	struct {
		u8 Data;
		u8 Addr;
	};
	u16 TxDat;
}Max528;

/////////////////////////////////////////////////////////////////////////


   s32 Max528_Init(struct _REG_ * Cfg);
  s32 Max528_WROpt(struct _REG_ * Cfg, Max528 *Tx, u32 *Rdata, u8 CS);
s32 Max528_Set_DAC(struct _REG_ * Cfg, float Vo, DAC_Chan Chan, u8 CS);





#endif






