SHELL = /bin/sh
MKDIR_P = mkdir -p
RM = -rm -rf
CP = cp
DATE := $(shell date +%s)

BUILD_DIR = ./build
TARGET_NAME = $(MAKECMDGOALS)
TARGET_DIR = $(BUILD_DIR)/$(TARGET_NAME)
EXE = $(TARGET_DIR)/$(TARGET_NAME)

all:
	$(MAKE) test
	
.PHONY: all clean

clean:
	$(RM) $(BUILD_DIR)/*

# Flags
include mk/warnings.mk

# Targets
include mk/test.mk

# Generic build rules
include mk/build.mk
