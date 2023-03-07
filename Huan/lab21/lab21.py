#!/usr/bin/env python3
import os
import sys
import re

if len(sys.argv) != 2:	# Проверка количества параметров
    print("Ошибка: необходимо передать один аргумент - путь к директории")
    print("Пример: ./script.py path/to/directory")
    sys.exit(1)

if not os.path.isdir(sys.argv[1]):	# Проверка, является ли аргумент директорией
    print(f'Ошибка: "{sys.argv[1]}" не является директорией')
    print("Правильный формат ввода: path/to/directory")
    sys.exit(1)

dir_path = sys.argv[1]

suffixes = set()
for root, dirs, files in os.walk(dir_path):
    pattern = r".+\..+$"
    for file in files:
        if re.match(pattern, file):		# Поиск имён файлов по заданному шаблону
            suffix = "." + file.split(".")[-1]
            suffixes.add(suffix)

print(f"Уникальные суффиксы файлов в каталоге {dir_path}:")
for suffix in sorted(suffixes):
    print(suffix)

print(f"Всего: {len(suffixes)} шт.")
