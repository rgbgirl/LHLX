/*

Version:
Author: LH Software Group
Copyright
UART Config:
	Baudrate: 115200
	8 bit length, no parity check, 1 bit stop
*/

#include "LH001_91.h"
#include <stdio.h>
#include "uart_print.h"




#define ADC_DATA_LEN 7500
uint32_t data_cnt;

ADC_DATA_NOFIFO_t ecg_dat;
volatile uint32_t data_ready_flag;

void delay(uint32_t t)
{
    for(uint32_t i=0;i<t;i++);
}

void lh001_91_init()
{

    LH001_91_ADC_INIT_t adc_init;
    LH001_91_PGA_INIT_t pga_init;
    LH001_91_LEADOFF_t leadoff_init;

    LH001_91_Spi_Init();
    lh001_91_sw_reset();
	
	lh001_91_adc_stop();
    lh001_91_rdatac_stop();

    leadoff_init.threshold = LH001_91_LEADOFF_DELTA_10;
    leadoff_init.current = LH001_91_LEADOFF_CURRENT_SOURCE_5nA;
    leadoff_init.sink_cfg = LH001_91_LEADOFF_SINK_AIN0_1;
    leadoff_init.source_cfg = LH001_91_LEADOFF_SOURCE_CLOSE;
    leadoff_init.rld_sink_en = 1;
    leadoff_init.ain0_detect_en = 1;
    leadoff_init.ain1_detect_en = 1;
    leadoff_init.rld_detect_en = 1;
    lh001_91_leadoff_init(&leadoff_init);

    lh001_91_rld_init(1,ENUM_LH001_91_RLD_REF_AVDD_DIV2,ENUM_LH001_91_RLD_CHOP_FMOD_DIV32);

	pga_init.gain = ENUM_LH001_91_PGA_PGAGAIN_6;
    pga_init.pga_bypass = 0;
    pga_init.power_mode = ENUM_LH001_91_PGA_POWER_LP;
    pga_init.comm_sense_en = 1;
	pga_init.pga_chop = ENUM_LH001_91_PGA_CHOP_DIV16;
    lh001_91_pga_init(&pga_init);

	  adc_init.Fmodclk = ENUM_LH001_91_ADC_FMODCLK_128K;
    adc_init.oversample_rate = ENUM_LH001_91_ADC_DR_DIV512; //update rate = Fmodclk/oversample_rate
    adc_init.conv_mode = ENUM_LH001_91_ADC_CONTINOUS;
    adc_init.ref_sel = ENUM_LH001_91_ADC_REF_2V;
    lh001_91_adc_init(&adc_init);
    //lh001_91_adc_channel(ENUM_LH001_91_ADCCHP_VCM,ENUM_LH001_91_ADCCHN_GND);	//FOR NOISE TEST
	lh001_91_adc_channel(ENUM_LH001_91_ADCCHP_AIN0,ENUM_LH001_91_ADCCHN_AIN1);	
	
	
}

/*check below registers for configuration*/
REG_DUMP_t reg[] =
{
  {ADDR_LH001_91_PGAGAIN,0,"ADDR_LH001_91_PGAGAIN"},
  {ADDR_LH001_91_PGACTRL,0,"ADDR_LH001_91_PGACTRL"},
  {ADDR_LH001_91_PGACTRL1,0,"ADDR_LH001_91_PGACTRL1"},
  {ADDR_LH001_91_CONFIG1,0,"ADDR_LH001_91_CONFIG1"},
  {ADDR_LH001_91_ADCCTRL,0,"ADDR_LH001_91_ADCCTRL"},
  {ADDR_LH001_91_ADCCHCON,0,"ADDR_LH001_91_ADCCHCON"},
  {ADDR_LH001_91_BUFCON,0,"ADDR_LH001_91_BUFCON"},
	{ADDR_LH001_91_LOCON1,0,"ADDR_LH001_91_LOCON1"},
  {ADDR_LH001_91_LOCON2,0,"ADDR_LH001_91_LOCON2"},
  {ADDR_LH001_91_LOCON3,0,"ADDR_LH001_91_LOCON3"},
  {ADDR_LH001_91_RLDCON,0,"ADDR_LH001_91_RLDCON"},
};

int main()
{

    float volt_mv;
    data_cnt = 0;
    data_ready_flag = 0;

	  uart_print_init();
    debug_pin_init();
	
	   printf("test start\r\n");
	
    lh001_91_init();
	
#if  1
    	/*dump register to check register configuration*/
    lh001_91_reg_dump(reg,sizeof(reg)/sizeof(REG_DUMP_t));
    for(uint32_t i=0;i<sizeof(reg)/sizeof(REG_DUMP_t);i++)
    {
      printf("%s:0x%x\r\n",reg[i].reg_name, reg[i].val);
    }
#endif

	  lh001_91_adc_go();
    lh001_91_rdatac_start();
	

    while(1)
    {
      if(data_ready_flag != 0 )
      {
				data_ready_flag = 0;
        data_cnt++;

        volt_mv = lh001_91_adc_code2mv(ecg_dat.data,2000);
        printf("%d,%x,%f\r\n",data_cnt,ecg_dat.loffstat,volt_mv);
			}
    }
}

//ADC interrupt
void EXTI4_15_IRQHandler()
{
  if(exti_interrupt_flag_get(EXTI_10) != RESET)
  {
    /* Clear the EXTI line 0 pending bit */
    exti_interrupt_flag_clear(EXTI_10);
    
    //read ADC data
    lh001_91_read_data_nofifo(&ecg_dat);
    data_ready_flag = 1;
  }
    
}
