/*
 * main.c
 *
 *  Created on: 2021��1��26��
 *      Author: 31573
 */


/*
  ** Include
*/
#include "xparameters.h"
#include "xiicps.h"
#include "xil_printf.h"


/*
  ** Define
*/
/*
  ** The following constants map to the XPAR parameters created in the
  ** xparameters.h file. They are defined here such that a user can easily
  ** change all the needed parameters in one place.
*/
#define 		IIC_DEVICE_ID			XPAR_XIICPS_0_DEVICE_ID


/*
  ** The slave address to send to and receive from.
*/
#define 		IIC_SLAVE_ADDR			(0x55)
#define 		IIC_SCLK_RATE			(100000)


/*
  ** The following constant controls the length of the buffers to be sent
  ** and received with the IIC.
*/
#define 		TEST_BUFFER_SIZE		(132)


static XIicPs Iic;		/**< Instance of the IIC Device */

int main(void)
{
	int Status;
	XIic_Config *ConfigPtr;	/* Pointer to configuration data */

	while (1)
	{

	}

	return 0;
}

