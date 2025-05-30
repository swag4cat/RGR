#!/bin/bash

DESKTOP_DIR=$(xdg-user-dir DESKTOP)
DEST="$DESKTOP_DIR/ENcrypt-DEcrypt"
DESKTOP_FILE="$DESKTOP_DIR/ENcrypt-DEcrypt.desktop"

echo "[×] Удаление ENcrypt-DEcrypt..."

# Флаг для отслеживания, было ли что-то удалено
deleted_any=false

# Удаление директории
if [ -d "$DEST" ]; then
    rm -rf "$DEST"
    echo "Папка удалена: $DEST"
    deleted_any=true
else
    echo "Папка не найдена: $DEST"
fi

# Удаление ярлыка
if [ -f "$DESKTOP_FILE" ]; then
    rm -f "$DESKTOP_FILE"
    echo "Ярлык удалён: $DESKTOP_FILE"
    deleted_any=true
else
    echo "Ярлык не найден: $DESKTOP_FILE"
fi

# Итог
if [ "$deleted_any" = true ]; then
    echo "[✓] Удаление завершено."
else
    echo "[!] Нечего удалять — программа, похоже, не была установлена."
fi
