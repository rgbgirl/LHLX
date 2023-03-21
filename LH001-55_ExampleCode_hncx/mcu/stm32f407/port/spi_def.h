/*

Version:
Author: LH Software Group
Copyright
*/

#ifndef __SPIDEF_H
#define __SPIDEF_H

#include "spi_port.h"

#define LH3001_SPI_TX_DUMMY      0xFF

#define LH3001_DELAY_10US()       stm_lh_delay_10us()    //rough delay, only requires longer than 10us
#define LH3001_START_SET()        stm_lh_start_set()
#define LH3001_START_CLR()        stm_lh_start_clr()
#define LH3001_PDEXTRST_SET()     stm_lh_pdextrst_set()
#define LH3001_PDEXTRST_CLR()     stm_lh_pdextrst_clr()
#define LH3001_Spi_Init()         stm_lh_spi_init()
#define LH3001_SpiTxRxByte(tx)    stm_lh_spi_txrx8bit(tx)


#endif
