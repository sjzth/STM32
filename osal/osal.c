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
    @brief      ��ʼ��ϵͳ����
    @param      ��
    @return     ��
    @note       ˳����������������������ʼ��
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
    @brief      ����ϵͳ
    @param      ��
    @return     ��
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
        HAL_ENTER_CRITICAL_SECTION(x);  //�����ٽ���
        events = tasksEvents[idx];      //���������¼�
        tasksEvents[idx] = 0;           //�¼����
        HAL_EXIT_CRITICAL_SECTION(x);   //�˳��ٽ���
			
			  activeTaskID = idx;             //���浱ǰ��������ID
        events = (tasksArr[idx])(idx, events); //���������¼�������
        activeTaskID = TASK_NO_TASK;    //��յ�ǰ��������ID

        HAL_ENTER_CRITICAL_SECTION(x);  //�����ٽ���
        tasksEvents[idx] |= events;     //��δ��������¼����·Ż�
        HAL_EXIT_CRITICAL_SECTION(x);   //�˳��ٽ���
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
