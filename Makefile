CXX = g++
CC = gcc
CXXFLAGS = -Wall -Wextra -std=c++11 -Iinclude/cpp -Iinclude/c -Iinclude/shared_lib/cpp -Iinclude/shared_lib/c -D_LINUX
CFLAGS = -Wall -Wextra -std=c11 -Iinclude/c -Iinclude/shared_lib/c

LDFLAGS = -lstdc++

SRC_DIR = src
CPP_SRC_DIR = $(SRC_DIR)/cpp
C_SRC_DIR = $(SRC_DIR)/c
SHARED_LIB_DIR = $(SRC_DIR)/shared_lib
BUILD_DIR = build
BIN_DIR = bin

CPP_SOURCES = $(CPP_SRC_DIR)/main.cc $(CPP_SRC_DIR)/account_manager.cc $(CPP_SRC_DIR)/account.cc \
              $(CPP_SRC_DIR)/database.cc $(CPP_SRC_DIR)/logger.cc $(CPP_SRC_DIR)/transaction.cc \
              $(SHARED_LIB_DIR)/cpp/shared_transaction.cc

C_SOURCES = $(C_SRC_DIR)/utils.c $(C_SRC_DIR)/security.c \
            $(SHARED_LIB_DIR)/c/shared_utils.c

CPP_OBJECTS = $(CPP_SOURCES:$(SRC_DIR)/%.cc=$(BUILD_DIR)/%.o)
C_OBJECTS = $(C_SOURCES:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

TARGET = $(BIN_DIR)/transaction_system

all: setup $(TARGET)

setup:
	@mkdir -p $(BUILD_DIR) $(BIN_DIR)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cc
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(CPP_OBJECTS) $(C_OBJECTS)
	$(CXX) $(CPP_OBJECTS) $(C_OBJECTS) $(LDFLAGS) -o $(TARGET)

clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)

run: all
	$(TARGET)
