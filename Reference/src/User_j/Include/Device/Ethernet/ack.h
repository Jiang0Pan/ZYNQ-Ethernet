/*
  ** @file           : ack.c
  ** @brief          : Tcp Server Receive Data Ack Source File
  **
  ** @attention
  **
  ** Copyright (c) 2020 ChengDuHangke.
  ** All rights reserved.
  **
  ** This software is licensed by ChengDuHangke under Ultimate Liberty license
  **
*/


#ifndef ACK_H_
#define ACK_H_


/*
  ** Include
*/


/*
  ** Function Prototype
*/
u8 Ack_Init(u8 Ip);
u8 Tcp_Ack(void);
u8 Tcp_Nack(void);

#endif /* ACK_H_ */


/*
  ** (C) COPYRIGHT ChengDuHangke END OF FILE
*/
