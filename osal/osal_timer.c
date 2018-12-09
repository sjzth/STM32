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
    @brief      ��Ӷ�ʱ��
    @param      timer��Ҫ����Ķ�ʱ����ַ
    @return     ��
    @note       ����ʱ�����������У��ļ��ڲ�ʹ�ú��������Ṹ��ⲿʹ��
*/
static void osal_timer_add( osalTimerRec_t *timer )
{
    osalTimerRec_t *tmp;
    osalTimerRec_t *over;
    //�����Ƿ��Ѵ���
    for( over = NULL, tmp = timerHead; tmp != NULL; over = tmp, tmp = tmp->next )
    {
        if( timer == tmp )
        {
            break;
        }
    }//û���ҵ�,��ӵ�β��
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
    @brief      ���Ҷ�ʱ��
    @param      task_id����ʱ��Ҫע�������ID
    @param      event_flag����ʱ��Ҫע����¼���־
    @return     ��ʱ����ַ�����Ҳ�����ΪNULL
    @note       ʹ�������¼������Ҷ�ʱ����ַ���ļ��ڲ�ʹ�ú��������Ṹ��ⲿʹ��
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
    @brief      ��ʼ����ʱ��
    @param      ��
    @return     ��
*/
void osal_timer_init( void )
{
    osal_systemClock = 0;
}
/*!
    @brief      ע�������¼���ʱ��
    @param      *timer��Ҫע�ᵽ�����¼��϶�ʱ���ĵ�ַ
    @param      task_id����ʱ��Ҫע�������ID
    @param      event_flag����ʱ��Ҫע����¼���־
    @return     ��
    @note       ��ϵͳ���ڴ���书�ܣ���Ҫ���ж��������ע�ᵽ�����¼��вſ����ж�ʱ����
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
    @brief      �����¼�������ʱ��
    @param      task_id��Ҫ������ʱ��������ID
    @param      event_flag��Ҫ������ʱ�����¼���־
    @param      timeout_value����ʱ������ʱ��(ms)�����ֵ60000
    @return     OSAL_SUCCESS����ɹ����øö�ʱ����TIMER_NOT_REGISTER�����Ҳ��������ʱ�����ο� @ref ͨ��״̬����ֵ 
    @note       ��������ʱ������������¼���־λ����һ��
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
    @brief      �����¼�ѭ��������ʱ��
    @param      task_id��Ҫ������ʱ��������ID
    @param      event_flag��Ҫ������ʱ�����¼���־
    @param      timeout_value����ʱ��ѭ������ʱ��(ms)�����ֵ60000
    @return     OSAL_SUCCESS����ɹ����øö�ʱ����TIMER_NOT_REGISTER�����Ҳ��������ʱ�����ο� @ref ͨ��״̬����ֵ 
    @note       δֹͣǰ�����������������¼���־λ
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
    @brief      ֹͣ��ʱ��
    @param      task_id��Ҫֹͣ��ʱ��������ID
    @param      event_flag��Ҫֹͣ��ʱ�����¼���־
    @return     OSAL_SUCCESS�����������ʱ����TIMER_NOT_REGISTER�����Ҳ��������ʱ�����ο� @ref ͨ��״̬����ֵ 
    @note       ���붨ʱ����ʱ������ʱ��(ms)
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
    @brief      ��ȡ��ʱ����ʱʱ��
    @param      task_id��Ҫ��ѯ������ID
    @param      event_flag��Ҫ��ѯ���¼���־
    @return     ��ʱʱ��(ms)����ʱ�������ڻ�δ���г�ʱ��Ϊ0
    @note       ���붨ʱ����ʱ������ʱ��(ms)
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
        //ѭ������
        for( timer = timerHead; timer != NULL; timer = timer->next )
        {//�Ƿ����ڼ�ʱ
            if( timer->timeout != 0 )
            {
                //�Ƿ�ʱ
                HAL_ENTER_CRITICAL_SECTION(x);
                if( timer->timeout <= elapsedMSec )//��ʱ
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
