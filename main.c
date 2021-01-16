#include"main.h"
#include"PinConfig.h"
#include "SoftSpi.h"
#include "work.h"
#include "led.h"
#include "music.h"
#include "music_led.h"
//主函数
void main()
{
	Init_OSC(4); //将系统时钟初始化为32M、使用外部晶振，
	Init_GPIO();
	IS31FL3265B_Init();
	PUIE=1; //使能外设中断
	AIE=1; //总中断开启
	Led_Hello_Check();
	if(!Get_Music())
	{
		Music_Loop();
	}
	while(1)
	{
		Tail_Stop_Check_Input();
		RT_Check_Input();
	}
}
//中断函数0:0X04入口地址
void int_fun0() __interrupt (0)
{
	if(T1IE & T1IF) //1ms中断
	{
		T1IF=0;
		Time_Increase();
	}
}


//中断函数1:0x14入口地址
void int_fun1() __interrupt (1)
{

}
