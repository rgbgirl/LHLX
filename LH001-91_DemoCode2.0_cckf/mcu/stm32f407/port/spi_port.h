/*

Version:
Author: LH Software Group
Copyright
*/

#ifndef __STM_LH_SPI_H
#define __STM_LH_SPI_H

#include "LH001_91.h"
#include "stm32f4xx_conf.h"
#include "stm32f4xx_spi.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_syscfg.h"
#include "stm32f4xx_exti.h"
#include "misc.h"

#define GPIO_EMULATE_SPI 0

//some LDO has enable pin, If an ldo used for LHxxx,
//this macro will set a GPIO from host to control this LDO enable pin
#define LDO_ENABLE_PIN_EN

//setup GPIO for drdy interrupt
#define DRDY_INT_ENABLE 1

/*
Connection between stm32 mother board and LH001_91 board

 STM32            |     LH001_91
 ------------------------------------
 PB12/SPI2_CS     |     LH_CS
 PB13/SPI2_SCLK   |     LH_SCLK
 PB14/SPI2_MISO   |     LH_DOUT
 PB15/SPI2_MOSI   |     LH_DIN
 PC8              |     PWDN
 PC7              |     START
 PC6              |     DRDY
 #ifdef LDO_ENABLE_PIN_EN
 PG6              |     AFE_EN(P2-7)  //used when user has ldo enable pin
 #endif
*/

/*
    1 - Use GPIO control SPI cs
    0 - Use SPI CS pin
*/
#ifndef SOFTWARE_SPI_CS
#define SOFTWARE_SPI_CS      1
#endif

#if SOFTWARE_SPI_CS
#define SPI_SET_CS()  GPIOB->BSRRL=GPIO_Pin_12
#define SPI_CLR_CS()  GPIOB->BSRRH=GPIO_Pin_12
#endif
#if GPIO_EMULATE_SPI
#define SPI_SET_SCLK()  GPIOB->BSRRL=GPIO_Pin_13
#define SPI_CLR_SCLK()  GPIOB->BSRRH=GPIO_Pin_13
#define SPI_SET_MOSI()  GPIOB->BSRRL=GPIO_Pin_15
#define SPI_CLR_MOSI()  GPIOB->BSRRH=GPIO_Pin_15
#endif

#define stm_lh_pdextrst_set() GPIOC->BSRRL=GPIO_Pin_8
#define stm_lh_pdextrst_clr() GPIOC->BSRRH=GPIO_Pin_8
#define stm_lh_start_set()    GPIOC->BSRRL=GPIO_Pin_7
#define stm_lh_start_clr()    GPIOC->BSRRH=GPIO_Pin_7
#ifdef LDO_ENABLE_PIN_EN
#define stm_giga_afeen_set()    GPIOG->BSRRL=GPIO_Pin_6
#endif

void stm_lh_spi_init(void);
uint8_t stm_lh_spi_txrx8bit(uint8_t tx_byte);
void stm_lh_delay_10us(void);

#endif
