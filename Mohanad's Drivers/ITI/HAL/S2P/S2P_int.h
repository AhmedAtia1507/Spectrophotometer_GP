/*
 * S2P_int.h
 *
 *  Created on: Aug 22, 2023
 *      Author: admin
 */

#ifndef HAL_S2P_S2P_INT_H_
#define HAL_S2P_S2P_INT_H_

void HS2P_vInit(void);
void HS2P_vSendData(u32 A_u32Data);
void HS2P_vSendData_Arr(u8 *A_u8Data , u8 A_u8Size);

#endif /* HAL_S2P_S2P_INT_H_ */
