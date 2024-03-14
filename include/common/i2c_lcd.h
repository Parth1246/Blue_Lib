/**
 * @file i2c_lcd.h
 * @author Parth Varsani
 * @brief 
 * @version 0.1
 * @date 2022-03-09
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <stdint.h>
#include "stm32f10x.h"

#ifndef __I2C_LCD_H
#define __I2C_LCD_H

#define I2C_module I2C1   // module used for I2C Interfacing
#define I2C_LCD_ADD (0x27 << 1)

void I2C_LCD_Instruction(uint8_t cmd);

void I2C_LCD_Data(uint8_t data);

void I2C_LCD_Init();

uint8_t LCD_Print_Line(char *str);

void I2C_LCD_Setcursor(uint8_t x , uint8_t y);

void I2C_LCD_Clear(void);

void I2C_LCD_Send(I2C_TypeDef *I2Cx,uint8_t address ,uint8_t *data,uint8_t n_bytes);





#endif

