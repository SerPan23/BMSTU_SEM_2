#!/bin/bash

GREEN='\033[0;32m'
OFF_COLOR='\033[0m'


names=$(sed -n "1p" config.ini)
opts=$(sed -n "2p" config.ini)
sizes=$(sed -n "3p" config.ini)

names_count=$((`wc -w <<< "$names"`))
opts_count=$((`wc -w <<< "$opts"`))
sizes_count=$((`wc -w <<< "$sizes"`))

max_count=$(($names_count * $opts_count * $sizes_count))
count=0


for name in $names; do
    for opt in $opts; do
        for size in $sizes; do
            count=$((count + 1))
            build_percent=$((count * 100 / $max_count))

            echo -n -e "\033[2K\rBuilding: $build_percent% ($name"_"$opt"_"$size)"

            gcc -std=c99 -Wall -Werror -Wpedantic -Wextra \
            -DN="$size""ULL" \
            -"$opt" "$name".c -o ./apps/"$name"_"$opt"_"$size".exe
        done
    done
done

echo -e "\033[2K\r${GREEN}Build complete${OFF_COLOR}"