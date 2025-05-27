#pragma once

#include <string>
#include <tuple>

#include <stdint.h>

// =============================================
//              ШИФР ГРОНСФЕЛЬДА
// =============================================

// Шифрует текст методом Гронсфельда
std::string gronsfeldEncrypt(const std::string& text, const std::string& key);

// Дешифрует текст, зашифрованный методом Гронсфельда
std::string gronsfeldDecrypt(const std::string& text, const std::string& key);

// =============================================
//               ШИФР ВИЖЕНЕРА
// =============================================

// Шифрует текст методом Виженера
std::string vigenereEncrypt(const std::string& text, const std::string& key);

// Дешифрует текст, зашифрованный методом Виженера
std::string vigenereDecrypt(const std::string& text, const std::string& key);

// =============================================
//              RSA ШИФРОВАНИЕ
// =============================================

// Генерирует ключи для RSA шифрования
std::tuple<uint64_t, uint64_t, uint64_t> rsaGenerateKeys();

// Шифрует текст методом RSA
std::string rsaEncrypt(const std::string& text, uint64_t e, uint64_t n);

// Дешифрует текст, зашифрованный методом RSA
std::string rsaDecrypt(const std::string& cipher, uint64_t d, uint64_t n);
