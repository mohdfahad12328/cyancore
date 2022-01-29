/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019, Cyancore Team
 *
 * File Name		: arch.h
 * Description		: This file prototypes arch related functions and
 *			  defines inline-able arch functions.
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#pragma once
#define _ARCH_H_
#include <machine_call.h>
#include <riscv.h>

/**
 * arch_early_setup - This needs to be called in early stages of boot
 */
void arch_early_setup();

/**
 * arch_setup - This needs to be called after inital setup is completed
 */
void arch_setup();

void arch_di_save_state();
void arch_ei_restore_state();

/**
 * arch_panic_handler - Executes when arch error occurs
 */
void arch_panic_handler();
void arch_unhandled_irq();

/**
 * arch_machine_call - Performs machine call
 *
 * Refer arch.c for more details.
 */
void arch_machine_call(unsigned  int, unsigned int, unsigned  int, unsigned  int, mret_t *);

/**
 * arch_register_interrupt_handler - Registers interrtup handler
 * for arch specific exception vectors
 */
void arch_register_interrupt_handler(unsigned int, void (*)(void));

/**
 * local_register_interrupt_handler - Registers interrupt handler
 * for cpu specific interrupt vectors
 */
void local_register_interrupt_handler(unsigned int, void (*)(void));

/**
 * arch_core_index - Returns code index
 */
static inline unsigned int arch_core_index()
{
	unsigned int id;
	asm volatile("csrr %0, mhartid" : "=r" (id));
	return id;
}

/**
 * arch_ei - arch enable global interrupts
 */
static inline void arch_ei()
{
	unsigned int bits = (1 << 3) | (1 << 7);
	asm volatile("csrs mstatus, %0" : : "r" (bits));
}

static inline void arch_ei_mtime()
{
	unsigned int bits = (1 << 7);
	asm volatile("csrs mie, %0" : : "r" (bits));
}

static inline void arch_di_mtime()
{
	unsigned int bits = (1 << 7);
	asm volatile("csrc mie, %0" : : "r" (bits));
}

static inline void arch_ei_softirq()
{
	unsigned int bits = (1 << 3);
	asm volatile("csrs mie, %0" : : "r" (bits));
}

static inline void arch_di_softirq()
{
	unsigned int bits = (1 << 3);
	asm volatile("csrc mie, %0" : : "r" (bits));
}

/**
 * arch_di - arch disable global interrupts
 */
static inline void arch_di()
{
	unsigned int bits = (1 << 3) | (1 << 7);
	asm volatile("csrc mstatus, %0" : : "r" (bits));
	asm volatile("csrc mie, %0" : : "r" (bits));
}

static inline void arch_nop()
{
	asm volatile("nop");
}

static inline void arch_wfi()
{
	asm volatile("wfi");
#if ERRATA_CIP578
	arch_nop();
	arch_nop();
#endif
}

static inline void arch_isb()
{
	asm volatile("fence.i");
}

static inline void arch_dsb()
{
	asm volatile("fence");
}

static inline void arch_dmb()
{
	fence(rw, rw);
}