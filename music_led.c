/*
 * music.c
 *
 *  Created on: 2021-1-11
 *      Author: Rick
 */
#include"main.h"
#include"PinConfig.h"
#include "SoftSpi.h"
#include "work.h"
#include "led.h"
#include "music.h"
#include "music_led.h"

extern uint32_t Time_Counter;

void OUTx_PWM(uint8_t device,uint8_t channel,uint8_t pwm)
{
	if(device==U6)
	{
		U6_SPI_Write_2Byte(channel, pwm);
		U6_SPI_Write_2Byte(0x37,0x00);//update
	}
	if(device==U8)
	{
		U8_SPI_Write_2Byte(channel, pwm);
		U8_SPI_Write_2Byte(0x37,0x00);//update
	}
}
void OUTx_Flash(uint8_t device,uint8_t channel)
{
	OUTx_PWM(device,channel,0xFF);
	delay_ms(10);
	OUTx_PWM(device,channel,0x00);
}
void All_LED_PWM(uint8_t pwm)
{
	uint8_t i;

	for(i=OUT1;i<=OUT18;i++)
	{
		U6_SPI_Write_2Byte(i, pwm);
	}

	for(i=OUT1;i<=OUT12;i++)
	{
		U8_SPI_Write_2Byte(i, pwm);
	}
	U6_SPI_Write_2Byte(0x37,0x00);//update
	U8_SPI_Write_2Byte(0x37,0x00);//update
}
void BASE_PWM(uint8_t pwm)
{
	uint8_t i;
	for(i=OUT12;i<=OUT18;i++)
	{
		U6_SPI_Write_2Byte(i, pwm);
	}
	U6_SPI_Write_2Byte(0x37,0x00);//update
}
void Gangqin_Flash(uint8_t device,uint8_t channel)
{
	OUTx_PWM(device,channel,0xFF);
	Delayms(10);
	OUTx_PWM(device,channel,0x05);
}
void SCAN(uint16_t t)
{
	uint8_t i;

	for(i=OUT12;i<=OUT18;i++)
	{
		U6_SPI_Write_2Byte(i, 0x20);
	}
	U6_SPI_Write_2Byte(0x37,0x00);//update

	for(i=OUT12;i<=OUT18;i++)
	{
		U6_SPI_Write_2Byte(i, 0x00);
		U6_SPI_Write_2Byte(0x37,0x00);//update
		Delayms(t);
	}
}

void SCAN_BACK(uint16_t t)
{
	uint8_t i;

    Delayms(t*12);
	for(i=OUT18;i>=OUT12;i--)
	{
		U6_SPI_Write_2Byte(i, 0x05);  //PWM = 0x05
		U6_SPI_Write_2Byte(0x37,0x00);//update
		Delayms(t);
	}
}

void Side_Liushui(uint16_t h)
{
	uint32_t differ;
	uint8_t status,i,t;
	for(t=0;t<h;t++)
	{
	    for(status = 0; status < (7 + 5); status++)   //ÐèÒª¾­¹ý num+length ¸ö×´Ì¬
    {
        All_LED_PWM(0x00);

        for(i = 0; i < 5; i++)  //ÓÐÊý¾ÝµÄµÆ¸²¸ÇÖ®Ç°µÄ0£¬Ã»ÓÐÊý¾ÝµÄ¼ÌÐøÎªÃð
        {
            differ = status - i;
            if((differ > 0) && (differ < 7))
            {
            	U6_SPI_Write_2Byte(OUT12 + differ, 0xFF);
            }
		}
		  U6_SPI_Write_2Byte(0x37, 0x00);  //update
		  Delayms(10);
    }
		for(status = 0; status < (7 + 5); status++)   //ÐèÒª¾­¹ý num+length ¸ö×´Ì¬
    {
         All_LED_PWM(0x00);


        for(i = 0; i < 5; i++)  //ÓÐÊý¾ÝµÄµÆ¸²¸ÇÖ®Ç°µÄ0£¬Ã»ÓÐÊý¾ÝµÄ¼ÌÐøÎªÃð
        {
            differ = status - i;
            if((differ > 0) && (differ < 7))
            {
            	U6_SPI_Write_2Byte(OUT18 - differ, 0xFF);
            }
		}
			U6_SPI_Write_2Byte(0x37, 0x00);  //update
			//U8_SPI_Write_2Byte(0x37, 0x00);  //update
			Delayms(10);
    	}
	}
}
void LIUSHUI(void)
{
	uint32_t differ;
	uint8_t status,i,t;
	for(t=0;t<6;t++)
	{
	    for(status = 0; status < (7 + 4); status++)   //ÐèÒª¾­¹ý num+length ¸ö×´Ì¬
	    {
			for(i = 0; i < 7; i++)
			{
				U6_SPI_Write_2Byte(OUT12+i, 0x00);
			}
			for(i = 0; i < 4; i++)  //ÓÐÊý¾ÝµÄµÆ¸²¸ÇÖ®Ç°µÄ0£¬Ã»ÓÐÊý¾ÝµÄ¼ÌÐøÎªÃð
			{
				differ = status - i;
				if((differ > 0) && (differ < 7))
				{
					U6_SPI_Write_2Byte(OUT12 + differ, 0xFF);
				}
			}
		  U6_SPI_Write_2Byte(0x37, 0x00);  //update
		  Delayms(10);
		}
	}
}

void All_STOP_PWM(uint8_t pwm)
{
	uint8_t i;
	for(i=OUT1;i<=OUT12;i++)
	{
		U8_SPI_Write_2Byte(i, pwm);
	}
	U8_SPI_Write_2Byte(0x37,0x00);//update
}
void Side_flash(uint8_t pwm) //
{
	uint8_t i;
	for(i=OUT1;i<=OUT3;i++)
	{
		U6_SPI_Write_2Byte(i, pwm);
	}

	for(i=OUT8;i<=OUT11;i++)
	{
		U6_SPI_Write_2Byte(i, pwm);
	}

	U6_SPI_Write_2Byte(0x37,0x00);//update
	Delayms(10);

	for(i=OUT1;i<=OUT3;i++)
	{
		U6_SPI_Write_2Byte(i, 0x00);
	}
	for(i=OUT8;i<=OUT11;i++)
	{
		U6_SPI_Write_2Byte(i, 0x00);

	}
	U6_SPI_Write_2Byte(0x37,0x00);//update
}

void Piano_flash(uint8_t device,uint8_t ch1)
{
	if(device==U6)
	{
		U6_SPI_Write_2Byte(ch1, 0xFF);
		U6_SPI_Write_2Byte(0x37,0x00);//update
		Delayms(10);
		U6_SPI_Write_2Byte(ch1, 0x00);
		U6_SPI_Write_2Byte(0x37,0x00);//update
	}
	if(device==U8)
	{
		U8_SPI_Write_2Byte(ch1, 0xFF);
		U8_SPI_Write_2Byte(0x37,0x00);//update
		Delayms(10);
		U8_SPI_Write_2Byte(ch1, 0x00);
		U8_SPI_Write_2Byte(0x37,0x00);//update
	}
}

void End(void)
{
}

void Step1(void)
{
	uint8_t i;
	for(i=OUT12;i<=OUT18;i++)
	{
		U6_SPI_Write_2Byte(i, 0xFF);
	}
	U6_SPI_Write_2Byte(0x37,0x00);//update

	Delayms(10);

	for(i=OUT12;i<=OUT18;i++)
	{
		U6_SPI_Write_2Byte(i, 0x00);
	}
	U6_SPI_Write_2Byte(0x37,0x00);//update
}
