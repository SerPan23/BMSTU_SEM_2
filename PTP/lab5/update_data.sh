#!/bin/bash

GREEN='\033[0;32m'
OFF_COLOR='\033[0m'


names=$(sed -n "1p" config.ini)
opts=$(sed -n "2p" config.ini)
sizes=$(sed -n "3p" config.ini)

count=1

if [ ! -z "$1" ]; then
    count="$1"
fi

if [ ! -z "$2" ]; then
    sizes="$2"
fi

if [ ! -z "$3" ]; then
    opts="$3"
fi

names_count=$((`wc -w <<< "$names"`))
opts_count=$((`wc -w <<< "$opts"`))
sizes_count=$((`wc -w <<< "$sizes"`))

max_count=$(($names_count * $opts_count * $sizes_count * $count))

progress_count=0

for i in $(seq "$count"); do
    for name in $names; do
        for opt in $opts; do
            for size in $sizes; do
                progress_count=$((progress_count + 1))
                progress_percent=$((progress_count * 100 / $max_count))
                echo -n -e "\033[2K\rPassing $i/$count Progress($progress_percent%) Program: $name| Optimization: $opt | Size: $size"
                ./apps/"$name"_"$opt"_"$size".exe >> ./data/"$name"_"$opt"_"$size".txt
            done
        done
    done
done

echo -e "\033[2K\r${GREEN}Update data completed${OFF_COLOR}"