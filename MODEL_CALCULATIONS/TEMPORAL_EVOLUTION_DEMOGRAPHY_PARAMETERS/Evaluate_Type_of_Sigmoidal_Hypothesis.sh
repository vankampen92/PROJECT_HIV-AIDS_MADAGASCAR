#!/bin/sh

count=0

for File in C1 C2 C3 C4 C5 C6 C7 C8 C9
do
    count=`expr $count + 1`             # Increment arithmetically the counter
    
    echo "Job Number: "$count "has been queued!!!"

    ./X2W2-Y_ -H21 1.0 -y0 3 -sP 8 -sN 300 -sT 1.0E-06  -I0 10 -H10  0.01 -m0 0.0 -M0 0.05 -A0 0.01   -I1 11 -H11 0.01 -m1 0.0 -M1 0.05   -I2 18 -H18 0.01 -m2 0.0 -M2 0.05 -A2 0.01   -I3 19 -H19  0.01 -m3 0.0 -M3 0.05 -A3 0.01   -I4 20 -H20  0.1  -m4 0.08 -M4 0.12 -A4 0.01  -I5 23 -H23  0.01 -m5 0.0  -M5 0.5 -A5 0.01  -I6 24 -H24  0.1 -m6 0.0  -M6 2.0  -A6 0.01  -I7 25 -H25  2011.0 -m7 2009.0 -M7 2013.0 -A7 0.1  -n 2 -v0 6 -v1 4 -iP 0 -i0 9 -u0 0.0 -U0 100.0 -i1 17 -u1 0.0 -U1 100.0 -en 0 -eP0 17 -eV 0.2 -em0 0.01 -eM0 5 -G0 1 -G1 2 -tn 17 -t0 2000.0 -t1 2016.0 -t4 1 -xn 0 -xR 1 -DP 5 -DC 0 -D0 0 -D1 4 -D2 1 -P0 13 -a0 0  -P1 2 -a1 0  -P2 3 -a2 0 -P3 4 -a3 0 -P4 22 -a4 0  -tE 2.0 -tR 0 -Fn 1 -F0 Sigmoidal_$File  
    
    echo "Job Number: "$count "has been finished!!!"
    
done


 
