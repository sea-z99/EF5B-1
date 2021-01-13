/*
 * main.h
 *
 *  Created on: 2019-9-27
 *      Author: charles_cai
 */

#include<KF8A200GQV.h>
#include "OSC.h"
#include "GPIO.h"

#ifndef MAIN_H_
#define MAIN_H_

#define uint8_t		unsigned char
#define uint16_t	unsigned short
#define uint32_t	unsigned int
#define uint64_t	unsigned long

#define U6 (0)
#define U8 (1)

#define CS_U2_6 (0)
#define CS_U2 (1)
#define CS_U6 (2)


void delay_ms(unsigned int num);

#endif /* MAIN_H_ */
