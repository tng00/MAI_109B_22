#!/bin/bash

prefix=""
min_name_len=0
max_name_len=0
while getopts ":p:m:M:" ARG; do
    case "$ARG" in
 p) prefix=$OPTARG ;;
 m) min_name_len=$OPTARG ;;
 M) max_name_len=$OPTARG ;;
    esac
done
if [ ${#prefix} -gt $max_name_len ]
then
    echo "ERROR: The prefix is bigger than acceptable file name length";
    exit 1;
fi

files_to_delete_count=`find . -name "$prefix*" -not -name 'files_remover.bash'|
    grep -x -E "[[:print:]]*/[[:print:]]{$min_name_len,$max_name_len}" |
    wc -w`
find . -name "$prefix*" -not -name 'files_remover.bash' |
    grep -x -E "[[:print:]]*/[[:print:]]{$min_name_len,$max_name_len}" |
    xargs rm
echo "Deleted $files_to_delete_count files"
