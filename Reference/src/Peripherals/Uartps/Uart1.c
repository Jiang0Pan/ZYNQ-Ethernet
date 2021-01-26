#include "uart1.h"
#include "error.h"


u8 tag = 0;
u32 count = 0;
static XUartPs UartPs_1;
u8 Rx_buf[Rx_MAX_LEN] = {0};

XUartPsFormat uart_format =
{
	.BaudRate = XUARTPS_DFT_BAUDRATE,   	//默认波特率 115200
	.DataBits = XUARTPS_FORMAT_8_BITS,		//数据位
	.Parity   = XUARTPS_FORMAT_NO_PARITY,	//校验位
	.StopBits = XUARTPS_FORMAT_1_STOP_BIT,	//停止位
};

/***********************************************************************
	[功	       能	]串口中断回调函数
	[参            数	]CallBackRef:回调函数参数
	[返    回    值	]无
***********************************************************************/
static void UartIntrHandler(void *CallBackRef)
{
	XUartPs *Uartptr = (XUartPs *)CallBackRef;
	u32 RecCount = 0;
	u32 Status = 0;

	//读取中断状态
	Status = XUartPs_ReadReg(Uartptr->Config.BaseAddress, XUARTPS_IMR_OFFSET);
	Status &= XUartPs_ReadReg(Uartptr->Config.BaseAddress, XUARTPS_ISR_OFFSET);

	if(Status & ((u32)XUARTPS_IXR_RXOVR))   	//接收FIFO中断
	{
		RecCount = XUartPs_Recv(Uartptr, &Rx_buf[count], Rx_MAX_LEN);	//接收数据
		count += RecCount;
		XUartPs_WriteReg(Uartptr->Config.BaseAddress, XUARTPS_ISR_OFFSET, XUARTPS_IXR_RXOVR);	//清除中断标志
	}
	if(Status & ((u32)XUARTPS_IXR_TOUT))		//接收超时中断
	{
		RecCount = XUartPs_Recv(Uartptr, &Rx_buf[count], Rx_MAX_LEN);	//接收最后一次数据
		count += RecCount;
		XUartPs_WriteReg(Uartptr->Config.BaseAddress, XUARTPS_ISR_OFFSET, XUARTPS_IXR_TOUT);	//清除中断标志

		/*****************************数据处理******************************/
		Rx_buf[count] = '\0';
		xil_printf("%s\n", Rx_buf);

		memset(Rx_buf, 0 ,count);
		tag = 1;
		/*******************************结束*******************************/

		count = 0;
	}
}

/***********************************************************************
	[功	       能	]串口初始化
	[参            数	]无
	[返    回    值	]初始化是否OK
***********************************************************************/
s32 Uartps_Init(void)
{
	s32 Status = 0;
	XUartPs_Config *Uart1;

	//串口初始化
	Uart1 = XUartPs_LookupConfig(UART1_ID);
	Status = XUartPs_CfgInitialize(&UartPs_1, Uart1, Uart1->BaseAddress);
	if(Status != SUCCESS)
		return FAILURE;


	Status = XUartPs_SetDataFormat(&UartPs_1, &uart_format);//设置串口参数
	if(Status != SUCCESS)
		return FAILURE;

	XUartPs_SetOperMode(&UartPs_1, XUARTPS_OPER_MODE_NORMAL); //正常模式

	Status = XScuGic_Connect(&XPS_XScuGic, XPAR_XUARTPS_1_INTR,
					  (Xil_ExceptionHandler)UartIntrHandler,
					  (void *)&UartPs_1);
	if (Status != SUCCESS)
		return FAILURE;

	XUartPs_SetFifoThreshold(&UartPs_1, 1);				//设置fifo阈值

	XUartPs_SetRecvTimeout(&UartPs_1, 8);				//设置超时周期8*4=32个

	XUartPs_SetInterruptMask(&UartPs_1, XUARTPS_IXR_TOUT|XUARTPS_IXR_RXOVR);//设置触发中断标志

	//指定中断号到cpu1
	Mask_CPU1_IntrID(XPAR_XUARTPS_1_INTR);

	//使能中断
	XScuGic_Enable(&XPS_XScuGic, XPAR_XUARTPS_1_INTR);

	return SUCCESS;
}







