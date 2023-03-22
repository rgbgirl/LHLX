/*

Version:
Author: LH Software Group
Copyright
*/

#include "uart_print.h"


void debug_pin_init()
{
  GPIO_InitTypeDef  GPIO_InitStructure;
   RCC_AHB1PeriphClockCmd(DEBUG_PIN_RCC, ENABLE);

  GPIO_InitStructure.GPIO_Pin = DEBUG_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(DEBUG_PIN_PORT, &GPIO_InitStructure);
}

void debug_pin_set()
{
    DEBUG_PIN_PORT->BSRRL = DEBUG_PIN;
}
void debug_pin_clr()
{
    DEBUG_PIN_PORT->BSRRH = DEBUG_PIN;
}
void debug_pin_toggle()
{
    uint32_t d = DEBUG_PIN_PORT->ODR;
    d = d^DEBUG_PIN;
    DEBUG_PIN_PORT->ODR = d;
}


/*!
    Initialization for debug functions like uart print and toggle GPIO
*/
void uart_print_init()
{
    //-----------  DEBUG GPIO Init  ----------------

#if DEBUG_UART_PORT_NUM==1
USART_InitTypeDef USART_InitStructure;
  
  /* USARTx configured as follows:
        - BaudRate = 115200 baud  
        - Word Length = 8 Bits
        - One Stop Bit
        - No parity
        - Hardware flow control disabled (RTS and CTS signals)
        - Receive and transmit enabled
  */
  USART_InitStructure.USART_BaudRate = UART_BAUDRATE;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

  //STM_EVAL_COMInit(COM1, &USART_InitStructure);

  GPIO_InitTypeDef GPIO_InitStructure;

  /* Enable GPIO clock */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOA, ENABLE);

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
  

  /* Connect PXx to USARTx_Tx*/
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_USART1);

  /* Connect PXx to USARTx_Rx*/
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_USART1);

  /* Configure USART Tx as alternate function  */
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  /* Configure USART Rx as alternate function  */
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  /* USART configuration */
  USART_Init(USART1, &USART_InitStructure);
    
  /* Enable USART */
  USART_Cmd(USART1, ENABLE);

#elif DEBUG_UART_PORT_NUM==3
    //--------------  DEBUG PRINT Init --------------
    USART_InitTypeDef USART_InitStructure;
  
  /* USARTx configured as follows:
        - BaudRate = 115200 baud  
        - Word Length = 8 Bits
        - One Stop Bit
        - No parity
        - Hardware flow control disabled (RTS and CTS signals)
        - Receive and transmit enabled
  */
  USART_InitStructure.USART_BaudRate = UART_BAUDRATE;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

  //STM_EVAL_COMInit(COM1, &USART_InitStructure);

  GPIO_InitTypeDef GPIO_InitStructure;

  /* Enable GPIO clock */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC | RCC_AHB1Periph_GPIOC, ENABLE);

  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
  

  /* Connect PXx to USARTx_Tx*/
  GPIO_PinAFConfig(GPIOC, GPIO_PinSource10, GPIO_AF_USART3);

  /* Connect PXx to USARTx_Rx*/
  GPIO_PinAFConfig(GPIOC, GPIO_PinSource11, GPIO_AF_USART3);

  /* Configure USART Tx as alternate function  */
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOC, &GPIO_InitStructure);

  /* Configure USART Rx as alternate function  */
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
  GPIO_Init(GPIOC, &GPIO_InitStructure);

  /* USART configuration */
  USART_Init(USART3, &USART_InitStructure);
    
  /* Enable USART */
  USART_Cmd(USART3, ENABLE);

#endif

}

#ifdef __ICCARM__
int putc(char c)
{
    #if DEBUG_UART_PORT_NUM==1
    while((USART1->SR & 0X40) == 0); 
    USART1->DR = (u8) c;    
    return c;
    #elif #if DEBUG_UART_PORT_NUM==3
    while((USART3->SR & 0X40) == 0); 
    USART3->DR = (u8) c;    
    return c;
    #endif
}
#else 
int fputc(int ch, FILE *f)
{
    #if DEBUG_UART_PORT_NUM==1
    while((USART1->SR & 0X40) == 0); 
    USART1->DR = (u8) ch;    
    return ch;
    #elif #if DEBUG_UART_PORT_NUM==3
    while((USART1->SR & 0X40) == 0); 
    USART1->DR = (u8) ch;    
    return ch;
    #endif

}
#endif

