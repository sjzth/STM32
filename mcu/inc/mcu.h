/********************************************************************************
  * @file    mcu.h 
  * @author  zhaocc
  * @version V1.0.0
  * @date    2018.12.7
  * @brief   
  ******************************************************************************
  * @attention
  *
  * 
  ******************************************************************************
  */ 
 #ifndef MCU_H
 #define MCU_H
 #include "mcu_typedef.h"
 #ifdef __cplusplus
 extern "C"
{
 #endif
/** @addtogroup Çý¶¯²ã
 * @{
 */
extern void hal_mcu_init(void);

extern void bsp_button_init(void);
extern uint32_t hal_get_elapsed_msec(void);
extern uint32_t hal_mcu_loop(void);
extern void SysTick_Handler(void);
 #ifdef __cplusplus
 }
 #endif

#endif
