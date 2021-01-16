/*
 * Work.c
 *
 *  Created on: 2020-10-7
 *      Author: Rick
 */
#include<KF8A200GQS.h>
#include "PinConfig.h"
#include "main.h"
#include "Work.h"
#include "Led.h"
#include "SoftSpi.h"
#include "HelloBye.h"

uint32_t Time_Counter = 0;

uint16_t PastMode=0;
uint16_t NowMode=0;
uint16_t ActMode=0;
uint16_t RT_PastMode=0;
uint16_t RT_NowMode=0;
uint16_t RT_ActMode=0;

volatile uint8_t RT_Status,Back_Status,Tail_Status=0;
volatile uint8_t WB_EN_Status,CB_Status,RT_EN_Status =0;

void Time_Increase(void)
{
	Time_Counter++;
}
void Time_Clear(void)
{
	Time_Counter=0;
}
void Init_42ms(void)
{
	T1CTL2 = 0x0C;	//	ʱ��Դ��SCLK/4��8��Ƶ
	T1H=0;
	T1L=0;
	PWMMODE = 1;	//ʹ������
	PP2=0xA4;		//42ms
	PP1=0x10;
	T1CS =0;
}
void Init_1ms(void)
{
	T1CTL2 = 0x0C;	//	ʱ��Դ��SCLK/4��8��Ƶ
	T1H=0;
	T1L=0;
	PWMMODE = 1;	//ʹ������
	PP2=0x03;		//1000
	PP1=0xE8;
	T1CS =0;
}
void Timer1_Start(void)
{
	Time_Counter=0;
	T1ON = 1;		//T1��ʱ������
	T1IF = 0;
	T1IE = 1;	//ʹ��T1��ʱ�����жϹ���
}
void Timer1_Stop(void)
{
	Time_Counter=0;
	T1ON = 0;		//T1��ʱ������
	T1IF = 0;
	T1IE = 0;	//ʹ��T1��ʱ�����жϹ���
}

uint8_t Get_Music(void)
{
	return MUSIC_EN;
}
void Led_Hello_Check(void)
{
	Tail_Status = TAIL;//43λ��
	RT_Status = RT;//90ת��
	RT_EN_Status = RT_EN;//ת��ʹ��
	if(Tail_Status==1&&RT_Status==1&&RT_EN_Status==1)
	{
		Init_1ms();
		Timer1_Start();
		Hello();
	}
	if(Tail_Status==1&&RT_Status==1&&RT_EN_Status==0)
	{
		LED_All_Open();//3265Bȫ����ת��
		Init_1ms();
		Timer1_Start();
		Bye();
	}
}
void Tail_Stop_Check_Input(void)
{
	Tail_Status = TAIL;//43λ��
	Back_Status = BACK;//42�ƶ�
	CB_Status = CB;//���
	if(Tail_Status==0&&Back_Status==0&&CB_Status==0)//ȫ��
	{
		PastMode = NowMode;NowMode = Mode0_Status;
		if(NowMode==PastMode)
		{
			ActMode=0;
		}
		else
		{
			ActMode=NowMode;
		}
	}
	else if(Tail_Status==0&&Back_Status==0&&CB_Status==1)//���
	{
		PastMode = NowMode;NowMode = Mode1_Status;
		if(NowMode==PastMode)
		{
			ActMode=0;
		}
		else
		{
			ActMode=NowMode;
		}
	}
	else if(Tail_Status==0&&Back_Status==1&&CB_Status==0)//ɲ��
	{
		PastMode = NowMode;NowMode = Mode2_Status;
		if(NowMode==PastMode)
		{
			ActMode=0;
		}
		else
		{
			ActMode=NowMode;
		}
	}
	else if(Tail_Status==0&&Back_Status==1&&CB_Status==1)//ɲ�����
	{
		PastMode = NowMode;NowMode = Mode3_Status;
		if(NowMode==PastMode)
		{
			ActMode=0;
		}
		else
		{
			ActMode=NowMode;
		}
	}
	else if(Tail_Status==1&&Back_Status==0&&CB_Status==0)//λ��
	{
		PastMode = NowMode;NowMode = Mode4_Status;
		if(NowMode==PastMode)
		{
			ActMode=0;
		}
		else
		{
			ActMode=NowMode;
		}
	}
	else if(Tail_Status==1&&Back_Status==0&&CB_Status==1)//λ�ò��
	{
		PastMode = NowMode;NowMode = Mode5_Status;
		if(NowMode==PastMode)
		{
			ActMode=0;
		}
		else
		{
			ActMode=NowMode;
		}
	}
	else if(Tail_Status==1&&Back_Status==1&&CB_Status==0)//λ��ɲ��
	{
		PastMode = NowMode;NowMode = Mode6_Status;
		if(NowMode==PastMode)
		{
			ActMode=0;
		}
		else
		{
			ActMode=NowMode;
		}
	}
	else if(Tail_Status==1&&Back_Status==1&&CB_Status==1)//ȫ��
	{
		PastMode = NowMode;NowMode = Mode7_Status;
		if(NowMode==PastMode)
		{
			ActMode=0;
		}
		else
		{
			ActMode=NowMode;
		}
	}
	Mode_Act();
}

void Mode_Act(void)
{
	switch(ActMode)
	{
	case Mode0_Status:			//ȫ��
		Led_Tail_AllClose();	//λ�õƹر�
		Led_Tail_Cebiao_Close();//���ƹر�
		Stop_Close();			//�ƶ��ƹر�
		break;
	case Mode1_Status:			//���
		Led_Tail_AllClose();	//λ�õƹر�
		Led_Tail_Cebiao_Open();	//���ƿ���
		Stop_Close();			//�ƶ��ƹر�
		break;
	case Mode2_Status:			//ɲ��
		Led_Tail_AllClose();	//λ�õƹر�
		Led_Tail_Cebiao_Close();//���ƹر�
		Stop_Open();			//�ƶ��ƿ���
		break;
	case Mode3_Status:			//���ɲ��
		Led_Tail_AllClose();	//λ�õƹر�
		Led_Tail_Cebiao_Open();	//���ƿ���
		Stop_Open();			//�ƶ��ƿ���
		break;
	case Mode4_Status:			//λ��
		Led_Tail_AllOpen();		//λ�õƿ���
		Led_Tail_Cebiao_Close();//���ƹر�
		Stop_Close();			//�ƶ��ƹر�
		break;
	case Mode5_Status:			//λ�ò��
		Led_Tail_AllOpen();		//λ�õƿ���
		Led_Tail_Cebiao_Open();	//���ƿ���
		Stop_Close();			//�ƶ��ƹر�
		break;
	case Mode6_Status:			//λ��ɲ��
		Led_Tail_AllOpen();		//λ�õƿ���
		Led_Tail_Cebiao_Close();//���ƹر�
		Stop_Open();			//�ƶ��ƿ���
		break;
	case Mode7_Status:			//ȫ��
		Led_Tail_AllOpen();		//λ�õƿ���
		Led_Tail_Cebiao_Open();	//���ƿ���
		Stop_Open();			//�ƶ��ƿ���
		break;
	default:break;
	}
}
void RT_Mode_Act(void)
{
	switch(RT_ActMode)
	{
	case Mode0_Status:
		Led_RT_AllClose();
		break;
	case Mode1_Status:
		delay_ms(150);//�ȴ�B
		Clear_RT();
		Led_RT_WaterOpen();
		Detect_RT();
		break;
	case Mode2_Status:
		Clear_RT();
		Led_RT_AllOpen();
		delay_ms(1);
		Detect_RT();
		break;
	default:break;
	}
}
void RT_Check_Input(void)
{
	RT_Status = RT;//43λ��
	RT_EN_Status = RT_EN;//42�ƶ�

	if(RT_Status==0)//ȫ��
	{
		RT_PastMode = RT_NowMode;RT_NowMode = Mode0_Status;
		if(RT_NowMode==RT_PastMode)
		{
			RT_ActMode=0;
		}
		else
		{
			RT_ActMode=RT_NowMode;
		}
	}
	else if(RT_Status==1&&RT_EN_Status==0)//��ˮ
	{
		RT_PastMode = RT_NowMode;RT_NowMode = Mode1_Status;
		if(RT_NowMode==RT_PastMode)
		{
			RT_ActMode=0;
		}
		else
		{
			RT_ActMode=RT_NowMode;
		}
	}
	else if(RT_Status==1&&RT_EN_Status==1)//����
	{
		RT_PastMode = RT_NowMode;RT_NowMode = Mode2_Status;
		if(RT_NowMode==RT_PastMode)
		{
			RT_ActMode=0;
		}
		else
		{
			RT_ActMode=RT_NowMode;
		}
	}
	RT_Mode_Act();
}

