#!/bin/bash

# проверка количества аргументов
if [ $# -lt 2 ]; then
	exit 1
fi

in_test=$1
out_test=$2
args_test=$3
bin_out_prog="out.bin"
out_prog="out_b.txt"
command="../../app.exe"
t2b="./t2b.exe"
b2t="./b2t.exe"

# Коды ошибок
test_p="0"
test_f="1"

$t2b "$in_test"

len=${#in_test} 
new_len=$((len - 4))
	
bin_in_test="${in_test:0:new_len}.bin"

programm_arg="$(sed -n "1p" "$args_test")"
command="$command $programm_arg $bin_in_test "

if [ "$programm_arg" == "ab" ]; then
	$command < "$(sed -n "2p" "$args_test")" > "$bin_out_prog"
	error="$?"
	out_prog="${in_test:0:new_len}_b.txt"
	$b2t "$bin_in_test"
else
	if [ "$programm_arg" == "fb" ]; then
		$command "$(sed -n "2p" "$args_test")" > "$out_prog"
		error="$?"
	else
		$command "$bin_out_prog"
		error="$?"
		$b2t "$bin_out_prog"
	fi
fi

# проверка завершения программы
if ! [ "$error" -eq 0 ]; then							# не нулевой код ошибки
	exit "$test_f"
fi

# сравниваем выходные данные программы и данные в тесте
if ! ./comparator.sh "$out_prog" "$out_test"; then		# неверный тест
	exit "$test_f"
else													# верный тест
	exit "$test_p"
fi