/*
Author: LH Software Group
Copyright
*/

#ifndef __LH001_55_H
#define __LH001_55_H

#include "stdint.h"
/*!
    spi_def header file
*/
#include "spi_def.h"

/*
    0 - Send SPI command to trigger ADC conversion
    1 - Set START pin to high to trigger ADC conversion
*/
#define ADC_CONV_START_HW 0


#define REG_VALUE_TBD  0x00
#define MANUAL_TRIM_ENABLE 0

#define ADC_REF_MV  2500
//#define ADC_REF_MV  2000

/*********************************************************
    Register Definition
*********************************************************/
/*MISC registers*/
#define ADDR_LH001_55_SYSCLK                0x14
#define ADDR_LH001_55_MODCLK                0x15
#define ADDR_LH001_55_CLKCON                0x16
#define ADDR_LH001_55_SPICTRL               0x17
#define ADDR_LH001_55_INTOEN                0x18
#define ADDR_LH001_55_FIFOSTA               0x19
#define ADDR_LH001_55_USERKEY               0x1E
//#define ADDR_LH001_55_CHIPID                0x00
#define ADDR_LH001_55_CHIPID                0x40
#define ADDR_LH001_55_OUTCLK                0x1C
/*ADC registers*/
#define ADDR_LH001_55_CONFIG1               0x01
#define ADDR_LH001_55_ADCCHOP               0x4B
#define ADDR_LH001_55_ADCCTRL               0x0C
#define ADDR_LH001_55_ADCCHCON              0x0B
#define ADDR_LH001_55_BUFCON                0x0A
#define ADDR_LH001_55_RWAB                  0x10
#define ADDR_LH001_55_GAIN                  0x11
#define ADDR_LH001_55_OFFSET                0x12

/*PGA registers*/
#define ADDR_LH001_55_PGAGAIN               0x0D
#define ADDR_LH001_55_PGACTRL               0x0E
#define ADDR_LH001_55_PGACTRL1              0x0F
/*GPIO Registers*/
#define ADDR_LH001_55_GPIO0                 0x1F
#define ADDR_LH001_55_GPIO1                 0x20
/*KEYS*/
#define ADDR_LH001_55_KEY0                  0x70
#define ADDR_LH001_55_KEY1                  0x71

/*DAC TIA*/
#define ADDR_LH001_55_DACCON                0x22
#define ADDR_LH001_55_TIACON                0x21   
#define ADDR_LH001_55_DACMUX                0x23
#define ADDR_LH001_55_DACRATE               0x28
#define ADDR_LH001_55_DACCODE0              0x29
#define ADDR_LH001_55_DACCODE1              0x2A
/*current source*/
#define ADDR_LH001_55_IEXECON               0x08
#define ADDR_LH001_55_IEXEMAG               0x09

#define ADDR_LH001_55_PLTFMPD                 0x55
    

/*********************************************************
    Register bit mask and bit position definition
*********************************************************/
/*MISC*/
#define MSK_LH001_55_SYSCLK_CD              0xFF
#define MSK_LH001_55_MODCLK_CD              0xFF
#define POS_LH001_55_MODCLK_CD              0x00
#define POS_LH001_55_MODCFG_ACIMPEN          2
#define MSK_LH001_55_MODCFG_ACIMPEN          (1<<POS_LH001_55_MODCFG_ACIMPEN)
#define MSK_LH001_55_CLKCON_CLKEN           0x01
#define POS_LH001_55_CLKCON_CLKEN           0
#define MSK_LH001_55_CLKCON_F2M             0x02
#define POS_LH001_55_CLKCON_F2M             1
#define MSK_LH001_55_CLKCON_PU              0x04
#define POS_LH001_55_CLKCON_PU              2
#define MSK_LH001_55_SPICTRL_DAISYIN        0x01
#define POS_LH001_55_SPICTRL_DAISYIN        0
#define MSK_LH001_55_SPICTRL_FIFOEN         0x02
#define POS_LH001_55_SPICTRL_FIFOEN         1
#define MSK_LH001_55_SPICTRL_DCMODE         0x04
#define POS_LH001_55_SPICTRL_DCMODE         2
#define MSK_LH001_55_INTOEN_INTEN           0x0F
#define POS_LH001_55_INTOEN_INTEN           0
#define MSK_LH001_55_INTOEN_INTBEN          (0x0F<<4)
#define POS_LH001_55_INTOEN_INTBEN          (4)
#define MSK_LH001_55_INTOEN_DRDY            (0x01<<0)
#define MSK_LH001_55_INTOEN_ENOUGH          (0x01<<1)
#define MSK_LH001_55_INTOEN_FULL            (0x01<<2)
#define MSK_LH001_55_INTOEN_OVERFLOW        (0x01<<3)
#define MSK_LH001_55_FIFOSTA_ENOUGHCNT      (0x1F<<0)
#define POS_LH001_55_FIFOSTA_ENOUGHCNT      (0)
#define MSK_LH001_55_FIFOSTA_ENOUGHTINT     (0x01<<5)
#define MSK_LH001_55_FIFOSTA_FULL           (0x01<<6)
#define MSK_LH001_55_FIFOSTA_OVERFLOW       (0x01<<7)
#define POS_LH001_55_OUTCLK_SEL             (0x00)
#define MSK_LH001_55_OUTCLK_SEL             (0x07<<POS_LH001_55_OUTCLK_SEL)
#define POS_LH001_55_OUTCLK_PIN             (0x3)
#define MSK_LH001_55_OUTCLK_PIN             (0x3<<POS_LH001_55_OUTCLK_PIN)

/*ADC*/
#define MSK_LH001_55_ADCCTRL_ADCEN          (0x01<<0)
#define POS_LH001_55_ADCCTRL_ADCEN          (0)
#define MSK_LH001_55_ADCCTRL_AMPEN          (0x01<<1)
#define POS_LH001_55_ADCCTRL_AMPEN          (1)
#define MSK_LH001_55_CONFIG1_DR             (0x07<<0)
#define MSK_LH001_55_CONFIG1_SGLESHOT       (0x01<<3)
#define MSK_LH001_55_CONFIG1_AVG            (0x0F<<4)
#define POS_LH001_55_CONFIG1_DR             (0)
#define POS_LH001_55_CONFIG1_SGLESHOT       (3)
#define POS_LH001_55_CONFIG1_AVG            (4)
#define POS_LH001_55_BUFCON_TEMPEN          (1)
#define MSK_LH001_55_BUFCON_TEMPEN          (1<<POS_LH001_55_BUFCON_TEMPEN)
#define POS_LH001_55_BUFCON_AVDD_DIV2       (2)
#define MSK_LH001_55_BUFCON_AVDD_DIV2       (1<<POS_LH001_55_BUFCON_AVDD_DIV2)
#define POS_LH001_55_BUFCON_ENREF           (4)
#define MSK_LH001_55_BUFCON_ENREF           (1<<POS_LH001_55_BUFCON_ENREF)
#define POS_LH001_55_BUFCON_EN2P5           (5)
#define MSK_LH001_55_BUFCON_EN2P5           (0x01<<POS_LH001_55_BUFCON_EN2P5)
#define POS_LH001_55_ADCCHCON_PSEL          (0)
#define POS_LH001_55_ADCCHCON_NSEL          (4)
/*PGA*/
#define MSK_LH001_55_PGACTRL_PD             (1<<0)
#define POS_LH001_55_PGACTRL_PD             (1<<0)
#define MSK_LH001_55_PGACTRL_BYPASS         (1<<1)
#define POS_LH001_55_PGACTRL_BYPASS         (1<<1)
#define MSK_LH001_55_PGACTRL_RESET          (1<<2)
#define POS_LH001_55_PGACTRL_RESET          (1<<2)
#define MSK_LH001_55_PGACTRL_LP             (1<<3)
#define POS_LH001_55_PGACTRL_LP             (3)
#define MSK_LH001_55_PGACTRL_AC             (1<<4)
#define MSK_LH001_55_PGACTRL1_CMSNS         (1<<2)
#define POS_LH001_55_PGACTRL1_CMSNS         (2)
#define POS_LH001_55_PGACTRL1_CHOP          (0)
#define MSK_LH001_55_PGACTRL1_CHOP          (3<<POS_LH001_55_PGACTRL1_CHOP)
#define POS_LH001_55_PGACTRL1_ACMUX         (5)
#define MSK_LH001_55_PGACTRL1_ACMUX         (7<<POS_LH001_55_PGACTRL1_ACMUX)
#define POS_LH001_55_PGAGAIN                0
#define MSK_LH001_55_PGAGAIN                0x3F
#define POS_LH001_55_PGACTRL_ACEN           (4)
#define MSK_LH001_55_PGACTRL_ACEN           (1<<POS_LH001_55_PGACTRL_ACEN)
#define POS_LH001_55_PGACTRL_ACGAIN         (5)
#define MSK_LH001_55_PGACTRL_ACGAIN         (7<<POS_LH001_55_PGACTRL_ACGAIN)
/*ECG*/
#define POS_LH001_55_LOCON1_THRESHOLD       (0)
#define MSK_LH001_55_LOCON1_THRESHOLD       (0x0F)
#define POS_LH001_55_LOCON1_CURRENT         (4)
#define MSK_LH001_55_LOCON1_CURRENT         (0x07<<POS_LH001_55_LOCON1_CURRENT)
#define POS_LH001_55_LOCON2_ACLOEN          (0)
#define MSK_LH001_55_LOCON2_ACLOEN          (1<<POS_LH001_55_LOCON2_ACLOEN)
#define POS_LH001_55_LOCON2_SINKEN          (1)
#define MSK_LH001_55_LOCON2_SINKEN          (3<<POS_LH001_55_LOCON2_SINKEN)
#define POS_LH001_55_LOCON2_SOURCEENB       (3)
#define MSK_LH001_55_LOCON2_SOURCEENB       (3<<POS_LH001_55_LOCON2_SOURCEENB)
#define POS_LH001_55_LOCON2_RLDLOEN         (5)
#define MSK_LH001_55_LOCON2_RLDLOEN         (1<<POS_LH001_55_LOCON2_RLDLOEN)
#define POS_LH001_55_LOCON3_DCLOEN          (0)
#define MSK_LH001_55_LOCON3_DCLOEN          (7<<POS_LH001_55_LOCON3_DCLOEN)
#define POS_LH001_55_LOCON3_TESTFREQ        (4)
#define MSK_LH001_55_LOCON3_TESTFREQ        (0xF<<POS_LH001_55_LOCON3_TESTFREQ)
#define POS_LH001_55_LOCON3_DCLOEN0         (0)
#define POS_LH001_55_LOCON3_DCLOEN1         (1)
#define POS_LH001_55_LOCON3_DCLOEN2         (2)
#define POS_LH001_55_RLDCON_CHOPFREQ        (0)
#define MSK_LH001_55_RLDCON_CHOPFREQ        (3<<POS_LH001_55_RLDCON_CHOPFREQ)
#define POS_LH001_55_RLDCON_EN              (2)
#define MSK_LH001_55_RLDCON_EN              (1<<POS_LH001_55_RLDCON_EN)
#define POS_LH001_55_RLDCON_RLDREFSEL       (3)
#define MSK_LH001_55_RLDCON_RLDREFSEL       (1<<POS_LH001_55_RLDCON_RLDREFSEL)
/*PLATFORM*/
#define POS_LH001_55_PLTFMPD_PDALL          (7)
#define MSK_LH001_55_PLTFMPD_PDALL          (1<<POS_LH001_55_PLTFMPD_PDALL)
/*CURRENT SOURCE*/
#define POS_LH001_55_IEXECON_EN             (0)
#define MSK_LH001_55_IEXECON_EN             (1<<POS_LH001_55_IEXECON_EN)
#define POS_LH001_55_IEXECON_AIN4           (1)
#define MSK_LH001_55_IEXECON_AIN4           (1<<POS_LH001_55_IEXECON_AIN4)
#define POS_LH001_55_IEXECON_AIN5           (2)
#define MSK_LH001_55_IEXECON_AIN5           (1<<POS_LH001_55_IEXECON_AIN5)
#define POS_LH001_55_IEXECON_EN100N         (3)
#define MSK_LH001_55_IEXECON_EN100N         (1<<POS_LH001_55_IEXECON_EN100N)
#define POS_LH001_55_IEXEMAG_AIN4           (0)
#define MSK_LH001_55_IEXEMAG_AIN4           (3<<POS_LH001_55_IEXEMAG_AIN4)
#define POS_LH001_55_IEXEMAG_AIN5           (3)
#define MSK_LH001_55_IEXEMAG_AIN5           (3<<POS_LH001_55_IEXEMAG_AIN5)

/*DAC*/
#define POS_LH001_55_DACCFG_WAVETYPE          0x0
#define MSK_LH001_55_DACCFG_WAVETYPE          (3<<POS_LH001_55_DACCFG_WAVETYPE)
#define POS_LH001_55_DACCFG_DACGAINEN         0x6
#define MSK_LH001_55_DACCFG_DACGAINEN         (1<<POS_LH001_55_DACCFG_DACGAINEN)
#define POS_LH001_55_DACCFG_DACOFFSETEN       0x7
#define MSK_LH001_55_DACCFG_DACOFFSETEN         (1<<POS_LH001_55_DACCFG_DACOFFSETEN)
#define POS_LH001_55_ACMUXSEL_ACPGASEL        0x0
#define MSK_LH001_55_ACMUXSEL_ACPGASEL        (0xF<<POS_LH001_55_ACMUXSEL_ACPGASEL)
#define POS_LH001_55_ACMUXSEL_TIAVDACSEL      0x5
#define MSK_LH001_55_ACMUXSEL_TIAVDACSEL      (7<<POS_LH001_55_ACMUXSEL_TIAVDACSEL)
#define POS_LH001_55_TIACON_TIAEN             0x0
#define MSK_LH001_55_TIACON_TIAEN             (1<<POS_LH001_55_TIACON_TIAEN)
#define POS_LH001_55_TIACON_GAIN              0x4
#define MSK_LH001_55_TIACON_GAIN              (0xF<<POS_LH001_55_TIACON_GAIN)


typedef enum{
    CURRENT_SOURCE_MAG_100nA = 0,
    CURRENT_SOURCE_MAG_50uA,
    CURRENT_SOURCE_MAG_100uA,
    CURRENT_SOURCE_MAG_250uA,
    CURRENT_SOURCE_MAG_500uA,
    CURRENT_SOURCE_MAG_750uA,
    CURRENT_SOURCE_MAG_1mA,
}CURRENT_SRC_MAG_t;

/*********************************************************
    enum  definition
*********************************************************/
/*ADC*/
#define ENUM_LH001_55_ADC_SINGLE             0x01
#define ENUM_LH001_55_ADC_CONTINOUS          0x00
#define ENUM_LH001_55_ADC_REF_2V             0x00
#define ENUM_LH001_55_ADC_REF_2V5            0x01
#define ENUM_LH001_55_ADCCHP_AIN0            0X00
#define ENUM_LH001_55_ADCCHP_AIN1            0X01
#define ENUM_LH001_55_ADCCHP_AIN2            0X02
#define ENUM_LH001_55_ADCCHP_AIN3            0X03
#define ENUM_LH001_55_ADCCHP_AIN4            0X04
#define ENUM_LH001_55_ADCCHP_AIN5            0X05
#define ENUM_LH001_55_ADCCHP_AIN6            0X06
#define ENUM_LH001_55_ADCCHP_AIN7            0X07
#define ENUM_LH001_55_ADCCHP_RLDIN           0X08
#define ENUM_LH001_55_ADCCHP_DVDD            0X09
#define ENUM_LH001_55_ADCCHP_AVDD            0X0A
#define ENUM_LH001_55_ADCCHP_VCM             0X0B
#define ENUM_LH001_55_ADCCHP_TEMP            0X0C
#define ENUM_LH001_55_ADCCHP_TEST            0X0D
#define ENUM_LH001_55_ADCCHN_AIN0            0X00
#define ENUM_LH001_55_ADCCHN_AIN1            0X01
#define ENUM_LH001_55_ADCCHN_AIN2            0X02
#define ENUM_LH001_55_ADCCHN_AIN3            0X03
#define ENUM_LH001_55_ADCCHN_AIN4            0X04
#define ENUM_LH001_55_ADCCHN_AIN5            0X05
#define ENUM_LH001_55_ADCCHN_AIN6            0X06
#define ENUM_LH001_55_ADCCHN_AIN7            0X07
#define ENUM_LH001_55_ADCCHN_RLDIN           0X08
#define ENUM_LH001_55_ADCCHN_GND             0X0F
/*PGA*/
#define ENUM_LH001_55_PGA_PGAGAIN_1          0x00
#define ENUM_LH001_55_PGA_PGAGAIN_2          0x01
#define ENUM_LH001_55_PGA_PGAGAIN_3          0x02
#define ENUM_LH001_55_PGA_PGAGAIN_4          0x03
#define ENUM_LH001_55_PGA_PGAGAIN_6          0x04
#define ENUM_LH001_55_PGA_PGAGAIN_8          0x05
#define ENUM_LH001_55_PGA_PGAGAIN_12         0x06
#define ENUM_LH001_55_PGA_PGAGAIN_24         0x07
#define ENUM_LH001_55_PGA_PGAGAIN_48         0x08
#define ENUM_LH001_55_PGA_POWER_LP           0x01
#define ENUM_LH001_55_PGA_POWER_HP           0x00
#define ENUM_LH001_55_PGA_CHOP_DIV64         0
#define ENUM_LH001_55_PGA_CHOP_DIV32         1
#define ENUM_LH001_55_PGA_CHOP_DIV16         2
#define ENUM_LH001_55_PGA_CHOP_DIV8          3
/*MISC*/
#define ENUM_LH001_55_CLKCON_OSCINT         0x00
#define ENUM_LH001_55_CLKCON_OSCOUT         0x01
#define ENUM_LH001_55_CLKCON_OSC2M          0x00
#define ENUM_LH001_55_CLKCON_OSC16M         0x01
#define ENUM_LH001_55_CLKCON_PULLUP         (0<<2)
#define ENUM_LH001_55_CLKCON_NOPULL         (1<<2)
#define LH001_55_USERKEY                    0x86
#define LH001_55_USERKEY_F2M                0x58
#define ENUM_LH001_55_OUTCLK_0              0x00
#define ENUM_LH001_55_OUTCLK_OSC            0x01
#define ENUM_LH001_55_OUTCLK_SYSCLK         0x02
#define ENUM_LH001_55_OUTCLK_MODCLK         0x03
#define ENUM_LH001_55_OUTCLK_LEADOFF        0x04
#define ENUM_LH001_55_OUTCLK_CHOP           0x05
#define ENUM_LH001_55_OUTCLK_DRDY           0x01
#define ENUM_LH001_55_OUTCLK_INTB           0x02


/*ECG*/
#define ENUM_LH001_55_TEST_FREQUENCY_DC    0
#define ENUM_LH001_55_TEST_FREQUENCY_0P5HZ 1
#define ENUM_LH001_55_TEST_FREQUENCY_1HZ   2
#define ENUM_LH001_55_TEST_FREQUENCY_2HZ   3
#define ENUM_LH001_55_RLD_CHOP_CLOSE       0
#define ENUM_LH001_55_RLD_CHOP_FMOD_DIV32  1
#define ENUM_LH001_55_RLD_CHOP_FMOD_DIV64  2
#define ENUM_LH001_55_RLD_CHOP_FMOD_DIV128 3
#define ENUM_LH001_55_RLD_REF_AVDD_DIV2    0
#define ENUM_LH001_55_RLD_REF_EXT          1




/*********************************************************
 *SPI command
 *********************************************************/
#define SPI_CMD_RESET                0x06   //reset device
#define SPI_CMD_CONV_START           0x08   //start conversion
#define SPI_CMD_CONV_STOP            0x0A   //stop conversion
#define SPI_CMD_RST_FIFO             0x0C   //reset data fifo
#define SPI_CMD_RDATAC               0x10   //start continous read
#define SPI_CMD_SDATAC               0x11   //stop continouse read
#define SPI_CMD_RDATA                0x12   //read data command
#define SPI_CMD_RREG_MSK             0x20   //read register from specified address, followed by register number to be read
#define SPI_CMD_WREG_MSK             0x40   //write register to specified address, followed by register number to be write
#define SPI_CMD_RREG_BK1_MSK         0xA0   //read register from specified address +32,followed by register number to be read
#define SPI_CMD_WREG_BK1_MSK         0xC0   //write register to specified address +32,followed by register number to be write

/*********************************************************
    Register reset value definition 
*********************************************************/
#define RST_VAL_LH001_55_GPIO0         0x00
#define RST_VAL_LH001_55_LOCON1        0x0F
#define RST_VAL_LH001_55_LOCON2        0x18
#define RST_VAL_LH001_55_BUFCON        0x11
#define RST_VAL_LH001_55_ADCCHCON      0x10
#define RST_VAL_LH001_55_CHIPID        0x01
#define RST_VAL_LH001_55_CONFIG1       0x06
#define RST_VAL_LH001_55_PGACTRL       0x0D
#define RST_VAL_LH001_55_SYSCLK        0x08
#define RST_VAL_LH001_55_CLKCON        0x06
#define RST_VAL_LH001_55_INTOEN        0x21
#define RST_VAL_LH001_55_FIFOSTA       0x0F

/*********************************************************
 Init structure
*********************************************************/
#define ENUM_LH001_55_ADC_FMODCLK_512K 4       //2048KHz/4
#define ENUM_LH001_55_ADC_FMODCLK_128K 16       //2048KHz/16
#define ENUM_LH001_55_ADC_FMODCLK_32K  64       //2048KHz/32
#define ENUM_LH001_55_ADC_FMODCLK_16K 128       //2048KHz/128

#define ENUM_LH001_55_ADC_FMODCLK_IMP1M   16       //16MHz/16
#define ENUM_LH001_55_ADC_FMODCLK_IMP512K 32       //16MHz/32
#define ENUM_LH001_55_ADC_FMODCLK_IMP128K 128       //16MHz/128

/*! DR definition for MODCFG.MD=1*/
#define ENUM_LH001_55_ADC_DR_DIV1024   0
#define ENUM_LH001_55_ADC_DR_DIV512   1
#define ENUM_LH001_55_ADC_DR_DIV256   2
#define ENUM_LH001_55_ADC_DR_DIV128   3
#define ENUM_LH001_55_ADC_DR_DIV64    4
#define ENUM_LH001_55_ADC_DR_DIV32    5
#define ENUM_LH001_55_ADC_DR_DIV16    6
#define ENUM_LH001_55_ADC_AVG_30K     0
#define ENUM_LH001_55_ADC_AVG_15K     1
#define ENUM_LH001_55_ADC_AVG_7K5     2
#define ENUM_LH001_55_ADC_AVG_3K75    3
#define ENUM_LH001_55_ADC_AVG_2K      4
#define ENUM_LH001_55_ADC_AVG_1K      5
#define ENUM_LH001_55_ADC_AVG_500     6
#define ENUM_LH001_55_ADC_AVG_100     7
#define ENUM_LH001_55_ADC_AVG_60      8
#define ENUM_LH001_55_ADC_AVG_50      9
#define ENUM_LH001_55_ADC_AVG_30      10
#define ENUM_LH001_55_ADC_AVG_25      11
#define ENUM_LH001_55_ADC_AVG_15      12
#define ENUM_LH001_55_ADC_AVG_10      13
#define ENUM_LH001_55_ADC_AVG_5       14
#define ENUM_LH001_55_ADC_AVG_2P5     15
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
	//ENUM_LH001_55_PGA_CHOP_DIV64
	//ENUM_LH001_55_PGA_CHOP_DIV32
	//ENUM_LH001_55_PGA_CHOP_DIV16
	//ENUM_LH001_55_PGA_CHOP_DIV8 
	uint32_t pga_chop;
    ///ENUM_LH001_55_PGA_POWER_LP, low power mode
    ///ENUM_LH001_55_PGA_POWER_HP, high power mode
    uint32_t power_mode;
    /// common mode voltage sense function, used for RLD
    ///0, disable
    ///1, enable
    uint32_t comm_sense_en;
}LH001_55_PGA_INIT_t;



typedef enum{
    LH001_55_CLKSRC_EXT = 0,  ///use external clock from clk pin
    LH001_55_CLKSRC_INT,      ///use internal 2.048M osc, clken=0
    ///use internal 2.048MHz OSC and output this clock to clk pin
    ///this feature depends on CLKSEL pin setting,
    /// clksel pad    |  clken     | clock source   | CLK pad
    ///-----------------------------------------------------------
    ///      0        |     x      |  external clock| input clock
    ///      1        |     0      |  internal osc  | three-state
    ///      1        |     1      |  internal osc  | output clock
    LH001_55_CLKSRC_INT_OUTPUT,       ///clken=1
}LH001_55_CLOCK_SOURCE_t;


typedef struct {
    uint8_t addr;
    uint8_t val;
    uint8_t reg_name[48];
}REG_DUMP_t;

typedef struct{
    uint64_t reserved0: 48;
    uint64_t start:4;
    uint64_t loffstat:5;
    uint64_t gpio:2;
    uint64_t reserved1:13;
    uint64_t data:24;
}ADC_DATA_NOFIFO_t;

typedef struct{
    uint64_t reserved0: 48;
    uint64_t start:4;
    uint64_t loffstat:5;
    uint64_t gpio:2;
    uint64_t reserved1:11;
    uint64_t data:24;
    uint64_t tail:2;
}ADC_DATA_FIFO_t;


typedef enum{
    RTIA_0=0,
    RTIA_500,
    RTIA_1K,
    RTIA_2K,
    RTIA_5K,
    RTIA_10K,
    RTIA_20K,
    RTIA_40K,
    RTIA_80K,
    RTIA_160K,
    RTIA_EXT,
}RTIA_Type;


#ifndef LH_ENABLE    
#define     LH_ENABLE   1
#endif 
#ifndef LH_DISABLE
#define LH_DISABLE      0
#endif

#define LH_FIFO_ENABLE       1
#define LH_FIFO_DISABLE      0

/*****************************************************************************************
                                API 
*****************************************************************************************/
void LH001_55_adc_go(void);
void LH001_55_adc_stop(void);
void LH001_55_sw_reset(void);
void LH001_55_reset_fifo(void);
void LH001_55_rdatac_start(void);
void LH001_55_rdatac_stop(void);

void LH001_55_hw_reset(void);
void LH001_55_write_regs(uint8_t addr, uint8_t *pRegs,uint8_t num);
void LH001_55_read_regs(uint8_t addr, uint8_t *pRegs,uint8_t num);
void LH001_55_read_data(uint8_t *pData,uint8_t num);
void LH001_55_read_data_nofifo(ADC_DATA_NOFIFO_t *pData);
void LH001_55_read_data_fifo(ADC_DATA_FIFO_t *pData);
void LH001_55_standby(void);
void LH001_55_wakeup(void);

void LH001_55_adc_init(LH001_55_ADC_INIT_t *pInit);
void LH001_55_adc_channel(uint32_t chP, uint32_t chN);
void LH001_55_pga_init(LH001_55_PGA_INIT_t *pInit);

void LH001_55_test_signal(uint32_t freq);
void LH001_55_spi_daisy_mode(uint32_t enable);
void LH001_55_clock_source(LH001_55_CLOCK_SOURCE_t clksrc);
void LH001_55_userkey_unlock(void);
float LH001_55_adc_code2mv(uint32_t code,uint32_t ref);

void LH001_55_Isource_cfg(uint32_t enable,CURRENT_SRC_MAG_t Isrc,uint32_t channel);

void LH001_55_reg_dump(REG_DUMP_t *pRegs,uint8_t num);
void LH001_55_post_setup(void);
void LH001_55_output_clk(uint32_t clkSrc,uint32_t pin);

uint32_t LH001_55_dac_mv2code(uint32_t mv);
void LH001_55_dac_enable(void);
void LH001_55_dac_disable(void);
void LH001_55_dac_code(uint16_t code);

void LH001_55_tia_config(uint32_t enable, RTIA_Type rtia);



#endif  //#ifndef __LH001_55_H

