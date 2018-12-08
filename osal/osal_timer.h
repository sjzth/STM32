/********************************************************************************
  * @file    osal_timer.h
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
#ifndef OSAL_TIMER
#define OSAL_TIMER
#include "typedef.h"
#ifdef __cplusplus
extern "C"
{
 #endif
/** @addtogroup 系统层
 * @{
 */

 /** 
  * @brief  定时器计数结构定义
  */
typedef struct
{
    void     *next;         ///< 定时器已链表方式储存
    uint16_t timeout;       ///< 超时时间
    uint16_t event_flag;    ///< 事件标志
    uint8_t  task_id;       ///< 任务ID
    uint16_t reloadTimeout; ///< 重载时间
} osalTimerRec_t;

 /** 
  * @brief  extern声明
  */	
extern void osal_time_updata(void);	
	
 #ifdef __cplusplus
 }
 #endif
#endif
 
