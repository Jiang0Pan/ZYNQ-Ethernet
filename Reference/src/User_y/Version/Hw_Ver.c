




#include "Hw_Ver.h"



/////////////////////////////////////////////////////////////////////////////////

/***********************************************************************
	[��	       ��	]��ȡӲ���汾��ϢHW Version: 0001 Board Type: 0001
	[��            ��	]HW_info:�汾��Ϣ, SlaveAddr:�ӻ���ַ, Chan:ͨ����
	[��    ��    ֵ	]�Ƿ�ɹ�
***********************************************************************/
s32 ReadIO_Info(u8 *HW_info, struct _IIC_ * dev)
{
	if(IO_Group_Get(Group0, HW_info, dev->PCA953_SlaveAddr, dev->HWChan))
		return FAILURE;

	return SUCCESS;
}










