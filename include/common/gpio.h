/**
 * @file  <gpio.h>
 * @brief <header file for declaration & Documentation of functions and MACROs of gpio.c>
 *
 * This implementation file provides declaration   of initialization, set
 * reset and read GPIO functions for stm32f103xx platform.
 *
 * @author <Kaushal dekivadia>
 * @date   <june 22 2021>
 *
 */
 

#ifndef __GPIO_H
#define __GPIO_H

#include <stdint.h>
#include "stm32f10x.h"

#define INPUT  0U   
#define OUTPUT 3U   
#define OUTPUT_10 1U    
#define OUTPUT_2 2U
#define OUTPUT_50 3U 


#define PUSHPULL    0U
#define OPENDRAIN   1U
#define AF_PUSHPULL 2U
#define AF_OPENDRAIN 3U

#define ANALOG      0U
#define FLOATING    1U
#define PULL_UP     2U


/**
 * @brief function to initialize GPIO MODES.
 *  
 * @param GPIOx     - Port of GPIO
 * @param pin       - pin number of GPIO
 * @param GPIO_MODE - MODE of GPIO :- OUTPUT/INPUT
 * @param GPIO_CNF  - Configuration of GPIO    
 *      
 * This function initialize diffrent GPIO modes as below
 *    
 *    1.GPIO_MODE = OUTPUT , GPIO_CNF = PUSHPULL
 *    2.GPIO_MODE = OUTPUT , GPIO_CNF = OPENDRAIN
 *    3.GPIO_MODE = OUTPUT , GPIO_CNF = AF_PUSHPULL
 *    4.GPIO_MODE = INPUT  , GPIO_CNF = FLOATING
 *    5.GPIO_MODE = INPUT  , GPIO_CNF = PULL_UP
 *    6.GPIO_MODE = INPUT  , GPIO_CNF = ANALOG
 *    
 * @return void
 */

extern void GPIO_Init(GPIO_TypeDef *GPIOx , uint8_t pin , uint8_t GPIO_MODE , uint8_t GPIO_CNF );



/**
 * @brief function to set GPIO pin( BSSR register bit)
 * 
 * @param GPIOx - Port of GPIO
 * @param pin   - pin of GPIO
 
 * @return void
 */

extern void GPIO_Set (GPIO_TypeDef *GPIOx , uint8_t pin);



/**
 * @brief function to reset GPIO pin( BRR register bit)
 * 
 * @param GPIOx - Port of GPIO
 * @param pin   - pin of GPIO
 
 * @return void
 */

 extern void GPIO_Reset (GPIO_TypeDef *GPIOx , uint8_t pin);




/**
 * @brief function to read GPIO input bit (IDR register bit)
 * 
 * @param GPIOx - Port of GPIO
 * @param pin   - pin of GPIO
 * 
 * @return 0 -> GPIO IDR bit is 0
 * @return 1 -> GPIO IDR bit is 1
 */

 extern uint8_t GPIO_Read(GPIO_TypeDef *GPIOx , uint8_t pin);


 /**
 * @brief function to Write GPIO output bit (ODR register bit)
 * 
 * @param GPIOx - Port of GPIO
 * @param pin   - pin of GPIO
 * @param value - value of bit to be written ( 0 or 1)
 * 
 * @return void
 */

 extern void GPIO_Write(GPIO_TypeDef *GPIOx , uint8_t pin, uint8_t value);


/**
 * @brief function to  Toggle Output bit (ODR register bit)
 * 
 * @param GPIOx - Port of GPIO
 * @param pin   - pin of GPIO
 * 
 * @return void
 */

 extern void GPIO_Toggle(GPIO_TypeDef *GPIOx , uint8_t pin);


 extern void GPIO_EXTI_Init(GPIO_TypeDef *GPIOx,uint8_t pin);

 

#endif