/*
 * PinConfig.h
 *
 *  Created on: 2020-10-6
 *      Author: Rick
 */

#ifndef PINCONFIG_H_
#define PINCONFIG_H_

#define	CS1HIGH		P0LR3=1
#define	CS1LOW		P0LR3=0

#define	CS2HIGH		P0LR4=1
#define	CS2LOW		P0LR4=0

#define SDB1		PBLR2
#define STOP		P9LR5
#define TEST		P3LR0

#define RT			P90
#define BACK 		P42
#define TAIL 		P43
#define MUSIC_EN 	P44
#define WB_EN 		P45
#define RT_EN 		P86//低流水
#define CB 			P84//高使能

#endif /* PINCONFIG_H_ */
