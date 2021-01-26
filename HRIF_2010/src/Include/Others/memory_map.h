/*
  ** @file           : memory_map.h
  ** @brief          : Memory Mapping Header File
  **
  ** @attention
  **
  ** Copyright (c) 2020 ChengDuHangke.
  ** All rights reserved.
  **
  ** This software is licensed by ChengDuHangke under Ultimate Liberty license
  **
*/


#ifndef SRC_INCLUDE_OTHERS_MEMORY_MAP_H_
#define SRC_INCLUDE_OTHERS_MEMORY_MAP_H_


/*
  ** Include
*/


/*
  ** Define
*/

/* Application Address */
#define     APP_ADDR            (0x100000)
/* Application Size */
#define		APP_SIZE            (0x2FF00000)

/* Ethernet Data Address */
#define     ETH_DATA_ADDR       (0x30000000)
/* Ethernet Data Size */
#define     ETH_DATA_SIZE       (0x200000)

/* DPS Config Data Address */
#define     DPS_CFG_DATA_ADDR   (ETH_DATA_ADDR + ETH_DATA_SIZE)
/* DPS Config Data Size */
#define     DPS_CFG_SIZE        (0x100000)

/* FPGA Config1 Data Address */
#define     FPGA_CFG1_DATA_ADDR (DPS_CFG_DATA_ADDR + DPS_CFG_SIZE)
/* FPGA Config1 Data Size */
#define     FPGA_CFG1_SIZE      (0x100000)
/* FPGA Config2 Data Address */
#define     FPGA_CFG2_DATA_ADDR (FPGA_CFG1_DATA_ADDR + FPGA_CFG1_SIZE)
/* FPGA Config2 Data Size */
#define     FPGA_CFG2_SIZE      (0x100000)

/* Board Information Address */
#define     BOARD_INFO_ADDR     (FPGA_CFG2_DATA_ADDR + FPGA_CFG2_SIZE)
/* Board Information Size */
#define     BOARD_INFO_SIZE     (0x100000)
/* Management Board Information Address */
#define     MB_INFO_ADDR  		(BOARD_INFO_ADDR)
/* Management Board Information Size */
#define     MB_INFO_SIZE        (0x10000)
/* Driver0 (Unidirectional) Board Information Address */
#define     DB0_INFO_ADDR 		(MB_INFO_ADDR + MB_INFO_SIZE)
/* Driver0 (Unidirectional) Board Information Size */
#define     DB0_INFO_SIZE       (0x10000)
/* Driver1 (Unidirectional) Board Information Address */
#define     DB1_INFO_ADDR 		(DB0_INFO_ADDR + DB0_INFO_SIZE)
/* Driver1 (Unidirectional) Board Information Size */
#define     DB1_INFO_SIZE       (0x10000)
/* Driver2 (Unidirectional) Board Information Address */
#define     DB2_INFO_ADDR 		(DB1_INFO_ADDR + DB1_INFO_SIZE)
/* Driver2 (Unidirectional) Board Information Size */
#define     DB2_INFO_SIZE       (0x10000)
/* Driver3 (Double-Sided) Board Information Address */
#define     DB3_INFO_ADDR 		(DB2_INFO_ADDR + DB2_INFO_SIZE)
/* Driver3 (Double-Sided) Board Information Size */
#define     DB3_INFO_SIZE       (0x10000)
/* Driver4 (Double-Sided) Board Information Address */
#define     DB4_INFO_ADDR 		(DB3_INFO_ADDR + DB3_INFO_SIZE)
/* Driver4 (Double-Sided) Board Information Size */
#define     DB4_INFO_SIZE      	(0x10000)
/* DPS0 Board Information Address */
#define     DPSB0_INFO_ADDR     (DB4_INFO_ADDR + DB4_INFO_SIZE)
/* DPS0 Board Information Size */
#define     DPSB0_INFO_SIZE     (0x10000)
/* DPS1 Board Information Address */
#define     DPSB1_INFO_ADDR     (DPSB0_INFO_ADDR + DPSB0_INFO_SIZE)
/* DPS1 Board Information Size */
#define     DPSB1_INFO_SIZE     (0x10000)

/* Aging Control Data Address */
#define     AGING_CTL_ADDR       (BOARD_INFO_ADDR + BOARD_INFO_SIZE)
/*Aging Control Data Size */
#define     AGING_CTL_SIZE       (0x400)
/* Pin Mask Information Address */
#define     PIN_MASK_INFO        (AGING_CTL_ADDR + AGING_CTL_SIZE)
/* Pin Mask Information Size */
#define     PIN_MASK_SIZE        (0x400)

/* Sample Data Address */
#define     SAMPLE_DATA_ADD      (0x31000000)
/* Sample Data Size */
#define     SAMPLE_DATA_SIZE     (0x100000)
/* Pattern Error Information Address */
#define     PAT_ERR_INFO_ADDR    (SAMPLE_DATA_ADD + SAMPLE_DATA_SIZE)
/* Pattern Error Information Size */
#define     PAT_ERR_INFO_SIZE    (0x100000)
/* Pattern Compare Information Address */
#define     PAT_C_INFO_ADDR      (PAT_ERR_INFO_ADDR + PAT_ERR_INFO_SIZE)
/* Pattern Compare Information Size */
#define     PAT_C_INFO_SIZE      (0x100000)
/* Pattern Running State Address */
#define     PAT_R_STS_ADDR       (PAT_C_INFO_ADDR + PAT_C_INFO_SIZE)
/* Pattern Running State Size */
#define     PAT_R_STS_SIZE       (0x100000)

/* Firmware Information Address */
/* Management Board Firmware Information Address */
#define     MB_FRW_INFO_ADDR     (0x32000000)
/* Management Board Firmware Information Size */
#define     MB_FRW_INFO_SIZE     (0x800000)
/* Driver Board Type0(A7) Firmware Information Address */
#define     DB_FRW_TY0_INFO_AAR  (MB_FRW_INFO_ADDR + MB_FRW_INFO_SIZE)
/* Driver Board Type0(A7) Firmware Information Size */
#define     DB_FRW_TY0_INFO_SIZE (0x800000)
/* Driver Board Type1(K7) Firmware Information Address */
#define     DB_FRW_TY1_INFO_AAR  (DB_FRW_TY0_INFO_AAR + DB_FRW_TY0_INFO_SIZE)
/* Driver Board Type1(K7) Firmware Information Size */
#define     DB_FRW_TY1_INFO_SIZE (0x800000)
/* DPS Board (CPLD) Firmware Information Address */
#define     DB_FRW_TY2_INFO_AAR  (DB_FRW_TY1_INFO_AAR + DB_FRW_TY1_INFO_SIZE)
/* DPS Board (CPLD) Firmware Information Size */
#define     DB_FRW_TY2_INFO_SIZE (0x800000)


#endif /* SRC_INCLUDE_OTHERS_MEMORY_MAP_H_ */


/*
  ** (C) COPYRIGHT ChengDuHangke END OF FILE
*/
