/**
 * @file timer_delay.c
 * @author Parth Varsani (parthvarsani45@gmail.com)
 * @brief - To generate delay using timer
 * @version 0.1
 * @date 2022-03-07
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <stdint.h>
#include "stm32f10x.h"


void TDelay_us(uint32_t microseconds){
  
	RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;
	
	/* Set counter to 0 */
	TIM4->CNT = 0;
	
	// Setup the prescaler to 72 -> ( 72 -1) clk = 72MHz/72 = 1Mhz =>> 1us

	TIM4->PSC = (72 -1);	
	
	/* initialize the Auto reload register value */
	TIM4->ARR = (microseconds-3);

    /*Counter stops counting at the next update event (clearing the bit CEN)*/
    TIM4->CR1 |= TIM_CR1_OPM;
    TIM4->CR1 |= TIM_CR1_CEN;

    while(TIM4->CR1 & TIM_CR1_CEN){

    }
}

void TDelay_ms(uint32_t milliseconds){
  
	RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;
	
	/* Set counter to 0 */
	TIM4->CNT = 0;
	
	/* Setup the prescaler to 36000 -> = 72MHz/36000 = 2KHz =>> 0.5 us */
 
	TIM4->PSC = (36000-1); /* to achieve 1Khz clock wee have to divide pclk by 
                              72000 which is not possible in 16 bit psc reg */
	
	/* initialize the Auto reload register value */

	TIM4->ARR = 2*milliseconds ;

    /*Counter stops counting at the next update event (clearing the bit CEN)*/
    TIM4->CR1 |= TIM_CR1_OPM;
    TIM4->CR1 |= TIM_CR1_CEN;

    while(TIM4->CR1 & TIM_CR1_CEN){

    }
}

