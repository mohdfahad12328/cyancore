#
# CYANCORE LICENSE
# Copyrights (C) 2019-2022, Cyancore Team
#
# File Name		: build.mk
# Description		: This file build and gathers project properties
# Primary Author	: Mohd Fahad [mohdfahad12328@gmail.com]
# Organisation		: Open Source Contribuitor
#

# NOTE [jul 13, 1:21 PM]: just copy pasted from demo.src/build.mk


PROJECT_DIR	:= $(GET_PATH)

include $(PROJECT_DIR)/../demo.src/build.mk
include $(PROJECT_DIR)/config.mk

DIR		:= $(PROJECT_DIR)
include mk/obj.mk
