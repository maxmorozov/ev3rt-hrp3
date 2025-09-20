/*
 *  TOPPERS Software
 *      Toyohashi Open Platform for Embedded Real-Time Systems
 * 
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2006-2018 by Embedded and Real-Time Systems Laboratory
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
 *  $Id: arm.h 412 2018-07-25 09:38:09Z ertl-hiro $
 */

/*
 *		ARM Core Support Module
 */

#ifndef TOPPERS_ARM_H
#define TOPPERS_ARM_H

#include <t_stddef.h>

/*
 *  Inline function definitions for ARM core special instructions
 */
#ifndef TOPPERS_MACRO_ONLY
#include "arm_insn.h"
#endif /*  TOPPERS_MACRO_ONLY */

/*
 *  ARM Exception Vectors
 */
#define RESET_VECTOR	UINT_C(0x00)
#define UNDEF_VECTOR	UINT_C(0x04)
#define SVC_VECTOR		UINT_C(0x08)
#define PABORT_VECTOR	UINT_C(0x0c)
#define DABORT_VECTOR	UINT_C(0x10)
#define IRQ_VECTOR		UINT_C(0x18)
#define FIQ_VECTOR		UINT_C(0x1c)

/*
 *  ARM exception vector number
 */
#define RESET_NUMBER	UINT_C(0)
#define UNDEF_NUMBER	UINT_C(1)
#define SVC_NUMBER		UINT_C(2)
#define PABORT_NUMBER	UINT_C(3)
#define DABORT_NUMBER	UINT_C(4)
#define IRQ_NUMBER		UINT_C(6)
#define FIQ_NUMBER		UINT_C(7)

/*
 *  CPSR interrupt disable bit
 */
#define CPSR_INT_MASK	UINT_C(0xc0)
#define CPSR_IRQ_BIT	UINT_C(0x80)
#define CPSR_FIQ_BIT	UINT_C(0x40)

/*
 *  Thumb bits in the CPSR
 */
#define CPSR_THUMB_BIT	UINT_C(0x20)

/*
 *  CPSR mode bits
 */
#define CPSR_MODE_MASK	UINT_C(0x1f)
#define CPSR_USER_MODE	UINT_C(0x10)
#define CPSR_FIQ_MODE	UINT_C(0x11)
#define CPSR_IRQ_MODE	UINT_C(0x12)
#define CPSR_SVC_MODE	UINT_C(0x13)
#define CPSR_ABT_MODE	UINT_C(0x17)
#define CPSR_UND_MODE	UINT_C(0x1b)
#define CPSR_SYS_MODE	UINT_C(0x1f)

/*
 *  CP15 system control register (SCTLR) setting value
 *
 *  In ARMv7, CP15_SCTLR_EXTPAGE is always set to 1.
 */
#if __TARGET_ARCH_ARM == 6
#define CP15_SCTLR_EXTPAGE		UINT_C(0x00800000)
#endif /* __TARGET_ARCH_ARM == 6 */
#define CP15_SCTLR_VECTOR		UINT_C(0x00002000)
#define CP15_SCTLR_ICACHE		UINT_C(0x00001000)
#define CP15_SCTLR_BP			UINT_C(0x00000800)
#define CP15_SCTLR_DCACHE		UINT_C(0x00000004)
#define CP15_SCTLR_MMU			UINT_C(0x00000001)

/*
 *  CP15 Coprocessor Access Control Register (CPACR) setting
 */
#define CP15_CPACR_ASEDIS			UINT_C(0x80000000)
#define CP15_CPACR_D32DIS			UINT_C(0x40000000)
#define CP15_CPACR_CP11_FULLACCESS	UINT_C(0x00c00000)
#define CP15_CPACR_CP10_FULLACCESS	UINT_C(0x00300000)

/*
 *  Reference value of the CP15 fault status register
 */
#define CP15_FSR_FS_MASK			UINT_C(0x0000040f)
#define CP15_FSR_FS_ALIGNMENT		UINT_C(0x00000001)
#define CP15_FSR_FS_TRANSLATION1	UINT_C(0x00000005)
#define CP15_FSR_FS_TRANSLATION2	UINT_C(0x00000007)
#define CP15_FSR_FS_PERMISSION1		UINT_C(0x0000000d)
#define CP15_FSR_FS_PERMISSION2		UINT_C(0x0000000f)

/*
 *  CP15 Performance Monitor Control Register (PMCR) setting value
 */
#define CP15_PMCR_ALLCNTR_ENABLE		UINT_C(0x01)
#define CP15_PMCR_PMCCNTR_DIVIDER		UINT_C(0x08)

/*
 *  CP15 Performance Monitor Count Enable Set Register (PMCNTENSET)
 *  Setting value
 */
#define CP15_PMCNTENSET_CCNTR_ENABLE	UINT_C(0x80000000)

/*
 *  CP15 Translation Table Base Register (TTBR) setting value
 */
#define CP15_TTBR_RGN_SHAREABLE		UINT_C(0x00000002)
#if __TARGET_ARCH_ARM == 7
#define CP15_TTBR_RGN_WBWA			UINT_C(0x00000008)
#endif /* __TARGET_ARCH_ARM == 7 */
#define CP15_TTBR_RGN_WTHROUGH		UINT_C(0x00000010)
#define CP15_TTBR_RGN_WBACK			UINT_C(0x00000018)
#if __TARGET_ARCH_ARM < 7
#define CP15_TTBR_RGN_CACHEABLE		UINT_C(0x00000001)
#else /* __TARGET_ARCH_ARM < 7 */
#define CP15_TTBR_IRGN_WBWA			UINT_C(0x00000040)
#define CP15_TTBR_IRGN_WTHROUGH		UINT_C(0x00000001)
#define CP15_TTBR_IRGN_WBACK		UINT_C(0x00000041)
#endif /* __TARGET_ARCH_ARM < 7 */

/*
 *  MMU-related definitions (VMSA)
 */

/*
 *  Section and Page Size
 */
#define ARM_SSECTION_SIZE			UINT_C(0x1000000)
#define ARM_SECTION_SIZE			UINT_C(0x0100000)
#define ARM_LPAGE_SIZE				UINT_C(0x0010000)
#define ARM_PAGE_SIZE				UINT_C(0x0001000)

/*
 *  Section table and page table sizes
 */
#define ARM_SECTION_TABLE_SIZE		UINT_C(0x4000)
#define ARM_SECTION_TABLE_ALIGN		UINT_C(0x4000)
#define ARM_SECTION_TABLE_ENTRY		(ARM_SECTION_TABLE_SIZE / sizeof(uint32_t))

#define ARM_PAGE_TABLE_SIZE			UINT_C(0x0400)
#define ARM_PAGE_TABLE_ALIGN		UINT_C(0x0400)
#define ARM_PAGE_TABLE_ENTRY		(ARM_PAGE_TABLE_SIZE / sizeof(uint32_t))

/*
 *  First-level descriptor setting value
 */
#define ARM_MMU_DSCR1_FAULT			0x00000U	/* Fault */
#define ARM_MMU_DSCR1_PAGETABLE		0x00001U	/* Coarse Page Table */
#define ARM_MMU_DSCR1_SECTION		0x00002U	/* Section */
#define ARM_MMU_DSCR1_SSECTION		0x40002U	/* Supersection */

#define ARM_MMU_DSCR1_SHARED		0x10000U	/* Shared Between Processors */
#define ARM_MMU_DSCR1_TEX000		0x00000U	/* TEX Bit is 000 */
#define ARM_MMU_DSCR1_TEX001		0x01000U	/* TEX Bit is 001 */
#define ARM_MMU_DSCR1_TEX010		0x02000U	/* TEX Bit is 010 */
#define ARM_MMU_DSCR1_TEX100		0x04000U	/* TEX Bit is 100 */
#define ARM_MMU_DSCR1_CB00			0x00000U	/* C Bit is 0, B Bit is 0 */
#define ARM_MMU_DSCR1_CB01			0x00004U	/* C Bit is 0, B Bit is 1 */
#define ARM_MMU_DSCR1_CB10			0x00008U	/* C Bit is 1, B Bit is 0 */
#define ARM_MMU_DSCR1_CB11			0x0000cU	/* C Bit is 1, B Bit is 1 */

#if __TARGET_ARCH_ARM < 6

#define ARMV5_MMU_DSCR1_AP01		0x00400U	/* AP Bit is 01 */
#define ARMV5_MMU_DSCR1_AP10		0x00800U	/* AP Bit is 10 */
#define ARMV5_MMU_DSCR1_AP11		0x00c00U	/* AP Bit is 11 */

#else /* __TARGET_ARCH_ARM < 6 */

#define ARMV6_MMU_DSCR1_NONGLOBAL	0x20000U	/* Not Global */
#define ARMV6_MMU_DSCR1_AP001		0x00400		/* AP Bit is 001 */
#define ARMV6_MMU_DSCR1_AP010		0x00800		/* AP Bit is 010 */
#define ARMV6_MMU_DSCR1_AP011		0x00c00		/* AP Bit is 011 */
#define ARMV6_MMU_DSCR1_AP101		0x08400		/* AP Bit is 101 */
#define ARMV6_MMU_DSCR1_AP110		0x08800		/* AP Bit is 110 */
#define ARMV6_MMU_DSCR1_AP111		0x08c00		/* AP bits are 111 */
#define ARMV6_MMU_DSCR1_ECC			0x00200U	/* ECC enabled (MPCore) */
#define ARMV6_MMU_DSCR1_NOEXEC		0x00010U	/* Cannot be executed */

#endif /* __TARGET_ARCH_ARM < 6 */

/*
 *  Second-level descriptor setting value
 */
#define ARM_MMU_DSCR2_FAULT			0x0000U		/* Fault */
#define ARM_MMU_DSCR2_LARGE			0x0001U		/* Large page */
#define ARM_MMU_DSCR2_SMALL			0x0002U		/* Small page */

#define ARM_MMU_DSCR2_CB00			0x0000U		/* C bit is 0, B bit is 0 */
#define ARM_MMU_DSCR2_CB01			0x0004U		/* C bit is 0, B bit is 1 */
#define ARM_MMU_DSCR2_CB10			0x0008U		/* C bit is 1, B bit is 0 */
#define ARM_MMU_DSCR2_CB11			0x000cU		/* C bit is 1, B bit is 1 */

#if __TARGET_ARCH_ARM < 6

#define ARMV5_MMU_DSCR2_AP01		0x0550U		/* AP[0-3] bits are 01 */
#define ARMV5_MMU_DSCR2_AP10		0x0aa0U		/* AP[0-3] bits are 10 */
#define ARMV5_MMU_DSCR2_AP11		0x0ff0U		/* AP[0-3] bits are 11 */

/* For large page descriptors */
#define ARMV5_MMU_DSCR2L_TEX000		0x0000U		/* TEX bit is 000 */
#define ARMV5_MMU_DSCR2L_TEX001		0x1000U		/* TEX bit is 001 */
#define ARMV5_MMU_DSCR2L_TEX010		0x2000U		/* TEX bit is 010 */
#define ARMV5_MMU_DSCR2L_TEX100		0x4000U		/* TEX bit is 100 */

#else /* __TARGET_ARCH_ARM < 6 */

#define ARMV6_MMU_DSCR2_NONGLOBAL	0x0800U		/* Not global */
#define ARMV6_MMU_DSCR2_SHARED		0x0400U		/* Shared between processors */
#define ARMV6_MMU_DSCR2_AP001		0x0010		/* AP bit is 001 */
#define ARMV6_MMU_DSCR2_AP010		0x0020		/* AP bit is 010 */
#define ARMV6_MMU_DSCR2_AP011		0x0030		/* AP bit is 011 */
#define ARMV6_MMU_DSCR2_AP101		0x0210		/* AP bit is 101 */
#define ARMV6_MMU_DSCR2_AP110		0x0220		/* AP bit is 110 */
#define ARMV6_MMU_DSCR2_AP111		0x0230		/* AP bit is 111 */

/* For large page descriptors */
#define ARMV6_MMU_DSCR2L_TEX000		0x0000U		/* TEX bit is 000 */
#define ARMV6_MMU_DSCR2L_TEX001		0x1000U		/* TEX bit is 001 */
#define ARMV6_MMU_DSCR2L_TEX010		0x2000U		/* TEX bit is 010 */
#define ARMV6_MMU_DSCR2L_TEX100		0x4000U		/* TEX bit is 100 */
#define ARMV6_MMU_DSCR2L_NOEXEC		0x8000U		/* Cannot execute */

/* For small page descriptors */
#define ARMV6_MMU_DSCR2S_TEX000		0x0000U		/* TEX bit is 000 */
#define ARMV6_MMU_DSCR2S_TEX001		0x0040U		/* TEX bit is 001 */
#define ARMV6_MMU_DSCR2S_TEX010		0x0080U		/* TEX bit is 010 */
#define ARMV6_MMU_DSCR2S_TEX100		0x0100U		/* TEX bit is 100 */
#define ARMV6_MMU_DSCR2S_NOEXEC		0x0001U		/* Cannot execute */

#endif /* __TARGET_ARCH_ARM < 6 */

#ifndef TOPPERS_MACRO_ONLY

/*
 *	Coprocessor 15 operation functions
 */

/*
 *  Set to use High exception vectors
 */
Inline void
arm_set_high_vectors(void)
{
	uint32_t	reg;

	CP15_READ_SCTLR(reg);
	reg |= CP15_SCTLR_VECTOR;
	CP15_WRITE_SCTLR(reg);
}

/*
 *  Set to use Low exception vectors
 */
Inline void
arm_set_low_vectors(void)
{
	uint32_t	reg;

	CP15_READ_SCTLR(reg);
	reg &= ~CP15_SCTLR_VECTOR;
	CP15_WRITE_SCTLR(reg);
}

/*
 *  Enable branch prediction
 */
Inline void
arm_enable_bp(void)
{
	uint32_t	reg;

	CP15_READ_SCTLR(reg);
	reg |= CP15_SCTLR_BP;
	CP15_WRITE_SCTLR(reg);
}

/*
 *  Disable branch prediction
 */
Inline void
arm_disable_bp(void)
{
	uint32_t	reg;

	CP15_READ_SCTLR(reg);
	reg &= ~CP15_SCTLR_BP;
	CP15_WRITE_SCTLR(reg);
}

/*
 *  Get the processor number
 *
 *  Reads the multiprocessor affinity register and returns the lowest 8 bits.
 *  On ARMv6, it is only available if multiprocessor support is available.
 */
#if __TARGET_ARCH_ARM >= 6

Inline uint32_t
arm_prc_index(void)
{
	uint32_t	reg;

	CP15_READ_MPIDR(reg);
	return(reg & 0xffU);
}

#endif /* __TARGET_ARCH_ARM >= 6 */

/*
 *  Cache operations
 */

/*
 *  Enable/disable instruction/data cache
 */
extern void arm_enable_icache(void);
extern void arm_disable_icache(void);
extern void arm_enable_dcache(void);
extern void arm_disable_dcache(void);

/*
 *  Enable Cache
 */
Inline void
arm_enable_cache(void)
{
	arm_enable_icache();
	arm_enable_dcache();
}

/*
 *  Disable cache
 */
Inline void
arm_disable_cache(void)
{
	arm_disable_icache();
	arm_disable_dcache();
}

/*
 *  Invalidate/clean data cache in ARMv5
 */
#if __TARGET_ARCH_ARM <= 5
extern void armv5_clean_and_invalidate_dcache(void);
#endif /* __TARGET_ARCH_ARM <= 5 */

/*
 *  Invalidate/clean data cache in ARMv7
 */
#if __TARGET_ARCH_ARM == 7
extern void armv7_invalidate_dcache(void);
extern void armv7_clean_and_invalidate_dcache(void);
#endif /* __TARGET_ARCH_ARM == 7 */

/*
 *  Invalidating Data and Integrated Caching
 */
Inline void
arm_invalidate_dcache(void)
{
#if __TARGET_ARCH_ARM <= 6
	CP15_INVALIDATE_DCACHE();
	CP15_INVALIDATE_UCACHE();
#else /* __TARGET_ARCH_ARM <= 6 */
	armv7_invalidate_dcache();
#endif /* __TARGET_ARCH_ARM <= 6 */
}

/*
 *  Cleaning and invalidating the data cache and unified cache
 */
Inline void
arm_clean_and_invalidate_dcache(void)
{
#if __TARGET_ARCH_ARM <= 5
	armv5_clean_and_invalidate_dcache();
#elif __TARGET_ARCH_ARM == 6
	CP15_CLEAN_AND_INVALIDATE_DCACHE();
	CP15_CLEAN_AND_INVALIDATE_UCACHE();
#else
	armv7_clean_and_invalidate_dcache();
#endif
}

/*
 *  Invalidate instruction cache
 */
Inline void
arm_invalidate_icache(void)
{
	CP15_INVALIDATE_ICACHE();
}

/*
 *  Disable branch prediction
 */
Inline void
arm_invalidate_bp(void)
{
	CP15_INVALIDATE_BP();
	data_sync_barrier();
	inst_sync_barrier();
}

/*
 *  TLB invalidation
 */
Inline void
arm_invalidate_tlb(void)
{
	CP15_INVALIDATE_TLB();
	data_sync_barrier();
}

#endif /* TOPPERS_MACRO_ONLY */

/*
 *  Floating-Point Exception Control Register (FPEXC) setting
 */
#define FPEXC_ENABLE		UINT_C(0x40000000)

#endif /* TOPPERS_ARM_H */
