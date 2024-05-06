/**
 * @file SPECTRO_Interface.h
 * @author Ahmed Atia Said (atiaa6501@gmail.com)
 * 
 * @version 1.0
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef _SPECTRO_INTERFACE_H_
#define _SPECTRO_INTERFACE_H_

Std_ReturnType SPECTRO_InitSystem               (void);
Std_ReturnType SPECTRO_InitSoftware             (void);
Std_ReturnType SPECTRO_InitHardware             (void);
Std_ReturnType SPECTRO_InitCalibration          (void);
unsigned char Medium_Step_Index(float* readings, unsigned char size);
#endif /*_SPECTRO_INTERFACE_H_*/