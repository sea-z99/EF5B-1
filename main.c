#include"main.h"
#include"PinConfig.h"
#include "SoftSpi.h"
#include "work.h"
#include "led.h"
#include "music.h"
#include "music_led.h"

//主函数
uint8_t music_flag=0;
void main()
{
    Init_OSC(1); //将系统时钟初始化为32M、使用外部晶振，
    Init_GPIO();
    Timer3_Init();
    IS31FL3265B_Init();
    PUIE=1; //使能外设中断
    AIE=1; //总中断开启
    PwmDetect();
    Led_Hello_Check(SearchPwmFlag());
    while(1)
    {
        if(!Get_Music()&&music_flag==0)
        {
            music_flag=1;
            Music_Loop();
        }
        else if(Get_Music()&&music_flag==1)
        {
            Music_Stop();
        }
        Tail_Check_Input();
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
	if(T2IE & T2IF) //1ms中断
	{
		T2IF=0;
		Hello_Bye_Callback();
	}
        if(T3IE & T3IF) //1ms中断
        {
                T3IF=0;
                Stop_PWM();
        }
	if(INT0IE && INT0IF) //INT0中断的响应
	{
		INT0IF=0;
		PwmFromInteruppt();
	}
}


//中断函数1:0x14入口地址
void int_fun1() __interrupt (1)
{

}
