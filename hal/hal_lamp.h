/********************************************************************************
  * @file    hal_lamp.h 
  * @author  zhaocc
  * @version V1.0.0
  * @date    2018.12.7
  * @brief   该文件为系统层的数据类型定义和函数声明
  ******************************************************************************
  * @attention
  *
  * 
  ******************************************************************************
  */ 
#ifndef HAL_LAMP_H
#define HAL_LAMP_H
#include "bsp.h"
#include "bsp_lamp.h"
#include "mcu_typedef.h"
#ifdef __cplusplus
extern "C"
{
 #endif
/** @addtogroup 驱动层
  * @{
  */
/** @addtogroup 指示灯驱动
  * @{
  */
/** @addtogroup 指示灯简易设置宏定义
  * @{
  */	
#define HAL_LAMP_HOLD 0xFFFF
#define HAL_LAMP_OPEN(TIME) TIME,(TIME == HAL_LAMP_HOLD)?0x0000:HAL_LAMP_HOLD
#define HAL_LAMP_CLOSE(TIME) (TIME == HAL_LAMP_HOLD)?0x0000:HAL_LAMP_HOLD,TIME
	
/** 
  * @brief  指示灯状态存储结构体、
  */
typedef  struct {
    const bsp_lamp_id_t lamp;            ///< 指示灯
    uint16_t   time;            ///< 设定时间：触发状态
    uint16_t   reloadTime;      ///< 设定时间：非触发状态
    uint16_t   count_time;      ///< 倒计时剩余时间：触发状态
    uint16_t   count_reloadTime;///< 倒计时剩余时间：非触发状态
}hal_lamp_t;
extern hal_lamp_t hal_all_lamp[];

/** 
    @brief 指示灯触发状态设置
    @param lamp_number:参考 @ref 指示灯名称
    @param time,reloadTime:
    @verbatim
    +------------------------------------------+
    |             |       reloadTime           |
    | state table +------+-----------+---------+
    |             | ==0  |>0&&<0xFFFF| ==0xFFFF|
    +-------------+------+-----------+---------+
    |t |   ==0    |  1   |     2     |   3     |
    |i +----------+------+-----------+---------+
    |m |0&&<0xFFFF|  6   |     5     |   6     |
    |e +----------+------+-----------+---------+
    |  |==0xFFFF  |  7   |     8     |   9     |
    +-------------+------+-----------+---------+ 

    1 or 2 or 3  : 长灭 
    4 or 7 or 9  : 长亮
    5            : 点亮time时间，熄灭reloadTime
    6            : 点亮time时间，长灭
    8            : 熄灭reloadTime时间，长亮
    @endverbatim
    同时可参考 @ref 指示灯简易设置宏定义使用示例
    @verbatim
    hal_lamp_set(xxx,HAL_LAMP_OPEN(HAL_LAMP_HOLD));//长亮
    hal_lamp_set(xxx,HAL_LAMP_CLOSE(HAL_LAMP_HOLD));//长灭
    hal_lamp_set(xxx,HAL_LAMP_OPEN(1000));//亮一秒长灭
    hal_lamp_set(xxx,HAL_LAMP_CLOSE(2000));//灭两秒长亮
    hal_lamp_set(xxx,HAL_LAMP_CYCLE(4000,25));//周期4秒，占空比25%闪烁
    @endverbatim
    
    @return     无
    @warning    定时最大60秒
 */
extern void hal_lamp_set(bsp_port_id hal_lamp_amount,uint16_t time,uint16_t reloadtime);
/** 
  * @brief  用于HAL层储存LAMP指示灯状态的数组（bsp层实现�
  * @note 	因无动态内存分配，所以需要在bsp层申请内存
  */
extern hal_lamp_t hal_all_lamp[];
/** 
  * @brief  用于保存储存LAMP指示灯状态数组的长度（bsp层实现�
  */
extern const uint8_t hal_lamp_amount;
extern void hal_lamp_loop(uint16_t PastTime);
extern void bsp_set_lamp( bsp_lamp_id_t lamp, uint8_t value );
 #ifdef __cplusplus
 }
 #endif
#endif

