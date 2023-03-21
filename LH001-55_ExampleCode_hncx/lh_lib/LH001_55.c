/*

Version:
Author: LH Software Group
Copyright
*/
#include "LH001_55.h"

void LH001_55_hw_reset()
{
	
  LH001_55_PDEXTRST_SET();
  for(uint32_t i=0;i<800000;i++);
  LH001_55_PDEXTRST_CLR();  //reset LH001_55
	for(uint32_t i=0;i<1000;i++)
	LH001_55_DELAY_10US();
  LH001_55_PDEXTRST_SET();  //reset LH001_55
  for(uint32_t i=0;i<10000;i++)
	LH001_55_DELAY_10US();
#if MANUAL_TRIM_ENABLE
	trim_osc();
#endif  
	
	LH001_55_adc_stop();
	
	LH001_55_rdatac_stop();
	
}

void LH001_55_adc_go()
{
#if ADC_CONV_START_HW
    LH001_55_START_SET();
#else 
    SPI_CLR_CS();
    
    LH001_55_SpiTxRxByte(SPI_CMD_CONV_START);
    SPI_SET_CS();
    
#endif
}

void LH001_55_adc_stop()
{
#if ADC_CONV_START_HW
    LH001_55_START_CLR();
#else 
    SPI_CLR_CS();
    
    LH001_55_SpiTxRxByte(SPI_CMD_CONV_STOP);
    SPI_SET_CS();
    
#endif
}

void LH001_55_sw_reset(void)
{
    SPI_CLR_CS();
    //
    LH001_55_SpiTxRxByte(SPI_CMD_RESET);
    SPI_SET_CS();
    // 
}

void LH001_55_reset_fifo(void)
{
    SPI_CLR_CS();
    
    LH001_55_SpiTxRxByte(SPI_CMD_RST_FIFO);
    SPI_SET_CS();
     
}

void LH001_55_rdatac_start(void)
{
    SPI_CLR_CS();
    
    LH001_55_SpiTxRxByte(SPI_CMD_RDATAC);
	
    SPI_SET_CS();
    
}

void LH001_55_rdatac_stop(void)
{
    SPI_CLR_CS();
    
    LH001_55_SpiTxRxByte(SPI_CMD_SDATAC);
	
    SPI_SET_CS();
    
}


void LH001_55_write_regs(uint8_t addr, uint8_t *pRegs,uint8_t num)
{
    uint8_t *p = pRegs;
    uint8_t reg_addr;
#if SOFTWARE_SPI_CS
    SPI_CLR_CS();
	for(uint32_t t=0;t<5;t++);
#endif

    reg_addr = addr&0x1F;
    //
    if(addr < 32)
    {
        LH001_55_SpiTxRxByte(SPI_CMD_WREG_MSK|reg_addr);
        LH001_55_SpiTxRxByte(num-1);
        for(uint8_t i=0;i<num;i++)
        {
            LH001_55_SpiTxRxByte(p[i]);
        }
    }
    else if(addr < 63)
    {
        LH001_55_SpiTxRxByte(SPI_CMD_WREG_BK1_MSK|reg_addr);
        LH001_55_SpiTxRxByte(num-1);
        for(uint8_t i=0;i<num;i++)
        {
            LH001_55_SpiTxRxByte(p[i]);
        }
    }
    else if(addr == 63)
    {
        LH001_55_SpiTxRxByte(SPI_CMD_WREG_BK1_MSK|reg_addr);
        LH001_55_SpiTxRxByte(0);
        LH001_55_SpiTxRxByte(0x72);
        LH001_55_SpiTxRxByte(p[0]);
    }
    else
    {
        //extend address mapping
        LH001_55_SpiTxRxByte(SPI_CMD_WREG_BK1_MSK|31);
        LH001_55_SpiTxRxByte(0);
        LH001_55_SpiTxRxByte(0x72);
        LH001_55_SpiTxRxByte(0x01);
        //
#if SOFTWARE_SPI_CS
		for(uint32_t t=0;t<5;t++);
        SPI_SET_CS();
#endif

#if SOFTWARE_SPI_CS
        SPI_CLR_CS();
		for(uint32_t t=0;t<5;t++);
#endif
        //
		
        if(addr < (64+32))
        {
            LH001_55_SpiTxRxByte(SPI_CMD_WREG_MSK|reg_addr);
        }
        else 
        {
            LH001_55_SpiTxRxByte(SPI_CMD_WREG_BK1_MSK|reg_addr);
        }
        LH001_55_SpiTxRxByte(num-1);
        for(uint8_t i=0;i<num;i++)
        {
            LH001_55_SpiTxRxByte(p[i]);
        }
        //
#if SOFTWARE_SPI_CS
		for(uint32_t t=0;t<5;t++);
        SPI_SET_CS();

#endif
        //
        //clear address extention
#if SOFTWARE_SPI_CS
        SPI_CLR_CS();
		for(uint32_t t=0;t<5;t++);
#endif
        
        LH001_55_SpiTxRxByte(SPI_CMD_WREG_BK1_MSK|31);
        LH001_55_SpiTxRxByte(0);
        LH001_55_SpiTxRxByte(0x72);
        LH001_55_SpiTxRxByte(0x00);
    }

	  //
#if SOFTWARE_SPI_CS
	for(uint32_t t=0;t<5;t++);
    SPI_SET_CS();
#endif
}

void LH001_55_read_regs(uint8_t addr, uint8_t *pRegs,uint8_t num)
{
    uint8_t *p = pRegs;
    uint8_t reg_addr;
#if SOFTWARE_SPI_CS
    SPI_CLR_CS();
#endif
    reg_addr = addr&0x1F;
	  //

    if(addr < 32)
    {
        LH001_55_SpiTxRxByte(SPI_CMD_RREG_MSK|reg_addr);
        LH001_55_SpiTxRxByte(num-1);
        for(uint8_t i=0;i<num;i++)
        {
            p[i] = LH001_55_SpiTxRxByte(LH001_55_SPI_TX_DUMMY);
        }
    }
    else if(addr < 63)
    {
        LH001_55_SpiTxRxByte(SPI_CMD_RREG_BK1_MSK|reg_addr);
        LH001_55_SpiTxRxByte(num-1);
        for(uint8_t i=0;i<num;i++)
        {
            p[i] = LH001_55_SpiTxRxByte(LH001_55_SPI_TX_DUMMY);
        }
    }
    else if (addr == 63)
    {
        LH001_55_SpiTxRxByte(SPI_CMD_RREG_BK1_MSK|reg_addr);
        LH001_55_SpiTxRxByte(0);
        LH001_55_SpiTxRxByte(0x72);
        p[0] = LH001_55_SpiTxRxByte(LH001_55_SPI_TX_DUMMY);
    }
    else 
    {
        //extend address mapping
        LH001_55_SpiTxRxByte(SPI_CMD_WREG_BK1_MSK|31);
        LH001_55_SpiTxRxByte(0);
        LH001_55_SpiTxRxByte(0x72);
        LH001_55_SpiTxRxByte(0x01);
        //
#if SOFTWARE_SPI_CS
        SPI_SET_CS();
#endif
        //
#if SOFTWARE_SPI_CS
        SPI_CLR_CS();
#endif
        //
        if(addr < (64+32))
        {
            LH001_55_SpiTxRxByte(SPI_CMD_RREG_MSK|reg_addr);
        }
        else 
        {
            LH001_55_SpiTxRxByte(SPI_CMD_RREG_BK1_MSK|reg_addr);
        }
        LH001_55_SpiTxRxByte(num-1);
        for(uint8_t i=0;i<num;i++)
        {
            p[i] = LH001_55_SpiTxRxByte(LH001_55_SPI_TX_DUMMY);
        }
        //
#if SOFTWARE_SPI_CS
        SPI_SET_CS();
#endif
        //
        //clear address extention
#if SOFTWARE_SPI_CS
        SPI_CLR_CS();
#endif
        //
        LH001_55_SpiTxRxByte(SPI_CMD_WREG_BK1_MSK|31);
        LH001_55_SpiTxRxByte(0);
        LH001_55_SpiTxRxByte(0x72);
        LH001_55_SpiTxRxByte(0x00);
    }
    
    //
#if SOFTWARE_SPI_CS
    SPI_SET_CS();
#endif
}

void LH001_55_read_data(uint8_t *pData,uint8_t num)
{
    uint8_t *p = pData;
#if SOFTWARE_SPI_CS
    SPI_CLR_CS();
#endif
	  
    LH001_55_SpiTxRxByte(SPI_CMD_RDATA);
    for(uint8_t i=0;i<num;i++)
    {
        p[i] = LH001_55_SpiTxRxByte(LH001_55_SPI_TX_DUMMY);
    }
#if SOFTWARE_SPI_CS
		
    SPI_SET_CS();
#endif
}

void LH001_55_read_data_nofifo(ADC_DATA_NOFIFO_t *pData)
{
    uint8_t dat[6];
#if SOFTWARE_SPI_CS
    SPI_CLR_CS();
#endif
    LH001_55_SpiTxRxByte(SPI_CMD_RDATA);
    for(uint32_t i=0;i<6;i++)
    {
        dat[i] = LH001_55_SpiTxRxByte(LH001_55_SPI_TX_DUMMY);
    }
#if SOFTWARE_SPI_CS
    SPI_SET_CS();
#endif
    pData->reserved0 = 0;
    pData->start = dat[0]>>4;
    pData->loffstat = ((dat[0]&0x0F)<<1)|(dat[1]>>7);
    pData->gpio = (dat[1]>>5)&0x03;
    pData->reserved1 = ((dat[1]&0x1F)<<8) | dat[2];
    pData->data = (dat[3]<<16) | (dat[4]<<8) |(dat[5]);
}

void LH001_55_read_data_fifo(ADC_DATA_FIFO_t *pData)
{
    uint8_t dat[6];
#if SOFTWARE_SPI_CS
    SPI_CLR_CS();
#endif
    LH001_55_SpiTxRxByte(SPI_CMD_RDATA);
    for(uint32_t i=0;i<6;i++)
    {
        dat[i] = LH001_55_SpiTxRxByte(LH001_55_SPI_TX_DUMMY);
    }
#if SOFTWARE_SPI_CS
    SPI_SET_CS();
#endif
    pData->reserved0 = 0;
    pData->start = dat[0]>>4;
    pData->loffstat = ((dat[0]&0x0F)<<1)|(dat[1]>>7);
    pData->gpio = (dat[1]>>5)&0x03;
    pData->reserved1 = ((dat[1]&0x1F)<<8) | (dat[2]>>2);
    pData->data = ((dat[2]&0x03)<<22) | (dat[3]<<14) | (dat[4]<<6) |(dat[5]>>2);
    pData->tail = dat[5]&0x03;
}


/*!
    \brief initalize ADC

    Related registers: CONFIG1,BUFCON,ADCCTRL, MODCLK
    @param pSetup:
       typedef struct 
        {
            ///Sigma-Delta ADC modulator clock
            ///recommend to use 512K or 128K modulator clock,
            ///hihger modulator has better performance with cost of power
            ///ENUM_LH001_55_ADC_FMODCLK_512K
            ///ENUM_LH001_55_ADC_FMODCLK_128K
            uint32_t Fmodclk;
            ///COFIG1[0]:DR, oversampling rate for sinc3 filter, this is the final data rate
            ///0:Fmodclk/1024
            ///1:Fmodclk/512
            ///2:Fmodclk/256
            ///3:Fmodclk/128
            ///4:Fmodclk/64
            ///5:Fmodclk/32
            ///6:Fmodclk/16
            ///7:Fmodclk/1024
            uint32_t oversample_rate;
            ///ENUM_LH001_55_ADC_SINGLE, single conversion
            ///ENUM_LH001_55_ADC_CONTINOUS, continous conversion
            uint32_t conv_mode;
            ///reference selection
            ///ENUM_LH001_55_ADC_REF_2V, 2v adc internal reference
            ///ENUM_LH001_55_ADC_REF_2V5, 2.5V adc internal reference
            uint32_t ref_sel;
        }LH001_55_ADC_INIT_t; 
*/
void LH001_55_adc_init(LH001_55_ADC_INIT_t *pInit)
{
    uint8_t val;

	if(pInit->Fmodclk == ENUM_LH001_55_ADC_FMODCLK_512K)
	{
			LH001_55_post_setup();
			val = 0x35;  
			LH001_55_write_regs(0x4E,&val,1);
	}
	else
	{
		LH001_55_post_setup();
		val = 0x10;  
		LH001_55_write_regs(0x4E,&val,1);
	}
    LH001_55_read_regs(ADDR_LH001_55_MODCLK,&val,1);
    val &= ~MSK_LH001_55_MODCLK_CD;
    val |= pInit->Fmodclk<<POS_LH001_55_MODCLK_CD;
    LH001_55_write_regs(ADDR_LH001_55_MODCLK,&val,1); 


    LH001_55_read_regs(ADDR_LH001_55_BUFCON,&val,1);
    val &= ~(MSK_LH001_55_BUFCON_EN2P5);
    val |= (pInit->ref_sel<<POS_LH001_55_BUFCON_EN2P5)|MSK_LH001_55_BUFCON_AVDD_DIV2|MSK_LH001_55_BUFCON_ENREF;
    LH001_55_write_regs(ADDR_LH001_55_BUFCON,&val,1); 

    LH001_55_read_regs(ADDR_LH001_55_CONFIG1,&val,1);
    val &= ~(MSK_LH001_55_CONFIG1_DR|MSK_LH001_55_CONFIG1_SGLESHOT);
    val |= (pInit->oversample_rate<<POS_LH001_55_CONFIG1_DR)|(pInit->conv_mode<<POS_LH001_55_CONFIG1_SGLESHOT);
    LH001_55_write_regs(ADDR_LH001_55_CONFIG1,&val,1); 

    LH001_55_read_regs(ADDR_LH001_55_ADCCTRL,&val,1);
    val |= (MSK_LH001_55_ADCCTRL_ADCEN|MSK_LH001_55_ADCCTRL_AMPEN);
    LH001_55_write_regs(ADDR_LH001_55_ADCCTRL,&val,1); 
}

/*!
    \brief PGA initialization

    Related registers: PGAGAIN, PGACTRL, PGACTRL1
    @param pInit 
        typedef struct 
        {
        ///PGA gain setting
        ///ENUM_LH001_55_PGA_PGAGAIN_1 
        ///ENUM_LH001_55_PGA_PGAGAIN_2 
        ///ENUM_LH001_55_PGA_PGAGAIN_3 
        ///ENUM_LH001_55_PGA_PGAGAIN_4 
        ///ENUM_LH001_55_PGA_PGAGAIN_6 
        ///ENUM_LH001_55_PGA_PGAGAIN_8 
        ///ENUM_LH001_55_PGA_PGAGAIN_12
        ///ENUM_LH001_55_PGA_PGAGAIN_24
        ///ENUM_LH001_55_PGA_PGAGAIN_48
        uint32_t gain;
        ///0, do not bypass
        ///1, bypass pga
        uint32_t pga_bypass;
        ///ENUM_LH001_55_PGA_POWER_LP, low power mode
        ///ENUM_LH001_55_PGA_POWER_HP, high power mode
        uint32_t power_mode;
        /// common mode voltage sense function, used for RLD
        ///0, disable
        ///1, enable
        uint32_t comm_sense_en;
        }LH001_55_PGA_INIT_t;
*/
void LH001_55_pga_init(LH001_55_PGA_INIT_t *pInit)
{
    uint8_t val;

    val = (pInit->gain)&MSK_LH001_55_PGAGAIN;
    LH001_55_write_regs(ADDR_LH001_55_PGAGAIN,&val,1); 

    LH001_55_read_regs(ADDR_LH001_55_PGACTRL1,&val,1);
    val &= ~(MSK_LH001_55_PGACTRL1_CHOP|MSK_LH001_55_PGACTRL1_CMSNS);
    val |= (pInit->comm_sense_en<<POS_LH001_55_PGACTRL1_CMSNS)|(pInit->pga_chop<<POS_LH001_55_PGACTRL1_CHOP);
    LH001_55_write_regs(ADDR_LH001_55_PGACTRL1,&val,1); 

    val = (pInit->pga_bypass<<POS_LH001_55_PGACTRL_BYPASS)|(pInit->power_mode<<POS_LH001_55_PGACTRL_LP);
    val &= ~MSK_LH001_55_PGACTRL_PD; //enable PGA
    LH001_55_write_regs(ADDR_LH001_55_PGACTRL,&val,1); 
}

void LH001_55_spi_daisy_mode(uint32_t enable)
{
    uint8_t val;
    val = (uint8_t)LH001_55_USERKEY;
    LH001_55_write_regs(ADDR_LH001_55_USERKEY,&val,1);
    LH001_55_read_regs(ADDR_LH001_55_CLKCON,&val,1);        
    val &= (~MSK_LH001_55_CLKCON_CLKEN);
    if(enable == LH_ENABLE)
    {
        val |= (ENUM_LH001_55_CLKCON_OSCOUT<<POS_LH001_55_CLKCON_CLKEN); //output clock
    }
    else  //disable daisy chain
    {
        val |= (ENUM_LH001_55_CLKCON_OSCINT<<POS_LH001_55_CLKCON_CLKEN); //internal osc only
    }
    LH001_55_write_regs(ADDR_LH001_55_CLKCON,&val,1); 

    LH001_55_read_regs(ADDR_LH001_55_SPICTRL,&val,1);        
    val &= (~MSK_LH001_55_SPICTRL_DAISYIN);
    if(enable == LH_ENABLE)
    {
        val |= MSK_LH001_55_SPICTRL_DAISYIN/*|MSK_LH001_55_SPICTRL_FIFOEN*/;    //Better use FIFO mode in daisychain
    }    
    LH001_55_write_regs(ADDR_LH001_55_SPICTRL,&val,1); 
}

void LH001_55_adc_channel(uint32_t chP, uint32_t chN)
{
    uint8_t val;
    val = (chP<<POS_LH001_55_ADCCHCON_PSEL)\
            |(chN<<POS_LH001_55_ADCCHCON_NSEL);
    LH001_55_write_regs(ADDR_LH001_55_ADCCHCON,&val,1);
}

/*!
    @param code: adc raw code
    @param ref: adc referece in mv, 2000 or 2500
*/
float LH001_55_adc_code2mv(uint32_t code, uint32_t ref)
{
    int32_t dat;
    float rlt;
    if(code & (1<<23))
        dat = (int)((0xFFu<<24)|code);
    else
        dat = (int)code;
    rlt = dat*2.0*ref/((1<<24)-1);
    return rlt;
}

void LH001_55_userkey_unlock()
{
    uint8_t val;
    val = (uint8_t)LH001_55_USERKEY_F2M;
    LH001_55_write_regs(ADDR_LH001_55_USERKEY,&val,1);
}


/*
    set current source to AIN4 or AIN5
    example: LH001_55_Isource_cfg(1,CURRENT_SOURCE_MAG_50uA,MSK_LH001_55_IEXECON_AIN4)
    @param Isrc:
        typedef enum{
        CURRENT_SOURCE_MAG_100nA = 0,
        CURRENT_SOURCE_MAG_50uA,
        CURRENT_SOURCE_MAG_100uA,
        CURRENT_SOURCE_MAG_250uA,
        CURRENT_SOURCE_MAG_500uA,
        CURRENT_SOURCE_MAG_750uA,
        CURRENT_SOURCE_MAG_1mA,
        }CURRENT_SRC_MAG_t;
    @param channel: 
        - MSK_LH001_55_IEXECON_AIN4, current source connect to AIN4
        - MSK_LH001_55_IEXECON_AIN5, current source connect to AIN5

*/
void LH001_55_Isource_cfg(uint32_t enable,CURRENT_SRC_MAG_t Isrc,uint32_t channel)
{
    uint8_t val;
    if(enable > 0)
    {
        LH001_55_read_regs(ADDR_LH001_55_IEXEMAG,&val,1);
        if (channel == MSK_LH001_55_IEXECON_AIN4)
        {
            val &= ~MSK_LH001_55_IEXEMAG_AIN4;
            val |= (Isrc<<POS_LH001_55_IEXEMAG_AIN4);
        }
        else if(channel == MSK_LH001_55_IEXECON_AIN5)
        {
            val &= ~MSK_LH001_55_IEXEMAG_AIN5;
            val |= (Isrc<<POS_LH001_55_IEXEMAG_AIN5);
        }
        LH001_55_write_regs(ADDR_LH001_55_IEXEMAG,&val,1);
        

        val = MSK_LH001_55_IEXECON_EN | (channel);
        if (Isrc == CURRENT_SOURCE_MAG_100nA)
        {
            val |= MSK_LH001_55_IEXECON_EN100N;
        }
        LH001_55_write_regs(ADDR_LH001_55_IEXECON,&val,1);

    }
    else
    {
        val = 0;
        LH001_55_write_regs(ADDR_LH001_55_IEXECON,&val,1);
        LH001_55_write_regs(ADDR_LH001_55_IEXEMAG,&val,1);
    }
    
}

/*
    Enter standby mode
    call lhxxx_wakeup function to wakeup.
*/
void LH001_55_standby(void)
{
    uint8_t reg_addr;
	
	//write PD.all to 0
    LH001_55_userkey_unlock();
	LH001_55_post_setup();
#if SOFTWARE_SPI_CS
    SPI_CLR_CS();
#endif
    reg_addr = ADDR_LH001_55_PLTFMPD&0x1F;
    LH001_55_DELAY_10US();
	
		//extend address mapping
		LH001_55_SpiTxRxByte(SPI_CMD_WREG_BK1_MSK|31);
		LH001_55_SpiTxRxByte(0);
		LH001_55_SpiTxRxByte(0x72);
		LH001_55_SpiTxRxByte(0x01);
		LH001_55_DELAY_10US();
#if SOFTWARE_SPI_CS
		SPI_SET_CS();
#endif
		LH001_55_DELAY_10US();
#if SOFTWARE_SPI_CS
		SPI_CLR_CS();
#endif
		LH001_55_DELAY_10US();

		LH001_55_SpiTxRxByte(SPI_CMD_WREG_MSK|reg_addr);
		LH001_55_SpiTxRxByte(0);
    LH001_55_SpiTxRxByte(0);
		
		LH001_55_DELAY_10US();
#if SOFTWARE_SPI_CS
		SPI_SET_CS();
#endif


		//write PD.all to 1
		LH001_55_DELAY_10US();
#if SOFTWARE_SPI_CS
     SPI_CLR_CS();
#endif
    LH001_55_DELAY_10US();
    LH001_55_SpiTxRxByte(SPI_CMD_WREG_BK1_MSK|31);
    LH001_55_SpiTxRxByte(0);
    LH001_55_SpiTxRxByte(0x72);
    LH001_55_SpiTxRxByte(0x00);
	LH001_55_DELAY_10US();
#if SOFTWARE_SPI_CS
    SPI_SET_CS();
#endif
		LH001_55_DELAY_10US();
    LH001_55_userkey_unlock();
		
		LH001_55_DELAY_10US();
#if SOFTWARE_SPI_CS
    SPI_CLR_CS();
#endif
    reg_addr = ADDR_LH001_55_PLTFMPD&0x1F;
    LH001_55_DELAY_10US();
		//extend address mapping
		LH001_55_SpiTxRxByte(SPI_CMD_WREG_BK1_MSK|31);
		LH001_55_SpiTxRxByte(0);
		LH001_55_SpiTxRxByte(0x72);
		LH001_55_SpiTxRxByte(0x01);
		LH001_55_DELAY_10US();
#if SOFTWARE_SPI_CS
		SPI_SET_CS();
#endif
		LH001_55_DELAY_10US();
#if SOFTWARE_SPI_CS
		SPI_CLR_CS();
#endif
		LH001_55_DELAY_10US();

		LH001_55_SpiTxRxByte(SPI_CMD_WREG_MSK|reg_addr);
		LH001_55_SpiTxRxByte(0);
    LH001_55_SpiTxRxByte(MSK_LH001_55_PLTFMPD_PDALL);
	//LH001_55_SpiTxRxByte((1<<3)|(1<<6)|(1<<5)|(1<<4));

		
		LH001_55_DELAY_10US();
#if SOFTWARE_SPI_CS
		SPI_SET_CS();
#endif

}

/*
    Any read to LH device will wakeup system
*/
void LH001_55_wakeup(void)
{
    uint8_t val;
    LH001_55_read_regs(ADDR_LH001_55_CHIPID,&val,1);	//read any register to wake up system
    for(uint32_t i=0;i<100;i++);
	
    
    //clear address extention
#if SOFTWARE_SPI_CS
        SPI_CLR_CS();
#endif
    
    LH001_55_SpiTxRxByte(SPI_CMD_WREG_BK1_MSK|31);
    LH001_55_SpiTxRxByte(0);
    LH001_55_SpiTxRxByte(0x72);
    LH001_55_SpiTxRxByte(0x00);

	  
#if SOFTWARE_SPI_CS
    SPI_SET_CS();
#endif
		
}


 void LH001_55_post_setup()
{

    uint8_t RegAddr;

    SPI_CLR_CS();
    LH001_55_DELAY_10US();
    LH001_55_SpiTxRxByte(31 | 0xc0);
    LH001_55_SpiTxRxByte(0x00);
    LH001_55_SpiTxRxByte(0x72);
    LH001_55_SpiTxRxByte(0x01);
    LH001_55_DELAY_10US();
    SPI_SET_CS();

    LH001_55_DELAY_10US();

    SPI_CLR_CS();
    LH001_55_DELAY_10US();
    RegAddr = ADDR_LH001_55_KEY0 & 0x1F;
    LH001_55_SpiTxRxByte(RegAddr | 0xc0);
    LH001_55_SpiTxRxByte(0x01);
    LH001_55_SpiTxRxByte(0xac);
    LH001_55_SpiTxRxByte(0xec);
    LH001_55_DELAY_10US();
    SPI_SET_CS();

    LH001_55_DELAY_10US();

    SPI_CLR_CS();
    LH001_55_DELAY_10US();
    LH001_55_SpiTxRxByte(31 | 0xc0);
    LH001_55_SpiTxRxByte(0x00);
    LH001_55_SpiTxRxByte(0x72);
    LH001_55_SpiTxRxByte(0x00);
    LH001_55_DELAY_10US();
    SPI_SET_CS();
}


/*
    @param clkSrc: 
        ENUM_LH001_55_OUTCLK_0       
        ENUM_LH001_55_OUTCLK_OSC     
        ENUM_LH001_55_OUTCLK_SYSCLK  
        ENUM_LH001_55_OUTCLK_MODCLK  
        ENUM_LH001_55_OUTCLK_LEADOFF 
        ENUM_LH001_55_OUTCLK_CHOP    
    @param pin:
        ENUM_LH001_55_OUTCLK_DRDY
        ENUM_LH001_55_OUTCLK_INTB
*/
void LH001_55_output_clk(uint32_t clkSrc, uint32_t pin)
{
    uint8_t val;
    val = (clkSrc<<POS_LH001_55_OUTCLK_SEL) | (pin<<POS_LH001_55_OUTCLK_PIN);
    LH001_55_write_regs(ADDR_LH001_55_OUTCLK,&val,1);
}

void LH001_55_reg_dump(REG_DUMP_t *pRegs,uint8_t num)
{
    for(uint32_t i=0;i<num;i++)
    {
        LH001_55_read_regs(pRegs[i].addr,&(pRegs[i].val),1);        
    }
}

uint32_t LH001_55_dac_mv2code(uint32_t mv){
	uint32_t code;
  if (mv==2500)
		code = 0xFFF;
	else
		code = (uint32_t)(mv*((1<<12)/2500.0));
	return code;
}

void LH001_55_dac_config(uint32_t gain_enable,uint32_t dac_rate){
	uint8_t reg;
	LH001_55_read_regs(ADDR_LH001_55_DACMUX,&reg,1);
	reg |= 1<<5;
	LH001_55_write_regs(ADDR_LH001_55_DACMUX,&reg,1);
}

void LH001_55_dac_enable(){
	uint8_t reg;
	
	reg = 0x20;
	LH001_55_userkey_unlock();
	LH001_55_write_regs(ADDR_LH001_55_DACCON,&reg,1);

	LH001_55_read_regs(ADDR_LH001_55_DACMUX,&reg,1);
	reg |= 1<<5;
	LH001_55_write_regs(ADDR_LH001_55_DACMUX,&reg,1);

}

void LH001_55_dac_disable(){
	uint8_t reg;
	
	reg = 0x11;
	LH001_55_userkey_unlock();
	LH001_55_write_regs(ADDR_LH001_55_DACCON,&reg,1);
}

void LH001_55_dac_code(uint16_t code){
	uint8_t reg;
	reg = code&0xff;
	LH001_55_write_regs(ADDR_LH001_55_DACCODE0,&reg,1);
	reg = code>>8;
	LH001_55_write_regs(ADDR_LH001_55_DACCODE1,&reg,1);
}

void LH001_55_tia_config(uint32_t enable, RTIA_Type rtia){
    uint8_t reg;
		LH001_55_read_regs(ADDR_LH001_55_DACMUX,&reg,1);
		reg |= (1<<5)|1;
		LH001_55_write_regs(ADDR_LH001_55_DACMUX,&reg,1);
    reg = (enable<<POS_LH001_55_TIACON_TIAEN) | (rtia<<POS_LH001_55_TIACON_GAIN);
    LH001_55_write_regs(ADDR_LH001_55_TIACON,&reg,1);
}
	



