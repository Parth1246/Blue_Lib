/**
 * @file  <delay.h>
 * @brief <header file for delay_init , delay_us and delay_ms functions >
 *
 *
 * @date   <mar 2 2021>
 *
 */


#ifndef __DELAY_H
#define __DELAY_H


#include "stm32f10x.h"

/**
 * @brief function to Initialize Delay
 * 
 * @param void
 * 
 * @return void
 */

void Delay_Init(void);

/**
 * @brief function to provide delay in us
 * 
 * @param us - time in us
 * 
 * @return void
 */
void Delay_us(uint32_t us);

/**
 * @brief function to provide delay in ms
 * 
 * @param us - time in ms
 * 
 * @return void
 */
void Delay_ms(uint32_t ms);


#endif
