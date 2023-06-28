#!/bin/bash

RED='\033[0;31m'
GREEN='\033[0;32m'
OFF_COLOR='\033[0m'

# количество ошибочных тестов
count_errors=0
pos=0
neg=0

# Коды ошибок
test_p="0"
test_f="1"

# обработка позитивных тестов
files="../data/pos_??_in.txt"
for file_in in $files; do

	# находим номер теста
	number=$(echo "$file_in" | grep -o "[0-9]*")

	# проверка на наличие тестов
	if [ -z "$number" ]; then
		break
	fi

	pos=1

	# названия выходного тестового файла
	file_out="../data/pos_""$number""_out.txt"

	# названия аргументов тестового файла
	file_args="../data/pos_""$number""_args.txt"

	# если выходной файл существует, передаем входной и выходной файлы 
	# в pos_case.sh
	# если не существует, то считаем тест проваленным и переходим к
	# следующему тесту

	if [ -f "$file_out" ]; then
		if [ -f "$file_args" ]; then
			command="./pos_case.sh ""$file_in ""$file_out ""$file_args"
		else
			command="./pos_case.sh ""$file_in ""$file_out"
		fi
	else
		echo -e "POS_""$number"": ${RED}FAILED${OFF_COLOR}"
		count_errors=$((count_errors + 1))
		continue
	fi

	$command
	error="$?"

	# выводим результат в соответствии с кодом ошибки ./pos_case.sh
	if [ "$error" -eq "$test_p" ]; then
		echo -e "POS_""$number"": ${GREEN}PASSED${OFF_COLOR}"
	fi
	if [ "$error" -eq "$test_f" ]; then
		echo -e "POS_""$number"": ${RED}FAILED${OFF_COLOR}"
		count_errors=$((count_errors + 1))
	fi
done

# обработка негативных тестов 
files="../data/neg_??_in.txt"
for file_in in $files; do

	# находим номер теста
	number=$(echo "$file_in" | grep -o "[0-9]*")

	# проверка на наличие тестов
	if [ -z "$number" ]; then
		break
	fi

	neg=1

	# названия выходного тестового файла
	file_out="../data/neg_""$number""_out.txt"

	# названия аргументов тестового файла
	file_args="../data/pos_""$number""_args.txt"


	# если выходной файл существует, передаем входной и выходной файлы 
	# в neg_case.sh
	# если не существует, то передаем только входной

	if [ -f "$file_out" ]; then
		if [ -f "$file_args" ]; then
			command="./pos_case.sh ""$file_in ""$file_out ""$file_args"
		else
			command="./pos_case.sh ""$file_in ""$file_out"
		fi
	else
		command="./neg_case.sh ""$file_in"
	fi
	

	
	$command
	error="$?"

	# выводим результат в соответствии с кодом ошибки ./neg_case.sh
	if [ "$error" -eq "$test_p" ]; then
		echo -e "NEG_""$number"": ${GREEN}PASSED${OFF_COLOR}"
	fi
	if [ "$error" -eq "$test_f" ]; then
		echo -e "NEG_""$number"": ${RED}FAILED${OFF_COLOR}"
		count_errors=$((count_errors + 1))
	fi
done

# вспомогательная информация

if [ "$count_errors" -eq 0 ]; then
	echo "All tests passed." 
else
	echo "Failed $count_errors tests." 
fi

if [ "$pos" -eq 0 ]; then
	echo "No positive tests." 
fi

if [ "$neg" -eq 0 ]; then 
	echo "No negative tests."
fi

exit "$count_errors"