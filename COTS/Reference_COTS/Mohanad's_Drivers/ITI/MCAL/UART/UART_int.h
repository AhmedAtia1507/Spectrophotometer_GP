/*
 * UART_init.h
 *
 *  Created on: Oct 10, 2022
 *      Author: Bahgat Mahmoud
 */

#ifndef MCAL_UART_UART_INT_H_
#define MCAL_UART_UART_INT_H_

#include "UART_prv.h"

/**********************************************/
/* 		The USART Structure Pointer 		  */
/**********************************************/
#define   USART1  ((USART_MemMap_t*)(USART1_BASE_ADDRESS))
#define   USART2  ((USART_MemMap_t*)(USART2_BASE_ADDRESS))
#define   USART6  ((USART_MemMap_t*)(USART6_BASE_ADDRESS))
typedef struct
{
	u32 BaudRate;
	u16 DataWidth;
	u16 StopBits ;
	u16 Parity_Enable;
	u16 Parity_Selection;
	u16 TransferDirection;//TX_ONLY  RX_ONLY  TX_RX
	u16 Oversampling;
}USART_InitType;
//typedef struct
//{
//	u8 ClockOutput ;
//	u8 ClockPolarity;
//	u8 ClockPhase ;
//	u8 LastBitClockPulse;
//}USART_ClockInitTypeDef;

#define USART_OVER_SAMPLING_16    0
#define USART_OVER_SAMPLING_8     1

#define USART_TX_ONLY             0
#define USART_RX_ONLY             1
#define USART_TX_RX               2

#define USART_EVEN_PARITY         0
#define USART_ODD_PARITY          1

#define USART_MODE_8BIT		      0
#define USART_MODE_9BIT		      1

#define USART_STOP_BIT_1	      0
#define USART_STOP_BIT_0_5	      1
#define USART_STOP_BIT_2	      2
#define USART_STOP_BIT_1_5	      3

#define    ENABLE			      1
#define    DISABLE			      0

void MUSART_vInit(USART_InitType *A_InitStruct,USART_MemMap_t *USARTx);
void MUSART_vEnable(USART_MemMap_t *USARTx);
void MUSART_vDisable(USART_MemMap_t *USARTx);

void MUSART_vTransmitByteSynch(USART_MemMap_t *USARTx ,u8 A_u8Byte);
u8 MUSART_vTransmitByteAsynch(USART_MemMap_t *USARTx ,u8 A_u8Byte);
void MUSART_vTransmitString(USART_MemMap_t *USARTx,u8 *A_ptru8String);

u8 MUSART_u8ReceiveByteSynchNonBlocking(USART_MemMap_t *USARTx);
void MUSART_ptrReceiveStringSynchNonBlocking(USART_MemMap_t *USARTx ,char A_u8str[] ,u32 A_u32Size );
u8 MUSART_u8ReceiveByteSynchBlocking(USART_MemMap_t *USARTx );

void MUSART_RxIntSetStatus(USART_MemMap_t *USARTx, u8 A_u8Status);
void MUSART_voidClearFlags(USART_MemMap_t *USARTx);
u8 MUSART_u8ReadDataRegister(USART_MemMap_t *USARTx);

void MUSART1_vSetCallBack(void (*ptr) (void) );
void MUSART2_vSetCallBack(void (*ptr) (void) );
void MUSART6_vSetCallBack(void (*ptr) (void) );

#endif /* MCAL_UART_UART_INT_H_ */
