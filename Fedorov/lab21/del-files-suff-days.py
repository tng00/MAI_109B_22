import argparse
from datetime import datetime
import os
import pathlib


def help_message():
    msg = """
    This utility can be used to delete all files with specified suffix
    which has not been accessed specified days quantity
    3 arguments required, check hint below
    Syntax: del-files-suff-days --path path/to/dir --suffix any_suffix --days days_quantity
    Example: del-files-suff-days --path /home/Downloads --suffix .gz --days 10
    --path (or -p) is an absolute path to directory where script will search for files
    --suffix (or -s) is a suffix of a file
    --days (or -d) is a number, which means amount of days file was last accessed.
    """
    return msg


def read_arguments():
    parser = argparse.ArgumentParser(usage=help_message())
    parser.add_argument('-p', '--path', help="Enter an absolute path to directory where script will search for files",
                        required=True)
    parser.add_argument('-s', '--suffix', help="Enter suffix of a file.",
                        required=True)
    parser.add_argument('-d', '--days', help="Enter a number, which means amount of days file was last accessed.",
                        required=True)

    args = parser.parse_args()
    if not os.path.exists(args.path):
        raise Exception("Path doesn't exist.")
    if not str(args.days).isdigit():
        raise Exception("Days quantity is not a number.")
    return args.path, args.suffix, int(args.days)


def del_files_accessed_days_ago(paths, days_quantity):
    for path_to_file in paths:
        last_access_time = path_to_file.stat().st_atime
        diff_btw_dates = datetime.now() - datetime.fromtimestamp(last_access_time)
        # Calc difference and check if file has been accessed "days_quantity" days
        # ago and if yes - delete it
        if diff_btw_dates.days == days_quantity:
            if os.path.isfile(path_to_file):
                os.remove(path_to_file)
                print(path_to_file)
            else:
                print('Path is not a file')


def main():
    path, suffix, days = read_arguments()
    pattern = "*" + suffix
    suitable_paths_to_files = list(pathlib.Path(path).rglob(pattern))
    del_files_accessed_days_ago(suitable_paths_to_files, days)


if __name__ == '__main__':
    main()
