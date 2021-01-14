/*
 * HelloBye.c
 *
 *  Created on: 2021-1-13
 *      Author: Rick
 */
#include <KF8A200GQS.h>
#include "PinConfig.h"
#include "Work.h"
#include "Led.h"
#include "SoftSpi.h"
#include "HelloBye.h"

extern uint32_t Time_Counter;

void Hello(void)
{
	while(1)
	{
		switch(Time_Counter)
		{
		case  0:break;//启动等待
		case  50:delay_ms(150);Led_RT_WaterOpen();Led_RT_WaterClose();break;//150ms等待B,启动自身转向流水4*50ms,间隔500ms,总850
		case  900:delay_ms(150);Led_RT_WaterOpen();Led_RT_WaterClose();break;//150ms等待B,启动自身转向流水4*50ms,间隔500ms,总850
		case  1750:delay_ms(600);Led_Tail14_WaterOpen(80);break;//600ms等待B的流水,启动自身位置14 30%PWM流水6*50ms,,间隔100ms总1000ms
		case  2750:delay_ms(600);Led_Tail14_WaterOpen(255);break;//600ms等待B的流水,启动自身位置14 100%PWM流水6*50ms,,间隔100ms总1000ms
		case  3750:delay_ms(100);Led_Tail8_WaterOpen(255);break;//100ms等待B的两颗流水,启动自身位置8 100%PWM流水5*50ms,,间隔100ms总450ms
		case  4200:delay_ms(50);Led_Tail7_WaterOpen(255);break;//50ms等待B的一颗流水,启动自身位置7 100%PWM流水5*50ms,,间隔100ms总400ms
		case  4600:Led_Tail6_WaterOpen(255);break;//启动自身位置6 100%PWM流水4*50ms,间隔100ms,总300ms
		case  4900:Stop_Open();Timer1_Stop();for(;;);break;//启动刹车亮 100% 停止计时，进入死循环
		default:break;
		}
	}
}
void Bye(void)
{
	while(1)
	{
		switch(Time_Counter)
		{
		case  0:break;//启动等待
		case  50:delay_ms(150);Led_RT_WaterOpen();Led_RT_WaterClose();break;//150ms等待B,启动自身转向流水4*50ms,间隔500ms,总850
		case  900:delay_ms(150);Led_RT_WaterOpen();Led_RT_WaterClose();break;//150ms等待B,启动自身转向流水4*50ms,间隔500ms,总850
		case  1750:Stop_Close();break;//关闭制动灯,间隔100ms,总100ms
		case  1850:Led_Tail6_WaterClose();break;//启动自身位置6流水关 0%PWM流水4*50ms,间隔100ms,总300ms
		case  2150:Led_Tail7_WaterClose();break;//启动自身位置7流水关 0%PWM流水5*50ms,等待B 50ms，间隔100ms,总400ms
		case  2550:Led_Tail8_WaterClose();break;//启动自身位置8流水关 0%PWM流水5*50ms,等待B 100ms，间隔100ms,总450ms
		case  3000:Led_Tail14_WaterClose(80);break;//启动自身位置14流水关 30%PWM流水6*50ms,等待B 600ms，间隔100ms,总1000ms
		case  4000:Led_Tail14_WaterClose(0);break;//启动自身位置14流水关 0%PWM流水6*50ms,等待B 600ms，间隔100ms,总1000ms
		case  5000:Timer1_Stop();for(;;);break;//灯光全灭，进入死循环
		default:break;
		}
	}
}

