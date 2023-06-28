#!/bin/bash

mkdir apps
mkdir data
mkdir preproc_data
mkdir postproc_data
mkdir postproc_data/1
mkdir postproc_data/2
mkdir postproc_data/3
mkdir postproc_data/4

./build_apps.sh
./update_data.sh 100

python3 make_preproc.py
python3 make_postproc.py

