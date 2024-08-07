/*
 * SPI_Config.h
 *
 *  Created on: Feb 25, 2024
 *      Author: Amal Mohamed
 */

#ifndef MCAL_SPI_SPI_CONFIG_H_
#define MCAL_SPI_SPI_CONFIG_H_

#include "../../LIB/STD_TYPES/Std_Types.h"

//Configuration structure
typedef struct
{
	uint16	Device_Mode; 						//Specifies the SPI operation mode @ref SPI_Device_Mode
	uint16	Communication_Mode; 				//Specifies the SPI bidirectional mode state @ref SPI_Communication_Mode
	uint16	Frame_Format; 						//Specifies LSB or MSB @ref SPI_Frame_Format
	uint16	DataSize; 							//@ref SPI_DataSize
	uint16	CLKPolarity; 						//@ref SPI_CLKPolarity
	uint16	CLKPhase; 							//@ref SPI_CLKPhase
	uint16	NSS; 								//Specifies whether the NSS signal is managed by hardware (NSS pin)
	                                    			// or by software using the SSI bitenable @ref SPI_NSS


	uint16	SPI_BAUDRATEPRESCALER; 				/*Specifies the band Rate prescaler value which will be used
	                                    			to configure the transmit and recieve SCK clock.
	                                    			This parameter can be a value of @ref SPI_BAUDRATEPRESCALER
	                                    			@note The communication clock is derived from the master clock.
	                                    			The slave cloch does not need to be set */
													// Take care you have to configure RCC to enter the correct clock to APB2 >>> to SPI

	uint16	IRQ_Enable; 						//@ref SPI_IRQ_Enable

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
#define SPI_IRQ_Enable_NONE 						(uint32)(0)
#define SPI_IRQ_Enable_TXEIE 						(uint32)(1<<7)	//SPI_CR2 Bit 7 TXEIE buffer empty interrupt
#define SPI_IRQ_Enable_RXNEIE 						(uint32)(1<<6)	//SPI_CR2 Bit 6 RXNEIE buffer not empty interrupt
#define SPI_IRQ_Enable_ERRIE 						(uint32)(1<<5)	//SPI_CR2 Bit 5 ERRIR: Error interrupt

enum PollingMechism{
	Pollingenable ,
	Pollingdisable
};

#endif /* MCAL_SPI_SPI_CONFIG_H_ */
