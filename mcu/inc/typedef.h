/********************************************************************************
  * @file    typedef.h 
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
#ifndef TYPEDEDEF_H
#define TYPEDEDEF_H
#include "mcu_typedef.h"
 
 #ifdef __cplusplus
 extern "C"
 {
 #endif
/** @defgroup ÏµÍ³²ã
  * @{
  */	 
#ifndef false
#define false 0
#endif

#ifndef true
#define true 1
#endif

#define OSAL_SUCCESS              0x00
#define OSAL_FAILURE              0x01
#define INVALIDPARAMETER          0x02
#define INVALID_TASK              0x03
#define MSG_BUFFER_NOT_AVAIL      0x04
#define INVALID_MSG_POINTER       0x05
#define INVALID_EVENT_ID          0x06
#define INVALID_INTERRUPT_ID      0x07
#define NO_TIMER_AVAIL            0x08
#define NV_ITEM_UNINIT            0x09
#define NV_OPER_FAILED            0x0A
#define INVALID_MEM_SIZE          0x0B
#define NV_BAD_ITEM_LEN           0x0C
#define TIMER_NOT_REGISTER        0x0D

/** @addtogroup extern
  * @{
  */
  extern void hal_mcu_init(void);
	 
 #ifdef __cplusplus
 }
 #endif	
  
#endif
