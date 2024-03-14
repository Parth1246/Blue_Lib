/**
 * @file   <test_gpio_intr.c>
 * @brief  <test file for basic uart function>
 * 	    
 * 	    - to test basic UART HAL function and send few bytes of data to capture on logic analyzer
 *
 * @author <Kaushal dekivadia>
 * @date   <Mar 11 2022>
 *
 */
#include "stm32f10x.h"
#include "gpio.h"
#include "delay.h"
#include "uart.h"

int main(){

	Delay_Init();

  UART_Init(USART2,8,1,9600); /// dataframe size - 8 , baudrate - 9600 , 1 stop bit
	
  while(1){
	
    UART_SendString(USART2," SUBJECT :4EL31 \n");
    Delay_ms(10);
    UART_SendString(USART2," PROJECT TITLE : BLUE-LIB \n");
    Delay_ms(10);
    UART_SendString(USART2," TEST : UART APIS \n ");
    Delay_ms(10);

  }

  return 0;

}

