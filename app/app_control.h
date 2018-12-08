/********************************************************************************
  * @file    app_control.h 
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
#ifndef APP_CONTROL_H
#define APP_CONTROL_H
#include "osal.h"
#ifdef __cplusplus
extern "C"
{
 #endif
extern uint16_t Control_event_loopTask(uint8_t task_id, uint16_t events);
	
/** @addtogroup ÏµÍ³²ã
  * @{
  */
  extern void hal_mcu_init(void);
	extern void bsp_init(void); 
 #ifdef __cplusplus
 }
 #endif	
#endif
