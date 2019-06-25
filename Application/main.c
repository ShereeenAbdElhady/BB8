#include "../STD_TYPES.h"
#include "../BIT_CALC.h"
#include "Delay.h"
#include "../include/RCC_interface.h"
#include "../include/DIO_interface.h"
#include "../include/MCU_interface.h"
#include "../include/NVIC_interface.h"
#include "../include/Bluetooth_interface.h"
#include "../include/TIMER_interface.h"
#include "../include/TIMER4_interface.h"
#include "../include/BTS7960_Motor_Driver_interface.h"

/*buffer to transmit data in it        */
//u8 TX_Buffer[] = "1234567890";
/*buffer to store the received string in it */
u8 RX_Buffer[1] ;
u8 right_counter;
u8 left_counter;
u8 CW_counter;
u8 ACW_counter;

void LED (void)
{
	static u8 pin =0;
	pin ^=1;
	///*LED on C14 ON    */
	DIO_u8SetPinValue(DIO_u8_PIN33, pin);

}

void MotorMove (void)
{
	//up (to let moves forward)
	if( (RX_Buffer[0] == 'u') )
	{
		BTS_MOTORDRIVER_u8MotorMove (BTS_MOTORDRIVER_u8_MOTOR1, BTS_MOTORDRIVER_u8_100_SPEED, BTS_MOTORDRIVER_u8_CW_FORWARD);
	}

	//down (to move backward)
	else if( (RX_Buffer[0] == 'd') )
	{
		BTS_MOTORDRIVER_u8MotorMove (BTS_MOTORDRIVER_u8_MOTOR1, BTS_MOTORDRIVER_u8_100_SPEED, BTS_MOTORDRIVER_u8_ACW_BACKWARD);

	}

	//right
	else if( (RX_Buffer[0] == 'r') && (right_counter==0))
	{
		BTS_MOTORDRIVER_u8MotorMove (BTS_MOTORDRIVER_u8_MOTOR1, BTS_MOTORDRIVER_u8_100_SPEED, BTS_MOTORDRIVER_u8_CW_FORWARD);
		BTS_MOTORDRIVER_u8MotorMove (BTS_MOTORDRIVER_u8_MOTOR2, BTS_MOTORDRIVER_u8_100_SPEED, BTS_MOTORDRIVER_u8_CW_FORWARD);
		right_counter++;
	}

	else if ((RX_Buffer[0] == 'r')  && (right_counter != 0))
	{
		BTS_MOTORDRIVER_u8MotorStop(BTS_MOTORDRIVER_u8_MOTOR2);
		right_counter = 0;
	}

	//left
	else if( (RX_Buffer[0] == 'l') && (left_counter==0))
	{
		BTS_MOTORDRIVER_u8MotorMove (BTS_MOTORDRIVER_u8_MOTOR1, BTS_MOTORDRIVER_u8_100_SPEED, BTS_MOTORDRIVER_u8_CW_FORWARD);
		BTS_MOTORDRIVER_u8MotorMove (BTS_MOTORDRIVER_u8_MOTOR2, BTS_MOTORDRIVER_u8_100_SPEED, BTS_MOTORDRIVER_u8_ACW_BACKWARD);
		left_counter++;
	}
	else if ((RX_Buffer[0] == 'l')  && (left_counter != 0))
	{
		BTS_MOTORDRIVER_u8MotorStop(BTS_MOTORDRIVER_u8_MOTOR2);
		left_counter = 0;
	}

	// Rotate clockwise
	else if ((RX_Buffer[0] == 'C') && (CW_counter == 0))
	{
		BTS_MOTORDRIVER_u8MotorStop(BTS_MOTORDRIVER_u8_MOTOR2);
		BTS_MOTORDRIVER_u8MotorStop(BTS_MOTORDRIVER_u8_MOTOR1);

		BTS_MOTORDRIVER_u8MotorMove (BTS_MOTORDRIVER_u8_MOTOR3, BTS_MOTORDRIVER_u8_100_SPEED, BTS_MOTORDRIVER_u8_ACW_BACKWARD);
		delay_milliSecond(1500);
		BTS_MOTORDRIVER_u8MotorMove (BTS_MOTORDRIVER_u8_MOTOR3, BTS_MOTORDRIVER_u8_100_SPEED, BTS_MOTORDRIVER_u8_CW_FORWARD);

		CW_counter++;
	}
	else if ((RX_Buffer[0] == 'C') && (CW_counter != 0))
	{
		BTS_MOTORDRIVER_u8MotorStop(BTS_MOTORDRIVER_u8_MOTOR3);
		CW_counter = 0;
	}

	// Rotate Anti clockwise
	else if ((RX_Buffer[0] == 'A') && (ACW_counter == 0))
	{
		BTS_MOTORDRIVER_u8MotorStop(BTS_MOTORDRIVER_u8_MOTOR2);
		BTS_MOTORDRIVER_u8MotorStop(BTS_MOTORDRIVER_u8_MOTOR1);

		BTS_MOTORDRIVER_u8MotorMove (BTS_MOTORDRIVER_u8_MOTOR3, BTS_MOTORDRIVER_u8_100_SPEED, BTS_MOTORDRIVER_u8_CW_FORWARD);
		delay_milliSecond(1500);
		BTS_MOTORDRIVER_u8MotorMove (BTS_MOTORDRIVER_u8_MOTOR3, BTS_MOTORDRIVER_u8_100_SPEED, BTS_MOTORDRIVER_u8_ACW_BACKWARD);


		ACW_counter++;
	}

	else if ((RX_Buffer[0] == 'A') && (ACW_counter != 0))
	{
		BTS_MOTORDRIVER_u8MotorStop(BTS_MOTORDRIVER_u8_MOTOR3);
		ACW_counter = 0;
	}

	else if( (RX_Buffer[0] == 's') )
	{
		BTS_MOTORDRIVER_u8MotorStop(BTS_MOTORDRIVER_u8_MOTOR3);
		BTS_MOTORDRIVER_u8MotorStop(BTS_MOTORDRIVER_u8_MOTOR2);
		BTS_MOTORDRIVER_u8MotorStop(BTS_MOTORDRIVER_u8_MOTOR1);
	}
	/*call this function again to receive more than one time                                     */
	Bluetooth_u8ReceiveInterrupt(RX_Buffer ,1, &MotorMove);
}

int main (void)
{
	/* INItilaize RCC */
	RCC_vidinit();
	/* enable PORTA clock */
	RCC_u8EnablePeripheralClock(RCC_u8_GPIOA,RCC_u8_ENABLE_CLK);
	/* enable PORTB clock */
	RCC_u8EnablePeripheralClock(RCC_u8_GPIOB,RCC_u8_ENABLE_CLK);
	/* enable PORTC clock */
	RCC_u8EnablePeripheralClock(RCC_u8_GPIOC,RCC_u8_ENABLE_CLK);
	/* enable UART2 clock */
	RCC_u8EnablePeripheralClock(RCC_u8_UART2,RCC_u8_ENABLE_CLK);
	/* enable AFIO clock */
	RCC_u8EnablePeripheralClock(RCC_u8_AFIO,RCC_u8_ENABLE_CLK);
	/* enable TIMER1 clock */
	RCC_u8EnablePeripheralClock(RCC_u8_TIMER1,RCC_u8_ENABLE_CLK);
	/* enable TIMER4 clock */
	RCC_u8EnablePeripheralClock(RCC_u8_TIMER4,RCC_u8_ENABLE_CLK);

	/*A2 (TX) OUTPUT_10MHZ_AF_PUSH_PULL , A3 (RX) INPUT_FLOATING , */
	DIO_vidInitialize();

	/* call this function to set group and sub group numbers to be able to configure the priority */
	MCU_u8SetGroupSubgroup (MCU_u32_SCB_PRIORITY_CONF);

	/* enable UART2 Interrupt                                                                     */
	NVIC_u8SetClearInterruptEnable (NVIC_u8_UART2_INDEX , NVIC_u8_INTERRUPT_ENABLE );
	/* set the priority of UART2                                                                  */
	NVIC_u8SetInterruptPriority (NVIC_u8_UART2_INDEX  , NVIC_u8_UART2_PRIORITY );

	Bluetooth_VidInitialize ();

	TIMER1_voidInitialize();

	TIMER1_voidTimerEnable();

	TIMER4_voidInitialize();

	TIMER4_voidTimerEnable();
	Bluetooth_u8ReceiveInterrupt(RX_Buffer, 1, &MotorMove);
	Bluetooth_u8TransmitInterrupt(RX_Buffer, &LED);


	while (1)
	{

	}
	return 0;
}
