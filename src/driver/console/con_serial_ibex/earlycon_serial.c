/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019, Cyancore Team
 *
 * File Name		: earlycon_serial.c
 * Description		: This file contains sources of uart earlycon
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <status.h>
#include <stdlib.h>
#include <syslog.h>
#include <lock/spinlock.h>
#include <resource.h>
#include <visor_call.h>
#include <arch.h>
#include <driver.h>
#include <interrupt.h>
#include <hal/uart.h>
#include <driver/console.h>
#include <driver/sysclk.h>

static uart_port_t *earlycon_port;

static status_t earlycon_serial_setup()
{
	uart_get_properties(earlycon_port, console_uart);

	sysdbg2("UART engine @ %p\n", earlycon_port->baddr);
	/*
	 * If memory mapping is applicable,
	 * put it in mmu supported guide.
	 */
	return success;
}

static status_t earlycon_serial_write(const char c)
{
	status_t ret;
	ret = uart_tx(earlycon_port, c);
	return ret;
}

static console_t *earlycon_serial_driver;

status_t earlycon_serial_driver_exit()
{
	status_t ret;
	ret = console_release_device();
	free(earlycon_port);
	free(earlycon_serial_driver);
	return ret;
}

status_t earlycon_serial_driver_setup()
{
	status_t ret;

	earlycon_port = (uart_port_t *)malloc(sizeof(uart_port_t));
	if(!earlycon_port)
	{
		ret = error_memory_low;
		goto cleanup_1;
	}

	earlycon_serial_driver = (console_t *)malloc(sizeof(console_t));
	if(!earlycon_serial_driver)
	{
		ret = error_memory_low;
		goto cleanup_1;
	}
	earlycon_serial_driver->write = &earlycon_serial_write;

	ret = earlycon_serial_setup();
	if(ret)
		goto cleanup_1;
	ret = console_attach_device(ret, earlycon_serial_driver);
	if(!ret)
		goto exit;
cleanup_1:
	earlycon_serial_driver_exit();
exit:
	return ret;
}

#if EARLYCON_SERIAL==1
INCLUDE_DRIVER(earlycon, earlycon_serial_driver_setup, earlycon_serial_driver_exit, 0, 2, 2);
#endif
