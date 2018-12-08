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
/** @addtogroup ϵͳ��
 * @{
 */

 /** 
  * @brief  ��ʱ�������ṹ����
  */
typedef struct
{
    void     *next;         ///< ��ʱ��������ʽ����
    uint16_t timeout;       ///< ��ʱʱ��
    uint16_t event_flag;    ///< �¼���־
    uint8_t  task_id;       ///< ����ID
    uint16_t reloadTimeout; ///< ����ʱ��
} osalTimerRec_t;

 /** 
  * @brief  extern����
  */	
extern void osal_time_updata(void);	
	
 #ifdef __cplusplus
 }
 #endif
#endif
 
