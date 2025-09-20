/*
 *  TOPPERS/HRP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      High Reliable system Profile Kernel
 * 
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2004-2019 by Embedded and Real-Time Systems Laboratory
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
 *  $Id: kernel.h 672 2019-03-01 12:06:42Z ertl-hiro $
 */

/*
 *		TOPPERS/HRP kernel standard header files
 *
 *  A header file that contains declarations of service calls supported by 
 *  the TOPPERS/HRP kernel and definitions of required data types, constants, and macros.
 *
 *  When including this file from an assembly language source file, 
 *  define TOPPERS_MACRO_ONLY. 
 *  This will remove anything other than macro definitions.
 */

#ifndef TOPPERS_KERNEL_H
#define TOPPERS_KERNEL_H

#ifdef __cplusplus
extern "C" {
#endif

/*
 *	TOPPERS common data types, constants, and macros
 */
#include <t_stddef.h>

/*
 *  Target-dependent part
 */
#include "target_kernel.h"

/*
 *  Memory layout method
 */
#ifdef TOPPERS_ML_MANUAL				/* Manual Memory Allocation */
#ifndef TOPPERS_TARGET_SUPPORT_ML_MANUAL
#error Manual memory layout is not supported on this target.
#endif /* TOPPERS_TARGET_SUPPORT_ML_MANUAL */
#else /* TOPPERS_ML_MANUAL */
#ifndef TOPPERS_TARGET_SUPPORT_ML_AUTO
#error Automatic memory layout is not supported on this target.
#endif /* TOPPERS_TARGET_SUPPORT_ML_AUTO */
#define TOPPERS_ML_AUTO					/* Automatic Memory Allocation */
#endif /* TOPPERS_ML_MANUAL */

/*
 *  Supported Features
 */
#ifdef TOPPERS_TARGET_SUPPORT_DIS_INT
#define TOPPERS_SUPPORT_DIS_INT			/* dis_int is supported */
#endif /* TOPPERS_TARGET_SUPPORT_DIS_INT */

#ifdef TOPPERS_TARGET_SUPPORT_ENA_INT
#define TOPPERS_SUPPORT_ENA_INT			/* ena_int is supported */
#endif /* TOPPERS_TARGET_SUPPORT_ENA_INT */

#ifdef TOPPERS_TARGET_SUPPORT_CLR_INT
#define TOPPERS_SUPPORT_CLR_INT			/* clr_int is supported */
#endif /* TOPPERS_TARGET_SUPPORT_CLR_INT */

#ifdef TOPPERS_TARGET_SUPPORT_RAS_INT
#define TOPPERS_SUPPORT_RAS_INT			/* ras_int is supported */
#endif /* TOPPERS_TARGET_SUPPORT_RAS_INT */

#ifdef TOPPERS_TARGET_SUPPORT_PRB_INT
#define TOPPERS_SUPPORT_PRB_INT			/* prb_int is supported */
#endif /* TOPPERS_TARGET_SUPPORT_PRB_INT */

#define TOPPERS_SUPPORT_PROTECT			/* Protection-enabled kernel */

#define TOPPERS_SUPPORT_MESSAGEBUF		/* Message buffer function */

#ifdef TOPPERS_TARGET_SUPPORT_ATT_MOD
#ifdef TOPPERS_ML_AUTO
#define TOPPERS_SUPPORT_ATT_MOD			/* ATT_MOD is supported */
#endif /* TOPPERS_ML_AUTO */
#endif /* TOPPERS_TARGET_SUPPORT_ATT_MOD */

#ifdef TOPPERS_TARGET_SUPPORT_ATT_PMA
#define TOPPERS_SUPPORT_ATT_PMA			/* ATT_PMA is supported */
#endif /* TOPPERS_TARGET_SUPPORT_ATT_PMA */

#define TOPPERS_SUPPORT_DYNAMIC_CRE		/* Dynamic Generation Extensions */

#ifndef TOPPERS_MACRO_ONLY

/*
 *  Data Type Definitions
 */

/*
 *  Bit pattern and object number type definitions
 */
typedef	uint_t		FLGPTN;		/* Event flag bit pattern */
typedef	uint_t		INTNO;		/* Interrupt number */
typedef	uint_t		INHNO;		/* Interrupt handler number */
typedef	uint_t		EXCNO;		/* CPU exception handler number */

/*
 *  Processing unit type definition
 */
typedef void	(*TASK)(intptr_t exinf);
typedef void	(*TMEHDR)(intptr_t exinf);
typedef void	(*ISR)(intptr_t exinf);
typedef void	(*INTHDR)(void);
typedef void	(*EXCHDR)(void *p_excinf);
typedef ER_UINT	(*EXTSVC)(intptr_t par1, intptr_t par2, intptr_t par3,
								intptr_t par4, intptr_t par5, ID cdmid);
typedef void	(*INIRTN)(intptr_t exinf);
typedef void	(*TERRTN)(intptr_t exinf);

/*
 *  Type definition for allocating memory area
 */
#ifndef TOPPERS_STK_T
#define TOPPERS_STK_T	intptr_t
#endif /* TOPPERS_STK_T */
typedef	TOPPERS_STK_T	STK_T;	/* Type for allocating stack area */

#ifndef TOPPERS_MPF_T
#define TOPPERS_MPF_T	intptr_t
#endif /* TOPPERS_MPF_T */
typedef	TOPPERS_MPF_T	MPF_T;	/* Type for allocating a fixed-size memory pool area */

/*
 *  Packet format definition for time event notification method
 */
typedef struct {
	intptr_t	exinf;		/* Extended information for time event handlers */
	TMEHDR		tmehdr;		/* Start address of the time event handler */
} T_NFY_HDR;

typedef struct {
	intptr_t	*p_var;		/* Variable address */
	intptr_t	value;		/* Value to set */
} T_NFY_VAR;

typedef struct {
	intptr_t	*p_var;		/* Variable address */
} T_NFY_IVAR;

typedef struct {
	ID			tskid;		/* Task ID */
} T_NFY_TSK;

typedef struct {
	ID			semid;		/* Semaphore ID */
} T_NFY_SEM;

typedef struct {
	ID			flgid;		/* Event flag ID */
	FLGPTN		flgptn;		/* Bit pattern to set */
} T_NFY_FLG;

typedef struct {
	ID			dtqid;		/* Data Queue ID */
	intptr_t	data;		/* The value to send */
} T_NFY_DTQ;

typedef struct {
	intptr_t	*p_var;		/* Variable address */
} T_ENFY_VAR;

typedef struct {
	ID			dtqid;		/* Data Queue ID */
} T_ENFY_DTQ;

typedef struct {
	MODE	nfymode;			/* Notification Processing Mode */
	union {						/* Additional information regarding time event notifications */
		T_NFY_HDR	handler;
		T_NFY_VAR	setvar;		
		T_NFY_IVAR	incvar;		
		T_NFY_TSK	acttsk;
		T_NFY_TSK	wuptsk;
		T_NFY_SEM	sigsem;
		T_NFY_FLG	setflg;
		T_NFY_DTQ	snddtq;
	} nfy;
	union {						/* Additional information regarding error notification */
		T_ENFY_VAR	setvar;
		T_NFY_IVAR	incvar;		
		T_NFY_TSK	acttsk;
		T_NFY_TSK	wuptsk;
		T_NFY_SEM	sigsem;
		T_NFY_FLG	setflg;
		T_ENFY_DTQ	snddtq;
	} enfy;
} T_NFYINFO;

/*
 *  Packet Format Definitions
 */
typedef struct t_ctsk {
	ATR			tskatr;		/* Task attributes */
	intptr_t	exinf;		/* Task extended information */
	TASK		task;		/* Starting address of the task's main routine */
	PRI			itskpri;	/* Task startup priority */
	size_t		stksz;		/* Task stack area size */
	STK_T		*stk;		/* Starting address of the task's stack area */
	size_t		sstksz;		/* Task system stack area size */
	STK_T		*sstk;		/* Starting address of the task's system stack area */
} T_CTSK;

typedef struct t_rtsk {
	STAT	tskstat;	/* Task state */
	PRI		tskpri;		/* Current task priority */
	PRI		tskbpri;	/* Base task priority */
	STAT	tskwait;	/* Waiting cause */
	ID		wobjid;		/* ID of the object being waited for */
	TMO		lefttmo;	/* Timeout period */
	uint_t	actcnt;		/* Number of queued activation requests */
	uint_t	wupcnt;		/* Number of queued wakeup requests */
	bool_t	raster;		/* Task termination request status */
	bool_t	dister;		/* Task termination prohibition status */
	uint_t	svclevel;	/* Nesting level of extended service calls */
} T_RTSK;

typedef struct t_csem {
	ATR		sematr;		/* Semaphore Attributes */
	uint_t	isemcnt;	/* Initial number of semaphore resources */
	uint_t	maxsem;		/* Maximum number of semaphore resources */
} T_CSEM;

typedef struct t_rsem {
	ID		wtskid;		/* ID number of the task at the head of the semaphore queue */
	uint_t	semcnt;		/* Current number of semaphore resources */
} T_RSEM;

typedef struct t_cflg {
	ATR		flgatr;		/* Event flag attributes */
	FLGPTN	iflgptn;	/* Event flag initial bit pattern */
} T_CFLG;

typedef struct t_rflg {
	ID		wtskid;		/* ID number of the task at the head of the event flag queue */
	FLGPTN	flgptn;		/* The current bit pattern of the event flag */
} T_RFLG;

typedef struct t_cdtq {
	ATR		dtqatr;		/* Data Queue Attributes */
	uint_t	dtqcnt;		/* Number of data items that can be stored in the data queue management area */
	void	*dtqmb;		/* Start address of the data queue management area */
} T_CDTQ;

typedef struct t_rdtq {
	ID		stskid;		/* ID number of the task at the top of the data queue waiting to send */
	ID		rtskid;		/* ID number of the task at the top of the data queue waiting to receive data */
	uint_t	sdtqcnt;	/* Number of data items stored in the data queue management area */
} T_RDTQ;

typedef struct t_cpdq {
	ATR		pdqatr;		/* Priority Data Queue Attributes */
	uint_t	pdqcnt;		/* Number of data items that can be stored in the priority data queue management area */
	PRI		maxdpri;	/* The maximum data priority that can be sent to the priority data queue.
						   Great Value */
	void	*pdqmb;		/* Start address of priority data queue management area */
} T_CPDQ;

typedef struct t_rpdq {
	ID		stskid;		/* The task at the top of the priority data queue waiting to send
						   ID number */
	ID		rtskid;		/* The task at the top of the priority data queue waiting to receive data
						   ID number */
	uint_t	spdqcnt;	/* Data stored in the priority data queue management area
						   Number of data */
} T_RPDQ;

typedef struct t_cmtx {
	ATR		mtxatr;		/* Mutex Attributes */
	PRI		ceilpri;	/* Mutex priority ceiling */
} T_CMTX;

typedef struct t_rmtx {
	ID		htskid;		/* The ID number of the task that has locked the mutex */
	ID		wtskid;		/* ID number of the task at the head of the mutex queue */
} T_RMTX;

typedef struct t_cmbf {
	ATR		mbfatr;		/* Message Buffer Attributes */
	uint_t	maxmsz;		/* Maximum messages in message buffer
							   Size (bytes)*/
	size_t	mbfsz;		/* Message buffer management area size
							   (number of bytes)*/
	void	*mbfmb;		/* Start address of message buffer management area */
} T_CMBF;

typedef struct t_rmbf {
	ID		stskid;		/* The task at the top of the message buffer send queue
						   ID number */
	ID		rtskid;		/* The task at the top of the message buffer receiving queue
						   ID number */
	uint_t	smbfcnt;	/* Messages stored in the message buffer management area
						   Number of messages */
	size_t	fmbfsz;		/* Size of free space in the message buffer management area */
} T_RMBF;

typedef struct t_cmpf {
	ATR		mpfatr;		/* Fixed-size memory pool attributes */
	uint_t	blkcnt;		/* Number of fixed-size memory blocks that can be acquired */
	uint_t	blksz;		/* Size of fixed-size memory blocks */
	MPF_T	*mpf;		/* Starting address of fixed-size memory pool area */
	void	*mpfmb;		/* Starting address of fixed-size memory pool management area */
} T_CMPF;

typedef struct t_rmpf {
	ID		wtskid;		/* ID number of the task at the head of the fixed-size 
    					   memory pool queue */
	uint_t	fblkcnt;	/* Number of fixed-size memory blocks that can be allocated to 
    					   the free memory area of the fixed-size memory pool */
} T_RMPF;

typedef struct t_ccyc {
	ATR			cycatr;		/* Periodic notification attribute */
	T_NFYINFO	nfyinfo;	/* Cycle notification method */
	RELTIM		cyctim;		/* Notification cycle for periodic notifications */
	RELTIM		cycphs;		/* Periodic notification phase */
} T_CCYC;

typedef struct t_rcyc {
	STAT	cycstat;	/* Periodic notification operation status */
	RELTIM	lefttim;	/* Relative time until next notification */
} T_RCYC;

typedef struct t_calm {
	ATR			almatr;		/* Alarm Notification Attributes */
	T_NFYINFO	nfyinfo;	/* Alarm notification method */
} T_CALM;

typedef struct t_ralm {
	STAT	almstat;	/* Alarm notification operation status */
	RELTIM	lefttim;	/* Relative time until notification time */
} T_RALM;

typedef struct t_cisr {
	ATR			isratr;		/* Interrupt Service Routine Attributes */
	intptr_t	exinf;		/* Extended information on interrupt service routines */
	INTNO		intno;		/* The interrupt number to register the interrupt service routine */
	ISR			isr;		/* Interrupt service routine start address */
	PRI			isrpri;		/* Interrupt Service Routine Priority */
} T_CISR;

typedef struct t_rmem {
	ATR		accatr;		/* Memory Object Access Attributes */
	void	*base;		/* Starting address of the memory object */
	size_t	size;		/* The size of the memory object (in bytes) */
} T_RMEM;

#endif /* TOPPERS_MACRO_ONLY */

/*
 *  Definitions and declarations for invoking service calls
 */
#include <kernel_fncode.h>				/* Function Code Definition */
#include "target_svc.h"					/* Called by a software interrupt */
#include <svc_call.h>					/* Called by a function call */

#define SVC_CALL(svc)	_kernel_##svc	/* Name to call by function call */

/*
 *  Service calls that can be invoked from non-task contexts
 */
#define iact_tsk(tskid)						act_tsk(tskid)
#define iwup_tsk(tskid)						wup_tsk(tskid)
#define irel_wai(tskid)						rel_wai(tskid)
#define isns_ter()							sns_ter()
#define isig_sem(semid)						sig_sem(semid)
#define iset_flg(flgid, setptn)				set_flg(flgid, setptn)
#define ipsnd_dtq(dtqid, data)				psnd_dtq(dtqid, data)
#define ifsnd_dtq(dtqid, data)				fsnd_dtq(dtqid, data)
#define ipsnd_pdq(pdqid, data, datapri)		psnd_pdq(pdqid, data, datapri)
#define ifch_hrt()							fch_hrt()
#define ista_alm(almid, almtim)				sta_alm(almid, almtim)
#define istp_alm(almid)						stp_alm(almid)
#define irot_rdq(tskpri)					rot_rdq(tskpri)
#define imrot_rdq(schedno, tskpri)			mrot_rdq(schedno, tskpri)
#define iget_did(p_domid)					get_did(p_domid)
#define iget_tid(p_tskid)					get_tid(p_tskid)
#define iloc_cpu()							loc_cpu()
#define iunl_cpu()							unl_cpu()
#define isns_ctx()							sns_ctx()
#define isns_loc()							sns_loc()
#define isns_dsp()							sns_dsp()
#define isns_dpn()							sns_dpn()
#define isns_ker()							sns_ker()
#define iext_ker()							ext_ker()
#define idis_int(intno)						dis_int(intno)
#define iena_int(intno)						ena_int(intno)
#define iclr_int(intno)						clr_int(intno)
#define iras_int(intno)						ras_int(intno)
#define iprb_int(intno)						prb_int(intno)
#define ixsns_dpn(p_excinf)					xsns_dpn(p_excinf)

/*
 *  Defining Object Attributes
 */
#define TA_DOM(domid)	((((uint_t) domid) & 0xffU) << 16)
										/* Specify the protection domain to which the task belongs */

#define TA_ACT			UINT_C(0x01)	/* Create the task in the activated state */
#define TA_NOACTQUE		UINT_C(0x02)	/* Do not queue activation requests */

#define TA_TPRI			UINT_C(0x01)	/* Task queue in priority order */

#define TA_WMUL			UINT_C(0x02)	/* Multiple waiting tasks */
#define TA_CLR			UINT_C(0x04)	/* Specify event flag clear */

#define TA_CEILING		UINT_C(0x03)	/* Priority ceiling protocol */

#define TA_STA			UINT_C(0x02)	/* Generate periodic notifications in the active state */

#define TA_NOWRITE		UINT_C(0x01)	/* Disable write access */
#define TA_NOREAD		UINT_C(0x02)	/* Disable read access */
#define TA_EXEC			UINT_C(0x04)	/* Permission to execute */
#define TA_MEMINI		UINT_C(0x08)	/* Initialize memory */
#define TA_MEMZERO		UINT_C(0x10)	/* Clear memory */
#define TA_SDATA		UINT_C(0x20)	/* Place in the short data area */
#define TA_UNCACHE		UINT_C(0x40)	/* Cannot be cached */
#define TA_IODEV		UINT_C(0x80)	/* Peripheral device area */

#define TA_ATTMEM		UINT_C(0x1000)	/* Register with ATT_MEM/ATT_PMA */
#define TA_USTACK		UINT_C(0x2000)	/* User stack area */

#define TA_NONKERNEL	UINT_C(0x02)	/* Interrupts not managed by the kernel */

#define TA_ENAINT		UINT_C(0x01)	/* Clear the interrupt request disable flag */
#define TA_EDGE			UINT_C(0x02)	/* Edge trigger */

#define TA_INISOM		UINT_C(0x01)	/* Initial system operating mode */

/*
 *  Standard memory object attributes [NGKI3963] [NGKI3964]
 */
#ifndef TA_TEXTSEC
#define TA_TEXTSEC			(TA_NOWRITE|TA_EXEC)
#endif /* TA_TEXTSEC */
#ifndef TA_RODATASEC
#define TA_RODATASEC		(TA_NOWRITE)
#endif /* TA_RODATASEC */
#ifndef TA_DATASEC
#define TA_DATASEC			(TA_MEMINI)
#endif /* TA_DATASEC */
#ifndef TA_BSSSEC
#define TA_BSSSEC			(TA_MEMZERO)
#endif /* TA_BSSSEC */
#ifndef TA_NOINITSEC
#define TA_NOINITSEC		(TA_NULL)
#endif /* TA_NOINITSEC */
#ifndef TA_LOSEC
#define TA_LOSEC			(TA_NOWRITE|TA_NOREAD)
#endif /* TA_LOSEC */

/*
 *  Defining the operation mode of a service call
 */
#define TWF_ORW			UINT_C(0x01)	/* OR wait for event flags */      
#define TWF_ANDW		UINT_C(0x02)	/* AND wait for event flags */     

#define TPM_WRITE		UINT_C(0x01)	/* Check write access rights */    
#define TPM_READ		UINT_C(0x02)	/* Check read access rights */     
#define TPM_EXEC		UINT_C(0x04)	/* Check execution access rights */

/*
 *  Defining the notification processing mode
 */
#define TNFY_HANDLER	UINT_C(0x00)		/* Call time event handler */  
#define TNFY_SETVAR		UINT_C(0x01)		/* Set variable */             
#define TNFY_INCVAR		UINT_C(0x02)		/* Increment variable */       
#define TNFY_ACTTSK		UINT_C(0x03)		/* Start task */               
#define TNFY_WUPTSK		UINT_C(0x04)		/* Wake up task */             
#define TNFY_SIGSEM		UINT_C(0x05)		/* Return semaphore resource */
#define TNFY_SETFLG		UINT_C(0x06)		/* Set event flag */           
#define TNFY_SNDDTQ		UINT_C(0x07)		/* Send to data queue */       

#define TENFY_SETVAR	UINT_C(0x10)		/* Set variable */             
#define TENFY_INCVAR	UINT_C(0x20)		/* Increment variable */       
#define TENFY_ACTTSK	UINT_C(0x30)		/* Start task */               
#define TENFY_WUPTSK	UINT_C(0x40)		/* Wake up task */             
#define TENFY_SIGSEM	UINT_C(0x50)		/* Return semaphore resource */
#define TENFY_SETFLG	UINT_C(0x60)		/* Set event flag */           
#define TENFY_SNDDTQ	UINT_C(0x70)		/* Send to data queue */       

/*
 *  Defining Object States
 */
#define TTS_RUN			UINT_C(0x01)	/* Running state */                                 
#define TTS_RDY			UINT_C(0x02)	/* Ready state */                                   
#define TTS_WAI			UINT_C(0x04)	/* Waiting state */                                 
#define TTS_SUS			UINT_C(0x08)	/* Suspended state */                               
#define TTS_WAS			UINT_C(0x0c)	/* Double wait state */                                 
#define TTS_DMT			UINT_C(0x10)	/* Paused state */                                  

#define TTW_SLP			UINT_C(0x0001)	/* Waiting for wakeup */                            
#define TTW_DLY			UINT_C(0x0002)	/* Waiting for time to elapse */                    
#define TTW_SEM			UINT_C(0x0004)	/* Waiting to acquire semaphore resources */        
#define TTW_FLG			UINT_C(0x0008)	/* Waiting for an event flag */                     
#define TTW_SDTQ		UINT_C(0x0010)	/* Waiting to send to a data queue */               
#define TTW_RDTQ		UINT_C(0x0020)	/* Waiting to receive from a data queue */          
#define TTW_SPDQ		UINT_C(0x0100)	/* Waiting to send to a priority data queue */      
#define TTW_RPDQ		UINT_C(0x0200)	/* Waiting to receive from a priority data queue */ 
#define TTW_MTX			UINT_C(0x0080)	/* Waiting to lock a mutex */                       
#define TTW_SMBF		UINT_C(0x0400)	/* Waiting to send to a message buffer */           
#define TTW_RMBF		UINT_C(0x0800)	/* Waiting to receive from a message buffer */      
#define TTW_MPF			UINT_C(0x2000)	/* Waiting to acquire a fixed-length memory block */

#define TCYC_STP		UINT_C(0x01)	/* Periodic notification is not active */           
#define TCYC_STA		UINT_C(0x02)	/* Periodic notification is active */               

#define TALM_STP		UINT_C(0x01)	/* Alarm notification is not active */              
#define TALM_STA		UINT_C(0x02)	/* Alarm notification is active */                  

/*
 *  Protection domain ID [NGKI0513]
 */
#define TDOM_SELF		0			/* The protection domain to which the invoking task belongs */
#define TDOM_KERNEL		(-1)		/* kernel domain */
#define TDOM_NONE		(-2)		/* Unaffiliated (not belonging to a protection domain)*/

/*
 *  Other constant definitions [NGKI0514]
 */
#define TSOM_STP		(-1)		/* System cycle stop */

#define TSK_SELF		0			/* Specify your own task */
#define TSK_NONE		0			/* There are no matching tasks */

#define TPRI_SELF		0			/* Base priority of the current task */
#define TPRI_INI		0			/* Task startup priority */

#define TIPM_ENAALL		0			/* Cancel all interrupt priority masks */

/*
 *  Macro to configure scheduling unit number [NGKI0634]
 */
#define SCHEDNO(prcid, domid)	(domid)

/*
 *  Configuration Constants and Macros
 */

/*
 *  Priority Range
 */
#define TMIN_TPRI		1			/* Minimum (highest) task priority */
#define TMAX_TPRI		16			/* Maximum (lowest) task priority */
#define TMIN_DPRI		1			/* Minimum (highest) data priority */
#define TMAX_DPRI		16			/* Maximum (lowest) data priority */
#define TMIN_ISRPRI		1			/* Minimum interrupt service routine priority */
#define TMAX_ISRPRI		16			/* Maximum interrupt service routine priority */

/*
 *  Version Information
 */
#define TKERNEL_MAKER	UINT_C(0x0118)	/* Kernel manufacturer code */
#define TKERNEL_PRID	UINT_C(0x0006)	/* Kernel identification number */
#define TKERNEL_SPVER	UINT_C(0xf633)	/* Kernel specification version number */
#define TKERNEL_PRVER	UINT_C(0x3010)	/* Kernel version number */

/*
 *  Maximum number of queuing times
 */
#define TMAX_ACTCNT		UINT_C(1)		/* Maximum number of startup requests queued */
#define TMAX_WUPCNT		UINT_C(1)		/* Maximum number of queued wake-up requests */

/*
 *  Number of bits in the bit pattern
 */
#ifndef TBIT_FLGPTN					/* Number of bits in the event flag */
#define TBIT_FLGPTN		(sizeof(FLGPTN) * CHAR_BIT)
#endif /* TBIT_FLGPTN */

/*
 *  Adjustable range of system time (unit: μsec)
 */
#define TMIN_ADJTIM		-1000000		/* Minimum system time adjustment */
#define TMAX_ADJTIM		1000000			/* Maximum system time adjustment time */

/*
 *  Maximum length of time window (unit: μs)
 */
#ifndef TMAX_TWDTIM
#define TMAX_TWDTIM		UINT32_MAX
#endif /* TMAX_TWDTIM */

/*
 *  Macros for allocating memory space
 *
 *  The following definitions of TOPPERS_COUNT_SZ and TOPPERS_ROUND_SZ assume 
 *  that unit is a power of two.
 */
#ifndef TOPPERS_COUNT_SZ
#define TOPPERS_COUNT_SZ(sz, unit)	(((sz) + (unit) - 1) / (unit))
#endif /* TOPPERS_COUNT_SZ */
#ifndef TOPPERS_ROUND_SZ
#define TOPPERS_ROUND_SZ(sz, unit)	(((sz) + (unit) - 1) & ~((unit) - 1))
#endif /* TOPPERS_ROUND_SZ */

#define COUNT_STK_T(sz)		TOPPERS_COUNT_SZ(sz, sizeof(STK_T))
#define ROUND_STK_T(sz)		TOPPERS_ROUND_SZ(sz, sizeof(STK_T))

#define COUNT_MB_T(sz)		TOPPERS_COUNT_SZ(sz, sizeof(MB_T))
#define ROUND_MB_T(sz)		TOPPERS_ROUND_SZ(sz, sizeof(MB_T))

#define TSZ_DTQMB(dtqcnt)	(sizeof(intptr_t) * (dtqcnt))
#define TCNT_DTQMB(dtqcnt)	COUNT_MB_T(TSZ_DTQMB(dtqcnt))

#ifndef TSZ_PDQMB
#define TSZ_PDQMB(pdqcnt)	(sizeof(intptr_t) * 3 * (pdqcnt))
#endif /* TSZ_PDQMB */
#define TCNT_PDQMB(pdqcnt)	COUNT_MB_T(TSZ_PDQMB(pdqcnt))

#define TSZ_MBFMB(msgcnt, msgsz) \
	((msgcnt) * (sizeof(uint_t) + TOPPERS_ROUND_SZ(msgsz, sizeof(uint_t))))
#define TCNT_MBFMB(mbfcnt)	COUNT_MB_T(TSZ_MBFMB(mbfcnt))

#define COUNT_MPF_T(blksz)	TOPPERS_COUNT_SZ(blksz, sizeof(MPF_T))
#define ROUND_MPF_T(blksz)	TOPPERS_ROUND_SZ(blksz, sizeof(MPF_T))

#define TSZ_MPFMB(blkcnt)	(sizeof(uint_t) * (blkcnt))
#define TCNT_MPFMB(blkcnt)	COUNT_MB_T(TSZ_MPFMB(blkcnt))

/*
 *  Other configuration constants
 */
#define TMAX_MAXSEM		UINT_MAX	/* Maximum number of semaphore resources */

/*
 *  Macros for checking memory access rights in extended service calls
 *
 *  It is assumed that cdmid is in the local variable.
 */
#ifndef EXTSVC_PROBE_MEM_RW
#define EXTSVC_PROBE_MEM_RW(p_var, type)								\
				(ALIGN_TYPE(p_var, type) && (cdmid == TDOM_KERNEL		\
							|| prb_mem((void *)(p_var), sizeof(type),	\
								TSK_SELF, TPM_WRITE|TPM_READ) == E_OK)
#endif /* EXTSVC_PROBE_MEM_RW */

#ifndef EXTSVC_PROBE_MEM_RW_SIZE
#define EXTSVC_PROBE_MEM_RW_SIZE(p_var, size)							\
				(cdmid == TDOM_KERNEL || prb_mem((void *)(p_var), size,	\
								TSK_SELF, TPM_WRITE|TPM_READ) == E_OK)
#endif /* EXTSVC_PROBE_MEM_RW_SIZE */

#ifndef EXTSVC_PROBE_MEM_RW_COUNT
#define EXTSVC_PROBE_MEM_RW_COUNT(p_var, type, count)					\
				(ALIGN_TYPE(p_var, type) && (cdmid == TDOM_KERNEL		\
					|| prb_mem((void *)(p_var), sizeof(type) * (count),	\
								TSK_SELF, TPM_WRITE|TPM_READ) == E_OK)
#endif /* EXTSVC_PROBE_MEM_RW_COUNT */

#ifndef EXTSVC_PROBE_MEM_READ
#define EXTSVC_PROBE_MEM_READ(p_var, type)								\
				(ALIGN_TYPE(p_var, type) && (cdmid == TDOM_KERNEL		\
							|| prb_mem((void *)(p_var), sizeof(type),	\
										TSK_SELF, TPM_READ) == E_OK))
#endif /* EXTSVC_PROBE_MEM_READ */

#ifndef EXTSVC_PROBE_MEM_READ_SIZE
#define EXTSVC_PROBE_MEM_READ_SIZE(p_var, size)							\
				(cdmid == TDOM_KERNEL || prb_mem((void *)(p_var), size,	\
										TSK_SELF, TPM_READ) == E_OK)
#endif /* EXTSVC_PROBE_MEM_READ_SIZE */

#ifndef EXTSVC_PROBE_MEM_READ_COUNT
#define EXTSVC_PROBE_MEM_READ_COUNT(p_var, type, count)					\
				(ALIGN_TYPE(p_var, type) && (cdmid == TDOM_KERNEL		\
					|| prb_mem((void *)(p_var), sizeof(type) * (count),	\
										TSK_SELF, TPM_READ) == E_OK))
#endif /* EXTSVC_PROBE_MEM_READ_COUNT */

#ifndef EXTSVC_PROBE_MEM_WRITE
#define EXTSVC_PROBE_MEM_WRITE(p_var, type)								\
				(ALIGN_TYPE(p_var, type) && (cdmid == TDOM_KERNEL		\
							|| prb_mem((void *)(p_var), sizeof(type),	\
										TSK_SELF, TPM_WRITE) == E_OK))
#endif /* EXTSVC_PROBE_MEM_WRITE */

#ifndef EXTSVC_PROBE_MEM_WRITE_SIZE
#define EXTSVC_PROBE_MEM_WRITE_SIZE(p_var, size)						\
				(cdmid == TDOM_KERNEL || prb_mem((void *)(p_var), size,	\
										TSK_SELF, TPM_WRITE) == E_OK)
#endif /* EXTSVC_PROBE_MEM_WRITE_SIZE */

#ifndef EXTSVC_PROBE_MEM_WRITE_COUNT
#define EXTSVC_PROBE_MEM_WRITE_COUNT(p_var, type, count)				\
				(ALIGN_TYPE(p_var, type) && (cdmid == TDOM_KERNEL		\
					|| prb_mem((void *)(p_var), sizeof(type) * (count),	\
										TSK_SELF, TPM_WRITE) == E_OK))
#endif /* EXTSVC_PROBE_MEM_WRITE_COUNT */

#ifdef __cplusplus
}
#endif

#endif /* TOPPERS_KERNEL_H */
