#
# CYANCORE LICENSE
# Copyrights (C) 2024, Cyancore Team
#
# File Name		: build.mk
# Description		: This file accumulates sources of locks
# Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
# Organisation		: Cyancore Core-Team
#

LIBLOCKS_PATH	:= $(GET_PATH)
LIB_OBJS	:=

LIB		+= liblocks.a
LIB_INCLUDE	+= $(LIBLOCKS_PATH)/include
DEP_LIBS_ARG	+= -llocks


DIR		:= $(LIBLOCKS_PATH)
include mk/lib.mk
