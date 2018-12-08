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


#include "osal.h"
#include "hal.h"
#include "mcu_port.h"
#include "stm32f10x.h"
	
static __IO uint32_t TimingDelay;

/* Private function prototypes -----------------------------------------------*/
void Delay(__IO uint32_t nTime);

/*!
    @brief      ��ʼ��ϵͳ����
    @param      ��
    @return     ��
    @note       ˳����������������������ʼ��
*/
void osal_init_system(void)
{
//    uint8_t idx = 0;
    hal_init();
//    do {
//        (tasksArr[idx])(idx,0x0000);
//    } while (++idx < tasksCnt);
//    hal_enable_interrupts();
}
/*!
    @brief      ����ϵͳ
    @param      ��
    @return     ��
    @note       
*/
void osal_run_system(void)
{
   Delay(500);
	 STM_SET_LEDOn(Lamp1);
	 Delay(500);
	 STM_EVAL_LEDOff(Lamp1);

}
void Delay(__IO uint32_t nTime)
{ 
  TimingDelay = nTime;

  while(TimingDelay != 0);
}
/**
  * @brief  Decrements the TimingDelay variable.
  * @param  None
  * @retval None
  */
void TimingDelay_Decrement(void)
{
  if (TimingDelay != 0x00)
  { 
    TimingDelay--;
  }
}
/*!
    @brief      stm32f1x3������
    @param      ��
    @return     int:��׼��������
    @note       ����ϵͳ�� 
*/
void osal_start_system(void)
{
    osal_init_system();
    for(;;){
		   osal_run_system();	  
		}
}
