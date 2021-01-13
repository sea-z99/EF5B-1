/*
 * Led.h
 *
 *  Created on: 2020-10-9
 *      Author: Rick
 */

#ifndef LED_H_
#define LED_H_

#define LED_Interval	(50)

#define OUT1 0x1F
#define OUT2 0x20
#define OUT3 0x21
#define OUT4 0x22
#define OUT5 0x23
#define OUT6 0x24
#define OUT7 0x25
#define OUT8 0x26
#define OUT9 0x27
#define OUT10 0x28
#define OUT11 0x29
#define OUT12 0x2A
#define OUT13 0x2B
#define OUT14 0x2C
#define OUT15 0x2D
#define OUT16 0x2E
#define OUT17 0x2F
#define OUT18 0x30

void Stop_Open(void);
void Stop_Close(void);
void Led_RT_AllOpen(void);
void Led_RT_AllClose(void);
void Led_Tail_AllOpen(void);
void Led_Tail_AllClose(void);
void Led_Tail_Cebiao_Open(void);
void Led_RT_WaterOpen(void);
void Led_RT_WaterClose(void);
void Led_Tail14_WaterOpen(uint8_t pwm);
void Led_Tail14_WaterClose(uint8_t pwm);
void Led_Tail8_WaterOpen(uint8_t pwm);
void Led_Tail8_WaterClose(void);
void Led_Tail7_WaterOpen(uint8_t pwm);
void Led_Tail7_WaterClose(void);
void Led_Tail6_WaterOpen(uint8_t pwm);
void Led_Tail6_WaterClose(void);
void LED_All_Open(void);
#endif /* LED_H_ */
