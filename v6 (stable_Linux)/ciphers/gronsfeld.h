#pragma once
#include <string>

// ======================================
//           ШИФР ГРОНСФЕЛЬДА
// ======================================

extern "C" {
    // Шифрует текст методом Гронсфельда
    std::string gronsfeldEncrypt(const std::string& text, const std::string& key);

    // Дешифрует текст, зашифрованный методом Гронсфельда
    std::string gronsfeldDecrypt(const std::string& text, const std::string& key);
}
