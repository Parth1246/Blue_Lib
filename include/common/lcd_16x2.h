/**
 * @file  <lcd_16x2.h>
 * @brief <header file for declaration d& Documantation of functions and MACROs of gpio.c>
 *
 * This implementation file provides declaration   of initialization, set
 * reset and read GPIO functions for stm32f103xx platform.
 *
 * @author <Kaushal dekivadia>
 * @date   <august 6 2021>
 *
 */


#ifndef _LCD_16x2_H
#define _LCD_16x2_H

#include <stdint.h>
#include "gpio.h"
#include "stm32f10x.h"

/**
* can change LCD pins by redefining them( pins and port) in main file after inclusion of header file
* 
*/

#define LCD_DATA_PORT    GPIOA
#define LCD_RW_PORT      GPIOB
#define LCD_RS_PORT      GPIOB
#define LCD_ENABLE_PORT  GPIOB

#define LCD_D4_PIN 8   /// data pins
#define LCD_D5_PIN 9
#define LCD_D6_PIN 10
#define LCD_D7_PIN 11

/**
* register select 
*/
#define LCD_RS_PIN     6  /// register select
#define LCD_RW_PIN     7  /// read-write mode (also can connect RW pin to -GND)
#define LCD_ENABLE_PIN 8  /// Enable




/**
 * @brief function to Initialization process for 16x2
 * 
 * @param void
 * 
 *This function initialize diffrent GPIOs for LCD as below
 * 
 *  - 4-bit mode
 *  - clears lcd and cursor enable
 * 
 * @return void
 */
void LCD_Init();


/**
 * @brief function to send instruction to LCD
 * 
 * @param cmd - 8-bit command  
 * 
 * @return void
 */
void LCD_Instruction(uint8_t cmd);


/**
 * @brief function to send data to LCD
 * 
 * @param cmd - 8-bit data or character
 * 
 * @return void
 */
void LCD_Data(uint8_t data);


/**
 * @brief function to display line(String) on LCD
 * 
 * @param str - buffer or string (length should be less than 16)   
 * 
 * @return number of characters successfully displayed
 */
uint8_t LCD_Print_Line( char * str);


/**
 * @brief function to set cursor position
 * 
 * @param x - row position
 * @param y - column position
 * 
 * @return void
 */
void LCD_Setcursor(uint8_t x , uint8_t y);

/**
 * @brief function to clear the screen of lcd
 * 
 * @param void
 * 
 * @return void
 */
void LCD_Clear(void);


#endif 
