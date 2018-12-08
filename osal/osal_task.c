/********************************************************************************
  * @file    osal_task.c 
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
#include "osal_task.h"
#include "app_control.h"
const pTaskEventHandlerFn tasksArr[] = {
    Control_event_loopTask,
};
const uint8_t tasksCnt = sizeof( tasksArr ) / sizeof( tasksArr[0] );
uint16_t tasksEvents[ sizeof( tasksArr ) / sizeof( tasksArr[0] ) ] = {0,};
