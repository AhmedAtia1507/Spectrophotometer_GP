/**
 * @file RCC_Interface.h
 * @author Ahmed Atia Said (atiaa6501@gmail.com)
 * @brief: C header file used to:
 *         1) Declare functions used to configure Reset & Clock Controller Peripheral.
 *         2) Define Macros used in multiple files 
 * @version 1.0
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef _RCC_INTERFACE_H_
#define _RCC_INTERFACE_H_

/*
    Reset & Clock Controller Peripheral is used to:
    1) Configure the micro controller's clock source
    2) Enable and Disable the clock entering the other peripherals except RCC Itself and 
        Core Peripherals
*/

#define MRCC_AHB                                     1
#define MRCC_APB1                                    2
#define MRCC_APB2                                    3

/******************************************AHB Peripherals*****************************************/

/*DMA1 clock enable*/
#define MRCC_AHBENR_DMA1EN                           0  
/*DMA2 clock enable*/                   
#define MRCC_AHBENR_DMA2EN                           1  
/*SRAM interface clock enable*/                 
#define MRCC_AHBENR_SRAMEN                           2  
/*FLITF clock enable*/                  
#define MRCC_AHBENR_FLITFEN                          4  
/*CRC clock enable*/                    
#define MRCC_AHBENR_CRCEN                            6
/*FSMC Clock Enable*/                   
#define MRCC_AHB_FSMC_EN                             8
/*SDIO Clock Enable*/                   
#define MRCC_AHB_SDIO_EN                             10

/******************************************APB1 Peripherals*****************************************/

/*Timer 2 clock enable*/
#define MRCC_APB1_TIM2_EN                            0
/*Timer 3 clock enable */                   
#define MRCC_APB1_TIM3_EN                            1
/*Timer 4 clock enable */                   
#define MRCC_APB1_TIM4_EN                            2
/*Timer 5 clock enable */                   
#define MRCC_APB1_TIM5_EN                            3
/*Timer 6 clock enable */                   
#define MRCC_APB1_TIM6_EN                            4
/*Timer 7 clock enable */                   
#define MRCC_APB1_TIM7_EN                            5
/*Timer 12 clock enable */                      
#define MRCC_APB1_TIM12_EN                           6
/*Timer 13 clock enable */                      
#define MRCC_APB1_TIM13_EN                           7
/*Timer 14 clock enable */                      
#define MRCC_APB1_TIM14_EN                           8
/*Window Watchdog clock enable*/                      
#define MRCC_APB1_WWDG_EN                            11
/*SPI2 clock enable*/                   
#define MRCC_APB1_SPI2_EN                            14
/*SPI3 clock enable*/                   
#define MRCC_APB1_SPI3_EN                            15
/*USART2 clock enable*/                     
#define MRCC_APB1_USART2_EN                          17
/*USART3 clock enable*/                     
#define MRCC_APB1_USART3_EN                          18
/*UART4 clock enable*/                  
#define MRCC_APB1_UART4_EN                           19
/*UART5 clock enable*/                  
#define MRCC_APB1_UART5_EN                           20
/*I2C1 clock enable*/                   
#define MRCC_APB1_I2C1_EN                            21
/*I2C2 clock enable*/                   
#define MRCC_APB1_I2C2_EN                            22
/*USB clock enable*/                    
#define MRCC_APB1_USB_EN                             23
/*CAN clock enable*/                    
#define MRCC_APB1_CAN_EN                             25
/*Backup interface clock enable*/ 
#define MRCC_APB1_BKP_EN                             27
/*Power interface clock enable*/                     
#define MRCC_APB1_PWR_EN                             28
/*DAC clock enable*/                    
#define MRCC_APB1_DAC_EN                             29 

/******************************************APB2 Peripherals*****************************************/

/* Alternate function IO clock enable*/
#define MRCC_APB2_AFIO_EN                            0  
/* I/O port A clock enable*/                       
#define MRCC_APB2_IOPA_EN                            2  
/* I/O port B clock enable*/                       
#define MRCC_APB2_IOPB_EN                            3  
/* I/O port C clock enable*/                       
#define MRCC_APB2_IOPC_EN                            4  
/* I/O port D clock enable*/                       
#define MRCC_APB2_IOPD_EN                            5  
/* I/O port E clock enable*/                       
#define MRCC_APB2_IOPE_EN                            6  
/* I/O port F clock enable*/                       
#define MRCC_APB2_IOPF_EN                            7  
/* I/O port G clock enable*/                       
#define MRCC_APB2_IOPG_EN                            8  
/* ADC1 clock enable*/                     
#define MRCC_APB2_ADC1_EN                            9  
/* ADC2 clock enable*/                     
#define MRCC_APB2_ADC2_EN                            10 
/* Timer 1 clock enable*/                      
#define MRCC_APB2_TIM1_EN                            11 
/* SPI1 clock enable*/                     
#define MRCC_APB2_SPI1_EN                            12 
/* Timer 8 clock enable*/                      
#define MRCC_APB2_TIM8_EN                            13 
/* USART1 clock enable*/                       
#define MRCC_APB2_USART1_EN                          14 
/* ADC3 clock enable*/                     
#define MRCC_APB2_ADC3_EN                            15 
/* Timer 9 clock enable*/                      
#define MRCC_APB2_TIM9_EN                            19 
/* Timer 10 clock enable*/                     
#define MRCC_APB2_TIM10_EN                           20 
/* Timer 11 clock enable*/                     
#define MRCC_APB2_TIM11_EN                           21 

/**
 * @brief: Function to initialize the clock of the micro controller whether it is:
 *         1) HSI: High Speed Internal clock (RC Circuit) (freq. 8MHz)
 *         2) HSE: High Speed External Clock -(RC Circuit) --> (Freq. 4 --> 25 MHz)
 *                                           -(Crystal Oscillator) (Freq. 4 --> 16 MHz)
 *         3) PLL: Phase-Locked Loop Clock (Output frequency = input frequency * number) 
 * 
 * @return Std_ReturnType
 * @retval E_OK:        Clock Initialized Successfully
 * @retval E_NOT_OK:    Clock is not initialized Successfully
 */
Std_ReturnType MRCC_InitClock               (void);
/**
 * @brief: Function to enable clock for any peripheral except RCC itself and 
 *          Core Peripherals
 * 
 * @param Copy_uint8BusID: ID of the bus the peripheral is connected to
 * @param Copy_uint8Peripheral: The peripheral whose clock is to be enabled
 * 
 * @return Std_ReturnType
 * @retval E_OK:        Peripheral Clock Enabled Successfully
 * @retval E_NOT_OK:    Peripheral Clock is not Enabled Successfully 
 */
Std_ReturnType MRCC_EnablePeripheralClock   (uint8 Copy_uint8BusID, uint8 Copy_uint8Peripheral);
/**
 * @brief: Function to disable clock for any peripheral except RCC itself and 
 *          Core Peripherals
 * 
 * @param Copy_uint8BusID: ID of the bus the peripheral is connected to
 * @param Copy_uint8Peripheral: The peripheral whose clock is to be disabled
 * 
 * @return Std_ReturnType
 * @retval E_OK:        Peripheral Clock Disabled Successfully
 * @retval E_NOT_OK:    Peripheral Clock is not Disabled Successfully 
 */
Std_ReturnType MRCC_DisablePeripheralClock  (uint8 Copy_uint8BusID, uint8 Copy_uint8Peripheral);
#endif /*_RCC_INTERFACE_H_*/
