# This orders lines after the 20th column of all files in a given directory
# This directory should contain all the files to be ordered in the right format
# Execution: 
# ~$ bash produce_ordered_files.sh
#
for f in *.dat
do
     awk '{ if ($20 < 1.0E+20) { print } }' $f | sort -n -k 20 > ${f/%.txt/_Ordered.dat}
done






