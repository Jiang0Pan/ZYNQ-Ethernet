


#ifndef _DRIVER_H
#define _DRIVER_H





#include "Dps.h"
#include "Timer.h"


void Time_Synchronous(void * recv, u16 Size);

//设置采样数据
void Set_Sample(struct _SAMP_  * samp);

//0XA157 读取采样数据          板卡编码    插板状态      老化状态
void Set_Sampl_packge(Sample_Data *Sample);

//用户电源输出控制
s32 UserDps_Switch(u16 bid, u16 ID, SW ON_OFF);

//驱动板电源输出控制
s32 DrivDps_Switch(u16 bid, u16 ID, SW ON_OFF);

//打开DPS电源输入
void OpenDpsIn(void);

//配置并打开电源
s32 DpsConfig(Sample_Data *Sample);

//Dps线性上电
u32 DpsLineOpen (struct _DpsArg_ *Dpsx, u16 id, u8 ProtectEn, u8 DpsAddr, IIC_Chan Chan);

//Dps线性下电
u32 DpsLineClose(struct _DpsArg_ *Dpsx, u16 id, u8 ProtectEn, u8 DpsAddr, IIC_Chan Chan);

//打开上电时序
void OpenDpsSequence(Sample_Data *Sample);

//关闭上电时序
void CloseDpsSequence(Sample_Data *Sample);

//驱动板参数配置
void db_Conf(Sample_Data *Sample);

//pin脚参数配置
void pin_Conf(Sample_Data *Sample);

//测试板卡ddr
void TEST_DDR(void);

//关闭用户电源
void CloseDps(void);








#endif







