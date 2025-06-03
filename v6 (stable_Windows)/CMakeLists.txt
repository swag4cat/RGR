cmake_minimum_required(VERSION 3.10)
project(ENcryptDecrypt)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Указать пути к исходникам
include_directories(
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/dll_loader
)

# Список исходных файлов
set(SOURCES
    src/main.cpp
    src/utils.cpp
    dll_loader/dynamic_loader_win.cpp
)

# Создать исполняемый файл
add_executable(encrypt_decrypt ${SOURCES})

# Поддержка кириллицы для MinGW
if(MINGW)
    add_definitions(-DUNICODE -D_UNICODE)
endif()

# Шифр Гронсфельда
add_library(gronsfeld SHARED ciphers/gronsfeld.cpp)

# Шифр Виженера
add_library(vigenere SHARED ciphers/vigenere.cpp)

# Шифр RSA
add_library(rsa SHARED ciphers/rsa.cpp)

# Создать пустой input.txt в папке сборки
add_custom_command(
    OUTPUT ${CMAKE_BINARY_DIR}/input.txt
    COMMAND ${CMAKE_COMMAND} -E touch ${CMAKE_BINARY_DIR}/input.txt
    COMMENT "input.txt ready for input"
)

add_custom_target(create_input ALL
    DEPENDS ${CMAKE_BINARY_DIR}/input.txt
)