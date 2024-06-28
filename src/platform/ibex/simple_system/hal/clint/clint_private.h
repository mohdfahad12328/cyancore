/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019, Cyancore Team
 *
 * File Name		: clint_private.h
 * Description		: This file contains CLINT core register offsets
 *			  and other private variables
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#pragma once

#define MTCMP_OFFSET		(0x0)
#define MTIME_OFFSET		(0x8)

typedef struct clint_port
{
	hw_devid_t port_id;
	uintptr_t baddr;
	uintptr_t stride;
} clint_port_t;
