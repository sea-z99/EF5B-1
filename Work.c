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
uint32_t Hello_Bye_Counter = 0;

uint16_t PastMode=0;
uint16_t NowMode=0;
uint16_t ActMode=0;
uint16_t RT_PastMode=0;
uint16_t RT_NowMode=0;
uint16_t RT_ActMode=0;

volatile uint8_t RT_Status,Back_Status,Tail_Status,WB_Status=0;
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
	T1CTL2 = 0x0C;	//	时钟源是SCLK/4，8分频
	T1H=0;
	T1L=0;
	PWMMODE = 1;	//使能重载
	PP2=0xA4;		//42ms
	PP1=0x10;
	T1CS =0;
}
void Init_1ms(void)
{
	T1CTL2 = 0x0C;	//	时钟源是SCLK/4，8分频
	T1H=0;
	T1L=0;
	PWMMODE = 1;	//使能重载
	PP2=0x03;		//1000
	PP1=0xE8;
	T1CS =0;
}
void Timer1_Start(void)
{
	Time_Counter=0;
	T1ON = 1;		//T1定时器启动
	T1IF = 0;
	T1IE = 1;	//使能T1定时器的中断功能
}
void Timer1_Stop(void)
{
	Time_Counter=0;
	T1ON = 0;		//T1定时器启动
	T1IF = 0;
	T1IE = 0;	//使能T1定时器的中断功能
}
void Timer2_Init(void)
{
	T2CTL0 = 0x0B;	//	预分频16，后分频2
	T2CTL1 = 0x02; //向上计数,时钟源是SCLK-32M，
	T2H=0;
	T2L=0;
	PP60H=0;		//1000
	PP60L=0x0A;
}
void Timer2_Start(void)
{
	T2IF = 0;
	T2ON = 1;		//T2定时器启动
	T2IE = 1;
}
void Timer2_Stop(void)
{
	T2IF = 0;
	T2ON = 0;		//T2定时器停止
	T2IE = 0;
}
void Timer5_Init(void)//1000
{
      T5CTL0 = 0x0B;  //      ʱ��Դ��SCLK-32M��Ԥ��Ƶ16�����Ƶ2
      T5CTL1 = 0x02; //���ϼ���,ʱ��Դ��SCLK-32M��
      T5H=0;
      T5L=0;
//      PP70H=0x75;             //30000
//      PP70L=0x30;
      PP70H=0x9C;             //40000
      PP70L=0x40;
}
void Timer5_Start(void)
{
      T5ON = 1;               //T5��ʱ������
      T5IF = 0;
      T5IE = 1;
}
void Timer5_Stop(void)
{
      T5ON = 0;               //T5��ʱ������
      T5IF = 0;
      T5IE = 0;
}
void PwmRisingInit(void)
{
	INT0IF=0;
	INT0IE=1;
	INT0SE=1;		//上升沿
}
void PwmFallingInit(void)
{
	INT0IF=0;
	INT0IE=1;
	INT0SE=0;		//下降沿
}
void PwmDeInit(void)
{
	INT0IE=0;
}
void Hello_Bye_Callback(void)
{
	Hello_Bye_Counter+=10;
}
typedef struct
{
	uint8_t State;
	uint32_t R_Time;
	uint32_t F_Time;
	uint32_t T_Time;
	float Duty;
	uint8_t ActFlag;
	uint8_t FromInteruppt;
}PwmStatus;
PwmStatus PwmDetectStatus;
void PwmFromInteruppt(void)
{
	PwmDetectStatus.FromInteruppt=1;
}
uint8_t SearchPwmFlag(void)
{
	return PwmDetectStatus.ActFlag;
}
void PwmStatusClear(void)
{
    PwmDetectStatus.State = 0;
    PwmDetectStatus.R_Time = 0;
    PwmDetectStatus.F_Time = 0;
    PwmDetectStatus.T_Time = 0;
    PwmDetectStatus.Duty = 0;
    PwmDetectStatus.ActFlag = 0;
    PwmDetectStatus.FromInteruppt = 0;
}
void PwmDetect(void)
{
	uint32_t time=5690;
	PwmStatusClear();
	Timer2_Init();
	PwmRisingInit();
	while(PwmDetectStatus.State!=3&&time-->0)
	{
		if(PwmDetectStatus.FromInteruppt)
		{
			PwmDetectStatus.FromInteruppt=0;
			switch(PwmDetectStatus.State)
			{
			case 0:
				Timer2_Start();
				PwmFallingInit();
				PwmDetectStatus.State = 1;
				break;
			case 1:
				PwmDetectStatus.R_Time = Hello_Bye_Counter;
				PwmRisingInit();
				PwmDetectStatus.State = 2;
				Hello_Bye_Counter = 0;
				break;
			case 2:
                                PwmDetectStatus.F_Time = Hello_Bye_Counter;
                                PwmDeInit();
                                Timer2_Stop();
                                PwmDetectStatus.T_Time = PwmDetectStatus.R_Time + PwmDetectStatus.F_Time;
                                PwmDetectStatus.Duty = (float)PwmDetectStatus.F_Time / (float)PwmDetectStatus.T_Time;
				PwmDetectStatus.State = 3;
				break;
			default:break;
			}
		}
	}
        if(PwmDetectStatus.R_Time==0)
        {
            PwmDetectStatus.ActFlag=0;
            return;
        }
	if(PwmDetectStatus.T_Time>=3500&&PwmDetectStatus.T_Time<=4400)//127--187
        {
            if(PwmDetectStatus.Duty>=0.2&&PwmDetectStatus.Duty<=0.4)//30-40
            {
                PwmDetectStatus.ActFlag=1;
            }
            if(PwmDetectStatus.Duty>=0.6&&PwmDetectStatus.Duty<=0.8)//70-80
            {
                PwmDetectStatus.ActFlag=2;
            }
        }
}
uint8_t Get_Music(void)
{
	return MUSIC_EN;
}
void Led_Hello_Check(uint8_t Flag)
{
	Tail_Status = TAIL;//43位置
	RT_Status = RT;
	WB_Status = WB_EN;
	if(Tail_Status==1&&Flag==1)
//	if(Tail_Status==1&&RT_Status==1&&WB_Status==1)
	{
		Init_1ms();
		Timer1_Start();
		Hello();
	}
	if(Tail_Status==1&&Flag==2)
//	if(Tail_Status==1&&RT_Status==1&&WB_Status==0)
	{
		LED_All_Open();//3265B全开除转向
		Init_1ms();
		Timer1_Start();
		Bye();
	}
}
void Stop_Check(void)
{
    STOP = BACK;//42制动
}
void Tail_Check_Input(void)
{
	Tail_Status = TAIL;//43位置
	CB_Status = CB;//侧标
	if(Tail_Status==0&&CB_Status==0)//全低
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
	else if(Tail_Status==0&&CB_Status==1)//侧标
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
	else if(Tail_Status==1&&CB_Status==0)//位置
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
	else if(Tail_Status==1&&CB_Status==1)//位置侧标
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
	Mode_Act();
}

void Mode_Act(void)
{
	switch(ActMode)
	{
	case Mode0_Status:			//全低
		Led_Tail_AllClose();	        //位置灯关闭
		Led_Tail_Cebiao_Close();        //侧标灯关闭
		break;
	case Mode1_Status:			//侧标
		Led_Tail_AllClose();	        //位置灯关闭
		Led_Tail_Cebiao_Open();	        //侧标灯开启
		break;
	case Mode2_Status:			//位置
	        Led_Tail_AllOpen();	        //位置灯开启
		Led_Tail_Cebiao_Close();        //侧标灯关闭
		break;
	case Mode3_Status:			//位置侧标
                Led_Tail_AllOpen();             //位置灯开启
                Led_Tail_Cebiao_Open();         //侧标灯开启
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
		Clear_RT();
		Led_RT_WaterOpen();
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
	RT_Status = RT;//转向
	RT_EN_Status = RT_EN;//转向使能

	if(RT_Status==0)//全低
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
	else if(RT_Status==1&&RT_EN_Status==0)//流水
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
	else if(RT_Status==1&&RT_EN_Status==1)//常亮
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

