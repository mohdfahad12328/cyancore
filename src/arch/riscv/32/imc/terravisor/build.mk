#
# CYANCORE LICENSE
# Copyrights (C) 2024, Cyancore Team
#
# File Name		: build.mk
# Description		: Build script for this directory.
# Primary Authod	: Akash Kollipara [akashkollipara@gmail.com]
# Organisation		: Cyancore Core-Team
#

RV32IMC_T_ARCH_DIR	:= $(GET_PATH)

include $(RV32IMC_T_ARCH_DIR)/../../i/terravisor/build.mk

DIR		:= $(RV32IMC_T_ARCH_DIR)
include mk/obj.mk
