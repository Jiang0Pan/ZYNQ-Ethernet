/*
  ** @file           : operation.h
  ** @brief          : Tcp Data Operation Header File
  **
  ** @attention
  **
  ** Copyright (c) 2020 ChengDuHangke.
  ** All rights reserved.
  **
  ** This software is licensed by ChengDuHangke under Ultimate Liberty license
  **
*/


#ifndef OPERATION_H_
#define OPERATION_H_


/*
  ** Function Prototype
*/
u8 Set_Dps_Cfg_Flag(void);
u8 Get_Dps_Cfg_Flag(void);
u8 Clear_Dps_Cfg_Flag(void);
u8 Set_FPGA_Cfg1_Flag(void);
u8 Get_FPGA_Cfg1_Flag(void);
u8 Clear_FPGA_Cfg1_Flag(void);
u8 Set_FPGA_Cfg2_Flag(void);
u8 Get_FPGA_Cfg2_Flag(void);
u8 Clear_FPGA_Cfg2_Flag(void);
u8 Data_Operation(void * Data);


#endif /* OPERATION_H_ */


/*
  ** (C) COPYRIGHT ChengDuHangke END OF FILE
*/
