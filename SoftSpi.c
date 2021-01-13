/*
 * SoftSpi.c
 *
 *  Created on: 2020-10-6
 *      Author: Rick
 */
#include<KF8A200GQS.h>
#include "PinConfig.h"
#include "SoftSpi.h"
#include "Work.h"
#define InitBright 0
void spi_init(void)
{
	TR92 =1;
	TR91 =0;
	TR03 =0;
	TR04 =0;
	TR62 =0;
	APFCTL9 =0x06;

	SSCI2EN=0;				//关闭SPI模块，初始化完之后再打开

	SSCI2CTL0=0X01;			//SPI 主控模式，时钟 = 工作时钟/64
	SSCI2CTL1=0X00;
	SSCI2CTL2=0X00;
	SSCI2STA=0X40;  //空闲时为低电平，在SCL下降沿发送数据

	SSCI2EN=1;

	SDB1=1;
	CS1HIGH;
	CS2HIGH;
}
void Spi_CS_High(char id)
{
	switch(id)
	{
		case 0:CS1HIGH;CS2HIGH;break;
		case 1:CS1HIGH;break;
		case 2:CS2HIGH;break;
	}
}
void Spi_CS_Low(char id)
{
	switch(id)
	{
		case 0:CS1LOW;CS2LOW;break;
		case 1:CS1LOW;break;
		case 2:CS2LOW;break;
	}
}
void SPI_Write_2Byte(unsigned char id,unsigned char addr,unsigned char dat)
{
	char i=0;
	volatile unsigned buf;
	volatile unsigned char SPI_adr, SPI_data;
	SPI_adr =addr;
	SPI_data =dat;
	Spi_CS_Low(id);
	SSCI2BUFR=SPI_adr; //将待发送的字节放入发送缓存中
	while(!SSCI2IF); //等待发送完毕后SSCIIF置位，
	SSCI2IF=0;
	buf =SSCI2BUFR;

	SSCI2BUFR=SPI_data; //将待发送的字节放入发送缓存中
	while(!SSCI2IF); //等待发送完毕后SSCIIF置位，
	SSCI2IF=0;
	buf =SSCI2BUFR;
	Spi_CS_High(id);
}
void SPI_All_Write_2Byte(unsigned char addr,unsigned char dat)
{
	char i=0;
	volatile unsigned buf;
	volatile unsigned char SPI_adr, SPI_data;
	SPI_adr =addr;
	SPI_data =dat;
	Spi_CS_Low(0);
	SSCI2BUFR=SPI_adr; //将待发送的字节放入发送缓存中
	while(!SSCI2IF); //等待发送完毕后SSCIIF置位，
	SSCI2IF=0;
	buf =SSCI2BUFR;

	SSCI2BUFR=SPI_data; //将待发送的字节放入发送缓存中
	while(!SSCI2IF); //等待发送完毕后SSCIIF置位，
	SSCI2IF=0;
	buf =SSCI2BUFR;
	Spi_CS_High(0);
}
void IS31FL3265B_Init(void)
{
	spi_init();
	Tail_One_Init();
	Tail_Two_Init();
}
void Tail_One_Init(void)
{
	char i=0;
	SPI_Write_2Byte(1,0x00,0x01);

	for(i=0x02;i<=0x13;i++)
	{
		SPI_Write_2Byte(1,i,0xFF);//SL
	}

	for(i=0x1F;i<=0x30;i++)
	{
		SPI_Write_2Byte(1,i,InitBright);//PWM
	}

	SPI_Write_2Byte(1,0x36,0x00);//update
	SPI_Write_2Byte(1,0x37,0x00);//update
	SPI_Write_2Byte(1,0x01,0x20);
}
void Tail_Two_Init(void)
{
	char i=0;
	SPI_Write_2Byte(2,0x00,0x01);

	for(i=0x02;i<=0x13;i++)
	{
		SPI_Write_2Byte(2,i,0xFF);//SL
	}

	for(i=0x1F;i<=0x30;i++)
	{
		SPI_Write_2Byte(2,i,InitBright);//PWM
	}

	SPI_Write_2Byte(2,0x36,0x00);//update
	SPI_Write_2Byte(2,0x37,0x00);//update
	SPI_Write_2Byte(2,0x01,0x20);
}
