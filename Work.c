/*
 * Work.c
 *
 *  Created on: 2020-10-7
 *      Author: Rick
 */
#include<KF8A200GQS.h>
#include "PinConfig.h"
#include "Work.h"
#include "Led.h"
#include "SoftSpi.h"

int PastMode=0;
int NowMode=0;
int ActMode=0;

volatile unsigned char TI_Status,BACK_Status,TAIL_Status=0;

void Check_Input(void)
{
	TI_Status = TI;//90转向
	BACK_Status = BACK;//42制动
	TAIL_Status = TAIL;//43位置

	if(TI_Status==0&&BACK_Status==0&&TAIL_Status==0)//全低
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
	else if(TI_Status==0&&BACK_Status==0&&TAIL_Status==1)//位置
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
	else if(TI_Status==0&&BACK_Status==1&&TAIL_Status==0)//制动
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
	else if(TI_Status==0&&BACK_Status==1&&TAIL_Status==1)//位置+制动
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
	else if(TI_Status==1&&BACK_Status==0&&TAIL_Status==0)//转向
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
	else if(TI_Status==1&&BACK_Status==0&&TAIL_Status==1)//转向+位置
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
	else if(TI_Status==1&&BACK_Status==1&&TAIL_Status==0)//转向+制动
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
	else if(TI_Status==1&&BACK_Status==1&&TAIL_Status==1)//全高
	{
		PastMode = NowMode;NowMode = Mode8_Status;
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
	case Mode1_Status:
		Led_Tail_AllClose();	//位置灯全关闭
		Stop_Close();			//制动灯全关闭
		Led_RT_AllClose();		//转向灯全关闭
		break;
	case Mode2_Status:
		Led_Tail_AllOpen();		//位置灯全开启
		Stop_Close();			//制动灯全关闭
		Led_RT_AllClose();		//转向灯全关闭
		break;
	case Mode3_Status:
		Stop_Open();			//制动灯全开启
		Led_RT_AllClose();		//转向灯全关闭
		Led_Tail_AllClose();	//位置灯全关闭
		break;
	case Mode4_Status:
		Led_Tail_AllOpen();		//位置灯全开启
		Stop_Open();			//制动灯全开启
		Led_RT_AllClose();		//转向灯全关闭
		break;
	case Mode5_Status:
		Led_RT_AllOpen();		//转向灯全开启
		Led_Tail_AllClose();	//位置灯全关闭
		Stop_Close();			//制动灯全关闭
		break;
	case Mode6_Status:
		Led_RT_AllOpen();		//转向灯全开启
		Led_Tail_AllOpen();		//位置灯全开启
		Stop_Close();			//制动灯全关闭
		break;
	case Mode7_Status:
		Led_RT_AllOpen();		//转向灯全开启
		Stop_Open();			//制动灯全开启
		Led_Tail_AllClose();	//位置灯全关闭
		break;
	case Mode8_Status:
		Led_Tail_AllOpen();		//位置灯全开启
		Led_RT_AllOpen();		//转向灯全开启
		Stop_Open();			//制动灯全开启
		break;
	default:break;
	}
}
