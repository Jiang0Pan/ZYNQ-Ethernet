





#include "GlobalRef.h"
#include "Hw_Ver.h"
#include "IIC.h"



//系统时间
Time_Sync_t SysTime = {
	      // 秒     分     时     日     月      年      世纪       保留
	.Data = {0, 0, 0, 1, 1, 20, 21, 0x5A}
};

//fpga控制对象
Driver_fpga	fpga_obj = {
	.Driver = {
		{
			.BoardType	  = 0x0,
			.VecSize      = 0x0,
			{
				.HWVersion        = 0,
				.PCBType          = 0,
				.PN               = {0},
				.SN               = {0},
				.Version          = {0},
				.CompTime         = {0},
				.ChipTemp  		  = 0.0,
				.ChipDAN          = 0,
				{
					.HWChan           = IIC02,
					.EEPROM_SlaveAddr = 0x51,
					.PCA953_SlaveAddr = 0x21,
				},
				.Output_LVL = {
					.Reg_Addr    = PORT0WRITE,
					.Group0_Data = 0x0,
					.Group1_Data = 0xff,
				},
			},
			{
				.Debug 	  = (volatile u32 *)(AXI_BASE_ADDR + 0x1000),
				.Opt_Addr = (volatile u32 *)(AXI_BASE_ADDR + 0x1004),
				.W_Data   = (volatile u32 *)(AXI_BASE_ADDR + 0x1008),
				.R_Data   = (volatile u32 *)(AXI_BASE_ADDR + 0x100C),
				.Data_Des = (volatile u32 *)(AXI_BASE_ADDR + 0x1010),
				.Opt_RW   = (volatile u32 *)(AXI_BASE_ADDR + 0x1014),
				.Trigger  = (volatile u32 *)(AXI_BASE_ADDR + 0x1018),
				.R_Update = (volatile u32 *)(AXI_BASE_ADDR + 0x101C),
				.WOpt_OK  = (volatile u32 *)(AXI_BASE_ADDR + 0x1020),
			},
		},
		{
			.BoardType	  = 0x0,
			.VecSize      = 0x0,
			{
				.HWVersion        = 0,
				.PCBType          = 0,
				.PN               = {0},
				.SN               = {0},
				.Version          = {0},
				.CompTime         = {0},
				.ChipTemp  		  = 0.0,
				.ChipDAN          = 0,
				{
					.HWChan           = IIC03,
					.EEPROM_SlaveAddr = 0x51,
					.PCA953_SlaveAddr = 0x21,
				},
				.Output_LVL = {
					.Reg_Addr    = PORT0WRITE,
					.Group0_Data = 0x0,
					.Group1_Data = 0xff,
				},
			},
			{
				.Debug 	  = (volatile u32 *)(AXI_BASE_ADDR + 0x2000),
				.Opt_Addr = (volatile u32 *)(AXI_BASE_ADDR + 0x2004),
				.W_Data   = (volatile u32 *)(AXI_BASE_ADDR + 0x2008),
				.R_Data   = (volatile u32 *)(AXI_BASE_ADDR + 0x200C),
				.Data_Des = (volatile u32 *)(AXI_BASE_ADDR + 0x2010),
				.Opt_RW   = (volatile u32 *)(AXI_BASE_ADDR + 0x2014),
				.Trigger  = (volatile u32 *)(AXI_BASE_ADDR + 0x2018),
				.R_Update = (volatile u32 *)(AXI_BASE_ADDR + 0x201C),
				.WOpt_OK  = (volatile u32 *)(AXI_BASE_ADDR + 0x2020),
			},
		},
		{
			.BoardType	  = 0x1,
			.VecSize      = 0x0,
			{
				.HWVersion        = 0,
				.PCBType          = 0,
				.PN               = {0},
				.SN               = {0},
				.Version          = {0},
				.CompTime         = {0},
				.ChipTemp  		  = 0.0,
				.ChipDAN          = 0,
				{
					.HWChan           = IIC04,
					.EEPROM_SlaveAddr = 0x51,
					.PCA953_SlaveAddr = 0x21,
				},
				.Output_LVL = {
					.Reg_Addr    = PORT0WRITE,
					.Group0_Data = 0x0,
					.Group1_Data = 0xff,
				},
			},
			{
				.Debug 	  = (volatile u32 *)(AXI_BASE_ADDR + 0x3000),
				.Opt_Addr = (volatile u32 *)(AXI_BASE_ADDR + 0x3004),
				.W_Data   = (volatile u32 *)(AXI_BASE_ADDR + 0x3008),
				.R_Data   = (volatile u32 *)(AXI_BASE_ADDR + 0x300C),
				.Data_Des = (volatile u32 *)(AXI_BASE_ADDR + 0x3010),
				.Opt_RW   = (volatile u32 *)(AXI_BASE_ADDR + 0x3014),
				.R_Update = (volatile u32 *)(AXI_BASE_ADDR + 0x3018),
				.Trigger  = (volatile u32 *)(AXI_BASE_ADDR + 0x3018),
				.R_Update = (volatile u32 *)(AXI_BASE_ADDR + 0x301C),
				.WOpt_OK  = (volatile u32 *)(AXI_BASE_ADDR + 0x3020),
			},
		},
		{
			.BoardType	  = 0x2,
			.VecSize      = 0x0,
			{
				.HWVersion        = 0,
				.PCBType          = 0,
				.PN               = {0},
				.SN               = {0},
				.Version          = {0},
				.CompTime         = {0},
				.ChipTemp  		  = 0.0,
				.ChipDAN          = 0,
				{
					.HWChan           = IIC00,
					.EEPROM_SlaveAddr = 0x51,
					.PCA953_SlaveAddr = 0x21,
				},
				.Output_LVL = {
					.Reg_Addr    = PORT0WRITE,
					.Group0_Data = 0x0,
					.Group1_Data = 0xff,
				},
			},
			{
				.Debug 	  = (volatile u32 *)(AXI_BASE_ADDR + 0x4000),
				.Opt_Addr = (volatile u32 *)(AXI_BASE_ADDR + 0x4004),
				.W_Data   = (volatile u32 *)(AXI_BASE_ADDR + 0x4008),
				.R_Data   = (volatile u32 *)(AXI_BASE_ADDR + 0x400C),
				.Data_Des = (volatile u32 *)(AXI_BASE_ADDR + 0x4010),
				.Opt_RW   = (volatile u32 *)(AXI_BASE_ADDR + 0x4014),
				.Trigger  = (volatile u32 *)(AXI_BASE_ADDR + 0x4018),
				.R_Update = (volatile u32 *)(AXI_BASE_ADDR + 0x401C),
				.WOpt_OK  = (volatile u32 *)(AXI_BASE_ADDR + 0x4020),
			},
		},
		{
			.BoardType	  = 0x3,
			.VecSize      = 0x0,
			{
				.HWVersion        = 0,
				.PCBType          = 0,
				.PN               = {0},
				.SN               = {0},
				.Version          = {0},
				.CompTime         = {0},
				.ChipTemp  		  = 0.0,
				.ChipDAN          = 0,
				{
					.HWChan           = IIC01,
					.EEPROM_SlaveAddr = 0x51,
					.PCA953_SlaveAddr = 0x21,
				},
				.Output_LVL = {
					.Reg_Addr    = PORT0WRITE,
					.Group0_Data = 0x0,
					.Group1_Data = 0xff,
				},
			},
			{
				.Debug 	  = (volatile u32 *)(AXI_BASE_ADDR + 0x5000),
				.Opt_Addr = (volatile u32 *)(AXI_BASE_ADDR + 0x5004),
				.W_Data   = (volatile u32 *)(AXI_BASE_ADDR + 0x5008),
				.R_Data   = (volatile u32 *)(AXI_BASE_ADDR + 0x500C),
				.Data_Des = (volatile u32 *)(AXI_BASE_ADDR + 0x5010),
				.Opt_RW   = (volatile u32 *)(AXI_BASE_ADDR + 0x5014),
				.Trigger  = (volatile u32 *)(AXI_BASE_ADDR + 0x5018),
				.R_Update = (volatile u32 *)(AXI_BASE_ADDR + 0x501C),
				.WOpt_OK  = (volatile u32 *)(AXI_BASE_ADDR + 0x5020),
			},
		},
	},
	.Vec_Addr = {
		.Debug  = (volatile u32 *)(AXI_BASE_ADDR + 0x6000),
		.S_Addr = (volatile u32 *)(AXI_BASE_ADDR + 0x6004),
		.D_Len  = (volatile u32 *)(AXI_BASE_ADDR + 0x6008),
		.W_Trig = (volatile u32 *)(AXI_BASE_ADDR + 0x600C),
		.Serial = (volatile u32 *)(AXI_BASE_ADDR + 0x6010),
		.MV_Flag= (volatile u32 *)(AXI_BASE_ADDR + 0x6014),
	}
};

DpsMsg	dps_info = {
	.GDQ54_SlaveAddr  = 0x5B,
	.EEPROM_SlaveAddr = 0x50,
	.PCA953_SlaveAddr = 0x20,
	.AD5694_SlaveAddr = 0x0C,
	.DBMsg = {
		{
			.Chan             = IIC06,
			.UseMask  		  = 0x0,
			.OpenMask 		  = 0x0,
			.CloseMask 		  = 0x0,
			.DpsAddr		  = {0x10, 0x11, 0x12, 0x13, 0x14, 0x15},
			.HWVersion        = 0,
			.PCBType          = 0,
			.PN               = {0},
			.SN               = {0},
			.Output_LVL = {
				.Reg_Addr    = PORT0WRITE,
				.Group0_Data = 0x0,
				.Group1_Data = 0xff,
			},
		},//DB0信息
		{
			.Chan             = IIC07,
			.UseMask  		  = 0x0,
			.OpenMask 		  = 0x0,
			.CloseMask 		  = 0x0,
			.DpsAddr		  = {0x17, 0x18, 0x19, 0x20, 0x21, 0x22},
			.HWVersion        = 0,
			.PCBType          = 0,
			.PN               = {0},
			.SN               = {0},
			.Output_LVL = {
				.Reg_Addr    = PORT0WRITE,
				.Group0_Data = 0x0,
				.Group1_Data = 0xff,
			},
		},//DB1信息
	},
};

BKBMsg	bbd_info = {
	.HWChan	          = IIC08,
	.EEPROM_SlaveAddr = 0x50,
	.PCA953_SlaveAddr = 0x20,
	.TOChan			  = IIC09,
	.IO_SlaveAddr     = 0x21,
	.HWVersion        = 0,
	.PCBType          = 0,
	.PN               = {0},
	.SN               = {0},

	.Output_LVL = {
		.Reg_Addr    = PORT0WRITE,
		.Group0_Data = 0x0,
		.Group1_Data = 0xff,
	},

	.Ctl_Output = {
		.Reg_Addr    = PORT0WRITE,
		.Group0_Data = 0x0,
		.Group1_Data = 0xff,
	},
};

MBMsg	mbd_info = {
	.HWChan 		  = PSIIC,
	.EEPROM_SlaveAddr = 0x50,
	.PCA953_SlaveAddr = 0x20,
	.HWVersion 		  = 0,
	.PCBType 		  = 0,
	.PN 			  = {0},
	.SN 			  = {0},

	.Version0 		  = {0},
	.CompTime0 		  = {0},
	.Version1 		  = {0},
	.CompTime1 		  = {0},
	.ChipTemp 		  = 0.0,
	.ChipDAN 		  = 0,
	.Output_LVL = {
		.Reg_Addr    = PORT0WRITE,
		.Group0_Data = 0x0,
		.Group1_Data = 0xff,
	}
};

BackIsp	All_isp;


