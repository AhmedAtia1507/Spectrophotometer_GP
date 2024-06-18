/**
 * @file SCommands_Private.h
 * @author Ahmed Atia Said (atiaa6501@gmail.com)
 * @version 1.0
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef _SCOMMANDS_PRIVATE_H_
#define _SCOMMANDS_PRIVATE_H_

void SCommands_GetUVStatus                                  (void);
void SCommands_SetUVOn                                      (void);
void SCommands_SetUVOff                                     (void);
void SCommands_GetVisStatus                                 (void);
void SCommands_SetVisOn                                     (void);
void SCommands_SetVisOff                                    (void);
void SCommands_GetSupplyVoltages                            (void);
void SCommands_SendCurrentMotorsSteps                       (void);
void SCommands_HomeLampMotor                                (void);
void SCommands_HomeWLSelectMotor                            (void);
void SCommands_HomeFilterSelectMotor                        (void);
void SCommands_SendCurrentWL                                (void);
void SCommands_SendCurrentDateTime                          (void);
void SCommands_SendCurrentDetectorValues                    (void);
void SCommands_GetLampMotorPosition                         (void);
void SCommands_SetLampMotorVisible                          (void);
void SCommands_SetLampMotorUV                               (void);

void SCommands_UpdateDateTime                               (uint8*);
void SCommands_SaveFilterMotorCalibSteps                    (uint8*);
void SCommands_SaveFilterMotorCalibWL                       (uint8*);
void SCommands_StartOperation                               (uint8*);
void SCommands_SetReferenceGain                             (uint8*);
void SCommands_SetSampleGain                                (uint8*);
void SCommands_MoveFilterRight                              (uint8*);
void SCommands_MoveFilterLeft                               (uint8*);
void SCommands_SelectFilter                                 (uint8*);
void SCommands_SelectGratingWL                              (uint8*);
void SCommands_MoveGratingLeft                              (uint8*);
void SCommands_MoveGratingRight                             (uint8*);

/*
void SCommands_GetDcDcP12Voltage                            (void);
void SCommands_GetDcDcN12Voltage                            (void);
void SCommands_GetSupply5Voltage                            (void);
void SCommands_GetSupply33Voltage                           (void);
void SCommands_GetSupply12Voltage                           (void);
void SCommands_SetSignalCondGain                            (uint8*);
void SCommands_MoveFilterSelectMotor                        (uint8*);
*/
#endif /*_SCOMMANDS_PRIVATE_H_*/