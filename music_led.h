/*
 * music.h
 *
 *  Created on: 2021-1-11
 *      Author: Rick
 */

#ifndef MUSIC_LED_H_
#define MUSIC_LED_H_

#define U2_SPI_Write_2Byte(a,b)	SPI_Write_2Byte(1,a,b)
#define U6_SPI_Write_2Byte(a,b)	SPI_Write_2Byte(2,a,b)
#define Delayms(value)	delay_ms(value)

void OUTx_PWM(uint8_t device,uint8_t channel,uint8_t pwm);
void OUTx_Flash(uint8_t device,uint8_t channel);
void All_LED_PWM(uint8_t pwm);
void BASE_PWM(uint8_t pwm);
void Gangqin_Flash(uint8_t device,uint8_t channel);
void SCAN(uint16_t t);
void SCAN_BACK(uint16_t t);
void Side_Liushui(uint16_t h);
void LIUSHUI(void);
void All_STOP_PWM(uint8_t pwm);
void Side_flash(uint8_t pwm);
void Piano_flash(uint8_t device,uint8_t ch1);
void End(void);
void Step1(void);

#endif /* MUSIC_H_ */
