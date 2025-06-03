#pragma once
#include <string>

// ======================================
//           ШИФР ГРОНСФЕЛЬДА
// ======================================

#ifdef _WIN32
#define DLL_EXPORT extern "C" __declspec(dllexport)
#else
#define DLL_EXPORT extern "C"
#endif

// Шифрует текст методом Гронсфельда
DLL_EXPORT std::string gronsfeldEncrypt(const std::string& text, const std::string& key);

// Дешифрует текст, зашифрованный методом Гронсфельда
DLL_EXPORT std::string gronsfeldDecrypt(const std::string& text, const std::string& key);
