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
		// case  0:break;//�����ȴ�
		// case  50:delay_ms(150);Led_RT_WaterOpen();delay_ms(200);Led_RT_WaterClose();break;//150ms�ȴ�B,��������ת����ˮ4*50ms,��200ms�����300ms,��850
		// case  900:delay_ms(150);Led_RT_WaterOpen();delay_ms(200);Led_RT_WaterClose();break;//150ms�ȴ�B,��������ת����ˮ4*50ms,��200ms�����300ms,��850
		// case  1750:delay_ms(600);Led_Tail14_WaterOpen(80);break;//600ms�ȴ�B����ˮ,��������λ��14 30%PWM��ˮ10*50ms,,���300ms��1400ms
		// case  3150:delay_ms(600);Led_Tail14_WaterOpen(255);break;//600ms�ȴ�B����ˮ,��������λ��14 100%PWM��ˮ10*50ms,,���300ms��1400ms
		// case  4550:Led_Tail8_BreathOpen();break;//��������λ��8 ��������255ms,,���300ms��555ms
		// case  5105:Led_Tail7_BreathOpen();break;//��������λ��7 ��������255ms,���300ms��555ms
		// case  5660:Led_Tail6_BreathOpen();break;//��������λ��6 ��������255ms,���300ms,��555ms
		// case  6215:Stop_Open();Timer1_Stop();for(;;);break;//����ɲ���� 100% ֹͣ��ʱ��������ѭ��
		// default:break;
		case  0:break;//�����ȴ�
		case  50:delay_ms(600);Led_Tail14_WaterOpen(80);break;//600ms�ȴ�B����ˮ,��������λ��14 30%PWM��ˮ10*50ms,,���300ms��1400ms
		case  1450:delay_ms(600);Led_Tail14_WaterOpen(255);break;//600ms�ȴ�B����ˮ,��������λ��14 100%PWM��ˮ10*50ms,,���300ms��1400ms
		case  2850:Led_Tail8_BreathOpen();break;//��������λ��8 ��������255ms,,���300ms��555ms
		case  3405:Led_Tail7_BreathOpen();break;//��������λ��7 ��������255ms,���300ms��555ms
		case  3960:Led_Tail6_BreathOpen();break;//��������λ��6 ��������255ms,���300ms,��555ms
		case  4515:Timer1_Stop();for(;;);break;//����ɲ���� 100% ֹͣ��ʱ��������ѭ��
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
		// case  0:break;//�����ȴ�
		// case  50:delay_ms(150);Led_RT_WaterOpen();delay_ms(200);Led_RT_WaterClose();break;//150ms�ȴ�B,��������ת����ˮ4*50ms,��200ms�����300ms,��850
		// case  900:delay_ms(150);Led_RT_WaterOpen();delay_ms(200);Led_RT_WaterClose();break;//150ms�ȴ�B,��������ת����ˮ4*50ms,��200ms�����300ms,s��850
		// case  1750:Stop_Close();break;//�ر��ƶ���,���300ms,��300ms
		// case  2050:Led_Tail6_BreathClose();break;//��������λ��6������255ms,���300ms,��555ms
		// case  2605:Led_Tail7_BreathClose();break;//��������λ��7������255ms,���300ms,��555ms
		// case  3160:Led_Tail8_BreathClose();break;//��������λ��8������255ms,���300ms,��555ms
		// case  3715:Led_Tail14_WaterClose(80);break;//��������λ��14��ˮ�� 30%PWM��ˮ10*50ms,�ȴ�B 600ms�����300ms,��1400ms
		// case  5115:Led_Tail14_WaterClose(0);break;//��������λ��14��ˮ�� 0%PWM��ˮ10*50ms,�ȴ�B 600ms�����300ms,��1400ms
		// case  6515:Timer1_Stop();for(;;);break;//�ƹ�ȫ�𣬽�����ѭ��
		// default:break;
		case  0:break;//�����ȴ�
		case  50:Stop_Close();break;//�ر��ƶ���,���300ms,��300ms
		case  350:Led_Tail6_BreathClose();break;//��������λ��6������255ms,���300ms,��555ms
		case  905:Led_Tail7_BreathClose();break;//��������λ��7������255ms,���300ms,��555ms
		case  1460:Led_Tail8_BreathClose();break;//��������λ��8������255ms,���300ms,��555ms
		case  2015:Led_Tail14_WaterClose(80);break;//��������λ��14��ˮ�� 30%PWM��ˮ10*50ms,�ȴ�B 600ms�����300ms,��1400ms
		case  3415:Led_Tail14_WaterClose(0);break;//��������λ��14��ˮ�� 0%PWM��ˮ10*50ms,�ȴ�B 600ms�����300ms,��1400ms
		case  4815:Timer1_Stop();for(;;);break;//�ƹ�ȫ�𣬽�����ѭ��
		default:break;
		}
	}
}

