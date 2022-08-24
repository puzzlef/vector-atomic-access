#!/usr/bin/env bash
src="sum-openmp-adjust-schedule"
out="/home/resources/Documents/subhajit/$src.log"
ulimit -s unlimited
printf "" > "$out"

# Download program
rm -rf $src
git clone https://github.com/puzzlef/$src
cd $src && echo ""

# Run
g++ -O3 -fopenmp main.cxx
stdbuf --output=L ./a.out 2>&1 | tee -a "$out"
