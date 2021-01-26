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
//#ifndef 	ON
//#define     ON 			        (1)
//#endif
//#ifndef 	OFF
//#define     OFF                 (0)
//#endif

#define     EMIO_MIN_ID         (0)
#define     EMIO_MAX_ID         (117)

#define 	SYSTEM_CPU0_LED		(54)
#define 	SYSTEM_CPU1_LED     (55)
#define 	SYSTEM_LWIP_LED     (56)

#define 	SYSTEM_BEEP         (57)

#define 	SYSTEM_SW0          (58)
#define 	SYSTEM_SW1          (59)
#define 	SYSTEM_SW2          (60)
#define 	SYSTEM_SW3          (61)

#define 	SYSTEM_IP0          (62)
#define 	SYSTEM_IP1          (63)
#define 	SYSTEM_IP2          (64)
#define 	SYSTEM_IP3          (65)
#define 	SYSTEM_IP4          (66)
#define 	SYSTEM_IP5          (67)
#define 	SYSTEM_IP6          (68)
#define 	SYSTEM_IP7          (69)

#define 	B0_BRD_IRQ          (70)
#define 	B1_BRD_IRQ          (71)
#define 	U0_BRD_IRQ          (72)
#define 	U1_BRD_IRQ          (73)
#define 	U2_BRD_IRQ          (74)
#define 	BURN_IRQ            (75)
#define 	DA_IRQ          	(76)
#define 	DPS0_IRQ          	(77)
#define 	DPS1_IRQ          	(78)
#define 	DA_TRIG          	(79)
#define 	IIC_REST          	(80)
#define 	SYS_TRIG          	(81)

#define     INPUT_PIN           (0)
#define     OUTPUT_PIN          (1)

#define     ENABLE_OUTPUT       (1)
#define     DISABLE_OUTPUT      (0)

#define     HIGH_LEVEL          (1)
#define     LOW_LEVEL           (0)

XGpioPs 	Emio;

/*
  ** Function Prototype
*/
u8 Emio_Config(u16 DeviceId,XGpioPs *Emio);
u8 Get_Ipaddr(XGpioPs *Emio);
u8 Set_System_Lwip_Led(XGpioPs *Emio,u8 Status);
u8 Set_System_Cpu0_Led(XGpioPs *Emio,u8 Status);
u8 Set_System_Beep(XGpioPs *Emio,u8 Status);
XGpioPs * Get_Emio_Point(void);

#endif /* EMIO_H_ */


/*
  ** (C) COPYRIGHT ChengDuHangke END OF FILE
*/
