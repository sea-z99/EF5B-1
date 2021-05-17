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
		case  770:Led_Tail14_WaterOpen(80);break;//720ms�ȴ�B����ˮ,��������λ��14 30%PWM��ˮ10*60ms,��1320ms
		case  2090:Led_Tail14_OpenMax();break;//720ms�ȴ�B����ˮ,��������λ��14 100%PWM��ˮ10*60ms,��1320ms
		case  2690:Led_Tail8_BreathOpen();break;//��������λ��8 ��������255ms,,���300ms��555ms
		case  2990:Led_Tail7_BreathOpen();break;//��������λ��7 ��������255ms,���300ms��555ms
		case  3290:Led_Tail6_BreathOpen();break;//��������λ��6 ��������255ms,���300ms,��555ms
		case  5000:Timer1_Stop();for(;;);break;//����ɲ���� 100% ֹͣ��ʱ��������ѭ��
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
		case  0:break;//�����ȴ�
		case  50:Stop_Close();break;//�ر��ƶ���,���300ms,��300ms
		case  350:Led_Tail6_BreathClose();break;//��������λ��6������255ms,�޼��0,��555ms
		case  670:Led_Tail7_BreathClose();break;//��������λ��7������255ms,�޼��0,��555ms
		case  990:Led_Tail8_BreathClose();break;//��������λ��8������255ms,�޼��0,��555ms
		case  1330:Led_Tail14_WaterClose(80);break;//��������λ��14��ˮ�� 30%PWM��ˮ10*50ms,�ȴ�B 600ms�����20ms,��1120ms
		case  2650:Led_Tail14_WaterClose(0);break;//��������λ��14��ˮ�� 0%PWM��ˮ10*50ms,�ȴ�B 600ms�����20ms,��1120ms
		case  5000:Timer1_Stop();for(;;);break;//�ƹ�ȫ�𣬽�����ѭ��
		default:break;
		}
	}
}

