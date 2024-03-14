/**
 * @file timer_delay.h
 * @author Kaushal Dekivadia (dekivadiakaushal1212@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-03-07
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef __TIMER_H
#define __TIMER_H

#include <stdint.h>
#include "stm32f10x.h"

/**
 * @brief - To get delay in microseconds
 * 
 * @param microseconds - microseconds delay
 */
void TDelay_us(uint32_t microseconds);

/**
 * @brief - To get delay in milli seconds
 * 
 * @param milliseconds - milli seconds delay
 */
void TDelay_ms(uint32_t milliseconds);

#endif