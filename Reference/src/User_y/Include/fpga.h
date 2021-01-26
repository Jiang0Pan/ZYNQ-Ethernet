



#ifndef _FPGA_H
#define _FPGA_H



#include "GlobalRef.h"
#include "xil_printf.h"
#include "fpga_reg.h"

#define Driver_INT_ID              	(61)
#define RISING_EDGE_TYPE    		(0x03)	//������
#define HIGHLEVEL_TYPE      		(0x01)	//�ߵ�ƽ
#define INT_TYPE_MASK          		(0x03)	//�ж�����

//�仯λ��
typedef enum {
	LE = 0x0,
	TE = 0x1,
}VaryPos;


extern volatile u32 HP_STATUS;
/////////////////////////////////////////////////////////////////

s32 AXIHP_Init(void);

s32 Fpga_WOpt(struct _REG_ * Cfg, u32 Addr, u32  Data);
s32 Fpga_ROpt(struct _REG_ * Cfg, u32 Addr, u32 *Rdata);

//��DDR����
s32 DDR_ROpt (struct _REG_ * Cfg, u32 Addr, u32 *Rdata);

//дDDR����
s32 DDR_WOpt (struct _REG_ * Cfg, u32 Addr, u32 Data);

//����ִ������
s32 DDR_Period(struct _REG_ * Cfg, u32 Period);

//DDR����
s32 Debug_DDR(struct _REG_ * Cfg);

//дddr����(������ŵ�ַ)
s32 DDR_WOpt_Arg(struct _REG_ * Cfg, u32 Waddr, u32 Wlen);

//��ddr����(fpga��������RAM׼����)
s32 DDR_ROpt_Arg(struct _REG_ * Cfg, u32 Waddr, u32 Wlen);

//��У���
s32 DDR_ROpt_Check(struct _REG_ * Cfg, u32 *Rdata);

//��У���
s32 DDR_Clear_Check(struct _REG_ * Cfg);

//����ִ�б�־
s32 DDR_ROpt_Vecflag(struct _REG_ * Cfg, u32 *Rdata);

//��ȡ����ִ������
s32 DDR_ROpt_Counter(struct _REG_ * Cfg, u32 *Rdata);

//IO���ԼĴ���
s32 Debug_IO(struct _REG_ * Cfg);

//IO�仯λ��
s32 IO_Var_WOpt(struct _REG_ * Cfg, u16 IO, VaryPos pos, u32 value);

//IO�Ƚ�λ��
s32 IO_Cmp_WOpt(struct _REG_ * Cfg, u16 IO, VaryPos pos, u32 value);

//��������
s32 MV_Vector(Vector_Arg *Vec, u32 Size);

//��ȡ���лؼ���
s32 Read_Back_isp(void);

//��ȡ���а忨����ִ�б�־
u32 Read_Vecflag(Sample_Data  *Sample);

#endif

