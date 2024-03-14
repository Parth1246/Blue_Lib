/**
 * @file   <test_spi.c>
 * @brief  <test file for basic spi functions>
 * 	    
 * 	    - to test basic SPI HAL function and send few bytes of data to capture on logic analyzer
 *
 * @author <Kaushal dekivadia>
 * @date   <Mar 11 2022>
 *
 */
#include "stm32f10x.h"
#include "gpio.h"
#include "delay.h"
#include "spi.h"

int main(){

	Delay_Init();
	SPI_Init(SPI2,MASTER,0,0,MSB,8);
	SPI_Set_Clk_Prescaler(SPI2,16);



	while(1){
		SPI_WriteReg(SPI2,0x33,0XAA);
		Delay_us(1);


		SPI_WriteReg(SPI2,0x54,0X34);
		Delay_us(1);
			
		SPI_WriteReg(SPI2,0x16,0X40);
		Delay_us(1);
	}

	return 0;
}
