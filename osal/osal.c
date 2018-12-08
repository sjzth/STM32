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
    @brief      初始化系统任务
    @param      无
    @return     无
    @note       顺序调用任务处理函数进行任务初始化
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
    @brief      运行系统
    @param      无
    @return     无
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
