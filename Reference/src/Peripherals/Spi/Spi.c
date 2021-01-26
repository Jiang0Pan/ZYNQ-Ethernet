





#include "spi.h"



XSpiPs psSpi[2];



/***********************************************************************
	[功	       能	]初始化spi接口
	[参            数	]无
	[返    回    值	]初始化是否成功
***********************************************************************/
s32 Spi_Init(void)
{
	s32 Status = 1;
	XSpiPs_Config *SpiConfig;


	SpiConfig = XSpiPs_LookupConfig(SPI0);
	if (NULL == SpiConfig)
		return FAILURE;
	SpiConfig = XSpiPs_LookupConfig(SPI1);
	if (NULL == SpiConfig)
		return FAILURE;

	Status = XSpiPs_CfgInitialize(&psSpi[SPI0], SpiConfig, SpiConfig->BaseAddress);
	if (Status != SUCCESS)
		return FAILURE;
	Status = XSpiPs_CfgInitialize(&psSpi[SPI1], SpiConfig, SpiConfig->BaseAddress);
	if (Status != SUCCESS)
		return FAILURE;

	Status = XSpiPs_SelfTest(&psSpi[SPI0]);
	if (Status != SUCCESS)
		return FAILURE;
	Status = XSpiPs_SelfTest(&psSpi[SPI1]);
	if (Status != SUCCESS)
		return FAILURE;

	//设置主/从，时钟、相位:CPOL=0,CPHA=0 XSPIPS_CPHA_OPTIONS
	Status = XSpiPs_SetOptions(&psSpi[SPI0], XSPIPS_MASTER_OPTION);
	if (Status != SUCCESS)
		return FAILURE;
	Status = XSpiPs_SetOptions(&psSpi[SPI1], XSPIPS_MASTER_OPTION);
	if (Status != SUCCESS)
		return FAILURE;

	Status = XSpiPs_SetClkPrescaler(&psSpi[SPI0], XSPIPS_CLK_PRESCALE_4);
	if (Status != SUCCESS)
		return FAILURE;
	Status = XSpiPs_SetClkPrescaler(&psSpi[SPI1], XSPIPS_CLK_PRESCALE_4);
	if (Status != SUCCESS)
		return FAILURE;

	XSpiPs_Enable(&psSpi[SPI0]);
	XSpiPs_Enable(&psSpi[SPI1]);

	return SUCCESS;
}

/***********************************************************************
	[功	       能	]spi传输
	[参            数	]Tx:发送数据指针, Rx:接收数据指针, size:收发字节数, spix:spi编号
	[返    回    值	]传输是否ok
***********************************************************************/
s32 Spi_Transfer(u8 *Tx, u8 *Rx, u8 size, Spi spix)
{
	if(XSpiPs_PolledTransfer(&psSpi[spix], Tx, Rx, size))
		return FAILURE;

	return SUCCESS;
}


u8 Spi_ReadWrite(u8 *Txdata ,u8 *Rxdata, u32 Length)
{
	if (XST_SUCCESS != XSpiPs_PolledTransfer(&psSpi[1],Txdata,Rxdata,Length)) {
		debug("Spi Interface PolledTransfer Data Failed In %s Files,%d Line\n",__FILE__,__LINE__);
		return OPER_FAILED;
	}

	return OPER_SUCCESS;
}


