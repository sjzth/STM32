/********************************************************************************
  * @file    bsp.h 
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
#ifndef BSP_H
#define BSP_H

#ifdef __cplusplus
extern "C"
{
 #endif
	
/** @task BSP task
  * @{
  */	 	
typedef enum {
   Lamp1_id,
	 Lamp2_id
} bsp_port_id;
	
/** @addtogroup ϵͳ��
  * @{
  */
  extern void hal_mcu_init(void);
	extern void bsp_init(void); 
 #ifdef __cplusplus
 }
 #endif	
#endif
