/********************************************************************************
  * @file    osal.c 
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
#include "hal.h"
#include "osal.h"
#include "osal_task.h"
#include "osal_timer.h"

static volatile uint8_t activeTaskID = TASK_NO_TASK;

uint8_t osal_set_eventEx( uint8_t task_id, uint16_t event_flag )
{
    if( task_id < tasksCnt )
    {
        halIntState_t x;
        HAL_ENTER_CRITICAL_SECTION(x);
        tasksEvents[task_id] |= event_flag;
        HAL_EXIT_CRITICAL_SECTION(x);
        return ( OSAL_SUCCESS );
    }
    else
    {
        return ( INVALID_TASK );
    }
}
/*!
    @brief      初始化系统任务
    @param      无
    @return     无
    @note       顺序调用任务处理函数进行任务初始化
*/
void osal_init_system(void)
{
    uint8_t idx = 0;
    hal_init();
    do {
        (tasksArr[idx])(idx,0x0000);
    } while (++idx < tasksCnt);
}
/*!
    @brief      运行系统
    @param      无
    @return     无
    @note       
*/
void osal_run_system(void)
{
    uint8_t idx = 0;
	 osal_time_updata();  //time update
    hal_loop();
	  do{
		   if(tasksEvents[idx])break;
		}while(++idx < tasksCnt);
		if(idx < tasksCnt)
		{
		    uint16_t events;
        halIntState_t x;
        HAL_ENTER_CRITICAL_SECTION(x);  //进入临界区
        events = tasksEvents[idx];      //保存任务事件
        tasksEvents[idx] = 0;           //事件清空
        HAL_EXIT_CRITICAL_SECTION(x);   //退出临界区
			
			  activeTaskID = idx;             //保存当前处理任务ID
        events = (tasksArr[idx])(idx, events); //调用任务事件处理函数
        activeTaskID = TASK_NO_TASK;    //清空当前处理任务ID

        HAL_ENTER_CRITICAL_SECTION(x);  //进入临界区
        tasksEvents[idx] |= events;     //将未处理完的事件重新放回
        HAL_EXIT_CRITICAL_SECTION(x);   //退出临界区
		}
}

/*!
    @brief      stm32f1x3主程序
    @param      无
    @return     int:标准返回类型
    @note       运行系统。 
*/
void osal_start_system(void)
{
    osal_init_system();
    for(;;){
		   osal_run_system();	  
		}
}
