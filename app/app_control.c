/********************************************************************************
  * @file    app_control.c 
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
#include "osal.h"
#include "hal_lamp.h"
#include "app_control.h"
#include "stm32f10x.h"

static uint8_t app_task_id=0;
static uint8_t enter = true;
static void set_event_register(void)
{
   if(app_task_id != 0 && enter == true)
	 {
	    hal_lamp_set(Lamp1_id,HAL_LAMP_CLOSE(HAL_LAMP_HOLD));
		 hal_lamp_set(Lamp2_id,HAL_LAMP_OPEN(HAL_LAMP_HOLD));
	 }
	 else if(app_task_id != 0 && enter == false)
	 {
	    ;
	 }
	 else
	 {
	    ;
	 }
	 
}
uint16_t Control_event_loopTask(uint8_t task_id, uint16_t events)
{
    if(events == 0x0000)
    {  //初始化
        app_task_id = task_id;  //记录分配的任务ID
        set_event_register();   //根据使能状态进行事件注册
		  return (events ^ 0x0000);
	 }
    else
	 {
		  ;
	 }			
}


