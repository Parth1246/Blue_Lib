/**
 * @file pwm.c
 * @author Parth Varsani (parthvarsani45@gmail.com)
 * 
 * @brief - Abstraction of PWM initialization and controlling duty cycle
 *  
 * @version 0.1
 * @date 2022-03-05
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <stdint.h>
#include <stddef.h>

#include "gpio.h"
#include "stm32f10x.h"
#include "pwm.h"


void PWM_Init(GPIO_TypeDef *GPIOx ,uint8_t pin){ 

    TIM_TypeDef *TIMx;
    uint8_t channel;

    TIMx = Get_TIM(GPIOx,pin);
    channel = Get_TIM_Channel(GPIOx,pin);

    /* enable Alternate function IO*/
    RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;

    /* enable clock for TIM peripheral*/

    if(TIMx == TIM1)
        RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
    else if(TIMx == TIM2)
        RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
    else if(TIMx == TIM3)
        RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
    else
        RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;


    GPIO_Init(GPIOx,pin,OUTPUT_50,AF_PUSHPULL);

    TIMx->PSC = (PSC_VAL-1);  /*  PCLK = 72 MHz , desired freq. for servo 50Hz
                                
                                72000000/50 = 1440x1000

                                so PSC = 1440 , ARR = 1000 */


    /* to select PWM mode 1 OCM1 bits = 110 (0x6) */ 
    switch(channel)
	{
		case 1: TIMx->CCMR1 |= (0x6<<4)|TIM_CCMR1_OC1PE;
                break;
		case 2: TIMx->CCMR1 |= (0x6<<12)|TIM_CCMR1_OC2PE;
                break;
		case 3: TIMx->CCMR2 |= (0x6<<4)|TIM_CCMR2_OC3PE;
                break;
		case 4: TIMx->CCMR2 |= (0x6<<12)|TIM_CCMR2_OC4PE;
                break;
	}
    
    /* Enable auto-reload preload
        TIMx_ARR register is buffered */

    TIMx->CR1 |= TIM_CR1_ARPE;

    /* capture/compare enable register - Enable channel */
    TIMx->CCER |= (1 << ((channel-1)*4));             

    /* Enable main output */
    TIMx->BDTR |= TIM_BDTR_MOE;

    /* Enable timer counter */
    TIMx->CR1 |= TIM_CR1_CEN;

}

void GPIO_PWM(GPIO_TypeDef *GPIOx ,uint8_t pin,uint32_t arr,uint32_t ccr){

    TIM_TypeDef *TIMx;
    uint8_t channel;

    TIMx = Get_TIM(GPIOx,pin);
    channel = Get_TIM_Channel(GPIOx,pin);

    /* load auto reload register value */
    TIMx->ARR = (arr-1);
    
    /* load compare register value */
    switch(channel)
	{
		case 1: TIMx->CCR1 = ccr; break;
		case 2: TIMx->CCR2 = ccr; break;
		case 3: TIMx->CCR3 = ccr; break;
		case 4: TIMx->CCR4 = ccr; break;
	}
}


TIM_TypeDef* Get_TIM(GPIO_TypeDef *GPIOx , uint8_t pin){

    /* to get timer number for specified gpio */
    if(GPIOx == GPIOA)
	{
		if(pin <= 3)
			return TIM2;
		else if ((pin >= 8) &&  (pin <= 10))
			return TIM1;
		else if ((pin == 6) &&  (pin == 7))
			return TIM3;

	}
	else if (GPIOx == GPIOB)
	{
		if(pin < 2)
			return TIM3;
		else
            return TIM4; 
	}

    return NULL;
}



uint8_t Get_TIM_Channel(GPIO_TypeDef *GPIOx , uint8_t pin){
    
    if(GPIOx == GPIOA)
	{
		switch(pin)
		{
			case 0 : return 1;
			case 1 : return 2;
			case 2 : return 3;
			case 3 : return 4;
			case 6 : return 1;
			case 7 : return 2;
			case 8 : return 1;
			case 9 : return 2;
			case 10 : return 3;
		}
        return 0;
	}
	else if(GPIOx == GPIOB)
	{
		switch(pin)
		{
			case 0 : return 3;
			case 1 : return 4;
            case 6 : return 1;
            case 7 : return 2;
            case 8 : return 3;
            case 9 : return 4;
		}
		return 0;
	}

	return 0;
}