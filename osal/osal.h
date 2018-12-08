/********************************************************************************
  * @file    osal.h 
  * @author  zhaocc
  * @version V1.0.0
  * @date    2018.12.7
  * @brief   ���ļ�Ϊϵͳ����������Ͷ���ͺ�������
  ******************************************************************************
  * @attention
  *
  * 
  ******************************************************************************
  */ 
#ifndef OSAL_H
#define OSAL_H
#include "typedef.h"

#ifdef __cplusplus
extern "C"
{
 #endif
/** @addtogroup ������
 * @{
 */
#define TASK_NO_TASK 0xff	
	
/** @@brief extern
 * @{
 */
extern void osal_start_system(void);
extern void TimingDelay_Decrement(void);
extern uint8_t osal_set_eventEx( uint8_t task_id, uint16_t event_flag );
	
 #ifdef __cplusplus
 }
 #endif
#endif

