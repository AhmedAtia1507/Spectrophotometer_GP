/**
 * @file GPIO_Private.h
 * @author Ahmed Atia Said (atiaa6501@gmail.com)
 * @brief: C header file to:
 *          1) Define Memory Mapping of General Purpose Input/Output
 *          2) Define macros used as choices for pre-build configurations of GPIO Peripheral
 * @version 1.0
 * @date 2023-08-30
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef _GPIO_PRIVATE_H_
#define _GPIO_PRIVATE_H_

#define GPIO_PORTA_BASE_ADDRESS                         0x40010800
#define GPIO_PORTB_BASE_ADDRESS                         0x40010C00
#define GPIO_PORTC_BASE_ADDRESS                         0x40011000
#define GPIO_PORTD_BASE_ADDRESS                         0x40011400
#define GPIO_PORTE_BASE_ADDRESS                         0x40011800
#define GPIO_PORTF_BASE_ADDRESS                         0x40011C00
#define GPIO_PORTG_BASE_ADDRESS                         0x40012000

/********************************GPIO Port A Registers******************************/

/*Port A configuration register low*/
#define GPIOA_CRL                                       (*(volatile u32*)(GPIO_PORTA_BASE_ADDRESS + 0x00))
/*Port A configuration register high*/
#define GPIOA_CRH                                       (*(volatile u32*)(GPIO_PORTA_BASE_ADDRESS + 0x04))
/*Port A input data register*/
#define GPIOA_IDR                                       (*(volatile u32*)(GPIO_PORTA_BASE_ADDRESS + 0x08))
/*Port A output data register*/
#define GPIOA_ODR                                       (*(volatile u32*)(GPIO_PORTA_BASE_ADDRESS + 0x0C))
/*Port A bit set/reset register*/
#define GPIOA_BSRR                                      (*(volatile u32*)(GPIO_PORTA_BASE_ADDRESS + 0x10))
/*Port A bit reset register*/
#define GPIOA_BRR                                       (*(volatile u32*)(GPIO_PORTA_BASE_ADDRESS + 0x14))
/*Port configuration lock register*/
#define GPIOA_LCKR                                      (*(volatile u32*)(GPIO_PORTA_BASE_ADDRESS + 0x18))
/********************************GPIO Port B Registers******************************/

/*Port B configuration register low*/
#define GPIOB_CRL                                       (*(volatile u32*)(GPIO_PORTB_BASE_ADDRESS + 0x00))
/*Port B configuration register high*/
#define GPIOB_CRH                                       (*(volatile u32*)(GPIO_PORTB_BASE_ADDRESS + 0x04))
/*Port B input data register*/
#define GPIOB_IDR                                       (*(volatile u32*)(GPIO_PORTB_BASE_ADDRESS + 0x08))
/*Port B output data register*/
#define GPIOB_ODR                                       (*(volatile u32*)(GPIO_PORTB_BASE_ADDRESS + 0x0C))
/*Port B bit set/reset register*/
#define GPIOB_BSRR                                      (*(volatile u32*)(GPIO_PORTB_BASE_ADDRESS + 0x10))
/*Port B bit reset register*/
#define GPIOB_BRR                                       (*(volatile u32*)(GPIO_PORTB_BASE_ADDRESS + 0x14))
/*Port B configuration lock register*/
#define GPIOB_LCKR                                      (*(volatile u32*)(GPIO_PORTB_BASE_ADDRESS + 0x18))
/********************************GPIO Port C Registers******************************/

/*Port C configuration register low*/
#define GPIOC_CRL                                       (*(volatile u32*)(GPIO_PORTC_BASE_ADDRESS + 0x00))
/*Port C configuration register high*/
#define GPIOC_CRH                                       (*(volatile u32*)(GPIO_PORTC_BASE_ADDRESS + 0x04))
/*Port C input data register*/
#define GPIOC_IDR                                       (*(volatile u32*)(GPIO_PORTC_BASE_ADDRESS + 0x08))
/*Port C output data register*/
#define GPIOC_ODR                                       (*(volatile u32*)(GPIO_PORTC_BASE_ADDRESS + 0x0C))
/*Port C bit set/reset register*/
#define GPIOC_BSRR                                      (*(volatile u32*)(GPIO_PORTC_BASE_ADDRESS + 0x10))
/*Port C bit reset register*/
#define GPIOC_BRR                                       (*(volatile u32*)(GPIO_PORTC_BASE_ADDRESS + 0x14))
/*Port C configuration lock register*/
#define GPIOC_LCKR                                      (*(volatile u32*)(GPIO_PORTC_BASE_ADDRESS + 0x18))
/********************************GPIO Port D Registers******************************/

/*Port D configuration register low*/
#define GPIOD_CRL                                       (*(volatile u32*)(GPIO_PORTD_BASE_ADDRESS + 0x00))
/*Port D configuration register high*/
#define GPIOD_CRH                                       (*(volatile u32*)(GPIO_PORTD_BASE_ADDRESS + 0x04))
/*Port D input data register*/
#define GPIOD_IDR                                       (*(volatile u32*)(GPIO_PORTD_BASE_ADDRESS + 0x08))
/*Port D output data register*/
#define GPIOD_ODR                                       (*(volatile u32*)(GPIO_PORTD_BASE_ADDRESS + 0x0C))
/*Port D bit set/reset register*/
#define GPIOD_BSRR                                      (*(volatile u32*)(GPIO_PORTD_BASE_ADDRESS + 0x10))
/*Port D bit reset register*/
#define GPIOD_BRR                                       (*(volatile u32*)(GPIO_PORTD_BASE_ADDRESS + 0x14))
/*Port D configuration lock register*/
#define GPIOD_LCKR                                      (*(volatile u32*)(GPIO_PORTD_BASE_ADDRESS + 0x18))
/********************************GPIO Port E Registers******************************/

/*Port E configuration register low*/
#define GPIOE_CRL                                       (*(volatile u32*)(GPIO_PORTE_BASE_ADDRESS + 0x00))
/*Port E configuration register high*/
#define GPIOE_CRH                                       (*(volatile u32*)(GPIO_PORTE_BASE_ADDRESS + 0x04))
/*Port E input data register*/
#define GPIOE_IDR                                       (*(volatile u32*)(GPIO_PORTE_BASE_ADDRESS + 0x08))
/*Port E output data register*/
#define GPIOE_ODR                                       (*(volatile u32*)(GPIO_PORTE_BASE_ADDRESS + 0x0C))
/*Port E bit set/reset register*/
#define GPIOE_BSRR                                      (*(volatile u32*)(GPIO_PORTE_BASE_ADDRESS + 0x10))
/*Port E bit reset register*/
#define GPIOE_BRR                                       (*(volatile u32*)(GPIO_PORTE_BASE_ADDRESS + 0x14))
/*Port E configuration lock register*/
#define GPIOE_LCKR                                      (*(volatile u32*)(GPIO_PORTE_BASE_ADDRESS + 0x18))
/********************************GPIO Port F Registers******************************/

/*Port F configuration register low*/
#define GPIOF_CRL                                       (*(volatile u32*)(GPIO_PORTF_BASE_ADDRESS + 0x00))
/*Port F configuration register high*/
#define GPIOF_CRH                                       (*(volatile u32*)(GPIO_PORTF_BASE_ADDRESS + 0x04))
/*Port F input data register*/
#define GPIOF_IDR                                       (*(volatile u32*)(GPIO_PORTF_BASE_ADDRESS + 0x08))
/*Port F output data register*/
#define GPIOF_ODR                                       (*(volatile u32*)(GPIO_PORTF_BASE_ADDRESS + 0x0C))
/*Port F bit set/reset register*/
#define GPIOF_BSRR                                      (*(volatile u32*)(GPIO_PORTF_BASE_ADDRESS + 0x10))
/*Port F bit reset register*/
#define GPIOF_BRR                                       (*(volatile u32*)(GPIO_PORTF_BASE_ADDRESS + 0x14))
/*Port F configuration lock register*/
#define GPIOF_LCKR                                      (*(volatile u32*)(GPIO_PORTF_BASE_ADDRESS + 0x18))

/********************************GPIO Port G Registers******************************/

/*Port G configuration register low*/
#define GPIOG_CRL                                       (*(volatile u32*)(GPIO_PORTG_BASE_ADDRESS + 0x00))
/*Port G configuration register high*/
#define GPIOG_CRH                                       (*(volatile u32*)(GPIO_PORTG_BASE_ADDRESS + 0x04))
/*Port G input data register*/
#define GPIOG_IDR                                       (*(volatile u32*)(GPIO_PORTG_BASE_ADDRESS + 0x08))
/*Port G output data register*/
#define GPIOG_ODR                                       (*(volatile u32*)(GPIO_PORTG_BASE_ADDRESS + 0x0C))
/*Port G bit set/reset register*/
#define GPIOG_BSRR                                      (*(volatile u32*)(GPIO_PORTG_BASE_ADDRESS + 0x10))
/*Port G bit reset register*/
#define GPIOG_BRR                                       (*(volatile u32*)(GPIO_PORTG_BASE_ADDRESS + 0x14))
/*Port G configuration lock register*/
#define GPIOG_LCKR                                      (*(volatile u32*)(GPIO_PORTG_BASE_ADDRESS + 0x18))

#endif /*_GPIO_PRIVATE_H_*/