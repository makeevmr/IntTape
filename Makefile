# Compilation flags
CC=g++
OPT=-O2
CFLAGS=-c -pedantic-errors -Wall -Wextra -std=c++20 $(OPT)
TFLAGS=-lgtest -lgtest_main -lpthread

# Files for Project
BUILD_DIR=obj
SOURCES=main.cpp src/SortTape/SortTape.cpp src/Tape/Tape.cpp src/DelayParse/DelayParse.cpp src/ConvertFile/ConvertFile.cpp
OBJECTS=$(patsubst %.cpp, $(BUILD_DIR)/%.o, $(SOURCES))
TARGET=IntTape

# #Files for TestMap
# SOURCES_TEST=TestMap.cpp Compare/Compare.cpp
# OBJECTS_TEST=$(patsubst %.cpp, $(BUILD_DIR)/%.o, $(SOURCES_TEST))
# TARGET_TEST=TestMap

# all: $(TARGET) $(TARGET_TEST)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@

# $(TARGET_TEST): $(OBJECTS_TEST)
# 	$(CC) $(OBJECTS_TEST) $(TFLAGS) -o $@

$(BUILD_DIR)/%.o: %.cpp
	$(CC) $(CFLAGS) $< -o $@

.PHONY: clean

clean:
	@find obj -type f -delete
	@rm $(TARGET)

# clean:
# 	@find obj -type f -delete
# 	@rm $(TARGET)
# 	@rm $(TARGET_TEST)
