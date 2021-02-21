#pragma once

typedef struct module
{
	uint8_t id;
	uintptr_t baddr;
	uintptr_t stride;
	unsigned long clk;
	unsigned int clk_id;
	size_t interrupt_id[MAX_INTERRUPTS_PER_DEVICE];
	int_trigger_t interrupt_trigger[MAX_INTERRUPTS_PER_DEVICE];
} module_t;

#define DP_PROTOTYPE_MODULE_FUNCTION(mod)	\
	module_t *dp_get_##mod##_info();

#if UART0
DP_PROTOTYPE_MODULE_FUNCTION(uart0)
#endif

#if ADC0
DP_PROTOTYPE_MODULE_FUNCTION(adc0)
#endif

#if TIMER0
DP_PROTOTYPE_MODULE_FUNCTION(timer0)
#endif

#if TIMER1
DP_PROTOTYPE_MODULE_FUNCTION(timer1)
#endif

#if TIMER2
DP_PROTOTYPE_MODULE_FUNCTION(timer2)
#endif

#if SPI0
DP_PROTOTYPE_MODULE_FUNCTION(spi0)
#endif

#if I2C0
DP_PROTOTYPE_MODULE_FUNCTION(i2c0)
#endif

#if WDT0
DP_PROTOTYPE_MODULE_FUNCTION(wdt0)
#endif