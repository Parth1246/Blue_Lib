/**
 * @file   <test_servo.c>
 * @brief  <test file for basic Servo functions>
 * 	    
 * 	    will keep fading the led as given input.
 *
 * @author <Parth Varsani>
 * @date   <Mar 12 2022>
 *
 */

#include "stm32f10x.h"
#include "gpio.h"
#include "delay.h"
#include "pwm.h"


int main(){

   
    PWM_Init(GPIOA,3);

   /* fading LED */

    while(1){

        for(int i = 0;i<=1000;i++){

            GPIO_PWM(GPIOA,3,1000,i); 
            Delay_ms(5);
        }

        for(int i = 1000;i>=0;i--){

            GPIO_PWM(GPIOA,3,1000,i);
            Delay_ms(5);
        }

        Delay_ms(500);

    }

    return 0;
}