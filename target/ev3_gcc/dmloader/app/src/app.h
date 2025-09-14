/*
 *  TOPPERS/ASP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Advanced Standard Profile Kernel
 *
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2004-2010 by Embedded and Real-Time Systems Laboratory
 *              Graduate School of Information Science, Nagoya Univ., JAPAN
 *
 *  上記著作権者は，以下の(1)〜(4)の条件を満たす場合に限り，本ソフトウェ
 *  ア（本ソフトウェアを改変したものを含む．以下同じ）を使用・複製・改
 *  変・再配布（以下，利用と呼ぶ）することを無償で許諾する．
 *  (1) 本ソフトウェアをソースコードの形で利用する場合には，上記の著作
 *      権表示，この利用条件および下記の無保証規定が，そのままの形でソー
 *      スコード中に含まれていること．
 *  (2) 本ソフトウェアを，ライブラリ形式など，他のソフトウェア開発に使
 *      用できる形で再配布する場合には，再配布に伴うドキュメント（利用
 *      者マニュアルなど）に，上記の著作権表示，この利用条件および下記
 *      の無保証規定を掲載すること．
 *  (3) 本ソフトウェアを，機器に組み込むなど，他のソフトウェア開発に使
 *      用できない形で再配布する場合には，次のいずれかの条件を満たすこ
 *      と．
 *    (a) 再配布に伴うドキュメント（利用者マニュアルなど）に，上記の著
 *        作権表示，この利用条件および下記の無保証規定を掲載すること．
 *    (b) 再配布の形態を，別に定める方法によって，TOPPERSプロジェクトに
 *        報告すること．
 *  (4) 本ソフトウェアの利用により直接的または間接的に生じるいかなる損
 *      害からも，上記著作権者およびTOPPERSプロジェクトを免責すること．
 *      また，本ソフトウェアのユーザまたはエンドユーザからのいかなる理
 *      由に基づく請求からも，上記著作権者およびTOPPERSプロジェクトを
 *      免責すること．
 * 
 *  本ソフトウェアは，無保証で提供されているものである．上記著作権者お
 *  よびTOPPERSプロジェクトは，本ソフトウェアに関して，特定の使用目的
 *  に対する適合性も含めて，いかなる保証も行わない．また，本ソフトウェ
 *  アの利用により直接的または間接的に生じたいかなる損害に関しても，そ
 *  の責任を負わない．
 *
 *  The above copyright holders grant permission to use, copy, modify, and redistribute
 *  (hereinafter referred to as "use") this software (including modified versions of this software; 
 *  the same applies hereinafter) free of charge, provided that the following conditions (1) through (4) are met:
 *  (1) If you use this software in source code form, the above copyright notice, these terms of use,
 *      and the disclaimer below must be included in the source code in their entirety.
 *  (2) If you redistribute this software in a form that can be used for the development of other
 *      software, such as in a library format, you must include the above copyright notice, these terms of
 *      use, and the disclaimer below in the documentation (such as the user manual) accompanying the
 *      distribution.
 *  (3) If you redistribute this software in a form that cannot be used for the development of other
 *      software, such as by incorporating it into a device, you must meet one of the following conditions:
 *    (a) You must include the above copyright notice, these terms of use, and the following
 *        disclaimer of warranty in any documentation accompanying the redistribution (such as the user
 *        manual).
 *    (b) You must report the form of redistribution to the TOPPERS Project in a manner specified
 *        separately.
 *  (4) You indemnify the above copyright holders and the TOPPERS Project from any damages arising
 *      directly or indirectly from the use of this software.
 *      You also indemnify the above copyright holders and the TOPPERS Project from any claims based on
 *      any reason whatsoever by users or end users of this software.
 * 
 *  This software is provided without warranty. The above copyright holders and the TOPPERS Project
 *  make no warranties regarding this software, including its suitability for a particular purpose.
 *  Furthermore, they are not liable for any damages arising directly or indirectly from the use of this
 *  software.
 *
 *  $Id: sample1.h 2416 2012-09-07 08:06:20Z ertl-hiro $
 */

/*
 *		Header file for sample program (1)
 */

/*
 *  Target Dependency Definitions
 */
#include "target_test.h"

/*
 *  Define the priority of each task
 */

#define MAIN_PRIORITY	5		/* Main task priority */
								/* Must be higher than HIGH_PRIORITY */

#define HIGH_PRIORITY	9		/* Priority of concurrently executed tasks */
#define MID_PRIORITY	10
#define LOW_PRIORITY	11

/*
 *  Defining constants that may be target dependent
 */

#ifndef STACK_SIZE
#define	STACK_SIZE		4096		/* Task stack size */
#endif /* STACK_SIZE */

#ifndef LOOP_REF
#define LOOP_REF		ULONG_C(1000000)	/* Number of loops for speed measurement */
#endif /* LOOP_REF */

/*
 *  Function prototype declaration
 */
#ifndef TOPPERS_MACRO_ONLY

extern void	task(intptr_t exinf);
extern void	main_task(intptr_t exinf);
extern void balance_task(intptr_t exinf);
extern void idle_task(intptr_t exinf);
//extern void	tex_routine(TEXPTN texptn, intptr_t exinf);
//#ifdef CPUEXC1
//extern void	cpuexc_handler(void *p_excinf);
//#endif /* CPUEXC1 */
//extern void	cyclic_handler(intptr_t exinf);
//extern void	alarm_handler(intptr_t exinf);
//
//extern void	gpio_handler_initialize(intptr_t exinf);
//extern void	gpio_handler(void);
extern void	gpio_irq_dispatcher(intptr_t exinf);
//
//extern void	uart_sensor_monitor(intptr_t exinf);
//
//extern void	ev3_uart_cyclic_handler(intptr_t exinf);
//extern void	ev3_uart_daemon(intptr_t exinf);
//extern void	ev3_uart_port2_irq(void);
//
//extern void initialize_ev3(intptr_t exinf);
#endif /* TOPPERS_MACRO_ONLY */
