/*
  ** @file           : axi_lite.c
  ** @brief          : Axi Lite Source File
  **
  ** @attention
  **
  ** Copyright (c) 2020 ChengDuHangke.
  ** All rights reserved.
  **
  ** This software is licensed by ChengDuHangke under Ultimate Liberty license
  **
*/


/*
  ** Include
*/
#include "debug_config.h"
#include "return_val.h"
#include "axi_lite.h"


/*
  ** Define
*/



/*
  ** Function Name        : Axi_Lite_Read_Register
  ** Function Description : PS Read Axi_Lite Regsiter
  ** Function Parameter   : Addr                : Register Address
  ** 						Length              : Read Data Length
  ** 						Regdata             : Read Data Address
  ** Function Return      : READ_FAILED 		: Read Failed
  **                        READ_SUCCESS	    : Read Success
  ** Notes				  : None
*/
u8 Axi_Lite_Read_Register(u32 Addr, u32 Length ,u32 * Regdata)
{
	if (NULL == (u32 *)Addr) {
		return READ_FAILED;
	}

	if (NULL == Regdata) {
		return READ_FAILED;
	}

	if (0 >= Length) {
		return READ_FAILED;
	}

	*Regdata = *(volatile u32 *)Addr;

	return READ_SUCCESS;
}


/*
  ** Function Name        : Axi_Lite_Write_Register
  ** Function Description : PS Write Axi_Lite Regsiter
  ** Function Parameter   : Addr                : Register Address
  ** 						Length              : Read Data Length
  ** 						Regdata             : Read Data
  ** Function Return      : WRITE_FAILED 		: Write Failed
  **                        WRITE_SUCCESS	    : Write Success
  ** Notes				  : None
*/
u8 Axi_Lite_Write_Register(u32 Addr, u32 Length ,u32 Regdata)
{
	if (NULL == (u32 *)Addr) {
		return WRITE_FAILED;
	}

	if (NULL == Regdata) {
		return WRITE_FAILED;
	}

	if (0 >= Length) {
		return WRITE_FAILED;
	}

	*(volatile u32 *)Addr = Regdata;

	return WRITE_SUCCESS;
}

/*
  ** (C) COPYRIGHT ChengDuHangke END OF FILE
*/
