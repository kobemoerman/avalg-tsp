CC = g++
OUT_FILE = tsp

# compiler flags:
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
CFLAGS = -g -Wall
DIRS := .
SOURCES := $(foreach dir, $(DIRS), $(wildcard $(dir)/*.cpp))

all: 
	$(CC) $(SOURCES) $(CFLAGS) -o $(OUT_FILE)
