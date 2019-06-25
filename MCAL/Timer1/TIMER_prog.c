/*
 * TIMER_prog.c
 *
 *  Created on: 20 Jun 2019
 *      Author: mahmoud-
 */
#include"../STD_TYPES.h"
#include"../include/TIMER_interface.h"
#include"../include/TIMER_config.h"


void TIMER1_voidInitialize(void)
{



	Timer1->CR1.BitAccess.Bit7=1;

	Timer1->BDTR.BitAccess.Bit15=1;

	Timer1->PSC.FourByteAccess=TIMER1_PRESCALE;
	Timer1->ARR.FourByteAccess=TIMER1_BUFFER;


	#if	Timer1_CHANNEL_1 == Timer1_CHANNEL_ENABLE

		Timer1->CCMR1.BitAccess.Bit6=1;
		Timer1->CCMR1.BitAccess.Bit5=1;
		Timer1->CCMR1.BitAccess.Bit4=0;
		Timer1->CCMR1.BitAccess.Bit3=1;
		Timer1->CCER.BitAccess.Bit0=1;
	#endif

	#if	Timer1_CHANNEL_2 == Timer1_CHANNEL_ENABLE

		Timer1->CCMR1.BitAccess.Bit14=1;
		Timer1->CCMR1.BitAccess.Bit13=1;
		Timer1->CCMR1.BitAccess.Bit12=0;
		Timer1->CCMR1.BitAccess.Bit11=1;
		Timer1->CCER.BitAccess.Bit4=1;

	#endif

	#if		Timer1_CHANNEL_3 == Timer1_CHANNEL_ENABLE

		Timer1->CCMR2.BitAccess.Bit6=1;
		Timer1->CCMR2.BitAccess.Bit5=1;
		Timer1->CCMR2.BitAccess.Bit4=0;
		Timer1->CCMR2.BitAccess.Bit3=1;
		Timer1->CCER.BitAccess.Bit8=1;
	#endif

#if		Timer1_CHANNEL_4 == Timer1_CHANNEL_ENABLE

		Timer1->CCMR2.BitAccess.Bit14=1;
		Timer1->CCMR2.BitAccess.Bit13=1;
		Timer1->CCMR2.BitAccess.Bit12=0;
		Timer1->CCMR2.BitAccess.Bit11=1;
		Timer1->CCER.BitAccess.Bit12=1;
	#endif


}


void TIMER1_voidTimerEnable(void)
{
	Timer1->CR1.BitAccess.Bit0=1;
}


u8 TIMER1_u8SetDutyCycle(u8 Copy_u8NbOfChannel,u8 Copy_u8DutyValue){

	u8 Local_u8ErrorState=STD_TYPES_u8_ERROR_OK;

	if(Copy_u8NbOfChannel > NB_OF_CHANNELS){
		Local_u8ErrorState=STD_TYPES_u8_ERROR_NOK;

	}
	else{


		switch(Copy_u8NbOfChannel){

		case TIMER1_CHANNEL_1 :
			Timer1->CCR1.FourByteAccess=((Copy_u8DutyValue * TIMER1_BUFFER) / 100);

			break;

		case TIMER1_CHANNEL_2 :
			Timer1->CCR2.FourByteAccess=((Copy_u8DutyValue * TIMER1_BUFFER) / 100);
			break;

		case TIMER1_CHANNEL_3 :
			Timer1->CCR3.FourByteAccess=((Copy_u8DutyValue * TIMER1_BUFFER) / 100);

			break;

		case TIMER1_CHANNEL_4 :
			Timer1->CCR4.FourByteAccess=((Copy_u8DutyValue * TIMER1_BUFFER) / 100);
			break;



		}
	}

return Local_u8ErrorState;
}
