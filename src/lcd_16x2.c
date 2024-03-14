
/**
 * @file   <lcd_16x2.c>
 * @brief  <Abstraction of LCD initialization,.......>
 *
 * This implementation file provides an abstraction of initialization
 *
 * @author <Parth Varsani>
 * @date   <mar 6 2022>
 *
 */
 

#include <stdint.h>
#include "delay.h"
#include "gpio.h"
#include "lcd_16x2.h"

void LCD_Init()
{

    GPIO_Init(LCD_DATA_PORT, LCD_D4_PIN, OUTPUT, PUSHPULL);
    GPIO_Init(LCD_DATA_PORT, LCD_D5_PIN, OUTPUT, PUSHPULL);
    GPIO_Init(LCD_DATA_PORT, LCD_D6_PIN, OUTPUT, PUSHPULL);
    GPIO_Init(LCD_DATA_PORT, LCD_D7_PIN, OUTPUT, PUSHPULL);

    GPIO_Init(LCD_RW_PORT,     LCD_RW_PIN,     OUTPUT, PUSHPULL);
    GPIO_Init(LCD_RS_PORT,     LCD_RS_PIN,     OUTPUT, PUSHPULL);
    GPIO_Init(LCD_ENABLE_PORT, LCD_ENABLE_PIN, OUTPUT, PUSHPULL);

    GPIO_Write(LCD_ENABLE_PORT,LCD_ENABLE_PIN , 0 );

    Delay_ms(10); //power-up rise time
    
    LCD_Instruction(0x33);  // for 4-bit mode
    LCD_Instruction(0x32);
    LCD_Instruction(0x28);

    LCD_Instruction(0x0e); // display on ,cursor on

    LCD_Instruction(0x01); // clear LCD
    LCD_Instruction(0x06); // shift cursor right

}

void LCD_Instruction(uint8_t cmd)
{
    // most significant nibble
    GPIO_Write(LCD_DATA_PORT,LCD_D4_PIN, (0x10 & cmd)&&1 );
    GPIO_Write(LCD_DATA_PORT,LCD_D5_PIN, (0x20 & cmd)&&1 );
    GPIO_Write(LCD_DATA_PORT,LCD_D6_PIN, (0x40 & cmd)&&1 );
    GPIO_Write(LCD_DATA_PORT,LCD_D7_PIN, (0x80 & cmd)&&1 );

    GPIO_Write(LCD_RS_PORT, LCD_RS_PIN, 0 );
    GPIO_Write(LCD_RW_PORT, LCD_RW_PIN, 0 );

    Delay_us(1);
    GPIO_Write(LCD_ENABLE_PORT, LCD_ENABLE_PIN, 1);
    Delay_us(10);
    GPIO_Write(LCD_ENABLE_PORT, LCD_ENABLE_PIN, 0);

    Delay_us(20);
    // Least significant nibble
    GPIO_Write(LCD_DATA_PORT,LCD_D4_PIN, (0x01 & cmd)&&1 );
    GPIO_Write(LCD_DATA_PORT,LCD_D5_PIN, (0x02 & cmd)&&1 );
    GPIO_Write(LCD_DATA_PORT,LCD_D6_PIN, (0x04 & cmd)&&1 );
    GPIO_Write(LCD_DATA_PORT,LCD_D7_PIN, (0x08 & cmd)&&1 );

    Delay_us(1);
    GPIO_Write(LCD_ENABLE_PORT, LCD_ENABLE_PIN, 1);
    Delay_us(1);
    GPIO_Write(LCD_ENABLE_PORT, LCD_ENABLE_PIN, 0);

    Delay_us(100); // delay before starting new cycle
}



void LCD_Data(uint8_t data)
{   // most significant nibble
    GPIO_Write(LCD_DATA_PORT,LCD_D4_PIN, (0x10 & data)&&1 );
    GPIO_Write(LCD_DATA_PORT,LCD_D5_PIN, (0x20 & data)&&1 );
    GPIO_Write(LCD_DATA_PORT,LCD_D6_PIN, (0x40 & data)&&1 );
    GPIO_Write(LCD_DATA_PORT,LCD_D7_PIN, (0x80 & data)&&1 );

    GPIO_Write(LCD_RS_PORT, LCD_RS_PIN, 1);
    GPIO_Write(LCD_RW_PORT, LCD_RW_PIN, 0 );
    
    Delay_us(1);
    GPIO_Write(LCD_ENABLE_PORT, LCD_ENABLE_PIN, 1);
    Delay_us(10);
    GPIO_Write(LCD_ENABLE_PORT, LCD_ENABLE_PIN, 0);

    Delay_us(20);
  // least significant nibble
    GPIO_Write(LCD_DATA_PORT,LCD_D4_PIN, (0x01 & data)&&1 );
    GPIO_Write(LCD_DATA_PORT,LCD_D5_PIN, (0x02 & data)&&1 );
    GPIO_Write(LCD_DATA_PORT,LCD_D6_PIN, (0x04 & data)&&1 );
    GPIO_Write(LCD_DATA_PORT,LCD_D7_PIN, (0x08 & data)&&1 );

    Delay_us(1);
    GPIO_Write(LCD_ENABLE_PORT, LCD_ENABLE_PIN, 1);
    Delay_us(1);
    GPIO_Write(LCD_ENABLE_PORT, LCD_ENABLE_PIN, 0);
 
    Delay_us(100);//delay before starting new cycle

}

uint8_t LCD_Print_Line(char * str)  // returns number of printed
{
    uint8_t i = 0;
    while(str[i] != '\0'){
        
        if(i==16)
            LCD_Setcursor(1,2);

        LCD_Data(str[i++]);
    }
  
    i--;
    return i;
}

void LCD_Setcursor(uint8_t x , uint8_t y)
{
    unsigned char firstcharadd[] = { 0x80, 0xC0, 0x94, 0xD4};
    LCD_Instruction(firstcharadd[y-1] + x -1);
    Delay_ms(1);
}

void LCD_Clear(void)
{
     LCD_Instruction(0x01); // clear LCD
    
     LCD_Setcursor(1,1);
}
