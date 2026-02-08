# Makefile to build Compy transpiler 

# Compiler
CC = gcc
CFLAGS = -O3

# Source & output
COMPY_SRC = compy.c
COMPY_EXE = compy.exe

# Default target
all: $(COMPY_EXE)

# Compile Compy
$(COMPY_EXE): $(COMPY_SRC)
	$(CC) $(CFLAGS) -o $@ $^

# Clean
clean:
	del /Q $(COMPY_EXE) 2>nul || rm -f $(COMPY_EXE)

# Phony targets
.PHONY: all clean
