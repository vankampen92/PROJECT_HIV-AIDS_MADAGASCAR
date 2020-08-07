# Bash Ordering Script

for S in C1 C2 C3 C4 C5 C6 C7 C8 C9
do

    for f in Demo_Parameter_Set_*_Sigmoidal_$S.dat;
    do
	head -n 1 $f > Title_Row.txt
	awk '{ if ($10 < 1.0E+20) { print } }' $f | sort -n -k 10 | awk 'NR==1 { temp=$10; ((temp+=2)) } NR>=1 { if ($10 <= temp) { print } }' > ${f/%.dat/.ord}; 
    done
    
    for f in Demo_Parameter_Set_*_Sigmoidal_$S.ord;
    do
	cat Title_Row.txt $f > ${f/%.ord/_Ordered.dat}
    done
    
    rm *.ord
    
done
