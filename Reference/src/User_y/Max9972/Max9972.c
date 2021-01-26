

#include "max9972.h"


s32 Max9972_WROpt(struct _REG_ * Cfg, Max9972 *Tx, u32 *Rdata, u8 CS)
{
	u32 busy = 0x0;

	if(Fpga_ROpt(Cfg, MAX9972BUSY, &busy))
		return FAILURE;
	if(busy)
		return FAILURE;

	if(Fpga_WOpt(Cfg, MAX9972TX + (0x4 * CS), Tx->Data))
		return FAILURE;

	if(NULL != Rdata)
		return Fpga_ROpt(Cfg, MAX9972RX + (0x4 * CS), Rdata);

	return SUCCESS;
}

//9972≥ı ºªØ≈‰÷√
s32 Max9972_InitCfg(struct _REG_ * Cfg)
{
	u16 i = 0x0;
	Max9972 Tx = {
		.TERM		= 0,
		.LLEAK      = 0,
		.SENSE_EN   = 0,
		.FORCE_EN   = 0,
		.EN_LOAD_L  = 0,
		.EN_LOAD_H  = 0,
		.CH1      	= 1,
		.CH2      	= 1,
		.CH3      	= 1,
		.CH4      	= 1,
	};

	for(i = 0; i < 8; i++)
	{
		if(Max9972_WROpt(Cfg, &Tx, NULL, i))
			return FAILURE;
	}

	return SUCCESS;
}
