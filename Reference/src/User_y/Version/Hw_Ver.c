




#include "Hw_Ver.h"



/////////////////////////////////////////////////////////////////////////////////

/***********************************************************************
	[功	       能	]读取硬件版本信息HW Version: 0001 Board Type: 0001
	[参            数	]HW_info:版本信息, SlaveAddr:从机地址, Chan:通道号
	[返    回    值	]是否成功
***********************************************************************/
s32 ReadIO_Info(u8 *HW_info, struct _IIC_ * dev)
{
	if(IO_Group_Get(Group0, HW_info, dev->PCA953_SlaveAddr, dev->HWChan))
		return FAILURE;

	return SUCCESS;
}










