# Компилятор и флаги
CXX = g++
CXXFLAGS = -Wall -std=c++17 -fPIC

# Каталоги
SRC_DIR := src
CIPHER_DIR := ciphers
BUILD_DIR := build
OBJ_DIR := obj

# Цель и библиотеки
TARGET := $(BUILD_DIR)/encrypt_decrypt
LIBS := $(BUILD_DIR)/libgronsfeld.so $(BUILD_DIR)/libvigenere.so $(BUILD_DIR)/librsa.so
INPUT_FILE := $(BUILD_DIR)/input.txt

# Объектные файлы
OBJS := $(OBJ_DIR)/main.o $(OBJ_DIR)/utils.o

# Цель по умолчанию
all: $(BUILD_DIR) $(OBJ_DIR) $(TARGET) $(LIBS) $(INPUT_FILE)

# Создание input.txt
$(INPUT_FILE):
	touch $@
	@echo "Файл input.txt создан в папке build"

# Сборка исполняемого файла
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ -ldl

# Сборка объектных файлов
$(OBJ_DIR)/main.o: $(SRC_DIR)/main.cpp $(SRC_DIR)/utils.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR)/utils.o: $(SRC_DIR)/utils.cpp $(SRC_DIR)/utils.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Сборка .so библиотек
$(BUILD_DIR)/libgronsfeld.so: $(CIPHER_DIR)/gronsfeld.cpp $(CIPHER_DIR)/gronsfeld.h
	$(CXX) $(CXXFLAGS) -shared -o $@ $<

$(BUILD_DIR)/libvigenere.so: $(CIPHER_DIR)/vigenere.cpp $(CIPHER_DIR)/vigenere.h
	$(CXX) $(CXXFLAGS) -shared -o $@ $<

$(BUILD_DIR)/librsa.so: $(CIPHER_DIR)/rsa.cpp $(CIPHER_DIR)/rsa.h
	$(CXX) $(CXXFLAGS) -shared -o $@ $<

# Создание директорий
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Очистка
clean:
	rm -rf $(OBJ_DIR) $(BUILD_DIR)
