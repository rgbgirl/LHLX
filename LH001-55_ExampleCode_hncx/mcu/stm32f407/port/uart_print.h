/*

Version:
Author: LH Software Group
Copyright
*/

#ifndef __UART_PRINT_H
#define __UART_PRINT_H

#include "stdio.h"
#include "stm32f4xx_conf.h"
#include "stm32f4xx_usart.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"

#define DEBUG_PIN_PORT      GPIOA
#define DEBUG_PIN           GPIO_Pin_1
#define DEBUG_PIN_RCC       RCC_AHB1Periph_GPIOA

//#define  UART_BAUDRATE            115200
#define  UART_BAUDRATE            5000000

#define DEBUG_UART_PORT_NUM       1
//#define DEBUG_UART_PORT_NUM       3

void debug_pin_init(void);
void debug_pin_set(void);
void debug_pin_clr(void);
void debug_pin_toggle(void);

void uart_print_init(void);


#endif
