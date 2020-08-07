/* Parameters Defining Initial Conditions for Human Population:
   see include.Initial_Conditions.default.c */
double XS__0;
double WS__0;
double XI__0;
double WI__0;
double XL__0;
double WL__0;
double XD__0;
double WD__0;

double YS__0;
double YI__0;
double YL__0;
double YD__0;

double X0S__0;
double X0I__0;
double X0L__0;
double X0D__0;

double W0S__0;
double W0I__0;
double W0L__0;
double W0D__0;

double X1S__0;
double X1I__0;
double X1L__0;
double X1D__0;

double W1S__0;
double W1I__0;
double W1L__0;
double W1D__0;

int TYPE_of_INITIAL_CONDITION;

double INITIAL_TOTAL_POPULATION;

/* If this parameter is 1, then the initial total population is always rescaled to be:
 'INITIAT_TOTAL_POPULATION'. Otherwise, it is not!!!
*/
int RESCALING_INITIAL_TOTAL_POPULATION;

int No_of_IC;

int IC_0, IC_1, IC_2, IC_3, IC_4, IC_5, IC_6, IC_7, IC_8, IC_9;
int IC_d0, IC_d1, IC_d2, IC_d3, IC_d4, IC_d5, IC_d6, IC_d7, IC_d8, IC_d9;
double IC_MAX_0, IC_MAX_1, IC_MAX_2, IC_MAX_3, IC_MAX_4, IC_MAX_5, IC_MAX_6, IC_MAX_7, IC_MAX_8, IC_MAX_9;
double IC_min_0, IC_min_1, IC_min_2, IC_min_3, IC_min_4, IC_min_5, IC_min_6, IC_min_7, IC_min_8, IC_min_9;
double IC_Acc_0, IC_Acc_1, IC_Acc_2, IC_Acc_3, IC_Acc_4, IC_Acc_5, IC_Acc_6, IC_Acc_7, IC_Acc_8, IC_Acc_9;

int IC_10, IC_11, IC_12, IC_13, IC_14, IC_15, IC_16, IC_17, IC_18, IC_19;
int IC_d10, IC_d11, IC_d12, IC_d13, IC_d14, IC_d15, IC_d16, IC_d17, IC_d18, IC_d19;
double IC_MAX_10, IC_MAX_11, IC_MAX_12, IC_MAX_13, IC_MAX_14, IC_MAX_15, IC_MAX_16, IC_MAX_17, IC_MAX_18, IC_MAX_19;
double IC_min_10, IC_min_11, IC_min_12, IC_min_13, IC_min_14, IC_min_15, IC_min_16, IC_min_17, IC_min_18, IC_min_19;
double IC_Acc_10, IC_Acc_11, IC_Acc_12, IC_Acc_13, IC_Acc_14, IC_Acc_15, IC_Acc_16, IC_Acc_17, IC_Acc_18, IC_Acc_19;

int IC_20, IC_21;
int IC_d20, IC_d21;
double IC_MAX_20, IC_MAX_21;
double IC_min_20, IC_min_21;
double IC_Acc_20, IC_Acc_21;

double ** Ranges_IC;
double * Acc_IC;     //Accuracy for each parameter dimension
int    * d_IC;       //Discretization for each parameter dimension
int    * Index_IC;
