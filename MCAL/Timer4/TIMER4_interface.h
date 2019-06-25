/*
 * TIMER_interface.h
 *
 *  Created on: 20 Jun 2019
 *      Author: mahmoud-
 */

#ifndef TIMER4_INTERFACE_H_
#define TIMER4_INTERFACE_H_








 typedef struct {


	Register_32Bit CR1;
	Register_32Bit CR2;
	Register_32Bit SMCR;
	Register_32Bit DIER;
	Register_32Bit SR;
	Register_32Bit EGR;
	Register_32Bit CCMR1;
	Register_32Bit CCMR2;
	Register_32Bit CCER;
	Register_32Bit CNT;
	Register_32Bit PSC;
	Register_32Bit ARR;
	Register_32Bit Reserved;
	Register_32Bit CCR1;
	Register_32Bit CCR2;
	Register_32Bit CCR3;
	Register_32Bit CCR4;
	Register_32Bit Reserved2;
	Register_32Bit DCR;
	Register_32Bit DMAR;

}Timer_Registers;


#define Timer4 ((Timer_Registers*)0x40000800)



#define TIMER4_CHANNEL_1			(u8)0
#define TIMER4_CHANNEL_2			(u8)1
#define TIMER4_CHANNEL_3	        (u8)2
#define TIMER4_CHANNEL_4	        (u8)3

void TIMER4_voidInitialize(void);

void TIMER4_voidTimerEnable(void);


u8 TIMER4_u8SetDutyCycle(u8 Copy_u8NbOfChannel,u8 Copy_u8DutyValue);


#endif /* TIMER4_INTERFACE_H_ */
