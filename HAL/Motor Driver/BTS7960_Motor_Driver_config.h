/*
 * Motor_Driver_Config.h
 *
 *  Created on: 15 Jun 2019
 *      Author: mahmoud-
 */

#ifndef BTS7960_MOTOR_DRIVER_CONFIG_H_
#define BTS7960_MOTOR_DRIVER_CONFIG_H_


/* The configurator will configure the number of motors according to the customer desire      */
#define BTS_MOTORDRIVER_u8_NO_MOTORS     (u8)3


/* 2D Array includes number of motors and the number of enable PINs to enable these motors    */
/* So that the configurator will configure each motor connected  to which L & R enable PINs   */
/* From the microcontroller GPIO PINs                                                         */
/* Range:            (LEN)                                (REN)                               */
/*        BTS_MOTORDRIVER_u8_LEN16                 BTS_MOTORDRIVER_u8_REN24                   */
/*        BTS_MOTORDRIVER_u8_LEN17                 BTS_MOTORDRIVER_u8_REN25                   */
/*        BTS_MOTORDRIVER_u8_LEN18                 BTS_MOTORDRIVER_u8_REN26                   */
/*        BTS_MOTORDRIVER_u8_LEN19                 BTS_MOTORDRIVER_u8_REN27                   */
/*        BTS_MOTORDRIVER_u8_LEN20                 BTS_MOTORDRIVER_u8_REN28                   */
/*        BTS_MOTORDRIVER_u8_LEN21                 BTS_MOTORDRIVER_u8_REN29                   */
/*        BTS_MOTORDRIVER_u8_LEN22                 BTS_MOTORDRIVER_u8_REN30                   */
/*        BTS_MOTORDRIVER_u8_LEN23                 BTS_MOTORDRIVER_u8_REN31                   */
u8 BTS_MOTORDRIVER_Au8EnablePins[BTS_MOTORDRIVER_u8_NO_MOTORS][BTS_MOTORDRIVER_u8_NO_ENABLE_PINS]
		= { {BTS_MOTORDRIVER_u8_LEN0 , BTS_MOTORDRIVER_u8_REN0},
            {BTS_MOTORDRIVER_u8_LEN1 , BTS_MOTORDRIVER_u8_REN1},
			{BTS_MOTORDRIVER_u8_LEN2 , BTS_MOTORDRIVER_u8_REN2}
          };


/* 2D Array includes number of motors and the number of PWM PINs to these motors              */
/* So that the configurator will configure each motor connected  to which L & R PWM PINs      */
/* From the microcontroller GPIO PINs                                                         */
/* Range:            (LPWM)                                (RPWM)                             */
/*        BTS_MOTORDRIVER_u8_LPWM0                 BTS_MOTORDRIVER_u8_RPWM8                   */
/*        BTS_MOTORDRIVER_u8_LPWM1                 BTS_MOTORDRIVER_u8_RPWM9                   */
/*        BTS_MOTORDRIVER_u8_LPWM2                 BTS_MOTORDRIVER_u8_RPWM10                  */
/*        BTS_MOTORDRIVER_u8_LPWM3                 BTS_MOTORDRIVER_u8_RPWM11                  */
/*        BTS_MOTORDRIVER_u8_LPWM4                 BTS_MOTORDRIVER_u8_RPWM12                  */
/*        BTS_MOTORDRIVER_u8_LPWM5                 BTS_MOTORDRIVER_u8_RPWM13                  */
/*        BTS_MOTORDRIVER_u8_LPWM6                 BTS_MOTORDRIVER_u8_RPWM14                  */
/*        BTS_MOTORDRIVER_u8_LPWM7                 BTS_MOTORDRIVER_u8_RPWM15                  */
// u8 BTS_MOTORDRIVER_Au8PwmPins[BTS_MOTORDRIVER_u8_NO_MOTORS][BTS_MOTORDRIVER_u8_NO_PWM_PINS]
	//	= { {BTS_MOTORDRIVER_u8_LPWM0 , BTS_MOTORDRIVER_u8_RPWM0},
      //      {BTS_MOTORDRIVER_u8_LPWM1 , BTS_MOTORDRIVER_u8_RPWM1}
        //  };

#endif /* BTS7960_MOTOR_DRIVER_CONFIG_H_ */
