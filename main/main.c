/*!
  ******************************************************************************
  * @file    Main.c
  * @author  zhaocc
  * @version V1.0.0
  * @date    2018.12.07
  * @brief   该文件内包含标准系统启动函数
  ******************************************************************************
	* @attention
  *
  */
	#include "osal.h"
	
	/** @defgroup 主函数
  * @{
  */
/*!
    @brief      stm32f1x3主程序
    @param      无
    @return     int:标准返回类型
    @note       运行系统。 
*/
int main(void)
{
    osal_start_system();
    return 0;
}

/**
  * @}
  */ 
