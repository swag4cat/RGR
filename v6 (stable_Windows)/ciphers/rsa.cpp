#include "rsa.h"
#include <sstream>
#include <stdexcept>

// =============================================
//          RSA ВСПОМОГАТЕЛЬНЫЕ ФУНКЦИИ
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

// Генерирует ключи для RSA алгоритма
std::tuple<uint64_t, uint64_t, uint64_t> rsaGenerateKeys() {
    uint64_t p = 61, q = 53;
    uint64_t n = p * q;
    uint64_t phi = (p - 1) * (q - 1);

    uint64_t e = 17;
    while (gcd(e, phi) != 1) ++e;

    uint64_t d = modInverse(e, phi);
    return {n, e, d};
}

// Шифрует текст алгоритмом RSA
std::string rsaEncrypt(const std::string& text, uint64_t e, uint64_t n) {
    std::ostringstream oss;
    for (unsigned char ch : text) {
        uint64_t c = modPow((uint64_t)ch, e, n);
        oss << c << ' ';
    }
    return oss.str();
}

// Дешифрует текст, зашифрованный алгоритмом RSA
std::string rsaDecrypt(const std::string& cipher, uint64_t d, uint64_t n) {
    std::istringstream iss(cipher);
    std::string result;
    uint64_t num;

    while (iss >> num) {
        uint64_t m = modPow(num, d, n);
        result += static_cast<char>(m);
    }

    return result;
}
