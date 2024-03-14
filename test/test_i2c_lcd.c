/**
 * @file   <test_lcd.c>
 * @brief  <test file for basic LCD functions>
 * 	    
 * 	    displays some line on LCD using I2C functions
 *
 * @author <Parth Varsani>
 * @date   <Mar 10 2022>
 *
 */

#include "stm32f10x.h"
#include "gpio.h"
#include "delay.h"
#include "i2c_lcd.h"
#include <stdio.h>

#include "qfpio.h"
#include "qfplib.h"


/* #define I2C_module I2C1 */
/* #define I2C_LCD_ADD (0x27 << 1) */

int main(){
 	float a = 37.28;
    char str[7];
    qfp_float2str(a,str,FMT_D);

    I2C_LCD_Init();
    I2C_LCD_Clear();

    Delay_ms(1000);
	while(1){

			I2C_LCD_Clear();
			I2C_LCD_Print_Line(str);
			Delay_ms(3000);

			I2C_LCD_Clear();
			I2C_LCD_Print_Line("PROJECT TITLE :");
			I2C_LCD_Setcursor(1,2);
			I2C_LCD_Print_Line("BLUE-LIBv2.0");
			Delay_ms(3000);

			I2C_LCD_Clear();
			I2C_LCD_Print_Line("TEST:           I2C_LCD HAL");
			Delay_ms(3000);
	}

	return 0;
}