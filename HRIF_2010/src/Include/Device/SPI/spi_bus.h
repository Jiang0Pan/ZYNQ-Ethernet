/*
  ** @file           : spi_bus.h
  ** @brief          : Spi Bus Interface Header File
  **
  ** @attention
  **
  ** Copyright (c) 2020 ChengDuHangke.
  ** All rights reserved.
  **
  ** This software is licensed by ChengDuHangke under Ultimate Liberty license
  **
*/

#ifndef SRC_INCLUDE_DEVICE_SPI_SPI_BUS_H_
#define SRC_INCLUDE_DEVICE_SPI_SPI_BUS_H_


#include "xil_types.h"


/*
  ** Function Declaration
*/
u8 Spi_Init(void);
u8 Spi_ReadWrite(u8 *Txdata ,u8 *Rxdata, u32 Length);


#endif /* SRC_INCLUDE_DEVICE_SPI_SPI_BUS_H_ */


/*
  ** (C) COPYRIGHT ChengDuHangke END OF FILE
*/
