/*
  ** @file           : iic_bus.c
  ** @brief          : IIC Bus Interface Source File
  **
  ** @attention
  **
  ** Copyright (c) 2020 ChengDuHangke.
  ** All rights reserved.
  **
  ** This software is licensed by ChengDuHangke under Ultimate Liberty license
  **
*/


/*
  ** Include
*/
#include "xiicps.h"
#include "return_val.h"
#include "debug_config.h"
#include "iic_bus.h"


/*
  ** Degfine
*/
#define 	IIC_DEVICE_ID		(XPAR_XIICPS_0_DEVICE_ID)
#define 	IIC_SCLK_RATE 		(400000)


/*
  ** Static Global Variable
*/
static XIicPs Iic_Bus;


/*
  ** Function Name        : Iic_Init
  ** Function Description : Iic Interface Bus Init
  ** Function Parameter   : Void
  ** Function Return      : INIT_FAILED 		: Init Failed
  **                        INIT_SUCCESS	    : Init Success
  ** Notes				  : None
*/
u8 Iic_Init(void)
{
	int Status;

	/* Ps_Iic Config Point  */
	XIicPs_Config *ConfigPtr;

	/* Get Ps_Iic Config */
	ConfigPtr = XIicPs_LookupConfig(IIC_DEVICE_ID);
	if (ConfigPtr == NULL) {
		debug("Iic Interface Init Failed In LookupConfig In %s Files,%d Line\n",__FILE__,__LINE__);
		return INIT_FAILED;
	}

	/* Default Config */
	Status = XIicPs_CfgInitialize(&Iic_Bus, ConfigPtr,
					ConfigPtr->BaseAddress);
	if (XST_SUCCESS != Status) {
		debug("Iic Interface Init Failed In CfgInitialize In %s Files,%d Line\n",__FILE__,__LINE__);
		return INIT_FAILED;
	}

	/* Set Clk */
	Status = XIicPs_SetSClk(&Iic_Bus, IIC_SCLK_RATE);
	if (XST_SUCCESS != Status) {
		debug("Iic Interface Init Failed In SetSClk In %s Files,%d Line\n",__FILE__,__LINE__);
		return INIT_FAILED;
	}

	/* Ps_Spi SelfTest */
	Status = XIicPs_SelfTest(&Iic_Bus);
	if (XST_SUCCESS != Status) {
		debug("Iic Interface Init Failed In SelfTest In %s Files,%d Line\n",__FILE__,__LINE__);
		return INIT_FAILED;
	}

	return INIT_SUCCESS;
}


/*
  ** Function Name        : Iic_Send
  ** Function Description : Iic Send Bus Send Data
  ** Function Parameter   : Data                : Send Data Address
  ** 						Datalength          : Send Data Length
  ** 						Iicaddr             : Send Data Slave IIC Address
  ** 						Timeout             : Wait Flag Timeout Value
  ** Function Return      : SEND_FAILED 		: Send Failed
  **                        SEND_SUCCESS	    : Send Success
  ** Notes				  : None
*/
u8 Iic_Send(u8 *Data ,u16 Datalength, u16 Iicaddr, u32 Timeout)
{
	if (XST_SUCCESS != XIicPs_MasterSendPolled(&Iic_Bus, Data, Datalength, Iicaddr)) {
		debug("Iic Interface Send Data Timeout In %s Files,%d Line\n",__FILE__,__LINE__);
		return SEND_FAILED;
	}

	while (XIicPs_BusIsBusy(&Iic_Bus)) {
		Timeout--;
		if (!Timeout) {
			debug("Iic Interface Wait Flag Timeout In %s Files,%d Line\n",__FILE__,__LINE__);
			break;
		}
	}

	return SEND_SUCCESS;
}


/*
  ** Function Name        : Iic_Recv
  ** Function Description : Iic Interface Bus Recv Data
  ** Function Parameter   : Data                : Send Data Address
  ** 						Datalength          : Send Data Length
  ** 						Iicaddr             : Send Data Slave IIC Address
  ** 						Timeout             : Wait Flag Timeout Value
  ** Function Return      : SEND_FAILED 		: Send Failed
  **                        SEND_SUCCESS	    : Send Success
  ** Notes				  : None
*/
u8 Iic_Recv(u8 *Data, u16 Datalength, u16 Iicaddr, u32 Timeout)
{
	if (XST_SUCCESS != XIicPs_MasterRecvPolled(&Iic_Bus, Data ,Datalength, Iicaddr)) {
		debug("Iic Interface Send Data Timeout In %s Files,%d Line\n",__FILE__,__LINE__);
		return SEND_FAILED;
	}

	while (XIicPs_BusIsBusy(&Iic_Bus)) {
		Timeout--;
		if (!Timeout) {
			debug("Iic Interface Wait Flag Timeout In %s Files,%d Line\n",__FILE__,__LINE__);
			break;
		}
	}

	return SEND_SUCCESS;
}


/*
  ** (C) COPYRIGHT ChengDuHangke END OF FILE
*/

