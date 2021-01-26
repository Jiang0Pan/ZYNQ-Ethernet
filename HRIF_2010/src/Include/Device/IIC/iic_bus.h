/*
  ** @file           : iic_bus.h
  ** @brief          : IIC Bus Interface Header File
  **
  ** @attention
  **
  ** Copyright (c) 2020 ChengDuHangke.
  ** All rights reserved.
  **
  ** This software is licensed by ChengDuHangke under Ultimate Liberty license
  **
*/


#ifndef SRC_INCLUDE_DEVICE_IIC_IIC_BUS_H_
#define SRC_INCLUDE_DEVICE_IIC_IIC_BUS_H_


/*
  ** function declaration
*/
u8 Iic_Init(void);
u8 iic_send(u8 *Data ,u16 Datalength, u16 Iicaddr, u32 Timeout);
u8 Iic_Recv(u8 *Data, u16 Datalength, u16 Iicaddr, u32 Timeout);


#endif /* SRC_INCLUDE_DEVICE_IIC_IIC_BUS_H_ */


/*
  ** (C) COPYRIGHT ChengDuHangke END OF FILE
*/
