


#ifndef _DRIVER_H
#define _DRIVER_H





#include "Dps.h"
#include "Timer.h"


void Time_Synchronous(void * recv, u16 Size);

//���ò�������
void Set_Sample(struct _SAMP_  * samp);

//0XA157 ��ȡ��������          �忨����    ���״̬      �ϻ�״̬
void Set_Sampl_packge(Sample_Data *Sample);

//�û���Դ�������
s32 UserDps_Switch(u16 bid, u16 ID, SW ON_OFF);

//�������Դ�������
s32 DrivDps_Switch(u16 bid, u16 ID, SW ON_OFF);

//��DPS��Դ����
void OpenDpsIn(void);

//���ò��򿪵�Դ
s32 DpsConfig(Sample_Data *Sample);

//Dps�����ϵ�
u32 DpsLineOpen (struct _DpsArg_ *Dpsx, u16 id, u8 ProtectEn, u8 DpsAddr, IIC_Chan Chan);

//Dps�����µ�
u32 DpsLineClose(struct _DpsArg_ *Dpsx, u16 id, u8 ProtectEn, u8 DpsAddr, IIC_Chan Chan);

//���ϵ�ʱ��
void OpenDpsSequence(Sample_Data *Sample);

//�ر��ϵ�ʱ��
void CloseDpsSequence(Sample_Data *Sample);

//�������������
void db_Conf(Sample_Data *Sample);

//pin�Ų�������
void pin_Conf(Sample_Data *Sample);

//���԰忨ddr
void TEST_DDR(void);

//�ر��û���Դ
void CloseDps(void);








#endif







