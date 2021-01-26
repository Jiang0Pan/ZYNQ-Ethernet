#ifndef _UART1_H_
#define _UART1_H_

#include "xscugic.h"
#include "xuartps.h"
#include "xuartps_hw.h"
#include "interrupt.h"



#define UART1_ID 		(XPAR_PS7_UART_1_DEVICE_ID)		//串口ID
#define Rx_MAX_LEN 		(128)							//最大接收长度

extern u8 tag;											//处理标记
extern u32 count;										//当前接收长度
extern u8 Rx_buf[Rx_MAX_LEN];							//接收缓存区



//////////////////////////////////////////////////////////////////////////////

//初始化
s32 Uartps_Init(void);									//串口初始化

#endif



