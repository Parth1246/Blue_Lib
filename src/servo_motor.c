/**
 * @file servo_motor.c
 * @author Parth Varsani (parthvarsani45@gmail.com)
 * 
 * @brief - Abstraction of Servo Initialization, angle controlling , 
 * @version 0.1
 * @date 2022-03-06
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <stdint.h>
#include <stddef.h>

#include "gpio.h"
#include "stm32f10x.h"
#include "pwm.h"

#define ARR_VAL 1000U

void Servo_Init(GPIO_TypeDef *GPIOx,uint8_t pin){

    PWM_Init(GPIOx,pin);

    /* set servo to 0 angle */
    GPIO_PWM(GPIOx,pin,ARR_VAL,25); /* ON time = 0.5ms   
                                      25/1000 = 0.025

                                      0.025(T) = (0.025)*(20ms)
                                               = 0.5 ms 
                                       T = 1/f
                                       f = operating freq. of servo
                                       f = 50 Hz 
                                       */                     
}

void Servo_Angle(GPIO_TypeDef *GPIOx,uint8_t pin,uint8_t angle){
    

    /* 5.556 microseconds(us) Per Degree  of the servo 
      
       0 angle -> 0.5 ms 
       180 angle -> 2.5 ms 
    */
    int ccr = (5556*angle)/10000 + 25 ;

    GPIO_PWM(GPIOx,pin,ARR_VAL,ccr);
}