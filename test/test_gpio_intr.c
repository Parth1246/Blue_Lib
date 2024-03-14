/**
 * @file   <test_gpio_intr.c>
 * @brief  <test file for basic gpio and delay function>
 * 	    
 * 	    test gpio in interrupt mode
 *
 * @author <Kaushal dekivadia>
 * @date   <Mar 4 2022>
 *
 */
#include "stm32f10x.h"
#include "gpio.h"
#include "delay.h"
 
 void EXTI15_10_IRQHandler( void){
  
  if(EXTI->PR && EXTI_PR_PR15){
  		EXTI->PR |= EXTI_PR_PR15;
  		GPIO_Toggle(GPIOA,5);
  }
 
 }

int main(){

	GPIO_Init(GPIOA,5,OUTPUT,PUSHPULL);
	

	GPIO_Set(GPIOA,5);

	GPIO_EXTI_Init(GPIOC,15);

	
	while(1);



	return 0;
}
