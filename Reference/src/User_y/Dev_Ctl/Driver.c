

#include "Driver.h"
#include "SystemInfo.h"


//同步时钟
void Time_Synchronous(void * recv, u16 Size)
{
	u8 *ptr = (u8 *)recv;
	memcpy(SysTime.Data, ptr, 8);
}

//设置采样数据
void Set_Sample(struct _SAMP_  * samp)
{

}

//0XA157 读取采样数据          板卡编码    插板状态      老化状态
void Set_Sampl_packge(Sample_Data *Sample)
{
	Sample->AgeTime      = AGETIME;
	//Sample.BoardCode   = BoardCode;
	//Sample.BoardStatus = BoardStatus;
	Build_Dps_Info(Sample->DpsVI, Sample->DpsVO, Sample->DpsIO, Sample->DpsTemp, Sample->DpsStat);
}

//使能User电源(bid:0---1, ID:0 -- 7)
s32 UserDps_Switch(u16 bid, u16 ID, SW ON_OFF)
{
	Cpld_Xfer Xfer;

	memset(&Xfer, 0, sizeof(Xfer));

	if(ON_OFF)
		dps_info.DBMsg[bid].UseMask |= 0x1 << ID;
	else
		dps_info.DBMsg[bid].UseMask &= ~(0x1 << ID);

	Xfer.Data = (dps_info.DBMsg[bid].UseMask) & 0xffff;

	//打开一级SPI
	IO_Level_Set(&(bbd_info.Ctl_Output), Group0, pin0, bbd_info.IO_SlaveAddr, 0, bbd_info.TOChan);
	IO_Level_Set(&(bbd_info.Ctl_Output), Group0, pin1, bbd_info.IO_SlaveAddr, 0, bbd_info.TOChan);

	//切换SPI到控制
	IO_Level_Set(&(dps_info.DBMsg[bid].Output_LVL), Group1, pin2, dps_info.PCA953_SlaveAddr, 0, dps_info.DBMsg[bid].Chan);
	IO_Level_Set(&(dps_info.DBMsg[bid].Output_LVL), Group1, pin1, dps_info.PCA953_SlaveAddr, 1, dps_info.DBMsg[bid].Chan);

	Xfer.Addr = ENABLE_LV1;
	Cpld_Transfer(&Xfer, NULL);

	Xfer.Addr = ENABLE_LV3;
	Cpld_Transfer(&Xfer, NULL);

	Xfer.Addr = ENABLE_LV2;
	Cpld_Transfer(&Xfer, NULL);

	//关闭一级SPI
	IO_Level_Set(&(bbd_info.Ctl_Output), Group0, pin0, bbd_info.IO_SlaveAddr, 1, bbd_info.TOChan);
	IO_Level_Set(&(bbd_info.Ctl_Output), Group0, pin1, bbd_info.IO_SlaveAddr, 1, bbd_info.TOChan);

	//切换SPI到控制
	IO_Level_Set(&(dps_info.DBMsg[bid].Output_LVL), Group1, pin2, dps_info.PCA953_SlaveAddr, 1, dps_info.DBMsg[bid].Chan);
	IO_Level_Set(&(dps_info.DBMsg[bid].Output_LVL), Group1, pin1, dps_info.PCA953_SlaveAddr, 1, dps_info.DBMsg[bid].Chan);

	return SUCCESS;
}

//使能驱动板信号电源电源(ID:0 -- 3)
s32 DrivDps_Switch(u16 bid, u16 ID, SW ON_OFF)
{
	Cpld_Xfer Xfer;

	memset(&Xfer, 0, sizeof(Xfer));

	if(ON_OFF)
		dps_info.DBMsg[bid].UseMask |=   0x1 << (ID + 8);
	else
		dps_info.DBMsg[bid].UseMask &= ~(0x1 << (ID + 8));

	Xfer.Data = (dps_info.DBMsg[bid].UseMask) & 0xffff;
	Xfer.RW   = WOPT;

	//打开一级SPI
	IO_Level_Set(&(bbd_info.Ctl_Output), Group0, pin0, bbd_info.IO_SlaveAddr, 0, bbd_info.TOChan);
	IO_Level_Set(&(bbd_info.Ctl_Output), Group0, pin1, bbd_info.IO_SlaveAddr, 0, bbd_info.TOChan);

	//切换SPI到控制
	IO_Level_Set(&(dps_info.DBMsg[bid].Output_LVL), Group1, pin1, dps_info.PCA953_SlaveAddr, 1, dps_info.DBMsg[bid].Chan);
	IO_Level_Set(&(dps_info.DBMsg[bid].Output_LVL), Group1, pin2, dps_info.PCA953_SlaveAddr, 0, dps_info.DBMsg[bid].Chan);

	Xfer.Addr = ENABLE_LV1;
	Cpld_Transfer(&Xfer, NULL);

	Xfer.Addr = ENABLE_LV3;
	Cpld_Transfer(&Xfer, NULL);

	Xfer.Addr = ENABLE_LV2;
	Cpld_Transfer(&Xfer, NULL);

	//关闭二级SPI
	IO_Level_Set(&(bbd_info.Ctl_Output), Group0, pin0, bbd_info.IO_SlaveAddr, 1, bbd_info.TOChan);
	IO_Level_Set(&(bbd_info.Ctl_Output), Group0, pin1, bbd_info.IO_SlaveAddr, 1, bbd_info.TOChan);

	//复位SPI到默认状态
	IO_Level_Set(&(dps_info.DBMsg[bid].Output_LVL), Group1, pin2, dps_info.PCA953_SlaveAddr, 1, dps_info.DBMsg[bid].Chan);
	IO_Level_Set(&(dps_info.DBMsg[bid].Output_LVL), Group1, pin2, dps_info.PCA953_SlaveAddr, 1, dps_info.DBMsg[bid].Chan);


	return FAILURE;
}

//打开DPS电源输入
void OpenDpsIn(void)
{

}

//配置电源
s32 DpsConfig(Sample_Data *Sample)
{
	//初始化配置
	u16 i = 0, j = 0, id = 0x0;
	Dps_Arg * Dps_ptr = (Dps_Arg * )DPS_CFG_DATA_ADDR;

	for(i = 0; i < 2; i++)
	{
		for(j = 0; j < (DPS_NUM/2); j++)
		{
			id++;

			if(j < ((DPS_NUM/2) - 2))
				Sample->AgeStatus |= Dps_Init(&Dps_ptr->Dsp[id], id, 1, dps_info.DBMsg[i].DpsAddr[j], dps_info.DBMsg[i].Chan);
			else
				Sample->AgeStatus |= Dps_Init(&Dps_ptr->Dsp[id], id, 1,    dps_info.AD5694_SlaveAddr, dps_info.DBMsg[i].Chan);
			UserDps_Switch(i, j, ON);
		}
	}

	return SUCCESS;
}

//Dps线性上电
u32 DpsLineOpen(struct _DpsArg_ *Dpsx, u16 id, u8 ProtectEn, u8 DpsAddr, IIC_Chan Chan)
{
	u32 error = 0x0;

	if(DpsX_VOUT(Dpsx,  DpsAddr, Chan))
	{
		if(ProtectEn)		//保护使能
			goto ERROR;
	}

	if(DpsX_On_Delay(Dpsx,  DpsAddr, Chan))
	{
		if(ProtectEn)		//保护使能
			goto ERROR;
	}

	if(DpsX_Rise_Time(Dpsx,  DpsAddr, Chan))
	{
		if(ProtectEn)		//保护使能
			goto ERROR;
	}

	if(Dps_WCode(Dpsx,     OPERATION, 0x84, DpsAddr, Chan))
	{
		if(ProtectEn)		//保护使能
			goto ERROR;
	}

    if(Dps_WCode(Dpsx, ON_OFF_CONFIG, 0x1A, DpsAddr, Chan))
	{
    	if(ProtectEn)		//保护使能
    		goto ERROR;
	}

	return SUCCESS;

ERROR:
	error |= 0x1 << (id + 8);

	return error;
}

//Dps线性下电
u32 DpsLineClose(struct _DpsArg_ *Dpsx, u16 id, u8 ProtectEn, u8 DpsAddr, IIC_Chan Chan)
{
	u32 error = 0x0;

	if(DpsX_Off_Delay(Dpsx,  DpsAddr, Chan))
	{
		if(ProtectEn)		//保护使能
			goto ERROR;
	}

	if(DpsX_Drop_Time(Dpsx,  DpsAddr, Chan))
	{
		if(ProtectEn)		//保护使能
			goto ERROR;
	}

	if(Dps_WCode(Dpsx,     OPERATION, 0x04, DpsAddr, Chan))
	{
    	if(ProtectEn)		//保护使能
    		goto ERROR;
	}

    if(Dps_WCode(Dpsx, ON_OFF_CONFIG, 0x17, DpsAddr, Chan))
	{
    	if(ProtectEn)		//保护使能
    		goto ERROR;
	}

	return SUCCESS;

ERROR:
	error |= 0x1 << (id + 8);

	return error;
}

//设置开电时序
void OpenDpsSequence(Sample_Data *Sample)
{
	//初始化配置
	u16 i = 0, j = 0, id = 0x0;
	Dps_Arg * Dps_ptr = (Dps_Arg * )DPS_CFG_DATA_ADDR;

	memset(DpsCount, 0, sizeof(u32)*DPS_NUM);
	memset(SetValue, 0, sizeof(u16)*DPS_NUM);
	for(i = 0; i < 2; i++)	//线性上电
	{
		for(j = 0; j < (DPS_NUM/2); j++)
		{
			id++;
			if(LINE_MODE == Dps_ptr->Dsp[id].Open.Mode)
			{
				if(j < ((DPS_NUM/2) - 2))
					Sample->AgeStatus |= DpsLineOpen(&Dps_ptr->Dsp[id], id, 1, dps_info.DBMsg[i].DpsAddr[j], dps_info.DBMsg[i].Chan);
				else
					Sample->AgeStatus |= DpsLineOpen(&Dps_ptr->Dsp[id], id, 1,    dps_info.AD5694_SlaveAddr, dps_info.DBMsg[i].Chan);
			}
		}
	}
	OpenFLAG = 0x1;			//阶梯上电
}

//设置关电时序
void CloseDpsSequence(Sample_Data *Sample)
{
	//初始化配置
	u16 i = 0, j = 0, id = 0x0;
	Dps_Arg * Dps_ptr = (Dps_Arg * )DPS_CFG_DATA_ADDR;

	memset(DpsCount, 0, sizeof(u32)*DPS_NUM);
	memset(SetValue, 0, sizeof(u16)*DPS_NUM);
	for(i = 0; i < 2; i++)
	{
		for(j = 0; j < (DPS_NUM/2); j++)
		{
			id++;
			if(j < ((DPS_NUM/2) - 2))
				Sample->AgeStatus |= DpsLineClose(&Dps_ptr->Dsp[id], id, 1, dps_info.DBMsg[i].DpsAddr[j], dps_info.DBMsg[i].Chan);
			else
				Sample->AgeStatus |= DpsLineClose(&Dps_ptr->Dsp[id], id, 1,    dps_info.AD5694_SlaveAddr, dps_info.DBMsg[i].Chan);
		}
	}
	CloseFLAG = 0x1;
}

//设置64pinDHV
void Set_DHV64(float Vo1, float Vo2)
{
	DrivDps_Vout(Vo1, 2, dps_info.AD5694_SlaveAddr, dps_info.DBMsg[1].Chan);
	DrivDps_Switch(0, 0, ON);
	DrivDps_Vout(Vo2, 3, dps_info.AD5694_SlaveAddr, dps_info.DBMsg[1].Chan);
	DrivDps_Switch(0, 1, OFF);
}

void Set_DHV32(struct _REG_ * Cfg, float Vo1, float Vo2)
{
	Max528_Set_DAC(Cfg, Vo1, DAC0, 0);
	Max528_Set_DAC(Cfg, Vo2, DAC0, 1);
}

void Set_DLV32(struct _REG_ * Cfg, float Vo1, float Vo2)
{
	Max528_Set_DAC(Cfg, Vo1, DAC1, 0);
	Max528_Set_DAC(Cfg, Vo2, DAC1, 1);
}

void Set_CPHV32(struct _REG_ * Cfg, float Vo1, float Vo2)
{
	Max528_Set_DAC(Cfg, Vo1, DAC2, 0);
	Max528_Set_DAC(Cfg, Vo2, DAC2, 1);
}

void Set_CPLV32(struct _REG_ * Cfg, float Vo1, float Vo2)
{
	Max528_Set_DAC(Cfg, Vo1, DAC3, 0);
	Max528_Set_DAC(Cfg, Vo2, DAC3, 1);
}

//驱动板参数配置
void db_Conf(Sample_Data *Sample)
{
	u16 db = 0x0;								//pin 小于   64
	Dri_Arg * DB_cfg = (Dri_Arg *)FPGA_CFG1_DATA_ADDR;

	for(db = 0; db < DRIV_BOARD_NUM; db++) {
		//执行周期
		DDR_Period(&(fpga_obj.Driver[db].Reg), DB_cfg->freq);

		if(db < 3)				//64pin参数
			Set_DHV64(DB_cfg->S_DHV1, DB_cfg->S_DHV2);
		else if(db == 3)		//32pin参数
		{
			Set_DHV32 (&(fpga_obj.Driver[db].Reg), DB_cfg->D_DHV1,  DB_cfg->D_DHV2 );
			Set_DLV32 (&(fpga_obj.Driver[db].Reg), DB_cfg->D_DLV1,  DB_cfg->D_DLV2 );
			Set_CPHV32(&(fpga_obj.Driver[db].Reg), DB_cfg->D_CPHV1, DB_cfg->D_CPHV2);
			Set_CPLV32(&(fpga_obj.Driver[db].Reg), DB_cfg->D_CPLV1, DB_cfg->D_CPLV2);
		}
		else if(db == 4)		//32pin参数
		{
			Set_DHV32 (&(fpga_obj.Driver[db].Reg), DB_cfg->D_DHV3,  DB_cfg->D_DHV4 );
			Set_DLV32 (&(fpga_obj.Driver[db].Reg), DB_cfg->D_DLV3,  DB_cfg->D_DLV4 );
			Set_CPHV32(&(fpga_obj.Driver[db].Reg), DB_cfg->D_CPHV3, DB_cfg->D_CPHV4);
			Set_CPLV32(&(fpga_obj.Driver[db].Reg), DB_cfg->D_CPLV3, DB_cfg->D_CPLV4);
		}
	}
}

//pin脚参数配置
void pin_Conf(Sample_Data *Sample)
{
	u16 db = 0x0, pin = 0x0, j = 0x0;
	pin_Arg * DB_pin = (pin_Arg *)FPGA_CFG2_DATA_ADDR;

	for(j = 0x0; j < PIN_NUM; j++) {  				//前三组为64pin, 后两组为32pin
		db  = (j < 192) ? (j/64):(((j-192)/32)+3);	//板卡编号
		pin = (j < 192) ? (j%64):((j-192)%32);		//内部pin脚号
		//IO变化位置
		IO_Var_WOpt(&(fpga_obj.Driver[db].Reg), pin%64, LE, DB_pin->Arg[j].Roll_TS);

		IO_Var_WOpt(&(fpga_obj.Driver[db].Reg), pin%64, TE, DB_pin->Arg[j].Roll_TE);

		//IO比较位置
		if(db > 2){//最后64pin需要写比较位置
			IO_Cmp_WOpt(&(fpga_obj.Driver[db].Reg), pin%64, LE, DB_pin->Arg[j].Comp_TS);

			IO_Cmp_WOpt(&(fpga_obj.Driver[db].Reg), pin%64, TE, DB_pin->Arg[j].Comp_TE);

		}
	}
}

//测试板卡ddr
void TEST_DDR(void)
{

}

//关闭电源
void CloseDps(void)
{
	u16 i = 0, j = 0;

	for(i = 0; i < 2; i++)	//线性上电
	{
		for(j = 0; j < (DPS_NUM/2); j++)
			UserDps_Switch(i, j, OFF);
	}
}



