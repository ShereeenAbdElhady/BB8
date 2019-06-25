/**********************************************************************************/
/*                                                                               */
/* File Name   : BTS7960 Motor Driver_prog.c                                    */
/*                                                                             */
/* Created on  : Apr 29, 2019                                                 */
/*                                                                           */
/* Author      : Mariam Ahmed & shereen Abd Elhady                          */
/*                                                                         */
/* Version     : V01                                                      */
/*                                                                       */
/* Description : software driver for BTS7960 DC motor driver to control */
/*               it's direction of rotation, speed and it's state      */
/*               with a defined public and private function           */
/*                                                                   */
/* Layer       : HAL                                                */
/*******************************************************************/

#include "../STD_TYPES.h"
#include "../BIT_CALC.h"
#include"../include/Delay.h"
#include "../include/DIO_interface.h"
#include "../include/TIMER_interface.h"
#include "../include/TIMER4_interface.h"
#include "../include/BTS7960_Motor_Driver_interface.h"
#include "../include/BTS7960_Motor_Driver_private.h"
#include "../include/BTS7960_Motor_Driver_config.h"





/* Array of flags used as an indication for the ON motors                                    */
//static u8 BTS_MOTORDRIVER_Au8MotorsONFlag[BTS_MOTORDRIVER_u8_NO_MOTORS ];
/* Array to set the rotation direction of the motors                                         */
static u8 BTS_MOTORDRIVER_Au8MotorsSetDirection[BTS_MOTORDRIVER_u8_NO_MOTORS];


/************************************************************************************
 * Description: Function to stop the motor's movement
 * Outputs    : Error state
 * Inputs     : u8 Copy_u8MotorIndex : index of the motor
 *************************************************************************************/
u8 BTS_MOTORDRIVER_u8MotorStop (u8 Copy_u8MotorIndex)
{
	/* Local Variable indication for Error status                                            */
	u8 Local_u8Error = STD_TYPES_u8_ERROR_OK;
	/* Input arguments validation                                                            */
	if (Copy_u8MotorIndex > BTS_MOTORDRIVER_u8_NO_MOTORS)
	{
		Local_u8Error = STD_TYPES_u8_ERROR_NOK;
	}
	else
	{
		/*alley l duty cycle till ywsl llzero mn driver bta3 MINAAAA 3shan my2fsh mra whda*/
		/*To deactivate the motor driver you have to set the left OR the right enable PINs   */
		/*  with LOW value                                                                   */
		DIO_u8SetPinValue(BTS_MOTORDRIVER_Au8EnablePins[Copy_u8MotorIndex][BTS_MOTORDRIVER_u8_REN_INDEX], BTS_MOTORDRIVER_u8_ENABLE_HIGH);
		DIO_u8SetPinValue(BTS_MOTORDRIVER_Au8EnablePins[Copy_u8MotorIndex][BTS_MOTORDRIVER_u8_LEN_INDEX], BTS_MOTORDRIVER_u8_ENABLE_LOW);
	}
	/* Function Return                                                                       */
	return Local_u8Error;
}


/************************************************************************************
 * Description: Function to control motor's movements whether it's gonna move forward
 *              Or in backward direction. Also to control the motor's speed.
 * Outputs    : Error state
 * Inputs     : u8 Copy_u8MotorIndex    : index of the motor.
 *              u8 Copy_u8MotorSpeed    : speed of the motor.
 *              u8 Copy_u8MotorDirection: rotation direction for the motor.
 *************************************************************************************/
u8 BTS_MOTORDRIVER_u8MotorMove (u8 Copy_u8MotorIndex, u8 Copy_u8MotorSpeed, u8 Copy_u8MotorDirection)
{
	/* Local Variable indication for Error status                                            */
	u8 Local_u8Error = STD_TYPES_u8_ERROR_OK;
	/* Input arguments validation                                                            */
	if ((Copy_u8MotorIndex > BTS_MOTORDRIVER_u8_NO_MOTORS) && (Copy_u8MotorSpeed > BTS_MOTORDRIVER_u8_MAX_SPEED))
	{
		Local_u8Error = STD_TYPES_u8_ERROR_NOK;
	}
	else
	{

		/*check for the sent direction                                                       */
		switch(Copy_u8MotorDirection)
		{
		/*in case it's forward                                                               */
		case BTS_MOTORDRIVER_u8_CW_FORWARD:
			/*call the clockwise function                                                    */
			BTS_MOTORDRIVER_u8MotorRotateClockWise(Copy_u8MotorIndex , Copy_u8MotorSpeed);
			break;
			/*in case it's backward                                                          */
		case  BTS_MOTORDRIVER_u8_ACW_BACKWARD:
			/*call the anti clockwise function                                               */
			BTS_MOTORDRIVER_u8MotorRotateAntiClockWise(Copy_u8MotorIndex , Copy_u8MotorSpeed);
			break;
			/*neither CW nor ACW then return an error and this is considered as input validation*/
		default: Local_u8Error = STD_TYPES_u8_ERROR_NOK;
		break;
		}
	}
	/* Function Return */
	return Local_u8Error;
}


/**************************************************************************************
 * Description: Function to set motor's direction of rotation to clockwise direction
 *              to move the motor in forward direction.
 * Outputs    : Error state
 * Inputs     : u8 Copy_u8MotorIndex : index of the motor
 *              u8 Copy_u8MotorSpeed    : speed of the motor.
 **************************************************************************************/
static void BTS_MOTORDRIVER_u8MotorRotateClockWise(u8 Copy_u8MotorIndex , u8 Copy_u8MotorSpeed)
{
	/* if the motor was rotating in the anti clockwise direction                             */
	if ((BTS_MOTORDRIVER_Au8MotorsSetDirection[Copy_u8MotorIndex] == BTS_MOTORDRIVER_u8_ACW_BACKWARD)
			&& (Copy_u8MotorIndex != BTS_MOTORDRIVER_u8_MOTOR3))
	{
		/*call motor stop function to stop the motor for 500ms                               */
		BTS_MOTORDRIVER_u8MotorStop(Copy_u8MotorIndex);
		delay_milliSecond(10000);
	}


	/*set the array of motors' directions with clockwise direction                           */
	BTS_MOTORDRIVER_Au8MotorsSetDirection[Copy_u8MotorIndex] = BTS_MOTORDRIVER_u8_CW_FORWARD;

	/*initiate the RPWM PIN with PWM signal mn timer driver bta3 MINAAA                      */
	/*change the duty cycle gradually till reaching the required speed                       */
	/*y3ny adelo PWM B duty cycle so8yra w tfdl tkbr 3shan l motor mysht8lsh mra whda        */
	switch (Copy_u8MotorIndex)
	{
	case BTS_MOTORDRIVER_u8_MOTOR1:
		/*To activate the motor driver you have to set the left & right enable PINs with high    */
		DIO_u8SetPinValue(BTS_MOTORDRIVER_Au8EnablePins[Copy_u8MotorIndex][BTS_MOTORDRIVER_u8_LEN_INDEX], BTS_MOTORDRIVER_u8_ENABLE_HIGH);
		DIO_u8SetPinValue(BTS_MOTORDRIVER_Au8EnablePins[Copy_u8MotorIndex][BTS_MOTORDRIVER_u8_REN_INDEX], BTS_MOTORDRIVER_u8_ENABLE_HIGH);

		TIMER1_u8SetDutyCycle(TIMER1_CHANNEL_1, Copy_u8MotorSpeed);
		TIMER1_u8SetDutyCycle(TIMER1_CHANNEL_2, 0);
		break;

	case BTS_MOTORDRIVER_u8_MOTOR2:
		/*To activate the motor driver you have to set the left & right enable PINs with high    */
		DIO_u8SetPinValue(BTS_MOTORDRIVER_Au8EnablePins[Copy_u8MotorIndex][BTS_MOTORDRIVER_u8_LEN_INDEX], BTS_MOTORDRIVER_u8_ENABLE_HIGH);
		DIO_u8SetPinValue(BTS_MOTORDRIVER_Au8EnablePins[Copy_u8MotorIndex][BTS_MOTORDRIVER_u8_REN_INDEX], BTS_MOTORDRIVER_u8_ENABLE_HIGH);

		TIMER1_u8SetDutyCycle(TIMER1_CHANNEL_3, Copy_u8MotorSpeed);
		TIMER1_u8SetDutyCycle(TIMER1_CHANNEL_4, 0);
		break;

	case BTS_MOTORDRIVER_u8_MOTOR3:
		/*To activate the motor driver you have to set the left & right enable PINs with high    */
		DIO_u8SetPinValue(BTS_MOTORDRIVER_Au8EnablePins[Copy_u8MotorIndex][BTS_MOTORDRIVER_u8_LEN_INDEX], BTS_MOTORDRIVER_u8_ENABLE_HIGH);
		DIO_u8SetPinValue(BTS_MOTORDRIVER_Au8EnablePins[Copy_u8MotorIndex][BTS_MOTORDRIVER_u8_REN_INDEX], BTS_MOTORDRIVER_u8_ENABLE_HIGH);

		TIMER4_u8SetDutyCycle(TIMER4_CHANNEL_1, Copy_u8MotorSpeed);
		TIMER4_u8SetDutyCycle(TIMER4_CHANNEL_2, 0);
		break;
	}
}


/**************************************************************************************
 * Description: Function to set motor's direction of rotation to anti clockwise direction
 *              to move the motor in backward direction.
 * Outputs    : Error state
 * Inputs     : u8 Copy_u8MotorIndex : index of the motor
 *              u8 Copy_u8MotorSpeed    : speed of the motor.
 **************************************************************************************/
static void BTS_MOTORDRIVER_u8MotorRotateAntiClockWise(u8 Copy_u8MotorIndex , u8 Copy_u8MotorSpeed)
{
	/* if the motor was rotating in the clockwise direction                                  */
	if ( (BTS_MOTORDRIVER_Au8MotorsSetDirection[Copy_u8MotorIndex] == BTS_MOTORDRIVER_u8_CW_FORWARD)
			&& (Copy_u8MotorIndex != BTS_MOTORDRIVER_u8_MOTOR3))
	{
		/*call motor stop function to stop the motor for 500ms                               */
		BTS_MOTORDRIVER_u8MotorStop (Copy_u8MotorIndex);
		delay_milliSecond(10000);
	}

	/*set the array of motors' directions with Anti clockwise direction                      */
	BTS_MOTORDRIVER_Au8MotorsSetDirection[Copy_u8MotorIndex] = BTS_MOTORDRIVER_u8_ACW_BACKWARD;

	/*initiate the LPWM PIN with PWM signal mn timer driver bta3 MINAAA                      */
	/*change the duty cycle gradually till reaching the required speed                       */
	/*y3ny adelo PWM B duty cycle so8yra w tfdl tkbr 3shan l motor mysht8lsh mra whda        */
	switch (Copy_u8MotorIndex)
	{
	case BTS_MOTORDRIVER_u8_MOTOR1:
		/*To activate the motor driver you have to set the left & right enable PINs with high    */
		DIO_u8SetPinValue(BTS_MOTORDRIVER_Au8EnablePins[Copy_u8MotorIndex][BTS_MOTORDRIVER_u8_LEN_INDEX], BTS_MOTORDRIVER_u8_ENABLE_HIGH);
		DIO_u8SetPinValue(BTS_MOTORDRIVER_Au8EnablePins[Copy_u8MotorIndex][BTS_MOTORDRIVER_u8_REN_INDEX], BTS_MOTORDRIVER_u8_ENABLE_HIGH);

		TIMER1_u8SetDutyCycle(TIMER1_CHANNEL_1, 0);
		TIMER1_u8SetDutyCycle(TIMER1_CHANNEL_2, Copy_u8MotorSpeed);
		break;

	case BTS_MOTORDRIVER_u8_MOTOR2:
		/*To activate the motor driver you have to set the left & right enable PINs with high    */
		DIO_u8SetPinValue(BTS_MOTORDRIVER_Au8EnablePins[Copy_u8MotorIndex][BTS_MOTORDRIVER_u8_LEN_INDEX], BTS_MOTORDRIVER_u8_ENABLE_HIGH);
		DIO_u8SetPinValue(BTS_MOTORDRIVER_Au8EnablePins[Copy_u8MotorIndex][BTS_MOTORDRIVER_u8_REN_INDEX], BTS_MOTORDRIVER_u8_ENABLE_HIGH);

		TIMER1_u8SetDutyCycle(TIMER1_CHANNEL_3, 0);
		TIMER1_u8SetDutyCycle(TIMER1_CHANNEL_4, Copy_u8MotorSpeed);
		break;

	case BTS_MOTORDRIVER_u8_MOTOR3:
		/*To activate the motor driver you have to set the left & right enable PINs with high    */
		DIO_u8SetPinValue(BTS_MOTORDRIVER_Au8EnablePins[Copy_u8MotorIndex][BTS_MOTORDRIVER_u8_LEN_INDEX], BTS_MOTORDRIVER_u8_ENABLE_HIGH);
		DIO_u8SetPinValue(BTS_MOTORDRIVER_Au8EnablePins[Copy_u8MotorIndex][BTS_MOTORDRIVER_u8_REN_INDEX], BTS_MOTORDRIVER_u8_ENABLE_HIGH);

		TIMER4_u8SetDutyCycle(TIMER4_CHANNEL_1, 0);
		TIMER4_u8SetDutyCycle(TIMER4_CHANNEL_2, Copy_u8MotorSpeed);
		break;
	}

}


///**********************************************************************************
// * Description: Function to fill the array of ON motors flags
// *              and fill the array of set motors' direction of rotation
// *              according to the defined initial motor state whether it was ON or OFF
// *              and the initial direction.
// * Outputs    : None
// * Inputs     : None
// **********************************************************************************/
//static void BTS_MOTORDRIVER_VidMotorInitialize (void)
//{
//	/* index to loop through a number of motors                                              */
//	u8 Local_u8LoopIndex;
//	/* For loop to go through a number of motors and check for their initial direction       */
//	/* Of rotation to fill the set direction array, also to check for their initial state    */
//	/* to fill the array of ON flags                                                         */
//	for (Local_u8LoopIndex = 0 ; Local_u8LoopIndex < BTS_MOTORDRIVER_u8_NO_MOTORS  ; Local_u8LoopIndex++)
//	{
//		/*if The initial state of motor was OFF the check for the initial direction          */
//		if (BTS_MOTORDRIVER_Au8MotorInitState[Local_u8LoopIndex ] == BTS_MOTORDRIVER_u8_INIT_STATE_OFF)
//		{
//			/*fill the array of ON motors with zero as an indication that this motor is OFF  */
//			BTS_MOTORDRIVER_Au8MotorsONFlag[Local_u8LoopIndex] = 0;
//			/*if the initial direction was clockwise                                         */
//			if(BTS_MOTORDRIVER_Au8MotorInitDirection[Local_u8LoopIndex] == BTS_MOTORDRIVER_u8_INIT_CW)
//			{
//				/*set the array of motors' directions with clockwise direction               */
//				BTS_MOTORDRIVER_Au8MotorsSetDirection[Local_u8LoopIndex] = BTS_MOTORDRIVER_u8_CW_FORWARD;
//			}
//			/*if the initial direction was anti clockwise                                    */
//			else if(BTS_MOTORDRIVER_Au8MotorInitDirection[Local_u8LoopIndex] == BTS_MOTORDRIVER_u8_INIT_ACW)
//			{
//				/*set the array of motors' directions with anti clockwise direction          */
//				BTS_MOTORDRIVER_Au8MotorsSetDirection[Local_u8LoopIndex] = BTS_MOTORDRIVER_u8_ACW_BACKWARD;
//			}
//		}
//		/*if The initial state of motor was ON the check for the initial direction           */
//		else if (BTS_MOTORDRIVER_Au8MotorInitState[Local_u8LoopIndex ] == BTS_MOTORDRIVER_u8_INIT_STATE_ON)
//		{
//			/*fill the array of ON motors with one as an indication that this motor is ON    */
//			BTS_MOTORDRIVER_Au8MotorsONFlag[Local_u8LoopIndex] = 1;
//			/*if the initial direction was clockwise                                         */
//			if(BTS_MOTORDRIVER_Au8MotorInitDirection[Local_u8LoopIndex] == BTS_MOTORDRIVER_u8_INIT_CW)
//			{
//				/*set the array of motors' directions with clockwise direction               */
//				BTS_MOTORDRIVER_Au8MotorsSetDirection[Local_u8LoopIndex] = BTS_MOTORDRIVER_u8_CW_FORWARD;
//			}
//			/*if the initial direction was anti clockwise                                    */
//			else if(BTS_MOTORDRIVER_Au8MotorInitDirection[Local_u8LoopIndex] == BTS_MOTORDRIVER_u8_INIT_ACW)
//			{
//				/*set the array of motors' directions with anti clockwise direction          */
//				BTS_MOTORDRIVER_Au8MotorsSetDirection[Local_u8LoopIndex] = BTS_MOTORDRIVER_u8_ACW_BACKWARD;
//			}
//		}
//	}
//}


