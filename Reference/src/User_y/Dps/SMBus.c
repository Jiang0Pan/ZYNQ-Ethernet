#include "SMBus.h"
#include <malloc.h>




/***********************************************************************
	[功	       能	]SMBus总线写数据(地址数据打包发送)
	[参            数	]Wbuf:数据地址, WSize:数据字节数, SlaveAddr:IIC地址, Code:SMBus命令, iicx:IIC通道
	[返    回    值	]操作是否成功
***********************************************************************/
s32 SMBus_Write(u8 *Wbuf, u8 WSize, u8 SlaveAddr, u8 Code, IIC_Chan Chan)
{
	s32 Status = FAILURE;
	u8 *buf = (u8 *)malloc(WSize+1);
	buf[0] = Code;
	memcpy(buf+1, Wbuf, WSize);

	Status = IIC_Write(buf, WSize+1, SlaveAddr, Chan);  //发送地址加数据
	if(FAILURE == Status)
	{
		free(buf);
		return FAILURE;
	}
	free(buf);
	return SUCCESS;
}

/***********************************************************************
	[功	       能	]SMBus读取数据，先发命令再读数据
	[参            数	]Rbuf:数据地址, RSize:数据字节数, SlaveAddr:IIC地址, Code:SMBus命令, iicx:IIC通道
	[返    回    值	]操作是否成功
***********************************************************************/
s32 SMBus_Read (u8 *Rbuf, u8 RSize, u8 SlaveAddr, u8 Code, IIC_Chan Chan)
{
	s32 Status = FAILURE;

	Status = IIC_Write(&Code, 1, SlaveAddr, Chan); //发送地址加Code
	if(FAILURE == Status)
		return FAILURE;

	Status = IIC_Read(Rbuf, RSize, SlaveAddr, Chan);//读取数据
	if(FAILURE == Status)
		return FAILURE;

	return SUCCESS;
}

/***********************************************************************
	[功	       能	]SMBus发送Code
	[参            数	]SlaveAddr:IIC地址, Code:SMBus命令, iicx:IIC通道
	[返    回    值	]操作是否成功
***********************************************************************/
s32 SMBus_Code(u8 SlaveAddr, u8 Code, IIC_Chan Chan)
{
	s32 Status = FAILURE;

	Status = IIC_Write(&Code, 1, SlaveAddr, Chan);  //Code加地址
	if(FAILURE == Status)
		return FAILURE;

	return SUCCESS;
}






