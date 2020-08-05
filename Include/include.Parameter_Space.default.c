No_of_PARAMETERS = MODEL_PARAMETER_SPACE_MAXIMUM;
/* No of parameters defining the actual dimension of the subparameter space */

I0 = 0;                // Delta
d0 = 100;
MAX_P0 = 1.0;
min_P0 = 0.0;
Acc_P0 = 0.1;

I1 = 1;                // Alpha_0
d1 = 100;
MAX_P1 = 100.0;
min_P1 = 0.0;
Acc_P1 = 0.1;

I2 = 2;                // Alpha_1
d2 = 100;
MAX_P2 = 100.0;
min_P2 = 0.0;
Acc_P2 = 0.01;

I3 = 3;                // Lambda_0
d3 = 100;
MAX_P3 = 10.0;
min_P3 = 0.01;
Acc_P3 = 0.01;

I4 = 4;                // Lambda_1
d4 = 100;
MAX_P4 = 10.0;
min_P4 = 0.01;
Acc_P4 = 0.01;

I5 = 5;                // f, cap factor
d5 = 100;
MAX_P5 = 0.5;
min_P5 = 0.0;
Acc_P5 = 0.01;

I6 = 6;                // g, gap difference g = Alpha_1 - Alpha_0
d6 = 100;
MAX_P6 = 50.0;
min_P6 = 0.0;
Acc_P6 = 0.01;

I7 = 7;
d7 = 100;
MAX_P7 = 10.0;
min_P7 = 0.0;
Acc_P7 = 0.01;

I8 = 8;
d8 = 100;
MAX_P8 = 10.0;
min_P8 = 0.0;
Acc_P8 = 0.01;

I9 = 9;
d9 = 100;
MAX_P9 = 2.0;
min_P9 = 0.0;
Acc_P9 = 0.01;

I10 = 10;
d10 = 100;
MAX_P10 = 2.0;          // Maximum value of the subparameter range
min_P10 = 0.0;          // Minimum value of the subparameter range
Acc_P10 = 0.1;          // Accuracy

I11 = 11;
d11 = 100;
MAX_P11 = 100.0;
min_P11 = 0.0;
Acc_P11 = 0.1;

I12 = 12;
d12 = 100;              // No of dicrete values
MAX_P12 = 1000.0;       // Maximum value of the subparameter range
min_P12 = 0.0;         // Minimum value of the subparameter range
Acc_P12 = 0.01;

I13 = 13;
d13 = 100;
MAX_P13 = 100.0;
min_P13 = 0.0;
Acc_P13 = 0.01;

I14 = 14;
d14 = 100;
MAX_P14 = 100.0;
min_P14 = 0.0;
Acc_P14 = 0.01;

I15 = 15;
d15 = 100;
MAX_P15 = 0.005;
min_P15 = 0.0;
Acc_P15 = 0.01;

I16 = 16;
d16 = 100;
MAX_P16 = 1.0;
min_P16 = 0.0;
Acc_P16 = 0.01;

I17 = 17;
d17 = 100;
MAX_P17 = 10.0;
min_P17 = 0.0;
Acc_P17 = 0.01;

I18 = 18;
d18 = 100;
MAX_P18 = 2.0;
min_P18 = 0.0;
Acc_P18 = 0.01;

I19 = 19;
d19 = 100;
MAX_P19 = 2.0;
min_P19 = 0.0;
Acc_P19 = 0.01;

I20 = 20;
d20 = 100;
MAX_P20 = 2.0;
min_P20 = 0.0;
Acc_P20 = 0.01;

I21 = 21;
d21 = 100;
MAX_P21 = 2.0;
min_P21 = 0.0;
Acc_P21 = 0.01;

TOLERANCE = 1.0E-3;
MAX_No_of_ITERATIONS = 100;

Ranges = (double **)calloc(2, sizeof(double *));
Ranges[0] = (double *)calloc(MODEL_PARAMETER_SPACE_MAXIMUM, sizeof(double));
Ranges[1] = (double *)calloc(MODEL_PARAMETER_SPACE_MAXIMUM, sizeof(double));
Acc       = (double *)calloc(MODEL_PARAMETER_SPACE_MAXIMUM, sizeof(double));
d     = (int *)calloc(MODEL_PARAMETER_SPACE_MAXIMUM, sizeof(int));
Index = (int *)calloc(MODEL_PARAMETER_SPACE_MAXIMUM, sizeof(int));

#include <include.Parameter_Space.default.aux.c>
