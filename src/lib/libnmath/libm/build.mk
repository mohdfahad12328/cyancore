#
# CYANCORE LICENSE
# Copyrights (C) 2024, Cyancore Team
#
# File Name		: build.mk
# Descrption		: This script generates tcmath library
#			  it uses toolchain's libm.a
# Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
# Organisation		: Cyancore Core-Team
#

TCMATH_PATH	:= $(GET_PATH)

LIB_OBJS	:= $$(TCL)/libm.a

LIB		:= libtcmath.a
LIB_INCLUDE	+= $(TCMATH_PATH)/include/
DEP_LIBS_ARG	+= -ltcmath

AR_FLAGS	:= rcsT

DIR		:= $(TCMATH_PATH)

include mk/lib.mk
