/*
  ** @file           : system_state.c
  ** @brief          : System State Source File
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
#include "FreeRTOS.h"
#include "task.h"
#include "return_val.h"
#include "debug_config.h"
#include "GlobalRef.h"
#include "memory_map.h"
#include "operation.h"
#include "system_state.h"
#include "Driver.h"
#include "fpga.h"


/*
  ** Static Global Variable
*/
/* System State . Default Wait State */
static volatile u8 sys_sts = SYS_IDLE;
/* Dps Enable Flag */
static u8 dps_enable = 0x00;


/*
  ** Function Name        : System_State_Process_Task
  ** Function Description : System State Process Task
  ** Function Parameter   : p 					: Task Parameter()
  ** Function Return      : Void
  ** Notes				  : None
*/
void System_State_Process_Task(void *p)
{
	//const TickType_t x1second = pdMS_TO_TICKS(DELAY_1_SECOND);

	Sample_Data   * Sample    = (Sample_Data   *)SAMPLE_DATA_ADD;		//采样数据
	BackIsp_Info  * Ispinfo   = (BackIsp_Info  *)PAT_C_INFO_ADDR;		//回检数据
	VecRun_t      * pat_r     = (VecRun_t      *)PAT_R_STS_ADDR;		//向量运行状态
	Dps_Arg       * dps_cfg   = (Dps_Arg       *)DPS_CFG_DATA_ADDR;		//电源配置信息
	Aging_Ctl     * aging_ctl = (Aging_Ctl     *)AGING_CTL_ADDR;		//老化控制
	Vec_Err_Count * pat_err   = (Vec_Err_Count *)PAT_ERR_INFO_ADDR;		//向量出错统计

	/* Sample Data Init */
	memset((void *)Sample,    0, sizeof(Sample_Data));
	/* error mask     */
	memset((void *)Ispinfo,   0, sizeof(BackIsp_Info));
	/* Pattern Running State */
	memset((void *)pat_r,     0, sizeof(VecRun_t));
	/* dps info */
	memset((void *)dps_cfg,   0, sizeof(Dps_Arg));
	/* aging contrl */
	memset((void *)aging_ctl, 0, sizeof(Aging_Ctl));
	/* Pattern Error Information */
	memset((void *)pat_err,   0, sizeof(Vec_Err_Count));

	/* State Cutover Flag */
	u8 cutover_flag = 0x00;
	//vTaskSuspendAll Suspend All Task
	//xTaskResumeAll Suspend All Task
	/* DPS Power On Test */

	/* Sample Data */
	Sample->AgeStatus = AGING_WAIT;

	/* Pattern Running State */
	u8 state = 0x0;

	pat_r->RunSta = WAITRUN;	//等待运行

	for ( ; ;)
	{
		switch (sys_sts) {		//下位机状态
			case SYS_IDLE: {	//空闲状态
				if (Get_Dps_Cfg_Flag()) {
					/* Clear Data */
					Set_Dps_Enable_Flag();
					Sample->AgeStatus = AGING_READY;
					Sample->AgeTime = 0x00;
					Clear_Dps_Cfg_Flag();
				}
			}
			break;
			case SYS_RUNNING: {	//下位机运行状态
				if (Sample->AgeTime >= dps_cfg->AgeTime) {	//老化时间超过配置时间
					if (aging_ctl->AutoStop) {				//自动停止
						System_State_Set_Stop();
						cutover_flag = 0x01;
						Sample->AgeStatus = AGING_CPL;		//老化完成
					}
				}
				if (Get_Dps_Enable_Flag()) {
					//初始化电源
					DpsConfig(Sample);
					OpenDpsSequence(Sample);
					Clear_Dps_Enable_Flag();
				}
				if (Get_FPGA_Cfg1_Flag()) {
					pin_Conf(Sample);
					Clear_FPGA_Cfg1_Flag();
				}
				if (Get_FPGA_Cfg2_Flag()) {
					db_Conf(Sample);
					Clear_FPGA_Cfg2_Flag();
				}

				pat_r->RunSta = RUNNING;

				if (0 == Read_Vecflag(Sample))		//运行完成
				{
					memset((void *)pat_err, 0, sizeof(Vec_Err_Count));

					Read_Back_isp();
					/* Pattern Error Infotmaiont */

					pat_r->RunSta = RUNOK;
				}

				/* Sample Data */
				if (AGING_DO == Sample->AgeStatus) {		//采样
					Set_Sampl_packge(Sample);
				}
				else if (AGING_STOP == Sample->AgeStatus) {	//清除
					memset((void *)Sample,   0, sizeof(Sample_Data));
					memset((void *)pat_err,  0, sizeof(Vec_Err_Count));
				}

				/* Pattern Running State */
				if (state) {
					state = 0x00;
				}
				else {
					state = 0x01;
				}
				pat_r->RunSta   = state;
				pat_r->ErrCount = 0x01;
			}
			break;
			case SYS_STOP: {
				if (cutover_flag) {
					CloseDpsSequence(Sample);
					/* DPS Enable */
//					DPS_Disable();
					//DpsClose();
//					FPGA_Disable();
					/* DPS Sample Disable */
//					DPS_Sample_Disable();
					pat_r->RunSta = 0xff;
					Sample->AgeStatus = AGING_STOP;
				}

				if (Get_Dps_Cfg_Flag())  {
					System_State_Set_Idle();
				}
			}
			break;
			default : {

			}
			break;
		}

	}

    /* Delete Task Itself */
	vTaskDelete(NULL);
}


/*
  ** Function Name        : System_State_Set_Idle
  ** Function Description : Set System State In Idle State
  ** Function Parameter   :	Void
  ** Function Return	  :	SET_SUCCESS         : Return Always
  ** Notes				  : None
*/
u8 System_State_Set_Idle(void)
{
	sys_sts = SYS_IDLE;
	return SET_SUCCESS;
}


/*
  ** Function Name        : System_State_Set_Running
  ** Function Description : Set System State In Running State
  ** Function Parameter   :	Void
  ** Function Return	  :	SET_SUCCESS         : Return Always
  ** Notes				  : None
*/
u8 System_State_Set_Running(void)
{
	sys_sts = SYS_RUNNING;
	return SET_SUCCESS;
}


/*
  ** Function Name        : System_State_Set_Stop
  ** Function Description : Set System State In Stop State
  ** Function Parameter   :	Void
  ** Function Return	  :	SET_SUCCESS         : Return Always
  ** Notes				  : None
*/
u8 System_State_Set_Stop(void)
{
	sys_sts = SYS_STOP;
	return SET_SUCCESS;
}


/*
  ** Function Name        : Set_Dps_Enable_Flag
  ** Function Description : Set Dps Enable Flag
  ** Function Parameter   : Void
  ** Function Return      : SET_SUCCESS         : Always
  ** Notes				  : None
*/
u8 Set_Dps_Enable_Flag(void)
{
	dps_enable = 0x01;
	return SET_SUCCESS;
}


/*
  ** Function Name        : Get_Dps_Enable_Flag
  ** Function Description : Get Dps Enable Flag
  ** Function Parameter   : Void
  ** Function Return      : u8			 		: Dps_Cfg_Flag Value
  ** Notes				  : None
*/
u8 Get_Dps_Enable_Flag(void)
{
	return dps_enable;
}


/*
  ** Function Name        : Clear_Dps_Enable_Flag
  ** Function Description : Clear Dps Enable Flag
  ** Function Parameter   : Void
  ** Function Return      : CLEAR_SUCCESS       : Always
  ** Notes				  : None
*/
u8 Clear_Dps_Enable_Flag(void)
{
	dps_enable = 0x00;
	return CLEAR_SUCCESS;
}


/*
  ** (C) COPYRIGHT ChengDuHangke END OF FILE
*/


