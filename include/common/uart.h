/**
 * @file  <uart.h>
 * @brief <header file for declaration & Documantation of functions and MACROs of uart.c>
 *
 *  This implementation file provides declaration for functions to initialize, read
 *  and write UART reg. for stm32f10xx microcontrollers
 *
 * @author <Kaushal dekivadia>
 * @date   <sept 28 2021>z
 *
 */

 #ifndef __UART_H
 #define __UART_H


#include <stdint.h>
#include "stm32f10x.h"
#include "gpio.h"

#define PCLK2 72000000
#define PCLK1 36000000


/**
 * @brief function to Initialization UART Peripheral
 * 
 * @param UARTx        - UART peripherel number (USART1 ,USART2 or USART3)
 * @param word_length  - word length of data frame ( 8 or 7)
 * @param stop_bit     - stop bit        (1 or 2)
 * @param buad rate    - value of baudrate ( eg. 9600 ,115200)
 * 
 *This function initialize UART peripheral and defines various specifications
 * 
 * @return void
 * 
 */

extern void UART_Init(USART_TypeDef *UARTx ,uint8_t word_length , uint8_t stop_bit,uint32_t buadrate);




/**
 * @brief function to Send byte in buffer register
 * 
 * @param UARTx        - UART peripherel number (USART1 ,USART2 or USART3)
 * @param value         - 7 or 8 bit data
 * 
 * @return - void
 */
extern void UART_SendByte(USART_TypeDef * UARTx ,uint8_t value);


/**
 * @brief function to Send string using uart
 *  
 * @param UARTx        - UART peripherel number (USART1 ,USART2 or USART3)
 * @param str          - pointer to char string
 * 
 * @return - void
 */

extern void UART_SendString(USART_TypeDef * UARTx , char *str);




/**
 * @brief function to receive byte using uart
 *  
 * @param UARTx        - UART peripherel number (USART1 ,USART2 or USART3)
 * 
 * @return - 8 - bit data
 * 
 **/

extern uint8_t UART_ReceiveByte(USART_TypeDef *UARTx);


/**
 * @brief function to Receive string using uart
 *  
 * @param UARTx        - UART peripherel number (USART1 ,USART2 or USART3)
 * @param rx_str       - pointer to empty receive buffer
 * @param len          - size of buffer
 * 
 * @return - void
 */

extern void UART_ReceiveString(USART_TypeDef *UARTx , char * rx_str , uint32_t len);



 #endif
