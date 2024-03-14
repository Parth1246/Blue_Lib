/**
 * @file   <test_gpio1.c>
 * @brief  <test file for basic gpio and delay function>
 * 	    
 * 	     OUTPUT-blinking led every 1s in pushpull mode
 *
 * @author <Parth Varsani>
 * @date   <Mar 9 2022>
 *
 */

 
 #include "stm32f10x.h"
 #include "gpio.h"
 #include "delay.h"


 int main(){

    Delay_Init(); /// Initialization of Delay (Systick (timer) configuration)
    GPIO_Init(GPIOB,6,OUTPUT,OPENDRAIN); // //Initialization of GPIO - B6 for output opendrain mode

    while(1){

        GPIO_Toggle(GPIOB,6); // Toggle the value of pin B6 every 1s

        Delay_ms(1000);
    }


    return 0;
 }
