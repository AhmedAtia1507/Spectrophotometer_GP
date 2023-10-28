/**
 * @file NVIC_Interface.h
 * @author Ahmed Atia Said (atiaa6501@gmail.com)
 * @brief: Header file to:
 *          1) Define function prototypes used to control Nested Vectored Interrupt Controller peripheral
 *          2) Define Macros to be used in other files for NVIC Peripheral
 * @version 1.0
 * @date 2023-09-03
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef _NVIC_INTERFACE_H_
#define _NVIC_INTERFACE_H_



/**
 * @brief: Enum to define the vector table of external interrupts in our microcontroller
 *         Each interrupt has an interrupt number defined in datasheet at vector table.
 *          "Refer to page 204 in STM32F10x Register Description"
 *         
 * 
 */
typedef enum NVIC_Interrupts
{
    NVIC_WWDG,                  /*Window Watchdog Interrupt*/
    NVIC_PVD,                   /*PVD through EXTI Line detection interrupt*/
    NVIC_TAMPER,                /*Tamper interrupt*/
    NVIC_RTC,                   /*RTC global interrupt*/
    NVIC_FLASH,                 /*Flash global interrupt*/
    NVIC_RCC,                   /*RCC global interrupt*/
    NVIC_EXTI0,                 /*EXTI Line0 interrupt*/
    NVIC_EXTI1,                 /*EXTI Line1 interrupt*/
    NVIC_EXTI2,                 /*EXTI Line2 interrupt*/
    NVIC_EXTI3,                 /*EXTI Line3 interrupt*/
    NVIC_EXTI4,                 /*EXTI Line4 interrupt*/
    NVIC_DMA1_CHANNEL1,         /*DMA1 Channel1 global interrupt*/
    NVIC_DMA1_CHANNEL2,         /*DMA1 Channel2 global interrupt*/
    NVIC_DMA1_CHANNEL3,         /*DMA1 Channel3 global interrupt*/
    NVIC_DMA1_CHANNEL4,         /*DMA1 Channel4 global interrupt*/
    NVIC_DMA1_CHANNEL5,         /*DMA1 Channel5 global interrupt*/
    NVIC_DMA1_CHANNEL6,         /*DMA1 Channel6 global interrupt*/
    NVIC_DMA1_CHANNEL7,         /*DMA1 Channel7 global interrupt*/
    NVIC_ADC1_2,                /*ADC1 and ADC2 global interrupt*/
    NVIC_USB_HP_CAN_TX,         /*USB High Priority or CAN TX interrupts*/
    NVIC_USB_LP_CAN_RX0,        /*USB Low Priority or CAN RX0 interrupts*/
    NVIC_CAN_RX1,               /*CAN RX1 interrupt*/
    NVIC_CAN_SCE,               /*CAN SCE interrupt*/
    NVIC_EXTI9_5,               /*EXTI Line[9:5] interrupts*/
    NVIC_TIM1_BRK,              /*TIM1 Break interrupt*/
    NVIC_TIM1_UP,               /*TIM1 Update interrupt*/
    NVIC_TIM1_TRG_COM,          /*TIM1 Trigger and Commutation interrupts*/
    NVIC_TIM1_CC,               /*TIM1 Capture Compare interrupt*/
    NVIC_TIM2,                  /*TIM2 global interrupt*/
    NVIC_TIM3,                  /*TIM3 global interrupt*/
    NVIC_TIM4,                  /*TIM4 global interrupt*/
    NVIC_I2C1_EV,               /*I2C1 event interrupt*/
    NVIC_I2C1_ER,               /*I2C1 error interrupt*/
    NVIC_I2C2_EV,               /*I2C2 event interrupt*/
    NVIC_I2C2_ER,               /*I2C2 error interrupt*/
    NVIC_SPI1,                  /*SPI1 global interrupt*/
    NVIC_SPI2,                  /*SPI2 global interrupt*/
    NVIC_USART1,                /*USART1 global interrupt*/
    NVIC_USART2,                /*USART2 global interrupt*/
    NVIC_USART3,                /*USART3 global interrupt*/
    NVIC_EXTI15_10,             /*EXTI Line[15:10] interrupts*/
    NVIC_RTC_ALARM,             /*RTC alarm through EXTI line interrupt*/
    NVIC_USB_WAKEUP,            /*USB wakeup from suspend through EXTI line interrupt*/
    NVIC_TIM8_BRK,              /*TIM8 Break interrupt*/
    NVIC_TIM8_UP,               /*TIM8 Update interrupt*/
    NVIC_TIM8_TRG_COM,          /*TIM8 Trigger and Commutation interrupts*/
    NVIC_TIM8_CC,               /*TIM8 Capture Compare interrupt*/
    NVIC_ADC3,                  /*ADC3 global interrupt*/
    NVIC_FSMC,                  /*FSMC global interrupt*/
    NVIC_SDIO,                  /*SDIO global interrupt*/
    NVIC_TIM5,                  /*TIM5 global interrupt*/
    NVIC_SPI3,                  /*SPI3 global interrupt*/
    NVIC_UART4,                 /*UART4 global interrupt*/
    NVIC_UART5,                 /*UART5 global interrupt*/
    NVIC_TIM6,                  /*TIM6 global interrupt*/
    NVIC_TIM7,                  /*TIM7 global interrupt*/
    NVIC_DMA2_CHANNEL1,         /*DMA2 Channel1 global interrupt*/
    NVIC_DMA2_CHANNEL2,         /*DMA2 Channel2 global interrupt*/
    NVIC_DMA2_CHANNEL3,         /*DMA2 Channel3 global interrupt*/
    NVIC_DMA2_CHANNEL4_5        /*DMA2 Channel4 and DMA2 Channel5 global interrupts*/
}NVIC_InterruptType;

/**
 * @brief: Function to enable interrupt of a peripheral
 * 
 * @param Copy_u8InterruptNumber: ID of the peripheral
 * @return Std_ReturnType
 * @retval E_OK: Peripheral Interrupt is enabled successfully
 * @retval E_NOT_OK: Peripheral Interrupt is not enabled 
 */
Std_ReturnType MNVIC_u8EnableInterrupt(NVIC_InterruptType Copy_u32InterruptNumber);
/**
 * @brief: Function to disable interrupt of a peripheral
 * 
 * @param Copy_u8InterruptNumber: ID of the peripheral
 * @return Std_ReturnType
 * @retval E_OK: Peripheral Interrupt is disabled successfully
 * @retval E_NOT_OK: Peripheral Interrupt is not disabled 
 */
Std_ReturnType MNVIC_u8DisableInterrupt(NVIC_InterruptType Copy_u32InterruptNumber);
/**
 * @brief: Function to set pending flag of interrupt of a peripheral
 * 
 * @param Copy_u8InterruptNumber: ID of the peripheral
 * @return Std_ReturnType
 * @retval E_OK: Peripheral Interrupt Pending Flag is set successfully
 * @retval E_NOT_OK: Peripheral Interrupt Pending Flag is not set 
 */
Std_ReturnType MNVIC_u8SetPendingFlag(NVIC_InterruptType Copy_u32InterruptNumber);
/**
 * @brief: Function to clear pending flag of interrupt of a peripheral
 * 
 * @param Copy_u8InterruptNumber: ID of the peripheral
 * @return Std_ReturnType
 * @retval E_OK: Peripheral Interrupt Pending Flag is cleared successfully
 * @retval E_NOT_OK: Peripheral Interrupt Pending Flag is not cleared 
 */
Std_ReturnType MNVIC_u8ClearPendingFlag(NVIC_InterruptType Copy_u32InterruptNumber);
/**
 * @brief: Function to get the status of active flag of an interrupt
 * 
 * @param Copy_u32InterruptNumber: ID of the interrupt
 * @param P_u8ActiveFlag: Pointer to send the status of active flag in (High or low)
 * @return Std_ReturnType
 * @retval E_OK: Peripheral Interrupt Active Flag Status is read successfully
 * @retval E_NOT_OK: Peripheral Interrupt Active Flag Status is not read  
 */
Std_ReturnType MNVIC_u8GetActiveFlag(NVIC_InterruptType Copy_u32InterruptNumber, u8* P_u8ActiveFlag);
/**
 * @brief: Function to set the priority of an interrupt
 * 
 * @param Copy_u32InterruptNumber: ID of the interrupt
 * @param Copy_u8GroupPriority: Group Priority of the interrupt
 * @param Copy_u8SubGroupPriority: Sub priority of the interrupt
 * 
 * @return Std_ReturnType
 * @retval E_OK: Priority has been set successfully
 * @retval E_NOT_OK: Priority has not been set
 * 
 * @note: In order for subpriority grouping to be successfully set, you have to use MSCB_u8SetPriorityGrouping
 *          to set the shape of the priority grouping, otherwise the subpriority will not be set  
 *
 */
Std_ReturnType MNVIC_u8SetInterruptPriority(NVIC_InterruptType Copy_u32InterruptNumber, u8 Copy_u8GroupPriority, u8 Copy_u8SubGroupPriority);
#endif /*_NVIC_INTERFACE_H_*/