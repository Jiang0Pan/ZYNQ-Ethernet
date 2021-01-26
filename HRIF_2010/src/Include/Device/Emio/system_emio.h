/*
  ** @file           : emio.h
  ** @brief          : Emio Header File
  **
  ** @attention
  **
  ** Copyright (c) 2020 ChengDuHangke.
  ** All rights reserved.
  **
  ** This software is licensed by ChengDuHangke under Ultimate Liberty license
  **
*/


#ifndef __SYSTEM_EMIO_H_
#define __SYSTEM_EMIO_H_

/*
  ** Include
*/
#include "xGpiops.h"


/*
  ** Define
*/
#define     ON 			        (1)
#define     OFF                 (0)


/*
  ** Function Prototype
*/
u8 Emio_Config(u16 DeviceId,XGpioPs *Emio);
u8 Get_Ipaddr(XGpioPs *Emio);
u8 Set_System_Lwip_Led(XGpioPs *Emio,u8 Status);
u8 Set_System_Cpu0_Led(XGpioPs *Emio,u8 Status);
u8 Set_System_Beep(XGpioPs *Emio,u8 Status);

#endif /* EMIO_H_ */


/*
  ** (C) COPYRIGHT ChengDuHangke END OF FILE
*/
