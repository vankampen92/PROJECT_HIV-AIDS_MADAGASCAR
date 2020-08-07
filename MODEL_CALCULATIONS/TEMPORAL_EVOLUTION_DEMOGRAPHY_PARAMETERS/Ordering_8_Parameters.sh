# Bash Ordering Script

for f in Demo_Parameter_Set_*_$1.dat;
do
    head -n 1 $f > Title_Row.txt
    awk '{ if ($10 < 1.0E+20) { print } }' $f | sort -n -k 10 | awk 'NR==1 { temp=$10; ((temp+=2)) } NR>=1 { if ($10 <= temp) { print } }' > ${f/%.dat/_Ord.dat}; 
done

for f in Demo_Parameter_Set_*_$1_Ord.dat;
do
    cat Title_Row.txt $f > ${f/%.dat/ered.dat}
done

rm *Ord.dat
