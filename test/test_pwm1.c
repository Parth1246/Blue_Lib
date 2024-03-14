/**
 * @file   <test_servo.c>
 * @brief  <test file for basic Servo functions>
 * 	    
 * 	    will fade the led as given input.
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

   
    PWM_Init(GPIOA,1);
    PWM_Init(GPIOA,2);
    PWM_Init(GPIOA,3);

   /* fading LED */

    GPIO_PWM(GPIOA,1,1000,250);
    GPIO_PWM(GPIOA,2,1000,500);
    GPIO_PWM(GPIOA,3,1000,750);

    while(1);

    return 0;
}