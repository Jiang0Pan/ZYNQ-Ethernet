


#include "Cpld.h"
#include "Dps.h"
#include "unistd.h"
#include "IO.h"


//ms��ʱ
void Delayms(u16 ms)
{
	while(ms--)
		usleep(1000);
}

//cpld����
s32 Cpld_Transfer(Cpld_Xfer *Xfer, u16 *Rdata)
{
	u8  Buff[3] = {0x0};

	Reveru16(Xfer->Data);

	if(Spi_Transfer(Xfer->Bytes, Buff, 3, CPLD_SPI))
		return FAILURE;

	if(Rdata != NULL)
	{
		(*Rdata)  = (Buff[1] << 8);
		(*Rdata) |= (Buff[2] << 0);
	}

	return SUCCESS;
}

//�����ж�����ʱ��
s32 Cpld_SetShark(u8 id, u16 delayus)
{
	u16 Rdata = 0;
	Cpld_Xfer Xfer;

	if(id >= DPS_NUM)
		return FAILURE;

	memset(&Xfer, 0, sizeof(Xfer));

	Xfer.Data = delayus;
	Xfer.RW   = WOPT;
	Xfer.Addr = CHA_ERROR_DELAY + (id * 4);
	if(Cpld_Transfer(&Xfer, &Rdata))
		return FAILURE;

	return SUCCESS;
}

//���õ�����Դ�ϵ�ʱ��
s32 Cpld_SetDelay(u8 id, u16 delayms)
{
	u16 Rdata = 0;
	Cpld_Xfer Xfer;

	if(id >= DPS_NUM)
		return FAILURE;

	memset(&Xfer, 0, sizeof(Xfer));

	Xfer.Data = delayms;
	Xfer.RW   = WOPT;
	Xfer.Addr = CHA_ON_DELAY + (id * 4);
	if(Cpld_Transfer(&Xfer, &Rdata))
		return FAILURE;

	return SUCCESS;
}

//��ʼ��CPLD
s32 Cpld_Init(u8 bid)
{
	u8 i = 0;

	DpsSpi_Open(bid, DPS_CTL);

	for(i = 0; i < 10; i++)
	{
		if(Cpld_SetShark(i, SHARKDELAY))
			return FAILURE;
		if(Cpld_SetDelay(i, ONDELAY))
			return FAILURE;
	}

	DpsSpi_Close(bid);

	return SUCCESS;
}




