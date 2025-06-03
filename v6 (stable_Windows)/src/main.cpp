#include <iostream>
#include <fstream>
#include <limits>
#include <sstream>
#include <cstdint>
#include <locale>
#include <windows.h>

#include "dynamic_loader.h"
#include "utils.h"

// Типы функций для шифрования/дешифрования
using EncryptFunc = std::string(*)(const std::string&, const std::string&);
using DecryptFunc = std::string(*)(const std::string&, const std::string&);

// Указатели на функции Виженера
EncryptFunc vigenereEncryptFunc = nullptr;
DecryptFunc vigenereDecryptFunc = nullptr;

// Типы функций для RSA
using KeyGenFunc = std::tuple<uint64_t, uint64_t, uint64_t>(*)();
using RSAEncryptFunc = std::string(*)(const std::string&, uint64_t, uint64_t);
using RSADecryptFunc = std::string(*)(const std::string&, uint64_t, uint64_t);

// Указатели на функции RSA
KeyGenFunc rsaGenerateKeysFunc = nullptr;
RSAEncryptFunc rsaEncryptFunc = nullptr;
RSADecryptFunc rsaDecryptFunc = nullptr;

// Загрузка библиотек шифрования
#ifdef _WIN32
    const char* gronsfeldPath = "libgronsfeld.dll";
    const char* vigenerePath  = "libvigenere.dll";
    const char* rsaPath       = "librsa.dll";
#else
    const char* gronsfeldPath = "./libgronsfeld.so";
    const char* vigenerePath  = "./libvigenere.so";
    const char* rsaPath       = "./librsa.so";
#endif

void* gronsfeldLib = loadLibrary(gronsfeldPath);
bool gronsfeldAvailable = (gronsfeldLib != nullptr);

void* vigenereLib = loadLibrary(vigenerePath);
bool vigenereAvailable = (vigenereLib != nullptr);

void* rsaLib = loadLibrary(rsaPath);
bool rsaAvailable = (rsaLib != nullptr);

void simulateProcessing();

int main() {
    try {

        SetConsoleOutputCP(CP_UTF8); // для вывода
        SetConsoleCP(CP_UTF8);       // для ввода
        std::locale::global(std::locale(""));

        printAsciiArt(); // Вывод логотипа

        // --------------------------------
        //       1. Защита паролем
        // --------------------------------

        int attempts = 3;
        std::string password;
        bool accessGranted = false;

        while (attempts-- > 0) {
            std::cout << "\nВведите пароль доступа: ";
            std::cin >> password;
            if (password == "123") {
                accessGranted = true;
                break;
            } else {
                std::cout << "Неверный пароль. Осталось попыток: " << attempts << "\n";
            }
        }

        if (!accessGranted) {
            std::cerr << "Доступ заблокирован.\n";
            pauseBeforeExit();
            return 1;
        }

        std::cout << "Доступ разрешён. Добро пожаловать в ENcrypt-DEcrypt!\n";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        // --------------------------------
        //       2. Выбор источника
        // --------------------------------

        std::string input;
        int sourceChoice;
        std::cout << "\nВыберите источник текста:\n1 — Файл\n2 — Ввести вручную\nВаш выбор: ";
        if (!safeInputInt(sourceChoice, "Введите 1 или 2.")) {
            pauseBeforeExit();
            return 1;

        }
        if (sourceChoice != 1 && sourceChoice != 2) {
            std::cerr << "Ошибка: неверный выбор источника.\n";
            pauseBeforeExit();
            return 1;
        }

        if (sourceChoice == 1) {
            std::string filename;
            std::cout << "Введите имя файла (например: input.txt): ";
            std::getline(std::cin, filename);

            std::ifstream inFile(filename);
            if (!inFile) {
                std::cerr << "Ошибка: файл не найден.\n";
                pauseBeforeExit();
                return 1;
            }

            std::ostringstream ss;
            ss << inFile.rdbuf();
            input = ss.str();
            inFile.close();
            std::cout << "Файл успешно прочитан.\n";
        } else {
            std::cout << "Введите текст вручную: ";
            std::getline(std::cin, input);
        }

        // --------------------------------
        //    3. Выбор показа результата
        // --------------------------------

        int showChoice;
        std::cout << "Показать результат на экран? (1 — да, 0 — нет): ";
        if (!safeInputInt(showChoice, "Введите 1 или 0.")) {
            pauseBeforeExit();
            return 1;

        }
        if (showChoice != 0 && showChoice != 1) {
            std::cerr << "Ошибка: введите только 1 (да) или 0 (нет).\n";
            pauseBeforeExit();
            return 1;
        }
        bool showResult = (showChoice == 1);

        // --------------------------------
        //         4. Выбор шифра
        // --------------------------------

        int cipherChoice;
        CipherType cipher;
        bool validCipher = false;

        while (!validCipher) {
            std::cout << "\nВыберите шифр:\n";
            if (gronsfeldAvailable) std::cout << "1 — Гронсфельд\n";
            if (vigenereAvailable)  std::cout << "2 — Виженера\n";
            if (rsaAvailable)       std::cout << "3 — RSA\n";
            std::cout << "Ваш выбор: ";

            if (!safeInputInt(cipherChoice, "Введите номер доступного шифра.")) {
                pauseBeforeExit();
                return 1;
            }
            cipher = static_cast<CipherType>(cipherChoice);

            switch (cipher) {
                case CipherType::Gronsfeld: validCipher = gronsfeldAvailable; break;
                case CipherType::Vigenere:  validCipher = vigenereAvailable; break;
                case CipherType::RSA:       validCipher = rsaAvailable; break;
                default: validCipher = false; break;
            }

            if (!validCipher) {
                std::cerr << "Выбранный модуль недоступен. Пожалуйста, выберите другой.\n";
            } else {
                // Сохранить выбор
                cipher = static_cast<CipherType>(cipherChoice);
                break;
            }
        }

        // --------------------------------
        //       5. Выбор действия
        // --------------------------------

        int actionChoice;
        std::cout << "Выберите действие:\n1 — Зашифровать\n2 — Расшифровать\nВаш выбор: ";
        if (!safeInputInt(actionChoice, "Введите 1 или 2.")) {
            pauseBeforeExit();
            return 1;
        }
        if (actionChoice != 1 && actionChoice != 2) {
            std::cerr << "Ошибка: неверный выбор действия.\n";
            pauseBeforeExit();
            return 1;
        }
        ActionType action = static_cast<ActionType>(actionChoice);

        // --------------------------------
        //         6. Ввод ключа
        // --------------------------------

        std::string key;
        int genChoice;
        std::cout << "Сгенерировать случайный цифровой ключ? (1 — да, 0 — нет): ";
        if (!safeInputInt(genChoice, "Введите 1 или 0.") || (genChoice != 0 && genChoice != 1)) {
            std::cerr << "Ошибка: необходимо ввести 1 (да) или 0 (нет).\n";
            pauseBeforeExit();
            return 1;
        }
        if (genChoice == 1) {
            key = generateRandomNumericKey();
            std::cout << "Сгенерированный ключ: " << key << "\n";
        } else {
            std::cout << "Введите ключ: ";
            std::getline(std::cin, key);
            if (!isNumericKeyValid(key)) {
                std::cerr << "Ошибка: ключ должен содержать только цифры.\n";
                pauseBeforeExit();
                return 1;
            }
        }

        // --------------------------------
        //    7. Визуализация процесса
        // --------------------------------

        int processChoice;
        std::cout << "Показать процесс шифрования? (1 — да, 0 — нет): ";
        if (!safeInputInt(processChoice, "Введите 1 или 0.")) {
            pauseBeforeExit();
            return 1;
        }
        if (processChoice != 0 && processChoice != 1) {
            std::cerr << "Ошибка: введите только 1 или 0.\n";
            pauseBeforeExit();
            return 1;
        }
        bool showProcess = (processChoice == 1);

        // --------------------------------
        //      8. Обработка данных
        // --------------------------------

        std::string output;
        if (showProcess) {
            std::cout << "\n[+] Начат процесс...\n";
            simulateProcessing();
        }

        EncryptFunc gronsfeldEncryptFunc = nullptr;
        DecryptFunc gronsfeldDecryptFunc = nullptr;

        if (!gronsfeldLib) {
            std::cerr << "Модуль шифра Гронсфельда не найден.\n";
        } else {
            gronsfeldEncryptFunc = (EncryptFunc)getFunction(gronsfeldLib, "gronsfeldEncrypt");
            gronsfeldDecryptFunc = (DecryptFunc)getFunction(gronsfeldLib, "gronsfeldDecrypt");
        }

        switch (cipher) {
            case CipherType::Gronsfeld:
                gronsfeldEncryptFunc = (EncryptFunc)getFunction(gronsfeldLib, "gronsfeldEncrypt");
                gronsfeldDecryptFunc = (DecryptFunc)getFunction(gronsfeldLib, "gronsfeldDecrypt");

                if (!gronsfeldEncryptFunc || !gronsfeldDecryptFunc) {
                    std::cerr << "Функции шифрования Гронсфельда не загружены.\n";
                    pauseBeforeExit();
                    return 1;
                }

                output = (action == ActionType::Encrypt)
                ? gronsfeldEncryptFunc(input, key)
                : gronsfeldDecryptFunc(input, key);
                break;

            case CipherType::Vigenere:
                vigenereEncryptFunc = (EncryptFunc)getFunction(vigenereLib, "vigenereEncrypt");
                vigenereDecryptFunc = (DecryptFunc)getFunction(vigenereLib, "vigenereDecrypt");

                if (!vigenereEncryptFunc || !vigenereDecryptFunc) {
                    std::cerr << "Функции шифрования Виженера не загружены.\n";
                    pauseBeforeExit();
                    return 1;
                }

                output = (action == ActionType::Encrypt)
                ? vigenereEncryptFunc(input, key)
                : vigenereDecryptFunc(input, key);
                break;

            case CipherType::RSA: {
                rsaGenerateKeysFunc = (KeyGenFunc)getFunction(rsaLib, "rsaGenerateKeys");
                rsaEncryptFunc = (RSAEncryptFunc)getFunction(rsaLib, "rsaEncrypt");
                rsaDecryptFunc = (RSADecryptFunc)getFunction(rsaLib, "rsaDecrypt");

                if (!rsaGenerateKeysFunc || !rsaEncryptFunc || !rsaDecryptFunc) {
                    std::cerr << "Функции RSA не загружены.\n";
                    pauseBeforeExit();
                    return 1;
                }

                {
                    auto [n, e, d] = rsaGenerateKeysFunc();
                    std::cout << "RSA ключи:\n n = " << n << "\n e = " << e << "\n d = " << d << "\n";

                    output = (action == ActionType::Encrypt)
                    ? rsaEncryptFunc(input, e, n)
                    : rsaDecryptFunc(input, d, n);
                }
                break;
            }

            default:
                std::cerr << "Ошибка: неизвестный шифр.\n";
                pauseBeforeExit();
                return 1;
        }

        // --------------------------------
        //          9. Логирование
        // --------------------------------

        std::string sourceName = (sourceChoice == 1) ? "file" : "manual";
        writeLog(cipher, action, key, sourceName);

        if (showProcess) {
            std::cout << "[+] Исходный текст: " << input << "\n";
            std::cout << "[+] Обработанный текст: " << output << "\n";
            std::cout << "[+] Процесс завершён.\n";
        }

        // --------------------------------
        //   10. Сохраниение результата
        // --------------------------------

        std::ofstream outFile("output.txt");
        outFile << output;
        outFile.close();

        std::cout << "\nРезультат записан в файл output.txt\n";

        if (showResult) {
            std::cout << "\nИтог:\n" << output << "\n";
        }

        pauseBeforeExit();

        // Закрытие библиотек
        if (gronsfeldLib) closeLibrary(gronsfeldLib);
        if (vigenereLib)  closeLibrary(vigenereLib);
        if (rsaLib)       closeLibrary(rsaLib);

    } catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
        pauseBeforeExit();
    }

    return 0;
}
