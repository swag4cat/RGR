@echo off
chcp 65001 > nul
title Сборка проекта ENcrypt-DEcrypt

echo [*] Создание каталога build...
if not exist build (
    mkdir build
)

cd build

echo [*] Запуск CMake...
cmake -G "MinGW Makefiles" ..

if %errorlevel% neq 0 (
    echo [!] CMake завершился с ошибкой.
    pause
    exit /b %errorlevel%
)

echo [*] Сборка проекта...
mingw32-make

if %errorlevel% neq 0 (
    echo [!] Сборка завершилась с ошибкой.
    pause
    exit /b %errorlevel%
)

echo [✓] Сборка завершена успешно!
pause
