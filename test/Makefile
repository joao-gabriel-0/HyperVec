#
# This file is NOT part of the HyperVec Library.
#

CC = gcc

CFLAGS = -Wall -Wextra -pedantic -Wpointer-arith -Wcast-qual -Wformat=2 -Wwrite-strings -Wstrict-prototypes -Wmissing-prototypes \
	     -Wmissing-declarations -Wnested-externs -Winline -Wdisabled-optimization -Wstrict-aliasing=2 -Winit-self \
		 -Wswitch-default -Wswitch-enum -Wundef -Wunsafe-loop-optimizations -Wbad-function-cast -Wcast-qual \
		 -Wstrict-overflow=5 -Wtrampolines -Wfloat-equal -Wredundant-decls

OPTIMIZATION_FLAGS = -ftree-loop-linear -floop-strip-mine -floop-block -floop-nest-optimize -floop-parallelize-all -ftree-vectorize \
				     -ftree-loop-distribution -ftree-partial-pre -fpeel-loops -fgraphite-identity -fno-math-errno -fno-trapping-math \
					 -fpredictive-commoning -fsplit-paths -fipa-pta -fivopts -fweb -flto=16 -fno-common -fno-plt -fgcse-after-reload \
					 -fno-semantic-interposition -fvect-cost-model=dynamic -fsimd-cost-model=dynamic -O3 -march=native -mtune=native \
					 -pipe -fdevirtualize-at-ltrans

# directories
SRC_DIRECTORY = ../src
BUILD_DIRECTORY = build

LIB_SRC_FILES = $(wildcard $(SRC_DIRECTORY)/*.c)
LIB_OBJ_FILES = $(patsubst $(SRC_DIRECTORY)/%.c, $(BUILD_DIRECTORY)/%.o, $(LIB_SRC_FILES))

# target executable name
TARGET = test

.PHONY: all
all: $(TARGET)

$(TARGET): $(LIB_OBJ_FILES) test.c
	$(CC) $^ -o $@ $(CFLAGS) $(OPTIMIZATION_FLAGS)

$(BUILD_DIRECTORY)/%.o: $(SRC_DIRECTORY)/%.c
	@mkdir -p $(dir $@)
	$(CC) -c $< -o $@ $(CFLAGS) $(OPTIMIZATION_FLAGS) -MMD -MP

.PHONY: clean
clean:
	-rm -rf $(TARGET) $(BUILD_DIRECTORY)

-include $(LIB_OBJ_FILES:.o=.d)
