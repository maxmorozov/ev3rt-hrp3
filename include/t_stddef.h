/*
 *  TOPPERS Software
 *      Toyohashi Open Platform for Embedded Real-Time Systems
 * 
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2004-2015 by Embedded and Real-Time Systems Laboratory
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
 *  $Id: t_stddef.h 216 2017-07-02 18:49:06Z ertl-hiro $
 */

/*
 *		TOPPERS共通ヘッダファイル
 *
 *  TOPPERS関連のすべてのソースファイルでインクルードすべきヘッダファイ
 *  ル．各種のカーネルやソフトウェア部品で共通に用いることを想定してい
 *  る．TOPPERSの各種のカーネルやソフトウェア部品で共通に用いるデータ型，
 *  定数，マクロの定義などを含む．
 *
 *  アセンブリ言語のソースファイルからこのファイルをインクルードする時
 *  は，TOPPERS_MACRO_ONLYを定義しておく．これにより，マクロ定義以外を
 *  除くようになっている．
 */

#ifndef TOPPERS_T_STDDEF_H
#define TOPPERS_T_STDDEF_H

#ifdef __cplusplus
extern "C" {
#endif

/*
 *  ターゲット依存部
 */
#include "target_stddef.h"

/*
 *  C言語/EC++でthrow()に対処するための定義
 */
#if !defined(__cplusplus) || defined(__embedded_cplusplus)
#define throw()
#endif

#ifndef TOPPERS_MACRO_ONLY

/*
 *  ターゲット依存のデータ型のマクロのデフォルト定義
 */
#ifndef TOPPERS_bool
#define TOPPERS_bool	int				/* ブール型 */
#endif /* TOPPERS_bool */

#ifndef TOPPERS_fp
struct TOPPERS_dummy_t { int TOPPERS_dummy_field; };
typedef	void			(*TOPPERS_fp_t)(struct TOPPERS_dummy_t);
#define TOPPERS_fp		TOPPERS_fp_t	/* プログラムの起動番地 */
#endif /* TOPPERS_fp */

/*
 *  Common Data Types
 */
typedef TOPPERS_bool	bool_t;		/* Boolean value */

typedef signed int		int_t;		/* Natural-size signed integer */
typedef unsigned int	uint_t;		/* Natural-size unsigned integer */

typedef signed long		long_t;		/* Long-size signed integer */
typedef unsigned long	ulong_t;	/* Long-size unsigned integer */

typedef int_t			FN;			/* Function code */
typedef	int_t			ER;			/* Error code */
typedef	int_t			ID;			/* Object ID number */
typedef	uint_t			ATR;		/* Object attribute */
typedef	uint_t			STAT;		/* Object status */
typedef	uint_t			MODE;		/* Service call operating mode */
typedef	int_t			PRI;		/* Priority */
typedef	uint32_t		TMO;		/* Timeout specification */
typedef	uint32_t		RELTIM;		/* Relative time [NGKI0550] */
#ifdef UINT64_MAX
typedef	uint64_t		SYSTIM;		/* System time [NGKI0548] */
#else /* UINT64_MAX */
typedef	uint32_t		SYSTIM;		/* System time [NGKI0548] */
#endif /* UINT64_MAX */
typedef	uint32_t		PRCTIM;		/* Processor time [NGKI0573] */
typedef	uint32_t		HRTCNT;		/* High-resolution timer count value */

typedef	TOPPERS_fp		FP;			/* Program start address */

typedef	int_t			ER_BOOL;	/* Error code or Boolean value */
typedef	int_t			ER_ID;		/* Error code or ID number */
typedef	int_t			ER_UINT;	/* Error code or unsigned integer */

typedef uintptr_t		MB_T;		/* Data type for allocating management area */

typedef	uint32_t		ACPTN;		/* Access permission pattern */
typedef	struct acvct {				/* Access permission vector */
	ACPTN		acptn1;				/* Access permission pattern for normal operation 1 */
	ACPTN		acptn2;				/* Access permission pattern for normal operation 2 */
	ACPTN		acptn3;				/* Access permission pattern for management operation */
	ACPTN		acptn4;				/* Access permission pattern for reference operation */
} ACVCT;

#endif /* TOPPERS_MACRO_ONLY */

/*
 *  Macros for creating integer constants
 */
#ifndef UINT_C
#define UINT_C(val)		(val ## U)		/* Macro to create a constant of type uint_t */
#endif /* UINT_C */

#ifndef ULONG_C
#define ULONG_C(val)	(val ## UL)		/* Macro to create a constant of type ulong_t */
#endif /* ULONG_C */

/*
 *  general constant
 */
#ifndef NULL
#define NULL		0			/* Invalid pointer */
#endif /* NULL */

#ifndef true
#define true		1			/* true */
#endif /* true */

#ifndef false
#define false		0			/* false */
#endif /* false */

#define E_OK		0			/* normal termination */

/*
 *  Main Error Code
 */
#define E_SYS		(-5)		/* System error */
#define E_NOSPT		(-9)		/* Unsupported function */
#define E_RSFN		(-10)		/* Reserved function code */
#define E_RSATR		(-11)		/* Reserved attribute */
#define E_PAR		(-17)		/* Parameter error */
#define E_ID		(-18)		/* Invalid ID number */
#define E_CTX		(-25)		/* Context error */
#define E_MACV		(-26)		/* Memory access violation */
#define E_OACV		(-27)		/* Object access violation */
#define E_ILUSE		(-28)		/* Invalid service call */
#define E_NOMEM		(-33)		/* Out of memory */
#define E_NOID		(-34)		/* Insufficient ID number */
#define E_NORES		(-35)		/* Insufficient resources */
#define E_OBJ		(-41)		/* Object state error */
#define E_NOEXS		(-42)		/* Object not created */
#define E_QOVR		(-43)		/* Queuing overflow */
#define E_RLWAI		(-49)		/* Forced release from waiting state */
#define E_TMOUT		(-50)		/* Polling failure or timeout */
#define E_DLT		(-51)		/* Deleted waiting object */
#define E_CLS		(-52)		/* Change in waiting object state */
#define E_RASTER	(-53)		/* Task termination request */
#define E_WBLK		(-57)		/* Non-blocking acceptance */
#define E_BOVR		(-58)		/* Buffer overflow */
#define E_COMM		(-65)		/* Communication error */

/*
 *  オブジェクト属性
 */
#define TA_NULL		UINT_C(0)	/* オブジェクト属性を指定しない */

/*
 *  タイムアウト指定
 */
#define TMO_POL		UINT_C(0)			/* ポーリング */
#define TMO_FEVR	(UINT32_MAX)		/* 永久待ち */
#define TMO_NBLK	(UINT32_MAX - 1)	/* ノンブロッキング */

/*
 *  アクセス許可パターン
 */
#define TACP_KERNEL	UINT_C(0)		/* カーネルドメインだけにアクセスを許可 */
#define TACP_SHARED	(~UINT_C(0))	/* すべてのドメインからアクセスを許可 */

/*
 *  型に関する情報を取り出すためのマクロ
 *
 *  以下のALIGN_TYPEの定義は，アラインメントの単位が2の巾乗であることを
 *  仮定している．
 */
#ifndef offsetof
#define	offsetof(structure, field) \
		((uintptr_t)(((char *) &(((structure *) 0)->field)) - ((char *) 0)))
#endif /* offsetof */

#ifndef alignof
#define alignof(type)	offsetof(struct { char field1; type field2; }, field2)
#endif /* alignof */

#ifndef ALIGN_TYPE				/* アラインメントのチェック */
#define ALIGN_TYPE(addr, type) \
						((((uintptr_t)(addr)) & (alignof(type) - 1)) == 0U)
#endif /* ALIGN_TYPE */

/*
 *  assertマクロ
 */
#undef assert
#ifndef NDEBUG
#define assert(exp)		((void)((exp) ? 0 : (TOPPERS_assert_fail(#exp, \
							__FILE__, __LINE__), TOPPERS_assert_abort(), 0)))
#else /* NDEBUG */
#define assert(exp)		((void) 0)
#endif /* NDEBUG */

#ifdef __cplusplus
}
#endif

/*
 *  エラーコード生成・分解マクロ
 *
 *  以下のマクロ定義は，符号付き整数が2の補数で表現されており，右シフト
 *  演算子（>>）が算術シフトされることを仮定している．そうでない開発環
 *  境では，target_stddef.hでこれらの定義を上書きしなければならない．
 *
 *  MERCDマクロの定義は，メインエラーコードが負であることを仮定している．
 *  そうでない場合，2つの定義が一致しなくなる．
 */
#ifndef ERCD
#define ERCD(mercd, sercd) \
				((ER)((((uint_t)(sercd)) << 8) | (((uint_t)(mercd)) & 0xffU)))
#endif /* ERCD */

#ifndef MERCD
#ifdef INT8_MAX
#define MERCD(ercd)		((ER)((int8_t)(ercd)))
#else /* INT8_MAX */
#define MERCD(ercd)		((ER)(((uint_t) ercd) | ~0xffU))
#endif /* INT8_MAX */
#endif /* MERCD */

#ifndef SERCD
#define SERCD(ercd)		((ER)((ercd) >> 8))
#endif /* SERCD */

/*
 *  アクセス許可パターン生成マクロ
 */
#define TACP(domid)		(1U << ((domid) - 1))	/* domidだけにアクセスを許可 */

/*
 *  相対時間（RELTIM）に指定できる最大値［NGKI0551］
 */
#define TMAX_RELTIM		4000000000U				/* 66分40秒まで指定可 */

#endif /* TOPPERS_T_STDDEF_H */
