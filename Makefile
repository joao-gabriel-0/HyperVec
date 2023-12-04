# 
# Direcotories
# 
SRC_DIR      = ./hypervec
TESTS_DIR    = .tests
EXAMPLES_DIR = ./examples
BUILD_DIR    = ./build

# 
# C version: C23
# 
CFLAGS = -std=c2x

# 
# Compiler warning flags
# 
CFLAGS += \
	-Wall -Wextra -Wpointer-arith -Wstrict-aliasing=2 -Wtrampolines -Wformat=2 \
	-Wformat-security -Wformat-nonliteral -Wwrite-strings -Wdouble-promotion -Wstrict-prototypes \
	-Wmissing-prototypes -Wmissing-declarations -Wnested-externs -Winline -Wdisabled-optimization \
	-Winit-self -Wswitch-default -Wswitch-enum -Wundef -Wunsafe-loop-optimizations -Wbad-function-cast \
	-Wcast-qual -Wstrict-overflow=5 -Wredundant-decls -Wsign-conversion -Wsign-compare -Wunused-parameter

# 
# Compiler sanitization flags
# 
CFLAGS += \
	-fsanitize=address -fsanitize=builtin -fsanitize=integer-divide-by-zero \
	-fsanitize=null -fsanitize=return -fsanitize=shift-exponent -fsanitize=vla-bound \
	-fsanitize=alignment -fsanitize=enum -fsanitize=object-size -fsanitize=returns-nonnull-attribute \
	-fsanitize=signed-integer-overflow -fsanitize=vptr -fsanitize=bool -fsanitize=float-cast-overflow \
	-fsanitize=pointer-compare -fsanitize=bounds -fsanitize=float-divide-by-zero -fsanitize=leak \
	-fsanitize=pointer-overflow -fsanitize=shift -fsanitize=undefined -fsanitize=bounds-strict \
	-fsanitize=nonnull-attribute -fsanitize=pointer-subtract -fsanitize=shift-base -fsanitize=unreachable

all:
	@echo
	@echo " Options:"
	@echo "  .  make tests              # Compiles all test-cases (developers only)"
	@echo "  .  make examples           # Compiles all example-cases"
	@echo "  .  make clean              # Cleans every file generated by this Makefile"
	@echo

.PHONY: tests
tests:
	@echo
	@echo "Compiling all test cases..."
	@echo
	-mkdir -p $(TESTS_DIR)
	gcc $(SRC_DIR)/hypervec.c $(TESTS_DIR)/tests.c -o $(TESTS_DIR)/tests $(CFLAGS)

.PHONY: examples
examples:
	@echo
	@echo "Compiling all example cases..."
	@echo
	-mkdir -p $(TESTS_DIR)
	cp $(SRC_DIR)/hypervec.c $(SRC_DIR)/hypervec.h $(EXAMPLES_DIR)/
	gcc $(EXAMPLES_DIR)/hypervec.c $(EXAMPLES_DIR)/examples.c -o $(EXAMPLES_DIR)/examples $(CFLAGS)
	
.PHONY: clean
clean:
	@echo
	@echo "Cleaning generated files..."
	@echo
	-rm $(TESTS_DIR)/tests
	-rm $(EXAMPLES_DIR)/examples
	-rm $(EXAMPLES_DIR)/hypervec.c $(EXAMPLES_DIR)/hypervec.h