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
/*!
    @brief      MCUѭ������
    @param      ��
    @return     �����ϴν���������ʱ��
*/
uint32_t hal_mcu_loop(void)
{
    uint32_t PastTime;
    IWDG_ReloadCounter();
    HAL_CRITICAL_STATEMENT(PastTime = loopPastTime;loopPastTime = 0;);
    return PastTime;
}
/*!
    @brief      ��ȡ����ʱ�亯�����ϵͳʹ�ã
    @param      ��
    @return     �����ϴν��������ŵ�ʱ��
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
