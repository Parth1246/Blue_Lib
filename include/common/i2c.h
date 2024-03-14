/**
 * @file i2c.h
 * @author Kaushal Dekivadia (dekivadiakaushal1212@gmail.com)
 *
 * @brief - header file for declaration & Documentation of functions and MACROs of 
 *          i2c.h
 * 
 * @version 0.1
 * @date 2022-02-28
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef __I2C_H
#define __I2C_H

#include <stdint.h>
#include "stm32f10x.h"
#include "gpio.h"

#define I2C_SM 0U
#define I2C_FM 1U

/**
 * @brief -function to Initialization I2C Peripheral
 * 
 * @param I2Cx - I2C peripheral number (I2C1 or I2C2)
 * @param speed_mode - speed mode if I2C peripheral
 *                     (I2C_SM - standard mode)
 *                     (I2C_FM - Fast mode) 
 * 
 * @return void
 */
void I2C_Init(I2C_TypeDef *I2Cx , uint8_t speed_mode);


/**
 * @brief - function to start I2C communication
 * 
 * @param I2Cx - I2C peripheral number (I2C1 or I2C2)
 * 
 * @return void
 */
void I2C_Start(I2C_TypeDef *I2Cx);


/**
 * @brief - function to stop I2C communication 
 * 
 * @param I2Cx - I2C peripheral number (I2C1 or I2C2)
 * 
 * @return void
 */
void I2C_Stop(I2C_TypeDef *I2Cx);

/**
 * @brief - function to send address 
 * 
 * @param I2Cx - I2C peripheral number (I2C1 or I2C2)
 * @param address - address of I2C device
 */
void I2C_SendAddress(I2C_TypeDef *I2Cx ,uint8_t address);



#endif