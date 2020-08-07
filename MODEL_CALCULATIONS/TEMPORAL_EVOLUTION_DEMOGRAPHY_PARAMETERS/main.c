/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                            David Alonso, 2018 (c)                         */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#include <Include/MODEL.h>

#include "global.h"

gsl_rng * r; /* Global generator defined in main.c */

/* This code calculates ODE model temporal evolution of the demographic
   model. Here, the goal is to estimate sigma parameters from data. Sigma
   parameters (and Alpha) control the distribution of females in the dif-
   ferent groups. Parameters F_X, F_Y, \delta_X and \delta_Y have been
   already estimated from demographic data. See directory:

   ./TEMPORAL_EVOLUTION_r_FACTOR_ESTIMATE

   F_X and F_Y are recruitment rates into adult sexually active life, and
   \delta_X and \delta_Y are adult mortality rates. They change every year.
   They are given in 'Time_Dependent_Parameters_Corrected_[CITY_NAME].dat'
   files.

   Two imput sets of files are required:

   1. Time_Dependent_Parameters_Corrected_[CITY_NAME].dat'

   2. Observed_Data_2Rows_[CITY_NAME]_[TYPE_of_HYPOTHESIS_COMMAND_LINE].dat

   Compilation:

   . ~$ make X_MODEL=X2W2 Y_MODEL=Y_

   Two hypotheses can be addressed:

   A. Parameters are searched under the hypothesis of constant ratio of female
   sexual workers to total female population. Then, observed data files are:

   Observed_Data_2Rows_[CITY_NAME].dat

   B. Parameters are searched under the hypothesis of ratio of female
   sexual workers to total female population following a sigmoidal curve
   with a break point in 2011.0 and smoothness parameters 0.1. Then, observed
   data files should be:

   Observed_Data_2Rows_[CITY_NAME]_[TYPE_of_HYPOTHESIS_COMMAND_LINE].dat

   In sum,  hypothesis A needs and generates files ending in 
   [TYPE_of_HYPOTHESIS_COMMAND_LINE].dat,  where this type of hypothesis is aimed
   at estimating only 5 parameters (-sP 5) non-sigmoidal type of hypothesis), while 
   hypothesis B requires files ending also in  *[TYPE_of_HYPOTHESIS_COMMAND_LINE].dat, 
   where this type hypothesis is sigmoidal and requires estimating 5 + 3 parameters 
   (-sP 8). These additional 3 parameters characterize the sigmoidal curves. Command line 
   arguments define the hypothesis, for instance:

   -Fn 0 -F0 Sigmoidal_C5

   The same program can be run with two very different purposes:
   
   If the command line arguments contains: -tR 0, then the program is used for the evaluation 
   and visualization of previously calculated solutions. If it contains: -tR 10000, then the code
   finds solutions that best fit the data by checking 10000 different initial parameter
   configuration (within given parameter ranges) to optimize and find the parameter
   configurations (or optimal solutions) that optimally fit the data. 

   A. Parameters are searched under the hypothesis of constant ratio of female
   sexual workers to total female population (STASIS HYPOTHESIS)

   Exectution: (Time-dependent parameters: -t4 1, and initial conditions as searcheable parameters:  -iP 2 -i0 0 -i1 1)

   . ~$ ./X2W2-Y_ -y0 3                                                // TYPE of MODEL
   / -sP 5 -sN 200                                                     // Parameter Space of Model Parameters:  [-sP : Dimension, Number of Model Parameters to be optimized]
   / -I0 10 -H10  0.01 -m0 0.0 -M0 0.05 -A0 0.01    Parameter: Sigma_0
   / -I1 11 -H11  0.01 -m1 0.0 -M1 0.05 -A1 0.01    Parameter: Sigam_0_r
   / -I2 18 -H18  0.01 -m2 0.0 -M2 0.05 -A2 0.01    Parameter: Sigma_1
   / -I3 19 -H19  0.01 -m3 0.0 -M3 0.05 -A3 0.01    Parameter: Sigma_1_r
   / -I4 20 -H20  0.1  -m4 0.08 -M4 0.12 -A4 0.01    Parameter: Alpha
   / -n 2   -v0 6 -v1 4                                                // Output/Observed Varables:             [-n  Number of Observed Variables]
   / -en 1  -eV 1.0 -eP0 17 -em0 0.01 -eM0 2.0                         // Parameter Space of Error Model        [-en Number of Error Model-related parameters to be optimized]
   / -iP 0  -i0 9 -u0 0.0 -U0 100.0 -i1 17 -u1 0.0 -U1 100.0           // Parameter Space of Initial Conditions [-iP Number of Initial Condition Variables to be optimized]
   / -G0 1  -G1 2 -tn 17 -t0 2000.0 -t1 2016.0 -t4 1 -xn 0 -xR 1       // Arguments Controling Numerical Integration
   / -DP 4  -DC 0 -D0 0 -D1 4 -D2 0 -P0 13 -a0 0 -P1 2 -a1 0  -P2 3 -a2 0 -P3 4 -a3 0  // Arguments controling type of time dependence of model parameters.

   . ~$ ./X2W2-Y_ -H21 1.0 -y0 3 -sP 5 -sN 300 -sT 1.0E-06  -I0 10 -H10  0.01 -m0 0.0 -M0 0.05 -A0 0.01   -I1 11 -H11 0.01 -m1 0.0 -M1 0.05   -I2 18 -H18 0.01 -m2 0.0 -M2 0.05 -A2 0.01   -I3 19 -H19  0.01 -m3 0.0 -M3 0.05 -A3 0.01   -I4 20 -H20  0.1  -m4 0.08 -M4 0.12 -A4 0.01  -iP 0 -i0 9 -u0 0.0 -U0 100.0 -i1 17 -u1 0.0 -U1 100.0 -en 0 -eP0 17 -eV 0.2 -em0 0.1 -eM0 5 -G0 2 -G1 1 -n 2 -v0 6 -v1 4 -tn 17 -t0 2000.0 -t1 2016.0 -t4 1 -xn 0 -xR 1 -DP 5 -DC 0 -D0 0 -D1 4 -D2 1 -P0 13 -a0 0  -P1 2 -a1 0  -P2 3 -a2 0 -P3 4 -a3 0 -P4 22 -a4 0 -tE 2.0 -tR 0 -Fn 1 -F0 Stasis_1

   B. Parameters are searched under the hypothesis of ratio of female
   sexual workers to total female population following a sigmoidal curve
   with a break point in 2011.0 and smoothness parameters.
   These files are generated in

	./OBSERVED_DATA_FILES_PREPARATION

   and resulting files are labelled as *_[TYPE_of_HYPOTHESIS_COMMAND_LINE].dat type of files.

   In this case, the search include three new parameters controling a corresponding
   break parameters in parameters Sigma_0 and Sigma_1. In addition, a new
   parameters D_Sigma has a sigmoidal time dependence (parameters 22), which
   imposes a time dependence in Sigma_0 and Sigma_1 through:

   Sigma_0(t) = Sigma_0 + D_Sigma(t)
   Sigma_1(t) = Simga_1 + D_Sigma(t)

   Exectution: (Time-dependent parameters: -t4 1; Initial conditions as searcheable parameters:  -iP 2 -i0 0 -i1 1)

   . ~$ ./X2W2-Y_ -y0 3             // TYPE of MODEL
   / -sP 8 -sN 200                  // Parameter Space of Model Parameters:  [-sP : Dimension, Number of Model Parameters to be optimized]: 8
   / -I0 10 -H10  0.01 -m0 0.0  -M0 0.05 -A0 0.01       Parameter: Sigma_0
   / -I1 11 -H11  0.01 -m1 0.0  -M1 0.05 -A1 0.01       Parameter: Sigam_0_r
   / -I2 18 -H18  0.01 -m2 0.0  -M2 0.05 -A2 0.01       Parameter: Sigma_1
   / -I3 19 -H19  0.01 -m3 0.0  -M3 0.05 -A3 0.01       Parameter: Sigma_1_r
   / -I4 20 -H20  0.1  -m4 0.08 -M4 0.12 -A4 0.01       Parameter: Alpha
   / -I5 23 -H23  0.01 -m5 0.0  -M5 0.5  -A5 0.01       Parameter: A_0
   / -I6 24 -H24  0.01 -m6 0.0  -M6 2.0  -A6 0.01       Parameter: L_0
   / -I7 25 -H25  2011.0 -m7 2009.0 -M7 2013.0 -A7 0.1  Parameter: T_0
   / -n 2   -v0 6 -v1 4                                                // Output/Observed Varables:             [-n  Number of Observed Variables]
   / -en 1  -eV 1.0 -eP0 17 -em0 0.01 -eM0 2.0                         // Parameter Space of Error Model        [-en Number of Error Model-related parameters to be optimized]
   / -iP 0  -i0 9 -u0 0.0 -U0 100.0 -i1 17 -u1 0.0 -U1 100.0           // Parameter Space of Initial Conditions [-iP Number of Initial Condition Variables to be optimized]
   / -G0 1  -G1 2 -tn 17 -t0 2000.0 -t1 2016.0 -t4 1 -xn 0 -xR 1       // Arguments Controling Numerical Integration
   / -DP 5  -DC 0 -D0 0 -D1 4 -D2 1 -P0 13 -a0 0 -P1 2 -a1 0  -P2 3 -a2 0 -P3 4 -a3 0 -P4 22 -a4 0// Arguments controling type of time dependence of model parameters.

   . ~$ ./X2W2-Y_ -H21 1.0 -y0 3 -sP 8 -sN 300 -sT 1.0E-06  -I0 10 -H10  0.01 -m0 0.0 -M0 0.05 -A0 0.01   -I1 11 -H11 0.01 -m1 0.0 -M1 0.05   -I2 18 -H18 0.01 -m2 0.0 -M2 0.05 -A2 0.01   -I3 19 -H19  0.01 -m3 0.0 -M3 0.05 -A3 0.01   -I4 20 -H20  0.1  -m4 0.08 -M4 0.12 -A4 0.01  -I5 23 -H23  0.01 -m5 0.0  -M5 0.5 -A5 0.01  -I6 24 -H24  0.1 -m6 0.0  -M6 2.0  -A6 0.01  -I7 25 -H25  2011.0 -m7 2009.0 -M7 2013.0 -A7 0.1  -n 2 -v0 6 -v1 4 -iP 0 -i0 9 -u0 0.0 -U0 100.0 -i1 17 -u1 0.0 -U1 100.0 -en 0 -eP0 17 -eV 0.2 -em0 0.01 -eM0 5 -G0 1 -G1 2 -tn 17 -t0 2000.0 -t1 2016.0 -t4 1 -xn 0 -xR 1 -DP 5 -DC 0 -D0 0 -D1 4 -D2 1 -P0 13 -a0 0  -P1 2 -a1 0  -P2 3 -a2 0 -P3 4 -a3 0 -P4 22 -a4 0  -tE 2.0 -tR 10000 -Fn 1 -F0 Sigmoidal_C5

   Command to order resuling files from the search:

   . ~$ for f in Demo_Parameter_Set_*_[TYPE_of_HYPOTHESIS_COMMAND_LINE].dat; do awk '{ if ($10 < 1.0E+20) { print } }' $f | sort -n -k 10 > ${f/%.dat/_Ordered.dat}; done

   . ~$ for f in Demo_Parameter_Set_*_Sigmoidal_C?.dat; do cat $f | sort -n -k 10 > ${f/%.dat/_Full_Ordered.dat}; done

   Important: -tR 0, for the evaluation and visualization of previously calculated solutions. In this
   case, it is possible to plot as output variables also other variables. For instance:

   . ~$ ./X2W2-Y_ -H21 1.0 -y0 3 -sP 8 -sN 300 -sT 1.0E-06  -I0 10 -H10  0.01 -m0 0.0 -M0 0.05 -A0 0.01   -I1 11 -H11 0.01 -m1 0.0 -M1 0.05   -I2 18 -H18 0.01 -m2 0.0 -M2 0.05 -A2 0.01   -I3 19 -H19  0.01 -m3 0.0 -M3 0.05 -A3 0.01   -I4 20 -H20  0.1  -m4 0.08 -M4 0.12 -A4 0.01  -I5 23 -H23  0.01 -m5 0.0  -M5 0.05 -A5 0.01  -I6 24 -H24  0.01 -m6 0.0  -M6 1.0  -A6 0.01  -I7 25 -H25  2011.0 -m7 2009.0 -M7 2013.0 -A7 0.1  -iP 0 -i0 9 -u0 0.0 -U0 100.0 -i1 17 -u1 0.0 -U1 100.0 -en 0 -eP0 17 -eV 0.2 -em0 0.1 -eM0 5 -G0 1 -G1 1 -n 2 -v0 6 -v1 4 -tn 17 -t0 2000.0 -t1 2016.0 -t4 1 -xn 0 -xR 1 -DP 5 -DC 0 -D0 0 -D1 4 -D2 1 -P0 13 -a0 0  -P1 2 -a1 0  -P2 3 -a2 0 -P3 4 -a3 0 -P4 22 -a4 0  tE 2.0 -tR 0 -Fn 1 -F0 Sigmoidal_C5

   In addition, variable 17 and 18 may show the sigmoidal evolution of parameters Sigma_0 and Sigma_1 through time. For example:

   We need to add -n 4 -v0 6 -v1 4 -v2 17 -v3 18 and invoke:

   . ~$ ./X2W2-Y_ -H21 1.0 -y0 3 -sP 8 -sN 300 -sT 1.0E-06  -I0 10 -H10  0.01 -m0 0.0 -M0 0.05 -A0 0.01   -I1 11 -H11 0.01 -m1 0.0 -M1 0.05   -I2 18 -H18 0.01 -m2 0.0 -M2 0.05 -A2 0.01   -I3 19 -H19  0.01 -m3 0.0 -M3 0.05 -A3 0.01   -I4 20 -H20  0.1  -m4 0.08 -M4 0.12 -A4 0.01  -I5 23 -H23  0.01 -m5 0.0  -M5 0.05 -A5 0.01  -I6 24 -H24  0.01 -m6 0.0  -M6 1.0  -A6 0.01  -I7 25 -H25  2011.0 -m7 2009.0 -M7 2013.0 -A7 0.1  -iP 0 -i0 9 -u0 0.0 -U0 100.0 -i1 17 -u1 0.0 -U1 100.0 -en 0 -eP0 17 -eV 0.2 -em0 0.1 -eM0 5 -G0 2 -G1 2 -n 4 -v0 6 -v1 4 -v2 17 -v3 18 -tn 17 -t0 2000.0 -t1 2016.0 -t4 1 -xn 0 -xR 1 -DP 5 -DC 0 -D0 0 -D1 4 -D2 1 -P0 13 -a0 0  -P1 2 -a1 0  -P2 3 -a2 0 -P3 4 -a3 0 -P4 22 -a4 0  -tE 2.0 -tR 0

   Another similar example, looking at sexual worker fraction (-v12): -n 4 -v0 6 -v1 4 -v2 12 -v3 17

   . ~$ ./X2W2-Y_ -H21 1.0 -y0 3 -sP 8 -sN 300 -sT 1.0E-06  -I0 10 -H10  0.01 -m0 0.0 -M0 0.05 -A0 0.01   -I1 11 -H11 0.01 -m1 0.0 -M1 0.05   -I2 18 -H18 0.01 -m2 0.0 -M2 0.05 -A2 0.01   -I3 19 -H19  0.01 -m3 0.0 -M3 0.05 -A3 0.01   -I4 20 -H20  0.1  -m4 0.08 -M4 0.12 -A4 0.01  -I5 23 -H23  0.01 -m5 0.0  -M5 0.05 -A5 0.01  -I6 24 -H24  0.01 -m6 0.0  -M6 1.0  -A6 0.01  -I7 25 -H25  2011.0 -m7 2009.0 -M7 2013.0 -A7 0.1  -iP 0 -i0 9 -u0 0.0 -U0 100.0 -i1 17 -u1 0.0 -U1 100.0 -en 0 -eP0 17 -eV 0.2 -em0 0.1 -eM0 5 -G0 2 -G1 2 -n 4 -v0 6 -v1 4 -v2 12 -v3 17 -tn 17 -t0 2000.0 -t1 2016.0 -t4 1 -xn 0 -xR 1 -DP 5 -DC 0 -D0 0 -D1 4 -D2 1 -P0 13 -a0 0  -P1 2 -a1 0  -P2 3 -a2 0 -P3 4 -a3 0 -P4 22 -a4 0  -tE 2.0 -tR 0

   Under hypothesis A or B, the error variance can also be optimized. In the following example (hypothesis A), notice that error variance is also optimized: -en 1 -eV 1.0 -eP0 17 -em0 1.0E-05 -eM0 2.0

   . ~$ ./X2W2-Y_ -H20 0.1 -H21 1.0 -y0 3 -sP 4 -sN 700 -sT 1.0E-06   -I0 10 -H10  0.01 -m0 0.0 -M0 0.05 -A0 0.01   -I1 11 -H11 0.01 -m1 0.0 -M1 0.05   -I2 18 -H18 0.01 -m2 0.0 -M2 0.05 -A2 0.01   -I3 19 -H19  0.01 -m3 0.0 -M3 0.05 -A3 0.01   -I4 20 -H20  0.1  -m4 0.8 -M4 0.12 -A4 0.01 -n 2 -v0 6 -v1 4 -iP 0 -i0 9 -u0 0.0 -U0 100.0 -i1 17 -u1 0.0 -U1 100.0 -en 1 -eP0 17 -eV 1.0 -em0 1.0E-05 -eM0 2.0 -G0 1 -G1 2 -tn 17 -t0 2000.0 -t1 2016.0 -t4 1 -xn 0 -xR 1 -DP 4  -DC 0 -D0 0 -D1 4 -D2 0 -P0 13 -a0 0 -P1 2 -a1 0  -P2 3 -a2 0 -P3 4 -a3 0 -tE 2.0

   -xn TYPE of INITIAL CONDITION (0 from default values in Parameter Table (Input Args); 1 at Random; 2 from fixed/stationary Point)
   -xR RESCALING INITIAL POPULATION (initial total population remains always the same)
   -xN INITIAL TOTAL POPULATION SIZE
   -t4 TYPE of TIME DEPENDENCE (0, no parameter time dependence). If the TYPE of TIME DEPENDENCE input argument is greater than 0, time dependence parameters are at play and time dependence files are required. See also ./Definition_Numerical_Integration/XWSILD-YSILD/deterministic_time_dynamics.c

   See file denition_OutPut_Variables.c for full -v?? input argument code definitions. Examples are:

   -v0  0   Effective Average Fraction ofInfectious Females
   -v1  1   Effective Average Fraction of Infectious Males
   -v1  4   Total Female Sexual Worker Population
   -v2  2   Total Female Population
   -v3  6   Total Population
   -v4  7   Total Disease Prevalence
   -v5  8   Total Female Disease Prevalence
   -v6  9   Total Male_Disease Prevalence
   -v7 10   Total Female Sexual Worker Disease Prevalence
   -v8 12   Female Sexual Worker Fraction
*/

double Discrepancy_Fraction_Female_Sexual_Worker(Parameter_Table *Table, double **Data )
{
  double value;
  double x_Data, x_Theory;
  double Female_Sexual_Worker_Population;
  double Female_Population;
  double Female_Sexual_Worker_Population_Theory;
  double Female_Population_Theory;
  int No_of_TIMES = Table->T->I_Time;

  assert( No_of_TIMES == 17 );
  assert( Table->SUB_OUTPUT_VARIABLES == 2);

  Female_Population                = Data[0][No_of_TIMES-1]/2.0;
  Female_Sexual_Worker_Population  = Data[1][No_of_TIMES-1];

  x_Data =  Female_Sexual_Worker_Population/Female_Population;

  Female_Population_Theory                = Table->Matrix_Output_Variables[0][No_of_TIMES-1]/2.0;
  Female_Sexual_Worker_Population_Theory  = Table->Matrix_Output_Variables[1][No_of_TIMES-1];

  x_Theory = Female_Sexual_Worker_Population_Theory/Female_Population_Theory;

  value = sqrt( (x_Theory-x_Data) * (x_Theory-x_Data) );

  return(value);
}

int main(int argc, char **argv)
{
  char * pF;
  char * FILE_LABEL;
  int No_of_SETS_MAX, No_of_PARAMETER_SETS, EVALUATION;
  double ** Demo_Data;
  FILE ** DEMO;
  FILE *** TEMPORAL_EVOLUTION_FILE;

  int i, j, k, n, s, key;
  double value, Min_Value;
  double Discrepancy_Value;
  Parameter_Table Table;
  Time_Control Time;
  Time_Dependence_Control Time_Dependence;
  P_ARG = &Table;

#include "default.c"

  /* Command line arguments */
  if(argc>1) ArgumentControl(argc, argv);
  
  if ( No_of_FILES == 1 ) FILE_LABEL = Name_of_FILE[0];
  else {
    printf(" Type of hypothesis (Sigmoidal or not) defining\n");
    printf(" the input files is not well defined!!!\n");
    printf(" The program will exit!!!\n"); exit(0);
  }
  
  // If you want to evaluate and plot previously calculate and  saved solutions,
  // please include -tR 0 in your command line. Otherwise, you will try a number
  // "Realizations" as initial guesses for different solutions.
  if (Realizations == 0) EVALUATION = 1; 
  else                   EVALUATION = 0;

  #include "include.Output_Variables.default.aux.c"
  P_A_R_A_M_E_T_E_R___T_A_B_L_E___A_L_L_O_C(   &Table );
  P_A_R_A_M_E_T_E_R___T_A_B_L_E___U_P_L_O_A_D( &Table, Index_Output_Variables );
  printf("Output variables:\n");
  for(i=0; i<SUB_OUTPUT_VARIABLES; i++) {
    key = Table.OUTPUT_VARIABLE_INDEX[i];
    printf("%d: %s\n", i, Table.Output_Variable_Name[key]);
  }
  printf(" Parameter_Table structure has been correctly allocated and initiated\n");

  Parameter_Model * Initial_Guess = (Parameter_Model *)malloc( 1 * sizeof(Parameter_Model) );
  P_A_R_A_M_E_T_E_R___I_N_I_T_I_A_L_I_Z_A_T_I_O_N (&Table, Initial_Guess);
  printf(" Parameter_Model structure 'Initial_Guess' has been correctly allocated and initiated\n");

  /* B E G I N : Reserving memmory for Error Model Parameter Space */
  Parameter_Space * Error_Space = (Parameter_Space *)calloc(1, sizeof(Parameter_Space));
  if( No_of_ERROR_PARAMETERS > 0 ) {
#include <include.Error_Control.default.aux.c>
    Parameter_Space_Alloc( Error_Space, No_of_ERROR_PARAMETERS, d_Error);
    Parameter_Table_Copy_into_Parameter_Model(Error_Space->Parameter_min, &Table);
    Model_Variables_Code_into_Parameter_Model(Error_Space->Parameter_min);
    Parameter_Table_Copy_into_Parameter_Model(Error_Space->Parameter_MAX, &Table);
    Model_Variables_Code_into_Parameter_Model(Error_Space->Parameter_MAX);
    Parameter_Table_Copy_into_Parameter_Model(Error_Space->Parameter_Acc, &Table);
    Model_Variables_Code_into_Parameter_Model(Error_Space->Parameter_Acc);
    Parameter_Space_Error_Initialization( Error_Space,
					  No_of_ERROR_PARAMETERS, d_Error,
					  Index_Error, Ranges_Error, Acc_Error );
    //Parameter_Space_fprintf( Initial_Condition_Space, stdout );

    printf("Initial Condition Parameter_Space structure has been correctly allocated and initiated\n");
  }
  Table.E_Space = Error_Space;
  /*     E N D : ------------------------------------- */

  /* B E G I N : Reserving memmory for Initial Conditions Parameter Space */
  Parameter_Space * Initial_Condition_Space = (Parameter_Space *)calloc(1, sizeof(Parameter_Space));
  if( No_of_IC > 0 ) {
#include <include.Initial_Conditions.default.aux.c>
    Parameter_Space_Alloc( Initial_Condition_Space, No_of_IC, d_IC );
    Parameter_Table_Copy_into_Parameter_Model(Initial_Condition_Space->Parameter_min, &Table);
    Model_Variables_Code_into_Parameter_Model(Initial_Condition_Space->Parameter_min);
    Parameter_Table_Copy_into_Parameter_Model(Initial_Condition_Space->Parameter_MAX, &Table);
    Model_Variables_Code_into_Parameter_Model(Initial_Condition_Space->Parameter_MAX);
    Parameter_Table_Copy_into_Parameter_Model(Initial_Condition_Space->Parameter_Acc, &Table);
    Model_Variables_Code_into_Parameter_Model(Initial_Condition_Space->Parameter_Acc);
    Parameter_Space_IC_Initialization( Initial_Condition_Space,
				       No_of_IC, d_IC, Index_IC, Ranges_IC, Acc_IC );
    //Parameter_Space_fprintf( Initial_Condition_Space, stdout );
    printf("Initial Condition Parameter_Space structure has been correctly allocated and initiated\n");
  }
  Table.IC_Space = Initial_Condition_Space;
  /*     E N D : ------------------------------------- */

  /* B E G I N : Reserving memmory for Model Parameter Space */
  #include <include.Parameter_Space.default.aux.c>
  Parameter_Space * Space = (Parameter_Space *)calloc(1, sizeof(Parameter_Space));
  Parameter_Space_Alloc( Space, No_of_PARAMETERS, d);
  Parameter_Space_Initialization( Space, No_of_PARAMETERS, TOLERANCE, MAX_No_of_ITERATIONS,
				  d, Index, Ranges, Acc);
  Parameter_Table_Index_Update(Index, No_of_PARAMETERS, &Table);
  Table.S = Space;
  printf("Parameter_Space structure has been correctly allocated and initiated\n");
  /*     E N D : ------------------------------------- */

  if (TYPE_of_TIME_DEPENDENCE == 0) {
    printf(" Time_Control structure will be allocated: \n");
    printf(" %d output variables of length %d points will be allocated\n",
	   SUB_OUTPUT_VARIABLES, I_Time);
    T_I_M_E___C_O_N_T_R_O_L___A_L_L_O_C( &Time, &Table, I_Time);
    T_I_M_E___C_O_N_T_R_O_L___U_P_L_O_A_D( &Time, &Table, I_Time);
    printf(" Time_Control structure has been correctly allocated and set up\n");
  }
  else {
#include <include.Time_Dependence_Control.default.aux.c>
    printf(" Time_Dependence_Control and Time_Control structures will be allocated: \n");
    printf(" %d output variables of length %d points will be allocated\n",
	   SUB_OUTPUT_VARIABLES, I_Time);
    Time_Dependence_Control_Alloc(&Time, &Time_Dependence, &Table,
				  I_Time, TIME_DEPENDENT_PARAMETERS, No_of_COVARIATES);
    printf(" Both Time_Control and Time_Dependence_Control structures have been\n");
    printf(" correctly allocated\n");
    // getchar();
  }

#if defined CPGPLOT_REPRESENTATION
  Table.CPG = A_C_T_I_V_A_T_E___C_P_G_P_L_O_T ( SUB_OUTPUT_VARIABLES, I_Time, 0, CPG_DRIVER_NAME);
  printf(" Parameter_CPGPLOT plotting structure has been correctly allocated and initiated\n");
#endif

#include <gsl_random_number_Setup.c>
#if defined VERBOSE
  /* BEGIN: Checking Random Number Generator Setup */
  for(i=0; i<10; i++){
    printf( "f(%d)=%g, ", i, gsl_rng_uniform(r) );
    printf( "f_GAUS(%d)=%g\n", i, gsl_ran_gaussian(r, 1.0) );
  }
  printf("\n");//Press_Key();
  /*   END: Checking Random Number Generator Setup */
#endif

  char   ** Name_of_Rows          = (char **)calloc(SUB_OUTPUT_VARIABLES, sizeof(char *) );
  double ** Empirical_Data_Matrix = (double **)calloc( SUB_OUTPUT_VARIABLES, sizeof(double *) );
  for (i=0; i<SUB_OUTPUT_VARIABLES; i++) {
    key = Table.OUTPUT_VARIABLE_INDEX[i];
    Name_of_Rows[i]         = Table.Output_Variable_Symbol[key];
    Empirical_Data_Matrix[i] = (double *)calloc( I_Time, sizeof(double) );
  }

  int No_of_CITIES = 11;
  const char * City_Names[] = { "Antananarivo",  "Antsiranana",
				"Mahajanga",     "Toamasina",
				"Fianarantsoa",  "Toliary",
				"Taolagnaro",    "Moramanga",
				"Antsirabe",     "Morondava",
				"Nosy_Be" };

  /* B E G I N : Time Dependent Parameters and Observed Data File Names */
  char ** TIME_PARAMETERS_FILE = (char **)calloc(No_of_CITIES, sizeof(char *) );
  char ** OBSERVED_DATA_FILE    = (char **)calloc(No_of_CITIES, sizeof(char *) );
  char ** DEMOGRAPHIC_PARAMETERS_CITY = (char **)calloc(No_of_CITIES, sizeof(char *) );
  char *** TIME_EVOLUTION_FILE_NAME = (char ***)calloc(No_of_CITIES, sizeof(char **) );

  for(k = 0; k<No_of_CITIES; k++) {
    TIME_PARAMETERS_FILE[k] = (char *)calloc( 100, sizeof(char) );
    OBSERVED_DATA_FILE[k]    = (char *)calloc( 100, sizeof(char) );
    DEMOGRAPHIC_PARAMETERS_CITY[k] = (char *)calloc( 100, sizeof(char) );
    TIME_EVOLUTION_FILE_NAME[k]= (char **)calloc( SUB_OUTPUT_VARIABLES, sizeof(char *) );
    for(i=0; i<SUB_OUTPUT_VARIABLES; i++)
      TIME_EVOLUTION_FILE_NAME[k][i] = (char *)calloc( 100, sizeof(char) );
  }

  for(k = 0; k<No_of_CITIES; k++) {
    TIME_PARAMETERS_FILE[k][0] = '\0';
    pF = strcat(TIME_PARAMETERS_FILE[k], "Time_Dependent_Parameters_Corrected_");
    pF = strcat(TIME_PARAMETERS_FILE[k], City_Names[k]);
    pF = strcat(TIME_PARAMETERS_FILE[k], ".dat");

    OBSERVED_DATA_FILE[k][0] = '\0';
    pF = strcat(OBSERVED_DATA_FILE[k], "Observed_Data_File_2Rows_");
    pF = strcat(OBSERVED_DATA_FILE[k], City_Names[k]);
    pF = strcat(OBSERVED_DATA_FILE[k], "_");
    pF = strcat(OBSERVED_DATA_FILE[k], FILE_LABEL);
    pF = strcat(OBSERVED_DATA_FILE[k], ".dat");

    if( EVALUATION == 1 ) {
      DEMOGRAPHIC_PARAMETERS_CITY[k][0] = '\0';
      pF = strcat(DEMOGRAPHIC_PARAMETERS_CITY[k], "Demo_Parameter_Set_");
      pF = strcat(DEMOGRAPHIC_PARAMETERS_CITY[k], City_Names[k]);
      pF = strcat(DEMOGRAPHIC_PARAMETERS_CITY[k], "_");
      pF = strcat(DEMOGRAPHIC_PARAMETERS_CITY[k], FILE_LABEL);
      pF = strcat(DEMOGRAPHIC_PARAMETERS_CITY[k], "_Ordered.dat");

      for(i=0; i<SUB_OUTPUT_VARIABLES; i++) {
	TIME_EVOLUTION_FILE_NAME[k][i][0] = '\0';
	pF = strcat(TIME_EVOLUTION_FILE_NAME[k][i], "Time_Evolution_");
	pF = strcat(TIME_EVOLUTION_FILE_NAME[k][i], City_Names[k]);
	pF = strcat(TIME_EVOLUTION_FILE_NAME[k][i], "_");
	key = Table.OUTPUT_VARIABLE_INDEX[i];
	pF = strcat(TIME_EVOLUTION_FILE_NAME[k][i], Table.Output_Variable_Symbol[key]);
	pF = strcat(TIME_EVOLUTION_FILE_NAME[k][i], "_");
	pF = strcat(TIME_EVOLUTION_FILE_NAME[k][i], FILE_LABEL);
	pF = strcat(TIME_EVOLUTION_FILE_NAME[k][i], ".dat");
      }
    }
    else {
      DEMOGRAPHIC_PARAMETERS_CITY[k][0] = '\0';
      pF = strcat(DEMOGRAPHIC_PARAMETERS_CITY[k], "Demo_Parameter_Set_");
      pF = strcat(DEMOGRAPHIC_PARAMETERS_CITY[k], City_Names[k]);
      pF = strcat(DEMOGRAPHIC_PARAMETERS_CITY[k], "_");
      pF = strcat(DEMOGRAPHIC_PARAMETERS_CITY[k], FILE_LABEL);
      pF = strcat(DEMOGRAPHIC_PARAMETERS_CITY[k], ".dat");
    }
  }

  int No_of_OBSERVED_VARIABLES;
  double *** Observed_Population_Data;
  double **** Temporal_Evolution;

  if( EVALUATION == 1 ) {
    Observed_Population_Data = (double ***)calloc(No_of_CITIES, sizeof(double **) );
    for(k = 0; k<No_of_CITIES; k++) {
      Observed_Population_Data[k] = (double **)calloc(SUB_OUTPUT_VARIABLES, sizeof(double *) );
      for(n = 0; n < SUB_OUTPUT_VARIABLES; n++) {
	Observed_Population_Data[k][n] = (double *)calloc(I_Time, sizeof(double) );
      }
    }

    No_of_SETS_MAX  = 10000;

    Temporal_Evolution = (double ****)calloc(No_of_CITIES, sizeof(double ***) );
    for(k = 0; k < No_of_CITIES; k++) {
      Temporal_Evolution[k] = (double ***)calloc(SUB_OUTPUT_VARIABLES, sizeof(double **) );
      for(n = 0; n < SUB_OUTPUT_VARIABLES; n++) {
	Temporal_Evolution[k][n] = (double **)calloc(No_of_SETS_MAX, sizeof(double *) );
	for(j = 0; j < No_of_SETS_MAX; j++) {
	  Temporal_Evolution[k][n][j] = (double *)calloc(I_Time, sizeof(double) );
	}
      }
    }

    Demo_Data = (double **)calloc(No_of_SETS_MAX, sizeof(double *));
    for(i=0; i<No_of_SETS_MAX; i++)
      Demo_Data[i] = (double *)calloc(No_of_PARAMETERS, sizeof(double));

    TEMPORAL_EVOLUTION_FILE = (FILE ***)calloc( No_of_CITIES, sizeof(FILE **) );
    for(k = 0; k<No_of_CITIES; k++) {
      TEMPORAL_EVOLUTION_FILE[k] = (FILE **)calloc( SUB_OUTPUT_VARIABLES, sizeof(FILE *) );
      for(i=0; i<SUB_OUTPUT_VARIABLES; i++) {
	TEMPORAL_EVOLUTION_FILE[k][i] = fopen(TIME_EVOLUTION_FILE_NAME[k][i], "w");
	for(j = 0; j<I_Time; j++)
	  fprintf(TEMPORAL_EVOLUTION_FILE[k][i], "%g\t", Time.Time_Vector[j]);
	fprintf(TEMPORAL_EVOLUTION_FILE[k][i], "\n");
      }
    }
  }
  else {
    DEMO = (FILE **)calloc( No_of_CITIES, sizeof(FILE *) );
    for(k = 0; k<No_of_CITIES; k++) {
      DEMO[k] = fopen(DEMOGRAPHIC_PARAMETERS_CITY[k], "w");
      fprintf(DEMO[k], "City\t");
      for(i=0; i<No_of_PARAMETERS; i++) {
	key = Space->Parameter_Index[i];
	fprintf(DEMO[k], "%s\t", Table.Symbol_Parameters[key]);
      }
      // fprintf(DEMO[k], "Alpha\t");
      for(i=0; i<No_of_IC; i++) {
	key = Initial_Condition_Space->Parameter_Index[i];
	fprintf(DEMO[k], "%s\t", Table.Model_Variable_Symbol[key]);
      }
      for(i=0; i<No_of_ERROR_PARAMETERS; i++) {
	key = Error_Space->Parameter_Index[i];
	if(key < OUTPUT_VARIABLES_GENUINE)
	  fprintf(DEMO[k], "Error(%s)\t", Table.Output_Variable_Symbol[key]);
	else
	fprintf(DEMO[k], "Error_Parameter_%d\t", i);
      }
      fprintf(DEMO[k], "NegLogLike\t"); fprintf(DEMO[k], "Deviation\n");
    }
  }
  /*     E N D : ------------------------------------------------------ */

  int * REALIZATIONS = (int *)calloc( No_of_CITIES, sizeof(int) );

  for(k = 0; k<No_of_CITIES; k++) {

    if ( EVALUATION == 1 ) {
      // Reading_Demographic_Parameters_from_File(DEMOGRAPHIC_PARAMETERS_CITY[k], Demo_Data,
      // &No_of_PARAMETER_SETS, 5);
      Reading_Model_Parameters_from_File(DEMOGRAPHIC_PARAMETERS_CITY[k], Demo_Data,
					 &No_of_PARAMETER_SETS, No_of_PARAMETERS );

      assert(No_of_PARAMETER_SETS < No_of_SETS_MAX);
      printf("Set of Demographic Parameters (City: %s):\n", City_Names[k]);
      // Writing_Demographic_Parameters_Matrix(&Table, City_Names[k],
      // Demo_Data, No_of_PARAMETER_SETS, 5);
      Writing_Model_Parameters_Matrix(&Table, City_Names[k],
				      Demo_Data, No_of_PARAMETER_SETS, No_of_PARAMETERS );
      Realizations    = No_of_PARAMETER_SETS;
      REALIZATIONS[k] = No_of_PARAMETER_SETS; // Realizations = 1;
    }

    for( j = 0; j<Realizations; j++ ) {

      int SUB_OUTPUT_VARIABLES_0 = SUB_OUTPUT_VARIABLES;
      Reading_Standard_Data_Matrix_from_File( OBSERVED_DATA_FILE[k],
					      Empirical_Data_Matrix,
					      &SUB_OUTPUT_VARIABLES, I_Time,
					      0, Name_of_Rows,
					      0, Time.Time_Vector );

      Writing_Standard_Data_Matrix(Empirical_Data_Matrix,
				   SUB_OUTPUT_VARIABLES, I_Time,
				   0, Name_of_Rows,
				   0, Time.Time_Vector);

      assert( SUB_OUTPUT_VARIABLES == 2);

      No_of_OBSERVED_VARIABLES = SUB_OUTPUT_VARIABLES;

      if( EVALUATION == 1) SUB_OUTPUT_VARIABLES = SUB_OUTPUT_VARIABLES_0;

      /* B E G I N : Reserving memmory for Observed Data and Fitting Structure */
      Observed_Data * Data = (Observed_Data *)calloc(1, sizeof(Observed_Data));
      Observed_Data_Alloc( Data, No_of_OBSERVED_VARIABLES, I_Time);
      Observed_Data_Initialization( Data, No_of_OBSERVED_VARIABLES, I_Time,
				    Empirical_Data_Matrix,
				    City_Names[k] );
      printf(" Observe_Data structure has been correctly allocated and initiated\n");
      /*     E N D : ------------------------------------- */

      Parameter_Fitting * F = (Parameter_Fitting*)calloc(1,sizeof(Parameter_Fitting));
      F->Data         = Data;
      F->Space        = Space;
      F->Table        = &Table;
      F->Verbose      = 0; // 1: Verbose                // 0: Non Verbose
      F->Minimization = 1; // 1: Function Minimization  // 0: Function Evaluation
      F->Bounded_Parameter_Set = 1;
      F->Function     = GSL_Function_to_Minimize; // GSL_Function_to_Minimize_Error_Model;

      /* Initial conditions from empirical data at the initial time ( -xn 0 ) */
      printf("... calculating city: %s\n", City_Names[k]);

      Parameter_Model_Copy_into_Parameter_Table(&Table, Initial_Guess);
      if ( EVALUATION == 1 ) {
	// Uploading_Demographic_Parameters_into_Parameter_Table(&Table, Demo_Data, j);
	Uploading_Model_Parameters_into_Parameter_Table(&Table, Demo_Data, j);
	F->Minimization = 0;
      }
      else {
      // Random_Initial_Guess_within_Boundaries_Table(&Table, Space);
	F->Minimization = Random_Initial_Guess_within_Boundaries_and_Data(&Table, Space,
									  Empirical_Data_Matrix, 4);
      }
      int No_of_EMPIRICAL_TIMES = 17;
      // Number of columns in the data files of time-dependent parameters
      Time_Dependence_Control_Upload(&Time, &Time_Dependence, &Table,
                                     I_Time, No_of_EMPIRICAL_TIMES,
                                     TIME_DEPENDENT_PARAMETERS, TYPE_of_TIME_DEPENDENCE,
                                     TYPE_0_PARAMETERS, TYPE_1_PARAMETERS, TYPE_2_PARAMETERS,
                                     No_of_COVARIATES,
                                     dependent_parameter, forcing_pattern,
                                     "File_of_Covariates.dat", TIME_PARAMETERS_FILE[k]);

      assert( Time_Dependence.No_of_TIMES == I_Time );
      // If Initial Guess is bad, then F->Minimiation will be 0 and no
      // minimization will be performed.
      // 1: Function Minimization  // 0: Function Evaluation
      Initial_Condition_from_Data_into_Parameter_Table (&Table, Empirical_Data_Matrix);

      if( F->Verbose ) {
	if(Table.No_of_IC > 0)
	  Parameter_Space_Write_Min_Max_IC_Values (Initial_Condition_Space, &Table );
	printf("\n");
	if(Table.No_of_ERROR_PARAMETERS > 0)
	  Parameter_Space_Write_Min_Max_Error_Values (Error_Space, &Table );
	printf("\n");
	Parameter_Space_Write_Min_Max_Values (Space, &Table );
	printf("\n");
      }

      if (EVALUATION == 0) {
	printf(" Simplex bounded optimization starts right at this point within the\n");
	printf(" parameter space boundaries given above\n");
      }

      Min_Value = GSL_Minimization_Driver( F );

      if( Min_Value == DBL_MAX || F->Bounded_Parameter_Set == 0) {
	if ( F->Verbose ) printf("Optimization process failed for current seed:\n");

	if (Min_Value == DBL_MAX) if ( F->Verbose ) printf("Error in simplex\n");
	else if ( F->Verbose ) printf("Current paramater optimal set is out of bounds\n");

	for(i=0; i<No_of_PARAMETERS; i++) {
	  key = Space->Parameter_Index[i];
	  value = AssignStructValue_to_VectorEntry(key, &Table);
	  if ( F->Verbose ) printf("%s = %g  ", Table.Symbol_Parameters[key], value);
	}
	if ( F->Verbose ) printf("\n");
      }
      else {
	printf("City %s:\t Min Value: D=%g\tBest Estimates: \n", City_Names[k],
	       Min_Value);

	if ( F->Minimization == 1 ) fprintf(DEMO[k], "%s\t", City_Names[k]);

	for(i=0; i<No_of_PARAMETERS; i++) {
	  key = Space->Parameter_Index[i];
	  value = AssignStructValue_to_VectorEntry(key, &Table);
	  if ( F->Verbose ) printf("%s = %g  ", Table.Symbol_Parameters[key], value);
	  if ( F->Minimization == 1 ) fprintf(DEMO[k], "%g\t", value);
	}
	for(i=0; i<No_of_IC; i++) {
	  key = Initial_Condition_Space->Parameter_Index[i];
	  value = Model_Variable_Initial_Condition_into_Vector_Entry_Table( key, &Table );
	  if ( F->Verbose ) printf("%s = %g  ", Table.Model_Variable_Symbol[key], value);
	  if ( F->Minimization == 1 ) fprintf(DEMO[k], "%g\t", value);
	}
	for(i=0; i<No_of_ERROR_PARAMETERS; i++) {
	  key = Error_Space->Parameter_Index[i];
	  value = Error_Model_into_Vector_Entry_Table( key, &Table );
	  if(key < OUTPUT_VARIABLES_GENUINE)
	    if ( F->Verbose ) printf("%s = %g  ", Table.Output_Variable_Symbol[key], value);
	  else
	    if ( F->Verbose ) printf("Error_Parameter_%d = %g  ", i, value);
	  if ( F->Minimization == 1 ) fprintf(DEMO[k], "%g\t", value);
	}
	if ( F->Minimization == 1 ) fprintf(DEMO[k], "%g\t", Min_Value);

	if ( F->Minimization == 1 ) {
	  Discrepancy_Value = Discrepancy_Fraction_Female_Sexual_Worker (&Table,
									 Empirical_Data_Matrix);

	  if (F->Verbose) printf("Discrepancy between theory and data (sexual worker fraction): %g\n",
				 Discrepancy_Value);

	  fprintf(DEMO[k], "%g\n", Discrepancy_Value );
	}

	// if (EVALUATION == 1) getchar();
	printf("\n\n");
      }

      printf(" %s: Population at year 2000: %g\n", City_Names[k], Table.INITIAL_TOTAL_POPULATION);
      printf("\n\n");

      if ( EVALUATION == 1 ) {
	for(n = 0;  n < SUB_OUTPUT_VARIABLES; n++) {
	  for( i = 0; i < I_Time; i++ ) {
	    Temporal_Evolution[k][n][j][i]    = Table.Matrix_Output_Variables[n][i];
	    if (n < No_of_OBSERVED_VARIABLES )
	      Observed_Population_Data[k][n][i] = F->Data->N[n][i];

	    fprintf(TEMPORAL_EVOLUTION_FILE[k][n], "%g\t", Table.Matrix_Output_Variables[n][i]);
	  }
	  fprintf(TEMPORAL_EVOLUTION_FILE[k][n], "\n");
	}
      }

      Observed_Data_Free(Data);
      free(Data);
      free(F);
    }

    if ( EVALUATION == 1 )
      for (n=0; n < SUB_OUTPUT_VARIABLES; n++) fclose(TEMPORAL_EVOLUTION_FILE[k][n]);

    if ( EVALUATION == 0 ) fclose(DEMO[k]);
    else { printf("Evaluating hypothesis %s\n", FILE_LABEL); } // getchar();

  }

#if defined CPGPLOT_REPRESENTATION
  if( EVALUATION == 1 ) {
    int SAME;
    double Ini_Year;
    double * x_Data = (double *)calloc( I_Time, sizeof(double) );
    double * y_Data = (double *)calloc( I_Time, sizeof(double) );
    char * Out_Var_Symbol = (char *)calloc(10, sizeof(char) );
    char * Title = (char *)calloc(200, sizeof(char) );
    /* BEGIN : ------------------------------------------------------------------------
     * Time Evolution Distributions across Cities, Parameter Sets, and Output Variables
     */
    for(k = 0; k<No_of_CITIES; k++) {

      Realizations = REALIZATIONS[k];

      Title[0] = '\0';
      pF = strcat(Title, City_Names[k]);
      pF = strcat(Title, " - ");
      pF = strcat(Title, FILE_LABEL);

      for (n=0; n<SUB_OUTPUT_VARIABLES; n++) {

	SAME = 0;

	// if( n == (SUB_OUTPUT_VARIABLES-1) ) Realizations = 1;

	Table.CPG->CPG__PANEL__X =  1;
	Table.CPG->CPG__PANEL__Y =  2;
	Table.CPG->type_of_Width =  5;
	Table.CPG->color_Index   =  3;
	Table.CPG->type_of_Symbol = 1;

	Ini_Year = 2000.0;
	key = Table.OUTPUT_VARIABLE_INDEX[n];
	AssignCPGPLOT_Symbol_to_Output_Variables(key, Out_Var_Symbol, &Table);

	Table.CPG->CPG_SCALE_X   = 1;        Table.CPG->CPG_SCALE_Y   =  0;
	Table.CPG->CPG_RANGE_X_0 = 1999.5;   Table.CPG->CPG_RANGE_Y_0 =  0.0;
	Table.CPG->CPG_RANGE_X_1 = 2016.5;   Table.CPG->CPG_RANGE_Y_1 =  1.0E+05;

	// if( n == (SUB_OUTPUT_VARIABLES-2) )  Table.CPG->CPG_SCALE_Y   =  1;
	// if( n == (SUB_OUTPUT_VARIABLES-2) )  Table.CPG->CPG_RANGE_Y_0 =  0.0;
	// if( n == (SUB_OUTPUT_VARIABLES-2) )  Table.CPG->CPG_RANGE_Y_1 =  0.7;

	for( j = 0; j<Realizations; j++ ) {
	  printf("City %s:\t Set ID: %d\n", City_Names[k], j);

	  for(i=0; i < I_Time; i++) {

	    y_Data[i] = Temporal_Evolution[k][n][j][i];
	    x_Data[i] = Ini_Year + i;


	  }
	  printf("\n");


	  CPGPLOT___X_Y___P_L_O_T_T_I_N_G___S_A_M_E___P_L_O_T  ( Table.CPG, SAME,
								 I_Time,
								 x_Data, y_Data,
								 "Year",
								 Out_Var_Symbol,
								 //City_Names[k],
								 Title,
								 Table.CPG->CPG_SCALE_X,
								 Table.CPG->CPG_SCALE_Y );
	  SAME = 1;
	}

	if ( n < No_of_OBSERVED_VARIABLES ) {
	  for(i=0; i < I_Time; i++) {
	    x_Data[i] = Ini_Year + i;
	    y_Data[i] = Observed_Population_Data[k][n][i];
	  }

	  Table.CPG->type_of_Symbol = 8;
	  Table.CPG->color_Index    = 1;

	  CPGPLOT___X_Y___S_C_A_T_T_E_R_E_D___S_A_M_E___P_L_O_T ( Table.CPG, SAME,
								  I_Time,
								  x_Data, y_Data,
								  "Year",
								  Out_Var_Symbol,
								  // City_Names[k],
								  Title,
								  Table.CPG->CPG_SCALE_X,
								  Table.CPG->CPG_SCALE_Y );
	}

	getchar();
      }
    }
    free(x_Data); free(y_Data); free(Out_Var_Symbol); free(Title);
    // getchar();
  }
  /*   END : ------------------------------------------------------------------------
   */
#endif

  free(REALIZATIONS);

  /* BEGIN : Freeing All Memmory * * * * * * * * * * * * * * */
#if defined CPGPLOT_REPRESENTATION
#include <include.CPG.default.free.c>
#include <include.FILES_to_READ.default.free.c>
  P_A_R_A_M_E_T_E_R___C_P_G_P_L_O_T___F_R_E_E( Table.CPG, SUB_OUTPUT_VARIABLES );
  cpgclos();
#endif

  #include <include.Parameter_Space.default.free.c>
  Parameter_Space_Free(Space, No_of_PARAMETERS); free( Space );

  #include <include.Initial_Conditions.default.free.c>
  if( No_of_IC > 0 ) {
    Parameter_Space_Free(Initial_Condition_Space, No_of_IC);
  }
  free(Initial_Condition_Space);

  #include <include.Error_Control.default.free.c>
  if( No_of_ERROR_PARAMETERS > 0 ) {
    Parameter_Space_Free(Error_Space, No_of_IC);
  }
  free(Error_Space);

#include <include.Output_Variables.default.free.c>

#include <include.Time_Dependence_Control.default.free.c>
  if (TYPE_of_TIME_DEPENDENCE == 0) T_I_M_E___C_O_N_T_R_O_L___F_R_E_E( &Time, &Table );
  else                        Time_Dependence_Control_Free( &Time_Dependence, &Table );

  free(Name_of_Rows);
  for (i=0; i<SUB_OUTPUT_VARIABLES; i++)  free(Empirical_Data_Matrix[i]);
  free(Empirical_Data_Matrix);

  if( EVALUATION == 1 ) {
    for(i=0; i<No_of_SETS_MAX; i++) free(Demo_Data[i]);
    free(Demo_Data);

    for(k = 0; k<No_of_CITIES; k++) {
      for(n = 0; n < SUB_OUTPUT_VARIABLES; n++) {
	for(j = 0; j < No_of_SETS_MAX; j++) free( Temporal_Evolution[k][n][j] );
	free(Temporal_Evolution[k][n]);
	free(Observed_Population_Data[k][n]);
      }

      free(Temporal_Evolution[k]);
      free(Observed_Population_Data[k]);

      for(i = 0; i<SUB_OUTPUT_VARIABLES; i++) free(TIME_EVOLUTION_FILE_NAME[k][i]);
      free( TIME_EVOLUTION_FILE_NAME[k] );

      free( TEMPORAL_EVOLUTION_FILE[k] );
    }
    free(Temporal_Evolution);
    free(Observed_Population_Data);
    free(TIME_EVOLUTION_FILE_NAME);
    free(TEMPORAL_EVOLUTION_FILE);
  }

  for(k = 0; k<No_of_CITIES; k++) {
    free(TIME_PARAMETERS_FILE[k]);
    free(OBSERVED_DATA_FILE[k]);
    free(DEMOGRAPHIC_PARAMETERS_CITY[k]);
  }
  free(TIME_PARAMETERS_FILE);
  free(OBSERVED_DATA_FILE);
  free(DEMOGRAPHIC_PARAMETERS_CITY);

  if( EVALUATION == 0 ) free(DEMO);

  free(Initial_Guess);

  P_A_R_A_M_E_T_E_R___T_A_B_L_E___F_R_E_E( &Table );
  /*  END : Freeing  All Memmory * * * * * * * * * * * * * * */

  #include <gsl_random_number_Free.c>

  printf("\nEnd of progam\n");
  return (0);
}
