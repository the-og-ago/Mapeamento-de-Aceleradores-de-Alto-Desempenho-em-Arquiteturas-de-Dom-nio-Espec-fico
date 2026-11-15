# Compiladores e Flags
CXX       := g++
CXXFLAGS  := -std=c++17 -O3 -Wall -Wextra -Iinclude

NVCC      := nvcc
NVCCFLAGS := -O3 -Iinclude -I.

# Diretórios
SRC_DIR   := src
BUILD_DIR := build
BIN_DIR   := bin

# Executáveis e ficheiro gerado
TARGET     := $(BIN_DIR)/cart_app
GPU_TARGET := $(BIN_DIR)/avaliador_gpu
GENERATED  := arvore_gerada.cu

# Deteta automaticamente todos os ficheiros .cpp na pasta src/
SRCS := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(SRCS:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)

# Regra principal (deve ser sempre a primeira)
all: $(TARGET)

# Cria o executável C++ combinando os ficheiros objeto (.o)
$(TARGET): $(OBJS) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Compila cada ficheiro .cpp individualmente para um .o dentro de build/
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Gera o kernel CUDA executando o programa C++
$(GENERATED): $(TARGET)
	./$(TARGET)

# Compila o avaliador CUDA (garante que arvore_gerada.cu já foi criado)
gpu: $(GPU_TARGET)

$(GPU_TARGET): $(SRC_DIR)/avaliador.cu $(SRC_DIR)/gerador.cpp $(GENERATED) | $(BIN_DIR)
	$(NVCC) $(NVCCFLAGS) $(SRC_DIR)/avaliador.cu $(SRC_DIR)/gerador.cpp -o $@

# Criação das pastas auxiliares caso não existam
$(BUILD_DIR) $(BIN_DIR):
	mkdir -p $@

# Atalhos de execução
run: $(GENERATED)

run-gpu: gpu
	./$(GPU_TARGET)

# Limpeza dos ficheiros de compilação e do kernel gerado
clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR) $(GENERATED)

.PHONY: all clean run gpu run-gpu