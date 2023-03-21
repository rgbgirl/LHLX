;/**************************************************************************//**
; * @file     startup_ARMCM0.s
; * @brief    CMSIS Core Device Startup File for
; *           ARMCM0 Device Series
; * @version  V1.08
; * @date     23. November 2012
; *
; * @note
; *
; ******************************************************************************/
;/* Copyright (c) 2011 - 2012 ARM LIMITED
;
;   All rights reserved.
;   Redistribution and use in source and binary forms, with or without
;   modification, are permitted provided that the following conditions are met:
;   - Redistributions of source code must retain the above copyright
;     notice, this list of conditions and the following disclaimer.
;   - Redistributions in binary form must reproduce the above copyright
;     notice, this list of conditions and the following disclaimer in the
;     documentation and/or other materials provided with the distribution.
;   - Neither the name of ARM nor the names of its contributors may be used
;     to endorse or promote products derived from this software without
;     specific prior written permission.
;   *
;   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
;   AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
;   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
;   ARE DISCLAIMED. IN NO EVENT SHALL COPYRIGHT HOLDERS AND CONTRIBUTORS BE
;   LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
;   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
;   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
;   INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
;   CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
;   ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
;   POSSIBILITY OF SUCH DAMAGE.
;   ---------------------------------------------------------------------------*/
;/*
;//-------- <<< Use Configuration Wizard in Context Menu >>> ------------------
;*/


; <h> Stack Configuration
;   <o> Stack Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

Stack_Size      EQU     0x00000400

                AREA    STACK, NOINIT, READWRITE, ALIGN=3
Stack_Mem       SPACE   Stack_Size
__initial_sp


; <h> Heap Configuration
;   <o>  Heap Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

Heap_Size       EQU     0x00000400

                AREA    HEAP, NOINIT, READWRITE, ALIGN=3
__heap_base
Heap_Mem        SPACE   Heap_Size
__heap_limit


                PRESERVE8
                THUMB


; Vector Table Mapped to Address 0 at Reset

                AREA    RESET, DATA, READONLY
                EXPORT  __Vectors
                EXPORT  __Vectors_End
                EXPORT  __Vectors_Size

__Vectors       DCD     __initial_sp              ; Top of Stack
                DCD     Reset_Handler             ; Reset Handler
                DCD     NMI_Handler               ; NMI Handler
                DCD     HardFault_Handler         ; Hard Fault Handler
                DCD     MemFault_Handler          ; Reserved
                DCD     BusFault_Handler                         ; Reserved
                DCD     UsageFault_Handler                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     SVC_Handler               ; SVCall Handler
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     PendSV_Handler            ; PendSV Handler
                DCD     SysTick_Handler           ; SysTick Handler

                ; External Interrupts
                DCD     PVD_IRQHandler            ;  0:  Watchdog Timer
                DCD     0        ;  1:  
                DCD     0        ;  2:  
                DCD     RTC_IRQHandler            ;  3:  RTC
                DCD     FLASH_IRQHandler          ;  4:  FLASH
                DCD     RCC_IRQHandler            ;  5:  RCC
                DCD     EXTI0_IRQHandler          ;  6: EXTI0
                DCD     EXTI1_IRQHandler          ;  7:  EXTI1
                DCD     EXTI2_IRQHandler          ;  8:  EXTI2
                DCD     EXTI3_IRQHandler          ;  9:  EXTI3
                DCD     EXTI4_IRQHandler           ; 10: EXTI4
                DCD     DMA_IRQHandler             ; 11: 
                DCD     SPI1_IRQHandler                  ; 12:
                DCD     UART1_IRQHandler                 ; 13: 
                DCD     RTC_ALARM_IRQHandler             ; 14:
                DCD     QSPI_IRQHandlern                 ; 15: 
                DCD     BEEPER_IRQHandler                ; 16:
                DCD     LCD_IRQHandler                   ; 17:
                DCD     ADC_IRQHandler                    ; 18:
                DCD     COMP_IRQHandler                   ; 19: 
                DCD     0                         ; 20: 
                DCD     0                         ; 21: 
                DCD     0                         ; 22: 
                DCD     EXINT7_5_IRQHandler                         ; 23: 
                DCD     TIMER1_BRK_IRQHandler                         ; 24: 
                DCD     TIMER1_UP_IRQHandler                         ; 25: 
                DCD     TIMER1_TRIG_COM_IRQHandler                         ; 26: 
                DCD     TIMER1_CC_IRQHandler                         ; 27: 
                DCD     TIMER2_IRQHandler       ; 28: 
                DCD     0                         ; 29: 
                DCD     I2C_ER_IRQHandler          ; 30: 
                DCD     I2C_EV_IRQHandler            ; 31: 
__Vectors_End

__Vectors_Size  EQU     __Vectors_End - __Vectors

                AREA    |.text|, CODE, READONLY


; Reset Handler

Reset_Handler   PROC
                EXPORT  Reset_Handler             [WEAK]
                IMPORT  SystemInit
                IMPORT  __main
				

                LDR     R0, =SystemInit
                BLX     R0
                LDR     R0, =__main
                BX      R0
                ENDP


; Dummy Exception Handlers (infinite loops which can be modified)

NMI_Handler     PROC
                EXPORT  NMI_Handler               [WEAK]
                B       .
                ENDP
HardFault_Handler\
                PROC
                EXPORT  HardFault_Handler         [WEAK]
                B       .
                ENDP
BusFault_Handler\
                PROC
                EXPORT  BusFault_Handler         [WEAK]
                B       .
                ENDP
MemFault_Handler\
                PROC
                EXPORT  MemFault_Handler         [WEAK]
                B       .
                ENDP
UsageFault_Handler\
                PROC
                EXPORT  UsageFault_Handler         [WEAK]
                B       .
                ENDP
SVC_Handler     PROC
                EXPORT  SVC_Handler               [WEAK]
                B       .
                ENDP
PendSV_Handler  PROC
                EXPORT  PendSV_Handler            [WEAK]
                B       .
                ENDP
SysTick_Handler PROC
                EXPORT  SysTick_Handler           [WEAK]
                B       .
                ENDP

Default_Handler PROC

				EXPORT  PVD_IRQHandler            [WEAK]		
				EXPORT  RTC_IRQHandler            [WEAK]	
				EXPORT  FLASH_IRQHandler          [WEAK]	
				EXPORT  RCC_IRQHandler            [WEAK]	
				EXPORT  EXTI0_IRQHandler          [WEAK]	
				EXPORT  EXTI1_IRQHandler          [WEAK]	
				EXPORT  EXTI2_IRQHandler          [WEAK]	
				EXPORT  EXTI3_IRQHandler          [WEAK]	
				EXPORT  EXTI4_IRQHandler          [WEAK] 	
				EXPORT  DMA_IRQHandler            [WEAK] 	
				EXPORT  SPI1_IRQHandler           [WEAK] 	
				EXPORT  UART1_IRQHandler          [WEAK] 	
				EXPORT  RTC_ALARM_IRQHandler      [WEAK] 	
				EXPORT  QSPI_IRQHandlern          [WEAK] 	
				EXPORT  BEEPER_IRQHandler         [WEAK] 	
				EXPORT  LCD_IRQHandler            [WEAK] 	
				EXPORT  ADC_IRQHandler            [WEAK] 	
				EXPORT  COMP_IRQHandler           [WEAK] 		
				EXPORT  EXINT7_5_IRQHandler       [WEAK] 	
				EXPORT  TIMER1_BRK_IRQHandler     [WEAK] 	
				EXPORT  TIMER1_UP_IRQHandler      [WEAK] 	
				EXPORT  TIMER1_TRIG_COM_IRQHandler [WEAK] 	
				EXPORT  TIMER1_CC_IRQHandler      [WEAK] 	
				EXPORT  TIMER2_IRQHandler         [WEAK]		
				EXPORT  I2C_ER_IRQHandler         [WEAK] 
                EXPORT  I2C_EV_IRQHandler         [WEAK] 

WDT_IRQHandler           
PVD_IRQHandler           
RTC_IRQHandler           
FLASH_IRQHandler         
RCC_IRQHandler           
EXTI0_IRQHandler         
EXTI1_IRQHandler         
EXTI2_IRQHandler         
EXTI3_IRQHandler         
EXTI4_IRQHandler         
DMA_IRQHandler           
SPI1_IRQHandler          
UART1_IRQHandler         
RTC_ALARM_IRQHandler     
QSPI_IRQHandlern         
BEEPER_IRQHandler        
LCD_IRQHandler           
ADC_IRQHandler           
COMP_IRQHandler          
EXINT7_5_IRQHandler      
TIMER1_BRK_IRQHandler    
TIMER1_UP_IRQHandler     
TIMER1_TRIG_COM_IRQHandler
TIMER1_CC_IRQHandler     
TIMER2_IRQHandler        
I2C_ER_IRQHandler        
I2C_EV_IRQHandler        
                B       .

                ENDP


                ALIGN


; User Initial Stack & Heap

                IF      :DEF:__MICROLIB

                EXPORT  __initial_sp
                EXPORT  __heap_base
                EXPORT  __heap_limit

                ELSE

                IMPORT  __use_two_region_memory
                EXPORT  __user_initial_stackheap

__user_initial_stackheap PROC
                LDR     R0, =  Heap_Mem
                LDR     R1, =(Stack_Mem + Stack_Size)
                LDR     R2, = (Heap_Mem +  Heap_Size)
                LDR     R3, = Stack_Mem
                BX      LR
                ENDP

                ALIGN

                ENDIF


                END
