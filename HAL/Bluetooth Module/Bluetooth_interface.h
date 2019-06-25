/******************************************************************************************/
/*                                                                                       */
/* File Name   : Bluetooth_interface.h                                                  */
/*                                                                                     */
/* Created on  : Jun 18, 2019                                                         */
/*                                                                                   */
/* Author      : Mariam Ahmed & shereen Abd Elhady                                  */
/*                                                                                 */
/* Version     : V01                                                              */
/*                                                                               */
/* Description : interface file for Bluetooth module includes transmitting and  */
/*               receiving functions' APIs using polling & interrupt mechanism */
/*               the implementation of this driver based on UART2 driver      */
/*               for  STM32F103C8 ARM Microcontroller .                      */
/*                                                                          */
/* Layer       : HAL                                                       */
/**************************************************************************/

#ifndef BLUETOOTH_INTERFACE_H_
#define BLUETOOTH_INTERFACE_H_


                /***************** APIs Prototypes *****************/
/*******************************************************************************
 * Description: function to initialize the UART2 peripheral by disabling the interrupts
 *              & clearing flags , adjust baud rate, configure frame format
 *              like start bits number, word size, parity check type
 *              finally enable TX & RX and UART peripheral.
 * Outputs   : None
 * Inputs    : None
 ******************************************************************************/
extern void Bluetooth_VidInitialize (void);


/**************************************************************************************
 * Description: Asynchronous function to transmit a string using interrupts
 *              without blocking the processor.
 * Outputs   : None
 * Inputs    : const u8*Copy_Pu8ArrayData : pointer to constant array of characters
 *             void (*Copy_PVidFunCallback) (void) : pointer to callback function to set the pointer
 *             Value with the address of the function needed to be implemented by the ISR
 *             u8 Copy_u8DataLength: length of data
 *************************************************************************************/
extern u8 Bluetooth_u8TransmitInterrupt(const u8*Copy_Pu8ArrayData , void (*Copy_PVidFunCallback) (void));


/**************************************************************************************
 * Description: synchronous function to transmit a string using polling
 *              which block the processor.
 * Outputs   : Error state
 * Inputs    : const u8*Copy_Pu8ArrayData : pointer to constant array of characters
 *************************************************************************************/
extern u8 Bluetooth_u8TransmitPolling(const u8*Copy_Pu8ArrayData);


/**************************************************************************************
 * Description: Asynchronous function to receive a string using interrupts
 *              without blocking the processor.
 * Outputs   : None
 * Inputs    : u8*Copy_Pu8ArrayData : pointer to array of characters to store the string in it
 *             void (*Copy_PVidFunCallback) (void) : pointer to callback function to set the pointer
 *             Value with the address of the function needed to be implemented by the ISR
 *             u8 Copy_u8DataLength: length of data
 *************************************************************************************/
extern u8 Bluetooth_u8ReceiveInterrupt(u8*Copy_Pu8ArrayData , u8 Copy_u8DataLength , void (*Copy_PVidFunCallback) (void));


/**************************************************************************************
 * Description: synchronous function to receive a string using polling
 *              which block the processor.
 * Outputs   : Error state
 * Inputs    : const u8*Copy_Pu8ArrayData : pointer to constant array of characters
 *             u8 Copy_u8DataLength       : length of data
 *************************************************************************************/
extern u8 Bluetooth_u8ReceivePolling(u8*Copy_Pu8ArrayData , u8 Copy_u8DataLength);

#endif /* BLUETOOTH_INTERFACE_H_ */
