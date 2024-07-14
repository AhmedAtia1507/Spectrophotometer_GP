/**
 * @file GPIO_Private.h
 * @author Ahmed Atia Said (atiaa6501@gmail.com)
 * @brief: C header file to:
 *          1) Define Memory Mapping of General Purpose Input/Output
 *          2) Define macros used as choices for pre-build configurations of GPIO Peripheral
 * @version 1.0
 * @date 2023-09-03
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef _GPIO_PRIVATE_H_
#define _GPIO_PRIVATE_H_

#define MGPIO_PORTA_BASE_ADDRESS                         0x40010800
#define MGPIO_PORTB_BASE_ADDRESS                         0x40010C00
#define MGPIO_PORTC_BASE_ADDRESS                         0x40011000
#define MGPIO_PORTD_BASE_ADDRESS                         0x40011400
#define MGPIO_PORTE_BASE_ADDRESS                         0x40011800
#define MGPIO_PORTF_BASE_ADDRESS                         0x40011C00
#define MGPIO_PORTG_BASE_ADDRESS                         0x40012000

/********************************GPIO Port A Registers******************************/

/*Port A configuration register low*/
#define MGPIOA_CRL                                       (*(volatile uint32*)(MGPIO_PORTA_BASE_ADDRESS + 0x00))
/*Port A configuration register high*/
#define MGPIOA_CRH                                       (*(volatile uint32*)(MGPIO_PORTA_BASE_ADDRESS + 0x04))
/*Port A input data register*/
#define MGPIOA_IDR                                       (*(volatile uint32*)(MGPIO_PORTA_BASE_ADDRESS + 0x08))
/*Port A output data register*/
#define MGPIOA_ODR                                       (*(volatile uint32*)(MGPIO_PORTA_BASE_ADDRESS + 0x0C))
/*Port A bit set/reset register*/
#define MGPIOA_BSRR                                      (*(volatile uint32*)(MGPIO_PORTA_BASE_ADDRESS + 0x10))
/*Port A bit reset register*/
#define MGPIOA_BRR                                       (*(volatile uint32*)(MGPIO_PORTA_BASE_ADDRESS + 0x14))
/*Port configuration lock register*/
#define MGPIOA_LCKR                                      (*(volatile uint32*)(MGPIO_PORTA_BASE_ADDRESS + 0x18))
/********************************GPIO Port B Registers******************************/

/*Port B configuration register low*/
#define MGPIOB_CRL                                       (*(volatile uint32*)(MGPIO_PORTB_BASE_ADDRESS + 0x00))
/*Port B configuration register high*/
#define MGPIOB_CRH                                       (*(volatile uint32*)(MGPIO_PORTB_BASE_ADDRESS + 0x04))
/*Port B input data register*/
#define MGPIOB_IDR                                       (*(volatile uint32*)(MGPIO_PORTB_BASE_ADDRESS + 0x08))
/*Port B output data register*/
#define MGPIOB_ODR                                       (*(volatile uint32*)(MGPIO_PORTB_BASE_ADDRESS + 0x0C))
/*Port B bit set/reset register*/
#define MGPIOB_BSRR                                      (*(volatile uint32*)(MGPIO_PORTB_BASE_ADDRESS + 0x10))
/*Port B bit reset register*/
#define MGPIOB_BRR                                       (*(volatile uint32*)(MGPIO_PORTB_BASE_ADDRESS + 0x14))
/*Port B configuration lock register*/
#define MGPIOB_LCKR                                      (*(volatile uint32*)(MGPIO_PORTB_BASE_ADDRESS + 0x18))
/********************************GPIO Port C Registers******************************/

/*Port C configuration register low*/
#define MGPIOC_CRL                                       (*(volatile uint32*)(MGPIO_PORTC_BASE_ADDRESS + 0x00))
/*Port C configuration register high*/
#define MGPIOC_CRH                                       (*(volatile uint32*)(MGPIO_PORTC_BASE_ADDRESS + 0x04))
/*Port C input data register*/
#define MGPIOC_IDR                                       (*(volatile uint32*)(MGPIO_PORTC_BASE_ADDRESS + 0x08))
/*Port C output data register*/
#define MGPIOC_ODR                                       (*(volatile uint32*)(MGPIO_PORTC_BASE_ADDRESS + 0x0C))
/*Port C bit set/reset register*/
#define MGPIOC_BSRR                                      (*(volatile uint32*)(MGPIO_PORTC_BASE_ADDRESS + 0x10))
/*Port C bit reset register*/
#define MGPIOC_BRR                                       (*(volatile uint32*)(MGPIO_PORTC_BASE_ADDRESS + 0x14))
/*Port C configuration lock register*/
#define MGPIOC_LCKR                                      (*(volatile uint32*)(MGPIO_PORTC_BASE_ADDRESS + 0x18))
/********************************GPIO Port D Registers******************************/

/*Port D configuration register low*/
#define MGPIOD_CRL                                       (*(volatile uint32*)(MGPIO_PORTD_BASE_ADDRESS + 0x00))
/*Port D configuration register high*/
#define MGPIOD_CRH                                       (*(volatile uint32*)(MGPIO_PORTD_BASE_ADDRESS + 0x04))
/*Port D input data register*/
#define MGPIOD_IDR                                       (*(volatile uint32*)(MGPIO_PORTD_BASE_ADDRESS + 0x08))
/*Port D output data register*/
#define MGPIOD_ODR                                       (*(volatile uint32*)(MGPIO_PORTD_BASE_ADDRESS + 0x0C))
/*Port D bit set/reset register*/
#define MGPIOD_BSRR                                      (*(volatile uint32*)(MGPIO_PORTD_BASE_ADDRESS + 0x10))
/*Port D bit reset register*/
#define MGPIOD_BRR                                       (*(volatile uint32*)(MGPIO_PORTD_BASE_ADDRESS + 0x14))
/*Port D configuration lock register*/
#define MGPIOD_LCKR                                      (*(volatile uint32*)(MGPIO_PORTD_BASE_ADDRESS + 0x18))
/********************************GPIO Port E Registers******************************/

/*Port E configuration register low*/
#define MGPIOE_CRL                                       (*(volatile uint32*)(MGPIO_PORTE_BASE_ADDRESS + 0x00))
/*Port E configuration register high*/
#define MGPIOE_CRH                                       (*(volatile uint32*)(MGPIO_PORTE_BASE_ADDRESS + 0x04))
/*Port E input data register*/
#define MGPIOE_IDR                                       (*(volatile uint32*)(MGPIO_PORTE_BASE_ADDRESS + 0x08))
/*Port E output data register*/
#define MGPIOE_ODR                                       (*(volatile uint32*)(MGPIO_PORTE_BASE_ADDRESS + 0x0C))
/*Port E bit set/reset register*/
#define MGPIOE_BSRR                                      (*(volatile uint32*)(MGPIO_PORTE_BASE_ADDRESS + 0x10))
/*Port E bit reset register*/
#define MGPIOE_BRR                                       (*(volatile uint32*)(MGPIO_PORTE_BASE_ADDRESS + 0x14))
/*Port E configuration lock register*/
#define MGPIOE_LCKR                                      (*(volatile uint32*)(MGPIO_PORTE_BASE_ADDRESS + 0x18))
/********************************GPIO Port F Registers******************************/

/*Port F configuration register low*/
#define MGPIOF_CRL                                       (*(volatile uint32*)(MGPIO_PORTF_BASE_ADDRESS + 0x00))
/*Port F configuration register high*/
#define MGPIOF_CRH                                       (*(volatile uint32*)(MGPIO_PORTF_BASE_ADDRESS + 0x04))
/*Port F input data register*/
#define MGPIOF_IDR                                       (*(volatile uint32*)(MGPIO_PORTF_BASE_ADDRESS + 0x08))
/*Port F output data register*/
#define MGPIOF_ODR                                       (*(volatile uint32*)(MGPIO_PORTF_BASE_ADDRESS + 0x0C))
/*Port F bit set/reset register*/
#define MGPIOF_BSRR                                      (*(volatile uint32*)(MGPIO_PORTF_BASE_ADDRESS + 0x10))
/*Port F bit reset register*/
#define MGPIOF_BRR                                       (*(volatile uint32*)(MGPIO_PORTF_BASE_ADDRESS + 0x14))
/*Port F configuration lock register*/
#define MGPIOF_LCKR                                      (*(volatile uint32*)(MGPIO_PORTF_BASE_ADDRESS + 0x18))

/********************************GPIO Port G Registers******************************/

/*Port G configuration register low*/
#define MGPIOG_CRL                                       (*(volatile uint32*)(MGPIO_PORTG_BASE_ADDRESS + 0x00))
/*Port G configuration register high*/
#define MGPIOG_CRH                                       (*(volatile uint32*)(MGPIO_PORTG_BASE_ADDRESS + 0x04))
/*Port G input data register*/
#define MGPIOG_IDR                                       (*(volatile uint32*)(MGPIO_PORTG_BASE_ADDRESS + 0x08))
/*Port G output data register*/
#define MGPIOG_ODR                                       (*(volatile uint32*)(MGPIO_PORTG_BASE_ADDRESS + 0x0C))
/*Port G bit set/reset register*/
#define MGPIOG_BSRR                                      (*(volatile uint32*)(MGPIO_PORTG_BASE_ADDRESS + 0x10))
/*Port G bit reset register*/
#define MGPIOG_BRR                                       (*(volatile uint32*)(MGPIO_PORTG_BASE_ADDRESS + 0x14))
/*Port G configuration lock register*/
#define MGPIOG_LCKR                                      (*(volatile uint32*)(MGPIO_PORTG_BASE_ADDRESS + 0x18))

#endif /*_GPIO_PRIVATE_H_*/