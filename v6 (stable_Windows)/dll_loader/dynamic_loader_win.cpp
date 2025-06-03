#include <iostream>
#include <string>

#ifdef _WIN32
#include <windows.h>
#endif
#include "dynamic_loader.h"

// Загрузка DLL и настройка консоли под UTF-8
void* loadLibrary(const std::string& name) {
    HMODULE lib = LoadLibraryA(name.c_str());

    SetConsoleOutputCP(CP_UTF8); // UTF-8 для вывода
    SetConsoleCP(CP_UTF8); // UTF-8 для ввода
    std::locale::global(std::locale("")); // Локализация

    if (!lib) {
        std::cerr << "Не удалось загрузить DLL: " << name
                  << " (ошибка " << GetLastError() << ")\n";
    }
    return lib;
}

// Получение указателя на функцию из DLL
void* getFunction(void* library, const std::string& name) {
    return reinterpret_cast<void*>(GetProcAddress(static_cast<HMODULE>(library), name.c_str()));
}

// Выгрузка DLL из памяти
void closeLibrary(void* library) {
    FreeLibrary(static_cast<HMODULE>(library));
}
