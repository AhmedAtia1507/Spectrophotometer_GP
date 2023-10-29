/*
 * SSD_int.h
 *
 *  Created on: Aug 22, 2023
 *      Author: Mohanad
 */

#ifndef HAL_SSD_SSD_INT_H_
#define HAL_SSD_SSD_INT_H_

#include "../../LIB/STD_TYPES.h"

typedef struct
{
	u8 port;
	u8 pin ;
}SSD_cfg_t;

/* A_u8Type */
#define SSD_COMMON_CATHOD		0
#define SSD_COMMON_ANODE		1

void HSSD_vInit(SSD_cfg_t *A_xptr);
void HSSD_vDisplay(SSD_cfg_t *A_xptr,u8 A_u8Val,u8 A_u8Type);
void HSSD_vTurnOff(SSD_cfg_t *A_xptr,u8 A_u8Type);

#endif /* HAL_SSD_SSD_INT_H_ */
