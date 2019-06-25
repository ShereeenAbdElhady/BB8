/**************************************************************************************************/
/*                                                                                               */
/* File Name   : BTS7960 Motor Driver_private.h                                                 */
/*                                                                                             */
/* Created on  : Apr 29, 2019                                                                 */
/*                                                                                           */
/* Author      : Mariam Ahmed & shereen Abd Elhady                                          */
/*                                                                                         */
/* Version     : V01                                                                      */
/*                                                                                       */
/* Description : Private header file for BTS7960 DC Motor driver                        */
/*               which contains private functions' prototypes                          */
/*               And the MACROS not needed by the upper layers' components.           */
/*                                                                                   */
/* Layer        : HAL                                                               */
/*                                                                                 */
/**********************************************************************************/


#ifndef BTS7960_MOTOR_DRIVER_PRIVATE_H_
#define BTS7960_MOTOR_DRIVER_PRIVATE_H_


/* Enable PINs numbers' definition where this motor driver has TWO enable PINs                */
/* LEN -> Left enable , REN -> Right enable to enable the PWM signal to enter the motor       */
#define BTS_MOTORDRIVER_u8_NO_ENABLE_PINS   (u8)2

/* PWM PINs numbers' definition where this motor driver has TWO PWM PINs                      */
/* LPWM -> Left PWM, RPWM -> Right PWM to control the motor's direction of rotation(CW , ACW) */
#define BTS_MOTORDRIVER_u8_NO_PWM_PINS      (u8)2

/* I forced the configurator to use specific PINs for LEN, REN, LPWM and RPWM                 */
/* To prevent him from configuring the same GPIO PIN number for two different Motor driver PINs*/
/* So i divided the GPIO PINs into 4 groups                                                   */

/* BTS7960 Motor driver's left PWM PIN definitions                                            */
/*
#define BTS_MOTORDRIVER_u8_LPWM0   DIO_u8_PIN0
#define BTS_MOTORDRIVER_u8_LPWM1   DIO_u8_PIN1
#define BTS_MOTORDRIVER_u8_LPWM2   DIO_u8_PIN2
#define BTS_MOTORDRIVER_u8_LPWM3   DIO_u8_PIN3
#define BTS_MOTORDRIVER_u8_LPWM4   DIO_u8_PIN4
#define BTS_MOTORDRIVER_u8_LPWM5   DIO_u8_PIN5
#define BTS_MOTORDRIVER_u8_LPWM6   DIO_u8_PIN6
#define BTS_MOTORDRIVER_u8_LPWM7   DIO_u8_PIN7
*/

/* BTS7960 Motor driver's Right PWM PIN definitions                                          */
/*
#define BTS_MOTORDRIVER_u8_LPWM0    DIO_u8_PIN9
#define BTS_MOTORDRIVER_u8_RPWM0    DIO_u8_PIN8
#define BTS_MOTORDRIVER_u8_LEN0     DIO_u8_PIN0
#define BTS_MOTORDRIVER_u8_REN0     DIO_u8_PIN1

#define BTS_MOTORDRIVER_u8_LPWM1    DIO_u8_PIN11
#define BTS_MOTORDRIVER_u8_RPWM1    DIO_u8_PIN10
#define BTS_MOTORDRIVER_u8_LEN1     DIO_u8_PIN2
#define BTS_MOTORDRIVER_u8_REN1     DIO_u8_PIN3
*/

/* BTS7960 Motor driver's left enable PIN definitions                                        */

#define BTS_MOTORDRIVER_u8_LEN0   DIO_u8_PIN0
#define BTS_MOTORDRIVER_u8_LEN1   DIO_u8_PIN4
#define BTS_MOTORDRIVER_u8_LEN2   DIO_u8_PIN6
/*
#define BTS_MOTORDRIVER_u8_LEN18  DIO_u8_PIN18
#define BTS_MOTORDRIVER_u8_LEN19  DIO_u8_PIN19
#define BTS_MOTORDRIVER_u8_LEN20  DIO_u8_PIN20
#define BTS_MOTORDRIVER_u8_LEN21  DIO_u8_PIN21
#define BTS_MOTORDRIVER_u8_LEN22  DIO_u8_PIN22
#define BTS_MOTORDRIVER_u8_LEN23  DIO_u8_PIN23
*/

/* BTS7960 Motor driver's right enable PIN definitions                                       */
#define BTS_MOTORDRIVER_u8_REN0   DIO_u8_PIN1
#define BTS_MOTORDRIVER_u8_REN1   DIO_u8_PIN5
#define BTS_MOTORDRIVER_u8_REN2   DIO_u8_PIN7
/*
#define BTS_MOTORDRIVER_u8_REN26  DIO_u8_PIN26
#define BTS_MOTORDRIVER_u8_REN27  DIO_u8_PIN27
#define BTS_MOTORDRIVER_u8_REN28  DIO_u8_PIN28
#define BTS_MOTORDRIVER_u8_REN29  DIO_u8_PIN29
#define BTS_MOTORDRIVER_u8_REN30  DIO_u8_PIN30
#define BTS_MOTORDRIVER_u8_REN31  DIO_u8_PIN31
 */


/* Initial direction of rotation definitions where it moves forward when the motor rotates CW */
/* And moves backward when the motor rotates in anti clockwise direction                      */
#define BTS_MOTORDRIVER_u8_INIT_CW        (u8)9
#define BTS_MOTORDRIVER_u8_INIT_ACW       (u8)10

/* Initial Motor state definitions where the motor is ON or OFF                              */
#define BTS_MOTORDRIVER_u8_INIT_STATE_ON   12
#define BTS_MOTORDRIVER_u8_INIT_STATE_OFF  13

/*Motor's Maximum speed definition                                                           */
#define BTS_MOTORDRIVER_u8_MAX_SPEED     (u8)100

/*Motor driver enable PINs values definitions                                                */
#define BTS_MOTORDRIVER_u8_ENABLE_HIGH   (u8)1
#define BTS_MOTORDRIVER_u8_ENABLE_LOW    (u8)0

/*LEN & REN PINs index in the 2D array where the LEN has index 0 & REN has index 1           */
#define BTS_MOTORDRIVER_u8_LEN_INDEX     (u8)0
#define BTS_MOTORDRIVER_u8_REN_INDEX     (u8)1

/*LPWM & RPWM PINs index in the 2D array where the LPWM has index 0 & RPWM has index 1       */
#define BTS_MOTORDRIVER_u8_LPWM_INDEX     (u8)0
#define BTS_MOTORDRIVER_u8_RPWM_INDEX     (u8)1

/* 	The Private file includes only the Private configurations from the configuration file    */


/*********************************** private functions Prototypes ************************************/

/**********************************************************************************
 * Description: Function to fill the array of ON motors flags
 *              and fill the array of set motors' direction of rotation
 *              according to the defined initial motor state whether it was ON or OFF
 *              and the initial direction.
 * Outputs    : None
 * Inputs     : None
 **********************************************************************************/


/**************************************************************************************
 * Description: Function to set motor's direction of rotation to clockwise direction
 *              to move the motor in forward direction.
 * Outputs    : Error state
 * Inputs     : u8 Copy_u8MotorIndex : index of the motor
 *              u8 Copy_u8MotorSpeed    : speed of the motor.
 **************************************************************************************/
static void BTS_MOTORDRIVER_u8MotorRotateClockWise(u8 Copy_u8MotorIndex , u8 Copy_u8MotorSpeed);


/**************************************************************************************
 * Description: Function to set motor's direction of rotation to anti clockwise direction
 *              to move the motor in backward direction.
 * Outputs    : Error state
 * Inputs     : u8 Copy_u8MotorIndex : index of the motor
 *              u8 Copy_u8MotorSpeed    : speed of the motor.
 **************************************************************************************/
static void BTS_MOTORDRIVER_u8MotorRotateAntiClockWise(u8 Copy_u8MotorIndex , u8 Copy_u8MotorSpeed);

#endif /* BTS7960_MOTOR_DRIVER_PRIVATE_H_ */
