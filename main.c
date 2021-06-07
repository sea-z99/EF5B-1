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
    Init_OSC(1);
    Init_GPIO();
    Timer5_Init();
    IS31FL3265B_Init();
    PUIE=1; //使能外设中断
    AIE=1; //总中断开启
    PwmDetect();
    Led_Hello_Check(SearchPwmFlag());
    while(1)
    {
//        if(Get_Music()==0)
//        {
//            Music_Loop();
//        }
        Tail_Check_Input();
        RT_Check_Input();
        Led_RT_WaterOpen_Loop();
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
        if(T5IE & T5IF) //20ms中断
        {
              T5IF=0;
              Led_RT_WaterOpen_Callback();
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
