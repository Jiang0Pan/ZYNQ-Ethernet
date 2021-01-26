/*
  ** @file           : return_val.h
  ** @brief          : Return Val Header File
  **
  ** @attention
  **
  ** Copyright (c) 2020 ChengDuHangke.
  ** All rights reserved.
  **
  ** This software is licensed by ChengDuHangke under Ultimate Liberty license
  **
*/


#ifndef RETURN_VAL_H_
#define RETURN_VAL_H_


/*
  ** Typedef Enum
*/
/* Init Status */
typedef enum INIT_Val {
	INIT_SUCCESS 		= 0x00,
	INIT_FAILED 		= 0x01,
}Init_val;
/* Config Status */
typedef enum CONFIG_Val {
	CONFIG_SUCCESS 		= 0x00,
	CONFIG_FAILED 		= 0x01,
}Config_val;
/* Set Status */
typedef enum SET_Val {
	SET_SUCCESS 		= 0x00,
	SET_FAILED 			= 0x01,
}Set_val;
/* Get Status */
typedef enum GET_Val {
	GET_SUCCESS 		= 0x00,
	GET_FAILED 			= 0x01,
}Get_val;
/* Create Status */
typedef enum CREATE_Val {
	CREATE_FAILED 		= 0x01,
	CREATE_SUCCESS 		= 0x00,
}Create_val;
/* Destroy Status */
typedef enum DESTROY_Val {
	DESTROY_FAILED      = 0x01,
	DESTROY_SUCCESS     = 0X00,
}Destroy_val;
/* Send Status */
typedef enum SEND_Val {
	SEND_FAILED         = 0x01,
	SEND_SUCCESS        = 0x00,
}Send_val;
/* Recv Status */
typedef enum RECV_Val {
	RECV_FAILED         = 0x01,
	RECV_SUCCESS        = 0x00,
}Recv_val;
/* Write Status */
typedef enum WRITE_Val {
	WRITE_FAILED        = 0x01,
	WRITE_SUCCESS       = 0x00,
}Write_val;
/* Read Status */
typedef enum READ_Val {
	READ_SUCCESS        = 0x00,
	READ_FAILED         = 0x01,
}Read_val;
/* Insert Status */
typedef enum INSERT_Val {
	INSERT_FAILED       = 0x01,
	INSERT_SUCCESS      = 0x00,
}Insert_val;
/* Delete Status */
typedef enum DELETE_Val {
	DELETE_FAILED       = 0x01,
	DELETE_SUCCESS      = 0x00,
}Delete_val;
/* Verify Status */
typedef enum VERITF_Val {
	VERIFY_FAILED       = 0x01,
	VERIFY_SUCCESS      = 0x00,
}Verify_val;
/* Operation Status */
typedef enum OPER_Val {
	OPER_FAILED         = 0x01,
	OPER_SUCCESS        = 0x00,
}Oper_val;
/* Clear Status */
typedef enum Clear_Val {
	CLEAR_FAILED         = 0x01,
    CLEAR_SUCCESS        = 0x00,
}Clear_val;


#endif /* RETURN_VAL_H_ */


/*
  ** (C) COPYRIGHT ChengDuHangke END OF FILE
*/
