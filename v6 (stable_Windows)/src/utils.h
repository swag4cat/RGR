#pragma once

#include <string>

// =============================================
//               ТИПЫ ДАННЫХ
// =============================================

// Типы шифров
enum class CipherType {
    Gronsfeld = 1,
    Vigenere = 2,
    RSA = 3
};

// Типы выполняемых действий
enum class ActionType {
    Encrypt = 1,
    Decrypt = 2
};

// =============================================
//           ВСПОМОГАТЕЛЬНЫЕ ФУНКЦИИ
// =============================================

// --------------------------------
//       Визуальные эффекты
// --------------------------------

// Выводит ASCII-арт логотипа программы
void printAsciiArt();

// Имитирует процесс обработки
void simulateProcessing();

// --------------------------------
//  Логирование и безопасный ввод
// --------------------------------

// Записывает лог операции в файл журнала
void writeLog(CipherType cipher, ActionType action, const std::string& key, const std::string& sourceName);

// Безопасно читает целое число из ввода
bool safeInputInt(int& var, const std::string& errorMsg);

// Ожидает нажатия Enter для завершения работы
void pauseBeforeExit();

// Генерация рандомного числового ключа
std::string generateRandomNumericKey(size_t length = 16);

// Проверка правильности ключа
bool isNumericKeyValid(const std::string& key);
