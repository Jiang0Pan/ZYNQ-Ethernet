

#include "SystemInfo.h"
#include "string.h"
#include "stdio.h"


//读取一块驱动板的信息
void ReadDBinfo(struct _REG_ * Cfg, struct _MSG_ *Msg)
{
	u8 HwVer = 0;

	ChipInfo Chip;
	memset(&Chip, 0, sizeof(Chip));

	Fpga_ROpt(Cfg,  VERSION, &Chip.Version.V_Data);
	Fpga_ROpt(Cfg,     DATE, &Chip.Date.D_Data   );
	Fpga_ROpt(Cfg,     TIME, &Chip.Time.T_Data   );
	Fpga_ROpt(Cfg,     DATE, &Chip.Core_temp     );
	Fpga_ROpt(Cfg,     DAN1, &Chip.DAN.DANL      );
	Fpga_ROpt(Cfg,     DAN2, &Chip.DAN.DANH      );

	sprintf((char *)Msg->Version, "%d.%d",
			((Chip.Version.Publish_V.Major)&0xf),
			((Chip.Version.Publish_V.Minor)&0xf));

	sprintf((char *)Msg->CompTime, "%d%d%d%d/%d%d/%d%d %d%d:%d%d",
			((Chip.Date.Year  )>>12)&0xf, ((Chip.Date.Year  )>>8)&0xf,
			((Chip.Date.Year  )>> 4)&0xf, ((Chip.Date.Year  )>>0)&0xf,
			((Chip.Date.Month )>> 4)&0xf, ((Chip.Date.Month )>>0)&0xf,
			((Chip.Date.Day   )>> 4)&0xf, ((Chip.Date.Day   )>>0)&0xf,
			((Chip.Time.Hour  )>> 4)&0xf, ((Chip.Time.Hour  )>>0)&0xf,
			((Chip.Time.Minute)>> 4)&0xf, ((Chip.Time.Minute)>>0)&0xf);

	Msg->ChipTemp  = (((Chip.Core_temp)*CORE_TEMP_COE)/4096) - CORE_TEMP_OFFSET;
	Msg->ChipDAN   = Chip.DAN.D_Data;

	ReadIO_Info(&HwVer, &Msg->Dev);
	Msg->HWVersion = (HwVer >> 4) & 0xf;
	Msg->PCBType   = (HwVer >> 0) & 0xf;

	EEPROM_ReadBuff( 0, Msg->PN, 32, Msg->Dev.EEPROM_SlaveAddr, Msg->Dev.HWChan);
	CRC8(Msg->PN, 31);
	EEPROM_ReadBuff(32, Msg->SN, 32, Msg->Dev.EEPROM_SlaveAddr, Msg->Dev.HWChan);
	CRC8(Msg->SN, 31);



}

//读取电源信息
void ReadDpsinfo(void)
{
	u8 i = 0, tp = 0x0;

	DB_Info_t  *dp[2];
	dp[0] = (DB_Info_t *)DPSB0_INFO_ADDR;
	dp[1] = (DB_Info_t *)DPSB1_INFO_ADDR;

	for(i = 0; i < 2; i++) {
		IO_Group_Get(Group0, &tp, dps_info.PCA953_SlaveAddr, dps_info.DBMsg[i].Chan);
		dps_info.DBMsg[i].HWVersion = (tp >> 4) & 0xf;
		dps_info.DBMsg[i].PCBType   = (tp >> 0) & 0xf;
		EEPROM_ReadBuff( 0, dps_info.DBMsg[i].PN, 32, dps_info.EEPROM_SlaveAddr, dps_info.DBMsg[i].Chan);
		CRC8(dps_info.DBMsg[i].PN, 31);
		EEPROM_ReadBuff(32, dps_info.DBMsg[i].SN, 32, dps_info.PCA953_SlaveAddr, dps_info.DBMsg[i].Chan);
		CRC8(dps_info.DBMsg[i].SN, 31);

		memcpy(dp[i]->DB_ERP_PN,   dps_info.DBMsg[i].PN, 16);
		memcpy(dp[i]->DB_ERP_SN,   dps_info.DBMsg[i].SN, 16);
		memcpy(dp[i]->DB_VSN_HW,  &dps_info.DBMsg[i].HWVersion, 2);
		memcpy(dp[i]->DB_OTR_BT,  &dps_info.DBMsg[i].PCBType, 4);
	}
}

//读取背板信息
void ReadBKinfo(void)
{
	u8 tp = 0x0;

	DB_Info_t * bk = (DB_Info_t *)BKB_INFO_ADDR;

	IO_Group_Get(Group0, &tp, bbd_info.PCA953_SlaveAddr, bbd_info.HWChan);
	bbd_info.HWVersion = (tp >> 4) & 0xf;
	bbd_info.PCBType   = (tp >> 0) & 0xf;
	EEPROM_ReadBuff( 0, bbd_info.PN, 32, bbd_info.EEPROM_SlaveAddr, bbd_info.HWChan);
	CRC8(bbd_info.PN, 31);
	EEPROM_ReadBuff(32, bbd_info.SN, 32, bbd_info.PCA953_SlaveAddr, bbd_info.HWChan);
	CRC8(bbd_info.SN, 31);

	memcpy(bk->DB_ERP_PN,   bbd_info.PN, 16);
	memcpy(bk->DB_ERP_SN,   bbd_info.SN, 16);
	memcpy(bk->DB_VSN_HW,  &bbd_info.HWVersion, 2);
	memcpy(bk->DB_OTR_BT,  &bbd_info.PCBType, 4);
}

//读取主板信息
void ReadMBinfo(void)
{
	u8 tp = 0x0;
	char Str[16] = {0};

	MB_Info_t *mb = (MB_Info_t *)MB_INFO_ADDR;

	//pl芯片信息
	ChipInfo plMsg;
	memset(&plMsg, 0, sizeof(ChipInfo));

	plMsg.Version.V_Data = PL_VERSION;
	plMsg.Date.D_Data    = PL_DATE;
	plMsg.Time.T_Data    = PL_TIME;
	plMsg.Core_temp		 = PL_TEMP;
	plMsg.DAN.DANL       = PL_DAN1;
	plMsg.DAN.DANH       = PL_DAN2;

	IO_Group_Get(Group0, &tp, mbd_info.PCA953_SlaveAddr, mbd_info.HWChan);
	mbd_info.HWVersion = (tp >> 4) & 0xf;
	mbd_info.PCBType   = (tp >> 0) & 0xf;
	EEPROM_ReadBuff( 0, mbd_info.PN, 32, mbd_info.EEPROM_SlaveAddr, mbd_info.HWChan);
	CRC8(mbd_info.PN, 31);
	EEPROM_ReadBuff(32, mbd_info.SN, 32, mbd_info.PCA953_SlaveAddr, mbd_info.HWChan);
	CRC8(mbd_info.SN, 31);

	memcpy(mbd_info.Version0, ZYNQ_VERSION, strlen(ZYNQ_VERSION));

	memcpy(Str, __DATE__, strlen(__DATE__));
	int year  = ((((Str[7]-'0')*10+(Str[8]-'0'))*10+(Str[9]-'0'))*10+(Str[10]-'0'));
	int month = (Str[2] == 'n' ? (Str[1] == 'a' ? 1 : 6) \
							 : Str[2] == 'b' ? 2 \
							 : Str[2] == 'r' ? (Str[0] == 'M' ? 3 : 4) \
							 : Str[2] == 'y' ? 5 \
							 : Str[2] == 'l' ? 7 \
							 : Str[2] == 'g' ? 8 \
							 : Str[2] == 'p' ? 9 \
							 : Str[2] == 't' ? 10\
							 : Str[2] == 'v' ? 11 : 12);
	int day   = ((Str [4] == ' ' ? 0 : Str[4] - '0') * 10 + (Str[5] - '0'));

	memcpy(Str, __TIME__, strlen(__TIME__));
	int hour  = ((Str[0] - '0') * 10 + (Str[1] - '0'));
	int minute= ((Str[3] - '0') * 10 + (Str[4] - '0'));
	sprintf((char*)(mbd_info.CompTime0), "%d/%02d/%02d %02d:%02d", year, month, day, hour, minute);


	sprintf((char *)(mbd_info.Version1), "%d.%d",
			((plMsg.Version.Publish_V.Major)&0xf),
			((plMsg.Version.Publish_V.Minor)&0xf));


	sprintf((char *)(mbd_info.CompTime1), "%d%d%d%d/%d%d/%d%d %d%d:%d%d",
			   ((plMsg.Date.Year  )>>12)&0xf, ((plMsg.Date.Year  )>>8)&0xf,
			   ((plMsg.Date.Year  )>> 4)&0xf, ((plMsg.Date.Year  )>>0)&0xf,
			   ((plMsg.Date.Month )>> 4)&0xf, ((plMsg.Date.Month )>>0)&0xf,
			   ((plMsg.Date.Day   )>> 4)&0xf, ((plMsg.Date.Day   )>>0)&0xf,
			   ((plMsg.Time.Hour  )>> 4)&0xf, ((plMsg.Time.Hour  )>>0)&0xf,
			   ((plMsg.Time.Minute)>> 4)&0xf, ((plMsg.Time.Minute)>>0)&0xf);

	memcpy(mb->MB_ERP_PN,     mbd_info.PN, 16);
	memcpy(mb->MB_ERP_SN,     mbd_info.SN, 16);
	memcpy(mb->MB_VSN_HW,    &mbd_info.HWVersion, 2);
	memcpy(mb->MB_VSN_FW0,    mbd_info.Version0, 16);
	memcpy(mb->MB_VSN_FWCT0,  mbd_info.CompTime0, 16);
	memcpy(mb->MB_VSN_FW1,    mbd_info.Version1, 16);
	memcpy(mb->MB_VSN_FWCT1,  mbd_info.CompTime1, 16);
	memcpy(mb->MB_OTR_BT,    &mbd_info.PCBType, 4);
}

//系统硬件设备初始化
void BoardHW_Init(void)
{
	u16 i = 0;

	//主板初件初始化
	PCA_IO_Init(&(mbd_info.Output_LVL), bbd_info.PCA953_SlaveAddr, bbd_info.HWChan);

	//背板硬件初始化
	PCA_IO_Init(&(bbd_info.Output_LVL), bbd_info.PCA953_SlaveAddr, bbd_info.HWChan);
	PCA_IO_Init(&(bbd_info.Ctl_Output),     bbd_info.IO_SlaveAddr, bbd_info.TOChan);

	//电源板硬件初始化
	PCA_IO_Init(&(dps_info.DBMsg[0].Output_LVL), dps_info.PCA953_SlaveAddr, dps_info.DBMsg[0].Chan);
	Set_AD5694(0, 2, dps_info.AD5694_SlaveAddr, dps_info.DBMsg[0].Chan);
	Set_AD5694(0, 3, dps_info.AD5694_SlaveAddr, dps_info.DBMsg[0].Chan);
	Cpld_Init(0);

	PCA_IO_Init(&(dps_info.DBMsg[1].Output_LVL), dps_info.PCA953_SlaveAddr, dps_info.DBMsg[1].Chan);
	Set_AD5694(0, 2, dps_info.AD5694_SlaveAddr, dps_info.DBMsg[1].Chan);
	Set_AD5694(0, 3, dps_info.AD5694_SlaveAddr, dps_info.DBMsg[1].Chan);
	Cpld_Init(1);

	//驱动板硬件初始化
	for(i = 0; i < DRIV_BOARD_NUM; i++) {

		PCA_IO_Init(&(fpga_obj.Driver[i].Msg.Output_LVL), fpga_obj.Driver[i].Msg.Dev.PCA953_SlaveAddr, fpga_obj.Driver[i].Msg.Dev.HWChan);
		//关闭fpga spi
		IO_Level_Set(&(fpga_obj.Driver[i].Msg.Output_LVL), Group1, pin2, 1, fpga_obj.Driver[i].Msg.Dev.PCA953_SlaveAddr, fpga_obj.Driver[i].Msg.Dev.HWChan);

		//初始化528
		Max528_Init(&(fpga_obj.Driver[i].Reg));

		//初始化9972
		Max9972_InitCfg(&(fpga_obj.Driver[i].Reg));
	}
}

//读取系统设备信息
void ReadSysteminfo(void)
{
	u16 i = 0;
	DB_Info_t  *db[DRIV_BOARD_NUM];

	db[0] = (DB_Info_t *)DB0_INFO_ADDR;
	db[1] = (DB_Info_t *)DB1_INFO_ADDR;
	db[2] = (DB_Info_t *)DB2_INFO_ADDR;
	db[3] = (DB_Info_t *)DB3_INFO_ADDR;
	db[4] = (DB_Info_t *)DB4_INFO_ADDR;

	ReadMBinfo();
	ReadBKinfo();
	ReadDpsinfo();
	for(i = 0; i < DRIV_BOARD_NUM; i++)
	{
		ReadDBinfo(&(fpga_obj.Driver[i].Reg), &(fpga_obj.Driver[i].Msg));			//读取芯片信息
		memcpy(db[i]->DB_ERP_PN,   fpga_obj.Driver[i].Msg.PN, 16);
		memcpy(db[i]->DB_ERP_SN,   fpga_obj.Driver[i].Msg.SN, 16);
		memcpy(db[i]->DB_VSN_HW,  &fpga_obj.Driver[i].Msg.HWVersion, 2);
		memcpy(db[i]->DB_VSN_FW,   fpga_obj.Driver[i].Msg.Version, 16);
		memcpy(db[i]->DB_VSN_FWCT, fpga_obj.Driver[i].Msg.CompTime, 16);
		memcpy(db[i]->DB_OTR_BT,  &fpga_obj.Driver[i].Msg.PCBType, 4);
	}
}









