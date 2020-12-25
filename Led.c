/*
 * Led.c
 *
 *  Created on: 2020-10-9
 *      Author: Rick
 */
#include<KF8A200GQS.h>
#include "PinConfig.h"
#include "Work.h"
#include "Led.h"
#include "SoftSpi.h"

void Stop_Open(void)
{
	STOP=1;
}
void Stop_Close(void)
{
	STOP=0;
}
void Led_RT_AllOpen(void)
{
	char i;
	for(i=0x25;i<=0x30;i++)
	{
		SPI_Write_2Byte(2,i,255);
	}
	SPI_Write_2Byte(2,0x37,0x00);//update
}
void Led_RT_AllClose(void)
{
	char i;
	for(i=0x25;i<=0x30;i++)
	{
		SPI_Write_2Byte(2,i,0);
	}
	SPI_Write_2Byte(2,0x37,0x00);//update
}
void Led_Tail_AllOpen(void)
{
	char i;
	for(i=0x1F;i<=0x24;i++)
	{
		SPI_Write_2Byte(2,i,0xE0);//88%
	}
	SPI_Write_2Byte(2,0x37,0x00);//update
	for(i=0x1F;i<=0x22;i++)
	{
		//SPI_Write_2Byte(1,i,0xFF);//100%--0xff
		SPI_Write_2Byte(1,i,0x66);//40%--0x66
	}
	for(i=0x23;i<=0x27;i++)
	{
		SPI_Write_2Byte(1,i,0xAA);//66.66%--0xAA
	}
	for(i=0x28;i<=0x2C;i++)
	{
		//SPI_Write_2Byte(1,i,0x66);//40%--0x66
		SPI_Write_2Byte(1,i,0xFF);//100%--0xFF
	}
	for(i=0x2D;i<=0x30;i++)
	{
		//SPI_Write_2Byte(1,i,0xFF);//100%-0xFF
		SPI_Write_2Byte(1,i,0xC0);//75%-0xC0
	}
	SPI_Write_2Byte(1,0x37,0x00);//update
}
void Led_Tail_AllClose(void)
{
	char i;
	for(i=0x1F;i<=0x24;i++)
	{
		SPI_Write_2Byte(2,i,0);//0%
	}
	SPI_Write_2Byte(2,0x37,0x00);//update
	for(i=0x1F;i<=0x30;i++)
	{
		SPI_Write_2Byte(1,i,0);//0%
	}
	SPI_Write_2Byte(1,0x37,0x00);//update
}
