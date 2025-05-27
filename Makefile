# Компилятор и флаги
CXX = g++
CXXFLAGS = -Wall -std=c++17
TARGET = encrypt_decrypt

# Файлы исходного кода
SRC = main.cpp shifrs.cpp
OBJ_DIR = obj
OBJS = $(addprefix $(OBJ_DIR)/, main.o shifrs.o utils.o)

# Основная цель сборки
all: $(OBJ_DIR) $(TARGET)

# Сборка исполняемого файла
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

# Правило для объектных файлов
$(OBJ_DIR)/%.o: %.cpp shifrs.h | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Создание директории для объектных файлов
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Очистка проекта
clean:
	rm -rf $(OBJ_DIR) $(TARGET) output.txt log.txt
