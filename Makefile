CC = g++
CFLAGS = -fdiagnostics-color=always -g -std=c++2a
SRC_DIR = src
INCLUDE_DIR = src/include
LIB_DIR = src/lib
BUILD_DIR = build
BIN_DIR = bin

# Lista de arquivos fonte (exceto arquivos main)
SRCS = $(wildcard $(SRC_DIR)/**/*.cpp)
SRCS := $(filter-out $(wildcard $(SRC_DIR)/*main*.cpp), $(SRCS))

# Lista de arquivos-objeto gerados a partir dos arquivos fonte (exceto arquivos main)
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRCS))

# Nome do executável final
TARGET = $(BIN_DIR)/my_executable.exe

# Nome do arquivo main a ser executado (pode ser passado como argumento para make)
MAIN_FILE = $(SRC_DIR)/aCENARIONOVO.cpp

all: $(TARGET)

$(TARGET): $(OBJS) $(MAIN_FILE)
	$(CC) $(CFLAGS) -o $@ $^ -I$(INCLUDE_DIR) -L$(LIB_DIR) -lmingw32 -lSDL2main -lSDL2

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c -o $@ $<

run:
	./$(TARGET)

clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)

.PHONY: all clean run
