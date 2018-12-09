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
    @brief      Ìí¼Ó¶¨Ê±Æ÷
    @param      timer£ºÒªÁ´ÈëµÄ¶¨Ê±Æ÷µØÖ·
    @return     ÎÞ
    @note       ½«¶¨Ê±Æ÷Á´ÈëÁ´±íÖÐ£¬ÎÄ¼þÄÚ²¿Ê¹ÓÃº¯Êý£¬²»Ìá¹¸øÍâ²¿Ê¹ÓÃ
*/
static void osal_timer_add( osalTimerRec_t *timer )
{
    osalTimerRec_t *tmp;
    osalTimerRec_t *over;
    //²éÕÒÊÇ·ñÒÑ´æÔÚ
    for( over = NULL, tmp = timerHead; tmp != NULL; over = tmp, tmp = tmp->next )
    {
        if( timer == tmp )
        {
            break;
        }
    }//Ã»ÓÐÕÒµ½,Ìí¼Óµ½Î²²¿
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
    @brief      ²éÕÒ¶¨Ê±Æ÷
    @param      task_id£º¶¨Ê±Æ÷Òª×¢²áµÄÈÎÎñID
    @param      event_flag£º¶¨Ê±Æ÷Òª×¢²áµÄÊÂ¼þ±êÖ¾
    @return     ¶¨Ê±Æ÷µØÖ·£¬ÈôÕÒ²»µ½ÔòÎªNULL
    @note       Ê¹ÓÃÈÎÎñÊÂ¼þÀ´²éÕÒ¶¨Ê±Æ÷µØÖ·£¬ÎÄ¼þÄÚ²¿Ê¹ÓÃº¯Êý£¬²»Ìá¹¸øÍâ²¿Ê¹ÓÃ
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
    @brief      ³õÊ¼»¯¶¨Ê±Æ÷
    @param      ÎÞ
    @return     ÎÞ
*/
void osal_timer_init( void )
{
    osal_systemClock = 0;
}
/*!
    @brief      ×¢²áÈÎÎñÊÂ¼þ¶¨Ê±Æ÷
    @param      *timer£ºÒª×¢²áµ½ÈÎÎñÊÂ¼þÉÏ¶¨Ê±Æ÷µÄµØÖ·
    @param      task_id£º¶¨Ê±Æ÷Òª×¢²áµÄÈÎÎñID
    @param      event_flag£º¶¨Ê±Æ÷Òª×¢²áµÄÊÂ¼þ±êÖ¾
    @return     ÎÞ
    @note       ¸ÃÏµÍ³ÎÞÄÚ´æ·ÖÅä¹¦ÄÜ£¬ÐèÒª×ÔÐÐ¶¨Òå±äÁ¿ÔÙ×¢²áµ½ÈÎÎñÊÂ¼þÖÐ²Å¿ÉÔËÐÐ¶¨Ê±¹¦ÄÜ
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
    @brief      Æô¶¯ÊÂ¼þ´¥·¢¶¨Ê±Æ÷
    @param      task_id£ºÒªÆô¶¯¶¨Ê±Æ÷µÄÈÎÎñID
    @param      event_flag£ºÒªÆô¶¯¶¨Ê±Æ÷µÄÊÂ¼þ±êÖ¾
    @param      timeout_value£º¶¨Ê±Æ÷´¥·¢Ê±¼ä(ms)£¬×î´óÖµ60000
    @return     OSAL_SUCCESS´ú±í³É¹¦ÉèÖÃ¸Ã¶¨Ê±Æ÷£»TIMER_NOT_REGISTER´ú±íÕÒ²»µ½Õâ¸ö¶¨Ê±Æ÷£»²Î¿¼ @ref Í¨ÓÃ×´Ì¬·µ»ØÖµ 
    @note       ¾­¹ý´¥·¢Ê±¼äºóÖÃÆðÈÎÎñÊÂ¼þ±êÖ¾Î»£¬½öÒ»´Î
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
    @brief      Æô¶¯ÊÂ¼þÑ­»·´¥·¢¶¨Ê±Æ÷
    @param      task_id£ºÒªÆô¶¯¶¨Ê±Æ÷µÄÈÎÎñID
    @param      event_flag£ºÒªÆô¶¯¶¨Ê±Æ÷µÄÊÂ¼þ±êÖ¾
    @param      timeout_value£º¶¨Ê±Æ÷Ñ­»·ÖÜÆÚÊ±¼ä(ms)£¬×î´óÖµ60000
    @return     OSAL_SUCCESS´ú±í³É¹¦ÉèÖÃ¸Ã¶¨Ê±Æ÷£»TIMER_NOT_REGISTER´ú±íÕÒ²»µ½Õâ¸ö¶¨Ê±Æ÷£»²Î¿¼ @ref Í¨ÓÃ×´Ì¬·µ»ØÖµ 
    @note       Î´Í£Ö¹Ç°½«ÖÜÆÚÐÔÖÃÆðÈÎÎñÊÂ¼þ±êÖ¾Î»
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
    @brief      Í£Ö¹¶¨Ê±Æ÷
    @param      task_id£ºÒªÍ£Ö¹¶¨Ê±Æ÷µÄÈÎÎñID
    @param      event_flag£ºÒªÍ£Ö¹¶¨Ê±Æ÷µÄÊÂ¼þ±êÖ¾
    @return     OSAL_SUCCESS´ú±íÓÐÕâ¸ö¶¨Ê±Æ÷£»TIMER_NOT_REGISTER´ú±íÕÒ²»µ½Õâ¸ö¶¨Ê±Æ÷£»²Î¿¼ @ref Í¨ÓÃ×´Ì¬·µ»ØÖµ 
    @note       ¾àÀë¶¨Ê±Æ÷³¬Ê±´¥·¢µÄÊ±¼ä(ms)
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
    @brief      »ñÈ¡¶¨Ê±Æ÷³¬Ê±Ê±¼ä
    @param      task_id£ºÒª²éÑ¯µÄÈÎÎñID
    @param      event_flag£ºÒª²éÑ¯µÄÊÂ¼þ±êÖ¾
    @return     ³¬Ê±Ê±¼ä(ms)£¬¶¨Ê±Æ÷²»´æÔÚ»òÎ´ÔËÐÐ³¬Ê±¼äÎª0
    @note       ¾àÀë¶¨Ê±Æ÷³¬Ê±´¥·¢µÄÊ±¼ä(ms)
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
        //Ñ­»·±éÀú
        for( timer = timerHead; timer != NULL; timer = timer->next )
        {//ÊÇ·ñÕýÔÚ¼ÆÊ±
            if( timer->timeout != 0 )
            {
                //ÊÇ·ñ³¬Ê±
                HAL_ENTER_CRITICAL_SECTION(x);
                if( timer->timeout <= elapsedMSec )//³¬Ê±
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
