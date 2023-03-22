/*
Author: LH Software Group
*/

#include "trim.h"
#include "lh001_91.h"

uint16_t t_cnt[TRIM_OSC_ADC_INT_CNT] = {0};


#define TRIM_OSC_FACTOR    1.0f
#if BLIND_TRIM_EN
static void osc_blind_trim()
{
	uint8_t val;
	val = 0x58;
	lh001_91_write_regs(ADDR_LH001_91_USERKEY, &val,1);  //write 0x58 to change clock setting
    lh001_91_pltformkey_unlock();
    val = 0x5B;
    lh001_91_write_regs(ADDR_LH001_91_OSCFREQTRIM2M, &val,1);	//bigger then slower
	val = 0x50;
    lh001_91_write_regs(ADDR_LH001_91_OSCFREQTRIM16M, &val,1);	//bigger then slower
}

#else
static uint32_t do_trim_osc()
{
    uint8_t  regarray[12];
    uint32_t t_sum;
    uint8_t trim_vale;
    uint32_t DRDYB_Pin_State;
    uint32_t i,t_avg;
    uint8_t val;
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;

    //Init ADC and clock settings
    trim_vale = 0x5E;
    val = 0x58;
    lh001_91_write_regs(ADDR_LH001_91_USERKEY, &val,1);  //write 0x58 to change clock setting
    lh001_91_pltformkey_unlock();
    val = 0x4C;
    lh001_91_write_regs(ADDR_LH001_91_OSCTCTRIM2M, &val,1);  //OSC:d74
    val = 0x58;
    lh001_91_write_regs(ADDR_LH001_91_USERKEY, &val,1);  //write 0x58 to change clock setting
    lh001_91_pltformkey_unlock();
    val = 0x5B;
    lh001_91_write_regs(ADDR_LH001_91_OSCFREQTRIM2M, &val,1);	//bigger then slower
    val = 0x1;
    lh001_91_write_regs(ADDR_LH001_91_OSCCON, &val,1); //Enable 2MHz output at full current mode
    val = 0x1;
    lh001_91_write_regs(ADDR_LH001_91_SYSCLK, &val,1); //
    val = 0x58;
    lh001_91_write_regs(ADDR_LH001_91_USERKEY, &val,1);  //write 0x58 to change clock setting
    lh001_91_pltformkey_unlock();
    val = 7;
    lh001_91_write_regs(ADDR_LH001_91_CLKCON, &val,1);
    val = 0x58;
    lh001_91_write_regs(ADDR_LH001_91_USERKEY, &val,1);  //write 0x58 to change clock setting
    lh001_91_pltformkey_unlock();
    val = 0x10;
    lh001_91_write_regs(ADDR_LH001_91_MODCLK, &val,1);   //128k:0x10  512k:0x04
    val = 0;
    lh001_91_write_regs(ADDR_LH001_91_SPICTRL, &val,1);
    val = ENUM_LH001_91_ADC_DR_DIV128;
    lh001_91_write_regs(ADDR_LH001_91_CONFIG1, &val,1); //Fmod/512
    val = 0x30;
    lh001_91_write_regs(ADDR_LH001_91_BUFCON, &val,1);//0x10, ADCREF=2.0V; 0x30, ADCREF=2.5V
    val = 0x10;
    lh001_91_write_regs(ADDR_LH001_91_ADCCHCON, &val,1);//0xfa, short to half VDD; 0xFB, internal shor; 0x10 AIN0/AIN1 select
    val = 0x03;
    lh001_91_write_regs(ADDR_LH001_91_ADCCTRL, &val,1);
    val = 0x07;
    lh001_91_write_regs(ADDR_LH001_91_PGAGAIN, &val,1); //0x0,gain=1;0x1,gain=2;0x2,gain=3;0x3,gain=4;0x4,gain=6;0x5,gain=8;0x6,gain=12;0x7,gain=24;0x8,gain=48
    val = 0x00;
    lh001_91_write_regs(ADDR_LH001_91_PGACTRL, &val,1); //PGA in HP mode
    val = 0x3;
    lh001_91_write_regs(ADDR_LH001_91_PGACTRL1, &val,1);	//0x0,1/64 modulator clock;	0x3,1/8 modulator clock

    //init timer
    t_sum = 0;
    //note default pclk1 is 168M/4
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE); 

    TIM_TimeBaseInitStructure.TIM_Period = 0xFFFF; 
    TIM_TimeBaseInitStructure.TIM_Prescaler=2; 	//168M/2=81MHz, 27MHz
    TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; 
    TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
    /*check timer using LED*/
#if TRIM_OSC_CHECK_STM32_TIMER
/*note there is a x2 from pclk to Tclk*/
	TIM_TimeBaseInitStructure.TIM_Prescaler=(uint32_t)(168.0/4*1000); //2K Hz
    TIM_TimeBaseInitStructure.TIM_Period = 10000*2; //10 second
    TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);
#endif

    TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);
    TIM_SetCounter(TIM3,0);
	
#if TRIM_OSC_CHECK_STM32_TIMER
	TIM_Cmd(TIM3,ENABLE);   //start timer
	GPIO_ToggleBits(GPIOA, GPIO_Pin_1 );//PA1 LED
    //for(i=0;i<10;i++)
		while(1)
    {
			if(TIM_GetITStatus(TIM3,TIM_IT_Update)==SET)
			{
			GPIO_ToggleBits(GPIOA, GPIO_Pin_1 );//PA1 LED
				TIM_ClearITPendingBit(TIM3,TIM_IT_Update);
			}
    }
    TIM_Cmd(TIM3,DISABLE);
#endif

    //start ADC
    lh001_91_rdatac_start();
    lh001_91_adc_go();

    //wait for timeout counter
	TIM_SetCounter(TIM3,0);
    do 
    {
        DRDYB_Pin_State	=	GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_6);
    }while(DRDYB_Pin_State!=0); //wait for first ADC data ready
	TIM_Cmd(TIM3,ENABLE);   //start timer
    lh001_91_read_data(regarray, 6);
    for(i=0;i<TRIM_OSC_ADC_INT_CNT;i++)
    {
        do 
        {
            DRDYB_Pin_State	=	GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_6);
        }while(DRDYB_Pin_State!=0); //wait for ADC data ready
        t_cnt[i] = TIM_GetCounter(TIM3);
        TIM_SetCounter(TIM3,0);
        lh001_91_read_data(regarray,6); //clear drdy
    }
    TIM_Cmd(TIM3,DISABLE);
    TIM_SetCounter(TIM3,0);
    lh001_91_adc_stop();
    lh001_91_rdatac_stop();

	for(i=3;i<TRIM_OSC_ADC_INT_CNT;i++)
    {
        t_sum += t_cnt[i];
    }
	t_avg = (uint32_t)(t_sum*1.0/(TRIM_OSC_ADC_INT_CNT-3));
	//1000 is the target
	trim_vale = (uint8_t)(trim_vale*1.0*27000*TRIM_OSC_FACTOR/t_avg);
    val = 0x58;
	lh001_91_write_regs(ADDR_LH001_91_USERKEY, &val,1);  //write 0x58 to change clock setting
	lh001_91_pltformkey_unlock();
    val = trim_vale;
	lh001_91_write_regs(ADDR_LH001_91_OSCFREQTRIM2M, &val,1);	//bigger then slower
	
    return (uint32_t)val;
}
#endif //BLIND_TRIM_EN

void trim_osc()
{
#if BLIND_TRIM_EN
	osc_blind_trim();
#else
    uint32_t flash_watermark;
    uint32_t trim_value;
    uint32_t sector_num;
    uint32_t i;
    uint8_t val;
	GPIO_InitTypeDef GPIO_InitStructure;
	
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC , ENABLE);

        //PDEXTRST pin Init
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC , ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
    stm_lh_pdextrst_set();
    //START PIN init
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
    stm_lh_start_clr();

    //DRDY PIN INIT
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
        //-------SPI PORT INIT
    /*!< Enable the SPI clock */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);
    /*!< Enable GPIO clocks */
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB , ENABLE);

    /*!< SPI pins configuration *************************************************/
    /*!< Connect SPI pins to AF5 */  
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource13, GPIO_AF_SPI2);
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource14, GPIO_AF_SPI2);
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource15, GPIO_AF_SPI2);
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_DOWN;
    /*!< SPI SCK pin configuration */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    /*!< SPI MOSI pin configuration */
    GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_13;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    /*!< SPI MISO pin configuration */
    GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_14;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    /*!< Configure sFLASH Card CS pin in output pushpull mode ********************/
#if SOFTWARE_SPI_CS
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
#else
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource12, GPIO_AF_SPI2);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
  
#endif
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    /*!< SPI configuration */
    SPI_InitTypeDef  SPI_InitStructure;

    SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
    SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
    SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
    SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
    SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
#if SOFTWARE_SPI_CS 
    SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
    SPI_SET_CS();
#else
    SPI_InitStructure.SPI_NSS = SPI_NSS_Hard;
#endif
    SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8;

    SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
    SPI_InitStructure.SPI_CRCPolynomial = 7;
    SPI_Init(SPI2, &SPI_InitStructure);

    /*!< Enable the SPI2  */
    SPI_Cmd(SPI2, ENABLE);

    flash_watermark = *((uint32_t *)(TRIM_VALUE_WATER_MARK_ADDR));
    trim_value= *((uint32_t *)(TRIM_VALUE_OSC_ADDR));
    if((flash_watermark==0xFFFFFFFF) && (trim_value==0xFFFFFFFF))
    {
        trim_value = do_trim_osc();
        //program trim to flash
        FLASH_Unlock();
        FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_OPERR | FLASH_FLAG_WRPERR | 
                  FLASH_FLAG_PGAERR | FLASH_FLAG_PGPERR|FLASH_FLAG_PGSERR); 
        sector_num = GetSector(TRIM_VALUE_WATER_MARK_ADDR);
        FLASH_EraseSector(sector_num, VoltageRange_3);
        FLASH_ProgramWord(TRIM_VALUE_WATER_MARK_ADDR, TRIM_VALUE_WATER_MARK_VALUE);
        FLASH_ProgramWord(TRIM_VALUE_OSC_ADDR, trim_value);
        for(i=0;i<1000;i++);
        //reset
        NVIC_SystemReset();
    }
    else if(flash_watermark == TRIM_VALUE_WATER_MARK_VALUE)
    {
        //update trim register
		val = 0x58;
        lh001_91_write_regs(ADDR_LH001_91_USERKEY, &val,1);  //write 0x58 to change clock setting
		lh001_91_pltformkey_unlock();
        val = trim_value;
	    lh001_91_write_regs(ADDR_LH001_91_OSCFREQTRIM2M, &val,1);
    }
    else 
    {
        //do nothing
    }  
		
		val = 0;  
    lh001_91_write_regs(ADDR_LH001_91_OUTCLK,&val,1);
#endif //no blind trim
}

#if (BLIND_TRIM_EN != 1)
/**
  * @brief  Gets the sector of a given address
  * @param  None
  * @retval The sector of a given address
  */
static uint32_t GetSector(uint32_t Address)
{
  uint32_t sector = 0;
  
  if((Address < ADDR_FLASH_SECTOR_1) && (Address >= ADDR_FLASH_SECTOR_0))
  {
    sector = FLASH_Sector_0;  
  }
  else if((Address < ADDR_FLASH_SECTOR_2) && (Address >= ADDR_FLASH_SECTOR_1))
  {
    sector = FLASH_Sector_1;  
  }
  else if((Address < ADDR_FLASH_SECTOR_3) && (Address >= ADDR_FLASH_SECTOR_2))
  {
    sector = FLASH_Sector_2;  
  }
  else if((Address < ADDR_FLASH_SECTOR_4) && (Address >= ADDR_FLASH_SECTOR_3))
  {
    sector = FLASH_Sector_3;  
  }
  else if((Address < ADDR_FLASH_SECTOR_5) && (Address >= ADDR_FLASH_SECTOR_4))
  {
    sector = FLASH_Sector_4;  
  }
  else if((Address < ADDR_FLASH_SECTOR_6) && (Address >= ADDR_FLASH_SECTOR_5))
  {
    sector = FLASH_Sector_5;  
  }
  else if((Address < ADDR_FLASH_SECTOR_7) && (Address >= ADDR_FLASH_SECTOR_6))
  {
    sector = FLASH_Sector_6;  
  }
  else if((Address < ADDR_FLASH_SECTOR_8) && (Address >= ADDR_FLASH_SECTOR_7))
  {
    sector = FLASH_Sector_7;  
  }
  else if((Address < ADDR_FLASH_SECTOR_9) && (Address >= ADDR_FLASH_SECTOR_8))
  {
    sector = FLASH_Sector_8;  
  }
  else if((Address < ADDR_FLASH_SECTOR_10) && (Address >= ADDR_FLASH_SECTOR_9))
  {
    sector = FLASH_Sector_9;  
  }
  else if((Address < ADDR_FLASH_SECTOR_11) && (Address >= ADDR_FLASH_SECTOR_10))
  {
    sector = FLASH_Sector_10;  
  }

  else/*(Address < FLASH_END_ADDR) && (Address >= ADDR_FLASH_SECTOR_11))*/
  {
    sector = FLASH_Sector_11;  
  }

  return sector;
}
#endif //BLIND_TRIM_EN


/*
    Trim ADC reference buffer, trim step 1.5mV
    default value is 0x10
*/
void trim_ref_buf(uint8_t code)
{
    uint8_t val;
    val = code;
    val = val << POS_TRIM_VREF;
    lh001_91_pltformkey_unlock();
    lh001_91_write_regs(ADDR_TRIM_VREF,&val,1);
}

/*
    Trim ALDO 
    0 ldo outputs 1.8V
    7 ldo outputs 1.98V
    8 ldo outputs 1.63V
    F ldo outputs 1.78V
*/
void trim_aldo(uint8_t code)
{
    uint8_t val;
    lh001_91_read_regs(ADDR_TRIM_LDO,&val,1);
    val &= ~(MSK_LDOTRIM_ALDO);
    val |= (code<<POS_LDOTRIM_ALDO);
    lh001_91_pltformkey_unlock();
    lh001_91_write_regs(ADDR_TRIM_LDO,&val,1);
}

void trim_dldo(uint8_t code)
{
    uint8_t val;
    lh001_91_read_regs(ADDR_TRIM_LDO,&val,1);
    val &= ~(MSK_LDOTRIM_DLDO);
    val |= (code<<POS_LDOTRIM_DLDO);
    lh001_91_pltformkey_unlock();
    lh001_91_write_regs(ADDR_TRIM_LDO,&val,1);
}

void trim_write_offset(int32_t offset)
{
    uint8_t val;
    lh001_91_userkey_unlock();	
	
	val = 2;	//MSB
	lh001_91_write_regs(ADDR_LH001_91_RWAB,&val,1);
	val = (uint8_t)(offset>>16);
    lh001_91_write_regs(ADDR_LH001_91_OFFSET, &val,1); 

	val = 1;	//second byte
	lh001_91_write_regs(ADDR_LH001_91_RWAB,&val,1);	
	val = (uint8_t)((offset>>8)&0xFF);
    lh001_91_write_regs(ADDR_LH001_91_OFFSET, &val,1); 
	
	val = 0;	//LSB
	lh001_91_write_regs(ADDR_LH001_91_RWAB,&val,1);	
	val = (uint8_t)((offset)&0xFF);
    lh001_91_write_regs(ADDR_LH001_91_OFFSET, &val,1); 
}

void trim_write_gain(uint32_t gain)
{
    uint8_t val;
    lh001_91_userkey_unlock();	
	
	val = 2;	//MSB
	lh001_91_write_regs(ADDR_LH001_91_RWAB,&val,1);
	val = (uint8_t)(gain>>16);
    lh001_91_write_regs(ADDR_LH001_91_GAIN, &val,1); 

	val = 1;	//second byte
	lh001_91_write_regs(ADDR_LH001_91_RWAB,&val,1);	
	val = (uint8_t)((gain>>8)&0xFF);
    lh001_91_write_regs(ADDR_LH001_91_GAIN, &val,1); 
	
	val = 0;	//LSB
	lh001_91_write_regs(ADDR_LH001_91_RWAB,&val,1);	
	val = (uint8_t)((gain)&0xFF);
    lh001_91_write_regs(ADDR_LH001_91_GAIN, &val,1); 
}

/*
Gain offset calibration using internal reference
Reference needs to be trimmed first.
Short AIN0 to AVDD_REG, Short AIN1 to GND
re-calibrate when PGA changes.
PGA gain options:
ENUM_LH001_91_PGA_PGAGAIN_1 
ENUM_LH001_91_PGA_PGAGAIN_2 
ENUM_LH001_91_PGA_PGAGAIN_3 
ENUM_LH001_91_PGA_PGAGAIN_4 
ENUM_LH001_91_PGA_PGAGAIN_6 
ENUM_LH001_91_PGA_PGAGAIN_8 
ENUM_LH001_91_PGA_PGAGAIN_12
ENUM_LH001_91_PGA_PGAGAIN_24
ENUM_LH001_91_PGA_PGAGAIN_48
*/
void trim_offset_gain(uint32_t gain)
{
    uint64_t target_code;
    uint32_t G;
    ADC_DATA_NOFIFO_t dat;
	LH001_91_ADC_INIT_t adc_init;
    LH001_91_PGA_INIT_t pga_init;
    int32_t code[17];
    int32_t avg_code;
    int32_t sum_code;
    uint32_t i;
    uint32_t DRDYB_Pin_State;


    lh001_91_rdatac_stop();
	lh001_91_adc_stop();

    pga_init.gain = gain;
    pga_init.pga_bypass = 0;
    pga_init.power_mode = ENUM_LH001_91_PGA_POWER_HP;
    pga_init.comm_sense_en = 1;
	pga_init.pga_chop = ENUM_LH001_91_PGA_CHOP_DIV32;
    lh001_91_pga_init(&pga_init);

	adc_init.Fmodclk = ENUM_LH001_91_ADC_FMODCLK_128K;
    adc_init.oversample_rate = ENUM_LH001_91_ADC_DR_DIV512; //update rate = Fmodclk/oversample_rate
    adc_init.conv_mode = ENUM_LH001_91_ADC_CONTINOUS;
    adc_init.ref_sel = ENUM_LH001_91_ADC_REF_2V5;
    lh001_91_adc_init(&adc_init);

    /*	DC mode for lower data rate
    lh001_91_pltformkey_unlock();
    lh001_91_write_regs(ADDR_LH001_91_MODCFG,&val,1);
    val &= ~(0x3);  //clear MODCFG.MD to 0
    lh001_91_write_regs(ADDR_LH001_91_MODCFG,&val,1);
    val = ENUM_LH001_91_ADC_AVG_10<<POS_LH001_91_CONFIG1_AVG;  
    lh001_91_write_regs(ADDR_LH001_91_CONFIG1,&val,1);
    */

    /*------------ Measuring offset with internal short --------------*/
	lh001_91_adc_channel(ENUM_LH001_91_ADCCHP_VCM,ENUM_LH001_91_ADCCHN_GND);
	//lh001_91_adc_channel(ENUM_LH001_91_ADCCHP_AIN0,ENUM_LH001_91_ADCCHN_AIN1);
	lh001_91_adc_go();
    lh001_91_rdatac_start();
    sum_code = 0;
    for(i=0;i<17;)
    {
        do 
        {
            DRDYB_Pin_State	=	GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_6);
        }while(DRDYB_Pin_State!=0); //wait for first ADC data ready
        lh001_91_read_data_nofifo(&dat);
		if(i!=0)
		{
			if(dat.data & (1<<23))
				code[i] = (int)((0xFFu<<24)|(dat.data));
			else
				code[i] = (int)(dat.data);
			sum_code += code[i];
		}
		i++;
    }
    
	avg_code = -(sum_code>>4);
    trim_write_offset(avg_code);

	lh001_91_adc_stop();
    lh001_91_rdatac_stop();
	
	for(uint32_t i=0;i<500000;i++);
#if 0
    /*------------ Measuring AVDD_REG  --------------*/
	lh001_91_adc_channel(ENUM_LH001_91_ADCCHP_AIN0,ENUM_LH001_91_ADCCHN_AIN1);
	//lh001_91_rdatac_start();
	lh001_91_adc_go();
    //lh001_91_rdatac_start();
    sum_code = 0;
    for(i=0;i<17;)
    {
        do 
        {
            DRDYB_Pin_State	=	GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_6);
        }while(DRDYB_Pin_State!=0); //wait for first ADC data ready
        lh001_91_read_data_nofifo(&dat);
		if(i!=0)
		{
			if(dat.data & (1<<23))
				code[i] = (int)((0xFFu<<24)|(dat.data));
			else
				code[i] = (int)(dat.data);
			sum_code += code[i];
		}
		i++;
    }
    lh001_91_adc_stop();
	lh001_91_rdatac_stop();
	
	avg_code = (sum_code>>4);
    target_code = (uint64_t)(((1<<24)-1)*(AVDD_REG_MV/(2500*2.0)) );
    G = (uint32_t)( (target_code<<23)/avg_code);
    
    trim_write_gain(G);
	
#endif


}




