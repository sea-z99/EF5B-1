#include"main.h"
#include"PinConfig.h"
#include "SoftSpi.h"
#include "work.h"
#include "led.h"
//主函数
void main()
{
	Init_OSC(4); //将系统时钟初始化为32M、使用外部晶振，
	Init_GPIO();
	IS31FL3265B_Init();
	while(1)
	{
		Check_Input();
	}
}
//中断函数0:0X04入口地址
void int_fun0() __interrupt (0)
{

}


//中断函数1:0x14入口地址
void int_fun1() __interrupt (1)
{

}
