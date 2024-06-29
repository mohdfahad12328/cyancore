/*
 * CYANCORE LICENSE
 * Copyrights (C) 2024, Cyancore Team
 *
 * File Name		: uart.c
 * Description		: This file contains sources for ibex simple system
 *			  HAL uart apis (uart here is sys-out)
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#include <stdint.h>
#include <status.h>
#include <syslog.h>
#include <arch.h>
#include <visor_call.h>
#include <resource.h>
#include <mmio.h>
#include <hal/uart.h>
#include "uart_private.h"

status_t uart_get_properties(uart_port_t *port, sw_devid_t dev)
{
	vret_t vres;
	swdev_t *sp;
	module_t *dp;
	hw_devid_t devid;

	arch_visor_call(fetch_sp, dev, 0, 0, &vres);
	if(vres.status != success)
	{
		sysdbg3("%p - sp node could not be found!\n", dev);
		return vres.status;
	}
	sp = (swdev_t *) vres.p;
	devid = sp->hwdev_id;
	port->pmux = sp->pmux;

	arch_visor_call(fetch_dp, (devid & 0xff00), (devid & 0xff), 0, &vres);
	if(vres.status != success)
	{
		sysdbg3("UART Device %d not found!\n", devid);
		return vres.status;
	}
	dp = (module_t *) vres.p;
	port->port_id = dp->id;
	port->clk_id = dp->clk_id;
	port->baddr = dp->baddr;
	port->baud = dp->clk;
	port->irq = &dp->interrupt[0];
	return success;
}

status_t uart_tx(const uart_port_t *port, const char data)
{
	MMIO32(port->baddr + TXDATA_OFFSET) = data;
	return success;
}

