/**
 * @file  <spi.h>
 * @brief <header file for declaration & Documantation of functions and MACROs of spi.c>
 *
 *  This implementation file provides declaration for functions to initialize, read
 *  and write SPI for stm32f10xx microcontrollers
 *
 * @author <Kaushal dekivadia>
 * @date   <sept 13 2021>
 *
 */

#ifndef __SPI_H
#define __SPI_H

#include <stdint.h>
#include "stm32f10x.h"
#include "gpio.h"

#define MASTER 0U
#define SLAVE 1U

#define MSB 2U
#define LSB 3U


#define SPI_NSS_ON(SPIx) ( (SPIx == SPI1) ? (GPIO_Reset(GPIOA,4)) : (GPIO_Reset(GPIOB,12))) // NSS pin control MACRO functions 

#define SPI_NSS_OFF(SPIx) ( (SPIx == SPI1) ? (GPIO_Set(GPIOA,4)) : (GPIO_Set(GPIOB,12))) 




/**
 * @brief function to Initialization SPI Peripheral
 * 
 * @param SPIx         - SPI peripherel number (SPI1 or SPI2 )
 * @param mode         - mode of SPI           (MASTER or SLAVE)
 * @param c_pol        - clock polarity        (0 or 1)
 * @param c_phase      - clock phase           (0 or 1)
 * @param first_tr_bit - firsr transmitted bit (MSB or LSB)
 * @param size_data    - data frame size       (8 or 16) 
 * 
 * 
 *This function initialize SPI peripheral and defines various specifications
 * 
 * @return void
 */

extern void SPI_Init(SPI_TypeDef *SPIx , uint8_t mode , uint8_t c_pol , uint8_t c_phase, uint8_t first_tr_bit,uint8_t size_data);


/**
 * @brief function to set clock prescaler for SCLK pin
 * 
 * @param SPIx      - SPI peripherel number (SPI1 or SPI2 ) 
 * @param prescaler - prescaler (2,4,8,16,32,64,128,256)
 * 
 * @return void
 */
extern void SPI_Set_Clk_Prescaler(SPI_TypeDef *SPIx,uint32_t prescaler);


/**
 * @brief function to Send byte in buffer register
 * 
 * @param SPIx      - SPI peripherel number (SPI1 or SPI2 ) 
 * @param data      - 8 or 16 bit data
 * 
 * @return - 8 or 16 bit recieved data
 */

extern uint16_t SPI_SendByte(SPI_TypeDef *SPIx , uint16_t data);



/**
 * @brief function to write SPI register
 * 
 * @param SPIx      - SPI peripherel number (SPI1 or SPI2 ) 
 * @param address   - address of slave register
 * @param value     - 8 or 16 bit data to be send
 * 
 * @return - void
 */

extern void SPI_WriteReg(SPI_TypeDef *SPIx,uint16_t address , uint16_t value);



/**
 * @brief function to Read byte from Rx buffer register
 * 
 * @param SPIx      - SPI peripherel number (SPI1 or SPI2 ) 
 * @param address   - address of slave register
 * 
 * @return - 8 or 16 bit recieved data
 */

extern uint16_t SPI_ReadReg(SPI_TypeDef* SPIx,uint16_t address);



 #endif
