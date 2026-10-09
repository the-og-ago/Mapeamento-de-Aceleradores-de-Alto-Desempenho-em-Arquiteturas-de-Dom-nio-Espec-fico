# Compilador e Flags
CXX      := g++
CXXFLAGS := -std=c++17 -O3 -Wall -Wextra -Iinclude

# Diretórios
SRC_DIR   := src
BUILD_DIR := build
BIN_DIR   := bin

# Nome do executável final
TARGET := $(BIN_DIR)/cart_app

# Deteta automaticamente todos os ficheiros .cpp na pasta src/
SRCS := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(SRCS:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)

# Regra principal
all: $(TARGET)

# Cria o executável combinando os ficheiros objeto (.o)
$(TARGET): $(OBJS) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Compila cada ficheiro .cpp individualmente para um .o dentro de build/
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Criação das pastas auxiliares caso não existam
$(BUILD_DIR) $(BIN_DIR):
	mkdir -p $@

# Atalho para compilar e executar o programa de seguida
run: all
	./$(TARGET)

# Limpeza dos ficheiros de compilação
clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)

.PHONY: all clean run