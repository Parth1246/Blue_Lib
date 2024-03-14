/**
 * @file pwm.h
 * @author Kaushal Dekivadia (dekivadiakaushal1212@gmail.com)
 * 
 * @brief header file for declaration & Documentation of 
 *        functions and MACROs of pwm.c
 * 
 * @version 0.1
 * @date 2022-03-06
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef __PWM_H
#define __PWM_H

#include <stdint.h>
#include "stm32f10x.h"


#define PSC_VAL 1440U // prescaler value 


/**
 * @brief Function to initialize PWM 
 *          
 *       pins that can be configured as PWM
 *       ->  A0 - A3
 *       ->  A6 - A10
 *       ->  B0 - B1
 *       ->  B6 - B9
 * 
 * @param GPIOx - Port of GPIO 
 * @param pin - Pin of GPIO
 */
void PWM_Init(GPIO_TypeDef *GPIOx ,uint8_t pin);


/**
 * @brief  Function to configure PWM 
 * 
 * @param GPIOx - Port of GPIO 
 * @param pin - Pin of GPIO
 * @param arr - Auto reload reg value
 * @param ccr - Compare reload reg value
 */
void GPIO_PWM(GPIO_TypeDef *GPIOx ,uint8_t pin,uint32_t arr,uint32_t ccr);



/**
 * @brief Function to get TIM peripheral number for specified gpio
 * 
 * @param GPIOx - Port of GPIO 
 * @param pin - Pin of GPIO
 * 
 * @return TIM_TypeDef* - pointer to TIM peripheral reg strucure  
 */
TIM_TypeDef* Get_TIM(GPIO_TypeDef *GPIOx , uint8_t pin);



/**
 * @brief Function to get TIM channel  number for specified gpio
 * 
 * @param GPIOx - Port of GPIO 
 * @param pin - Pin of GPIO
 * 
 * @return uint8_t - channel number  
 */

uint8_t Get_TIM_Channel(GPIO_TypeDef *GPIOx , uint8_t pin);


#endif