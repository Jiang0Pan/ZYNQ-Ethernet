/*
  ** @file           : 24lc256e.h
  ** @brief          : The Device Of 24LC256E/SNG(IIC EEPROM Device) Header File
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
#include "return_val.h"
#include "debug_config.h"
#include "24lc256e.h"


/*
  ** Define
*/
/* Product Nunber Size */
#define     PN_SIZE              (0x10)
/* Serial Nunber Size */
#define     SN_SIZE              (0x10)
/* Hardware Version Size */
#define     HW_SIZE              (0x10)
/* Firmware Version Size */
#define     FW_SIZE              (0x10)


/*
  ** Static Global Variable
*/
static u8 MPN[PN_SIZE] = {0x00};

/*
  ** Function Name        : Read_PN_SN
  ** Function Description : Iic Interface Bus Read EEPROM Data(P/N And S/N)
  ** Function Parameter   : Iic_Addr            : EEPROM Addr
  ** 						Pn                  : Product Number(P/N) Address
  ** 						Sn                  : Serial Number(S/N) Address
  ** Function Return      : READ_FAILED 		: Read Failed
  **                        READ_SUCCESS	    : Read Success
  ** Notes				  : None
*/
u8 Read_PN_SN(u8 Iic_Addr, u8 *Pn, u8 *Sn)
{

	return READ_SUCCESS;
}


/*
  ** (C) COPYRIGHT ChengDuHangke END OF FILE
*/


