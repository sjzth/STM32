#ifndef MCU_INTERRUTS_H
#define MCU_INTERRUTS_H

#include "stm32f10x.h"
#include "core_cm3.h"

#ifdef __cplusplus
extern "C"
{
#endif

#ifndef HAL_ENABLE_INTERRUPTS
#define HAL_ENABLE_INTERRUPTS         do { __enable_irq(); } while (__LINE__ == -1)
#endif
#ifndef HAL_DISABLE_INTERRUPTS
#define HAL_DISABLE_INTERRUPTS        do { __disable_irq(); } while (__LINE__ == -1)
#endif

#ifdef __cplusplus
}
#endif

#endif
