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
		SPI_Write_2Byte(1,i,0x66);//40%--0x66
	}
	for(i=0x23;i<=0x27;i++)
	{
		SPI_Write_2Byte(1,i,0xAA);//66.66%--0xAA
	}
	for(i=0x28;i<=0x2C;i++)
	{
		SPI_Write_2Byte(1,i,0xFF);//100%--0xFF
	}
	for(i=0x2D;i<=0x30;i++)
	{
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
void Led_Tail_Cebiao_Open(void)//侧标灯
{
	char i;
	for(i=0x1F;i<=0x2C;i++)
	{
		SPI_Write_2Byte(1,i,0);//100%
	}
	for(i=0x2D;i<=0x30;i++)
	{
		SPI_Write_2Byte(1,i,0xFF);//100%
	}
	SPI_Write_2Byte(1,0x37,0x00);//update
}
void Led_RT_WaterOpen(void)//转向流水开，50ms
{
	char i;
	for(i=OUT17;i>=OUT8;i-=3)
	{
		SPI_Write_2Byte(CS_U6,i+1,0xFF);//100%
		SPI_Write_2Byte(CS_U6,i,0xFF);//100%
		SPI_Write_2Byte(CS_U6,i-1,0xFF);//100%
		SPI_Write_2Byte(CS_U6,0x37,0x00);//update
		delay_ms(LED_Interval);
	}
}
void Led_RT_WaterClose(void)//转向流水关，50ms
{
	char i;
	for(i=OUT17;i>=OUT8;i-=3)
	{
		SPI_Write_2Byte(CS_U6,i+1,0);//100%
		SPI_Write_2Byte(CS_U6,i,0);//100%
		SPI_Write_2Byte(CS_U6,i-1,0);//100%
		SPI_Write_2Byte(CS_U6,0x37,0x00);//update
	}
}
void Led_Tail14_WaterOpen(uint8_t pwm)//位置流水开，50ms
{
	char i;
	for(i=OUT6;i>=OUT1;i--)
	{
		SPI_Write_2Byte(CS_U6,i,pwm);//32%
		SPI_Write_2Byte(CS_U6,0x37,0x00);//update
		delay_ms(LED_Interval);
	}
}
void Led_Tail14_WaterClose(uint8_t pwm)//转向流水关
{
	char i;
	for(i=OUT1;i<=OUT6;i++)
	{
		SPI_Write_2Byte(CS_U6,i,pwm);
		SPI_Write_2Byte(CS_U6,0x37,0x00);//update
		delay_ms(LED_Interval);
	}
}
void Led_Tail8_WaterOpen(uint8_t pwm)//位置流水开，50ms
{
	char i;
	for(i=OUT14;i>=OUT10;i--)
	{
		SPI_Write_2Byte(CS_U2,i,pwm);
		SPI_Write_2Byte(CS_U2,0x37,0x00);//update
		delay_ms(LED_Interval);
	}
}
void Led_Tail8_WaterClose(void)//转向流水关
{
	char i;
	for(i=OUT10;i<=OUT14;i++)
	{
		SPI_Write_2Byte(CS_U2,i,0);
		SPI_Write_2Byte(CS_U2,0x37,0x00);//update
		delay_ms(LED_Interval);
	}
}
void Led_Tail7_WaterOpen(uint8_t pwm)//位置流水开，50ms
{
	char i;
	for(i=OUT9;i>=OUT5;i--)
	{
		SPI_Write_2Byte(CS_U2,i,pwm);
		SPI_Write_2Byte(CS_U2,0x37,0x00);//update
		delay_ms(LED_Interval);
	}
}
void Led_Tail7_WaterClose(void)//转向流水关
{
	char i;
	for(i=OUT5;i<=OUT9;i++)
	{
		SPI_Write_2Byte(CS_U2,i,0);
		SPI_Write_2Byte(CS_U2,0x37,0x00);//update
		delay_ms(LED_Interval);
	}
}
void Led_Tail6_WaterOpen(uint8_t pwm)//位置流水开，50ms
{
	char i;
	for(i=OUT4;i>=OUT1;i--)
	{
		SPI_Write_2Byte(CS_U2,i,pwm);
		SPI_Write_2Byte(CS_U2,0x37,0x00);//update
		delay_ms(LED_Interval);
	}
}
void Led_Tail6_WaterClose(void)//转向流水关
{
	char i;
	for(i=OUT1;i<=OUT4;i++)
	{
		SPI_Write_2Byte(CS_U2,i,0);
		SPI_Write_2Byte(CS_U2,0x37,0x00);//update
		delay_ms(LED_Interval);
	}

}
void LED_All_Open(void)
{
	char i;
	Stop_Open();
	for(i=OUT1;i<=OUT18;i++)
	{
		SPI_Write_2Byte(CS_U2_6,i,0xFF);
	}
	for(i=0x25;i<=0x30;i++)
	{
		SPI_Write_2Byte(2,i,0);
	}
	SPI_Write_2Byte(CS_U2_6,0x37,0x00);
}
