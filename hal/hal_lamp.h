/********************************************************************************
  * @file    hal_lamp.h 
  * @author  zhaocc
  * @version V1.0.0
  * @date    2018.12.7
  * @brief   ���ļ�Ϊϵͳ����������Ͷ���ͺ�������
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
/** @addtogroup ������
  * @{
  */
/** @addtogroup ָʾ������
  * @{
  */
/** @addtogroup ָʾ�Ƽ������ú궨��
  * @{
  */	
#define HAL_LAMP_HOLD 0xFFFF
#define HAL_LAMP_OPEN(TIME) TIME,(TIME == HAL_LAMP_HOLD)?0x0000:HAL_LAMP_HOLD
#define HAL_LAMP_CLOSE(TIME) (TIME == HAL_LAMP_HOLD)?0x0000:HAL_LAMP_HOLD,TIME
	
/** 
  * @brief  ָʾ��״̬�洢�ṹ�塢
  */
typedef  struct {
    const bsp_lamp_id_t lamp;            ///< ָʾ��
    uint16_t   time;            ///< �趨ʱ�䣺����״̬
    uint16_t   reloadTime;      ///< �趨ʱ�䣺�Ǵ���״̬
    uint16_t   count_time;      ///< ����ʱʣ��ʱ�䣺����״̬
    uint16_t   count_reloadTime;///< ����ʱʣ��ʱ�䣺�Ǵ���״̬
}hal_lamp_t;
extern hal_lamp_t hal_all_lamp[];

/** 
    @brief ָʾ�ƴ���״̬����
    @param lamp_number:�ο� @ref ָʾ������
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

    1 or 2 or 3  : ���� 
    4 or 7 or 9  : ����
    5            : ����timeʱ�䣬Ϩ��reloadTime
    6            : ����timeʱ�䣬����
    8            : Ϩ��reloadTimeʱ�䣬����
    @endverbatim
    ͬʱ�ɲο� @ref ָʾ�Ƽ������ú궨��ʹ��ʾ��
    @verbatim
    hal_lamp_set(xxx,HAL_LAMP_OPEN(HAL_LAMP_HOLD));//����
    hal_lamp_set(xxx,HAL_LAMP_CLOSE(HAL_LAMP_HOLD));//����
    hal_lamp_set(xxx,HAL_LAMP_OPEN(1000));//��һ�볤��
    hal_lamp_set(xxx,HAL_LAMP_CLOSE(2000));//�����볤��
    hal_lamp_set(xxx,HAL_LAMP_CYCLE(4000,25));//����4�룬ռ�ձ�25%��˸
    @endverbatim
    
    @return     ��
    @warning    ��ʱ���60��
 */
extern void hal_lamp_set(bsp_port_id hal_lamp_amount,uint16_t time,uint16_t reloadtime);
/** 
  * @brief  ����HAL�㴢��LAMPָʾ��״̬�����飨bsp��ʵ�֣
  * @note 	���޶�̬�ڴ���䣬������Ҫ��bsp�������ڴ�
  */
extern hal_lamp_t hal_all_lamp[];
/** 
  * @brief  ���ڱ��洢��LAMPָʾ��״̬����ĳ��ȣ�bsp��ʵ�֣
  */
extern const uint8_t hal_lamp_amount;
extern void hal_lamp_loop(uint16_t PastTime);
extern void bsp_set_lamp( bsp_lamp_id_t lamp, uint8_t value );
 #ifdef __cplusplus
 }
 #endif
#endif

