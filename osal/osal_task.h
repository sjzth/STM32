/********************************************************************************
  * @file    mcu_port.h 
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
#ifndef OSAL_TASKS_H
#define OSAL_TASKS_H
#include "osal.h"
#ifdef __cplusplus
extern "C"
{
#endif

/* ���������ṹ */
typedef uint16_t (*pTaskEventHandlerFn)( uint8_t task_id, uint16_t events );

/* ������������ */
extern const pTaskEventHandlerFn tasksArr[];
extern uint16_t tasksEvents[];
extern const uint8_t tasksCnt;
#ifdef __cplusplus
}
#endif

#endif
