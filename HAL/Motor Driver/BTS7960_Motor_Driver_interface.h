/****************************************************************************************/
/*                                                                                     */
/* File Name   : BTS7960 Motor Driver_interface.h                                     */
/*                                                                                   */
/* Created on  : Apr 29, 2019                                                       */
/*                                                                                 */
/* Author      : Mariam Ahmed & shereen Abd Elhady                                */
/*                                                                               */
/* Version     : V01                                                            */
/*                                                                             */
/* Description : Interface file for BTS7960 DC MOTOR driver includes APIs'    */
/*                                                                           */
/*             prototypes And MACROS for call                               */
/*                                                                         */
/* Layer       : HAL                                                      */
/*                                                                       */
/************************************************************************/

#ifndef BTS7960_MOTOR_DRIVER_INTERFACE_H_
#define BTS7960_MOTOR_DRIVER_INTERFACE_H_

/* 	The interface file includes only the Public configurations from the configuration file   */

/*Motors' indecies definitions to be used by the user                                        */
#define BTS_MOTORDRIVER_u8_MOTOR1         (u8)0
#define BTS_MOTORDRIVER_u8_MOTOR2         (u8)1
#define BTS_MOTORDRIVER_u8_MOTOR3         (u8)2

/* Direction of rotation definitions where it moves forward when the motor rotates clockwise */
/* And moves backward when the motor rotates in anti clockwise direction                     */
#define BTS_MOTORDRIVER_u8_CW_FORWARD     (u8)1
#define BTS_MOTORDRIVER_u8_ACW_BACKWARD   (u8)0

/*Different speeds' definitions each speed is equivalent to a Duty cycle percentage generated*/
/* From Timers' peripheral                                                                   */
#define BTS_MOTORDRIVER_u8_0_SPEED       (u8)0
#define BTS_MOTORDRIVER_u8_20_SPEED      (u8)20
#define BTS_MOTORDRIVER_u8_25_SPEED      (u8)25
#define BTS_MOTORDRIVER_u8_50_SPEED      (u8)50
#define BTS_MOTORDRIVER_u8_75_SPEED      (u8)75
#define BTS_MOTORDRIVER_u8_100_SPEED     (u8)100

     /*********************************** APIs Prototypes ************************************/

/************************************************************************************
 * Description: Function to stop the motor's movement
 * Outputs    : Error state
 * Inputs     : u8 Copy_u8MotorIndex : index of the motor
 *************************************************************************************/
u8 BTS_MOTORDRIVER_u8MotorStop (u8 Copy_u8MotorIndex);


/************************************************************************************
 * Description: Function to control motor's movements whether it's gonna move forward
 *              Or in backward direction. Also to control the motor's speed.
 * Outputs    : Error state
 * Inputs     : u8 Copy_u8MotorIndex    : index of the motor.
 *              u8 Copy_u8MotorSpeed    : speed of the motor.
 *              u8 Copy_u8MotorDirection: rotation direction for the motor.
 *************************************************************************************/
u8 BTS_MOTORDRIVER_u8MotorMove (u8 Copy_u8MotorIndex, u8 Copy_u8MotorSpeed, u8 Copy_u8MotorDirection);



#endif /* BTS7960_MOTOR_DRIVER_INTERFACE_H_ */
