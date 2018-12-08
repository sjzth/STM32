/********************************************************************************
  * @file    hal_lamp.c 
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
#include "hal_lamp.h"
#include "mcu_typedef.h"
void hal_lamp_loop(uint16_t PastTime)
{
    uint8_t i;
	  if(PastTime)
		{
		   for(i = 0;i < hal_lamp_amount; i++)
			{
          uint8_t lamp_on_off = 0;
				  if(hal_all_lamp[i].time == 0)
					{
						  lamp_on_off = BSP_LAMP_OFF;
					}
					else if(hal_all_lamp[i].time != HAL_LAMP_HOLD
						      && hal_all_lamp[i].time != 0
					        && hal_all_lamp[i].reloadTime != HAL_LAMP_HOLD
					        && hal_all_lamp[i].reloadTime != 0)
					{//周期
					   if(hal_all_lamp[i].count_time < hal_all_lamp[i].time)	
						 {
						    hal_all_lamp[i].count_time += PastTime;
							  lamp_on_off = BSP_LAMP_ON;
						 }							 
					   else if(hal_all_lamp[i].count_reloadTime < hal_all_lamp[i].reloadTime)
						 {
						     hal_all_lamp[i].count_reloadTime += PastTime;
							   lamp_on_off = BSP_LAMP_OFF;
						 }
						 else
						 {
						     hal_all_lamp[i].count_time = PastTime;
							   hal_all_lamp[i].count_reloadTime = 0;
						 }
					}
					else if(hal_all_lamp[i].time != HAL_LAMP_HOLD
						      && hal_all_lamp[i].time != 0
					        && hal_all_lamp[i].reloadTime == HAL_LAMP_HOLD)
					{//亮后灭
					   if(hal_all_lamp[i].count_time < hal_all_lamp[i].time)	
						 {
						    hal_all_lamp[i].count_time += PastTime;
							  lamp_on_off = BSP_LAMP_ON;
						 }							 
						 else
						 {
						    lamp_on_off = BSP_LAMP_OFF;
						 }
					}
					else if(hal_all_lamp[i].time == HAL_LAMP_HOLD
						      && hal_all_lamp[i].reloadTime != 0
					        && hal_all_lamp[i].reloadTime != HAL_LAMP_HOLD)
					{//灭后亮
					   if(hal_all_lamp[i].count_reloadTime < hal_all_lamp[i].reloadTime)	
						 {
						    hal_all_lamp[i].count_reloadTime += PastTime;
							  lamp_on_off = BSP_LAMP_OFF;
						 }							 
						 else
						 {
						    lamp_on_off = BSP_LAMP_ON;
						 }
					}
					else//长亮
					{
					   lamp_on_off = BSP_LAMP_ON;
					}
					bsp_set_lamp(hal_all_lamp[i].lamp,lamp_on_off);
			}			
		}
}
void hal_lamp_set(bsp_port_id hal_lamp_amount,uint16_t time,uint16_t reloadTime)
{
	 uint8_t i=0; 
	 if(time > 60000 && time != HAL_LAMP_HOLD) time = 60000;
	 if(reloadTime > 60000 && reloadTime != HAL_LAMP_HOLD) reloadTime = 60000;
	 for(i=0;i<hal_lamp_amount;i++)
	 {
	    if(hal_all_lamp[i].lamp == hal_lamp_amount)
			{
			   hal_all_lamp[i].time=time;
				 hal_all_lamp[i].reloadTime = reloadTime;
				
				 if(hal_all_lamp[i].time != HAL_LAMP_HOLD
					    &&hal_all_lamp[i].time != 0
				      &&hal_all_lamp[i].reloadTime == HAL_LAMP_HOLD)
				   {
				       hal_all_lamp[i].count_time = 0;
				   }
				 if(hal_all_lamp[i].time != HAL_LAMP_HOLD
					     &&hal_all_lamp[i].reloadTime != 0
				       &&hal_all_lamp[i].reloadTime != HAL_LAMP_HOLD)
				   {
				       hal_all_lamp[i].count_reloadTime = 0;
				   }
					break;
			}
			
	 }
}

