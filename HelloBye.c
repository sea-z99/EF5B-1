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
		case  50:delay_ms(150);Led_RT_WaterOpen();Led_RT_WaterClose();break;//150ms�ȴ�B,��������ת����ˮ4*50ms,���500ms,��850
		case  900:delay_ms(150);Led_RT_WaterOpen();Led_RT_WaterClose();break;//150ms�ȴ�B,��������ת����ˮ4*50ms,���500ms,��850
		case  1750:delay_ms(600);Led_Tail14_WaterOpen(80);break;//600ms�ȴ�B����ˮ,��������λ��14 30%PWM��ˮ6*50ms,,���100ms��1000ms
		case  2750:delay_ms(600);Led_Tail14_WaterOpen(255);break;//600ms�ȴ�B����ˮ,��������λ��14 100%PWM��ˮ6*50ms,,���100ms��1000ms
		case  3750:delay_ms(100);Led_Tail8_WaterOpen(255);break;//100ms�ȴ�B��������ˮ,��������λ��8 100%PWM��ˮ5*50ms,,���100ms��450ms
		case  4200:delay_ms(50);Led_Tail7_WaterOpen(255);break;//50ms�ȴ�B��һ����ˮ,��������λ��7 100%PWM��ˮ5*50ms,,���100ms��400ms
		case  4600:Led_Tail6_WaterOpen(255);break;//��������λ��6 100%PWM��ˮ4*50ms,���100ms,��300ms
		case  4900:Stop_Open();Timer1_Stop();for(;;);break;//����ɲ���� 100% ֹͣ��ʱ��������ѭ��
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
		case  50:delay_ms(150);Led_RT_WaterOpen();Led_RT_WaterClose();break;//150ms�ȴ�B,��������ת����ˮ4*50ms,���500ms,��850
		case  900:delay_ms(150);Led_RT_WaterOpen();Led_RT_WaterClose();break;//150ms�ȴ�B,��������ת����ˮ4*50ms,���500ms,��850
		case  1750:Stop_Close();break;//�ر��ƶ���,���100ms,��100ms
		case  1850:Led_Tail6_WaterClose();break;//��������λ��6��ˮ�� 0%PWM��ˮ4*50ms,���100ms,��300ms
		case  2150:Led_Tail7_WaterClose();break;//��������λ��7��ˮ�� 0%PWM��ˮ5*50ms,�ȴ�B 50ms�����100ms,��400ms
		case  2550:Led_Tail8_WaterClose();break;//��������λ��8��ˮ�� 0%PWM��ˮ5*50ms,�ȴ�B 100ms�����100ms,��450ms
		case  3000:Led_Tail14_WaterClose(80);break;//��������λ��14��ˮ�� 30%PWM��ˮ6*50ms,�ȴ�B 600ms�����100ms,��1000ms
		case  4000:Led_Tail14_WaterClose(0);break;//��������λ��14��ˮ�� 0%PWM��ˮ6*50ms,�ȴ�B 600ms�����100ms,��1000ms
		case  5000:Timer1_Stop();for(;;);break;//�ƹ�ȫ�𣬽�����ѭ��
		default:break;
		}
	}
}

