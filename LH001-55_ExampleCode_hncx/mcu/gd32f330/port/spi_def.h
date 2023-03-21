/*

Version:
Author: LH Software Group
Copyright
*/

#ifndef __SPIDEF_H
#define __SPIDEF_H

#include "spi_port.h"

#define LH001_55_SPI_TX_DUMMY      0xFF

#define LH001_55_DELAY_10US()       stm_lh_delay_10us()    //rough delay, only requires longer than 10us
#define LH001_55_START_SET()        stm_lh_start_set()
#define LH001_55_START_CLR()        stm_lh_start_clr()
#define LH001_55_PDEXTRST_SET()     stm_lh_pdextrst_set()
#define LH001_55_PDEXTRST_CLR()     stm_lh_pdextrst_clr()
#define LH001_55_Spi_Init()         stm_lh_spi_init()
#define LH001_55_SpiTxRxByte(tx)    stm_lh_spi_txrx8bit(tx)


#endif
