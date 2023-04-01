import codecs
import os
import shutil
import time
from typing import Dict


START_PATH = '.'

BLACK_LIST = ['lab21', 'lab22', 'lab25']

BASIC_USER_LIST = ['Yashin', 'Potapov', 'Tuzova']

TEMPLATE = u'**Поток:** <ins>{thread}</ins>.</br>**Дополнительное задание:** {additional_task}</br></br>' \
    '**Вариант №:** <ins><Ваш номер варинта></ins></br>**Задание:** <Текст задания>'

PATH_TO_TEMPLATE_MAKEFILE = './tools/Makefile'

MD_TITLE_LABS_DESCRIPTIONS: Dict[str, str] = {
    'KP6': u'# Курсовая работа. Задание 6. Реализация базы данных на файлах.\n',
    'KP7': u'# Курсовая работа. Задание 7. Разреженные матрицы.\n',
    'KP8': u'# Курсовая работа. Задание 8. Линейные списки.\n',
    'KP9': u'# Курсовая работа. Задание 9. Сортировка и поиск.\n',
    'lab21': u'# Лабораторная работа № 21. Автоматизация рутинных задач на Bash.\n',
    'lab22': u'# Лабораторная работа № 22. Издательская система LaTeX.\n',
    'lab23': u'# Лабораторная работа № 23. Деревья.\n',
    'lab24': u'# Лабораторная работа № 24. Деревья выражений.\n',
    'lab25': u'# Лабораторная работа № 25. Система сборки проектов make.\n',
    'lab26': u'# Лабораторная работа № 26. Абстрактные типы данных.\n',
}

ADDITIONAL_TASKS = {
    'KP6': u'Реализуйте взаимодействие с таблицей через язык запросов SQL. Необходимо ' \
    'реализовать, чтобы через SQL можно было удалить строки из таблицы, вставить новые, найти нужные, ' \
    'обновлять старые записи. Интерфейс: пользователь через stdin вводит SQL запрос и получает вывод. ' \
    'Если SQL запрос неккоректный, то необходимо вызвать исключение.',
    'KP7': u'Написать бенчмарк сравнения с std::vector.',
    'KP8': u'Написать бенчмарк сравнения с std::list/std::forward_list',
    'KP9': u'Написать бенчмарк сравнения с std::sort',
    'lab21': u'Написать решение задачи ещё и на Python.',
    'lab22': '-',
    'lab23': u'Почитать про AVL-дерево, красно-чёрные дерево, B-дерево, B+ дерево, дерево отрезков.',
    'lab24': '-',
    'lab25': u'Почитать про систему сборки Cmake',
    'lab26': u'Написать бенчмарк сравнения с std::deque/std::stack/std::queue',
}


def generate_mds(path_to_lab: str) -> None:
    lab = os.path.basename(path_to_lab)
    user = path_to_lab.split(os.sep)[-2]
    path_to_readme = os.path.join(path_to_lab, 'README.md')
    if not check_if_need_to_generate(path_to_readme):
        return
    with codecs.open(path_to_readme, 'w', 'utf-16') as file:
        file.write(MD_TITLE_LABS_DESCRIPTIONS.get(lab) + TEMPLATE.format(
            thread='advanced' if user not in BASIC_USER_LIST else 'basic',
            additional_task='-' if user in BASIC_USER_LIST else ADDITIONAL_TASKS.get(lab)
        ))


def generate_makefiles(path_to_lab: str) -> None:
    if os.path.basename(path_to_lab) in BLACK_LIST:
        return
    path_to_makefile = os.path.join(path_to_lab, 'Makefile')
    try:
        os.remove(path_to_makefile)
        os.remove(os.path.join(os.path.dirname(path_to_lab), 'Makefile'))
    except FileNotFoundError:
        pass
    shutil.copyfile(PATH_TO_TEMPLATE_MAKEFILE, path_to_makefile)

def check_if_need_to_generate(path_to_lab: str) -> bool:
    return 'Feb 19' in time.ctime(os.path.getmtime(path_to_lab))

def generate_project_struct(path_to_lab: str) -> None:
    if os.path.basename(path_to_lab) in BLACK_LIST:
        delete_trash_dirs(path_to_lab)
        return
    try:
        os.mkdir(os.path.join(path_to_lab, 'src'))
        open(os.path.join(path_to_lab, 'src', 'delete_me_please=('), 'a+').close()
        os.mkdir(os.path.join(path_to_lab, 'include'))
        open(os.path.join(path_to_lab, 'include', 'delete_me_please=('), 'a+').close()
        os.mkdir(os.path.join(path_to_lab, 'tests'))
        open(os.path.join(path_to_lab, 'tests', 'delete_me_please=('), 'a+').close()
    except FileExistsError:
        pass

def delete_trash_dirs(path_to_lab: str) -> None:
    try:
        os.rmdir(os.path.join(path_to_lab, 'src'))
        os.rmdir(os.path.join(path_to_lab, 'include'))
        os.rmdir(os.path.join(path_to_lab, 'tests'))
    except (FileNotFoundError, OSError):
        pass


def generate_repository() -> None:
    list_of_user = [os.path.join(START_PATH, user) for user in os.listdir(START_PATH) if os.path.isdir(os.path.join(START_PATH, user))]
    print(list_of_user)
    for path_to_user in list_of_user:
        if os.path.basename(path_to_user).startswith('.'):
            continue
        list_labs = [os.path.join(path_to_user, dir) for dir in os.listdir(path_to_user) if os.path.isdir(os.path.join(path_to_user, dir))]
        for path_to_lab in list_labs:
            delete_trash_dirs(path_to_lab)
            generate_mds(path_to_lab)
            generate_makefiles(path_to_lab)
            generate_project_struct(path_to_lab)


def main():
    generate_repository()


main()
