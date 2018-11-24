ifeq ($(MAKECMDGOALS), test)

include mk/clang-x86_64.mk

INC_DIRS += ./inc

SRC_DIRS = ./src/test

endif

test: $(EXE)
	@echo "Build took $$(($$(date +%s)-$(DATE))) seconds"
	
    