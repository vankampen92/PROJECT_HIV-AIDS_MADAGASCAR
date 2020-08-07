TIME_DEPENDENT_PARAMETERS = DEPENDENT_PARAMETERS_MAXIMUM; 

No_of_COVARIATES   = 0; 
TYPE_0_PARAMETERS  = 0;
TYPE_1_PARAMETERS  = 4;
TYPE_2_PARAMETERS  = 0; 

dep_0 = 0;                
pat_0 = 0;

dep_1 = 1;                
pat_1 = 0;

dep_2 = 2;                
pat_2 = 0;

dep_3 = 3;                
pat_3 = 0;

dep_4 = 4;                
pat_4 = 0;

dep_5 = 5;                
pat_5 = 0;

dep_6 = 6;                
pat_6 = 0;

dep_7 = 7;
pat_7 = 0;

dep_9 = 9;
pat_9 = 0;

dep_10 = 10;
pat_10 = 0;          

dep_11 = 11;
pat_11 = 0;

dep_12 = 12;
pat_12 = 0;       

dep_13 = 13;
pat_13 = 0;

dep_14 = 14;
pat_14 = 0;

dep_15 = 15;
pat_15 = 0;

dep_16 = 16;
pat_16 = 0;

dep_17 = 17;
pat_17 = 0;

dep_18 = 18;
pat_18 = 0;

dep_19 = 19;
pat_19 = 0;

dep_20 = 20;
pat_20 = 0;

dep_21 = 21;
pat_21 = 0;

dependent_parameter = (int *)calloc(MODEL_PARAMETERS_MAXIMUM, sizeof(int));
forcing_pattern     = (int *)calloc(MODEL_PARAMETERS_MAXIMUM, sizeof(int));

#include <include.Time_Dependence_Control.default.aux.c>
