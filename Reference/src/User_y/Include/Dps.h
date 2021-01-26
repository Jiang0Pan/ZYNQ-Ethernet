

#ifndef _DPS_H
#define _DPS_H


#include "SMBus.h"
#include "GlobalRef.h"


#define BYTE_SIZE				(1)
#define L11_SIZE				(2)
#define L16U_SIZE				(2)
#define L16S_SIZE				(2)
#define MAXFAIL_VIN				(13.0)
#define MINFAIL_VIN				(7.0)

#define MAXWARN_VIN				(7.0)
#define MINWARN_VIN				(7.0)

#define AD5694_VREF				(5.0)


#define DPS_B0IIC				(IIC09)
#define DPS_B1IIC				(IIC10)

#define LINE_MODE				(0x1)
#define LADDER_MODE				(0x2)


typedef enum {
	OPERATION 					= 0x01,
	ON_OFF_CONFIG 				= 0x02,
	CLEAR_FAULTS  				= 0x03,
	STORE_USER_ALL				= 0x15,
	RESTORE_USER_ALL			= 0x16,
	VOUT_MODE					= 0x20,
	VOUT_COMMAND				= 0x21,
	VOUT_CAL_OFFSET				= 0x23,
	VOUT_MAX					= 0x24,
	VOUT_MARGIN_HIGH			= 0x25,
	VOUT_MARGIN_LOW				= 0x26,
	VOUT_TRANSITION_RATE		= 0x27,
	VOUT_DROOP					= 0x28,
	FREQUENCY_SWITCH			= 0x33,
	INTERLEAVE					= 0x37,
	IOUT_CAL_GAIN				= 0x38,
	IOUT_CAL_OFFSET				= 0x39,
	VOUT_OV_FAULT_LIMIT			= 0x40,
	VOUT_OV_FAULT_RESPONSE		= 0x41,
	VOUT_OV_WARN_LIMIT			= 0x42,
	VOUT_UV_WARN_LIMIT			= 0x43,
	VOUT_UV_FAULT_LIMIT			= 0x44,
	VOUT_UV_FAULT_RESPONSE		= 0x45,
	IOUT_OC_FAULT_LIMIT			= 0x46,
	IOUT_UC_FAULT_LIMIT			= 0x4B,
	OT_FAULT_LIMIT				= 0x4F,
	OT_FAULT_RESPONSE			= 0x50,
	OT_WARN_LIMIT				= 0x51,
	UT_WARN_LIMIT				= 0x52,
	UT_FAULT_LIMIT				= 0x53,
	UT_FAULT_RESPONSE			= 0x54,
	VIN_OV_FAULT_LIMIT			= 0x55,
	VIN_OV_FAULT_RESPONSE		= 0x56,
	VIN_OV_WARN_LIMIT			= 0x57,
	VIN_UV_WARN_LIMIT			= 0x58,
	VIN_UV_FAULT_LIMIT			= 0x59,
	VIN_UV_FAULT_RESPONSE		= 0x5A,
	POWER_GOOD_ON				= 0x5E,
	TON_DELAY					= 0x60,
	TON_RISE					= 0x61,
	TOFF_DELAY					= 0x64,
	TOFF_FALL					= 0x65,
	STATUS_BYTE					= 0x78,
	STATUS_WORD					= 0x79,
	STATUS_VOUT					= 0x7A,
	STATUS_IOUT					= 0x7B,
	STATUS_INPUT				= 0x7C,
	STATUS_TEMPERATURE			= 0x7D,
	STATUS_CML					= 0x7E,
	STATUS_MFR_SPECIFIC			= 0x80,
	READ_VIN					= 0x88,
	READ_VOUT					= 0x8B,
	READ_IOUT					= 0x8C,
	READ_INTERNAL_TEMP			= 0x8D,
	READ_DUTY_CYCLE				= 0x94,
	READ_FREQUENCY				= 0x95,
	READ_IOUT_0					= 0x96,
	READ_IOUT_1					= 0x97,
	MFR_ID						= 0x99,
	MFR_MODEL					= 0x9A,
	MFR_REVISION				= 0x9B,
	MFR_LOCATION				= 0x9C,
	MFR_DATE					= 0x9D,
	MFR_SERIAL					= 0x9E,
	LEGACY_FAULT_GROUP			= 0xA8,
	USER_DATA_00				= 0xB0,
	ISENSE_CONFIG				= 0xD0,
	USER_CONFIG					= 0xD1,
	DDC_CONFIG					= 0xD3,
	POWER_GOOD_DELAY			= 0xD4,
	ASCR_CONFIG					= 0xDF,
	SEQUENCE					= 0xE0,
	DDC_GROUP					= 0xE2,
	DEVICE_ID					= 0xE4,
	MFR_IOUT_OC_FAULT_RESPONSE	= 0xE5,
	MFR_IOUT_UC_FAULT_RESPONSE	= 0xE6,
	SYNC_CONFIG					= 0xE9,
	SNAPSHOT					= 0xEA,
	BLANK_PARAMS				= 0xEB,
	SNAPSHOT_CONTROL			= 0xF3,
	RESTORE_FACTORY				= 0xF4,
	MFR_VMON_OV_FAULT_LIMIT		= 0xF5,
	MFR_VMON_UV_FAULT_LIMIT		= 0xF6,
	MFR_READ_VMON				= 0xF7,
	VMON_OV_FAULT_RESPONSE		= 0xF8,
	VMON_UV_FAULT_RESPONSE		= 0xF9,
}Dps_Cmd;


typedef union {
	struct {
		//error
		u16 bit00:  	1;	//通信异常
		u16 bit01:  	1;	//过压
		u16 bit02:  	1;	//欠压
		u16 bit03:  	1;	//过流
		u16 bit04:  	1;	//超温
		u16 bit05:  	1;	//输入超压
		u16 bit06:  	1;	//输入欠压
		u16 bit07:  	1;	//电源开关状态
		//warning
		u16 bit08:  	1;
		u16 bit09:  	1;
		u16 bit10:  	1;
		u16 bit11:  	1;
		u16 bit12:  	1;
		u16 bit13:  	1;
		u16 bit14:  	1;
		u16 bit15:  	1;
	};
	u16 uData;
}DpsSta;

/////////////////////////////////////////////////////////////

//报警温度℃
#define WARNING_TEMP	(60.0)
//故障温度℃
#define FAULT_TEMP		(70.0)
//开始上电延时时间
#define ON_Time			(10.0)	//ms
//上升时间
#define RISE_Time		(10.0)	//ms
//开始下电延时时间
#define OFF_Time		(10.0)	//ms
//下降时间
#define DOWN_Time		(10.0)	//ms
//电流校准值(欧姆)
#define IOUT_GAIN		(0.86)	//Ω
//电流校准偏移(安培)
#define IOUT_OFFSET		(0.0)	//A

 s32 DpsX_MaxFAIL_VIN(struct _DpsArg_ *Dpsx, u8 DpsAddr, IIC_Chan Chan);

 s32 DpsX_MinFAIL_VIN(struct _DpsArg_ *Dpsx, u8 DpsAddr, IIC_Chan Chan);

 s32 DpsX_MaxWARN_VIN(struct _DpsArg_ *Dpsx, u8 DpsAddr, IIC_Chan Chan);

 s32 DpsX_MinWARN_VIN(struct _DpsArg_ *Dpsx, u8 DpsAddr, IIC_Chan Chan);

    s32 DpsX_Max_VOUT(struct _DpsArg_ *Dpsx, u8 DpsAddr, IIC_Chan Chan);

    s32 DpsX_Min_VOUT(struct _DpsArg_ *Dpsx, u8 DpsAddr, IIC_Chan Chan);

s32 DpsX_MaxMARG_VOUT(struct _DpsArg_ *Dpsx, u8 DpsAddr, IIC_Chan Chan);

s32 DpsX_MinMARG_VOUT(struct _DpsArg_ *Dpsx, u8 DpsAddr, IIC_Chan Chan);

    s32 DpsX_Max_IOUT(struct _DpsArg_ *Dpsx, u8 DpsAddr, IIC_Chan Chan);

          s32 DpsX_PG(struct _DpsArg_ *Dpsx, u8 DpsAddr, IIC_Chan Chan);

        s32 DpsX_VOUT(struct _DpsArg_ *Dpsx, u8 DpsAddr, IIC_Chan Chan);

s32 DpsX_Warning_TEMP(struct _DpsArg_ *Dpsx, u8 DpsAddr, IIC_Chan Chan);

  s32 DpsX_Fault_TEMP(struct _DpsArg_ *Dpsx, u8 DpsAddr, IIC_Chan Chan);

    s32 DpsX_On_Delay(struct _DpsArg_ *Dpsx, u8 DpsAddr, IIC_Chan Chan);

   s32 DpsX_Off_Delay(struct _DpsArg_ *Dpsx, u8 DpsAddr, IIC_Chan Chan);

   s32 DpsX_Rise_Time(struct _DpsArg_ *Dpsx, u8 DpsAddr, IIC_Chan Chan);

   s32 DpsX_Drop_Time(struct _DpsArg_ *Dpsx, u8 DpsAddr, IIC_Chan Chan);

   s32 DpsX_IOUT_GAIN(struct _DpsArg_ *Dpsx, u8 DpsAddr, IIC_Chan Chan);

 s32 DpsX_IOUT_OFFSET(struct _DpsArg_ *Dpsx, u8 DpsAddr, IIC_Chan Chan);

		float Dps_VIN(struct _DpsArg_ *Dpsx, u8 DpsAddr, IIC_Chan Chan); //读取电源输入电压(V)

	   float Dps_VOUT(struct _DpsArg_ *Dpsx, u8 DpsAddr, IIC_Chan Chan);//读取电源输出电压(V)

	   float Dps_IOUT(struct _DpsArg_ *Dpsx, u8 DpsAddr, IIC_Chan Chan);//读取电源输出电流(A)

	   float Dps_TEMP(struct _DpsArg_ *Dpsx, u8 DpsAddr, IIC_Chan Chan);//读取电源芯片温度(℃)

 //写Dps寄存器
 s32 Dps_WCode(struct _DpsArg_ *Dpsx, u8 Code, u8 Data, u8 DpsAddr, IIC_Chan Chan);

//读取电源芯片状态, 返回电源状态(低16警告,高16故障)
u16 Dps_Status(struct _DpsArg_ *Dpsx, u8 DpsAddr, IIC_Chan Chan);

  s32 Dps_Init(struct _DpsArg_ *Dpsx, u16 id, u8 ProtectEn, u8 DpsAddr, IIC_Chan Chan);

void Build_Dps_Info(u16 DpsVI[], u16 DpsVO[], u16 DpsIO[], u16 DpsTemp[], u16 DpsStat[]);

s32 Set_AD5694(float Vo, u8 n_dac, u8 SlaveAddr, IIC_Chan Chan);

s32 DpsX_UpdateV(float Value, u8 DpsAddr, IIC_Chan Chan);

//驱动板信号电源
#define DrivDps_Vout(Vo, n_dac, SlaveAddr, Chan) (Set_AD5694(Vo, n_dac, SlaveAddr, Chan))

#endif


