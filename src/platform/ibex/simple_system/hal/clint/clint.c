/*
 * CYANCORE LICENSE
 * Copyrights (C) 2024, Cyancore Team
 *
 * File Name		: clint.c
 * Description		: This file contains sources of CLINT core
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#include <stdint.h>
#include <status.h>
#include <stdlib.h>
#include <assert.h>
#include <arch.h>
#include <visor_call.h>
#include <resource.h>
#include <hal/clint.h>
#include <driver.h>
#include <mmio.h>
#include <platform.h>
#include "clint_private.h"

static clint_port_t *port;

static status_t clint_setup()
{
	vret_t vres;
	const module_t *dp;

	arch_visor_call(fetch_dp, clint, 0, 0, &vres);

	if(vres.status != success)
		return vres.status;

	port = (clint_port_t *)malloc(sizeof(clint_port_t));
	if(!port)
		return error_memory_low;

	dp = (module_t *)vres.p;
	port->baddr = dp->baddr;
	port->stride = dp->stride;
	port->port_id = clint;
	MMIO64(port->baddr + MTIME_OFFSET) = 0;
	return success;
}

static status_t clint_exit()
{
	free(port);
	return success;
}

status_t clint_config_tcmp(size_t core_id, uint64_t value)
{
	STATUS_CHECK_COREID(core_id);
	MMIO64(port->baddr + MTCMP_OFFSET) = value;
	arch_dsb();
	return success;
}

uint64_t clint_read_time()
{
	uint64_t time_stamp;
	time_stamp = MMIO64(port->baddr + MTIME_OFFSET);
	return time_stamp;
}

INCLUDE_DRIVER(plat_clint, clint_setup, clint_exit, 0, 0, 0);
