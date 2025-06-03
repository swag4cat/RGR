#!/bin/bash

set -e  # Завершать при ошибке

# Определяем путь до рабочего стола
DESKTOP_DIR=$(xdg-user-dir DESKTOP)
DEST="$DESKTOP_DIR/ENcrypt-DEcrypt"
DESKTOP_FILE="$DESKTOP_DIR/ENcrypt-DEcrypt.desktop"

echo "[+] Установка ENcrypt-DEcrypt..."

# Проверка наличия собранных файлов
if [ ! -f build/encrypt_decrypt ]; then
    echo "Ошибка: файл build/encrypt_decrypt не найден."
    echo "Сначала выполните 'make' для сборки проекта."
    exit 1
fi

for lib in libgronsfeld.so libvigenere.so librsa.so; do
    if [ ! -f build/$lib ]; then
        echo "Ошибка: отсутствует библиотека build/$lib"
        echo "Убедитесь, что сборка завершена успешно."
        exit 1
    fi
done

# Удаляем старую версию (если есть)
rm -rf "$DEST"
rm -f "$DESKTOP_FILE"

# Копируем всю папку build на рабочий стол
cp -r build "$DEST"

# Создаём скрипт запуска внутри директории
echo "#!/bin/bash
cd \"\$(dirname \"\$0\")\"
./encrypt_decrypt
" > "$DEST/run.sh"
chmod +x "$DEST/run.sh"

# Создаём .desktop ярлык
echo "[Desktop Entry]
Name=ENcrypt-DEcrypt
Comment=Шифрование и дешифрование файлов
Exec=$DEST/run.sh
Icon=utilities-terminal
Terminal=true
Type=Application
Categories=Utility;" > "$DESKTOP_FILE"
chmod +x "$DESKTOP_FILE"

echo "[✓] Установка завершена!"
echo "Папка: $DEST"
echo "Ярлык: $DESKTOP_FILE"
echo "Дважды кликните по ярлыку для запуска программы."
