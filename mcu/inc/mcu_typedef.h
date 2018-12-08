/*!
  ******************************************************************************
  * @file    mcu_types.h
  * @author  zhaocc
  * @version V1.0.0
  * @date    2018.12.08
  * @brief   
  ******************************************************************************
  */
#ifndef MCU_TYPES_H
#define MCU_TYPES_H
#include "stdint.h"
#ifdef __cplusplus
extern "C"
{
#endif

#ifndef NULL
#define NULL ((void *) 0)
#endif

typedef volatile char     vint8_t ;
typedef volatile int      vint16_t;
typedef volatile long     vint32_t;


typedef volatile unsigned char vuint8_t ;
typedef volatile unsigned int  vuint16_t;
typedef volatile unsigned long vuint32_t;
/*
 *  This macro is for use by other macros to form a fully valid C statement.
 *  Without this, the if/else conditionals could show unexpected behavior.
 *
 *  For example, use...
 *    #define SET_REGS()  st( ioreg1 = 0; ioreg2 = 0; )
 *  instead of ...
 *    #define SET_REGS()  { ioreg1 = 0; ioreg2 = 0; }
 *  or
 *    #define  SET_REGS()    ioreg1 = 0; ioreg2 = 0;
 *  The last macro would not behave as expected in the if/else construct.
 *  The second to last macro will cause a compiler error in certain uses
 *  of if/else construct
 *
 *  It is not necessary, or recommended, to use this macro where there is
 *  already a valid C statement.  For example, the following is redundant...
 *    #define CALL_FUNC()   st(  func();  )
 *  This should simply be...
 *    #define CALL_FUNC()   func()
 *
 * (The while condition below evaluates false without generating a
 *  constant-controlling-loop type of warning on most compilers.)
 */
#define st(x)      do { x } while (__LINE__ == -1)


/**************************************************************************************************
 */
#ifdef __cplusplus
}
#endif

#endif
