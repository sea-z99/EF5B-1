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
		 case  0:break;//�����ȴ�
		 case  50:delay_ms(60);Led_RT_WaterOpen();delay_ms(200);Led_RT_WaterClose();break;//60ms�ȴ�B,��������ת����ˮ4*20ms,��80ms�����200ms,�ȴ�200ms��540
		 case  590:delay_ms(60);Led_RT_WaterOpen();delay_ms(200);Led_RT_WaterClose();break;//60ms�ȴ�B,��������ת����ˮ4*20ms,��80ms�����300ms,��540
		 case  1130:delay_ms(600);Led_Tail14_WaterOpen(80);break;//600ms�ȴ�B����ˮ,��������λ��14 30%PWM��ˮ10*50ms,,���300ms��1400ms
		 case  2530:delay_ms(600);Led_Tail14_WaterOpen(255);break;//600ms�ȴ�B����ˮ,��������λ��14 100%PWM��ˮ10*50ms,,���300ms��1400ms
		 case  3930:Led_Tail8_BreathOpen();break;//��������λ��8 ��������255ms,,���300ms��555ms
		 case  4485:Led_Tail7_BreathOpen();break;//��������λ��7 ��������255ms,���300ms��555ms
		 case  5040:Led_Tail6_BreathOpen();break;//��������λ��6 ��������255ms,���300ms,��555ms
		 case  5595:Timer1_Stop();for(;;);break;//����ɲ���� 100% ֹͣ��ʱ��������ѭ��
		 default:break;
//		case  0:break;//�����ȴ�
//		case  50:delay_ms(600);Led_Tail14_WaterOpen(80);break;//600ms�ȴ�B����ˮ,��������λ��14 30%PWM��ˮ10*50ms,,���300ms��1400ms
//		case  1450:delay_ms(600);Led_Tail14_WaterOpen(255);break;//600ms�ȴ�B����ˮ,��������λ��14 100%PWM��ˮ10*50ms,,���300ms��1400ms
//		case  2850:Led_Tail8_BreathOpen();break;//��������λ��8 ��������255ms,,���300ms��555ms
//		case  3405:Led_Tail7_BreathOpen();break;//��������λ��7 ��������255ms,���300ms��555ms
//		case  3960:Led_Tail6_BreathOpen();break;//��������λ��6 ��������255ms,���300ms,��555ms
//		case  4515:Timer1_Stop();for(;;);break;//����ɲ���� 100% ֹͣ��ʱ��������ѭ��
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
		 case  0:break;//�����ȴ�
		 case  50:delay_ms(60);Led_RT_WaterOpen();delay_ms(200);Led_RT_WaterClose();break;//60ms�ȴ�B,��������ת����ˮ4*20ms,��80ms�����200ms,�ȴ�100��540
		 case  590:delay_ms(60);Led_RT_WaterOpen();delay_ms(200);Led_RT_WaterClose();break;//60ms�ȴ�B,��������ת����ˮ4*20ms,��80ms�����200ms,�ȴ�100��540
		 case  1130:Stop_Close();break;//�ر��ƶ���,���300ms,��300ms
		 case  1430:Led_Tail6_BreathClose();break;//��������λ��6������255ms,���300ms,��555ms
		 case  1985:Led_Tail7_BreathClose();break;//��������λ��7������255ms,���300ms,��555ms
		 case  2540:Led_Tail8_BreathClose();break;//��������λ��8������255ms,���300ms,��555ms
		 case  3095:Led_Tail14_WaterClose(80);break;//��������λ��14��ˮ�� 30%PWM��ˮ10*50ms,�ȴ�B 600ms�����300ms,��1400ms
		 case  4495:Led_Tail14_WaterClose(0);break;//��������λ��14��ˮ�� 0%PWM��ˮ10*50ms,�ȴ�B 600ms�����300ms,��1400ms
		 case  5895:Timer1_Stop();for(;;);break;//�ƹ�ȫ�𣬽�����ѭ��
		 default:break;
//		case  0:break;//�����ȴ�
//		case  50:Stop_Close();break;//�ر��ƶ���,���300ms,��300ms
//		case  350:Led_Tail6_BreathClose();break;//��������λ��6������255ms,���300ms,��555ms
//		case  905:Led_Tail7_BreathClose();break;//��������λ��7������255ms,���300ms,��555ms
//		case  1460:Led_Tail8_BreathClose();break;//��������λ��8������255ms,���300ms,��555ms
//		case  2015:Led_Tail14_WaterClose(80);break;//��������λ��14��ˮ�� 30%PWM��ˮ10*50ms,�ȴ�B 600ms�����300ms,��1400ms
//		case  3415:Led_Tail14_WaterClose(0);break;//��������λ��14��ˮ�� 0%PWM��ˮ10*50ms,�ȴ�B 600ms�����300ms,��1400ms
//		case  4815:Timer1_Stop();for(;;);break;//�ƹ�ȫ�𣬽�����ѭ��
//		default:break;
		}
	}
}

