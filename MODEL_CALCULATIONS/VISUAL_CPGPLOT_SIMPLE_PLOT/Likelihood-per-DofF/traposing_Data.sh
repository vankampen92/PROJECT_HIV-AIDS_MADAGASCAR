# Example 
# ~ $ ./mtrxpose.sh "a b c d e f" "aa bb cc dd ee ff" "A B C D E F"
# a  aa   A
# b  bb   B
# c  cc   C
# d  dd   D
# e  ee   E
# f  ff   F

ar1=( $1 )
ar2=( $2 )

# for ((i=0; i<${#ar1[@]}; i++)); do
#
#    printf "  %2s  %2s\n" ${ar1[i]} ${ar2[i]}
#
# done

# Tabulated results... 
for ((i=0; i<${#ar1[@]}; i++)); do

    printf "%2s\t%2s\n" ${ar1[i]} ${ar2[i]}

done
