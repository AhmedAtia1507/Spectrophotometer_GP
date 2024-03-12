/*
 * SPI_Program.c
 *
 *  Created on: Feb 25, 2024
 *      Author: Amal Mohamed
 */


#include "SPI_Interface.h"

/*
 * =======================================================================================
 * 							Generic Variables
 * =======================================================================================
 */
SPI_Config* Global_SPI_Config[2]  = {0,0} ;
SPI_Config Global_SPI_Config1 ;
SPI_Config Global_SPI_Config2 ;

/*
 * =======================================================================================
 * 							Generic Macros
 * =======================================================================================
 */

#define 		SPI1_INDEX 				0
#define 		SPI2_INDEX 				1

/*
 * =======================================================================================
 * 							APIs
 * =======================================================================================
 */

/**================================================================
 * @Fn				-MCAL_SPI_Init
 * @brief 			- Initialize the SPI according to the specified parameters
 * @param [in] 		- SPIx: where x can be (1..3 depending on device used)
 * @param [in] 		- SPI_Config: All SPI Configuration EXTI_PinConfig_t
 * @retval 			-none
 * Note				-Support for SPI Full Duplex Master/Slave only  & NSS HW only for slave
 * 					- in case of master you have to configure pin and drive it
 */
void MCAL_SPI_Init (SPI_TypeDef *SPIx, SPI_Config* SPI_Config)
{
	uint16 tmpreg_CR1 = 0;
	uint16 tmpreg_CR2 = 0;

	if (SPIx == SPI1)
	{
		Global_SPI_Config1 = *SPI_Config ;
		Global_SPI_Config[SPI1_INDEX] =  &Global_SPI_Config1 ;
		MRCC_EnablePeripheralClock(MRCC_APB2, MRCC_APB2_SPI1_EN);

	}else if (SPIx == SPI2)
	{
		Global_SPI_Config2 = *SPI_Config ;
		Global_SPI_Config[SPI2_INDEX] =  &Global_SPI_Config2 ;
		MRCC_EnablePeripheralClock(MRCC_APB1, MRCC_APB1_SPI2_EN);

	}


	//Enabe SPI  CR1:Bit 6 SPE: SPI enable
	tmpreg_CR1 = (0x1U<<6) ;

	//Master or Slave
	tmpreg_CR1 |=  SPI_Config->Device_Mode ;

	//SPI_Communication_Mode
	tmpreg_CR1 |=  SPI_Config->Communication_Mode ;

	//SPI_Frame_Format
	tmpreg_CR1 |=  SPI_Config->Frame_Format ;

	//SPI_DataSize
	tmpreg_CR1 |=  SPI_Config->DataSize ;

	//SPI_Clock_Polarity
	tmpreg_CR1 |=  SPI_Config->CLKPolarity ;

	//SPI_Clock_Phase
	tmpreg_CR1 |=  SPI_Config->CLKPhase ;

	//======================NSS=================================

	if (SPI_Config->NSS == SPI_NSS_Hard_Master_SS_output_enable )
	{
		tmpreg_CR2 |=  SPI_Config->NSS ;

	}else	if (SPI_Config->NSS == SPI_NSS_Hard_Master_SS_output_disable )
	{
		tmpreg_CR2 &=  SPI_Config->NSS ;

	}else
	{
		tmpreg_CR1 |=  SPI_Config->NSS ;

	}

	//=======================================================


	//SPI_BAUDRATEPRESCALER
	tmpreg_CR1 |=  SPI_Config->SPI_BAUDRATEPRESCALER ;


//	if (SPI_Config->IRQ_Enable  != SPI_IRQ_Enable_NONE)
//	{
//		// SPI_IRQ_Enable_define
//		tmpreg_CR2 |= SPI_Config->IRQ_Enable ;
//
//
//		if (SPIx == SPI1)
//		{
//			NVIC_IRQ35_SPI1_Enable() ;
//
//		}else if (SPIx == SPI2)
//		{
//			NVIC_IRQ36_SPI2_Enable() ;
//		}
//
//	}



	SPIx->SPI_CR1 = tmpreg_CR1 ;
	SPIx->SPI_CR2 = tmpreg_CR2 ;
	  /* Activate the SPI mode (Reset I2SMOD bit in I2SCFGR register) */
	SPIx->SPI_I2SCFGR &= ~(1<<11);

	SPIx->SPI_CRCPR = 0x0 ;
}

void MCAL_SPI_DeInit (SPI_TypeDef *SPIx)
{
	if (SPIx == SPI1)
	{
		//NVIC_IRQ35_SPI1_Disable();
		MRCC_DisablePeripheralClock(MRCC_APB2, MRCC_APB2_SPI1_EN);

	}else if (SPIx == SPI2)
	{
		//NVIC_IRQ36_SPI2_Disable();
		MRCC_DisablePeripheralClock(MRCC_APB1, MRCC_APB1_SPI2_EN);
	}



}
#define  SPI_SR_TXE                          ((uint16)0x02)               /*!< Transmit buffer Empty */
#define  SPI_SR_RXNE                         ((uint16)0x01)               /*!< Receive buffer Not Empty */


void  MCAL_SPI_TX_RX (SPI_TypeDef *SPIx, uint16 *pTxBuffer,enum PollingMechism PollingEn )
{
	while(!((SPIx)->SPI_SR & SPI_SR_TXE));
	SPIx->SPI_DR = *pTxBuffer;
	while(!((SPIx)->SPI_SR & SPI_SR_RXNE));
	*pTxBuffer = SPIx->SPI_DR;


}

void MCAL_SPI_SendData	(SPI_TypeDef *SPIx, uint16 *pTxBuffer,enum PollingMechism PollingEn )
{
	uint8 index = 0 ;
	if (SPIx == SPI1)
	{
		index =  SPI1_INDEX ;

	}else if (SPIx == SPI2)
	{
		index =  SPI2_INDEX ;
	}

	if (Global_SPI_Config[index]->Communication_Mode ==  SPI_Direction_2LINES || Global_SPI_Config[index]->Communication_Mode == SPI_Direction_1LINE_transmit_only) {
		if (PollingEn == Pollingenable) //Bit 1 TXE: Transmit buffer empty
			while(!((SPIx)->SPI_SR & SPI_SR_TXE));


		SPIx->SPI_DR =  (*pTxBuffer ) ;


	}
	else
	{
		//SPIx->SPI_DR =  (*pTxBuffer ) ;//todo
	}

}

void MCAL_SPI_ReceiveData	(SPI_TypeDef *SPIx, uint16 *pTxBuffer ,enum PollingMechism PollingEn )
{
	uint8 index = 0 ;
	if (SPIx == SPI1)
	{
		index =  SPI1_INDEX ;

	}else if (SPIx == SPI2)
	{
		index =  SPI2_INDEX ;
	}

	if ( (Global_SPI_Config[index]->Communication_Mode ==  SPI_Direction_2LINES)  || (Global_SPI_Config[index]->Communication_Mode  ==  SPI_Direction_2LINES_RXONLY) )
	{

		if (PollingEn == Pollingenable) //Bit 0 RXNE: Receive buffer not empty
			while(!((SPIx)->SPI_SR & SPI_SR_RXNE));


		*pTxBuffer = 	SPIx->SPI_DR  ;
	}
	else
	{
		//todo
	}
}



/*
 * =======================================================================================
 * 							Generic Functions
 * =======================================================================================
 */
//ISR
//void SPI1_IRQHandler (void)
//{
//	struct S_IRQ_SRC irq_src ;
//	irq_src.TXE = ( ( SPI1->SPI_SR &  (1<<1)) >> 1 );
//	irq_src.RXNE = ( ( SPI1->SPI_SR &  (1<<0)) >> 0 );
//	irq_src.ERRI = ( ( SPI1->SPI_SR &  (1<<4)) >> 4 );
//
//
//	Global_SPI_Config[SPI1_INDEX]->P_IRQ_CallBack (irq_src) ;
//
//}
//void SPI2_IRQHandler (void)
//{
//	struct S_IRQ_SRC irq_src ;
//	irq_src.TXE = ( ( SPI2->SPI_SR &  (1<<1)) >> 1 );
//	irq_src.RXNE = ( ( SPI2->SPI_SR &  (1<<0)) >> 0 );
//	irq_src.ERRI = ( ( SPI2->SPI_SR &  (1<<4)) >> 4 );
//	Global_SPI_Config[SPI2_INDEX]->P_IRQ_CallBack (irq_src) ;
//}




void MCAL_SPI_GPIO_Set_Pins (SPI_TypeDef *SPIx)
{
	if (SPIx == SPI1)
	{
		//		PA4 : SPI1_NSS
		//		PA5 : SPI1_SCK
		//		PA6 : SPI1_MISO
		//		PA7 : SPI1_MOSI

		if (Global_SPI_Config[SPI1_INDEX]->Device_Mode == SPI_Device_Mode_MASTER )
		{


			//PA4 : SPI1_NSS

			switch  (Global_SPI_Config[SPI1_INDEX]->NSS)
			{

			case SPI_NSS_Hard_Master_SS_output_disable:
				//Hardware master /slave Input floating
				MGPIO_SetPinMode(MGPIO_PORTA, MGPIO_PIN4, MGPIO_INPUT_FLOATING_MODE);
				break ;


			case SPI_NSS_Hard_Master_SS_output_enable:
				//Hardware master/ NSS output enabled Alternate function push-pull
				MGPIO_SetPinMode(MGPIO_PORTA, MGPIO_PIN4, MGPIO_OUTPUT_AF_PUSH_PULL_10MHZ);
				break ;
			}


			//		PA5 : SPI1_SCK
			//			Master Alternate function push-pull
			MGPIO_SetPinMode(MGPIO_PORTA, MGPIO_PIN5, MGPIO_OUTPUT_AF_PUSH_PULL_10MHZ);


			//		PA6 : SPI1_MISO  (supported only full duplex)
			//			Full duplex / master Input floating

			MGPIO_SetPinMode(MGPIO_PORTA, MGPIO_PIN6, MGPIO_INPUT_FLOATING_MODE);

			//todo to suport half duplex and simplex


			//		PA7 : SPI1_MOSI
			//			Full duplex / master Alternate function push-pull
			MGPIO_SetPinMode(MGPIO_PORTA, MGPIO_PIN7, MGPIO_OUTPUT_AF_PUSH_PULL_10MHZ);



		}else  //Slave
		{

			//PA4 : SPI1_NSS

			if   (Global_SPI_Config[SPI1_INDEX]->NSS == SPI_NSS_Hard_Slave)
			{

				//Hardware master /slave Input floating
				MGPIO_SetPinMode(MGPIO_PORTA, MGPIO_PIN4, MGPIO_INPUT_FLOATING_MODE);

			}

			//		PA5 : SPI1_SCK
			//			Slave Input floating
			MGPIO_SetPinMode(MGPIO_PORTA, MGPIO_PIN5, MGPIO_INPUT_FLOATING_MODE);


			//		PA6 : SPI1_MISO  (supported only full duplex)
			//			Full duplex / slave (point to point) Alternate function push-pull
			//todo			Full duplex / slave (multi-slave) Alternate function open drain
			MGPIO_SetPinMode(MGPIO_PORTA, MGPIO_PIN6, MGPIO_OUTPUT_AF_PUSH_PULL_10MHZ);

			//		PA7 : SPI1_MOSI
			//			Full duplex / slave Input floating
			MGPIO_SetPinMode(MGPIO_PORTA, MGPIO_PIN7, MGPIO_INPUT_FLOATING_MODE);

		}


		//============================================================SPI2
	}else if (SPIx == SPI2)
	{

		//		PB12 : SPI2_NSS
		//		PB13 : SPI2_SCK
		//		PB14 : SPI2_MISO
		//		PB15 : SPI2_MOSI

		if (Global_SPI_Config[SPI2_INDEX]->Device_Mode == SPI_Device_Mode_MASTER )
		{


			//		PB12 : SPI2_NSS

			switch  (Global_SPI_Config[SPI2_INDEX]->NSS)
			{

			case SPI_NSS_Hard_Master_SS_output_disable:
				//Hardware master /slave Input floating
				MGPIO_SetPinMode(MGPIO_PORTB, MGPIO_PIN12, MGPIO_INPUT_FLOATING_MODE);
				break ;


			case SPI_NSS_Hard_Master_SS_output_enable:
				//Hardware master/ NSS output enabled Alternate function push-pull
				MGPIO_SetPinMode(MGPIO_PORTB, MGPIO_PIN12, MGPIO_OUTPUT_AF_PUSH_PULL_10MHZ);
				break ;
			}


			//		PB13 : SPI2_SCK
			//			Master Alternate function push-pull
			MGPIO_SetPinMode(MGPIO_PORTB, MGPIO_PIN13, MGPIO_OUTPUT_AF_PUSH_PULL_10MHZ);


			//		PB14 : SPI1_MISO  (supported only full duplex)
			//			Full duplex / master Input floating

			MGPIO_SetPinMode(MGPIO_PORTB, MGPIO_PIN14, MGPIO_INPUT_FLOATING_MODE);

			//todo to suport half duplex and simplex


			//		PB15 : SPI1_MOSI
			//			Full duplex / master Alternate function push-pull
			MGPIO_SetPinMode(MGPIO_PORTB, MGPIO_PIN15, MGPIO_OUTPUT_AF_PUSH_PULL_10MHZ);



		}else  //Slave
		{

			//PB12 : SPI1_NSS

			switch  (Global_SPI_Config[SPI2_INDEX]->NSS)
			{

			case SPI_NSS_Hard_Slave:
				//slave Input floating
				MGPIO_SetPinMode(MGPIO_PORTB, MGPIO_PIN12, MGPIO_INPUT_FLOATING_MODE);

			}

			//		B13 : SPI1_SCK
			//			Slave Input floating
			MGPIO_SetPinMode(MGPIO_PORTB, MGPIO_PIN13, MGPIO_INPUT_FLOATING_MODE);


			//		PB14 : SPI1_MISO  (supported only full duplex)
			//			Full duplex / slave (point to point) Alternate function push-pull
			//todo			Full duplex / slave (multi-slave) Alternate function open drain
			MGPIO_SetPinMode(MGPIO_PORTB, MGPIO_PIN14, MGPIO_OUTPUT_AF_PUSH_PULL_10MHZ);

			//		PB15 : SPI1_MOSI
			//			Full duplex / slave Input floating
			MGPIO_SetPinMode(MGPIO_PORTB, MGPIO_PIN15, MGPIO_OUTPUT_AF_PUSH_PULL_10MHZ);

		}


	}

}
