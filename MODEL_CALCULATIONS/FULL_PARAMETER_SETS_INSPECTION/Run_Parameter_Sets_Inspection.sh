#!/bin/bash
# A shell script to run multiple jobs

# To run this script, please invoke:

# . ~$ bash Run_Parameter_Sets_Inspection.sh


for Year in 2000 2001 ### 2002 2003 2004 ### 2005 2006 2007 2008 2009 2010                                           ### Inner for loop ###
do
    count=0
    for File in Antananarivo Antsiranana Mahajanga Toamasina Fianarantsoa Toliary Taolagnaro Moramanga Antsirabe Morondava Nosy_Be
    do
	
        ./X2W2SILD-YSILD -y0 1 -G0 5 -G1 4 -n 3 -v0 6 -v1 4 -v2 14 -en 0 -iP 0 -tn 17 -t0 2000.0 -t1 2016.0 -Fn 2 -F0 $File -X0 $count -F1 $Year
        
	count=`expr $count + 1`                                                                                          ### Increment arithmetically the counter
	
        echo "Job Number: "$count "has been successfully run ("$File") ("$Year")!!!"
	
    done
done
