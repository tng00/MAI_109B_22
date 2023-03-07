#!/bin/bash

if [ $# -ne 1 ]; then   # Проверка длины аргумента
        echo "Ошибка: необходимо передать один аргумент - путь к директории"
        echo "Пример: ./script.sh path/to/directory"
        exit 1
fi

if [ ! -d "$1" ]; then  # Проверка является ли аргумент директорией
        echo "Ошибка: \"$1\" не является директорией"
        echo "Правильный формат ввода: path/to/directory"
        exit 1
fi

dir=$1

# Поиск имён файлов по заданному шаблону, получение списка уникальных отсортированных суффиксов
find "$dir" -type f -exec basename {} \; | grep -E ".+\..+" | rev | cut -d . -f 1 | rev | sort | uniq > out

suffixes=$(wc -l < out)      # Подсчёт количества суффиксов

echo "Уникальные суффиксы файлов в каталоге $dir:"
while read line; do
	echo ".$line"
done < out

echo "Всего: $suffixes шт."
rm out
