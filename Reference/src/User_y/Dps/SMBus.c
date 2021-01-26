#include "SMBus.h"
#include <malloc.h>




/***********************************************************************
	[��	       ��	]SMBus����д����(��ַ���ݴ������)
	[��            ��	]Wbuf:���ݵ�ַ, WSize:�����ֽ���, SlaveAddr:IIC��ַ, Code:SMBus����, iicx:IICͨ��
	[��    ��    ֵ	]�����Ƿ�ɹ�
***********************************************************************/
s32 SMBus_Write(u8 *Wbuf, u8 WSize, u8 SlaveAddr, u8 Code, IIC_Chan Chan)
{
	s32 Status = FAILURE;
	u8 *buf = (u8 *)malloc(WSize+1);
	buf[0] = Code;
	memcpy(buf+1, Wbuf, WSize);

	Status = IIC_Write(buf, WSize+1, SlaveAddr, Chan);  //���͵�ַ������
	if(FAILURE == Status)
	{
		free(buf);
		return FAILURE;
	}
	free(buf);
	return SUCCESS;
}

/***********************************************************************
	[��	       ��	]SMBus��ȡ���ݣ��ȷ������ٶ�����
	[��            ��	]Rbuf:���ݵ�ַ, RSize:�����ֽ���, SlaveAddr:IIC��ַ, Code:SMBus����, iicx:IICͨ��
	[��    ��    ֵ	]�����Ƿ�ɹ�
***********************************************************************/
s32 SMBus_Read (u8 *Rbuf, u8 RSize, u8 SlaveAddr, u8 Code, IIC_Chan Chan)
{
	s32 Status = FAILURE;

	Status = IIC_Write(&Code, 1, SlaveAddr, Chan); //���͵�ַ��Code
	if(FAILURE == Status)
		return FAILURE;

	Status = IIC_Read(Rbuf, RSize, SlaveAddr, Chan);//��ȡ����
	if(FAILURE == Status)
		return FAILURE;

	return SUCCESS;
}

/***********************************************************************
	[��	       ��	]SMBus����Code
	[��            ��	]SlaveAddr:IIC��ַ, Code:SMBus����, iicx:IICͨ��
	[��    ��    ֵ	]�����Ƿ�ɹ�
***********************************************************************/
s32 SMBus_Code(u8 SlaveAddr, u8 Code, IIC_Chan Chan)
{
	s32 Status = FAILURE;

	Status = IIC_Write(&Code, 1, SlaveAddr, Chan);  //Code�ӵ�ַ
	if(FAILURE == Status)
		return FAILURE;

	return SUCCESS;
}






