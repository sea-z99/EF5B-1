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
    STOP = 0;
}
void Led_RT_AllOpen(void)
{
    char i;
    for(i=OUT7;i<=OUT18;i++)
    {
        SPI_Write_2Byte(2,i,0xE8);//91%
    }
    SPI_Write_2Byte(2,0x37,0x00);//update
}
void Led_RT_AllClose(void)
{
    char i;
    Timer5_Stop();
    for(i=0x25;i<=0x30;i++)
    {
        SPI_Write_2Byte(2,i,0);
    }
    SPI_Write_2Byte(2,0x37,0x00);//update
    TEST=0;
}
void Clear_RT(void)
{
    TEST=1;
    SPI_Read(CS_U6,0x15);
    SPI_Read(CS_U6,0x16);
    SPI_Read(CS_U6,0x17);
}
void Detect_RT(void)
{
    uint8_t dat1 = 0;
    uint8_t dat2 = 0;
    dat1 = SPI_Read(CS_U6,0x16);
    dat2 = SPI_Read(CS_U6,0x17);
    if(dat1>0||dat2>0)
    {
        Led_RT_AllClose();
        TEST=0;
    }
    else
    {
        TEST=1;
    }
}
void Led_Tail_AllOpen(void)
{
    char i;
    for(i=OUT1;i<=OUT6;i++)
    {
            SPI_Write_2Byte(2,i,0xE0);//88%
    }
    SPI_Write_2Byte(2,0x37,0x00);//update
    for(i=OUT1;i<=OUT4;i++)
    {
            SPI_Write_2Byte(1,i,0x33);//20%
    }
    for(i=OUT5;i<=OUT9;i++)
    {
            SPI_Write_2Byte(1,i,0x7D);//49%
    }
    for(i=OUT10;i<=OUT14;i++)
    {
            SPI_Write_2Byte(1,i,0xFF);//100%
    }
    for(i=OUT15;i<=OUT18;i++)
    {
            SPI_Write_2Byte(1,i,0);//侧标关
    }
    SPI_Write_2Byte(1,0x37,0x00);//update
}
void Led_Tail_AllClose(void)
{
    char i;
    for(i=0x1F;i<=0x24;i++)
    {
            SPI_Write_2Byte(2,i,0);//88%
    }
    SPI_Write_2Byte(2,0x37,0x00);//update
    for(i=0x1F;i<=0x22;i++)
    {
            SPI_Write_2Byte(1,i,0);//40%--0x66
    }
    for(i=0x23;i<=0x27;i++)
    {
            SPI_Write_2Byte(1,i,0);//66.66%--0xAA
    }
    for(i=0x28;i<=0x2C;i++)
    {
            SPI_Write_2Byte(1,i,0);//100%--0xFF
    }
    for(i=0x2D;i<=0x30;i++)
    {
            SPI_Write_2Byte(1,i,0);//侧标关
    }
    SPI_Write_2Byte(1,0x37,0x00);//update
}
void Led_Tail_Cebiao_Open(void)//侧标灯
{
    char i;
    for(i=0x2D;i<=0x30;i++)
    {
            SPI_Write_2Byte(1,i,0xBD);//74%
    }
    SPI_Write_2Byte(1,0x37,0x00);//update
}
void Led_Tail_Cebiao_Close(void)//侧标灯
{
    char i;
    for(i=0x2D;i<=0x30;i++)
    {
            SPI_Write_2Byte(1,i,0);//100%
    }
    SPI_Write_2Byte(1,0x37,0x00);//update
}
uint8_t RT_Num = 0;
uint8_t RT_Water_Flag = 0;
void Led_RT_WaterOpen_Callback(void)
{
    RT_Water_Flag = 1;
}
void Led_RT_WaterOpen_Loop(void)
{
  if(RT_Water_Flag)
  {
    RT_Water_Flag = 0;
    if(RT_Num>OUT17)
    {
        RT_Num--;
    }
    else
    {
      if(RT_Num>=OUT8)
      {
          SPI_Write_2Byte(CS_U6,RT_Num+1,0xE8);//91%
          SPI_Write_2Byte(CS_U6,RT_Num,0xE8);//91%
          SPI_Write_2Byte(CS_U6,RT_Num-1,0xE8);//91%
          SPI_Write_2Byte(CS_U6,0x37,0x00);//update
          RT_Num -= 3;
          delay_ms(1);
          Detect_RT();
      }
      else
      {
          Timer5_Stop();
//          delay_ms(1);
//          Detect_RT();
      }
    }
  }
}
void Led_RT_WaterOpen(void)//转向流水开，20ms
{
//	char i;
//	for(i=OUT17;i>=OUT8;i-=3)
//	{
//		SPI_Write_2Byte(CS_U6,i+1,0xFF);//100%
//		SPI_Write_2Byte(CS_U6,i,0xFF);//100%
//		SPI_Write_2Byte(CS_U6,i-1,0xFF);//100%
//		SPI_Write_2Byte(CS_U6,0x37,0x00);//update
//		delay_ms(RT_Interval);
//	}
    if(BACK==1&&TAIL==0)
    {
        RT_Num = OUT21;
    }
    else
    {
        RT_Num = OUT20;
    }
    RT_Water_Flag = 1;
    Timer5_Start();
    Clear_RT();
}
void Led_Tail14_WaterOpen(uint8_t pwm)//位置流水开，50ms
{
	char i;
	for(i=OUT6;i>=OUT1;i--)
	{
		SPI_Write_2Byte(CS_U6,i,pwm);//32%
		SPI_Write_2Byte(CS_U6,0x37,0x00);//update
		delay_ms(60);
	}
	for(i=OUT18;i>=OUT15;i--)
	{
		SPI_Write_2Byte(CS_U2,i,pwm);//100%
		SPI_Write_2Byte(CS_U2,0x37,0x00);//update
		delay_ms(60);
	}

}
void Led_Tail14_OpenMax(void)
{
        char i;
        for(i=OUT6;i>=OUT1;i--)
        {
                SPI_Write_2Byte(CS_U6,i,0xE0);//32%
                SPI_Write_2Byte(CS_U6,0x37,0x00);//update
                delay_ms(60);
        }
        for(i=OUT18;i>=OUT15;i--)
        {
                SPI_Write_2Byte(CS_U2,i,0xC4);//100%
                SPI_Write_2Byte(CS_U2,0x37,0x00);//update
                delay_ms(60);
        }

}
void Led_Tail14_WaterClose(uint8_t pwm)//转向流水关
{
	char i;
	for(i=OUT15;i<=OUT18;i++)
	{
		SPI_Write_2Byte(CS_U2,i,pwm);//100%
		SPI_Write_2Byte(CS_U2,0x37,0x00);//update
		delay_ms(60);
	}
	for(i=OUT1;i<=OUT6;i++)
	{
		SPI_Write_2Byte(CS_U6,i,pwm);
		SPI_Write_2Byte(CS_U6,0x37,0x00);//update
		delay_ms(60);
	}
}
void Led_Tail876_BreathOpen(void)
{
    Led_Tail8_BreathOpen();
    delay_ms(20);
    Led_Tail7_BreathOpen();
    delay_ms(20);
    Led_Tail6_BreathOpen();
    delay_ms(20);
}
void Led_Tail8_BreathOpen(void)//位置呼吸开，50ms
{
      static uint8_t i;
      for(i=0;i<0xC7;i++)
      {
              SPI_Write_2Byte(CS_U2,OUT10,i);
              SPI_Write_2Byte(CS_U2,OUT11,i);
              SPI_Write_2Byte(CS_U2,OUT12,i);
              SPI_Write_2Byte(CS_U2,OUT13,i);
              SPI_Write_2Byte(CS_U2,OUT14,i);
              SPI_Write_2Byte(CS_U2,0x37,0x00);//update
              delay_ms(1);
      }
      for(i=0xC7;i<0xFF;i++)
      {
              delay_ms(1);
      }
}
void Led_Tail8_BreathClose(void)//位置呼吸关
{
	static uint8_t i;
	for(i=0xFF;i>0;i--)
	{
		SPI_Write_2Byte(CS_U2,OUT10,i);
		SPI_Write_2Byte(CS_U2,OUT11,i);
		SPI_Write_2Byte(CS_U2,OUT12,i);
		SPI_Write_2Byte(CS_U2,OUT13,i);
		SPI_Write_2Byte(CS_U2,OUT14,i);
		SPI_Write_2Byte(CS_U2,0x37,0x00);//update
		delay_ms(1);
	}
	SPI_Write_2Byte(CS_U2,OUT10,0);
	SPI_Write_2Byte(CS_U2,OUT11,0);
	SPI_Write_2Byte(CS_U2,OUT12,0);
	SPI_Write_2Byte(CS_U2,OUT13,0);
	SPI_Write_2Byte(CS_U2,OUT14,0);
	SPI_Write_2Byte(CS_U2,0x37,0x00);//update
}
void Led_Tail7_BreathOpen(void)//位置呼吸开，50ms
{
	static uint8_t i;
	for(i=0;i<0x8C;i++)
	{
		SPI_Write_2Byte(CS_U2,OUT5,i);
		SPI_Write_2Byte(CS_U2,OUT6,i);
		SPI_Write_2Byte(CS_U2,OUT7,i);
		SPI_Write_2Byte(CS_U2,OUT8,i);
		SPI_Write_2Byte(CS_U2,OUT9,i);
		SPI_Write_2Byte(CS_U2,0x37,0x00);//update
		delay_ms(1);
	}
        for(i=0x8C;i<0xFF;i++)
        {
            delay_ms(1);
        }
}
void Led_Tail7_BreathClose(void)//位置呼吸关
{
	static uint8_t i;
	for(i=0xFF;i>0;i--)
	{
		SPI_Write_2Byte(CS_U2,OUT5,i);
		SPI_Write_2Byte(CS_U2,OUT6,i);
		SPI_Write_2Byte(CS_U2,OUT7,i);
		SPI_Write_2Byte(CS_U2,OUT8,i);
		SPI_Write_2Byte(CS_U2,OUT9,i);
		SPI_Write_2Byte(CS_U2,0x37,0x00);//update
		delay_ms(1);
	}
	SPI_Write_2Byte(CS_U2,OUT5,0);
	SPI_Write_2Byte(CS_U2,OUT6,0);
	SPI_Write_2Byte(CS_U2,OUT7,0);
	SPI_Write_2Byte(CS_U2,OUT8,0);
	SPI_Write_2Byte(CS_U2,OUT9,0);
	SPI_Write_2Byte(CS_U2,0x37,0x00);//update
}
void Led_Tail6_BreathOpen(void)//位置呼吸开，50ms
{
	static uint8_t i;
	for(i=0;i<0x4C;i++)
	{
		SPI_Write_2Byte(CS_U2,OUT1,i);
		SPI_Write_2Byte(CS_U2,OUT2,i);
		SPI_Write_2Byte(CS_U2,OUT3,i);
		SPI_Write_2Byte(CS_U2,OUT4,i);
		SPI_Write_2Byte(CS_U2,0x37,0x00);//update
		delay_ms(1);
	}
        for(i=0x4C;i<0xFF;i++)
        {
            delay_ms(1);
        }
}
void Led_Tail678_BreathClose(void)
{
    Led_Tail6_BreathClose();
    delay_ms(20);
    Led_Tail7_BreathClose();
    delay_ms(20);
    Led_Tail8_BreathClose();
    delay_ms(20);
}
void Led_Tail6_BreathClose(void)//位置呼吸关
{
	static uint8_t i;
	for(i=0xFF;i>0;i--)
	{
		SPI_Write_2Byte(CS_U2,OUT1,i);
		SPI_Write_2Byte(CS_U2,OUT2,i);
		SPI_Write_2Byte(CS_U2,OUT3,i);
		SPI_Write_2Byte(CS_U2,OUT4,i);
		SPI_Write_2Byte(CS_U2,0x37,0x00);//update
		delay_ms(1);
	}
	SPI_Write_2Byte(CS_U2,OUT1,0);
	SPI_Write_2Byte(CS_U2,OUT2,0);
	SPI_Write_2Byte(CS_U2,OUT3,0);
	SPI_Write_2Byte(CS_U2,OUT4,0);
	SPI_Write_2Byte(CS_U2,0x37,0x00);//update

}
void LED_All_Open(void)
{
	char i;
	for(i=0x1F;i<=0x24;i++)
	{
		SPI_Write_2Byte(2,i,0xFF);//88%
	}
	SPI_Write_2Byte(2,0x37,0x00);//update
	for(i=0x1F;i<=0x22;i++)
	{
		SPI_Write_2Byte(1,i,0xFF);//100%--0xFF
	}
	for(i=0x23;i<=0x27;i++)
	{
		SPI_Write_2Byte(1,i,0xFF);//100%--0xFF
	}
	for(i=0x28;i<=0x2C;i++)
	{
		SPI_Write_2Byte(1,i,0xFF);//100%--0xFF
	}
	for(i=0x2D;i<=0x30;i++)
	{
		SPI_Write_2Byte(1,i,0xFF);//侧标关
	}
	SPI_Write_2Byte(1,0x37,0x00);//update
}
