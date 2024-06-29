#
# CYANCORE LICENSE
# Copyrights (C) 2024, Cyancore Team
#
# File Name		: build.mk
# Description		: This file provides and accumulates configs
#			  and sources for simple system by ibex
# Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
# Organisation		: Cyancore Core-Team
#

SIMSYS_DIR	:= $(GET_PATH)

ARCH		:= riscv
BIT		:= 32
ARCH_VARIANT	:= imc
ARCH_ABI	:= ilp32
TARGET_FLAGS	+= -march=rv32imc -mabi=$(ARCH_ABI)
PLAT_INCLUDE	+= $(SIMSYS_DIR)/include
OUTPUT_FORMAT	:= elf32-littleriscv


LD_SCRIPT       := $(SIMSYS_DIR)/sections.ld.sx
PLAT_INCLUDE	+= $(SIMSYS_DIR)/include
LINT_FLAGS	+= --platform=unix32

USE_DEFAULT_RESOURCES	:= 1
LOCAL_INTERRUPT_DEVICE	:= 1
PLAT_INTERRUPT_DEVICE	:= 0

include $(SIMSYS_DIR)/config.mk
include $(SIMSYS_DIR)/arch/build.mk
include $(SIMSYS_DIR)/hal/build.mk
include $(SIMSYS_DIR)/platform/build.mk
$(eval $(call check_and_include,USE_DEFAULT_RESOURCES,$(SIMSYS_DIR)/resources/build.mk))
