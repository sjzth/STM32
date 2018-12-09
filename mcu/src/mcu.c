/*!
  ******************************************************************************
  * @file    mcu.c
  * @author  zhaocc
  * @version V1.0.0
  * @date    2018.12.07
  * @brief   
  ******************************************************************************
	* @attention
  *
  **/
#include "bsp_lamp.h"
#include "hal.h"
#include "mcu.h"
#include "mcu_typedef.h"

static uint32_t sysGetPastTime=0;
static uint32_t loopPastTime=0;
/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
   sysGetPastTime++;
	 loopPastTime++;
}
/*!
    @brief      MCU循环函数
    @param      无
    @return     距离上次进入所流逝时间
*/
uint32_t hal_mcu_loop(void)
{
    uint32_t PastTime;
    //IWDG_ReloadCounter();
    HAL_CRITICAL_STATEMENT(PastTime = loopPastTime;loopPastTime = 0;);
    return PastTime;
}
/*!
    @brief      获取流逝时间函数（瓜低呈褂茫
    @param      无
    @return     距离上次进入所流逝的时间
*/
uint32_t hal_get_elapsed_msec(void)
{
    uint32_t returnTime;
    HAL_CRITICAL_STATEMENT(returnTime = sysGetPastTime;sysGetPastTime = 0;);
    return returnTime;
}
void bsp_button_init(void)
{
	
}

void hal_mcu_init(void)
{
  if (SysTick_Config(48000))
  { 
    /* Capture error */ 
    while (1);
  } 
}
