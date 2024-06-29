/*
 * CYANCORE LICENSE
 * Copyrights (C) 2024, Cyancore Team
 *
 * File Name		: dp.c
 * Description		: This file contains sources for platform
 *			  device properties
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#include <status.h>
#include <resource.h>
#include <plat_mem.h>
#include <hal/gpio.h>

#ifndef XCLK
#define XCLK 0
INFO(< ! > XCLK is not defined!)
#endif

create_cpu(core0, "riscv-ibex", 0);

create_memory(mem, RAM_START, RAM_LENGTH);

create_module(uart0, (uart | 0), 0x20000, 0x1, 0, 0);

create_module(timer_core0, (timer | 0), 0, 0, 2000000, 0,
		add_irq(0, int_local, 7, int_level));

create_module(clint0, clint, 0x30000, 16, 0, 0);

create_gpio_list(port_list, 0);

create_module_list(mod_list, &uart0, &clint0, &timer_core0);

create_dp(device_prop, XCLK, mem, port_list, mod_list,
	add_cpu(0, core0));
