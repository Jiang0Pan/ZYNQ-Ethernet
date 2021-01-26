#include "uart1.h"
#include "error.h"


u8 tag = 0;
u32 count = 0;
static XUartPs UartPs_1;
u8 Rx_buf[Rx_MAX_LEN] = {0};

XUartPsFormat uart_format =
{
	.BaudRate = XUARTPS_DFT_BAUDRATE,   	//Ĭ�ϲ����� 115200
	.DataBits = XUARTPS_FORMAT_8_BITS,		//����λ
	.Parity   = XUARTPS_FORMAT_NO_PARITY,	//У��λ
	.StopBits = XUARTPS_FORMAT_1_STOP_BIT,	//ֹͣλ
};

/***********************************************************************
	[��	       ��	]�����жϻص�����
	[��            ��	]CallBackRef:�ص���������
	[��    ��    ֵ	]��
***********************************************************************/
static void UartIntrHandler(void *CallBackRef)
{
	XUartPs *Uartptr = (XUartPs *)CallBackRef;
	u32 RecCount = 0;
	u32 Status = 0;

	//��ȡ�ж�״̬
	Status = XUartPs_ReadReg(Uartptr->Config.BaseAddress, XUARTPS_IMR_OFFSET);
	Status &= XUartPs_ReadReg(Uartptr->Config.BaseAddress, XUARTPS_ISR_OFFSET);

	if(Status & ((u32)XUARTPS_IXR_RXOVR))   	//����FIFO�ж�
	{
		RecCount = XUartPs_Recv(Uartptr, &Rx_buf[count], Rx_MAX_LEN);	//��������
		count += RecCount;
		XUartPs_WriteReg(Uartptr->Config.BaseAddress, XUARTPS_ISR_OFFSET, XUARTPS_IXR_RXOVR);	//����жϱ�־
	}
	if(Status & ((u32)XUARTPS_IXR_TOUT))		//���ճ�ʱ�ж�
	{
		RecCount = XUartPs_Recv(Uartptr, &Rx_buf[count], Rx_MAX_LEN);	//�������һ������
		count += RecCount;
		XUartPs_WriteReg(Uartptr->Config.BaseAddress, XUARTPS_ISR_OFFSET, XUARTPS_IXR_TOUT);	//����жϱ�־

		/*****************************���ݴ���******************************/
		Rx_buf[count] = '\0';
		xil_printf("%s\n", Rx_buf);

		memset(Rx_buf, 0 ,count);
		tag = 1;
		/*******************************����*******************************/

		count = 0;
	}
}

/***********************************************************************
	[��	       ��	]���ڳ�ʼ��
	[��            ��	]��
	[��    ��    ֵ	]��ʼ���Ƿ�OK
***********************************************************************/
s32 Uartps_Init(void)
{
	s32 Status = 0;
	XUartPs_Config *Uart1;

	//���ڳ�ʼ��
	Uart1 = XUartPs_LookupConfig(UART1_ID);
	Status = XUartPs_CfgInitialize(&UartPs_1, Uart1, Uart1->BaseAddress);
	if(Status != SUCCESS)
		return FAILURE;


	Status = XUartPs_SetDataFormat(&UartPs_1, &uart_format);//���ô��ڲ���
	if(Status != SUCCESS)
		return FAILURE;

	XUartPs_SetOperMode(&UartPs_1, XUARTPS_OPER_MODE_NORMAL); //����ģʽ

	Status = XScuGic_Connect(&XPS_XScuGic, XPAR_XUARTPS_1_INTR,
					  (Xil_ExceptionHandler)UartIntrHandler,
					  (void *)&UartPs_1);
	if (Status != SUCCESS)
		return FAILURE;

	XUartPs_SetFifoThreshold(&UartPs_1, 1);				//����fifo��ֵ

	XUartPs_SetRecvTimeout(&UartPs_1, 8);				//���ó�ʱ����8*4=32��

	XUartPs_SetInterruptMask(&UartPs_1, XUARTPS_IXR_TOUT|XUARTPS_IXR_RXOVR);//���ô����жϱ�־

	//ָ���жϺŵ�cpu1
	Mask_CPU1_IntrID(XPAR_XUARTPS_1_INTR);

	//ʹ���ж�
	XScuGic_Enable(&XPS_XScuGic, XPAR_XUARTPS_1_INTR);

	return SUCCESS;
}







