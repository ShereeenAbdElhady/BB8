/*
 * Servo_prog.c
 *
 *  Created on: 22 Jun 2019
 *      Author: mahmoud-
 */


#include"BIT_CALC.h"
#include"STD_TYPES.h"
#include"TIMER4_interface.h"
#include"Servo_interface.h"




static void Servo1_voidSetAngle(u8 Copy_u8Angle);

static void Servo2_voidSetAngle(u8 Copy_u8Angle);
static void Servo3_voidSetAngle(u8 Copy_u8Angle);

u8 SERVO_u8SetAngle(u8 Copy_u8ServoNb, u8 Copy_u8Angle){

	u8 Local_u8ErrorState=STD_TYPES_u8_ERROR_OK;
	if(Copy_u8ServoNb > MAX_NB_OF_SERVO){

		Local_u8ErrorState=STD_TYPES_u8_ERROR_NOK;

	}

	else{


		switch(Copy_u8ServoNb){


		case SERVO_1 :
			Servo1_voidSetAngle(Copy_u8Angle);

			break;

		case SERVO_2:
			Servo2_voidSetAngle(Copy_u8Angle);
			break;

		case SERVO_3:
			Servo3_voidSetAngle(Copy_u8Angle);
			break;

		}


	}

return Local_u8ErrorState;

}


static void Servo1_voidSetAngle(u8 Copy_u8Angle){

	switch(Copy_u8Angle){

	case SERVO_ANGLE0 :
		TIMER4_u8SetDutyCycle(TIMER4_CHANNEL_1,3);
		break;

	case SERVO_ANGLE90 :
		TIMER4_u8SetDutyCycle(TIMER4_CHANNEL_1,8);
		break;

	case SERVO_ANGLE180 :
		TIMER4_u8SetDutyCycle(TIMER4_CHANNEL_1,12);
		break;
	}


}

static void Servo2_voidSetAngle(u8 Copy_u8Angle){

	switch(Copy_u8Angle){

	case SERVO_ANGLE0 :
		TIMER4_u8SetDutyCycle(TIMER4_CHANNEL_2,3);
		break;

	case SERVO_ANGLE90 :
		TIMER4_u8SetDutyCycle(TIMER4_CHANNEL_2,8);
		break;

	case SERVO_ANGLE180 :
		TIMER4_u8SetDutyCycle(TIMER4_CHANNEL_2,12);
		break;
	}


}
static void Servo3_voidSetAngle(u8 Copy_u8Angle){

	switch(Copy_u8Angle){

	case SERVO_ANGLE0 :
		TIMER4_u8SetDutyCycle(TIMER4_CHANNEL_3,3);
		break;

	case SERVO_ANGLE90 :
		TIMER4_u8SetDutyCycle(TIMER4_CHANNEL_3,8);
		break;

	case SERVO_ANGLE180 :
		TIMER4_u8SetDutyCycle(TIMER4_CHANNEL_3,12);
		break;
	}


}
