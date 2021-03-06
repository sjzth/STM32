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
/*!
    @brief      添加定时器
    @param      timer：要链入的定时器地址
    @return     无
    @note       将定时器链入链表中，文件内部使用函数，不提垢獠渴褂�
*/
static void osal_timer_add( osalTimerRec_t *timer )
{
    osalTimerRec_t *tmp;
    osalTimerRec_t *over;
    //查找是否已存在
    for( over = NULL, tmp = timerHead; tmp != NULL; over = tmp, tmp = tmp->next )
    {
        if( timer == tmp )
        {
            break;
        }
    }//没有找到,添加到尾部
    if( tmp == NULL )
    {
        halIntState_t x;
        HAL_ENTER_CRITICAL_SECTION(x);
        if(over == NULL)
            timerHead = timer;
        else
            over->next = timer;
        HAL_EXIT_CRITICAL_SECTION(x);
    }
}
/*!
    @brief      查找定时器
    @param      task_id：定时器要注册的任务ID
    @param      event_flag：定时器要注册的事件标志
    @return     定时器地址，若找不到则为NULL
    @note       使用任务事件来查找定时器地址，文件内部使用函数，不提垢獠渴褂�
*/
static osalTimerRec_t* osal_timer_find( uint8_t task_id, uint16_t event_flag )
{
    osalTimerRec_t *timer;
    for( timer = timerHead; timer != NULL; timer = timer->next )
    {
        if( timer->task_id == task_id && timer->event_flag == event_flag )
        {
            return timer;
        } 
    }
    return NULL;
}
/*!
    @brief      初始化定时器
    @param      无
    @return     无
*/
void osal_timer_init( void )
{
    osal_systemClock = 0;
}
/*!
    @brief      注册任务事件定时器
    @param      *timer：要注册到任务事件上定时器的地址
    @param      task_id：定时器要注册的任务ID
    @param      event_flag：定时器要注册的事件标志
    @return     无
    @note       该系统无内存分配功能，需要自行定义变量再注册到任务事件中才可运行定时功能
*/
void osal_timer_registerEx( osalTimerRec_t *timer, uint8_t task_id, uint16_t event_flag )
{
    halIntState_t x;
    HAL_ENTER_CRITICAL_SECTION(x);
    timer->timeout       = 0;
    timer->reloadTimeout = 0;
    timer->event_flag    = event_flag;
    timer->task_id       = task_id;
    HAL_EXIT_CRITICAL_SECTION(x);
    osal_timer_add( timer );
}
/*!
    @brief      启动事件触发定时器
    @param      task_id：要启动定时器的任务ID
    @param      event_flag：要启动定时器的事件标志
    @param      timeout_value：定时器触发时间(ms)，最大值60000
    @return     OSAL_SUCCESS代表成功设置该定时器；TIMER_NOT_REGISTER代表找不到这个定时器；参考 @ref 通用状态返回值 
    @note       经过触发时间后置起任务事件标志位，仅一次
*/
uint8_t osal_start_timerEx( uint8_t task_id, uint16_t event_flag, uint16_t timeout_value )
{
    osalTimerRec_t *timer;
    timer = osal_timer_find( task_id,event_flag );
    if( timer != NULL ) 
    {
        halIntState_t x;
        HAL_ENTER_CRITICAL_SECTION(x);
        timer->timeout = timeout_value;
        timer->reloadTimeout = 0;
        HAL_EXIT_CRITICAL_SECTION(x);
        return OSAL_SUCCESS;
    }
    return TIMER_NOT_REGISTER;
} 
/*!
    @brief      启动事件循环触发定时器
    @param      task_id：要启动定时器的任务ID
    @param      event_flag：要启动定时器的事件标志
    @param      timeout_value：定时器循环周期时间(ms)，最大值60000
    @return     OSAL_SUCCESS代表成功设置该定时器；TIMER_NOT_REGISTER代表找不到这个定时器；参考 @ref 通用状态返回值 
    @note       未停止前将周期性置起任务事件标志位
*/
uint8_t osal_start_reload_timerEx( uint8_t task_id, uint16_t event_flag, uint16_t timeout_value )
{
    osalTimerRec_t *timer;
    timer = osal_timer_find( task_id, event_flag );
    if(timeout_value > 60000) timeout_value = 60000;
    if( timer != NULL ) 
    {
        halIntState_t x;HAL_ENTER_CRITICAL_SECTION(x);
        timer->timeout       = timeout_value;
        timer->reloadTimeout = timeout_value;
        HAL_EXIT_CRITICAL_SECTION(x);
        return OSAL_SUCCESS;
    }
    return TIMER_NOT_REGISTER;
}
/*!
    @brief      停止定时器
    @param      task_id：要停止定时器的任务ID
    @param      event_flag：要停止定时器的事件标志
    @return     OSAL_SUCCESS代表有这个定时器；TIMER_NOT_REGISTER代表找不到这个定时器；参考 @ref 通用状态返回值 
    @note       距离定时器超时触发的时间(ms)
*/
uint8_t osal_stop_timerEx( uint8_t task_id, uint16_t event_flag )
{
    osalTimerRec_t *timer;
    timer = osal_timer_find( task_id,event_flag );
    if( timer != NULL ) 
    {
        halIntState_t x;
        HAL_ENTER_CRITICAL_SECTION(x);
        timer->timeout       = 0;
        timer->reloadTimeout = 0;
        HAL_EXIT_CRITICAL_SECTION(x);
        return OSAL_SUCCESS;
    }
    return TIMER_NOT_REGISTER;
}
/*!
    @brief      获取定时器超时时间
    @param      task_id：要查询的任务ID
    @param      event_flag：要查询的事件标志
    @return     超时时间(ms)，定时器不存在或未运行超时间为0
    @note       距离定时器超时触发的时间(ms)
*/
uint16_t osal_get_timeoutEx( uint8_t task_id, uint16_t event_flag )
{
    osalTimerRec_t *timer;
    timer = osal_timer_find( task_id, event_flag );
    if( timer != NULL ) 
    {
        return timer->timeout;
    }
    return 0;
}
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
