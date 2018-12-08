/********************************************************************************
  * @file    osal_timer.c 
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
#include "mcu.h"
#include "hal.h"
#include "osal.h"
#include "osal_timer.h"

static osalTimerRec_t *timerHead;
static uint32_t osal_systemClock;

void osal_timer_update( uint16_t elapsedMSec )
{
    if( elapsedMSec != 0 )
    {
        osalTimerRec_t *timer;
        halIntState_t x;
        HAL_ENTER_CRITICAL_SECTION(x);
        osal_systemClock += elapsedMSec;
        HAL_EXIT_CRITICAL_SECTION(x);
        //循环遍历
        for( timer = timerHead; timer != NULL; timer = timer->next )
        {//是否正在计时
            if( timer->timeout != 0 )
            {
                //是否超时
                HAL_ENTER_CRITICAL_SECTION(x);
                if( timer->timeout <= elapsedMSec )//超时
                {
                    timer->timeout = timer->reloadTimeout;
                }
                else
                {
                    timer->timeout -= elapsedMSec;
                }HAL_EXIT_CRITICAL_SECTION(x);
                if(timer->timeout == timer->reloadTimeout)//
                {
                    osal_set_eventEx( timer->task_id, timer->event_flag );
                }
            }
        }
    }
}
void osal_time_updata(void)
{
	uint16_t elapsedMSec;
	elapsedMSec = hal_get_elapsed_msec();
	if(elapsedMSec != 0)
	{
		osal_timer_update(elapsedMSec);
	}
}
