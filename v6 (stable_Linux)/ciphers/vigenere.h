#pragma once
#include <string>

// ======================================
//           ШИФР ВИЖЕНЕРА
// ======================================

extern "C" {
    // Шифрует текст методом Виженера
    std::string vigenereEncrypt(const std::string& text, const std::string& key);

    // Дешифрует текст, зашифрованный методом Виженера
    std::string vigenereDecrypt(const std::string& text, const std::string& key);
}
