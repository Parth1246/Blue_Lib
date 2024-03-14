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
#include "i2c.h"

int main(){

   
    Delay_Init();
    I2C_Init(I2C1,I2C_SM);

    Delay_ms(1000);
    while(1){
        
        I2C_Start(I2C1);
        I2C_SendAddress(I2C1,0x27<<1);
        I2C_Write(I2C1,0x33);
        I2C_Stop(I2C1);

    }

    return 0;
}