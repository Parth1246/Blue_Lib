

/**
 * @file i2c_lcd.c
 * 
 * 
 * @author Parth Varsani 
 * 
 * @brief - Abstraction of I2C_LCD Initialization,Send data ,command and strings
 * 
 * @version 0.1
 * @date 2022-03-09
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <stdint.h>
#include "stm32f10x.h"

#include "gpio.h"
#include "i2c.h"
#include "i2c_lcd.h"


void I2C_LCD_Instruction(uint8_t cmd){

    char nibble_h,nibble_l;

    uint8_t command[4];     // xxxx 0000
                             // 1011 1010
    nibble_h = (cmd & 0xF0); //1011 0000
    nibble_l = ((cmd << 4 ) & 0XF0);        // 1010 1100

    command[0] = nibble_h | 0x0C;
    command[1] = nibble_h | 0x08;

    command[2] = nibble_l | 0x0C;
    command[3] = nibble_l | 0x08;

    I2C_LCD_Send(I2C_module,I2C_LCD_ADD,command,4);

}

void I2C_LCD_Data(uint8_t data){

    char nibble_h,nibble_l;

    uint8_t temp[4];     // xxxx 0000
                             // 1011 1010
    nibble_h = (data & 0xF0); //1011 0000
    nibble_l = ((data << 4 ) & 0XF0);        // 1010 1001

    temp[0] = nibble_h | 0x0D;
    temp[1] = nibble_h | 0x09;

    temp[2] = nibble_l | 0x0D;
    temp[3] = nibble_l | 0x09;

    I2C_LCD_Send(I2C_module,I2C_LCD_ADD,temp,4);
    
}

void I2C_LCD_Init()
{

    I2C_Init(I2C_module,I2C_SM);

    Delay_ms(10); //power-up rise time
    
    I2C_LCD_Instruction(0x33);  // for 4-bit mode
    I2C_LCD_Instruction(0x32);
    I2C_LCD_Instruction(0x28);

    I2C_LCD_Instruction(0x0e); // display on ,cursor on

    I2C_LCD_Instruction(0x01); // clear LCD
    I2C_LCD_Instruction(0x06); // shift cursor right

}


uint8_t I2C_LCD_Print_Line(char *str)  // returns number of printed
{
    uint8_t i = 0;
    while(str[i] != '\0'){
        
        if(i==16)
            I2C_LCD_Setcursor(1,2);

        I2C_LCD_Data(str[i++]);
    }
  
    i--;
    return i;
}

void I2C_LCD_Setcursor(uint8_t x , uint8_t y)
{
    unsigned char firstcharadd[] = { 0x80, 0xC0, 0x94, 0xD4};
    I2C_LCD_Instruction(firstcharadd[y-1] + x -1);
    Delay_ms(1);

}
void I2C_LCD_Clear(void)
{
     I2C_LCD_Instruction(0x01); // clear LCD
    
     I2C_LCD_Setcursor(1,1);
}


void I2C_LCD_Send(I2C_TypeDef *I2Cx,uint8_t address ,uint8_t *data,uint8_t n_bytes){

    I2C_Start(I2Cx);
    I2C_SendAddress(I2Cx,address);
    I2C_SendString(I2Cx,data,n_bytes);
    I2C_Stop(I2Cx);
}