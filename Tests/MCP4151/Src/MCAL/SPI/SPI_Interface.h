/*
 * SPI_Interface.h
 *
 *  Created on: Feb 25, 2024
 *      Author: Amal Mohamed
 */

#ifndef MCAL_SPI_SPI_INTERFACE_H_
#define MCAL_SPI_SPI_INTERFACE_H_

#include "SPI_Config.h"
#include "SPI_Private.h"
#include "../../LIB/STD_TYPES/Std_Types.h"
#include "../../MCAL/RCC/RCC_Interface.h"
#include "../../MCAL/GPIO/GPIO_Interface.h"

//==============================================================
//                APIs Suppported by "MCAL SPI DRIVER"
//=============================================================

void MCAL_SPI_Init (SPI_TypeDef *SPIx, SPI_Config* SPI_Config);

void MCAL_SPI_DeInit (SPI_TypeDef *SPIx);

void MCAL_SPI_Set_Pins (SPI_TypeDef *SPIx);

void MCAL_SPI_SendData (SPI_TypeDef *SPIx, uint16 *pTxBuffer, enum PollingMechism PollingEn);

void MCAL_SPI_ReceiveData (SPI_TypeDef *SPIx, uint16 *pTxBuffer, enum PollingMechism PollingEn);

void MCAL_SPI_TX_RX (SPI_TypeDef *SPIx, uint16 *pTxBuffer, enum PollingMechism PollingEn);

void MCAL_SPI_GPIO_Set_Pins (SPI_TypeDef *SPIx);

//void SPI1_IRQHandler (void);
//void SPI2_IRQHandler (void);

#endif /* MCAL_SPI_SPI_INTERFACE_H_ */
