/******************************************************************************************/
/*                                                                                       */
/* File Name   : Bluetooth_prog.c                                                       */
/*                                                                                     */
/* Created on  : Jun 18, 2019                                                         */
/*                                                                                   */
/* Author      : Mariam Ahmed & shereen Abd Elhady                                  */
/*                                                                                 */
/* Version     : V01                                                              */
/*                                                                               */
/* Description : software driver for Bluetooth module includes transmitting     */
/*               And receiving function using polling & interrupt mechanism    */
/*               the implementation of this driver based on UART2 driver      */
/*               for  STM32F103C8 ARM Microcontroller .                      */
/*                                                                          */
/* Layer       : HAL                                                       */
/**************************************************************************/


#include "../STD_TYPES.h"
#include "../BIT_CALC.h"
#include "../include/UART_interface.h"
#include "../include/Bluetooth_interface.h"

/*******************************************************************************
 * Description: function to initialize the UART2 peripheral by disabling the interrupts
 *              & clearing flags , adjust baud rate, configure frame format
 *              like start bits number, word size, parity check type
 *              finally enable TX & RX and UART peripheral.
 * Outputs   : None
 * Inputs    : None
 ******************************************************************************/
extern void Bluetooth_VidInitialize (void)
{
	/*Initialize UART2                                                                           */
	UART_VidInit ();
}


/**************************************************************************************
 * Description: Asynchronous function to transmit a string using interrupts
 *              without blocking the processor.
 * Outputs   : None
 * Inputs    : const u8*Copy_Pu8ArrayData : pointer to constant array of characters
 *             void (*Copy_PVidFunCallback) (void) : pointer to callback function to set the pointer
 *             Value with the address of the function needed to be implemented by the ISR
 *             u8 Copy_u8DataLength: length of data
 *************************************************************************************/
extern u8 Bluetooth_u8TransmitInterrupt(const u8*Copy_Pu8ArrayData , void (*Copy_PVidFunCallback) (void))
{
	/* Local Variable indication for Error status                                  */
	u8 Local_u8Error = STD_TYPES_u8_ERROR_NOK;
	if ( (Copy_Pu8ArrayData != NULL ) && (Copy_PVidFunCallback != NULL))
	{
		UART_VidTransmitStringAsynch (Copy_Pu8ArrayData , Copy_PVidFunCallback);
	}
	else
	{
		Local_u8Error = STD_TYPES_u8_ERROR_NOK;
	}
	/* Function Return                                                            */
	return Local_u8Error;
}



/**************************************************************************************
 * Description: synchronous function to transmit a string using polling
 *              which block the processor.
 * Outputs   : Error state
 * Inputs    : const u8*Copy_Pu8ArrayData : pointer to constant array of characters
 *************************************************************************************/
extern u8 Bluetooth_u8TransmitPolling(const u8*Copy_Pu8ArrayData)
{
	/* Local Variable indication for Error status                                  */
	u8 Local_u8Error = STD_TYPES_u8_ERROR_NOK;
	if ( Copy_Pu8ArrayData != NULL)
	{
		UART_u8TransmitStringSynch (Copy_Pu8ArrayData);
	}
	else
	{
		Local_u8Error = STD_TYPES_u8_ERROR_NOK;
	}
	/* Function Return                                                            */
	return Local_u8Error;
}



/**************************************************************************************
 * Description: Asynchronous function to receive a string using interrupts
 *              without blocking the processor.
 * Outputs   : None
 * Inputs    : u8*Copy_Pu8ArrayData : pointer to array of characters to store the string in it
 *             void (*Copy_PVidFunCallback) (void) : pointer to callback function to set the pointer
 *             Value with the address of the function needed to be implemented by the ISR
 *             u8 Copy_u8DataLength: length of data
 *************************************************************************************/
extern u8 Bluetooth_u8ReceiveInterrupt(u8*Copy_Pu8ArrayData , u8 Copy_u8DataLength , void (*Copy_PVidFunCallback) (void))
{
	/* Local Variable indication for Error status                                  */
	u8 Local_u8Error = STD_TYPES_u8_ERROR_NOK;
	if ( (Copy_Pu8ArrayData != NULL ) && (Copy_PVidFunCallback != NULL) && (Copy_u8DataLength != 0))
	{
		UART_VidRecieveStringAsynch(Copy_Pu8ArrayData , Copy_u8DataLength , Copy_PVidFunCallback);
	}
	else
	{
		Local_u8Error = STD_TYPES_u8_ERROR_NOK;
	}
	/* Function Return                                                            */
	return Local_u8Error;
}


/**************************************************************************************
 * Description: synchronous function to receive a string using polling
 *              which block the processor.
 * Outputs   : Error state
 * Inputs    : const u8*Copy_Pu8ArrayData : pointer to constant array of characters
 *             u8 Copy_u8DataLength       : length of data
 *************************************************************************************/
extern u8 Bluetooth_u8ReceivePolling(u8*Copy_Pu8ArrayData , u8 Copy_u8DataLength)
{
	/* Local Variable indication for Error status                                  */
	u8 Local_u8Error = STD_TYPES_u8_ERROR_OK;
	/*Input arguments validation                                                  */
	if ( (Copy_Pu8ArrayData != NULL)  && (Copy_u8DataLength !=  0))
	{
		UART_u8RecieveStringSynch (Copy_Pu8ArrayData , Copy_u8DataLength);

	}
	else
	{
		Local_u8Error = STD_TYPES_u8_ERROR_NOK;
	}
	/* Function Return                                                            */
	return Local_u8Error;

}
