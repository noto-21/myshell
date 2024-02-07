# NT
# Makefile for myshell

# Compiler and compiler flags
CC = gcc
CFLAGS = -Wall

# Source files
SRCS = myshell.c utility.c

# Header files
HDRS = myshell.h

# Object files
OBJS = $(SRCS:.c=.o)

# Target executable
TARGET = myshell

# Rule to build the executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

# Rule to build object files
%.o: %.c $(HDRS)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean rule
clean:
	rm -f $(OBJS)

# .PHONY rule to avoid conflicts with file named 'clean'
.PHONY: clean
