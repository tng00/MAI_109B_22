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

echo "Уникальные суффиксы файлов в каталоге $dir:"

suffixes=0

# Поиск имён файлов по заданному шаблону, получение списка уникальных отсортированных суффиксов
for file in $(find "$dir" -type f -exec basename {} \; | grep -E ".+\..+" | rev | cut -d . -f 1 | rev | sort | uniq) 
	do
	echo ".$file"
	suffixes=$(($suffixes+1))
	done

echo "Всего: $suffixes шт."

