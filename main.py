# https://www.kaggle.com/wolfram77/puzzlef-vector-atomic-access
import os
from IPython.display import FileLink
src="vector-atomic-access"
out="{}.txt".format(src)
!printf "" > "$out"
display(FileLink(out))
!echo ""

# Download program
!rm -rf $src
!git clone https://github.com/puzzlef/$src
!echo ""

# Run
!g++ -std=c++17 -O3 -latomic -fopenmp $src/main.cxx
!ulimit -s unlimited && stdbuf --output=L ./a.out 2>&1 | tee -a "$out"
