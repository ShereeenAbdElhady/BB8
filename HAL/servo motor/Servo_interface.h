/*
 * Servo_interface.h
 *
 *  Created on: 22 Jun 2019
 *      Author: mahmoud-
 */

#ifndef SERVO_INTERFACE_H_
#define SERVO_INTERFACE_H_

#define MAX_NB_OF_SERVO		(u8)3

#define SERVO_1			(u8)0

#define SERVO_2				(u8)1

#define SERVO_3				(u8)2

#define SERVO_ANGLE0		(u8)0

#define SERVO_ANGLE90		(u8)1

#define SERVO_ANGLE180		(u8)2

u8 SERVO_u8SetAngle(u8 Copy_u8ServoNb, u8 Copy_Angle);



#endif /* SERVO_INTERFACE_H_ */
