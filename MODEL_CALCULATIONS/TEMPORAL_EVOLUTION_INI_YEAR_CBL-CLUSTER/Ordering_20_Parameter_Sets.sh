# Bash Ordering Script

for f in Full_Parameter_Set_$2_$1.dat;
do
    head -n 1 $f > Title_Row.txt
    awk '{ if ($22 < 1.0E+20) { print } }' $f
    cat $f | more
    sort -n -k 22 $f | awk 'NR==1 { temp=$22; ((temp+=2)) } NR>=1 { if ($22 <= temp) { print } }' > ${f/%.dat/_Ord.dat};
done

for f in Full_Parameter_Set_*_$1_Ord.dat;
do
    cat Title_Row.txt $f > ${f/%.dat/ered.dat}
done

rm *Ord.dat
