#
# CYANCORE LICENSE
# Copyrights (C) 2019, Cyancore Team
#
# File Name		: build.mk
# Description		: This file accumulates the build scripts from
#			  all other directories that have atmega328p
#			  board support sources
# Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
# Organisation		: Cyancore Core-Team
#

F103_DIR	:= $(GET_PATH)

ARCH		:= arm-m
BIT		:= 32
ARCH_VARIANT	:= m3
TL_TYPE		:= thumb/v7-m
TARGET_FLAGS	+= -mcpu=cortex-m3 -mfloat-abi=softfp
#PLAT_INCLUDE	+= $(F103_DIR)/include
OUTPUT_FORMAT	:= elf32-littlearm

#include $(ATMEGA328P_DIR)/config.mk
#include $(ATMEGA328P_DIR)/arch/build.mk
#include $(ATMEGA328P_DIR)/platform/build.mk
#include $(ATMEGA328P_DIR)/../common/build.mk
#$(eval $(call check_and_include,USE_DEFAULT_RESOURCES,$(F103_DIR)/resources/build.mk))
