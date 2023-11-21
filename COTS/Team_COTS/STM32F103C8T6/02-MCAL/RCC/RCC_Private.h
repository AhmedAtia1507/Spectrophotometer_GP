/**
 * @file RCC_Private.h
 * @author Ahmed Atia Said (atiaa6501@gmail.com)
 * @brief: C header file to:
 *          1) Define Memory Mapping of Reset & Clock Controller Registers
 *          2) Define macros used as choices for pre-build configurations of RCC Peripheral
 * @version 1.0
 * @date 2023-08-30
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef _RCC_PRIVATE_H_
#define _RCC_PRIVATE_H_

#define RCC_REGISTERS_BASE_ADDRESS                      0x40021000

/*************************************RCC Registers' Memory Mapping*************************************/

/*Clock control register*/
#define RCC_CR                                          (*(volatile uint32*)(RCC_REGISTERS_BASE_ADDRESS + 0x00))
/*Clock configuration register*/
#define RCC_CFGR                                        (*(volatile uint32*)(RCC_REGISTERS_BASE_ADDRESS + 0x04))
/*Clock interrupt register*/
#define RCC_CIR                                         (*(volatile uint32*)(RCC_REGISTERS_BASE_ADDRESS + 0x08))
/*APB2 peripheral reset register*/
#define MRCC_APB2RSTR                                    (*(volatile uint32*)(RCC_REGISTERS_BASE_ADDRESS + 0x0C))
/*APB1 peripheral reset register*/
#define MRCC_APB1RSTR                                    (*(volatile uint32*)(RCC_REGISTERS_BASE_ADDRESS + 0x10))
/*AHB peripheral clock enable register*/
#define MRCC_AHBENR                                      (*(volatile uint32*)(RCC_REGISTERS_BASE_ADDRESS + 0x14))
/*APB2 peripheral clock enable register*/
#define MRCC_APB2ENR                                     (*(volatile uint32*)(RCC_REGISTERS_BASE_ADDRESS + 0x18))
/*APB1 peripheral clock enable register*/
#define MRCC_APB1ENR                                     (*(volatile uint32*)(RCC_REGISTERS_BASE_ADDRESS + 0x1C))
/*Backup domain control register*/
#define RCC_BDCR                                        (*(volatile uint32*)(RCC_REGISTERS_BASE_ADDRESS + 0x20))
/*Control/status register*/
#define RCC_CSR                                         (*(volatile uint32*)(RCC_REGISTERS_BASE_ADDRESS + 0x24))

/****************************Clock control register bits*************************/

/*Internal high-speed clock enable*/
#define RCC_CR_HSION                                    0
/*Internal high-speed clock ready flag*/
#define RCC_CR_HSIRDY                                   1
/*Internal high-speed clock trimming "4 Bits"*/
#define RCC_CR_HSITRIM_START                            3
/*Internal high-speed clock enable "8 Bits"*/
#define RCC_CR_HSICAL_START                             8
/*External high-speed clock enable*/
#define RCC_CR_HSEON                                    16
/*External high-speed clock ready flag*/
#define RCC_CR_HSERDY                                   17
/*External high-speed clock bypass*/
#define RCC_CR_HSEBYP                                   18
/*Clock security system enable*/
#define RCC_CR_CSSON                                    19
/*Phase locked loop clock enable*/
#define RCC_CR_PLLON                                    24
/*Phase locked loop clock ready flag*/
#define RCC_CR_PLLRDY                                   25

/****************************Clock configuration register bits*************************/

/*System Clock Switch "2 Bits"*/
#define RCC_CFGR_SW_START                               0
/*System clock switch status "2 bits"*/
#define RCC_CFGR_SWS_START                              2
/*AHB prescaler "4 bits"*/
#define RCC_CFGR_HPRE_START                             4
/*APB low-speed prescaler (APB1) "3 bits"*/
#define RCC_CFGR_PPRE1_START                            8
/*APB high-speed prescaler (APB2) "3 bits"*/
#define RCC_CFGR_PPRE2_START                            11
/*ADC prescaler "2 bits"*/
#define RCC_CFGR_ADCPRE_START                           14
/*PLL entry clock source*/
#define RCC_CFGR_PLLSRC                                 16
/*HSE divider for PLL entry*/
#define RCC_CFGR_PLLXTPRE                               17
/*PLL multiplication factor "3 bits"*/
#define RCC_CFGR_PLLMUL_START                           18
/*USB prescaler*/
#define RCC_CFGR_USBPRE                                 22
/*Microcontroller clock output "3 bits"*/
#define RCC_CFGR_MCO_START                              24

/****************************Macros for Configurations*************************/

/*Clock Sources*/
#define MRCC_HSE_CLOCK                                   1
#define MRCC_HSI_CLOCK                                   2
#define MRCC_PLL_CLOCK                                   3

/*Options for High-Speed External Clock*/
#define MRCC_HSE_CRYSTAL_CLOCK                           1
#define MRCC_HSE_RC_CLOCK                                2

/*Options for PLL Input*/
#define MRCC_HSE_CLOCK                                   1
#define MRCC_HSE_CLOCK_DIV_2                             2
#define MRCC_HSI_CLOCK_DIV_2                             3

/*Options for AHB Prescalar*/
#define MRCC_AHB_CLK_DIV_1                               0b0000
#define MRCC_AHB_CLK_DIV_2                               0b1000
#define MRCC_AHB_CLK_DIV_4                               0b1001
#define MRCC_AHB_CLK_DIV_8                               0b1010
#define MRCC_AHB_CLK_DIV_16                              0b1011
#define MRCC_AHB_CLK_DIV_64                              0b1100
#define MRCC_AHB_CLK_DIV_128                             0b1101
#define MRCC_AHB_CLK_DIV_256                             0b1110
#define MRCC_AHB_CLK_DIV_512                             0b1111

/*Options for APB1 Prescalar*/
#define MRCC_APB1_CLK_DIV_1                              0b000
#define MRCC_APB1_CLK_DIV_2                              0b100
#define MRCC_APB1_CLK_DIV_4                              0b101
#define MRCC_APB1_CLK_DIV_8                              0b110
#define MRCC_APB1_CLK_DIV_16                             0b111

/*Options for APB2 Prescalar*/
#define MRCC_APB2_CLK_DIV_1                              0b000
#define MRCC_APB2_CLK_DIV_2                              0b100
#define MRCC_APB2_CLK_DIV_4                              0b101
#define MRCC_APB2_CLK_DIV_8                              0b110
#define MRCC_APB2_CLK_DIV_16                             0b111
#endif /*_RCC_PRIVATE_H_*/