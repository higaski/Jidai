AS = clang
CC = clang
CXX = clang++
LD = clang++
AR = llvm-ar

# Create include flags
INC_FLAGS = $(addprefix -I,$(INC_DIRS))

# Preprocessor flags
CPPFLAGS += $(INC_FLAGS) -MMD -MP

# Common flags
FLAGS += $(VFLAG) 
FLAGS += -fmessage-length=0 -fsigned-char
FLAGS += $(OPTFLAGS)
FLAGS += $(WARNFLAGS)
FLAGS += $(DBGFLAGS)

# Assembler flags
ASFLAGS += $(FLAGS)
ASFLAGS += -x assembler-with-cpp

# C flags
CFLAGS += $(FLAGS)
CFLAGS += -std=gnu11

# C++ flags
CXXFLAGS += $(FLAGS)
CXXFLAGS += -std=c++2a -ftemplate-depth=2048 -ftemplate-backtrace-limit=0

# Linker flags
LDFLAGS += $(FLAGS)