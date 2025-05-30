#include <iostream>
#include <fstream>
#include <thread>
#include <limits>

#include "utils.h"

// Вывод ASCII-арта
void printAsciiArt() {
    std::cout << " _____                                                                                        _____ \n";
    std::cout << "( ___ )                                                                                      ( ___ )\n";
    std::cout << " |   |~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|   | \n";
    std::cout << " |   |  _____ _   _                       _             ____  _____                      _    |   | \n";
    std::cout << " |   | | ____| \\ | | ___ _ __ _   _ _ __ | |_          |  _ \\| ____|___ _ __ _   _ _ __ | |_  |   | \n";
    std::cout << " |   | |  _| |  \\| |/ __| '__| | | | '_ \\| __|  _____  | | | |  _| / __| '__| | | | '_ \\| __| |   | \n";
    std::cout << " |   | | |___| |\\  | (__| |  | |_| | |_) | |_  |_____| | |_| | |__| (__| |  | |_| | |_) | |_  |   | \n";
    std::cout << " |   | |_____|_| \\_|\\___|_|   \\__, | .__/ \\__|         |____/|_____\\___|_|   \\__, | .__/ \\__| |   | \n";
    std::cout << " |   |                        |___/|_|                                       |___/|_|         |   | \n";
    std::cout << " |___|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|___| \n";
    std::cout << "(_____)                                                                                      (_____)\n";
}

// Анимация процесса обработки
void simulateProcessing() {
    std::cout << "\n[+] Процесс шифрования";
    for (int i = 0; i < 3; ++i) {
        std::cout << ".";
        std::cout.flush();
        std::this_thread::sleep_for(std::chrono::milliseconds(600));
    }
    std::cout << " Готово!\n";
};

// Логирование операций шифрования/дешифрования
void writeLog(CipherType cipher, ActionType action, const std::string& key, const std::string& sourceName) {
    std::ofstream log("log.txt", std::ios::app);
    if (!log.is_open()) return;

    // Форматирование времени
    std::time_t now = std::time(nullptr);
    char timebuf[100];
    std::strftime(timebuf, sizeof(timebuf), "%d.%m.%Y %H:%M:%S", std::localtime(&now));

    // Определение названия шифра
    std::string cipherName;
    switch (cipher) {
        case CipherType::Gronsfeld: cipherName = "Gronsfeld"; break;
        case CipherType::Vigenere:  cipherName = "Vigenere"; break;
        case CipherType::RSA:       cipherName = "RSA"; break;
        default:                    cipherName = "Unknown"; break;
    }

    std::string actionName = (action == ActionType::Encrypt) ? "Encrypt" : "Decrypt";

    // Запись в лог
    log << "[Time: " << timebuf << "] "
    << "[Cipher: " << cipherName << "] "
    << "[Action: " << actionName << "] "
    << "[Source: " << sourceName << "] "
    << "[Key: " << key << "]\n";

    log.close();
}

// Безопасный ввод числа
bool safeInputInt(int& var, const std::string& errorMsg) {
    if (!(std::cin >> var)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ← УДАЛИТЬ ЭТО
        std::cerr << "Ошибка: " << errorMsg << "\n";
        return false;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ← И ЭТО ТОЖЕ
    return true;
}

// Ожидает нажатия Enter для завершения работы
void pauseBeforeExit() {
    std::cin.clear(); // сброс флагов ошибок
    std::cout << "\nНажмите Enter для выхода...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // удалить '\n' от предыдущего ввода
    std::cin.get(); // теперь точно дождётся нового нажатия Enter
}
