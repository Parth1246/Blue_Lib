/**
 * @file   <test_gpio1.c>
 * @brief  <test file for basic gpio and delay function>
 * 	    
 * 	     OUTPUT-blinking led every 1s in pushpull mode
 *
 * @author <Kaushal dekivadia>
 * @date   <Mar 9 2022>
 *
 */

#include "stm32f10x.h"
#include "gpio.h"
#include "delay.h"

int main(){

	GPIO_Init(GPIOA,5,OUTPUT,PUSHPULL); //Initialization of GPIO - C13 for output pushpull mode

	// infinite loop..

	while(1){

		GPIO_Set(GPIOA,5);  // set C13 GPIO value to HIGH
		Delay_ms(1000);	// delay of 1s
		GPIO_Reset(GPIOA,5);  // set C13 GPIO value to LOW
		Delay_ms(1000);	// delay of 1s
	}

	return 0;
}
