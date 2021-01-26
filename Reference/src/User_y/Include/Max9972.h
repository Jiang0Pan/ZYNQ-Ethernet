
#ifndef _MAX9972_H
#define _MAX9972_H



#include "error.h"
#include "fpga.h"

//9972¿ØÖÆ
typedef union {
	struct{
		u16 TERM:		1;
		u16 LLEAK:		1;
		u16 SENSE_EN:	1;
		u16 FORCE_EN:	1;
		u16 EN_LOAD_L:	1;
		u16 EN_LOAD_H:	1;
		u16 :			2;
		u16 CH1:		1;
		u16 CH2:		1;
		u16 CH3:		1;
		u16 CH4:		1;
		u16 :			4;
	};
	u16  Data;
}Max9972;

////////////////////////////////////////////////////////////////////////////


s32 Max9972_InitCfg(struct _REG_ * Cfg);
s32   Max9972_WROpt(struct _REG_ * Cfg, Max9972 *Tx, u32 *Rdata, u8 CS);



#endif






