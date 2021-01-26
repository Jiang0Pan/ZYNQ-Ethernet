/*
  ** @file           : axi_lite.h
  ** @brief          : Axi Lite Header File
  **
  ** @attention
  **
  ** Copyright (c) 2020 ChengDuHangke.
  ** All rights reserved.
  **
  ** This software is licensed by ChengDuHangke under Ultimate Liberty license
  **
*/


#ifndef AXI_LITE_H_
#define AXI_LITE_H_


/*
  ** Include
*/
#include "xil_types.h"


/*
  ** Define
*/

/* AXI_Lite  Base Address */
#define     PL_AXI_BASE_ADDR    (0x43C00000)
/* Basic Information Register */
/* PL Test Register Address . RW */
#define     PL_TEST_REG	        (PL_AXI_BASE_ADDR + 0x0)
/* PL Version Information Register Address . RO */
#define     PL_VERSION_REG      (PL_AXI_BASE_ADDR + 0x4)
/* PL Date Information Register Address . RO */
#define     PL_DATE_REG         (PL_AXI_BASE_ADDR + 0x8)
/* PL Time Information Register Address . RO  */
#define     PL_TIME_REG         (PL_AXI_BASE_ADDR + 0xC)
/* PL Timer State Information Register Address . RW */
#define     PL_TIMERSTE_REG     (PL_AXI_BASE_ADDR + 0x10)
/* PL Timer Data Information Register Address . RO */
#define     PL_TIMERDAT_REG     (PL_AXI_BASE_ADDR + 0x14)
/* PL Temperature Register Address . RO */
#define     PL_TEMP_REG         (PL_AXI_BASE_ADDR + 0x18)
/* PL DNA (High Bits) Address . RO */
#define     PL_DNA_HIGH_REG     (PL_AXI_BASE_ADDR + 0x1C)
/* PL DNA (Low Bits) Address . RO */
#define     PL_DNA_LOW_REG      (PL_AXI_BASE_ADDR + 0x20)

/* Device 1 Base Address */
#define     DEV1_AXI_BASEADDR   (0x43C01000)
/* Device 1 Test Register Address . RW */
#define     DEVICE1_TEST_REG    (DEV1_AXI_BASEADDR + 0x0)

/* Device 2 Base Address */
#define     DEV2_AXI_BASEADDR   (0x43C02000)
/* Device 2 Test Register Address . RW */
#define     DEVICE2_TEST_REG    (DEV2_AXI_BASEADDR + 0x0)

/* Device 3 Base Address */
#define     DEV3_AXI_BASEADDR   (0x43C03000)
/* Device 3 Test Register Address . RW */
#define     DEVICE3_TEST_REG    (DEV3_AXI_BASEADDR + 0x0)

/* Device 4 Base Address */
#define     DEV4_AXI_BASEADDR   (0x43C04000)
/* Device 4 Test Register Address . RW */
#define     DEVICE4_TEST_REG    (DEV4_AXI_BASEADDR + 0x0)

/* Reserved Base Address */
#define     RESERD_AXI_BASEADDR (0x43C06000)
/* Reserved Test Register Address . RW */
#define     RESERD_TEST_REG     (RESERD_AXI_BASEADDR + 0x00)
/* Reserved DDR Start Register Address . RW */
#define     RESEED_DDRSAT_REG   (RESERD_AXI_BASEADDR + 0x04)
/* Reserved DDR Length Register Address . RW */
#define     RESEED_DDRLEG_REG   (RESERD_AXI_BASEADDR + 0x08)
/* Reserved Trigger Register Address . WC */
#define     RESEED_TRIGGER_REG  (RESERD_AXI_BASEADDR + 0x0C)
/* Reserved CS Register Address . WO */
#define     RESEED_CS_REG       (RESERD_AXI_BASEADDR + 0x10)
/* Reserved Done Register Address . RC */
#define     RESEED_DONE_REG     (RESERD_AXI_BASEADDR + 0x14)
/* Reserved Clear Sum Register Address . WC */
#define     RESEED_CLRSUM_REG   (RESERD_AXI_BASEADDR + 0x18)
/* Reserved Get Register Address . WO */
#define     RESEED_GETSUM_REG   (RESERD_AXI_BASEADDR + 0x1C)
/* Reserved Sum Flag Register Address . WO */
#define     RESEED_FLAG_REG     (RESERD_AXI_BASEADDR + 0x20)


/*
  ** Function Prototype
*/
u8 Axi_Lite_Read_Register(u32 Addr, u32 Length ,u32 * Regdata);
u8 Axi_Lite_Write_Register(u32 Addr, u32 Length ,u32 Regdata);


#endif /* AXI_LITE_H_ */


/*
  ** (C) COPYRIGHT ChengDuHangke END OF FILE
*/
