/**
 * @file   <uart.c>
 * @brief  <Abstraction of UART initialization, send buffer , receive buffer operations>
 *
 * This implementation file provides an abstraction of initialization, send
 * and receive buffer data using uart
 *
 * @author <Parth Varsani>
 * @date   <mar 8 2022>
 *
 */

#include <stdint.h>
#include "stm32f10x.h"
#include "gpio.h"
#include "uart.h"


 void UART_Init(USART_TypeDef *UARTx ,uint8_t word_length , uint8_t stop_bit,uint32_t buadrate){

         /* Enable clock for Alternate function IO */

         RCC->APB2ENR |=  RCC_APB2ENR_AFIOEN;


         if(UARTx == USART1){
            RCC->APB2ENR |= RCC_APB2ENR_USART1EN;   // enable APB2 clock(max = 72MHz) for USART1

            GPIO_Init(GPIOA,9,OUTPUT,AF_PUSHPULL);  // TX1 pin - A9 
            GPIO_Init(GPIOA,10,INPUT,PULL_UP);      // RX1 pin - A10

         }else if(UARTx == USART2){

             RCC->APB1ENR |= RCC_APB1ENR_USART2EN;   // enable APB1 clock(max = 36MHz) for USART2

             GPIO_Init(GPIOA,2,OUTPUT,AF_PUSHPULL);   // TX1 pin - A2
             GPIO_Init(GPIOA,3,INPUT,PULL_UP);        // RX1 pin - A3

         }else{
            RCC->APB1ENR |= RCC_APB1ENR_USART3EN;   // enable APB1 clock(max = 36MHz) for USART3

            GPIO_Init(GPIOB,10,OUTPUT,AF_PUSHPULL);  // TX1 pin - B10
            GPIO_Init(GPIOB,11,INPUT,PULL_UP);       // RX1 pin - B11
         }

         
         UARTx->CR1 |= USART_CR1_UE ; // (1<<13) - uart enable

         if(word_length == 7){
            UARTx->CR1 &= ~(USART_CR1_M);  //1 Start bit, 8 Data bits(7data + 1 paraity), n Stop bit
         }else{
            UARTx->CR1 |= USART_CR1_M;    //  1 Start bit, 9 Data bits(8 data + 1 parity), n Stop bit
         }

         UARTx->CR1 |= USART_CR1_PCE; // Parity control enable - even parity

    
         
         if(stop_bit == 2){
            UARTx->CR2 |= USART_CR2_STOP_1;  // stop bits - 2 ( default - 1)
         }

         UARTx->CR3 = 0;
         UARTx->GTPR = 0;

         // buad rate

         if(UARTx == USART1){
            
            UARTx->BRR = PCLK2/buadrate;   // PCLK2 = 72000000U
         }else{

            UARTx->BRR = PCLK1/buadrate;   // PCLK1 = 36000000U
         }

         /* uart transmitter and reciever enable*/
         UARTx->CR1 |= USART_CR1_RE;
         UARTx->CR1 |= USART_CR1_TE;
 }

void UART_SendByte(USART_TypeDef * UARTx ,uint8_t value){

   while(!(UARTx->SR & USART_SR_TXE )); // wait till Transmit data register become empty

   UARTx->DR = value;

}

void UART_SendString(USART_TypeDef * UARTx , char *str){

   while(*str != '\0'){
      UART_SendByte(UARTx,*str);
      str++;
   }

   while(!(UARTx->SR & USART_SR_TC));  // wait till Transmission completes
}

uint8_t UART_ReceiveByte(USART_TypeDef *UARTx){

   while(!(UARTx->SR & USART_SR_RXNE));  // wait till  Read data register not empty

      return UARTx->DR;
}

void UART_ReceiveString(USART_TypeDef *UARTx , char * rx_str , uint32_t len){

   uint32_t i =0;

   for(i = 0;i<len;i++){
      *rx_str = UART_ReceiveByte(UARTx);
      rx_str++;
   }

   *rx_str = '\0';
   rx_str = rx_str - len;
}
