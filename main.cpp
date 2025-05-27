#include <iostream>
#include <fstream>
#include <limits>
#include <sstream>
#include "shifrs.h"
#include "utils.h"

void simulateProcessing();

int main() {
    try {
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
        if (!safeInputInt(sourceChoice, "Введите 1 или 2.")) return 1;
        if (sourceChoice != 1 && sourceChoice != 2) {
            std::cerr << "Ошибка: неверный выбор источника.\n";
            return 1;
        }

        if (sourceChoice == 1) {
            std::string filename;
            std::cout << "Введите имя файла (например: input.txt): ";
            std::getline(std::cin, filename);

            std::ifstream inFile(filename);
            if (!inFile) {
                std::cerr << "Ошибка: файл не найден.\n";
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
        if (!safeInputInt(showChoice, "Введите 1 или 0.")) return 1;
        if (showChoice != 0 && showChoice != 1) {
            std::cerr << "Ошибка: введите только 1 (да) или 0 (нет).\n";
            return 1;
        }
        bool showResult = (showChoice == 1);

        // --------------------------------
        //         4. Выбор шифра
        // --------------------------------

        int cipherChoice;
        std::cout << "Выберите шифр:\n1 — Гронсфельд\n2 — Виженера\n3 — RSA\nВаш выбор: ";
        if (!safeInputInt(cipherChoice, "Введите 1, 2 или 3.")) return 1;
        if (cipherChoice < 1 || cipherChoice > 3) {
            std::cerr << "Ошибка: неверный выбор шифра.\n";
            return 1;
        }
        CipherType cipher = static_cast<CipherType>(cipherChoice);

        // --------------------------------
        //       5. Выбор действия
        // --------------------------------

        int actionChoice;
        std::cout << "Выберите действие:\n1 — Зашифровать\n2 — Расшифровать\nВаш выбор: ";
        if (!safeInputInt(actionChoice, "Введите 1 или 2.")) return 1;
        if (actionChoice != 1 && actionChoice != 2) {
            std::cerr << "Ошибка: неверный выбор действия.\n";
            return 1;
        }
        ActionType action = static_cast<ActionType>(actionChoice);

        // --------------------------------
        //         6. Ввод ключа
        // --------------------------------

        std::string key;
        std::cout << "Введите ключ: ";
        std::getline(std::cin, key);

        // --------------------------------
        //    7. Визуализация процесса
        // --------------------------------

        int processChoice;
        std::cout << "Показать процесс шифрования? (1 — да, 0 — нет): ";
        if (!safeInputInt(processChoice, "Введите 1 или 0.")) return 1;
        if (processChoice != 0 && processChoice != 1) {
            std::cerr << "Ошибка: введите только 1 или 0.\n";
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

        switch (cipher) {
            case CipherType::Gronsfeld:
                output = (action == ActionType::Encrypt)
                ? gronsfeldEncrypt(input, key)
                : gronsfeldDecrypt(input, key);
                break;

            case CipherType::Vigenere:
                output = (action == ActionType::Encrypt)
                ? vigenereEncrypt(input, key)
                : vigenereDecrypt(input, key);
                break;

            case CipherType::RSA: {
                auto [n, e, d] = rsaGenerateKeys();
                std::cout << "RSA ключи:\n n = " << n << "\n e = " << e << "\n d = " << d << "\n";
                output = (action == ActionType::Encrypt)
                ? rsaEncrypt(input, e, n)
                : rsaDecrypt(input, d, n);
                break;
            }

            default:
                std::cerr << "Ошибка: неизвестный шифр.\n";
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

    } catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    }

    return 0;
}
