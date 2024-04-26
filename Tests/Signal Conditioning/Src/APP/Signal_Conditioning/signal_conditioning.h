/*
 * signal_conditioning.h
 *
 *  Created on: Apr 23, 2024
 *      Author: Mohanad
 */

#ifndef APP_SIGNAL_CONDITIONING_SIGNAL_CONDITIONING_H_
#define APP_SIGNAL_CONDITIONING_SIGNAL_CONDITIONING_H_

#include "Std_Types.h"

void read_reference_voltage(float32 *ref, float32 *gain);
void read_sample_voltage(float32 *sample, float32 *gain);

#endif /* APP_SIGNAL_CONDITIONING_SIGNAL_CONDITIONING_H_ */
