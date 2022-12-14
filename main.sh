#!/usr/bin/env bash
src="vector-atomic-access"
out="/home/resources/Documents/subhajit/$src.log"
ulimit -s unlimited
printf "" > "$out"

# Download program
rm -rf $src
git clone https://github.com/puzzlef/$src
cd $src

# Run
g++ -std=c++17 -O3 -latomic -fopenmp main.cxx
stdbuf --output=L ./a.out 2>&1 | tee -a "$out"
