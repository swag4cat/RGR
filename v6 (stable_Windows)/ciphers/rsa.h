#pragma once
#include <string>
#include <tuple>
#include <stdint.h>

#ifdef _WIN32
#define DLL_EXPORT extern "C" __declspec(dllexport)
#else
#define DLL_EXPORT extern "C"
#endif

// ======================================
//           RSA ШИФРОВАНИЕ
// ======================================

// Генерирует ключи для RSA алгоритма
DLL_EXPORT std::tuple<uint64_t, uint64_t, uint64_t> rsaGenerateKeys();

// Шифрует текст алгоритмом RSA
DLL_EXPORT std::string rsaEncrypt(const std::string& text, uint64_t e, uint64_t n);

// Дешифрует текст, зашифрованный алгоритмом RSA
DLL_EXPORT std::string rsaDecrypt(const std::string& cipher, uint64_t d, uint64_t n);
