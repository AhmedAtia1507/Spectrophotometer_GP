/**
 * @file GI_Program.c
 * @author Ahmed Atia Said (atiaa6501@gmail.com)
 * @brief 
 * @version 1.0
 * @date 2023-09-12
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "GI_Interface.h"

/**
 * @brief: Function to enable global interrupt
 * 
 */
void GI_EnableGlobalInterrupt(void)
{
    __asm volatile("cpsie i");
}
/**
 * @brief: Function to disable global interrupt
 * 
 */
void GI_DisableGlobalInterrupt(void)
{
    __asm volatile("cpsid i");
}
