#pragma once
#include <string>

#ifdef _WIN32
#include <windows.h>
#endif

// Загрузка библиотеки по пути
void* loadLibrary(const std::string& path);

// Получение указателя на функцию из библиотеки
void* getFunction(void* library, const std::string& name);

// Закрытие библиотеки
void  closeLibrary(void* library);