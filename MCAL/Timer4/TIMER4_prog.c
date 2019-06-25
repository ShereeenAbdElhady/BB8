/*
 * TIMER_prog.c
 *
 *  Created on: 20 Jun 2019
 *      Author: mahmoud-
 */
#include"../STD_TYPES.h"
#include "../include/TIMER4_config.h"
#include "../include/TIMER4_interface.h"


void TIMER4_voidInitialize(void){



	Timer4->CR1.BitAccess.Bit7=1;

	//Timer4->BDTR.BitAccess.Bit15=1;

	Timer4->PSC.FourByteAccess=TIMER4_PRESCALE;
	Timer4->ARR.FourByteAccess=TIMER4_BUFFER;


#if	Timer4_CHANNEL_1 == Timer4_CHANNEL_ENABLE

	Timer4->CCMR1.BitAccess.Bit6=1;
	Timer4->CCMR1.BitAccess.Bit5=1;
	Timer4->CCMR1.BitAccess.Bit4=0;
	Timer4->CCMR1.BitAccess.Bit3=1;
	Timer4->CCER.BitAccess.Bit0=1;
#endif

#if	Timer4_CHANNEL_2 == Timer4_CHANNEL_ENABLE

	Timer4->CCMR1.BitAccess.Bit14=1;
	Timer4->CCMR1.BitAccess.Bit13=1;
	Timer4->CCMR1.BitAccess.Bit12=0;
	Timer4->CCMR1.BitAccess.Bit11=1;
	Timer4->CCER.BitAccess.Bit4=1;

#endif

#if		Timer4_CHANNEL_3 == Timer4_CHANNEL_ENABLE

	Timer4->CCMR2.BitAccess.Bit6=1;
	Timer4->CCMR2.BitAccess.Bit5=1;
	Timer4->CCMR2.BitAccess.Bit4=0;
	Timer4->CCMR2.BitAccess.Bit3=1;
	Timer4->CCER.BitAccess.Bit8=1;
#endif

#if		Timer4_CHANNEL_4 == Timer4_CHANNEL_ENABLE

	Timer4->CCMR2.BitAccess.Bit14=1;
	Timer4->CCMR2.BitAccess.Bit13=1;
	Timer4->CCMR2.BitAccess.Bit12=0;
	Timer4->CCMR2.BitAccess.Bit11=1;
	Timer4->CCER.BitAccess.Bit12=1;
#endif


}


void TIMER4_voidTimerEnable(void){

	Timer4->CR1.BitAccess.Bit0=1;


}

u8 TIMER4_u8SetDutyCycle(u8 Copy_u8NbOfChannel,u8 Copy_u8DutyValue)
{

	u8 Local_u8ErrorState=STD_TYPES_u8_ERROR_OK;

	if(Copy_u8NbOfChannel > NB_OF_CHANNELS)
	{
		Local_u8ErrorState=STD_TYPES_u8_ERROR_NOK;

	}
	else
	{
		switch(Copy_u8NbOfChannel){

		case TIMER4_CHANNEL_1 :
			Timer4->CCR1.FourByteAccess=((Copy_u8DutyValue * TIMER4_BUFFER) / 100);

			break;

		case TIMER4_CHANNEL_2 :
			Timer4->CCR2.FourByteAccess=((Copy_u8DutyValue * TIMER4_BUFFER) / 100);
			break;

		case TIMER4_CHANNEL_3 :
			Timer4->CCR3.FourByteAccess=((Copy_u8DutyValue * TIMER4_BUFFER) / 100);

			break;

		case TIMER4_CHANNEL_4 :
			Timer4->CCR4.FourByteAccess=((Copy_u8DutyValue * TIMER4_BUFFER) / 100);
			break;
		}
	}

	return Local_u8ErrorState;
}
