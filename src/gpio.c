/**
 * @file   <gpio.c>
 * @brief  <Abstraction of GPIO initialization, bit_set, bit_reset, bit_write, bit_read operations>
 *
 * This implementation file provides an abstraction of initialization, set
 * reset and read GPIO registers for stm32f103xx platform.
 *
 * @author <Parth Varsani>
 * @date   <june 22 2022>
 *
 */


#include <stdint.h>
#include "gpio.h"
#include "stm32f10x.h"

void GPIO_Init(GPIO_TypeDef *GPIOx , uint8_t pin , uint8_t GPIO_MODE , uint8_t GPIO_CNF ){

    if (GPIOx == GPIOA)
            RCC->APB2ENR |= RCC_APB2ENR_IOPAEN ;

    else if (GPIOx == GPIOB)
            RCC->APB2ENR |= RCC_APB2ENR_IOPBEN ;

    else if (GPIOx == GPIOC)
            RCC->APB2ENR |= RCC_APB2ENR_IOPCEN ;

    else 
            RCC->APB2ENR |= RCC_APB2ENR_IOPDEN ;



    if(pin > 7){
        pin = pin - 8;
        GPIOx->CRH &= ~(0xF<<pin*4);

        GPIOx->CRH |= (GPIO_MODE<<pin*4) | (GPIO_CNF << (pin*4 + 2));
    }
    else{

        GPIOx->CRL &= ~(0xF<<pin*4);
        GPIOx->CRL |= (GPIO_MODE<<pin*4) | (GPIO_CNF << (pin*4 + 2));
    }

}



void GPIO_Set (GPIO_TypeDef *GPIOx , uint8_t pin){

    GPIOx->BSRR |= (1<<pin);
}

void GPIO_Reset (GPIO_TypeDef *GPIOx , uint8_t pin){

    GPIOx->BRR |= (1<<pin);
}

uint8_t GPIO_Read(GPIO_TypeDef *GPIOx , uint8_t pin){
    
    if(GPIOx->IDR & (1 << pin ))
        return 1;
     else
        return 0;
}


void GPIO_Write(GPIO_TypeDef *GPIOx , uint8_t pin, uint8_t value){
    
    if(value == 1)
      GPIOx->BSRR |= (1<<pin);
    
    if(value == 0)
      GPIOx->BRR |= (1<<pin);
    
}

void GPIO_Toggle(GPIO_TypeDef *GPIOx , uint8_t pin){

    GPIOx->ODR ^= (1<<pin);
}

void GPIO_EXTI_Init(GPIO_TypeDef *GPIOx,uint8_t pin){

    GPIO_Init(GPIOx,pin,INPUT,FLOATING);

    if((pin>=0) && (pin<=4)){
         NVIC_EnableIRQ(pin + 6);
         NVIC_SetPriority( pin+6 ,0);
     }
    else if((pin>=5) && (pin<=9)){
        NVIC_EnableIRQ(23);
        NVIC_SetPriority(23,0);
    }
    else{
        NVIC_EnableIRQ(40);
        NVIC_SetPriority(40,0);
    }


    EXTI->IMR |= (1<<pin);
    EXTI->RTSR |= (1<<pin);

    if(GPIOx == GPIOA){
        AFIO->EXTICR[pin/4] |= (0<<(pin%4)*4);
    }else if(GPIOx == GPIOB){
        AFIO->EXTICR[pin/4] |= (1<<(pin%4)*4);
    }else{
        AFIO->EXTICR[pin/4] |= (2<<(pin%4)*4);
    }


}
