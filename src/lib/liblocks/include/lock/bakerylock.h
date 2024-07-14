
#pragma once
#define _BAKERYLOCK_H_

#include <stdbool.h>

#pragma pack(1)
typedef struct
{
	volatile uint8_t thread_count[N_CORES];
	volatile bool protect[N_CORES];
} bakerylock_t;
#pragma pack()

extern void bakerylock_acquire(bakerylock_t *);
extern void bakerylock_release(bakerylock_t *);
