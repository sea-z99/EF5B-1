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
	TI_Status = TI;//90ת��
	BACK_Status = BACK;//42�ƶ�
	TAIL_Status = TAIL;//43λ��

	if(TI_Status==0&&BACK_Status==0&&TAIL_Status==0)//ȫ��
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
	else if(TI_Status==0&&BACK_Status==0&&TAIL_Status==1)//λ��
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
	else if(TI_Status==0&&BACK_Status==1&&TAIL_Status==0)//�ƶ�
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
	else if(TI_Status==0&&BACK_Status==1&&TAIL_Status==1)//λ��+�ƶ�
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
	else if(TI_Status==1&&BACK_Status==0&&TAIL_Status==0)//ת��
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
	else if(TI_Status==1&&BACK_Status==0&&TAIL_Status==1)//ת��+λ��
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
	else if(TI_Status==1&&BACK_Status==1&&TAIL_Status==0)//ת��+�ƶ�
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
	else if(TI_Status==1&&BACK_Status==1&&TAIL_Status==1)//ȫ��
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
		Led_Tail_AllClose();	//λ�õ�ȫ�ر�
		Stop_Close();			//�ƶ���ȫ�ر�
		Led_RT_AllClose();		//ת���ȫ�ر�
		break;
	case Mode2_Status:
		Led_Tail_AllOpen();		//λ�õ�ȫ����
		Stop_Close();			//�ƶ���ȫ�ر�
		Led_RT_AllClose();		//ת���ȫ�ر�
		break;
	case Mode3_Status:
		Stop_Open();			//�ƶ���ȫ����
		Led_RT_AllClose();		//ת���ȫ�ر�
		Led_Tail_AllClose();	//λ�õ�ȫ�ر�
		break;
	case Mode4_Status:
		Led_Tail_AllOpen();		//λ�õ�ȫ����
		Stop_Open();			//�ƶ���ȫ����
		Led_RT_AllClose();		//ת���ȫ�ر�
		break;
	case Mode5_Status:
		Led_RT_AllOpen();		//ת���ȫ����
		Led_Tail_AllClose();	//λ�õ�ȫ�ر�
		Stop_Close();			//�ƶ���ȫ�ر�
		break;
	case Mode6_Status:
		Led_RT_AllOpen();		//ת���ȫ����
		Led_Tail_AllOpen();		//λ�õ�ȫ����
		Stop_Close();			//�ƶ���ȫ�ر�
		break;
	case Mode7_Status:
		Led_RT_AllOpen();		//ת���ȫ����
		Stop_Open();			//�ƶ���ȫ����
		Led_Tail_AllClose();	//λ�õ�ȫ�ر�
		break;
	case Mode8_Status:
		Led_Tail_AllOpen();		//λ�õ�ȫ����
		Led_RT_AllOpen();		//ת���ȫ����
		Stop_Open();			//�ƶ���ȫ����
		break;
	default:break;
	}
}
