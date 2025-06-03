#include "gronsfeld.h"
#include <stdexcept>
#include <cctype>

// ======================================
//           ШИФР ГРОНСФЕЛЬДА
// ======================================

// Шифрует текст методом Гронсфельда
std::string gronsfeldEncrypt(const std::string& text, const std::string& key) {
    if (key.empty()) throw std::invalid_argument("Ключ пуст");

    std::string result;
    size_t key_len = key.length();

    for (size_t i = 0; i < text.length(); ++i) {
        char k = key[i % key_len];
        if (!isdigit(k)) throw std::invalid_argument("Ключ должен содержать только положительные цифры");

        unsigned char c = static_cast<unsigned char>(text[i]);
        int shift = k - '0';

        c = static_cast<unsigned char>((c + shift) % 256);
        result += c;
    }

    return result;
}

// Дешифрует текст, зашифрованный методом Гронсфельда
 std::string gronsfeldDecrypt(const std::string& text, const std::string& key) {
    if (key.empty()) throw std::invalid_argument("Ключ пуст");

    std::string result;
    size_t key_len = key.length();

    for (size_t i = 0; i < text.length(); ++i) {
        char k = key[i % key_len];
        if (!isdigit(k)) throw std::invalid_argument("Ключ должен содержать только цифры");

        unsigned char c = static_cast<unsigned char>(text[i]);
        int shift = k - '0';

        c = static_cast<unsigned char>((c - shift + 256) % 256);
        result += c;
    }

    return result;
}
