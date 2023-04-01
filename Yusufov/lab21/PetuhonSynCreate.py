import os
import argparse

# The function accepts and returns the specified suffix.
def get_args():
    ParserSuf = argparse.ArgumentParser(description = "Suffix")
    ParserSuf.add_argument("--suffix", "-s", type = str, help = "Suffix of file")
    args = ParserSuf.parse_args()
    return args

def get_files():
    files = os.listdir()
    filtered_files = [f for f in files if f.endswith(get_args().suffix) and os.stat(f).st_nlink <= 1]
    return filtered_files

def create_symlink(suffix: str) -> None:
    for file in get_files():
        suffix_without_dot = suffix[1:]
        filename_without_suffix = file.replace(suffix, "")
        new_name = suffix_without_dot + filename_without_suffix
        os.symlink(file, new_name)

def main():
    args = get_args()
    create_symlink(args.suffix)

if __name__ =='__main__':
    main()