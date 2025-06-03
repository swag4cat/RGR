#pragma once
#include <string>

#ifdef _WIN32
#define DLL_EXPORT extern "C" __declspec(dllexport)
#else
#define DLL_EXPORT extern "C"
#endif

// ======================================
//           ШИФР ВИЖЕНЕРА
// ======================================

// Шифрует текст методом Виженера
DLL_EXPORT std::string vigenereEncrypt(const std::string& text, const std::string& key);

// Дешифрует текст, зашифрованный методом Виженера
DLL_EXPORT std::string vigenereDecrypt(const std::string& text, const std::string& key);
