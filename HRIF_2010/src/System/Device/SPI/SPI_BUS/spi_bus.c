/*
  ** @file           : spi_bus.c
  ** @brief          : Spi Bus Interface Source File
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
#include "xspips.h"
#include "debug_config.h"
#include "return_val.h"
#include "spi_bus.h"


/*
  ** Define
*/
#define 	SPI_DEVICE_ID		(XPAR_XSPIPS_1_DEVICE_ID)


/*
  ** Static Global Variable
*/
static XSpiPs Spi_Bus;


/*
  ** Function Name        : Spi_Init
  ** Function Description : Spi Interface Bus Init
  ** Function Parameter   : Void
  ** Function Return      : INIT_FAILED 		: Init Failed
  **                        INIT_SUCCESS	    : Init Success
  ** Notes				  : None
*/
u8 Spi_Init(void)
{
	u8 Status;

	/* Ps_Spi Config Point  */
	XSpiPs_Config *SpiConfig;

	/* Get Ps_Spi Config */
	SpiConfig = XSpiPs_LookupConfig(SPI_DEVICE_ID);
	if (NULL == SpiConfig) {
		debug("Spi Interface Init Failed In LookupConfig In %s Files,%d Line\n",__FILE__,__LINE__);
		return INIT_FAILED;
	}

	/* Default Config */
	Status = XSpiPs_CfgInitialize(&Spi_Bus, SpiConfig,
				       SpiConfig->BaseAddress);
	if (XST_SUCCESS != Status) {
		debug("Spi Interface Init Failed In CfgInitialize In %s Files,%d Line\n",__FILE__,__LINE__);
		return INIT_FAILED;
	}

	/* Ps_Spi SelfTest */
	Status = XSpiPs_SelfTest(&Spi_Bus);
	if (XST_SUCCESS != Status) {
		debug("Spi Interface Init Failed In SelfTest In %s Files,%d Line\n",__FILE__,__LINE__);
		return INIT_FAILED;
	}

	/* Ps_Spi Set Option CPOL:0 CPHA:1 */
	Status = XSpiPs_SetOptions(&Spi_Bus, XSPIPS_MASTER_OPTION | XSPIPS_FORCE_SSELECT_OPTION);
	if (XST_SUCCESS != Status) {
		debug("Spi Interface Init Failed In SetOptions In %s Files,%d Line\n",__FILE__,__LINE__);
		return INIT_FAILED;
	}

	/* Set Clk . This is 200M/64 */
	Status = XSpiPs_SetClkPrescaler(&Spi_Bus, XSPIPS_CLK_PRESCALE_64);
	if (XST_SUCCESS != Status) {
		debug("Spi Interface Init Failed In SetClkPrescaler In %s Files,%d Line\n",__FILE__,__LINE__);
		return INIT_FAILED;
	}

	return INIT_SUCCESS;
}


/*
  ** Function Name        : Spi_ReadWrite
  ** Function Description : Spi Interface Bus Read And Write Data
  ** Function Parameter   : Txdata              : Write Data Address
  ** 						Rxdata              : Read Data Address
  ** 						Length              : Data Length
  ** Function Return      : OPER_FAILED 		: Operation Failed
  **                        OPER_SUCCESS	    : Operation Success
  ** Notes				  : None
*/
u8 Spi_ReadWrite(u8 *Txdata ,u8 *Rxdata, u32 Length)
{
	if (XST_SUCCESS != XSpiPs_PolledTransfer(&Spi_Bus,Txdata,Rxdata,Length)) {
		debug("Spi Interface PolledTransfer Data Failed In %s Files,%d Line\n",__FILE__,__LINE__);
		return WRITE_READ_FAILED;
	}

	return WRITE_READ_SUCCESS;
}


/*
  ** (C) COPYRIGHT ChengDuHangke END OF FILE
*/
