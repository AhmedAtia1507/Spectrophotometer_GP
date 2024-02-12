/*
 * Stm32_F103C6_SPI_Driver.h
 *
 *  Created on: Dec 10, 2023
 *      Author: Restart
 */

#ifndef INC_STM32_F103C6_SPI_DRIVER_H_
#define INC_STM32_F103C6_SPI_DRIVER_H_

#include "stdlib.h"
#include <stdint.h>

#include "Stm32_F103C6_GPIO_Driver.h"
//GPIO
//A,B fully included in LQFP48 Package
#define GPIOA_BASE						0X40010800UL
#define GPIOB_BASE						0X40010C00UL


//C,D Partial included in LQFP48 Package
#define GPIOC_BASE						0X40011000UL
#define GPIOD_BASE						0X40011400UL

//E not included in LQFP48 Package
#define GPIOE_BASE						0X40011800UL
///////////
//SPI
#define SPI1_BASE                       0x40013000UL
//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register: GPIO
//-*-*-*-*-*-*-*-*-*-*-*

typedef struct
{
	volatile uint32_t CRL;
	volatile uint32_t CRH;
	volatile uint32_t IDR;
	volatile uint32_t ODR;
	volatile uint32_t BSRR;
	volatile uint32_t BRR;
	volatile uint32_t LCKR;
}GPIO_TypeDef;


//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register: SPI
//-*-*-*-*-*-*-*-*-*-*-*

typedef struct
{
	volatile uint32_t SPI_CR1;
	volatile uint32_t SPI_CR2;
	volatile uint32_t SPI_SR;
	volatile uint32_t SPI_DR;
	volatile uint32_t SPI_CRCPR;
	volatile uint32_t SPI_RXCRCR;
	volatile uint32_t SPI_TXCRCR;
	volatile uint32_t SPI_I2SCFGR;
	volatile uint32_t SPI_I2SPR;
}SPI_TypeDef;

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral Instants:
//-*-*-*-*-*-*-*-*-*-*-*

#define GPIOA			((GPIO_TypeDef *)GPIOA_BASE)
#define GPIOB			((GPIO_TypeDef *)GPIOB_BASE)
#define GPIOC			((GPIO_TypeDef *)GPIOC_BASE)
#define GPIOD			((GPIO_TypeDef *)GPIOD_BASE)
#define GPIOE			((GPIO_TypeDef *)GPIOE_BASE)

#define SPI1			((SPI_TypeDef *)SPI1_BASE)
#define SPI2			((SPI_TypeDef *)SPI2_BASE)
//EXTI

#define SPI1_IQR			35
#define SPI2_IQR			36

//Clock enable
#define RCC_GPIOA_CLK_EN()	(RCC->APB2ENR |= 1<<2)
#define RCC_GPIOB_CLK_EN()	(RCC->APB2ENR |= 1<<3)
#define RCC_GPIOC_CLK_EN()	(RCC->APB2ENR |= 1<<4)
#define RCC_GPIOD_CLK_EN()	(RCC->APB2ENR |= 1<<5)
#define RCC_GPIOE_CLK_EN()	(RCC->APB2ENR |= 1<<6)

#define AFIO_GPIOE_CLK_EN()	(RCC->APB2ENR |= 1<<0)

#define RCC_SPI1_CLK_EN()	(RCC->APB2ENR |= 1<<12)
#define RCC_SPI2_CLK_EN()	(RCC->APB1ENR |= 1<<14)

//Clock reset mechamism
#define RCC_SPI1_Reset()	(RCC->APB2RSTR |= 1<<12)
#define RCC_SPI2_Reset()	(RCC->APB1RSTR |= 1<<14)

//============================================================

struct S_IRQ_SRC
{
	uint8_t	TXE:1;			 //TX buffer empty interrupt
	uint8_t	RXNE:1;          //RX buffer not empty interrupt
	uint8_t	ERRI:1;          //Error interrupt
	uint8_t	Reserved:5;
};


//Configuration structure
typedef struct
{
	uint16_t	Device_Mode; 						//Specifies the SPI operation mode @ref SPI_Device_Mode
	uint16_t	Communication_Mode; 				//Specifies the SPI bidirectional mode state @ref SPI_Communication_Mode
	uint16_t	Frame_Format; 						//Specifies LSB or MSB @ref SPI_Frame_Format
	uint16_t	DataSize; 							//@ref SPI_DataSize
	uint16_t	CLKPolarity; 						//@ref SPI_CLKPolarity
	uint16_t	CLKPhase; 							//@ref SPI_CLKPhase
	uint16_t	NSS; 								//Specifies whether the NSS signal is managed by hardware (NSS pin)
	                                    			// or by software using the SSI bitenable @ref SPI_NSS


	uint16_t	SPI_BAUDRATEPRESCALER; 				/*Specifies the band Rate prescaler value which will be used
	                                    			to configure the transmit and recieve SCK clock.
	                                    			This parameter can be a value of @ref SPI_BAUDRATEPRESCALER
	                                    			@note The communication clock is derived from the master clock.
	                                    			The slave cloch does not need to be set */
													// Take care you have to configure RCC to enter the correct clock to APB2 >>> to SPI

	uint16_t	IRQ_Enable; 						//@ref SPI_IRQ_Enable

	void(* P_IRQ_CallBack)(struct S_IRQ_SRC irq_scr); //set the C Function() which will be called once the IRQ Happen
}SPI_Config;

//-*-*-*-*-*-*-*-*-*-*-*-
//Referance Macros:
//-*-*-*-*-*-*-*-*-*-*-*



//@ref_SPI_Device_Mode
#define SPI_Device_Mode_SLAVE						(0x00000000U)
#define SPI_Device_Mode_MASTER						(0x1U << 2)		 //CR1.MASTER :1: Master configuration

//@ref_SPI_Communication_Mode
#define SPI_Direction_2LINES						(0x00000000U)
#define SPI_Direction_2LINES_RXONLY					(0x1U << 10)	//CR1 Bit 10 RXONLY: Receiver only
#define SPI_Direction_1LINE_recieve_only			(0x1U << 15)	//CR1 Bit 15 BITMODE: Bidirectional data mode enable
#define SPI_Direction_1LINE_transmit_only			((0x1U << 15) | (0x1U << 14))	//CR1 Bit 15 BITMODE: Bidirectional data mode enable & Bit 14 BIDIOE: output enable in Bidirectional mode
#define SPI_Direction_2LINES_RXONLY					(0x1U << 10)	//CR1 Bit 10 RXONLY: Receiver only


//@ref_SPI_DataSize
#define SPI_DataSize_8BIT							(0x00000000U)
#define SPI_DataSize_16BIT							(0x1U << 11) 		//CR1 Bit 11 DFF: Data frame format


//@ref_SPI_Frame_Format
#define SPI_Frame_Format_MSB_transmitted_first		(0x00000000U)
#define SPI_Frame_Format_LSB_transmitted_first		(0x1U << 7) 		//CR1 Bit 7 LSBFIRST: fame format


//@ref_SPI_Clock_Polarity
#define SPI_CLKPolarity_LOW_when_idle				(0x00000000U)
#define SPI_CLKPolarity_HIGH_when_idle				(0x1U << 1) 		//Bit 1 CPOL: Clock Polarity

//@ref_SPI_ClkPhase
#define SPI_Clock_Phase_1EDGE_first_data_capture_edge (0x00000000U)
#define SPI_Clock_Phase_2EDGE_first_data_capture_edge (0x1U << 0) 		//Bit 0 CPHA: Clock phase


//@ref_SPI_NSS  SPI Slave Select Management
//=============================NSS=================================
//Hadrware
#define SPI_NSS_Hard_Slave 							(0x00000000U)
#define SPI_NSS_Hard_Master_SS_output_enable 		(0x1U << 2)         //SPI_CR2 Bit 2 SSOE: SS output enable
#define SPI_NSS_Hard_Master_SS_output_disable 		~(0x1U << 2)       //SPI_CR2 Bit 2 SSOE: SS output disable

//NSS is Driven by SW (Master or Slave)
#define SPI_NSS_soft_NSSInternalSoft_Reset  		(0x1U << 9)
#define SPI_NSS_soft_NSSInternalSoft_Set 		    ((0x1U << 9) | (0x1U << 8))

//===============================================================


//@ref SPI_BAUDRATEPRESCALER
#define SPI_BAUDRATEPRESCALER_2                     (0x00000000U)
#define SPI_BAUDRATEPRESCALER_4                     (0b001U << 3)
#define SPI_BAUDRATEPRESCALER_8                     (0b010U << 3)
#define SPI_BAUDRATEPRESCALER_16                    (0b011U << 3)
#define SPI_BAUDRATEPRESCALER_32                    (0b100U << 3)
#define SPI_BAUDRATEPRESCALER_64                    (0b101U << 3)
#define SPI_BAUDRATEPRESCALER_128                   (0b110U << 3)
#define SPI_BAUDRATEPRESCALER_256                   (0b111U << 3)


//@ref SPI_IRQ_Enable
#define SPI_IRQ_Enable_NONE 						(uint32_t)(0)
#define SPI_IRQ_Enable_TXEIE 						(uint32_t)(1<<7)	//SPI_CR2 Bit 7 TXEIE buffer empty interrupt
#define SPI_IRQ_Enable_RXNEIE 						(uint32_t)(1<<6)	//SPI_CR2 Bit 6 RXNEIE buffer not empty interrupt
#define SPI_IRQ_Enable_ERRIE 						(uint32_t)(1<<5)	//SPI_CR2 Bit 5 ERRIR: Error interrupt

enum PollingMechism{
	Pollingenable ,
	Pollingdisable
};

//==============================================================
//                APIs Suppported by "MCAL SPI DRIVER"
//=============================================================

void MCAL_SPI_Init (SPI_TypeDef *SPIx, SPI_Config* SPI_Config);

void MCAL_SPI_DeInit (SPI_TypeDef *SPIx);

void MCAL_SPI_Set_Pins (SPI_TypeDef *SPIx);

void MCAL_SPI_SendData (SPI_TypeDef *SPIx, uint16_t *pTxBuffer, enum PollingMechism PollingEn);

void MCAL_SPI_ReceiveData (SPI_TypeDef *SPIx, uint16_t *pTxBuffer, enum PollingMechism PollingEn);

void MCAL_SPI_TX_RX (SPI_TypeDef *SPIx, uint16_t *pTxBuffer, enum PollingMechism PollingEn);

void MCAL_SPI_GPIO_Set_Pins (SPI_TypeDef *SPIx);

//void SPI1_IRQHandler (void);
//void SPI2_IRQHandler (void);

#endif /* INC_STM32_F103C6_SPI_DRIVER_H_ */
