/* Parameters Defining Initial Conditions for Human Population:
   see include.Initial_Conditions.default.c */

XS__0 = 20990.0;
XI__0 = 0.0;
XL__0 = 0.0;
XD__0 = 0.0;

WS__0 = 1999.0;
WI__0 = 1.0;
WL__0 = 0.0;
WD__0 = 0.0;

YS__0  = 45000.0;
YI__0  = 0.0;
YL__0  = 0.0;
YD__0  = 0.0;

X0S__0 =   20990.0;
X0I__0 =   0.0 ;
X0L__0 =   0.0 ;
X0D__0 =   0.0 ;

W0S__0 =   1999.0;
W0I__0 =   1.0 ;
W0L__0 =   0.0 ;
W0D__0 =   0.0 ;

X1S__0 =   20990.0;
X1I__0 =   0.0 ;
X1L__0 =   0.0 ;
X1D__0 =   0.0 ;

W1S__0 =   2000.0 ;
W1I__0 =   0.0 ;
W1L__0 =   0.0 ;
W1D__0 =   0.0 ;


TYPE_of_INITIAL_CONDITION = 0;

INITIAL_TOTAL_POPULATION = 90980.0;

/* If this parameter is 1, then the initial total population is always rescaled to be:
 'INITIAT_TOTAL_POPULATION'. Otherwise, it is not!!!
*/
RESCALING_INITIAL_TOTAL_POPULATION = 0;;

No_of_IC = 0;     /* Number of Initial Conditions Variables in the optimization procedure */

IC_0 = 0;
IC_d0 = 0;
IC_MAX_0 = 1.0E+07;
IC_min_0 = 0.0;
IC_Acc_0 = 1.0;

IC_1 = 1;
IC_d1 = 0;
IC_MAX_1 = 1.0E+07;
IC_min_1 = 0.0;
IC_Acc_1 = 1.0;

IC_2 = 2;
IC_d2 = 0;
IC_MAX_2 = 1.0E+07;
IC_min_2 = 0.0;
IC_Acc_2 = 1.0;

IC_3 = 3;
IC_d3 = 0;
IC_MAX_3 = 1.0E+07;
IC_min_3 = 0.0;
IC_Acc_3 = 1.0;

IC_4 = 4;
IC_d4 = 0;
IC_MAX_4 = 1.0E+07;
IC_min_4 = 0.0;
IC_Acc_4 = 1.0;

IC_5 = 5;
IC_d5 = 0;
IC_MAX_5 = 1.0E+07;
IC_min_5 = 0.0;
IC_Acc_5 = 1.0;

IC_6 = 6;
IC_d6 = 0;
IC_MAX_6 = 1.0E+07;
IC_min_6 = 0.0;
IC_Acc_6 = 1.0;

IC_7 = 7;
IC_d7 = 0;
IC_MAX_7 = 1.0E+07;
IC_min_7 = 0.0;
IC_Acc_7 = 1.0;

IC_8 = 8;
IC_d8 = 0;
IC_MAX_8 = 1.0E+07;
IC_min_8 = 0.0;
IC_Acc_8 = 1.0;

IC_9 = 9;
IC_d9 = 0;
IC_MAX_9 = 1.0E+07;
IC_min_9 = 0.0;
IC_Acc_9 = 1.0;

IC_10 = 10;
IC_d10 = 0;
IC_MAX_10 = 1.0E+07;          // Maximum value of the subparameter range
IC_min_10 = 0.0;          // Minimum value of the subparameter range
IC_Acc_10 = 1.0;          // Accuracy

IC_11 = 11;
IC_d11 = 0;
IC_MAX_11 = 1.0E+07;
IC_min_11 = 0.0;
IC_Acc_11 = 1.0;

IC_12 = 12;
IC_d12 = 0;              // No of dicrete values
IC_MAX_12 = 1.0E+07;       // Maximum value of the subparameter range
IC_min_12 = 0.0;         // Minimum value of the subparameter range
IC_Acc_12 = 1.0;

IC_13 = 13;
IC_d13 = 0;
IC_MAX_13 = 1.0E+07;
IC_min_13 = 0.0;
IC_Acc_13 = 1.0;

IC_14 = 14;
IC_d14 = 0;
IC_MAX_14 = 1.0E+07;
IC_min_14 = 0.0;
IC_Acc_14 = 1.0;

IC_15 = 15;
IC_d15 = 0;
IC_MAX_15 = 1.0E+07;
IC_min_15 = 0.0;
IC_Acc_15 = 1.0;

IC_16 = 16;
IC_d16 = 0;
IC_MAX_16 = 1.0E+07;
IC_min_16 = 0.0;
IC_Acc_16 = 1.0;

IC_17 = 17;
IC_d17 = 0;
IC_MAX_17 = 1.0E+07;
IC_min_17 = 0.0;
IC_Acc_17 = 1.0;

IC_18 = 18;
IC_d18 = 0;
IC_MAX_18 = 1.0E+07;
IC_min_18 = 0.0;
IC_Acc_18 = 1.0;

IC_19 = 19;
IC_d19 = 0;
IC_MAX_19 = 1.0E+07;
IC_min_19 = 0.0;
IC_Acc_19 = 1.0;

IC_20 = 20;
IC_d20 = 0;
IC_MAX_20 = 1.0E+07;
IC_min_20 = 0.0;
IC_Acc_20 = 1.0;

IC_21 = 21;
IC_d21 = 0;
IC_MAX_21 = 1.0E+07;
IC_min_21 = 0.0;
IC_Acc_21 = 1.0;


Ranges_IC = (double **)calloc(2, sizeof(double *));
Ranges_IC[0] = (double *)calloc(MODEL_PARAMETER_SPACE_MAXIMUM, sizeof(double));
Ranges_IC[1] = (double *)calloc(MODEL_PARAMETER_SPACE_MAXIMUM, sizeof(double));
Acc_IC       = (double *)calloc(MODEL_PARAMETER_SPACE_MAXIMUM, sizeof(double));
d_IC         = (int *)calloc(MODEL_PARAMETER_SPACE_MAXIMUM, sizeof(int));
Index_IC = (int *)calloc(MODEL_PARAMETER_SPACE_MAXIMUM, sizeof(int));

#include <include.Initial_Conditions.default.aux.c>
