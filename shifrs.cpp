#include "shifrs.h"
#include <sstream>

// =============================================
//              ШИФР ГРОНСФЕЛЬДА
// =============================================

std::string gronsfeldEncrypt(const std::string& text, const std::string& key) {
    if (key.empty()) throw std::invalid_argument("Ключ пуст");

    std::string result;
    size_t key_len = key.length();

    for (size_t i = 0; i < text.length(); ++i) {
        char k = key[i % key_len];
        if (!isdigit(k)) throw std::invalid_argument("Ключ должен содержать только положительные цифры");

        unsigned char c = static_cast<unsigned char>(text[i]);
        int shift = k - '0';

        // Применение сдвига
        c = static_cast<unsigned char>((c + shift) % 256);
        result += c;
    }

    return result;
}

std::string gronsfeldDecrypt(const std::string& text, const std::string& key) {
    if (key.empty()) throw std::invalid_argument("Ключ пуст");

    std::string result;
    size_t key_len = key.length();

    for (size_t i = 0; i < text.length(); ++i) {
        char k = key[i % key_len];
        if (!isdigit(k)) throw std::invalid_argument("Ключ должен содержать только цифры");

        unsigned char c = static_cast<unsigned char>(text[i]);
        int shift = k - '0';

        // Обратный сдвиг с защитой от переполнения
        c = static_cast<unsigned char>((c - shift + 256) % 256);
        result += c;
    }

    return result;
}

// =============================================
//               ШИФР ВИЖЕНЕРА
// =============================================

std::string vigenereEncrypt(const std::string& text, const std::string& key) {
    if (key.empty()) throw std::invalid_argument("Ключ пуст");

    std::string result;
    size_t key_len = key.length();

    for (size_t i = 0; i < text.length(); ++i) {
        unsigned char t = static_cast<unsigned char>(text[i]);
        unsigned char k = static_cast<unsigned char>(key[i % key_len]);

        // Сложение символов текста и ключа
        result += static_cast<unsigned char>((t + k) % 256);
    }

    return result;
}

std::string vigenereDecrypt(const std::string& text, const std::string& key) {
    if (key.empty()) throw std::invalid_argument("Ключ пуст");

    std::string result;
    size_t key_len = key.length();

    for (size_t i = 0; i < text.length(); ++i) {
        unsigned char t = static_cast<unsigned char>(text[i]);
        unsigned char k = static_cast<unsigned char>(key[i % key_len]);

        // Вычитание ключа с защитой от переполнения
        result += static_cast<unsigned char>((t - k + 256) % 256);
    }

    return result;
}

// =============================================
//           RSA ВСПОМОГАТЕЛЬНЫЕ ФУНКЦИИ
// =============================================

// Наибольший общий делитель (алгоритм Евклида)
uint64_t gcd(uint64_t a, uint64_t b) {
    while (b != 0) {
        uint64_t t = b;
        b = a % b;
        a = t;
    }
    return a;
}

// Расширенный алгоритм Евклида
uint64_t modInverse(uint64_t a, uint64_t m) {
    int64_t m0 = m, x0 = 0, x1 = 1;
    while (a > 1) {
        int64_t q = a / m;
        int64_t t = m;
        m = a % m, a = t;
        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
    }
    return x1 < 0 ? x1 + m0 : x1;
}

// Быстрое возведение в степень по модулю
uint64_t modPow(uint64_t base, uint64_t exp, uint64_t mod) {
    uint64_t result = 1;
    base %= mod;
    while (exp > 0) {
        if (exp % 2 == 1) result = (result * base) % mod;
        base = (base * base) % mod;
        exp /= 2;
    }
    return result;
}

// =============================================
//           RSA ОСНОВНЫЕ ФУНКЦИИ
// =============================================

std::tuple<uint64_t, uint64_t, uint64_t> rsaGenerateKeys() {
    uint64_t p = 61, q = 53;
    uint64_t n = p * q;
    uint64_t phi = (p - 1) * (q - 1);

    uint64_t e = 17; // должно быть взаимно просто с phi
    while (gcd(e, phi) != 1) ++e;

    uint64_t d = modInverse(e, phi);
    return {n, e, d};
}

std::string rsaEncrypt(const std::string& text, uint64_t e, uint64_t n) {
    std::ostringstream oss;
    for (unsigned char ch : text) {

        // Шифрование каждого символа
        uint64_t c = modPow((uint64_t)ch, e, n);
        oss << c << ' ';
    }
    return oss.str();
}

std::string rsaDecrypt(const std::string& cipher, uint64_t d, uint64_t n) {
    std::istringstream iss(cipher);
    std::string result;
    uint64_t num;

    while (iss >> num) {
        uint64_t m = modPow(num, d, n);

        // Дешифровка
        result += static_cast<char>(m);
    }

    return result;
}
