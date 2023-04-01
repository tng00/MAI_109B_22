import os
import re
import sys
import argparse

def RemoveTargetFiles(dir_list, prefix, min_name_len, max_name_len):
    files_to_delete_count = 0
    if min_name_len - len(prefix) < 1:
        min_name_len = 1
    for _address, _directories, _files in dir_list:
        for _file in _files:
            match = re.fullmatch(
                "{pr}.{{{mn},{mx}}}".format(
                    pr = prefix,
                    mn = min_name_len-len(prefix) if min_name_len > len(prefix) else 0,
                    mx = max_name_len-len(prefix)),
                _file)
            if match == None:
                continue
            if match.group() == "files_remover.py":
                continue
            os.remove(_address + "/" +  match.group())
            files_to_delete_count += 1
    print("Deleted " + str(files_to_delete_count) + " files.")

def GetArgs():
    parser = argparse.ArgumentParser(description = 'File remover')
    parser.add_argument(
        '-p',
        '--prefix',
        type = str,
        help = 'provide prefix'
    )
    parser.add_argument(
        '-m',
        '--minlen',
        type = int,
        help = 'Provide minimal file name.'
    )
    parser.add_argument(
        '-M',
        '--maxlen',
        type = int,
        help = 'Provide maximal file name. Must be greater or equal than prefix'
    )
    args = parser.parse_args()
    return (args.prefix, args.minlen, args.maxlen)

def main():
    
    prefix, min_name_len, max_name_len = GetArgs()
    dir_list = list(os.walk(".", topdown = True, onerror = None, followlinks = False))
    
    if len(prefix) > int(max_name_len):
        sys.exit("ERROR: The prefix if bigger than acceptable file name length")
        
    RemoveTargetFiles(dir_list, prefix, min_name_len, max_name_len)


if __name__ == '__main__':
    main()
