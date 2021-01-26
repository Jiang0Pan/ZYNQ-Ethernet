



#ifndef _FPGA_H
#define _FPGA_H



#include "GlobalRef.h"
#include "xil_printf.h"
#include "fpga_reg.h"

#define Driver_INT_ID              	(61)
#define RISING_EDGE_TYPE    		(0x03)	//上升沿
#define HIGHLEVEL_TYPE      		(0x01)	//高电平
#define INT_TYPE_MASK          		(0x03)	//中断掩码

//变化位置
typedef enum {
	LE = 0x0,
	TE = 0x1,
}VaryPos;


extern volatile u32 HP_STATUS;
/////////////////////////////////////////////////////////////////

s32 AXIHP_Init(void);

s32 Fpga_WOpt(struct _REG_ * Cfg, u32 Addr, u32  Data);
s32 Fpga_ROpt(struct _REG_ * Cfg, u32 Addr, u32 *Rdata);

//读DDR数据
s32 DDR_ROpt (struct _REG_ * Cfg, u32 Addr, u32 *Rdata);

//写DDR数据
s32 DDR_WOpt (struct _REG_ * Cfg, u32 Addr, u32 Data);

//配置执行周期
s32 DDR_Period(struct _REG_ * Cfg, u32 Period);

//DDR测试
s32 Debug_DDR(struct _REG_ * Cfg);

//写ddr参数(向量存放地址)
s32 DDR_WOpt_Arg(struct _REG_ * Cfg, u32 Waddr, u32 Wlen);

//读ddr参数(fpga读向量到RAM准备好)
s32 DDR_ROpt_Arg(struct _REG_ * Cfg, u32 Waddr, u32 Wlen);

//读校验和
s32 DDR_ROpt_Check(struct _REG_ * Cfg, u32 *Rdata);

//清校验和
s32 DDR_Clear_Check(struct _REG_ * Cfg);

//向量执行标志
s32 DDR_ROpt_Vecflag(struct _REG_ * Cfg, u32 *Rdata);

//读取向量执行数量
s32 DDR_ROpt_Counter(struct _REG_ * Cfg, u32 *Rdata);

//IO调试寄存器
s32 Debug_IO(struct _REG_ * Cfg);

//IO变化位置
s32 IO_Var_WOpt(struct _REG_ * Cfg, u16 IO, VaryPos pos, u32 value);

//IO比较位置
s32 IO_Cmp_WOpt(struct _REG_ * Cfg, u16 IO, VaryPos pos, u32 value);

//搬移向量
s32 MV_Vector(Vector_Arg *Vec, u32 Size);

//读取所有回检结果
s32 Read_Back_isp(void);

//读取所有板卡向量执行标志
u32 Read_Vecflag(Sample_Data  *Sample);

#endif

