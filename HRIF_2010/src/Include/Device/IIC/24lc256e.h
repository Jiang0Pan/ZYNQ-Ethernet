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


#ifndef SRC_INCLUDE_DEVICE_IIC_24LC256E_H_
#define SRC_INCLUDE_DEVICE_IIC_24LC256E_H_


/*
  ** Include
*/
#include "xil_types.h"


/*
  ** Define
*/
/* Management Board EEPROM IIC Address */
#define 	MB_EEPROM_IIC_ADDR  (0xA0 >> 1)


/*
  ** function declaration
*/
u8 Read_PN_SN(u8 Iic_Addr, u8 *Pn, u8 *Sn);


#endif /* SRC_INCLUDE_DEVICE_IIC_24LC256E_H_ */


/*
  ** (C) COPYRIGHT ChengDuHangke END OF FILE
*/
