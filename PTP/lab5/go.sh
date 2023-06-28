#!/bin/bash

mkdir apps
mkdir data
mkdir preproc_data
mkdir postproc_data

./build_apps.sh
./update_data.sh 2000

python3 make_preproc.py
python3 make_postproc.py

