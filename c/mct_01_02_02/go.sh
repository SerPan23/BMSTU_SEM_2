#!/bin/bash

"./build_gcov.sh"

cd ./func_tests/scripts/ || exit 1

./func_tests.sh

cd ../../

"./collect_coverage.sh"
"./clean.sh"