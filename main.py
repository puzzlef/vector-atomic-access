# https://www.kaggle.com/wolfram77/puzzlef-sum-openmp-adjust-schedule
import os
from IPython.display import FileLink
src="sum-openmp-adjust-schedule"
out="{}.txt".format(src)
!printf "" > "$out"
display(FileLink(out))
!echo ""

# Download program
!rm -rf $src
!git clone https://github.com/puzzlef/$src
!echo ""

# Run
!g++ -O3 -fopenmp $src/main.cxx
!ulimit -s unlimited && stdbuf --output=L ./a.out 2>&1 | tee -a "$out"
