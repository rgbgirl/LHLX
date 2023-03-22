/*
Author: LH Software Group
*/

#ifndef __TRIM_H__
#define __TRIM_H__


#include "stm32f4xx_conf.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_syscfg.h"
#include "stm32f4xx_flash.h"
#include "misc.h"
#include "LH001_91.h"
//#include "timer.h"

#define BLIND_TRIM_EN 1

#define AVDD_REG_MV 1805

#define ADDR_OSCTCTRIM2M   0x5C
#define ADDR_OSCFREQTRIM2M 0x5B
#define ADDR_TRIM_VREF     0x4A
#define ADDR_TRIM_LDO      0x56

#define POS_TRIM_VREF 2
#define RST_TRIM_VREF 0x10
#define HPREF_TRIM_STEP 1.5f
#define POS_LDOTRIM_DLDO 0
#define POS_LDOTRIM_ALDO 4
#define MSK_LDOTRIM_DLDO (0xF<<POS_LDOTRIM_DLDO)
#define MSK_LDOTRIM_ALDO (0xF<<POS_LDOTRIM_ALDO)



/*modify based on MCU flash information*/
#define MCU_FLASH_SIZE     (64*1024)
#define MCU_FLASH_START_ADDR  (0x08000000)
#define MCU_FLASH_SECTOR_SIZE (1024*16)
/*end*/


#define TRIM_VALUE_FLASH_OFFSET 512
#define TRIM_VALUE_WATER_MARK_ADDR   (MCU_FLASH_START_ADDR+MCU_FLASH_SIZE-TRIM_VALUE_FLASH_OFFSET)
#define TRIM_VALUE_WATER_MARK_VALUE 0x4C4855AA
#define TRIM_VALUE_OSC_ADDR   (TRIM_VALUE_WATER_MARK_ADDR+8)  

#define TRIM_OSC_ADC_INT_CNT   6
#define TRIM_OSC_CHECK_STM32_TIMER 0

/* Base address of the Flash sectors */ 
#define ADDR_FLASH_SECTOR_0     ((uint32_t)0x08000000) /* Base address of Sector 0, 16 Kbytes   */
#define ADDR_FLASH_SECTOR_1     ((uint32_t)0x08004000) /* Base address of Sector 1, 16 Kbytes   */
#define ADDR_FLASH_SECTOR_2     ((uint32_t)0x08008000) /* Base address of Sector 2, 16 Kbytes   */
#define ADDR_FLASH_SECTOR_3     ((uint32_t)0x0800C000) /* Base address of Sector 3, 16 Kbytes   */
#define ADDR_FLASH_SECTOR_4     ((uint32_t)0x08010000) /* Base address of Sector 4, 64 Kbytes   */
#define ADDR_FLASH_SECTOR_5     ((uint32_t)0x08020000) /* Base address of Sector 5, 128 Kbytes  */
#define ADDR_FLASH_SECTOR_6     ((uint32_t)0x08040000) /* Base address of Sector 6, 128 Kbytes  */
#define ADDR_FLASH_SECTOR_7     ((uint32_t)0x08060000) /* Base address of Sector 7, 128 Kbytes  */
#define ADDR_FLASH_SECTOR_8     ((uint32_t)0x08080000) /* Base address of Sector 8, 128 Kbytes  */
#define ADDR_FLASH_SECTOR_9     ((uint32_t)0x080A0000) /* Base address of Sector 9, 128 Kbytes  */
#define ADDR_FLASH_SECTOR_10    ((uint32_t)0x080C0000) /* Base address of Sector 10, 128 Kbytes */
#define ADDR_FLASH_SECTOR_11    ((uint32_t)0x080E0000) /* Base address of Sector 11, 128 Kbytes */

void trim_osc(void);
void trim_ref_buf(uint8_t code);
void trim_aldo(uint8_t code);
void trim_dldo(uint8_t code);
void trim_offset_gain(uint32_t gain);
void trim_write_offset(int32_t offset);
void trim_write_gain(uint32_t gain);

static uint32_t GetSector(uint32_t Address);

#endif

