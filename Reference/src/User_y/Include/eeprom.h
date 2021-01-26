#ifndef _EEPROM_H

#include "Hw_ver.h"



/////////////////////////////////////////////////////////////////////
//���д����
void CLEAR_WP(_Output_ * IO, u8 SlaveAddr, IIC_Chan i2cX);
//����д����
void ADD_WP  (_Output_ * IO, u8 SlaveAddr, IIC_Chan i2cX);
//�жϵ�ַ�Ƿ�Ϸ�
u8 Addr_Legal(u16 Addr);

//eeprom��ȡһ���ֽ�
s32 EEPROM_ReadByte(u16 Addr, u8 *Byte, u8 SlaveAddr, IIC_Chan i2cX);

//eepromдһ���ֽ�
s32 EEPROM_WriteByte(u16 Addr, u8 Byte, u8 SlaveAddr, IIC_Chan i2cX);

//eeprom��ȡn���ֽ�(n < 64)
s32 EEPROM_ReadBuff(u16 Addr, u8 *Buff, u8 Size, u8 SlaveAddr, IIC_Chan i2cX);

//eepromдn���ֽ�(n < 64)
s32 EEPROM_WriteBuff(u16 Addr, u8 *Buff, u8 Size, u8 SlaveAddr, IIC_Chan i2cX);

//����һƬ����
s32 EEPROM_EraseBuff(u16 Addr, u8 Size, u8 SlaveAddr, IIC_Chan i2cX);

u8 CRC8(u8 *ptr, u8 len);

























#endif













































