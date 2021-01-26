#ifndef _SMBUS_H
#define _SMBUS_H


#include "iic.h"


s32 SMBus_Write(u8 *Wbuf, u8 WSize, u8 SlaveAddr, u8 Code, IIC_Chan Chan);

s32 SMBus_Read (u8 *Rbuf, u8 RSize, u8 SlaveAddr, u8 Code, IIC_Chan Chan);

s32 SMBus_Code(u8 SlaveAddr, u8 Code, IIC_Chan Chan);





#endif
