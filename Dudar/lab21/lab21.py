import os, sys


def len_cheker():
    if not len(sys.argv) == 2:
        print("Use: {} <directory>".format(sys.argv[0]))
        sys.exit(1)


def correkt_path_cheker():
    if not os.path.isdir(sys.argv[1]):
        print("Err: {} is not a directory".format(sys.argv[1]))
        sys.exit(1)


def dirpath_walk(dir_path):
    for dirpath, dirnames, _ in os.walk(dir_path):
        for dirname in dirnames:
            subdir_path = os.path.join(dirpath, dirname)
            print(subdir_path)


def main():
    len_cheker()
    correkt_path_cheker()
    dir_path = sys.argv[1]
    dirpath_walk(dir_path)


if __name__ == "__main__":
    main()
