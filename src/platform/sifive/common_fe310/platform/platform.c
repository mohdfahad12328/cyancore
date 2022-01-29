#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <status.h>
#include <arch.h>
#include <driver.h>
#include <insignia.h>
#include <terravisor/platform.h>
#include <terravisor/workers.h>
#include <platform.h>

void platform_early_setup()
{
	status_t ret = success;

	ret |= platform_copy_data();
	ret |= platform_copy_itim();
	ret |= platform_bss_clear();
	ret |= platform_resources_setup();

	if(ret != success)
		exit(EXIT_FAILURE);
	return;
}

void platform_setup()
{
	status_t ret = success;

	ret |= driver_setup("earlycon");
	cyancore_insignia();

	if(ret != success)
		exit(EXIT_FAILURE);
	return;
}

void platform_cpu_setup()
{
	status_t ret = success;

	if(ret != success)
		exit(EXIT_FAILURE);
	return;
}