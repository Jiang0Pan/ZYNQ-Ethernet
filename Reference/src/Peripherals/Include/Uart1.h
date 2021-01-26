#ifndef _UART1_H_
#define _UART1_H_

#include "xscugic.h"
#include "xuartps.h"
#include "xuartps_hw.h"
#include "interrupt.h"



#define UART1_ID 		(XPAR_PS7_UART_1_DEVICE_ID)		//����ID
#define Rx_MAX_LEN 		(128)							//�����ճ���

extern u8 tag;											//������
extern u32 count;										//��ǰ���ճ���
extern u8 Rx_buf[Rx_MAX_LEN];							//���ջ�����



//////////////////////////////////////////////////////////////////////////////

//��ʼ��
s32 Uartps_Init(void);									//���ڳ�ʼ��

#endif



