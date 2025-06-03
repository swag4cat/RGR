#include "vigenere.h"
#include <stdexcept>

extern "C" {

    // ======================================
    //           ШИФР ВИЖЕНЕРА
    // ======================================

    // Шифрует текст методом Виженера
    std::string vigenereEncrypt(const std::string& text, const std::string& key) {
        if (key.empty()) throw std::invalid_argument("Ключ пуст");

        std::string result;
        size_t key_len = key.length();

        for (size_t i = 0; i < text.length(); ++i) {
            unsigned char t = static_cast<unsigned char>(text[i]);
            unsigned char k = static_cast<unsigned char>(key[i % key_len]);
            result += static_cast<unsigned char>((t + k) % 256);
        }

        return result;
    }

    // Дешифрует текст, зашифрованный методом Виженера
    std::string vigenereDecrypt(const std::string& text, const std::string& key) {
        if (key.empty()) throw std::invalid_argument("Ключ пуст");

        std::string result;
        size_t key_len = key.length();

        for (size_t i = 0; i < text.length(); ++i) {
            unsigned char t = static_cast<unsigned char>(text[i]);
            unsigned char k = static_cast<unsigned char>(key[i % key_len]);
            result += static_cast<unsigned char>((t - k + 256) % 256);
        }

        return result;
    }

}
