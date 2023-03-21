/*

Version:
Author: LH Software Group
Copyright
*/

#include "LH001_55.h"
#include <stdio.h>
#include "uart_print.h"

uint32_t adc_data;
uint32_t data_cnt;
uint32_t data_ready_flag;
uint32_t pga_gain;


void delay(uint32_t t)
{
	
    for(uint32_t i=0;i<t;i++);
}



void LH001_55_init()
{
    LH001_55_ADC_INIT_t adc_init;
    LH001_55_PGA_INIT_t pga_init;
    uint8_t val;
  
    LH001_55_Spi_Init();
		LH001_55_sw_reset();
	  for(uint32_t i=0;i<80000;i++);
	  
		LH001_55_adc_stop();
    LH001_55_rdatac_stop();


		//pga_init.gain = ENUM_LH001_55_PGA_PGAGAIN_48;
	  //pga_gain = 48;
		pga_init.gain = ENUM_LH001_55_PGA_PGAGAIN_1;
	  pga_gain = 1;
    pga_init.pga_bypass = 0;
    pga_init.power_mode = ENUM_LH001_55_PGA_POWER_HP;
		pga_init.pga_chop = ENUM_LH001_55_PGA_CHOP_DIV32;
    LH001_55_pga_init(&pga_init);

    adc_init.Fmodclk = ENUM_LH001_55_ADC_FMODCLK_512K;
    adc_init.conv_mode = ENUM_LH001_55_ADC_CONTINOUS;
    adc_init.ref_sel = ENUM_LH001_55_ADC_REF_2V5;
    LH001_55_adc_init(&adc_init);
	
		//setup for sample, remove for ATE tested product
    LH001_55_post_setup();
    LH001_55_read_regs(0x64,&val,1);
    val &= ~(0x3);  
    LH001_55_write_regs(0x64,&val,1);
    val = ENUM_LH001_55_ADC_AVG_10<<POS_LH001_55_CONFIG1_AVG;  //30 sps data rate
    LH001_55_write_regs(ADDR_LH001_55_CONFIG1,&val,1);
		
		LH001_55_adc_channel(ENUM_LH001_55_ADCCHP_AIN2,ENUM_LH001_55_ADCCHN_AIN3);		//ADC Measure AIN2 VS AIN3 
		//LH001_55_adc_channel(ENUM_LH001_55_ADCCHP_TEST,ENUM_LH001_55_ADCCHN_GND);	//internal 2.5v DC test signal 
		//enable current source 1mA on AIN4
		LH001_55_Isource_cfg(1,CURRENT_SOURCE_MAG_1mA,MSK_LH001_55_IEXECON_AIN4);

		
}

/*check below registers for configuration*/
REG_DUMP_t reg[] =
{
	{ADDR_LH001_55_CHIPID,0,"ADDR_LH001_55_CHIPID"},
  {ADDR_LH001_55_TIACON,0,"ADDR_LH001_55_TIACON"},

};

int main()
{
	int dat;
  data_cnt = 0;
	data_ready_flag = 0;
	
	uart_print_init();
  debug_pin_init();
	printf("test start\n");
	
  LH001_55_init();
	LH001_55_tia_config(1,RTIA_1K);

#if  1 
    	/*dump register to check register configuration*/
    LH001_55_reg_dump(reg,sizeof(reg)/sizeof(REG_DUMP_t));
    for(uint32_t i=0;i<sizeof(reg)/sizeof(REG_DUMP_t);i++)
    {
      printf("%s:0x%x\r\n",reg[i].reg_name, reg[i].val);
    }
#endif
		
		printf("RawAdc,mV\r\n");
		LH001_55_adc_go();
    LH001_55_rdatac_start();
    while(1)
    {	
			if(data_ready_flag>0)
			{
				data_ready_flag = 0;
				if(adc_data & (1<<23))
					dat = (int)((0xFFu<<24)|(adc_data));
				else
					dat = (int)(adc_data);
				printf("%d,%d,%f mV\r\n",data_cnt,dat,dat*5000.0/((1<<24)-1)/pga_gain);
			}	 

    }
}


void EXTI4_15_IRQHandler()
{
  ADC_DATA_NOFIFO_t dat;
  if(exti_interrupt_flag_get(EXTI_10) != RESET)
  {
    /* Clear the EXTI line 0 pending bit */
    exti_interrupt_flag_clear(EXTI_10);
    //read ADC data
    LH001_55_read_data_nofifo(&dat);
    adc_data = dat.data;
    data_cnt++;
		data_ready_flag++;
  
  }
	
  
    
}
