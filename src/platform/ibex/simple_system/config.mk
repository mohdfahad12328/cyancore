#
# CYANCORE LICENSE
# Copyrights (C) 2024, Cyancore Team
#
# File Name		: config.mk
# Description		: This file defines configuration for ibex Simple System
# Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
# Organisation		: Cyancore Core-Team
#

#======================================================================
# Configuration file for Platforms
#======================================================================

#======================================================================
# Platform Configuration
# Do not alter below FLAGS unless explicitly mentioned
#======================================================================
N_CORES		:= 1
$(eval $(call add_define,N_CORES))

CCSMP		:= 0
$(eval $(call add_define,CCSMP))

$(eval $(call add_define,BIT))

RV_VEC_MODE	:= 1
$(eval $(call add_define,RV_VEC_MODE))

RV_NO_WFI	:= 1
$(eval $(call add_define,RV_NO_WFI))

BOOT_CORE_ID:= 0
$(eval $(call add_define,BOOT_CORE_ID))

RAM_START	:= 0x100000
RAM_SIZE	:= 0x100000	# 1M
HEAP_SIZE	?= 50K
STACK_SIZE	?= 0x2000
STACK_SIZE_PCPU	?= 0x2000

$(eval $(call add_define,HEAP_SIZE))
$(eval $(call add_define,STACK_SIZE))
$(eval $(call add_define,STACK_SIZE_PCPU))

N_EXCEP		:= 12
$(eval $(call add_define,N_EXCEP))

N_IRQ		:= 12
$(eval $(call add_define,N_IRQ))

N_PLAT_IRQS	:= 0
$(eval $(call add_define,N_PLAT_IRQS))

MAX_INTERRUPTS_PER_DEVICE	:= 1
$(eval $(call add_define,MAX_INTERRUPTS_PER_DEVICE))

USE_SPINLOCK	?= 1
$(eval $(call add_define,USE_SPINLOCK))

#======================================================================
# MEMBUF Configuration
#======================================================================
MEMBUF_SIZE	?= 1024
$(eval $(call add_define,MEMBUF_SIZE))
#======================================================================

#======================================================================
# Timer: Sched timer/wall clock
#======================================================================
USE_TIMER	?= 1
$(eval $(call add_define,USE_TIMER))
#======================================================================

#======================================================================
# PRNG: Use upgraded prng
#======================================================================
USE_PRNG	?= 1
$(eval $(call add_define,USE_PRNG))
#======================================================================
