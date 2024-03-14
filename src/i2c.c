/**
 * @file i2c.c
 * @author Parth Varsani (parthvarsani45@gmail.com)
 * 
 * @brief - Abstraction of I2C initialization, read, write operations 
 * 
 *        -  This implementation file provides an abstraction of initialization, read
 *            and write to i2C
 * 
 * @version 0.1
 * @date 2022-02-19
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <stdint.h>
#include "stm32f10x.h"
#include "gpio.h"
#include "i2c.h"


void I2C_Init(I2C_TypeDef *I2Cx , uint8_t speed_mode){

    //Enable clock for Alternate function IO 
    RCC->APB2ENR |= (RCC_APB2ENR_AFIOEN);

    if(I2Cx == I2C1){

        // Enable clock for I2C1 
        RCC->APB1ENR |= (RCC_APB1ENR_I2C1EN);

        // GPIO-Pin initialization for I2C1
        GPIO_Init(GPIOB,6,OUTPUT_50,AF_OPENDRAIN); // SCL1 pin - B6 - (Serial Clock) 
        GPIO_Init(GPIOB,7,OUTPUT_50,AF_OPENDRAIN); // SDA1 pin - B7 - (Serial Data)

    }
    else if(I2Cx == I2C2){
        
        // Enable clock for I2C2 
        RCC->APB1ENR |= (RCC_APB1ENR_I2C2EN);

        // GPIO-Pin initialization for I2C1
        GPIO_Init(GPIOB,10,OUTPUT_50,AF_OPENDRAIN); // SCL2 pin - B10 - (Serial Clock) 
        GPIO_Init(GPIOB,11,OUTPUT_50,AF_OPENDRAIN); // SDA2 pin - B11 - (Serial Data)
    }

    // Reset the I2C

    I2Cx->CR1 |= (I2C_CR1_SWRST);
    I2Cx->CR1 &= ~(I2C_CR1_SWRST);

    //Set the I2C clock

    I2Cx->CR2 |= (36<<0); // 36 MHz -> PCLK1 Frequency 

    if(speed_mode == I2C_SM){  // Standard Mode

        I2Cx->CCR |= (0xB4<<0);
        I2Cx->TRISE |= 36 + 1; // TRISE = Tr(SCL)/Tpclk1 + 1
    }
    else{                      // Fast Mode

        I2Cx->CCR |= (0x21<<0);
        I2Cx->CCR |= (I2C_CCR_FS);
        I2Cx->TRISE |= 11 + 1; // // TRISE = Tr(SCL)/Tpclk1 + 1
    }

    // Enable i2c peripheral

    I2Cx->CR1 |= (I2C_CR1_PE);
    
}


void I2C_Start(I2C_TypeDef *I2Cx){

    I2Cx->CR1 |= (I2C_CR1_ACK); // Enable Acknowledgement bit
    I2Cx->CR1 |= (I2C_CR1_START); // send start condition

    while(!(I2Cx->SR1 & I2C_SR1_SB)); // wait for start condition to get generated
}

void I2C_Stop(I2C_TypeDef *I2Cx){

    I2Cx->CR1 |= (I2C_CR1_STOP);

}

void I2C_SendAddress(I2C_TypeDef *I2Cx ,uint8_t address){

    I2Cx->DR = address;  // send address to data register
    
    while(!(I2Cx->SR1 & I2C_SR1_ADDR)); // wait for End of Address transmission 
   
    uint8_t tmp = I2Cx->SR1; // read both status register to clear ADDR bit
    tmp = I2Cx->SR2;
}

void I2C_Write(I2C_TypeDef *I2Cx,uint8_t data){

    while(!(I2Cx->SR1 & I2C_SR1_TXE));

    I2Cx->DR = data;

    while(!(I2Cx->SR1 & I2C_SR1_BTF));

}

void I2C_SendString(I2C_TypeDef *I2Cx,char *str,uint8_t size){

    while(!(I2Cx->SR1 & I2C_SR1_TXE));

    while(size--){
        
        I2C_Write(I2Cx,(uint8_t)*str);
        str++;
    }

}

void I2C_Read(I2C_TypeDef *I2Cx,uint8_t reg_addr,char *buff , uint8_t size){

    uint8_t received  = 0;

    if(size == 1){

        I2Cx->DR = reg_addr;
        while(!(I2Cx->SR1 & I2C_SR1_ADDR));

        I2Cx->CR1 &= ~(I2C_CR1_ACK); //clear ACK bit
        int8_t temp = I2Cx->SR1 | I2Cx->SR2; // read both status register to clear ADDR bit

        I2Cx->CR1 |= (I2C_CR1_STOP);

        while(!(I2Cx->SR1 & I2C_SR1_RXNE));
        buff[0] = I2Cx->DR;
    }
    else{

        I2Cx->DR = reg_addr;
        while(!(I2Cx->SR1 & I2C_SR1_ADDR));
        int8_t temp = I2Cx->SR1 | I2Cx->SR2; // read both status register to clear ADDR bit

        while(received < size-2){

            while(!(I2Cx->SR1 & I2C_SR1_RXNE));
            buff[received++] = I2Cx->DR;

            I2Cx->CR1 |= (I2C_CR1_ACK); //send the acknowledge bit

        }

        while(!(I2Cx->SR1 & I2C_SR1_RXNE)); // wait till rx buffer is full

        buff[received++] = I2Cx->DR;

        I2Cx->CR1 &= ~(I2C_CR1_ACK); //clear ACK bit
        I2Cx->CR1 |= (I2C_CR1_STOP);

        while(!(I2Cx->SR1 & I2C_SR1_RXNE));

        buff[received] = I2Cx->DR;

    }
}

