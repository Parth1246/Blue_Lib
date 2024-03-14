/**
 * @file   <spi.c>
 * @brief  <Abstraction of SPI initialization, read, write operations>
 *
 * This implementation file provides an abstraction of initialization, read
 * and write to SPI
 *
 * @author <Parth Varsani>
 * @date   <mar 13 2022>
 *
 */
 
#include <stdint.h>
#include "spi.h"
#include "stm32f10x.h"
#include "gpio.h"


void SPI_Init(SPI_TypeDef *SPIx , uint8_t mode , uint8_t c_pol , uint8_t c_phase, uint8_t first_tr_bit,uint8_t size_data){

    if(SPIx == SPI1){
      
         /// Enable clock for SPI1 and Alternate function IO 
         RCC->APB2ENR |= (RCC_APB2ENR_SPI1EN | RCC_APB2ENR_AFIOEN);
         
         /// GPIO-Pin initialization for SPI1
         GPIO_Init(GPIOA, 4, OUTPUT, PUSHPULL) ;    /// NSS1 pin - A4- (Chip select)
         GPIO_Set(GPIOA,4);
         GPIO_Init(GPIOA, 5, OUTPUT, AF_PUSHPULL);  /// SCK1 pin - A5 - (seriel clk output)
         GPIO_Init(GPIOA, 6, INPUT, PULL_UP);       /// MISO pin - A6 - (Master in slave out)
         GPIO_Init(GPIOA, 7, OUTPUT, AF_PUSHPULL);  /// MOSI pin - A7 - (Master out slave in)

    }else{

         // Enable clock for SPI2 and Alternate function IO 
         RCC->APB2ENR |= (RCC_APB2ENR_AFIOEN);
         RCC->APB1ENR |= (RCC_APB1ENR_SPI2EN);

          // GPIO-Pin initialization for SPI1
         GPIO_Init(GPIOB, 12, OUTPUT, PUSHPULL) ;    // NSS2 pin - B12- (Chip select)
         GPIO_Set(GPIOB,12);
         GPIO_Init(GPIOB, 13, OUTPUT, AF_PUSHPULL);  // SCK2 pin - B13 - (seriel clk output)
         GPIO_Init(GPIOB, 14, INPUT, PULL_UP);       // MISO pin - B14 - (Master in slave out)
         GPIO_Init(GPIOB, 15, OUTPUT, AF_PUSHPULL);  // MOSI pin - B15 - (Master out slave in)
     }

     if(mode == MASTER)        // master configuration enable
        SPIx->CR1 |= (1<<2);
     else
        SPIx->CR1 &= ~(1<<2);

     SPIx->CR1 |= (7<<3);    // seriel clk baudrate configuration - fPCLK/256 (default)


     SPIx->CR1 |= SPI_CR1_SSM ;   // software slave management enable
     SPIx->CR1 |= SPI_CR1_SSI;    // Internal slave select

     SPIx->CR1 |= SPI_CR1_SPE;    // SPI peripheral enable;
     

     
     if((c_pol == 0) && (c_phase == 0)){
        SPIx->CR1 &= ~(1<<0);  // clk_phase = 0
        SPIx->CR1 &= ~(1<<1);  // clk_pol = 0

     }else if((c_pol == 0) && (c_phase == 1)){
        SPIx->CR1 |=  (1<<0);  // clk_phase = 1
        SPIx->CR1 &= ~(1<<1);  // clk_pol = 0

     }else if((c_pol == 1) && (c_phase == 0)){
        SPIx->CR1 &= ~(1<<0);  // clk_phase = 0
        SPIx->CR1 |= (1<<1);  // clk_pol = 1

     }else{
        SPIx->CR1 |= (1<<0);  // clk_phase = 1
        SPIx->CR1 |= (1<<1);  // clk_pol = 1

     }

     

     if(size_data == 16)       // data frame format 
        SPIx->CR1 |= (1<<11);
     else
        SPIx->CR1 &= ~(1<<11);

     if(first_tr_bit == MSB) 
        SPIx->CR1 &= ~(1<<7); // MSB transmitted first
     else
        SPIx->CR1 |= (1<<7);  //LSB transmitted first


     SPIx->CR2 = 0x0000 ;  // no interrupt or DMA used
}

void SPI_Set_Clk_Prescaler(SPI_TypeDef *SPIx,uint32_t prescaler)
{
   if(prescaler == 2){
      SPIx->CR1 &= ~(7<<3);             // sclk speed = Pclk/2 = 72 MHz / 2 = 36 MHz

   }else if(prescaler == 4){
      SPIx->CR1 &= ~(6<<3);            
      SPIx->CR1 |= (1<<3);

   }else if(prescaler == 8){
      SPIx->CR1 &= ~(5<<3);
      SPIx->CR1 |= (2<<3);

   }else if(prescaler == 16){
      SPIx->CR1 &= ~(4<<3);
      SPIx->CR1 |= (3<<3);

   }else if(prescaler == 32){
      SPIx->CR1 &= ~(3<<3);
      SPIx->CR1 |= (4<<3);

   }else if(prescaler == 64){
      SPIx->CR1 &= ~(2<<3);
      SPIx->CR1 |= (5<<3);

   }else if(prescaler == 128){
      SPIx->CR1 &= ~(1<<3);
      SPIx->CR1 |= (6<<3);

   }else if(prescaler == 256){   // by default in initialization function
      SPIx->CR1 |= (7<<3);

   }
   
}


uint16_t SPI_SendByte(SPI_TypeDef *SPIx , uint16_t data){

   while(!(SPIx->SR & (1<<1)));     // wait till Tx buffer is empty
      SPIx->DR = data;

   while(!(SPIx->SR & (1<<0)));  // wait till Rx buffer gets full
      return SPIx->DR;
}


void SPI_WriteReg(SPI_TypeDef *SPIx,uint16_t address , uint16_t value){
   SPI_NSS_ON(SPIx);             
   SPI_SendByte(SPIx,address);
   SPI_SendByte(SPIx,value);
   SPI_NSS_OFF(SPIx);
}

uint16_t SPI_ReadReg(SPI_TypeDef* SPIx,uint16_t address){

   uint16_t value;
   SPI_NSS_ON(SPIx);
   SPI_SendByte(SPIx,address);
   value = SPI_SendByte(SPIx,0x00);
   SPI_NSS_OFF(SPIx);

   return value;
}
