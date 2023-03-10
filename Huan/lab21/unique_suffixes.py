#!/usr/bin/env python3
import os
import sys
import re


def FindSuffixes(path):
    suffixes = set()
    pattern = r".+\..+$"
    for root, dirs, files in os.walk(path):
        for file in files:
            if re.match(pattern, file):
                suffix = "." + file.split(".")[-1]
                suffixes.add(suffix)
    return suffixes


def main():
    if len(sys.argv) != 2:
        print("Ошибка: необходимо передать один аргумент - путь к директории")
        print("Пример: ./script.py path/to/directory")
        sys.exit(1)

    if not os.path.isdir(sys.argv[1]):
        print(f'Ошибка: "{sys.argv[1]}" не является директорией')
        print("Правильный формат ввода: path/to/directory")
        sys.exit(1)

    dir_path = sys.argv[1]
    suffixes = FindSuffixes(dir_path)

    print(f"Уникальные суффиксы файлов в каталоге {dir_path}:")
    for suffix in sorted(suffixes):
        print(suffix)
    print(f"Всего: {len(suffixes)} шт.")


if __name__ == '__main__':
    main()

