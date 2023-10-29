/*
 * RCC_prv.h
 *
 *  Created on: Aug 8, 2023
 *      Author: Mohanad
 */

#ifndef MCAL_RCC_RCC_PRV_H_
#define MCAL_RCC_RCC_PRV_H_

#define RCC_BASE_ADDR		0x40023800		// base address of the registers (from memory map)

typedef struct								// contains the addresses of the registers
{
	u32 CR;				//0x00
	u32 PLLCFGR;		//0x04
	u32 CFGR;			//0x08
	u32 CIR;			//0x0C
	u32 AHB1RSTR;		//0X10
	u32 AHB2RSTR;		//0x14
	u32 Reserved_1;		//0x18
	u32 Reserved_2;		//0x1C
	u32 APB1RSTR;		//0x20
	u32 APB2RSTR;		//0x24
	u32 Reserved_3;		//0x28
	u32 Reserved_4;		//0x2C
	u32 AHB1ENR;		//0x30
	u32 AHB2ENR;		//0x34
	u32 Reserved_5;		//0x38
	u32 Reserved_6;		//0x3C
	u32 APB1ENR;		//0x40
	u32 APB2ENR;		//0x44
	u32 Reserved_7;		//0x48
	u32 Reserved_8;		//0x4C
	u32 AHB1LPENR;		//0X50
	u32 AHB2LPENR;		//0X54
	u32 Reserved_9;		//0x58
	u32 Reserved_10;	//0x5C
	u32 APB1LPENR;		//0X60
	u32 APB2LPENR;		//0X64
	u32 Reserved_11;	//0x68
	u32 Reserved_12;	//0x6C
	u32 BDCR;			//0x70
	u32 CSR;			//0x74
	u32 Reserved_13;	//0x78
	u32 Reserved_14;	//0x7C
	u32 SSCGR;			//0X80
	u32 PLLI2SCFGR;		//0x84
	u32 Reserved_15;	//0x88
	u32 DCKCFGR;		//0X8c
}RCC_MemMap_t;

#define RCC				((volatile RCC_MemMap_t*)(RCC_BASE_ADDR))

#define ENABLE		1
#define DISABLE		0
/* Reg_BITS	RCC_CR */
#define HSEBYP		18
#define CSS_ON		19
#define SW0			0
#define SW1			1
#define SW2			2
#define PLLSRC		22
#define HPRE0		4
#define HPRE1		5
#define HPRE2		6
#define HPRE3		7
#define HSE_ON		16
#define HSI_ON		0
#define PLL_ON		24
#define DMA2		22
#define DMA1		21
#define CRC			12
#define GPIOH		7
#define GPIOE		4
#define GPIOD		3
#define GPIOC		2
#define GPIOB		1
#define GPIOA		0
#define OTGFS		7
#define PWR			28
#define I2C3		23
#define I2C2		22
#define I2C1		21
#define USART2		17
#define SPI3		15
#define SPI2		14
#define WWDG		11
#define TIM5		3
#define TIM4		2
#define TIM3		1
#define TIM2		0
#define TIM11		18
#define TIM10		17
#define TIM9		16
#define SYSCFG		14
#define SPI4		13
#define SPI1		12
#define SDIO		11
#define ADC1		8
#define USART6		5
#define USART1		4
#define TIM1		0

enum Bus_Id{
	AHB1,
	AHB2,
	APB1,
	APB2
}A_u32BusId;

#define RCC_AHB_PS_0		0
#define RCC_AHB_PS_2		0b1000
#define RCC_AHB_PS_4		0b1001
#define RCC_AHB_PS_8		0b1010
#define RCC_AHB_PS_16		0b1011
#define RCC_AHB_PS_64		0b1100
#define RCC_AHB_PS_128		0b1101
#define RCC_AHB_PS_256		0b1110
#define RCC_AHB_PS_512		0b1111

#endif /* MCAL_RCC_RCC_PRV_H_ */
