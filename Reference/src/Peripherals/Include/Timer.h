#ifndef _TIMER_H_
#define _TIMER_H_

#include "interrupt.h"
#include "xscutimer.h"
#include "gpio.h"
#include "Driver.h"


//��ʱʱ�� = 1/��ʱ��Ƶ��*��Ԥ����ֵ+1��
//us��ʱ��LOAD value
#define  Load_us(US)		(333*(US)-1)

//ms��ʱ��LOAD value
#define  Load_ms(MS)		(333000*(MS)-1)

//1S��ʱ��LOAD value
#define  Load_s(S)    	    (333000000*(S)-1) 					//1S


extern u8 OpenFLAG;
extern u8 CloseFLAG;
extern u32 DpsCount[2][DPS_NUM/2];
extern u16 SetValue[2][DPS_NUM/2];

////////////////////////////////////////////////////////////////////


s32 Timer_Init(u32 Load_Value);

void Timer_Start(void);

void Timer_Stop(void);

void Sys_Run(void);




#endif
