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
		 case  50:delay_ms(60);Led_RT_WaterOpen();delay_ms(300);Led_RT_WaterClose();break;//60ms等待B,启动自身转向流水4*20ms,亮80ms，间隔300ms,总440
		 case  490:delay_ms(60);Led_RT_WaterOpen();delay_ms(300);Led_RT_WaterClose();break;//60ms等待B,启动自身转向流水4*20ms,亮80ms，间隔300ms,总440
		 case  930:delay_ms(600);Led_Tail14_WaterOpen(80);break;//600ms等待B的流水,启动自身位置14 30%PWM流水10*50ms,,间隔300ms总1400ms
		 case  2330:delay_ms(600);Led_Tail14_WaterOpen(255);break;//600ms等待B的流水,启动自身位置14 100%PWM流水10*50ms,,间隔300ms总1400ms
		 case  3730:Led_Tail8_BreathOpen();break;//启动自身位置8 呼吸点亮255ms,,间隔300ms总555ms
		 case  4285:Led_Tail7_BreathOpen();break;//启动自身位置7 呼吸点亮255ms,间隔300ms总555ms
		 case  4840:Led_Tail6_BreathOpen();break;//启动自身位置6 呼吸点亮255ms,间隔300ms,总555ms
		 case  5395:Stop_Open();Timer1_Stop();for(;;);break;//启动刹车亮 100% 停止计时，进入死循环
		 default:break;
//		case  0:break;//启动等待
//		case  50:delay_ms(600);Led_Tail14_WaterOpen(80);break;//600ms等待B的流水,启动自身位置14 30%PWM流水10*50ms,,间隔300ms总1400ms
//		case  1450:delay_ms(600);Led_Tail14_WaterOpen(255);break;//600ms等待B的流水,启动自身位置14 100%PWM流水10*50ms,,间隔300ms总1400ms
//		case  2850:Led_Tail8_BreathOpen();break;//启动自身位置8 呼吸点亮255ms,,间隔300ms总555ms
//		case  3405:Led_Tail7_BreathOpen();break;//启动自身位置7 呼吸点亮255ms,间隔300ms总555ms
//		case  3960:Led_Tail6_BreathOpen();break;//启动自身位置6 呼吸点亮255ms,间隔300ms,总555ms
//		case  4515:Timer1_Stop();for(;;);break;//启动刹车亮 100% 停止计时，进入死循环
//		default:break;
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
		 case  50:delay_ms(60);Led_RT_WaterOpen();delay_ms(300);Led_RT_WaterClose();break;//60ms等待B,启动自身转向流水4*20ms,亮80ms，间隔300ms,总440
		 case  490:delay_ms(60);Led_RT_WaterOpen();delay_ms(300);Led_RT_WaterClose();break;//60ms等待B,启动自身转向流水4*20ms,亮80ms，间隔300ms,总440
		 case  930:Stop_Close();break;//关闭制动灯,间隔300ms,总300ms
		 case  1230:Led_Tail6_BreathClose();break;//启动自身位置6呼吸关255ms,间隔300ms,总555ms
		 case  1785:Led_Tail7_BreathClose();break;//启动自身位置7呼吸关255ms,间隔300ms,总555ms
		 case  2340:Led_Tail8_BreathClose();break;//启动自身位置8呼吸关255ms,间隔300ms,总555ms
		 case  2895:Led_Tail14_WaterClose(80);break;//启动自身位置14流水关 30%PWM流水10*50ms,等待B 600ms，间隔300ms,总1400ms
		 case  4295:Led_Tail14_WaterClose(0);break;//启动自身位置14流水关 0%PWM流水10*50ms,等待B 600ms，间隔300ms,总1400ms
		 case  5695:Timer1_Stop();for(;;);break;//灯光全灭，进入死循环
		 default:break;
//		case  0:break;//启动等待
//		case  50:Stop_Close();break;//关闭制动灯,间隔300ms,总300ms
//		case  350:Led_Tail6_BreathClose();break;//启动自身位置6呼吸关255ms,间隔300ms,总555ms
//		case  905:Led_Tail7_BreathClose();break;//启动自身位置7呼吸关255ms,间隔300ms,总555ms
//		case  1460:Led_Tail8_BreathClose();break;//启动自身位置8呼吸关255ms,间隔300ms,总555ms
//		case  2015:Led_Tail14_WaterClose(80);break;//启动自身位置14流水关 30%PWM流水10*50ms,等待B 600ms，间隔300ms,总1400ms
//		case  3415:Led_Tail14_WaterClose(0);break;//启动自身位置14流水关 0%PWM流水10*50ms,等待B 600ms，间隔300ms,总1400ms
//		case  4815:Timer1_Stop();for(;;);break;//灯光全灭，进入死循环
//		default:break;
		}
	}
}

