/*
  ** @file           : operation.c
  ** @brief          : Tcp Data Operation Source File
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
#include "return_val.h"
#include "debug_config.h"
#include "app_layer_protocol.h"
#include "tcp_server.h"
#include "ack.h"
#include "verify.h"
#include "GlobalRef.h"
#include "system_emio.h"
#include "main.h"
#include "system_state.h"
#include "memory_map.h"
#include "operation.h"
#include "fpga.h"
#include "unistd.h"
#include "Gpio.h"


/*
  ** Define
*/
/* Check Crc */
#define     CHECK_CRC           (0x0)
/* AXI LITE */
#define     AXI_LITE            (0x0)


/*
  ** Static Funtion
*/
static u8 Beep_Control(void * Data);
static u8 Time_Synchronous(void * Data);
static u8 DPS_Config(void * Data);
static u8 Pattern_Handle(void * Data);
static u8 Control_Command(void * Data);
static u8 Timer_Restart(void * Data);
static u8 Pin_Config(void * Data);
static u8 S_Sample_Data(void * Data);
static u8 DPS_Channel_Status(void * Data);
static u8 Realtime_Status(void * Data);
static u8 Pattern_Error_Information(void * Data);
static u8 Set_Pattern_Status(void * Data);
static u8 Driver_Board_Version(void * Data);
static u8 Pattern_Status_Debug(void * Data);
static u8 Pattern_Status(void * Data);
static u8 Pin_Config_Debug(void * Data);
static u8 Max9972_Debug(void * Data);
static u8 Driver_Board_Firmware(void * Data);
static u8 DDR_Test(void * Data);
static u8 DDR_Test_Status(void * Data);


/*
  ** Static Global Variable
*/
static u8 Dps_Cfg_Flag   = 0x0;
static u8 FPGA_Cfg1_Flag = 0x00;
static u8 FPGA_Cfg2_Flag = 0x00;


/*
  ** Function Name        : Set_Dps_Cfg_Flag
  ** Function Description : Set Dps Config Flag
  ** Function Parameter   : Void
  ** Function Return      : SET_SUCCESS         : Always
  ** Notes				  : None
*/
u8 Set_Dps_Cfg_Flag(void)
{
	Dps_Cfg_Flag = 0x01;
	return SET_SUCCESS;
}


/*
  ** Function Name        : Get_Dps_Cfg_Flag
  ** Function Description : Get Dps Config Flag
  ** Function Parameter   : Void
  ** Function Return      : u8			 		: Dps_Cfg_Flag Value
  ** Notes				  : None
*/
u8 Get_Dps_Cfg_Flag(void)
{
	return Dps_Cfg_Flag;
}


/*
  ** Function Name        : Clear_Dps_Cfg_Flag
  ** Function Description : Clear Dps Config Flag
  ** Function Parameter   : Void
  ** Function Return      : CLEAR_SUCCESS       : Always
  ** Notes				  : None
*/
u8 Clear_Dps_Cfg_Flag(void)
{
	Dps_Cfg_Flag = 0x00;
	return CLEAR_SUCCESS;
}


/*
  ** Function Name        : Set_FPGA_Cfg1_Flag
  ** Function Description : Set FPGA Config1 Flag
  ** Function Parameter   : Void
  ** Function Return      : SET_SUCCESS         : Always
  ** Notes				  : None
*/
u8 Set_FPGA_Cfg1_Flag(void)
{
	FPGA_Cfg1_Flag = 0x01;
	return SET_SUCCESS;
}


/*
  ** Function Name        : Get_FPGA_Cfg1_Flag
  ** Function Description : Get FPGA Config1 Flag
  ** Function Parameter   : Void
  ** Function Return      : u8			 		: FPGA_Cfg1_Flag Value
  ** Notes				  : None
*/
u8 Get_FPGA_Cfg1_Flag(void)
{
	return FPGA_Cfg1_Flag;
}


/*
  ** Function Name        : Clear_FPGA_Cfg1_Flag
  ** Function Description : Clear FPGA Config1 Flag
  ** Function Parameter   : Void
  ** Function Return      : CLEAR_SUCCESS       : Always
  ** Notes				  : None
*/
u8 Clear_FPGA_Cfg1_Flag(void)
{
	FPGA_Cfg1_Flag = 0x00;
	return CLEAR_SUCCESS;
}


/*
  ** Function Name        : Set_FPGA_Cfg2_Flag
  ** Function Description : Set FPGA Config2 Flag
  ** Function Parameter   : Void
  ** Function Return      : SET_SUCCESS         : Always
  ** Notes				  : None
*/
u8 Set_FPGA_Cfg2_Flag(void)
{
	FPGA_Cfg2_Flag = 0x01;
	return SET_SUCCESS;
}


/*
  ** Function Name        : Get_FPGA_Cfg2_Flag
  ** Function Description : Get FPGA Config2 Flag
  ** Function Parameter   : Void
  ** Function Return      : u8			 		: FPGA_Cfg2_Flag Value
  ** Notes				  : None
*/
u8 Get_FPGA_Cfg2_Flag(void)
{
	return FPGA_Cfg2_Flag;
}


/*
  ** Function Name        : Clear_FPGA_Cfg2_Flag
  ** Function Description : Clear FPGA Config2 Flag
  ** Function Parameter   : Void
  ** Function Return      : CLEAR_SUCCESS       : Always
  ** Notes				  : None
*/
u8 Clear_FPGA_Cfg2_Flag(void)
{
	FPGA_Cfg2_Flag = 0x00;
	return CLEAR_SUCCESS;
}


/*
  ** Function Name        : Data_Operation
  ** Function Description : Operation Tcp Server Receive Data
  ** Function Parameter   : Data                : Point Receive Data Pointer
  ** Function Return      : OPER_FAILED 		: Operation Failed
  **                        OPER_SUCCESS	    : Operation Success
  ** Notes				  : None
*/
u8 Data_Operation(void * Data)
{
	/* Check Parameter (Data) */
	if (NULL == Data) {
		debug("The Data Point Is NULL In %s Files,%d Line\n",__FILE__,__LINE__);
		return OPER_FAILED;
	}

	static Frame * temp_data = NULL;
	static u8 status = 0;
	temp_data = (Frame *)Data;
	switch (temp_data->com) {
	    /* Beep Control Order */
		case R_BEEP_CONTROL: {
			status = Beep_Control(Data);
			if (OPER_SUCCESS != status) {
				debug("Beep Control Order Error In %s Files,%d Line\n",__FILE__,__LINE__);
			}
		}
		break;
		/* Time Synchronous Order */
		case R_TIME_SYNC: {
			status = Time_Synchronous(Data);
			if (OPER_SUCCESS != status) {
				debug("Time Synchronous Order Error In %s Files,%d Line\n",__FILE__,__LINE__);
			}
		}
		break;
		/* DPS Channel Config Order */
		case R_DPS_CONFIG: {
			status = DPS_Config(Data);
			if (OPER_SUCCESS != status) {
				debug("DPS Channel Config Order Error In %s Files,%d Line\n",__FILE__,__LINE__);
			}
		}
		break;
		/* Pattern File Order */
		case R_PATTERN: {
			status = Pattern_Handle(Data);
			if (OPER_SUCCESS != status) {
				debug("Pattern File Order Error In %s Files,%d Line\n",__FILE__,__LINE__);
			}
		}
		break;
		/* Control Command Order */
		case R_CONTROL_COM: {
			status = Control_Command(Data);
			if (OPER_SUCCESS != status) {
				debug("Control Order Error In %s Files,%d Line\n",__FILE__,__LINE__);
			}
		}
		break;
		/* Time Restart Order */
		case R_TIME_RESTART: {
			status = Timer_Restart(Data);
			if (OPER_SUCCESS != status) {
				debug("Time Restart Order Error In %s Files,%d Line\n",__FILE__,__LINE__);
			}
		}
		break;
		/* Pin Config Order */
		case R_PIN_CONFIG: {
			status = Pin_Config(Data);
			if (OPER_SUCCESS != status) {
				debug("Pin Config Order Error In %s Files,%d Line\n",__FILE__,__LINE__);
			}
		}
		break;
		/* Not Used Order */
		case R_ALARM: {

		}
		break;
		/* Sample Data Order */
		case S_SAMPLE_DATA: {
			status = S_Sample_Data(Data);
			if (OPER_SUCCESS != status) {
				debug("Sample Data Order Error In %s Files,%d Line\n",__FILE__,__LINE__);
			}
		}
		break;
		/* Not Used Order */
		case S_MAX9979_DATA: {

		}
		break;
		/* DPS Channel Status */
		case R_DPS_CH_STATUS: {
			status = DPS_Channel_Status(Data);
			if (OPER_SUCCESS != status) {
				debug("Pin Config Order Error In %s Files,%d Line\n",__FILE__,__LINE__);
			}
		}
		break;
		/* Not Used Order */
		case R_TEMP_SAMPLE_DATA: {

		}
		break;
	    /* Realtime Status */
		case S_REALTIME_STATUS: {
			status = Realtime_Status(Data);
			if (OPER_SUCCESS != status) {
				debug("Realtime Status Order Error In %s Files,%d Line\n",__FILE__,__LINE__);
			}
		}
		break;
		/* Pattern Error Informaion */
		case S_PATTERN_ERR_INFO: {
			status = Pattern_Error_Information(Data);
			if (OPER_SUCCESS != status) {
				debug("Pattern Error Information Order Error In %s Files,%d Line\n",__FILE__,__LINE__);
			}
		}
		break;
		/* Set Pattern Status */
		case R_SET_PATTERN_STS: {
			status = Set_Pattern_Status(Data);
			if (OPER_SUCCESS != status) {
				debug("Pattern Error Information Order Error In %s Files,%d Line\n",__FILE__,__LINE__);
			}
		}
		break;
		/* Driver Board Version */
		case S_DB_VERSION: {
			status = Driver_Board_Version(Data);
			if (OPER_SUCCESS != status) {
				debug("Pattern Error Information Order Error In %s Files,%d Line\n",__FILE__,__LINE__);
			}
		}
		break;
		/* Not Used Order */
		case S_DB_PATTERN_STS: {

		}
		break;
		/* Pattern Status (Debug) */
		case R_PATTERN_DSTS: {
			status = Pattern_Status_Debug(Data);
			if (OPER_SUCCESS != status) {
				debug("Pattern Status Debug Order Error In %s Files,%d Line\n",__FILE__,__LINE__);
			}
		}
		break;
		/* Pattern Status */
		case S_PATTERN_STS: {
			status = Pattern_Status(Data);
			if (OPER_SUCCESS != status) {
					debug("Pattern Status Order Error In %s Files,%d Line\n",__FILE__,__LINE__);
			}
		}
		break;
		/* Pin Config (Debug) */
		case R_PIN_DCONFIG: {
			status = Pin_Config_Debug(Data);
			if (OPER_SUCCESS != status) {
					debug("Pin Config Debug Order Error In %s Files,%d Line\n",__FILE__,__LINE__);
			}
		}
		break;
		/* Max9972 Debug */
		case R_9972_DEBUG: {
			status = Max9972_Debug(Data);
			if (OPER_SUCCESS != status) {
					debug("Pin Config Debug Order Error In %s Files,%d Line\n",__FILE__,__LINE__);
			}
		}
		break;
		/* Not Used Order */
		case R_MB_FIRMWARE: {

		}
		break;
		/* Driver Board Firmware */
		case R_DB_FIRMWARE: {
			status = Driver_Board_Firmware(Data);
			if (OPER_SUCCESS != status) {
					debug("Driver Board Firmware Order Error In %s Files,%d Line\n",__FILE__,__LINE__);
			}
		}
		break;
		/* Not Used Order */
		case S_VERSION: {

		}
		break;
		/* DDR */
		case S_DDR_TEST: {
			status = DDR_Test(Data);
			if (OPER_SUCCESS != status) {
					debug("DDR Test Order Error In %s Files,%d Line\n",__FILE__,__LINE__);
			}
		}
		break;
		case S_DDR_TEST_STS: {
			status = DDR_Test_Status(Data);
			if (OPER_SUCCESS != status) {
					debug("DDR Test Status Order Error In %s Files,%d Line\n",__FILE__,__LINE__);
			}
		}
		break;
		default : {
			status = Tcp_Nack();
			if (SEND_SUCCESS != status) {
				debug("Tcp Server Send Nack Failed In %s Files,%d Line\n",__FILE__,__LINE__);
				status = OPER_FAILED;
			}
			else {
				status = OPER_SUCCESS;
			}
		}
		break;
	}

	return status;
}


/*
  ** Function Name        : Beep_Control
  ** Function Description : Beep Control Operation
  ** Function Parameter   : Data                : Point Receive Data Pointer
  ** Function Return      : OPER_FAILED 		: Operation Failed
  **                        OPER_SUCCESS	    : Operation Success
  ** Notes				  : Static
*/
static u8 Beep_Control(void * Data)
{
	/* Check Parameter (Data) */
	if (NULL == Data) {
		return OPER_FAILED;
	}

	/* Frame End */
	Frame * temp = (Frame *)Data;
	Beep_Control_t * point = (Beep_Control_t *)temp->data;
	XGpioPs * emio = NULL;
	emio = Get_Emio_Point();

	/* Beep Disable */
	if ((BEEP_DISABLE == point->enable)) {
		/* Nothing To Do */
	}
	/* Beep Enable */
	else if (BEEP_ENABLE == point->enable) {
		/* Beep Off */
		if (BEEP_OFF == point->state) {
			Set_System_Beep(emio,OFF);
		}
		/* Beep On */
		else if (BEEP_0N == point->state) {
			Set_System_Beep(emio,ON);
		}
		/* Others . Error */
		else {
			debug("Beep Control Order Error In %s Files,%d Line\n",__FILE__,__LINE__);
			/* Tcp Server Send Nack */
			if (SEND_SUCCESS != Tcp_Nack()) {
				debug("Send Nack Failed In Beep Control In %s Files,%d Line\n",__FILE__,__LINE__);
				return OPER_FAILED;
			}
			return OPER_FAILED;
		}
	}
	/* Others . Error */
	else {
		debug("Beep Control Order Error In %s Files,%d Line\n",__FILE__,__LINE__);
		/* Tcp Server Send Nack */
		if (SEND_SUCCESS != Tcp_Nack()) {
			debug("Send Nack Failed In Beep Control In %s Files,%d Line\n",__FILE__,__LINE__);
			return OPER_FAILED;
		}
		return OPER_FAILED;
	}

	/* Tcp Server Send Ack */
	if (SEND_SUCCESS != Tcp_Ack()) {
		debug("Send Ack Failed In Beep Control In %s Files,%d Line\n",__FILE__,__LINE__);
		return OPER_FAILED;
	}

	return OPER_SUCCESS;
}


/*
  ** Function Name        : Time_Synchronous
  ** Function Description : ZYNQ Synchronous Time
  ** Function Parameter   : Data                : Point Receive Data Pointer
  ** Function Return      : OPER_FAILED 		: Operation Failed
  **                        OPER_SUCCESS	    : Operation Success
  ** Notes				  : Static
*/
static u8 Time_Synchronous(void * Data)
{
	/* Check Parameter (Data) */
	if (NULL == Data) {
		return OPER_FAILED;
	}

	/* Synchronous Time Process */
	//Frame * temp = (Frame *)Data;
	//Time_Sync_t * point = (Time_Sync_t *)temp->data;



	/* Tcp Server Send Ack */
	if (SEND_SUCCESS != Tcp_Ack()) {
		debug("Send Ack Failed In Time Synchronous In %s Files,%d Line\n",__FILE__,__LINE__);
		return OPER_FAILED;
	}

	return OPER_SUCCESS;
}


/*
  ** Function Name        : DPS_Config
  ** Function Description : DPS Channel Config Operation
  ** Function Parameter   : Data                : Point Receive Data Pointer
  ** Function Return      : OPER_FAILED 		: Operation Failed
  **                        OPER_SUCCESS	    : Operation Success
  ** Notes				  : Static
*/
static u8 DPS_Config(void * Data)
{
	/* Check Parameter (Data) */
	if (NULL == Data) {
		return OPER_FAILED;
	}

	/* DPS Channel Config */
	Frame * temp = (Frame *)Data;
	/* Copy DPS Config Data */
	u8 * point = (u8 *)temp->data;
	u8 * desaddr = (void *)DPS_CFG_DATA_ADDR;

	u32 count = 0x00;
	u32 size = sizeof(Dps_Arg);

	for (count = 0x00; count < size; count++) {
		desaddr[count] = point[count];
	}
	/* Set DPS Config Flag */
	Set_Dps_Cfg_Flag();

	/* Tcp Server Send Ack */
	if (SEND_SUCCESS != Tcp_Ack()) {
		debug("Send Ack Failed In DPS Config In %s Files,%d Line\n",__FILE__,__LINE__);
		return OPER_FAILED;
	}

	return OPER_SUCCESS;
}




/*
  ** Function Name        : Pattern_Handle
  ** Function Description : Pattern File Operation
  ** Function Parameter   : Data                : Point Receive Data Pointer
  ** Function Return      : OPER_FAILED 		: Operation Failed
  **                        OPER_SUCCESS	    : Operation Success
  ** Notes				  : Static
*/
static u8 Pattern_Handle(void * Data)
{
	static u32 Length =  0x0;
	/* Check Parameter (Data) */
	if (NULL == Data) {
		return OPER_FAILED;
	}

	Frame * temp = (Frame *)Data;
	Vector_Arg * temp_1 = (Vector_Arg *)temp->data;

	Length = (temp->length) - HEAD_SIZE - COM_SIZE - LENGTH_SIZE - 8;

	//判断HP状态
	if(!HP_STATUS)
	{
		if(MV_Vector(temp_1, Length))			//发向量
		{
			if (SEND_SUCCESS != Tcp_Nack()) {
				debug("Send Nack Failed In Beep Control In %s Files,%d Line\n",__FILE__,__LINE__);
				return OPER_FAILED;
			}
			return OPER_FAILED;
		}
	}
	/* Pattern File */
/* File CRC */
#if CHECK_CRC
	static u32 crc32 = 0;
	static u32 crc_recv = 0;
	static u32 Length = 0;

	Frame * temp = (Frame *)Data;
	Vector_Arg * temp_1 = (Vector_Arg *)temp->data;

	Length =  temp->length - HEAD_SIZE - COM_SIZE - LENGTH_SIZE - 8;

	if (0x00000000 == temp_1->lseek) {
		crc32 = 0xFFFFFFFF;
	}
	else {

	}

	if (0xFFFFFFFF == temp_1->lseek) {
		crc_recv = *(u32 *)&temp_1->Data[Length - 4];
		if (crc_recv == crc32) {
			if (SEND_SUCCESS != Tcp_Ack()) {
				debug("Send Ack Failed In DPS Config In %s Files,%d Line\n",__FILE__,__LINE__);
				return OPER_FAILED;
			}
//			debug("Pattern Crc32 Check Success In %s Files,%d Line\n",__FILE__,__LINE__);
		}
		else {
			if (SEND_SUCCESS != Tcp_Nack()) {
				debug("Send Nack Failed In DPS Config In %s Files,%d Line\n",__FILE__,__LINE__);
				return OPER_FAILED;
			}
//			debug("Pattern Crc32 Check Error In %s Files,%d Line\n",__FILE__,__LINE__);
		}
	}
	else {
		crc32 = Get_Crc32_Val(crc32,temp_1->Data,Length);
		crc_recv = *(u32 *)&temp_1->Data[Length];
		if (crc_recv == crc32) {
			if (SEND_SUCCESS != Tcp_Ack()) {
				debug("Send Ack Failed In DPS Config In %s Files,%d Line\n",__FILE__,__LINE__);
				return OPER_FAILED;
			}
		}
		else {
			if (SEND_SUCCESS != Tcp_Nack()) {
				debug("Send Nack Failed In DPS Config In %s Files,%d Line\n",__FILE__,__LINE__);
				return OPER_FAILED;
			}
		}
	}
#endif

	return OPER_SUCCESS;
}


/*
  ** Function Name        : Control_Command
  ** Function Description : Control Command Operation
  ** Function Parameter   : Data                : Point Receive Data Pointer
  ** Function Return      : OPER_FAILED 		: Operation
  ** Failed
  **                        OPER_SUCCESS	    : Operation Success
  ** Notes				  : Static
*/
static u8 Control_Command(void * Data)
{
	/* Check Parameter (Data) */
	if (NULL == Data) {
		return OPER_FAILED;
	}

	/* Control Command */
	Sample_Data * samp_data = (Sample_Data *)SAMPLE_DATA_ADD;
	/* Get Control Command */
	Frame * temp = (Frame *)Data;
	Sample_Data * point     = (Sample_Data *)temp->data;
	u8 * point1 = (u8 *)temp->data;
	u8 * desdaddr = (void *)AGING_CTL_ADDR;

	u32 count = 0x00;
	u32 size = sizeof(Sample_Data);

	for (count = 0x00; count < size; count++) {
		desdaddr[count] = point1[count];
	}

	samp_data->AgeStatus = point->AgeStatus;
	/* Set Systrm State */
	switch (point->AgeStatus) {
		case AGING_DO:
			samp_data->AgeStatus = point->AgeStatus;
			if (SET_SUCCESS != System_State_Set_Running()) {
				debug("Set System Running State Error In %s Files,%d Line\n",__FILE__,__LINE__);
			}
		break;
		case AGING_PAUSE:
			samp_data->AgeStatus = point->AgeStatus;
			if (SET_SUCCESS != System_State_Set_Stop()) {
				debug("Set System Stop State Error In %s Files,%d Line\n",__FILE__,__LINE__);
			}
		break;
		case AGING_CTE:
			samp_data->AgeStatus = AGING_DO;
			if (SET_SUCCESS != System_State_Set_Running()) {
				debug("Set System Running State Error In %s Files,%d Line\n",__FILE__,__LINE__);
			}
		break;
		case AGING_CPL:
			if (SET_SUCCESS != System_State_Set_Stop()) {
				debug("Set System Stop State Error In %s Files,%d Line\n",__FILE__,__LINE__);
			}
		break;
		case AGING_STOP:
			samp_data->AgeStatus = point->AgeStatus;
			if (SET_SUCCESS != System_State_Set_Stop()) {
				debug("Set System Stop State Error In %s Files,%d Line\n",__FILE__,__LINE__);
			}
		break;
		default:

		break;
	}

	/* Clear System Error Information */

	/* Set Aging Timer */


	/* Clear  Pattren Record */
	Pattern_Running_Sts_t * pat_point = (Pattern_Running_Sts_t *)PAT_R_STS_ADDR;
	pat_point->pat_r_sts = 0xFF;
	pat_point->pat_r_c_pos = 0x00;

#if 0
	Sample_Data_t * samp_data = (Sample_Data_t *)SAMPLE_DATA_ADD;

	/* Control */
	samp_data->aging_state = point->aging_state;
	if (0x03 == samp_data->aging_state) {
		samp_data->aging_state = 0x01;
	}
#endif

	/* Tcp Server Send Ack */
	if (SEND_SUCCESS != Tcp_Ack()) {
		debug("Send Ack Failed In Control Command In %s Files,%d Line\n",__FILE__,__LINE__);
		return OPER_FAILED;
	}
	/* Tcp Server Send Data */
	/* Control State */
	u8 con_sts = 0x00;
	if (SEND_SUCCESS != Tcp_Server_Send((const char *)&con_sts,sizeof(con_sts))) {
		debug("Send Control Command Failed In %s Files,%d Line\n",__FILE__,__LINE__);
		return OPER_FAILED;
	}

	return OPER_SUCCESS;
}


/*
  ** Function Name        : Timer_Restart
  ** Function Description : Patern Status Operation
  ** Function Parameter   : Void
  ** Function Return      : OPER_FAILED 		: Operation Failed
  **                        OPER_SUCCESS	    : Operation Success
  ** Notes				  : Static
*/
static u8 Timer_Restart(void * Data)
{
	/* Check Parameter (Data) */
	if (NULL == Data) {
		return OPER_FAILED;
	}

	/* Timer Restart */
	Frame * temp = (Frame *)Data;
	Retime_Enable_t * point = (Retime_Enable_t *)temp->data;
	Sample_Data * samp_data = (Sample_Data *)SAMPLE_DATA_ADD;
	/* Clear Aging Timer */
	if	(point->clr_timer) {
		samp_data->AgeTime = 0x00;
	}
	/* Nothing To Do */
	else {

	}

	/* Tcp Server Send Ack */
	if (SEND_SUCCESS != Tcp_Ack()) {
		debug("Send Ack Failed In Timer Restart In %s Files,%d Line\n",__FILE__,__LINE__);
		return OPER_FAILED;
	}

	return OPER_SUCCESS;
}


/*
  ** Function Name        : Pin_Config
  ** Function Description : Pin Config Operation
  ** Function Parameter   : Data                : Point Receive Data Pointer
  ** Function Return      : OPER_FAILED 		: Operation Failed
  **                        OPER_SUCCESS	    : Operation Success
  ** Notes				  : Static
*/
static u8 Pin_Config(void * Data)
{
	/* Check Parameter (Data) */
	if (NULL == Data) {
		return OPER_FAILED;
	}

	/* Pin Config */
	Frame * temp = (Frame *)Data;
	/* Copy FPGA Config1 Data */
	u8 * point = (u8 *)temp->data;
	u8 * desdaddr = (void *)FPGA_CFG1_DATA_ADDR;

	u32 count = 0x00;
	u32 size = sizeof(Dri_Arg);

	for (count = 0x00; count < size; count++) {
		desdaddr[count] = point[count];
	}
	/* Set FPGA Config1 Flag */
	Set_FPGA_Cfg1_Flag();

	/* Tcp Server Send Ack */
	if (SEND_SUCCESS != Tcp_Ack()) {
		debug("Send Ack Failed In Pin Config In %s Files,%d Line\n",__FILE__,__LINE__);
		return OPER_FAILED;
	}

	return OPER_SUCCESS;
}


/*
  ** Function Name        : Sample_Data
  ** Function Description : Sample Data Operation
  ** Function Parameter   : Void
  ** Function Return      : OPER_FAILED 		: Operation Failed
  **                        OPER_SUCCESS	    : Operation Success
  ** Notes				  : Static
*/
static u8 S_Sample_Data(void * Data)
{
	/* Check Parameter (Data) */
	if (NULL == Data) {
		return OPER_FAILED;
	}

	/* Pin Config */
	/* Tcp Server Send Sample Data */
	Sample_Data * samp_data = (Sample_Data *)SAMPLE_DATA_ADD;

	debug("Send %d\n", samp_data->AgeStatus);


	/* Tcp Server Send Ack */
	if (SEND_SUCCESS != Tcp_Ack()) {
		debug("Send Ack Failed In Realtime Status In %s Files,%d Line\n",__FILE__,__LINE__);
		return OPER_FAILED;
	}
	/* Tcp Server Send Data*/
	if (SEND_SUCCESS != Tcp_Server_Send((const char *)samp_data,sizeof(Sample_Data))) {
		debug("Send Realtime Status Failed In %s Files,%d Line\n",__FILE__,__LINE__);
		return OPER_FAILED;
	}

	return OPER_SUCCESS;
}


/*
  ** Function Name        : DPS_Channel_Status
  ** Function Description : Control DPS Channel Status Operation
  ** Function Parameter   : Data                : Point Receive Data Pointer
  **                        Length				: Receive Data Length
  ** Function Return      : OPER_FAILED 		: Operation Failed
  **                        OPER_SUCCESS	    : Operation Success
  ** Notes				  : Static
*/
static u8 DPS_Channel_Status(void * Data)
{
	/* Check Parameter (Data) */
	if (NULL == Data) {
		return OPER_FAILED;
	}

	/* DPS Channel Status */
//	Frame * temp = (Frame *)Data;
//	DPS_Channel_Sts_t * point = (DPS_Channel_Sts_t *)temp->data;


	/* Tcp Server Send Ack */
	if (SEND_SUCCESS != Tcp_Ack()) {
		debug("Send Ack Failed In DPS Channel Status In %s Files,%d Line\n",__FILE__,__LINE__);
		return OPER_FAILED;
	}

	return OPER_SUCCESS;
}


/*
  ** Function Name        : Realtime_Status
  ** Function Description : System Realtime Status Operation
  ** Function Parameter   : Void
  ** Function Return      : OPER_FAILED 		: Operation Failed
  **                        OPER_SUCCESS	    : Operation Success
  ** Notes				  : Static
*/
static u8 Realtime_Status(void * Data)
{
	/* Check Parameter (Data) */
	if (NULL == Data) {
		return OPER_FAILED;
	}

	/* Tcp Server Send Pattern Status */
	Vec_Err_Count * point = (Vec_Err_Count *)PAT_ERR_INFO_ADDR;

	/* Tcp Server Send Ack */
	if (SEND_SUCCESS != Tcp_Ack()) {
		debug("Send Ack Failed In Realtime Status In %s Files,%d Line\n",__FILE__,__LINE__);
		return OPER_FAILED;
	}

	/* Tcp Server Send Data */
	if (SEND_SUCCESS != Tcp_Server_Send((const char *)point,sizeof(Vec_Err_Count))) {
		debug("Send Realtime Status Failed In %s Files,%d Line\n",__FILE__,__LINE__);
		return OPER_FAILED;
	}

	return OPER_SUCCESS;
}


/*
  ** Function Name        : Pattern_Error_Information
  ** Function Description : Pattern Error Information Operation
  ** Function Parameter   : Void
  ** Function Return      : OPER_FAILED 		: Operation Failed
  **                        OPER_SUCCESS	    : Operation Success
  ** Notes				  : Static
*/
static u8 Pattern_Error_Information(void * Data)
{
	/* Check Parameter (Data) */
	if (NULL == Data) {
		return OPER_FAILED;
	}

	BackIsp_Info * point = (BackIsp_Info *)PAT_C_INFO_ADDR;

	/* Tcp Server Send Ack */
	if (SEND_SUCCESS != Tcp_Ack()) {
		debug("Send Ack Failed In Pattern Error Information In %s Files,%d Line\n",__FILE__,__LINE__);
		return OPER_FAILED;
	}

	/* Tcp Server Send Data */
	if (SEND_SUCCESS != Tcp_Server_Send((const char *)point,sizeof(BackIsp_Info))) {
		debug("Send Realtime Status Failed In %s Files,%d Line\n",__FILE__,__LINE__);
		return OPER_FAILED;
	}

	/* Tcp Server Send Pattern Status */
	return OPER_SUCCESS;
}


/*
  ** Function Name        : Set_Pattern_Status
  ** Function Description : Set Pattern Status Operation
  ** Function Parameter   : Data                : Point Receive Data Pointer
  **                        Length				: Receive Data Length
  ** Function Return      : OPER_FAILED 		: Operation Failed
  **                        OPER_SUCCESS	    : Operation Success
  ** Notes				  : Static
*/
static u8 Set_Pattern_Status(void * Data)
{

	/* Check Parameter (Data) */
	if (NULL == Data) {
		return OPER_FAILED;
	}

	/* Set_Pattern_Status */
	u8  i = 0x0;
	u32 Rdata = 0x0;
	u8 status = 0x0;

	Frame * temp = (Frame *)Data;
	Pat_Set_Sts_t * setptr = (Pat_Set_Sts_t *)temp->data;


	for(i = 0; i < DRIV_BOARD_NUM; i++)
	{
		if(0x8 == setptr->Run_state)
		{
			Rdata = 0x0;
			if(DDR_ROpt_Arg(&(fpga_obj.Driver[i].Reg), setptr->StartAddr, setptr->LineNum))
				status |= 0x1 << i;
		}
	}

	for(i = 0; i < DRIV_BOARD_NUM; i++)
	{
		if(DDR_ROpt(&(fpga_obj.Driver[i].Reg), FIFOLEN, &Rdata))
		{
			status |= 0x1 << i;
		}
		else
		{
			if(0x0 == Rdata)
				status |= 0x1 << i;
		}
	}

	//触发信号
	Set_pin_value(SYS_TRIG, 1);
	usleep(100000);
	Set_pin_value(SYS_TRIG, 0);



	/* Tcp Server Send Ack */
	if (SEND_SUCCESS != Tcp_Ack()) {
		debug("Send Ack Failed In Set Pattern Status In %s Files,%d Line\n",__FILE__,__LINE__);
		return OPER_FAILED;
	}

	if (SEND_SUCCESS != Tcp_Server_Send((const char *)&status,1)) {
		debug("Send Set Pattern Status FailedI In %s Files,%d Line\n",__FILE__,__LINE__);
		return OPER_FAILED;
	}

	return OPER_SUCCESS;
}


/*
  ** Function Name        : Deiver_Board_Version
  ** Function Description : Driver Operation
  ** Function Parameter   : Void
  ** Function Return      : OPER_FAILED 		: Operation Failed
  **                        OPER_SUCCESS	    : Operation Success
  ** Notes				  : Static
*/
static u8 Driver_Board_Version(void * Data)
{
	/* Check Parameter (Data) */
	if (NULL == Data) {
		return OPER_FAILED;
	}

	/* Tcp Server Send Driver Board Version */


	/* Tcp Server Send Ack */
	if (SEND_SUCCESS != Tcp_Ack()) {
		debug("Send Ack Failed In Driver Board Version In %s Files,%d Line\n",__FILE__,__LINE__);
		return OPER_FAILED;
	}

	return OPER_SUCCESS;
}


/*
  ** Function Name        : Pattern_Status_Debug
  ** Function Description : Pattern Status Debug Operation
  ** Function Parameter   : Void
  ** Function Return      : OPER_FAILED 		: Operation Failed
  **                        OPER_SUCCESS	    : Operation Success
  ** Notes				  : Static
*/
static u8 Pattern_Status_Debug(void * Data)
{
	/* Check Parameter (Data) */
	if (NULL == Data) {
		return OPER_FAILED;
	}

	/* Set Pattern Status Debug */


	/* Tcp Server Send Ack */
	if(SEND_SUCCESS != Tcp_Ack()) {
		debug("Send Ack Failed In Pattern Status Debug In %s Files,%d Line\n",__FILE__,__LINE__);
		return OPER_FAILED;
	}

	return OPER_SUCCESS;
}


/*
  ** Function Name        : Pattern_Status
  ** Function Description : Pattern Status Operation
  ** Function Parameter   : Void
  ** Function Return      : OPER_FAILED 		: Operation Failed
  **                        OPER_SUCCESS	    : Operation Success
  ** Notes				  : Static
*/
static u8 Pattern_Status(void * Data)
{
	/* Check Parameter (Data) */
	if (NULL == Data) {
		return OPER_FAILED;
	}

	/* Tcp Server Send Pattern Status */
	Pattern_Running_Sts_t * point = (Pattern_Running_Sts_t *)PAT_R_STS_ADDR;

	/* Tcp Server Send Ack */
	if(SEND_SUCCESS != Tcp_Ack()) {
		debug("Send Ack Failed In Pattern Status In %s Files,%d Line\n",__FILE__,__LINE__);
		return OPER_FAILED;
	}

	if (SEND_SUCCESS != Tcp_Server_Send((const char *)point,\
			sizeof(Pattern_Running_Sts_t))) {
		debug("Send Pattern Status Failed In %s Files,%d Line\n",__FILE__,__LINE__);
		return OPER_FAILED;
	}

	return OPER_SUCCESS;
}


/*
  ** Function Name        : Pin_Config_Debug
  ** Function Description : Pin Config Debug Operation
  ** Function Parameter   : Data                : Point Receive Data Pointer
  **                        Length				: Receive Data Length
  ** Function Return      : OPER_FAILED 		: Operation Failed
  **                        OPER_SUCCESS	    : Operation Success
  ** Notes				  : Static
*/
static u8 Pin_Config_Debug(void * Data)
{
	/* Check Parameter (Data) */
	if (NULL == Data) {
		return OPER_FAILED;
	}

	/* Pin Config Debug */
	Frame * temp = (Frame *)Data;
	/* Copy FPGA Config2 Data */
	u8 * point = (void *)temp->data;
	u8 * desdaddr = (void *)FPGA_CFG2_DATA_ADDR;

	u32 count = 0x00;
	u32 size = 0x00;
	size = sizeof(pin_Arg);

	for (count = 0x00; count < size; count++) {
		desdaddr[count] = point[count];
	}
	/* Set FPGA Config2 Flag */
	Set_FPGA_Cfg2_Flag();

	/* Tcp Server Send Ack */
	if (SEND_SUCCESS != Tcp_Ack()) {
		debug("Send Ack Failed In Pin Config Debug In %s Files,%d Line\n",__FILE__,__LINE__);
		return OPER_FAILED;
	}

	return OPER_SUCCESS;
}


/*
  ** Function Name        : Max9972_Debug
  ** Function Description : Max9972 Debug Operation
  ** Function Parameter   : Data                : Point Receive Data Pointer
  **                        Length				: Receive Data Length
  ** Function Return      : OPER_FAILED 		: Operation Failed
  **                        OPER_SUCCESS	    : Operation Success
  ** Notes				  : Static
*/
static u8 Max9972_Debug(void * Data)
{
	/* Check Parameter (Data) */
	if (NULL == Data) {
		return OPER_FAILED;
	}

	/* Max9972 Debug */


	/* Tcp Server Send Ack */
	if (SEND_SUCCESS != Tcp_Ack()) {
		debug("Send Ack Failed In Max9972 Debug In %s Files,%d Line\n",__FILE__,__LINE__);
		return OPER_FAILED;
	}

	return OPER_SUCCESS;
}


/*
  ** Function Name        : Driver_Board_Firmware
  ** Function Description : Driver Board Firmware Operation
  ** Function Parameter   : Data                : Point Receive Data Pointer
  **                        Length				: Receive Data Length
  ** Function Return      : OPER_FAILED 		: Operation Failed
  **                        OPER_SUCCESS	    : Operation Success
  ** Notes				  : Static
*/
static u8 Driver_Board_Firmware(void * Data)
{
	/* Check Parameter (Data) */
	if (NULL == Data) {
		return OPER_FAILED;
	}

	/* Driver Board Firmware */


	/* Tcp Server Send Ack */
	if (SEND_SUCCESS != Tcp_Ack()) {
		debug("Send Ack Failed In Driver Board Firmware In %s Files,%d Line\n",__FILE__,__LINE__);
		return OPER_FAILED;
	}

	return OPER_SUCCESS;
}


/*
  ** Function Name        : DDR_Test
  ** Function Description : DDR Test Operation
  ** Function Parameter   : Data                : Point Receive Data Pointer
  **                        Length				: Receive Data Length
  ** Function Return      : OPER_FAILED 		: Operation Failed
  **                        OPER_SUCCESS	    : Operation Success
  ** Notes				  : Static
*/
static u8 DDR_Test(void * Data)
{
	/* Check Parameter (Data) */
	if (NULL == Data) {
		return OPER_FAILED;
	}

	/* DDR Test */


	/* Tcp Server Send Ack */
	if (SEND_SUCCESS != Tcp_Ack()) {
		debug("Send Ack Failed In DDR Test In %s Files,%d Line\n",__FILE__,__LINE__);
		return OPER_FAILED;
	}

	return OPER_SUCCESS;
}


/*
  ** Function Name        : DDR_Test_Status
  ** Function Description : DDR Test Operation
  ** Function Parameter   : Data                : Point Receive Data Pointer
  **                        Length				: Receive Data Length
  ** Function Return      : OPER_FAILED 		: Operation Failed
  **                        OPER_SUCCESS	    : Operation Success
  ** Notes				  : Static
*/
static u8 DDR_Test_Status(void * Data)
{
	/* Check Parameter (Data) */
	if (NULL == Data) {
		return OPER_FAILED;
	}

	/* DDR Test Status */


	/* Tcp Server Send Ack */
	if (SEND_SUCCESS != Tcp_Ack()) {
		debug("Send Ack Failed In DDR Test Status In %s Files,%d Line\n",__FILE__,__LINE__);
		return OPER_FAILED;
	}

	return OPER_SUCCESS;
}


/*
  ** (C) COPYRIGHT ChengDuHangke END OF FILE
*/
