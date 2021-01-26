



#ifndef _SYSTEMINFO_H
#define _SYSTEMINFO_H


#include "GlobalRef.h"
#include "fpga.h"
#include "Hw_ver.h"
#include "eeprom.h"
#include "Cpld.h"
#include "Dps.h"
#include "Max528.h"
#include "Max9972.h"


#define     ZYNQ_VERSION	"1.0"


#define 	PL_VERSION 	 	(*((volatile u32 *)(AXI_BASE_ADDR + 0x000)))
#define		PL_SYSDEBUG		(*((volatile u32 *)(AXI_BASE_ADDR + 0x004)))
#define		PL_DATE    	 	(*((volatile u32 *)(AXI_BASE_ADDR + 0x008)))
#define		PL_TIME    	 	(*((volatile u32 *)(AXI_BASE_ADDR + 0x00C)))
#define		PL_REST    	 	(*((volatile u32 *)(AXI_BASE_ADDR + 0x010)))
#define		PL_TEMP    	 	(*((volatile u32 *)(AXI_BASE_ADDR + 0x014)))
#define		PL_DAN1   	 	(*((volatile u32 *)(AXI_BASE_ADDR + 0x018)))
#define		PL_DAN2 	 	(*((volatile u32 *)(AXI_BASE_ADDR + 0x01C)))



//��ȡһ�����������Ϣ
void ReadDBinfo(struct _REG_ * Cfg, struct _MSG_ *Msg);

//��ȡ��Դ��Ϣ
void ReadDpsinfo(void);

//��ȡ������Ϣ
void ReadBKinfo(void);

//��ȡ������Ϣ
void ReadMBinfo(void);

//�忨Ӳ����ʼ��
void BoardHW_Init(void);

//��ȡϵͳӲ����Ϣ
void ReadSysteminfo(void);



#endif

