/*
 *  TOPPERS/HRP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      High Reliable system Profile Kernel
 * 
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2004-2018 by Embedded and Real-Time Systems Laboratory
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
 *  $Id: t_syslog.h 415 2018-07-27 09:06:40Z ertl-hiro $
 */

/*
 *      Definition for system log output
 *
 *  The system log service is a service for outputting system log information.
 *  It is also used to output log information from the kernel, so it never 
 *  enters a waiting state internally.
 *
 *  Log information is written to the kernel log buffer or output using 
 *  low-level character output functions.
 *  The method of use can be switched using an extended service call.
 *
 *  If the log buffer area overflows, old log information is erased and 
 *  overwritten.
 *
 *  When including this file from an assembly language source file, you can 
 *  exclude all code other than macro definitions by defining TOPPERS_MACRO_ONLY.
 */

#ifndef TOPPERS_T_SYSLOG_H
#define TOPPERS_T_SYSLOG_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef TOPPERS_OMIT_TECS
#include <t_stddef.h>
#else /* TOPPERS_OMIT_TECS */
#include <kernel.h>
#include <extsvc_fncode.h>
#endif /* TOPPERS_OMIT_TECS */

#ifndef TOPPERS_MACRO_ONLY
#include <stdarg.h>
#endif /* TOPPERS_MACRO_ONLY */

/*
 *  Definition of log information types
 */
#define LOG_TYPE_COMMENT	UINT_C(0x01)	/* Comment */
#define LOG_TYPE_ASSERT		UINT_C(0x02)	/* Assertion failure */

#define LOG_TYPE_INH		UINT_C(0x11)	/* Interrupt handler */
#define LOG_TYPE_ISR		UINT_C(0x12)	/* Interrupt service routine */
#define LOG_TYPE_CYC		UINT_C(0x13)	/* Cyclic handler */
#define LOG_TYPE_ALM		UINT_C(0x14)	/* Alarm handler */
#define LOG_TYPE_OVR		UINT_C(0x15)	/* Overrun handler */
#define LOG_TYPE_EXC		UINT_C(0x16)	/* CPU exception handler */
#define LOG_TYPE_TSKSTAT	UINT_C(0x21)	/* Task state change */
#define LOG_TYPE_DSP		UINT_C(0x31)	/* Dispatcher */
#define LOG_TYPE_SVC		UINT_C(0x41)	/* Service call */

#define LOG_ENTER			UINT_C(0x00)	/* Entry/start */
#define LOG_LEAVE			UINT_C(0x80)	/* Exit/end */

/*
 *  Defining the importance of log information
 */
#define LOG_EMERG			UINT_C(0)		/* Shutdown-worthy errors */
#define LOG_ALERT			UINT_C(1)
#define LOG_CRIT			UINT_C(2)
#define LOG_ERROR			UINT_C(3)		/* System Error */
#define LOG_WARNING			UINT_C(4)		/* Warning message */
#define LOG_NOTICE			UINT_C(5)
#define LOG_INFO			UINT_C(6)
#define LOG_DEBUG			UINT_C(7)		/* Debugging messages */

#ifndef TOPPERS_MACRO_ONLY

/*
 *  Log information data structure
 */

#ifndef LOGTIM
#define LOGTIM		HRTCNT			/* Log time data type */
#endif /* LOGTIM */

#define TNUM_LOGPAR		6			/* Number of log parameters */

#ifndef LOGPAR
#define LOGPAR		intptr_t		/* Log parameter data type */
#define ULOGPAR		uintptr_t
#endif /* LOGPAR */

typedef struct {
	uint_t	logtype;				/* Log information type */
	LOGTIM	logtim;					/* Log Time */
	LOGPAR	logpar[TNUM_LOGPAR];	/* Log parameters */
} SYSLOG;

/*
 *  Output of log information
 *
 *  When TOPPERS_SVC_CALL is not defined, log information is output via
 *  the system log function adapter. When it is defined, the system log function
 *  described in TECS is called directly.
 *
 *  When calling via the adapter, an error may be returned.
 *  If an error is returned, TOPPERS_assert_abort is called (unless NDEBUG is defined).
 *  When calling directly, there is no possibility of an error being returned.
 */
#ifndef TOPPERS_SVC_CALL

#ifndef TOPPERS_OMIT_TECS

extern ER	syslog_wri_log(uint_t prio, const SYSLOG *p_syslog) throw();

#else /* TOPPERS_OMIT_TECS */

Inline ER
syslog_wri_log(uint_t prio, const SYSLOG *p_syslog)
{
	return((ER) cal_svc(TFN_SYSLOG_WRI_LOG, (intptr_t) prio,
										(intptr_t) p_syslog, 0, 0, 0));
}

#endif /* TOPPERS_OMIT_TECS */

#ifndef NDEBUG
#define syslog_write(prio, p_syslog) \
						((void)(syslog_wri_log(prio, p_syslog) >= 0 \
										? 0 : (TOPPERS_assert_abort(), 0)))
#else /* NDEBUG */
#define syslog_write(prio, p_syslog) \
						((void) syslog_wri_log(prio, p_syslog))
#endif /* NDEBUG */

#else /* TOPPERS_SVC_CALL */

#ifndef TOPPERS_OMIT_TECS

extern ER	tSysLog_eSysLog_write(uint_t priority,
									const SYSLOG *p_syslog) throw();
#define syslog_write(prio, p_syslog) \
						((void) tSysLog_eSysLog_write(prio, p_syslog))

#else /* TOPPERS_OMIT_TECS */

extern ER	_syslog_wri_log(uint_t prio, const SYSLOG *p_syslog) throw();

#define syslog_write(prio, p_syslog) \
						((void) _syslog_wri_log(prio, p_syslog))

#endif /* TOPPERS_OMIT_TECS */

#endif /* TOPPERS_SVC_CALL */

#ifndef TOPPERS_OMIT_SYSLOG
/*
 *  Low-level library functions for system logging
 */

Inline void
t_syslog_0(uint_t prio, uint_t type)
{
	SYSLOG	logbuf;

	logbuf.logtype = type;
	syslog_write(prio, &logbuf);
}

Inline void
t_syslog_1(uint_t prio, uint_t type, LOGPAR arg1)
{
	SYSLOG	logbuf;

	logbuf.logtype = type;
	logbuf.logpar[0] = arg1;
	syslog_write(prio, &logbuf);
}

Inline void
t_syslog_2(uint_t prio, uint_t type, LOGPAR arg1, LOGPAR arg2)
{
	SYSLOG	logbuf;

	logbuf.logtype = type;
	logbuf.logpar[0] = arg1;
	logbuf.logpar[1] = arg2;
	syslog_write(prio, &logbuf);
}

Inline void
t_syslog_3(uint_t prio, uint_t type, LOGPAR arg1, LOGPAR arg2, LOGPAR arg3)
{
	SYSLOG	logbuf;

	logbuf.logtype = type;
	logbuf.logpar[0] = arg1;
	logbuf.logpar[1] = arg2;
	logbuf.logpar[2] = arg3;
	syslog_write(prio, &logbuf);
}

Inline void
t_syslog_4(uint_t prio, uint_t type, LOGPAR arg1, LOGPAR arg2,
											LOGPAR arg3, LOGPAR arg4)
{
	SYSLOG	logbuf;

	logbuf.logtype = type;
	logbuf.logpar[0] = arg1;
	logbuf.logpar[1] = arg2;
	logbuf.logpar[2] = arg3;
	logbuf.logpar[3] = arg4;
	syslog_write(prio, &logbuf);
}

Inline void
t_syslog_5(uint_t prio, uint_t type, LOGPAR arg1, LOGPAR arg2,
								LOGPAR arg3, LOGPAR arg4, LOGPAR arg5)
{
	SYSLOG	logbuf;

	logbuf.logtype = type;
	logbuf.logpar[0] = arg1;
	logbuf.logpar[1] = arg2;
	logbuf.logpar[2] = arg3;
	logbuf.logpar[3] = arg4;
	logbuf.logpar[4] = arg5;
	syslog_write(prio, &logbuf);
}

Inline void
t_syslog_6(uint_t prio, uint_t type, LOGPAR arg1, LOGPAR arg2,
					LOGPAR arg3, LOGPAR arg4, LOGPAR arg5, LOGPAR arg6)
{
	SYSLOG	logbuf;

	logbuf.logtype = type;
	logbuf.logpar[0] = arg1;
	logbuf.logpar[1] = arg2;
	logbuf.logpar[2] = arg3;
	logbuf.logpar[3] = arg4;
	logbuf.logpar[4] = arg5;
	logbuf.logpar[5] = arg6;
	syslog_write(prio, &logbuf);
}

/*
 *  Library function for outputting log information (comments) (vasyslog.c)
 */
extern void	tt_syslog(SYSLOG *p_logbuf, const char *format, va_list ap);

Inline void
syslog(uint_t prio, const char *format, ...)
{
	va_list	ap;
	SYSLOG	logbuf;

	va_start(ap, format);
	tt_syslog(&logbuf, format, ap);
	va_end(ap);
	syslog_write(prio, &logbuf);
}

/*
 *  Library function for outputting error messages (t_perror.c)
 */
extern void	tt_perror(SYSLOG *p_logbuf, const char *file, int_t line,
		 									const char *expr, ER ercd);

Inline void
t_perror(uint_t prio, const char *file, int_t line, const char *expr, ER ercd)
{
	SYSLOG	logbuf;

	tt_perror(&logbuf, file, line, expr, ercd);
	syslog_write(prio, &logbuf);
}

#else /* TOPPERS_OMIT_SYSLOG */
/*
 *  To suppress system log output:
 */

Inline void
t_syslog_0(uint_t prio, uint_t type)
{
}

Inline void
t_syslog_1(uint_t prio, uint_t type, LOGPAR arg1)
{
}

Inline void
t_syslog_2(uint_t prio, uint_t type, LOGPAR arg1, LOGPAR arg2)
{
}

Inline void
t_syslog_3(uint_t prio, uint_t type, LOGPAR arg1, LOGPAR arg2, LOGPAR arg3)
{
}

Inline void
t_syslog_4(uint_t prio, uint_t type, LOGPAR arg1, LOGPAR arg2,
											LOGPAR arg3, LOGPAR arg4)
{
}

Inline void
t_syslog_5(uint_t prio, uint_t type, LOGPAR arg1, LOGPAR arg2,
								LOGPAR arg3, LOGPAR arg4, LOGPAR arg5)
{
}

Inline void
t_syslog_6(uint_t prio, uint_t type, LOGPAR arg1, LOGPAR arg2,
					LOGPAR arg3, LOGPAR arg4, LOGPAR arg5, LOGPAR arg6)
{
}

Inline void
syslog(uint_t prio, const char *format, ...)
{
}

Inline void
t_perror(uint_t prio, const char *file, int_t line, const char *expr, ER ercd)
{
}

#endif /* TOPPERS_OMIT_SYSLOG */

/*
 * Library function for system log output
 *
 * Macro for creating a message from the format and subsequent arguments
 * and outputting it as log information with a severity level of prio.
 * arg1 through argn are cast to the LOGPAR type, so they can be any type
 * that can be converted to the LOGPAR type.
 */

#define syslog_0(prio, format) \
				t_syslog_1(prio, LOG_TYPE_COMMENT, (LOGPAR)(format))

#define syslog_1(prio, format, arg1) \
				t_syslog_2(prio, LOG_TYPE_COMMENT, (LOGPAR)(format), \
														(LOGPAR)(arg1))

#define syslog_2(prio, format, arg1, arg2) \
				t_syslog_3(prio, LOG_TYPE_COMMENT, (LOGPAR)(format), \
										(LOGPAR)(arg1), (LOGPAR)(arg2))

#define syslog_3(prio, format, arg1, arg2, arg3) \
				t_syslog_4(prio, LOG_TYPE_COMMENT, (LOGPAR)(format), \
						(LOGPAR)(arg1), (LOGPAR)(arg2), (LOGPAR)(arg3))

#define syslog_4(prio, format, arg1, arg2, arg3, arg4) \
				t_syslog_5(prio, LOG_TYPE_COMMENT, (LOGPAR)(format), \
						(LOGPAR)(arg1), (LOGPAR)(arg2), (LOGPAR)(arg3), \
														(LOGPAR)(arg4))

#define syslog_5(prio, format, arg1, arg2, arg3, arg4, arg5) \
				t_syslog_6(prio, LOG_TYPE_COMMENT, (LOGPAR)(format), \
						(LOGPAR)(arg1), (LOGPAR)(arg2), (LOGPAR)(arg3), \
										(LOGPAR)(arg4), (LOGPAR)(arg5))

/*
 *  Macros for outputting log information (assertion failures)
 */
#ifndef TOPPERS_assert_fail
#define TOPPERS_assert_fail(exp, file, line) \
				t_syslog_3(LOG_EMERG, LOG_TYPE_ASSERT, (LOGPAR)(file), \
										(LOGPAR)(line), (LOGPAR)(exp))
#endif /* TOPPERS_assert_fail */

#endif /* TOPPERS_MACRO_ONLY */

#ifdef __cplusplus
}
#endif

#endif /* TOPPERS_T_SYSLOG_H */
