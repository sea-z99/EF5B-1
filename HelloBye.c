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
		case  770:Led_Tail14_WaterOpen(80);break;//720ms等待B的流水,启动自身位置14 30%PWM流水10*60ms,总1320ms
		case  2090:Led_Tail14_OpenMax();break;//720ms等待B的流水,启动自身位置14 100%PWM流水10*60ms,总1320ms
		case  2690:Led_Tail8_BreathOpen();break;//启动自身位置8 呼吸点亮255ms,,间隔300ms总555ms
		case  2990:Led_Tail7_BreathOpen();break;//启动自身位置7 呼吸点亮255ms,间隔300ms总555ms
		case  3290:Led_Tail6_BreathOpen();break;//启动自身位置6 呼吸点亮255ms,间隔300ms,总555ms
		case  5000:Timer1_Stop();for(;;);break;//启动刹车亮 100% 停止计时，进入死循环
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
		case  50:Stop_Close();break;//关闭制动灯,间隔300ms,总300ms
		case  350:Led_Tail6_BreathClose();break;//启动自身位置6呼吸关255ms,无间隔0,总555ms
		case  670:Led_Tail7_BreathClose();break;//启动自身位置7呼吸关255ms,无间隔0,总555ms
		case  990:Led_Tail8_BreathClose();break;//启动自身位置8呼吸关255ms,无间隔0,总555ms
		case  1330:Led_Tail14_WaterClose(80);break;//启动自身位置14流水关 30%PWM流水10*50ms,等待B 600ms，间隔20ms,总1120ms
		case  2650:Led_Tail14_WaterClose(0);break;//启动自身位置14流水关 0%PWM流水10*50ms,等待B 600ms，间隔20ms,总1120ms
		case  5000:Timer1_Stop();for(;;);break;//灯光全灭，进入死循环
		default:break;
		}
	}
}

