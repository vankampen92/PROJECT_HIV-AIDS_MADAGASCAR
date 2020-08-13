#!/bin/bash
# A shell script to consolidat two sets of results. 

# To run this script, please invoke:

# . ~$ bash CONSOLIDATING_SETS_OF_RESULTS.sh [Type_of_Hypothesis] [PATH]

# Notice that for this to work, we need to have coincidental file names 
# in two different directories:
#    ./RESULTS_1 (working directory where this script is launched)
#    ./RESULTS_2 (directory where final consolidated files are saved)

export TERM=xterm

for File in Full_Parameter_Sets_*_20??_$1_Ordered.dat
do

    ls -la $File $2/$File

    tail -n +2 $2/$File > A.tmp

    cat $File A.tmp  > $2/${File}

    echo "File: "$File "has been processed"

done

rm A.tmp
