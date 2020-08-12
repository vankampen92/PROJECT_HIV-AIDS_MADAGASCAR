/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                            David Alonso, 2018 (c)                         */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#include <Include/MODEL.h>

#include "global.h"

gsl_rng * r; /* Global generator defined in main.c */

/* This code inspect parameter combinations of the ODE model describing temporal 
   evolution of the whole disease. Here, the goal is to analyze the different 
   parameter sets, which are read from corresponding files. 

   Parameters F_X, F_Y, \delta_X and \delta_Y have been already estimated from 
   demographic data and play the role of time-dependent extern parameters driving
   the system. See directory:

   ./TEMPORAL_EVOLUTION_r_FACTOR_ESTIMATE

   If the ODE model is required to run, then this TIME-DEPENDENT parameter
   files should be provided to be read by the program. F_X and F_Y are recruitment 
   rates into adutl sexually active life, and \delta_X and \delta_Y are adult 
   mortality rates. They change every year.  
   
   They are given in 'Time_Dependent_Parameters_Corrected_[CITY_NAME].dat' files.

   Compilation:

   . ~$ make X_MODEL=X2W2SILD Y_MODEL=YSILD

   The code is prepared to inspect parameter combinations from different 
   assumptions: 

   A. Parameters are searched under the hypothesis of constant ratio of female
   sexual workers to total female population: 
   
   B. Parameters are searched under the hypothesis of ratio of female
   sexual workers to total female population following a sigmoidal curve 
   with a break point in 2011.0 and smoothness parameters 0.1.

   C. As B, but with much contrained parameter ranges.

   Both B and C hypothesis can be generated under different sigmoidal curves, 
   this is, for different sigmoidal parameters (L_0 and T_0). This will define 
   sub-hypothesis within each of them: 
   
   B1 or C1: L_0 = 0.1 and T_0 = 2011
   B2 or C2: L_0 = 1.0 and T_0 = 2011

   Hypothesis A needs parameter sets of 17 parameters (-sP 17), while hypothesis B and C
   requires parameter sets of 20 parameters (-sP 20). 

   The command line may indicate which city, year,  for example, as follows:

   -Fn 2 -F0 Antananarivo -X0 0 -F1 2001

   -X0 0 represents the index of city Antananarivo (see array City_Names_All[] below).

   If this information is not given, the program goes over all cities and all years. 

   A. Parameters are searched under the hypothesis of constant ratio of female
   sexual workers to total female population: 

   Exectution: (Time-dependent parameters: -t4 1)

   . ~$ ./X2W2SILD-YSILD -y0 1                // TYPE of MODEL
   / -sP 17 -sN 100   -sT 1.0E-06             // Parameter Space of Model Parameters:  [-sP : Dimension, Number of Model Parameters to be optimized]
   / -I0 21 -H21 1.0   -m0 0.8  -M0 1.2     -A0 0.01      // Parameter: r_R
   / -I1 0  -H0 100.0  -m1 96.0 -M1 120.0   -A1 0.1       // Parameter: Beta_Y
   / -I2 8  -H8 100.0  -m2 96.0 -M2 120.0   -A2 0.1       // Parameter: Beta_X
   / -I3 12 -H12   9   -m3 1.0  -M3 19.0    -A3 0.01      // Parameter: Eta
   / -I4 7  -H7  9.0   -m4 0.0  -M4 99.0    -A4 0.01      // Parameter: mDelta
   / -I5 16 -H16 0.2   -m5 0.0  -M5 0.99    -A5 0.01      // Parameter: f_W
   / -I6 17 -H17 0.5   -m6 0.0  -M6 0.99    -A6 0.01      // Parameter: f_0
   / -I7 1  -H1 0.001  -m7 0.0  -M7 0.005   -A7 0.0001    // Parameter: p_XY
   / -I8 9  -H9 0.0005 -m8 0.0  -M8 0.001   -A8 0.0001    // Parameter: p_YX
   / -I9 5  -H5 1.5    -m9 0.5  -M9 4.0     -A9 0.01      // Parameter: Gamma
   / -I10 6 -H6 0.1    -m10 0.05 -M10 0.20  -A10 0.01     // Parameter: Mu
   / -I11 15 -H15 10.0 -m11 1.0 -M11 50.0   -A11 0.1      // Parameter: Xhi
   / -I12 10 -H10  0.01 -m12 0.0  -M12 0.05   -A12 0.01   // Parameter: Sigma_0
   / -I13 11 -H11  0.01 -m13 0.0  -M13 0.05   -A13 0.01   // Parameter: Sigam_0_r
   / -I14 18 -H18  0.01 -m14 0.0  -M14 0.05   -A14 0.01   // Parameter: Sigma_1
   / -I15 19 -H19  0.01 -m15 0.0  -M15 0.05   -A15 0.01   // Parameter: Sigma_1_r
   / -I16 20 -H20  0.1  -m16 0.08 -M16 0.12   -A16 0.01   // Parameter: Alpha

   / -en 0 -eP0 17 -eV 1.0              // Parameter Space of Error Model        [-en Number of Error Model-related parameters to be optimized: -eP0 17 [Error_Parameter_0]
   / -n 3  -v0 6 -v1 4 -v2 14           // Output/Observed Varables:             [-n  Number of Observed Variables]
   / -iP 0                              // Parameter Space of Initial Conditions [-iP Number of Initial Condition Variables to be optimized]
   / -i0  9 -u0 0.0 -U0 100.0
   /- i1 17 -u1 0.0 -U1 100.0
   / -G0 1  -G1 3 -tn 17 -t0 2000.0 -t1 2016.0 -t4 1 -xn 0 -xR 1  // Arguments Controling Numerical Integration
   / -DP 4  -DC 0 -D0 0 -D1 4 -D2 0 -P0 13 -a0 0  -P1 2 -a1 0  -P2 3 -a2 0  -P3 4 -a3 0 // Arguments controling type of time dependence of model parameters.

   . ~$ ./X2W2SILD-YSILD -y0 1 -G0 5 -G1 4 -n 3 -v0 6 -v1 4 -v2 14 -en 0 -iP 0 -tn 17 -t0 2000.0 -t1 2016.0 -Fn 2 -F0 Antananarivo -X0 0 -F1 2001
   
   No numerical integration is performed. Therefore, the arguments: 
	
   -t4 1 -xn 0 -xR 1 -DP 4  -DC 0 -D0 0 -D1 4 -D2 0 -P0 13 -a0 0  -P1 2 -a1 0  -P2 3 -a2 0  -P3 4 -a3 0 -tE 2.0 
   
   are not necessary. 	

   B. Parameters are searched under the hypothesis of ratio of female
   sexual workers to total female population following a sigmoidal curve 
   with a break point in 2011.0 and smoothness parameters 0.1. This estimates
   are generated in ./OBSERVED_DATA_FILES_PREPARATION and resulting files 
   are *_Sigmoidal.dat files.  
   
   In this case, the set of demographic parameters include three new parameters controling 
   a corresponding break point in parameters Sigma_0 and Sigma_1. In addition, a new 
   parameters D_Sigma has a sigmoidal time dependence (parameters 22), which 
   imposes a time dependence in Sigma_0 and Sigma_1 through:
   
   Sigma_0(t) = Sigma_0 + D_Sigma(t)
   Sigma_1(t) = Simga_1 + D_Sigma(t) 

   . ~$ ./X2W2SILD-YSILD -y0 1                // TYPE of MODEL
   / -sP 20 -sN 100   -sT 1.0E-06             // Parameter Space of Model Parameters:  [-sP : Dimension, Number of Model Parameters to be optimized]
   / -I0 21  -H21 1.0   -m0 0.0   -M0 2.0     -A0 0.01      // Parameter: r_R
   / -I1 0   -H0 100.0  -m1 0.0   -M1 200.0   -A1 0.1       // Parameter: Beta_Y
   / -I2 8   -H8  50.0  -m2 0.0   -M2 100.0   -A2 0.1       // Parameter: Beta_X
   / -I3 12  -H12   9   -m3 1.0   -M3 20.0    -A3 0.01      // Parameter: Eta
   / -I4 7   -H7  9.0   -m4 1.0   -M4 99.0    -A4 0.01      // Parameter: mDelta
   / -I5 16  -H16 0.2   -m5 0.0   -M5 0.99    -A5 0.01      // Parameter: f_W
   / -I6 17  -H17 0.5   -m6 0.0   -M6 0.99    -A6 0.01      // Parameter: f_0
   / -I7 1   -H1 0.03   -m7 0.0   -M7 0.10    -A7 0.001     // Parameter: p_XY
   / -I8 9   -H9 0.01   -m8 0.0   -M8 0.10    -A8 0.001     // Parameter: p_YX
   / -I9 5   -H5 1.5    -m9 0.0   -M9 10.0    -A9 0.1       // Parameter: Gamma
   / -I10 6  -H6 0.2    -m10 0.0  -M10 1.0    -A10 0.01     // Parameter: Mu
   / -I11 15 -H15 10.0  -m11 1.0  -M11 100.0  -A11 0.1      // Parameter: Xhi
   / -I12 10 -H10  0.01 -m12 0.0  -M12 0.05   -A12 0.01     // Parameter: Sigma_0
   / -I13 11 -H11  0.01 -m13 0.0  -M13 0.05   -A13 0.01     // Parameter: Sigam_0_r
   / -I14 18 -H18  0.01 -m14 0.0  -M14 0.05   -A14 0.01     // Parameter: Sigma_1
   / -I15 19 -H19  0.01 -m15 0.0  -M15 0.05   -A15 0.01     // Parameter: Sigma_1_r
   / -I16 20 -H20  0.1  -m16 0.08 -M16 0.12   -A16 0.01     // Parameter: Alpha
   / -I17 23 -H23  0.4  -m17 0.0  -M17 5.0    -A17 0.01     // Parameter: A_0  Magnitud of the jump 
   / -I18 24 -H24  3.0  -m18 0.0  -M18 5.0    -A18 0.01     // Parameter: L_0  Smoothness of the jump
   / -I19 25 -H25  2013 -m19 2009 -M19 2013.0 -A19 0.1      // Parameter: T_0  Time of the jump  

   / -en 0 -eP0 17 -eV 0.2              // Parameter Space of Error Model        [-en Number of Error Model-related parameters to be optimized: -eP0 17 [Error_Parameter_0]
   / -n 3  -v0 6 -v1 4 -v2 14           // Output/Observed Varables:             [-n  Number of Observed Variables]
   / -iP 0                              // Parameter Space of Initial Conditions [-iP Number of Initial Condition Variables to be optimized]
   / -i0  9 -u0 0.0 -U0 100.0
   /- i1 17 -u1 0.0 -U1 100.0
   / -G0 1  -G1 3 -tn 17 -t0 2000.0 -t1 2016.0 -t4 1 -xn 0 -xR 1  // Arguments Controling Numerical Integration
   / -DP 4  -DC 0 -D0 0 -D1 4 -D2 0 -P0 13 -a0 0  -P1 2 -a1 0  -P2 3 -a2 0  -P3 4 -a3 0 // Arguments controling type of time dependence of model parameters.
   / -Fn 1 -F0 ../../DATA_FILES/2019.05.31_Demographic_Parameters_per_City_NLL.dat

   . ~$ ./X2W2SILD-YSILD -y0 1 -G0 5 -G1 4 -n 3 -v0 6 -v1 4 -v2 14 -en 0 -iP 0 -tn 17 -t0 2000.0 -t1 2016.0 -Fn 2 -F0 Antananarivo -X0 0 -F1 2001

   No numerical integration is performed. Therefore, the arguments: 
        
      -t4 1 -xn 0 -xR 1 -DP 5  -DC 0 -D0 0 -D1 4 -D2 1 -P0 13 -a0 0  -P1 2 -a1 0  -P2 3 -a2 0  -P3 4 -a3 0 -P4 22 -a4 0 -tE 2.0  -Fn 2 -F0 Antananarivo -X0 0 -F1 2001
   
   are not necessary. 

   For both A and B hypothesis, it is possible to plot as output variables also other variables. 
   For instance:
   
   -n 4 -v0 6 -v1 4 -v2 17 -v3 18
   
   Variable 17 and 18 will show the sigmoidal evolution of parameters Sigma_0 and Sigma_1 through time. 

   To read the whole parameter list from a file, execute:

   . ~$ ./X2W2SILD-YSILD $(cat Arguments_Command_Line_Antananarivo.dat)

   -xn TYPE of INITIAL CONDITION (0 from default values in Parameter Table (Input Args); 1 at Random; 2 from fixed/stationary Point)
   -xN INITIAL TOTAL POPULATION SIZE
   -t4 TYPE of TIME DEPENDENCE (0, no parameter time dependence). If the TYPE of TIME DEPENDENCE input argument is greater than 0, time dependence parameters are at play and time dependence files are required. See also ./Definition_Numerical_Integration/XWSILD-YSILD/deterministic_time_dynamics.c

   See file denition_OutPut_Variables.c for full -v?? input argument code definitions. Examples are:

   -v0  0   Effective Average Fraction of Infectious Females
   -v1  1   Effective Average Fraction of Infectious Males
   -v1  4   Total Female Sexual Worker Population
   -v2  2   Total Female Population
   -v3  6   Total Population
   -v4  7   Total Disease Prevalence
   -v5  8   Total Female Disease Prevalence
   -v6  9   Total Male_Disease Prevalence
   -v7 10   Total Female Sexual Worker Disease Prevalence
   -v8 12   Female Sexual Worker Fraction

   C. Parameters are searched under the same hypothesis as B, but all parameter ranges are chosen 
   to be maximally constrained in agreement with  the information we have about the behavior of 
   the disease. As in B, parameters are searched under the hypothesis of ratio of female sexual 
   workers to total female population following a sigmoidal curve with a break point in 2011.0 
   and smoothness parameters 0.1. This pseudo-data are generated in 
   
   ./OBSERVED_DATA_FILES_PREPARATION 
   
   and resulting files are *_Sigmoidal.dat files.  
   
   In this case, the set of demographic parameters include three new parameters controling 
   a break point in parameters Sigma_0 and Sigma_1. These three parameters are A_0, L_0 and 
   T_0, which are also object to search. In addition, a new parameters D_Sigma has a sigmoidal 
   time dependence (parameter 22), which imposes a time dependence in Sigma_0 and Sigma_1 
   through:
   
   Sigma_0(t) = Sigma_0 + D_Sigma(t)
   Sigma_1(t) = Simga_1 + D_Sigma(t) 

   Exectution: (Time-dependent parameters: -t4 1)

   . ~$ ./X2W2SILD-YSILD -y0 1                // TYPE of MODEL
   / -sP 12 -sN 2500   -sT 1.0E-08            // Parameter Space of Model Parameters:  [-sP : Dimension, Number of Model Parameters to be optimized]
   / -I0 21 -H21 1.0   -m0 0.8  -M0 1.2     -A0 0.01      // Parameter: r_R
   / -I1 0  -H0 100.0  -m1 96.0 -M1 120.0   -A1 0.1       // Parameter: Beta_Y
   / -I2 8  -H8 100.0  -m2 96.0 -M2 120.0   -A2 0.1       // Parameter: Beta_X
   / -I3 12 -H12   9   -m3 1.0  -M3 19.0    -A3 0.01      // Parameter: Eta
   / -I4 7  -H7  9.0   -m4 0.0  -M4 99.0    -A4 0.01      // Parameter: mDelta
   / -I5 16 -H16 0.2   -m5 0.0  -M5 0.99    -A5 0.01      // Parameter: f_W
   / -I6 17 -H17 0.5   -m6 0.0  -M6 0.99    -A6 0.01      // Parameter: f_0
   / -I7 1  -H1 0.001  -m7 0.0  -M7 0.005   -A7 0.0001     // Parameter: p_XY
   / -I8 9  -H9 0.0005 -m8 0.0  -M8 0.001   -A8 0.0001     // Parameter: p_YX
   / -I9 5  -H5 1.5    -m9 0.5  -M9 4.0     -A9 0.01       // Parameter: Gamma
   / -I10 6 -H6 0.1    -m10 0.05 -M10 0.20  -A10 0.01     // Parameter: Mu
   / -I11 15 -H15 10.0 -m11 1.0 -M11 50.0   -A11 0.1      // Parameter: Xhi
   / -I12 10 -H10  0.01 -m12 0.0  -M12 0.05   -A12 0.01     // Parameter: Sigma_0
   / -I13 11 -H11  0.01 -m13 0.0  -M13 0.05   -A13 0.01     // Parameter: Sigam_0_r
   / -I14 18 -H18  0.01 -m14 0.0  -M14 0.05   -A14 0.01     // Parameter: Sigma_1
   / -I15 19 -H19  0.01 -m15 0.0  -M15 0.05   -A15 0.01     // Parameter: Sigma_1_r
   / -I16 20 -H20  0.1  -m16 0.08 -M16 0.12   -A16 0.01     // Parameter: Alpha                        In ./TEMPORAL_EVOLUTION_DEMOGRAPHY_PARAMETERS:
   / -I17 23 -H23  0.4  -m17 0.0  -M17 5.0    -A17 0.01     // Parameter: A_0  Magnitud of the jump    // -I5 23 -H23  0.01 -m5 0.0  -M5 0.5  -A5 0.01           // Parameter: A_0 
   / -I18 24 -H24  3.0  -m18 0.0  -M18 5.0    -A18 0.01     // Parameter: L_0  Smoothness of the jump  // -I6 24 -H24  0.01 -m6 0.0  -M6 2.0  -A6 0.01           // Parameter: L_0  
   / -I19 25 -H25  2013 -m19 2009 -M19 2013.0 -A19 0.1      // Parameter: T_0  Time of the jump        // -I7 25 -H25  2011.0 -m7 2009.0 -M7 2013.0 -A7 0.1      // Parameter: T_0 

   // City-specific demographic parameters (Antananarivo):
   / -H10  0.0325332                          // Parameter: Sigma_0
   / -H11  0.704745                           // Parameter: Sigma_0_r
   / -H18  0.0265231                          // Parameter: Sigma_1
   / -H19  0.550609                           // Parameter: Sigma_1_r
   / -H20  0.056651                           // Parameter: Alpha
   / -H23  0.48356                            // Parameter: A_0  Magnitud of the jump 
   / -H24  3.02678                            // Parameter: L_0  Smoothness of the jump
   / -H25  2013                               // Parameter: T_0  Time of the jump 

   / -en 0 -eP0 17 -eV 0.2                    // Parameter Space of Error Model        [-en Number of Error Model-related parameters to be optimized: -eP0 17 [Error_Parameter_0]
   / -n 3  -v0 6 -v1 4 -v2 14                 // Output/Observed Varables:             [-n  Number of Observed Variables]
   / -iP 2                                    // Parameter Space of Initial Conditions [-iP Number of Initial Condition Variables to be optimized]
   / -i0  9 -u0 0.0 -U0 100.0
   /- i1 17 -u1 0.0 -U1 100.0
   / -G0 1  -G1 3 -tn 17 -t0 2000.0 -t1 2016.0 -t4 1 -xn 0 -xR 1  // Arguments Controling Numerical Integration
   / -DP 5  -DC 0 -D0 0 -D1 4 -D2 1 -P0 13 -a0 0  -P1 2 -a1 0  -P2 3 -a2 0  -P3 4 -a3 0 -P4 22 -a4 0 // Arguments controling type of time dependence of model parameters.

   . ~$ ./X2W2SILD-YSILD -y0 1 -G0 5 -G1 4 -n 3 -v0 6 -v1 4 -v2 14  -en 0  -iP 0  -tn 17 -t0 2000.0 -t1 2016.0 -Fn 2 -F0 Antananarivo -X0 0 -F1 2001
   
   . ~$ ./X2W2SILD-YSILD -y0 1 -G0 5 -G1 4 -n 3 -v0 6 -v1 4 -v2 14  -en 0  -iP 0  -tn 17 -t0 2000.0 -t1 2016.0 -Fn 2 -F0 Nosy_Be -X0 0 -F1 2000

   AIC (corrected) representation: 

   . ~$ ./X2W2SILD-YSILD -y0 1 -G0 5 -G1 2 -n 3 -v0 6 -v1 4 -v2 14  -en 0  -iP 0  -tn 17 -t0 2000.0 -t1 2016.0

   In no case, no numerical integration is performed. Therefore, the arguments: 
        
      -t4 1 -xn 0 -xR 1 -DP 5  -DC 0 -D0 0 -D1 4 -D2 1 -P0 13 -a0 0  -P1 2 -a1 0  -P2 3 -a2 0  -P3 4 -a3 0 -P4 22 -a4 0 -tE 2.0  
   
   are not necessary.

   Run also:

   . ~$ Run_Parameter_Sets_Inspection.sh

   for exhautive inspection.  
*/

int main(int argc, char **argv)
{
  FILE * FF;
  char * pF;
  int No_of_PARAMETER_SETS;
  int i, j, k, n, l, z, key, n_BINS;
  double kk, AIC, AIC_c; 
  double value, Min_Value, Min_Value_0;
  double Likelihood_Value, Average_Likelihood_Value, Standard_Error_Value, Ave, Var;
  double MIN_Y_0, MAX_Y_1;
  Parameter_Table Table;
  Time_Control Time;
  double * Time_Vector; 
  int I_Time_Total;
  Time_Dependence_Control Time_Dependence;
  double * AIC_Average;
  double * AIC_Variance;
  double ** Variable;
  double ** Variable_Per;
  int No_of_PERCENTILES = 5;
  double Per[] = {0.05, 0.25, 0.5, 0.75, 0.95};

  P_ARG = &Table;
  
#include "default.c"
  
  /* Command line arguments */
  if(argc>1) ArgumentControl(argc, argv);

  #include "include.Output_Variables.default.aux.c"
  P_A_R_A_M_E_T_E_R___T_A_B_L_E___A_L_L_O_C(   &Table );
  P_A_R_A_M_E_T_E_R___T_A_B_L_E___U_P_L_O_A_D( &Table, Index_Output_Variables );
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
 
#if defined CPGPLOT_REPRESENTATION
  /* CPG_DRIVER_NAME[0] = '\0';                                                   */
  /* p_CPG_Name = strcat( CPG_DRIVER_NAME, "Likelihood_per_Degree_of_Freedom_" ); */
  /* p_CPG_Name = strcat( CPG_DRIVER_NAME, ".ps/CPS" );                           */

  // Activating 1st Window 
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

  int No_of_SETS_MAX      = 80000;
  int No_of_INITIAL_YEARS ; // 11; (3 different initial years: 2000, 2001, and 2002)
  int No_of_CITIES_MAX    = 11;
  int No_of_CITIES        ; // 11
  //int Index_of_City[No_of_CITIES_MAX];
  int * Index_of_City = (int *)calloc( No_of_CITIES_MAX, sizeof(int) );
  
  char ** City_Names  = (char **)calloc( No_of_CITIES_MAX, sizeof(char *) );
  for (i=0; i<No_of_CITIES_MAX; i++) City_Names[i] = (char *)calloc(20, sizeof(char));
  
  const char * City_Names_All[] = { "Antananarivo",  "Antsiranana",
				    "Mahajanga",     "Toamasina",
				    "Fianarantsoa",  "Toliary",
				    "Taolagnaro",    "Moramanga",
				    "Antsirabe",     "Morondava",
				    "Nosy_Be" };
  int n_Year; 
  char * Year = (char *)calloc(30, sizeof(char));
  int No_of_INITIAL_YEARS_MAX = 15;
  char ** Year_List = (char **)calloc( No_of_INITIAL_YEARS_MAX, sizeof(char *) );
  for (i=0; i<No_of_INITIAL_YEARS_MAX; i++) {
    Year_List[i] = (char *)calloc( 10, sizeof(char) );
    sprintf(Year_List[i], "%d", 2000+i);
  }

  const char * FILE_LABEL_ALL[] = { "Sigmoidal",
				    "Sigmoidal_C1", "Sigmoidal_C2", "Sigmoidal_C3",
				    "Sigmoidal_C4", "Sigmoidal_C5", "Sigmoidal_C6", 
				    "Stasis", "Stasis_Non" };
  int No_of_HYPOTHESIS = 7;
  char ** FILE_LABEL = (char **)calloc( No_of_HYPOTHESIS, sizeof(char *) ); 
  for (i=0; i<No_of_HYPOTHESIS; i++) FILE_LABEL[i] = (char *)calloc( 50, sizeof(char) );
  int * Type_of_Hypothesis = (int *)calloc( No_of_HYPOTHESIS, sizeof(int) );

  char * AIC_FILE_NAME = (char *)calloc( 50, sizeof(char) ); 
 
  if ( No_of_HYPOTHESIS == 9 )
    for (i=0; i<No_of_HYPOTHESIS; i++) Type_of_Hypothesis[i] = i;
  else {
    // No_of_HYPOTHESIS = 5;
    // Type_of_Hypothesis[0] = 0; 
    // Type_of_Hypothesis[1] = 2;
    // Type_of_Hypothesis[2] = 5;
    // Type_of_Hypothesis[3] = 7;
    // Type_of_Hypothesis[4] = 8; 
    // No_of_HYPOTHESIS = 2;
    // Type_of_Hypothesis[0] = 2; 
    // Type_of_Hypothesis[1] = 5;
    No_of_HYPOTHESIS = 7;
    Type_of_Hypothesis[0] = 0; 
    Type_of_Hypothesis[1] = 1;
    Type_of_Hypothesis[2] = 2;
    Type_of_Hypothesis[3] = 3;
    Type_of_Hypothesis[4] = 4; 
    Type_of_Hypothesis[3] = 5;
    Type_of_Hypothesis[4] = 6; 
  }

  for (i=0; i<No_of_HYPOTHESIS; i++) {
      key = Type_of_Hypothesis[i];
      strcpy( FILE_LABEL[i], FILE_LABEL_ALL[key] );
  }
  
  if( No_of_FILES == 2 ) {
    No_of_CITIES        = 1;
    City_Names[0]       = Name_of_FILE[0];
    Index_of_City[0]    = F_x_GRID[0];

    No_of_INITIAL_YEARS = 1;
    strcpy(Year_List[0], Name_of_FILE[1]);
  }
  else{
    No_of_CITIES     = 11;  
    for(i=0; i<No_of_CITIES; i++) Index_of_City[i] = i; 

    /* No_of_CITIES     = 5;                    */
    /* Index_of_City[0] = 0;  // "Antananarivo" */
    /* Index_of_City[1] = 1;  // "Antsiranana"  */
    /* Index_of_City[2] = 6;  // "Taolagnaro"   */
    /* Index_of_City[3] = 7;  // "Moramanga"    */
    /* Index_of_City[4] = 10; // "Nosy_Be"      */
 
    for (i=0; i<No_of_CITIES; i++) {
      key = Index_of_City[i];
      strcpy( City_Names[i], City_Names_All[key] );
    }
    
    No_of_INITIAL_YEARS = 1;
  }
 
  /* B E G I N : File Names of Parameter Congigurations */
  char ** PARAMETER_SET_FILE   = (char **)calloc(No_of_CITIES, sizeof(char *) ); /* Input files */ 
  for(k = 0; k<No_of_CITIES; k++) {
    PARAMETER_SET_FILE[k]   = (char *)calloc( 100, sizeof(char) );
  }
  /*     E N D : ------------------------------------------------------------------------ */

  double ** Demo_Data    = (double **)calloc(No_of_SETS_MAX, sizeof(double *));
  char   ** Names_of_Rows = (char **)calloc(No_of_SETS_MAX, sizeof(char *) );
  for(i=0; i<No_of_SETS_MAX; i++) {
    Demo_Data[i] = (double *)calloc(MODEL_PARAMETERS_MAXIMUM+2, sizeof(double));
    Names_of_Rows[i] = (char *)calloc(50, sizeof(char));
  }

  double ***** Likelihood = (double *****)calloc(No_of_HYPOTHESIS, sizeof(double ****) );
  for(l=0; l<No_of_HYPOTHESIS; l++) { 
    Likelihood[l] = (double ****)calloc(No_of_CITIES, sizeof(double ***) );
    for (i=0; i<No_of_CITIES; i++) {
      Likelihood[l][i] = (double ***)calloc(No_of_INITIAL_YEARS, sizeof(double **) );
      for(j=0; j<No_of_INITIAL_YEARS; j++) {
	Likelihood[l][i][j] = (double **)calloc(MODEL_PARAMETERS_MAXIMUM+2, sizeof(double *) );
	for(k=0; k<MODEL_PARAMETERS_MAXIMUM+2; k++)
	  Likelihood[l][i][j][k] = (double *)calloc(No_of_SETS_MAX, sizeof(double) );
      }
    }
  }

  int *** sn = (int ***)calloc(No_of_HYPOTHESIS, sizeof(int **) );
  for(l=0; l<No_of_HYPOTHESIS; l++) { 
    sn[l] = (int **)calloc(No_of_CITIES, sizeof(int *) );
    for(k = 0; k<No_of_CITIES; k++)
      sn[l][k] = (int *)calloc(No_of_INITIAL_YEARS, sizeof(int) );
  }

  int No_of_COMMON_PARAMETERS = 17;
  int No_of_PARAMETERS_MAX    = 20; 
  
  for(l=0; l<No_of_HYPOTHESIS; l++) {

    if( l > 6 ) {  // Stasis or Stasis_Non Hypothesis
      No_of_PARAMETERS = 17; 
      I0 = 21;  min_P0 = 0.8;   MAX_P0 = 1.2;   Acc_P0 = 0.01; 
      I1 = 0;   min_P1 = 96.0;  MAX_P1 = 120.0; Acc_P1 = 0.1;
      I2 = 8;   min_P2 = 96.0;  MAX_P2 = 120.0; Acc_P2 = 0.1;
      I3 = 12;  min_P3 = 1.0;   MAX_P3 = 19.0;  Acc_P3 = 0.01;
      I4 = 7;   min_P4 = 0.0;   MAX_P4 = 99.0;  Acc_P4 = 0.01;
      I5 = 16;  min_P5 = 0.0;   MAX_P5 = 0.99;  Acc_P5 = 0.01;
      I6 = 17;  min_P6 = 0.0;   MAX_P6 = 0.99;  Acc_P6 = 0.01;
      I7 = 1;   min_P7 = 0.0;   MAX_P7 = 0.005; Acc_P7 = 0.0001;
      I8 = 9;   min_P8 = 0.0;   MAX_P8 = 0.001; Acc_P8 = 0.0001;
      I9 = 5;   min_P9 = 0.5;   MAX_P9 = 4.0;   Acc_P9 = 0.01;
      I10 = 6;  min_P10 = 0.05; MAX_P10 = 0.20; Acc_P10 = 0.01;
      I11 = 15; min_P11 = 1.0;  MAX_P11 = 100.0; Acc_P11 = 0.1;
      I12 = 10; min_P12 = 0.0;  MAX_P12 = 0.05; Acc_P12 = 0.01;
      I13 = 11; min_P13 = 0.0;  MAX_P13 = 0.05; Acc_P13 = 0.01;
      I14 = 18; min_P14 = 0.0;  MAX_P14 = 0.05; Acc_P14 = 0.01;
      I15 = 19; min_P15 = 0.0;  MAX_P15 = 0.05; Acc_P15 = 0.01;
      I16 = 20; min_P16 = 0.08; MAX_P16 = 0.12; Acc_P16 = 0.01;
    }
    else {        // Sigmoidal Hypothesis
      No_of_PARAMETERS = 20; 
      I0 = 21;  min_P0 = 0.8;   MAX_P0 = 1.2;        Acc_P0 = 0.01;
      I1 = 0;   min_P1 = 96.0;  MAX_P1 = 120.0;      Acc_P1 = 0.1;
      I2 = 8;   min_P2 = 96.0;  MAX_P2 = 120.0;      Acc_P2 = 0.1;
      I3 = 12;  min_P3 = 1.0;   MAX_P3 = 19.0;       Acc_P3 = 0.01;
      I4 = 7;   min_P4 = 0.0;   MAX_P4 = 99.0;       Acc_P4 = 0.01; 
      I5 = 16;  min_P5 = 0.0;   MAX_P5 = 0.99;       Acc_P5 = 0.01;
      I6 = 17;  min_P6 = 0.0;   MAX_P6 = 0.99;       Acc_P6 = 0.01;
      I7 = 1;   min_P7 = 0.0;   MAX_P7 = 0.005;      Acc_P7 = 0.0001;
      I8 = 9;   min_P8 = 0.0;   MAX_P8 = 0.001;      Acc_P8 = 0.0001;
      I9 = 5;   min_P9 = 0.5;   MAX_P9 = 4.0;        Acc_P9 = 0.01;
      I10 = 6;  min_P10 = 0.05; MAX_P10 = 0.20;      Acc_P10 = 0.01;
      I11 = 15; min_P11 = 1.0;  MAX_P11 = 100.0;      Acc_P11 = 0.1;
      I12 = 10; min_P12 = 0.0;  MAX_P12 = 0.05;      Acc_P12 = 0.01;
      I13 = 11; min_P13 = 0.0;  MAX_P13 = 0.05;      Acc_P13 = 0.01;
      I14 = 18; min_P14 = 0.0;  MAX_P14 = 0.05;      Acc_P14 = 0.01;
      I15 = 19; min_P15 = 0.0;  MAX_P15 = 0.05;      Acc_P15 = 0.01;
      I16 = 20; min_P16 = 0.08; MAX_P16 = 0.12;      Acc_P16 = 0.01;
      I17 = 23; min_P17 = 0.0;  MAX_P17 = 0.5;       Acc_P17 = 0.01;
      I18 = 24; min_P18 = 0.0;  MAX_P18 = 5.0;       Acc_P18 = 0.01;
      I19 = 25; min_P19 = 2009.0; MAX_P19 = 2013.0;  Acc_P19 = 0.1;
    }
    /* B E G I N : Reserving memmory for Parameter Space */
#include <include.Parameter_Space.default.aux.c>
    Parameter_Space * Space = (Parameter_Space *)calloc(1, sizeof(Parameter_Space));
    Parameter_Space_Alloc( Space, No_of_PARAMETERS, d);
    Parameter_Space_Initialization( Space, No_of_PARAMETERS, TOLERANCE, MAX_No_of_ITERATIONS,
				    d, Index, Ranges, Acc);
    Parameter_Table_Index_Update(Index, No_of_PARAMETERS, &Table);
    Table.S = Space;
    printf("Parameter_Space structure has been correctly allocated and initiated\n");
    /*     E N D : ------------------------------------- */
    
    I_Time_Total = I_Time;
    for(k = 0; k<No_of_CITIES; k++) {
      // k=8 is a city with no infection ("Antsirabe")
      if ( Index_of_City[k] != 8 ) {

	for(n=0; n < No_of_INITIAL_YEARS; n++) { // For each introduction time

	  Year[0]='\0';                 
	  strcpy (Year, Year_List[n]);  printf("Initial Year: %s\n", Year);
	  
	  n_Year = atoi(Year) - 2000; 
	  
	  /* B E G I N : Reading parameters sets ----------------------------------------------------
	   */
	  PARAMETER_SET_FILE[k][0] = '\0';
	  pF = strcat(PARAMETER_SET_FILE[k], "Full_Parameter_Set_");
	  pF = strcat(PARAMETER_SET_FILE[k], City_Names[k]);
	  pF = strcat(PARAMETER_SET_FILE[k], "_");
	  pF = strcat(PARAMETER_SET_FILE[k], Year);
	  pF = strcat(PARAMETER_SET_FILE[k], "_");
	  pF = strcat(PARAMETER_SET_FILE[k], FILE_LABEL[l]);
	  pF = strcat(PARAMETER_SET_FILE[k], "_Ordered.dat");
	  
	  Reading_Standard_Data_Matrix_from_File( PARAMETER_SET_FILE[k], Demo_Data,
						  &No_of_PARAMETER_SETS, No_of_PARAMETERS+2,
						  1, Names_of_Rows,
						  2, Time_Vector ); 
	  
	  assert( No_of_PARAMETER_SETS < No_of_SETS_MAX );
	  
	  Min_Value_0 = Demo_Data[0][No_of_PARAMETERS];
	  
	  Writing_Standard_Data_Matrix(Demo_Data, No_of_PARAMETER_SETS, No_of_PARAMETERS+2,
				       1, Names_of_Rows,
				       0, Time_Vector );
	  printf("Full Set of Parameters (City: %s, Year: %s) has been correctly uploaded:\n",
		 City_Names[k], Year);
	  // getchar(); 
	  /*     E N D : ---------------------------------------------------------------------------
	   */
	  
	  I_Time = I_Time_Total - n_Year;
	  Time_0 = 2000.0 + (double)n_Year;
	  Time_1 = 2016.0;
	  
	  int No_of_Parameter_Sets = No_of_PARAMETER_SETS;
	  
	  // if( No_of_PARAMETER_SETS > 2000 ) No_of_Parameter_Sets = 2000;

	  sn[l][k][n] = No_of_Parameter_Sets;
	  
	  for(j=0; j<No_of_Parameter_Sets; j++) {
	    
	    Min_Value        = Demo_Data[j][No_of_PARAMETERS];
	    Likelihood_Value = Demo_Data[j][No_of_PARAMETERS+1];
	    
	    printf(" City: %s [Year: %s]:\t", City_Names[k], Year);
	    printf(" NLL(0) = %g\t NLL(%d) = %g\n", Min_Value_0, j, Min_Value);
	    
	    Uploading_Model_Parameters_into_Parameter_Table(&Table, Demo_Data, j);

	    for(z=0; z<No_of_PARAMETERS; z++) Likelihood[l][k][n][z][j] = Demo_Data[j][z];
	      
	    Likelihood[l][k][n][No_of_PARAMETERS][j]   = Min_Value;
	    Likelihood[l][k][n][No_of_PARAMETERS+1][j] = Likelihood_Value;
	  }

	  if( sn[l][k][n] > 0 )
	      Average_and_Variance_double_Vector(Likelihood[l][k][n][No_of_PARAMETERS],
						 sn[l][k][n], &Ave, &Var);
	    
	  Average_Likelihood_Value = Ave;
	  Standard_Error_Value     = sqrt(Var);
	  
	  printf("Hypothesis: %s\t City: %s\t Introduction Year: %s\t NLL +/- SDErr: %g +/- %g\n",
		 FILE_LABEL[l], City_Names[k], Year, Average_Likelihood_Value,
		 Standard_Error_Value);
	  // getchar(); 
	}
	I_Time = I_Time_Total;
      }
    }
    
    Parameter_Space_Free(Space, No_of_PARAMETERS);
    free( Space );
  }
	
#if defined CPGPLOT_REPRESENTATION
  /* Representing overall results */
  Table.CPG->type_of_Width  = 4;
  Table.CPG->type_of_Symbol = 8;
  Table.CPG->color_Index    = 2;
  
  /* BEGIN : ------------------------------------------------------------------------
   * Likelihood distributions at each introduction year for each and every city and 
   * type of hypothesis  (corrected by degrees of freedom)
   */
  int dg_of_Freedom;
  double * x_Data;
  double * y_Data;
  int SAME;

  I_Time = I_Time_Total;
	 
  for (n=0; n<No_of_INITIAL_YEARS; n++) {
    for(k = 0; k<No_of_CITIES; k++) {
      if ( Index_of_City[k] != 8 ) { // k=8 is a city with no infection ("Antsirabe")
	Year[0]='\0';                 
	strcpy (Year, Year_List[n]);  printf("Initial Year: %s\n", Year);
	n_Year = atoi(Year) - 2000;

	Table.CPG->Title[0]='\0';
	pF = strcat(Table.CPG->Title, City_Names[k]);
	pF = strcat(Table.CPG->Title, " --- ");
	pF = strcat(Table.CPG->Title, Year);
	
	Table.CPG->CPG_SCALE_X   = 1;                        
	Table.CPG->CPG_RANGE_X_0 = 0.0;                      
	Table.CPG->CPG_RANGE_X_1 = (double)No_of_HYPOTHESIS + 1.0;
	
	Table.CPG->CPG_SCALE_Y   =  1;

	if( No_of_FILES == 2 ) {  
	  for(z=0;  z < No_of_PARAMETERS_MAX; z++) {
	    SAME = 0;
	    
	    Table.CPG->Y_label[0]='\0';
	    pF = strcat(Table.CPG->Y_label, Table.Symbol_Parameters_Greek_CPGPLOT[Index[z]] );
	    
	    MIN_Y_0 =  Likelihood[0][k][n][z][0];
	    MAX_Y_1 =  Likelihood[0][k][n][z][0];
	    for(l=0; l<No_of_HYPOTHESIS; l++) {
	      for(j=0; j < sn[l][k][n]; j++) {
		MIN_Y_0 = MIN( MIN_Y_0, Likelihood[l][k][n][z][j]);
		MAX_Y_1 = MAX( MAX_Y_1, Likelihood[l][k][n][z][j]);
	      }
	    }
	    Table.CPG->CPG_RANGE_Y_0 = MIN_Y_0;
	    Table.CPG->CPG_RANGE_Y_1 = MAX_Y_1;
	    
	    Table.CPG->CPG_RANGE_Y_0 = Ranges[0][z];
	    Table.CPG->CPG_RANGE_Y_1 = Ranges[1][z];
	    
	    for(l=0; l<No_of_HYPOTHESIS; l++) {
	      Table.CPG->color_Index    = 3+l;
	      
	      if( l < 6 || z < No_of_COMMON_PARAMETERS ) { 
		
		if( sn[l][k][n] > No_of_PERCENTILES * 10 ) {
		  
		  Variable_Per    = (double **)calloc(No_of_PERCENTILES, sizeof(double *) );
		  for(j = 0; j < No_of_PERCENTILES; j++ )
		    Variable_Per[j] = (double *)calloc(sn[l][k][n], sizeof(double) );
		  
		  Variable = (double **)calloc(sn[l][k][n], sizeof(double *) );
		  for(j = 0; j < sn[l][k][n]; j++ )
		    Variable[j] = (double *)calloc(1, sizeof(double) );
		  x_Data = (double *)calloc(1, sizeof(double) );
		  
		  for(j=0; j < sn[l][k][n]; j++) Variable[j][0] = Likelihood[l][k][n][z][j];
		  
		  x_Data[0] = (double)l+1.0;
		  
		  Percentile_Calculation_Simple(x_Data, Variable, 1, sn[l][k][n],
						Per, No_of_PERCENTILES,
						Variable_Per);
		  
		  cpgslct(Table.CPG->DEVICE_NUMBER);
		  CPGPLOT___B_O_X___P_L_O_T_T_I_N_G___S_A_M_E___P_L_O_T ( Table.CPG, SAME,
									  1,
									  x_Data, Variable_Per,
									  No_of_PERCENTILES,
									  "Type of Hypothesis",
									  Table.CPG->Y_label,
									  Table.CPG->Title,
									  Table.CPG->CPG_SCALE_X,
									  Table.CPG->CPG_SCALE_Y );
		  
		  for(j = 0; j < No_of_PERCENTILES; j++ ) free(Variable_Per[j]);
		  free(Variable_Per);
		  for(j = 0; j < sn[l][k][n]; j++ ) free(Variable[j]);
		  free(Variable);
		  free(x_Data);
		}
		else {
		  x_Data = (double *)calloc( sn[l][k][n], sizeof(double) );
		  y_Data = (double *)calloc( sn[l][k][n], sizeof(double) );
		  
		  for(j=0; j < sn[l][k][n]; j++) {
		    x_Data[j] = (double)l+1.0;
		    y_Data[j] = Likelihood[l][k][n][z][j];
		  }
		  
		  cpgslct(Table.CPG->DEVICE_NUMBER);
		  CPGPLOT___X_Y___S_C_A_T_T_E_R_E_D___S_A_M_E___P_L_O_T ( Table.CPG, SAME,
									  sn[l][k][n],
									  x_Data, y_Data,
									  "Type of Hypothesis",
									  Table.CPG->Y_label,
									  Table.CPG->Title,
									  Table.CPG->CPG_SCALE_X,
									  Table.CPG->CPG_SCALE_Y);
		  free(x_Data); free(y_Data);
		}
	      }
	      SAME = 1;
	    }
	  }
	  getchar();
	}	
	else {  // Only if No_of_FILES is not equal to 2, then likelihood represenation  
	  SAME = 0; 
	  Table.CPG->CPG_SCALE_Y   =  1; // 1
	  Table.CPG->CPG_RANGE_Y_0 =  450.0;   
	  Table.CPG->CPG_RANGE_Y_1 =  800.0; 
	  
	  AIC_Average  = (double *)calloc(No_of_HYPOTHESIS, sizeof(double));
	  AIC_Variance  = (double *)calloc(No_of_HYPOTHESIS, sizeof(double));
	  
	  for(l=0; l<No_of_HYPOTHESIS; l++) {
	    
	    Table.CPG->color_Index    = 3+l;
	    
	    x_Data = (double *)calloc( sn[l][k][n], sizeof(double) );
	    y_Data = (double *)calloc( sn[l][k][n], sizeof(double) );
	    
	    if( l > 6 ) No_of_PARAMETERS = 17; // Stasis or Stasis_Non Hypothesis
	    else        No_of_PARAMETERS = 20; // Sigmoidal Hypothesis
	    
	    dg_of_Freedom = (double)SUB_OUTPUT_VARIABLES*(double)(I_Time-1-n_Year)-(double)No_of_PARAMETERS;	  
	    for(j=0; j < sn[l][k][n]; j++) {
	      
	      x_Data[j] = (double)l+1.0;
	      
	      assert(dg_of_Freedom > 0.0); 
	      
	      if (dg_of_Freedom > 0.0) {
		kk  = (double)No_of_PARAMETERS;
		AIC = 2.0 * kk + 2.0 * Likelihood[l][k][n][No_of_PARAMETERS][j];
		AIC_c = AIC + (2.0*(kk-1)*kk)/((double)dg_of_Freedom - 1); 
		// y_Data[j] = Likelihood[l][k][n][No_of_PARAMETERS][j]/(double)dg_of_Freedom;
		y_Data[j] = AIC_c;
	      }
	      else  y_Data[j] = 0.0;
	      
	    }
	    printf("\n");
	    
	    cpgslct(Table.CPG->DEVICE_NUMBER);
	    CPGPLOT___X_Y___S_C_A_T_T_E_R_E_D___S_A_M_E___P_L_O_T ( Table.CPG, SAME,
								    sn[l][k][n],
								    x_Data, y_Data,
								    "Type of Hypothesis",
								    "AIC_c",
								    Table.CPG->Title,
								    Table.CPG->CPG_SCALE_X,
								    Table.CPG->CPG_SCALE_Y);
	    
	    if( sn[l][k][n] > 0 )
	      Average_and_Variance_double_Vector(y_Data, sn[l][k][n], &Ave, &Var);

	    printf("Hypothesis: %s\t %s: Introduction Time: %d\t Corrected Likelihood (Ave): %g\n",
		     FILE_LABEL[l], City_Names[k], 2000+n_Year, Ave);
	  
	    // AIC_Average[l] = Average_double_Vector(y_Data, sn[l][k][n]);
	    AIC_Average[l] = Ave;
	    AIC_Variance[l] = Var; 
	    
	    free(x_Data); free(y_Data);
	    SAME = 1;
	  }
	  
	  AIC_FILE_NAME[0] = '\0';
	  pF = strcat(AIC_FILE_NAME, "AIC_CORRECTED_");
	  pF = strcat(AIC_FILE_NAME, City_Names[k]);
	  pF = strcat(AIC_FILE_NAME, "_");
	  pF = strcat(AIC_FILE_NAME, Year);
	  pF = strcat(AIC_FILE_NAME, ".dat");
	  
	  FF = fopen(AIC_FILE_NAME, "w");
	  for(l=0; l<No_of_HYPOTHESIS; l++) fprintf(FF, "%g\t%g\t%g\t%g\n", (double)l,
						    AIC_Average[l],
						    AIC_Average[l]-sqrt(AIC_Variance[l]), 
						    AIC_Average[l]+sqrt(AIC_Variance[l])); 
	  fclose(FF); 					  
	  free(AIC_Average); 
	  free(AIC_Variance);
	  // getchar();
	}
	
	if( No_of_FILES == 2 ) {
	  // Activate C drawing estructure here to draw histograms from scratch for every
	  // city and year 
	  int No_of_PARAMETER_HISTOGRAMS = No_of_COMMON_PARAMETERS; // 17: total number of common parameters 
	  CPG__PANEL__X =  No_of_HYPOTHESIS;
	  CPG__PANEL__Y =  5; 
	  CPG_DRIVER_NAME[0] = '\0';
	  // p_CPG_Name = strcat( CPG_DRIVER_NAME, "Likelihood_per_Degree_of_Freedom_" );
	  // p_CPG_Name = strcat( CPG_DRIVER_NAME,  FILE_LABEL[l]);
	  p_CPG_Name = strcat( CPG_DRIVER_NAME, "/XSERVE" );
	  Parameter_CPGPLOT * C = A_C_T_I_V_A_T_E___C_P_G_P_L_O_T ( 2, I_Time, 0, CPG_DRIVER_NAME);
	  printf(" Parameter_CPGPLOT plotting structure has been correctly allocated and initiated\n");
	  
	  C->type_of_Width =  5;
	  C->color_Index  = 7;
	  
	  for(z=0;  z < No_of_PARAMETER_HISTOGRAMS; z++) { 
	    
	    C->X_label[0]='\0';
	    pF = strcat(C->X_label, Table.Symbol_Parameters_Greek_CPGPLOT[Index[z]] );
	    
	    for(l=0; l<No_of_HYPOTHESIS; l++) {
	      
	      C->Title[0]='\0';
	      pF = strcat(C->Title, City_Names[k]);
	      pF = strcat(C->Title, " - ");
	      pF = strcat(C->Title, Year);
	      pF = strcat(C->Title, " - ");
	      pF = strcat(C->Title, FILE_LABEL[l]);
	      
	      MIN_Y_0 =  Likelihood[l][k][n][z][0];
	      MAX_Y_1 =  Likelihood[l][k][n][z][0];
	      for(j=0; j < sn[l][k][n]; j++) {
		MIN_Y_0 = MIN( MIN_Y_0, Likelihood[l][k][n][z][j]); 
		MAX_Y_1 = MAX( MAX_Y_1, Likelihood[l][k][n][z][j]);
	      }   
	      C->CPG_SCALE_X   = 1;                        
	      C->CPG_RANGE_X_0 = MIN_Y_0;  				   
	      C->CPG_RANGE_X_1 = MAX_Y_1;
	      
	      C->CPG_RANGE_X_0 = Ranges[0][z];
	      C->CPG_RANGE_X_1 = Ranges[1][z];
	      
	      if ( sn[l][k][n] > 1000 )                            n_BINS = 100;
	      else if ( sn[l][k][n] < 1000 && sn[l][k][n] > 100 )  n_BINS = 50;
	      else                                                 n_BINS = 20;
	      
	      C->CPG_SCALE_Y   = 0;                        
	      C->CPG_RANGE_Y_0 = 0.0;  				   
	      C->CPG_RANGE_Y_1 = (double)sn[l][k][n]/(double)n_BINS * 10.0;
	      
	      x_Data = (double *)calloc( sn[l][k][n], sizeof(double) );
	      y_Data = (double *)calloc( sn[l][k][n], sizeof(double) );
	      
	      for(j=0; j < sn[l][k][n]; j++) x_Data[j] = Likelihood[l][k][n][z][j];
	      
	      cpgslct(C->DEVICE_NUMBER);
	      CPGPLOT___X_Y___H_I_S_T_O_G_R_A_M ( C, sn[l][k][n], x_Data, n_BINS,
						  C->X_label,
						  "Frequency",
						  C->Title,
						  C->CPG_SCALE_X,
						  C->CPG_SCALE_Y );
	      free(x_Data); free(y_Data);
	      SAME = 0;
	    }
	    if( (z+1)%C->CPG__PANEL__Y  == 0) getchar(); 
	    SAME = 0;
	  }
	
	  C->X_label[0]='\0';
	  pF = strcat(C->X_label, "NLL");
	  
	  for(l=0; l<No_of_HYPOTHESIS; l++) {
	    
	    C->Title[0]='\0';
	    pF = strcat(C->Title, City_Names[k]);
	    pF = strcat(C->Title, " - ");
	    pF = strcat(C->Title, Year);
	    pF = strcat(C->Title, " - ");
	    pF = strcat(C->Title, FILE_LABEL[l]);
	    
	    if( l > 6 ) No_of_PARAMETERS = 17; // Stasis or Stasis_Non Hypothesis
	    else        No_of_PARAMETERS = 20; // Sigmoidal Hypothesis
	    
	    MIN_Y_0 =  Likelihood[l][k][n][No_of_PARAMETERS][0];
	    MAX_Y_1 =  Likelihood[l][k][n][No_of_PARAMETERS][0];
	    for(j=0; j < sn[l][k][n]; j++) {
	      MIN_Y_0 = MIN( MIN_Y_0, Likelihood[l][k][n][No_of_PARAMETERS][j]); 
	      MAX_Y_1 = MAX( MAX_Y_1, Likelihood[l][k][n][No_of_PARAMETERS][j]);
	    }   
	    C->CPG_SCALE_X   = 1;                        
	    C->CPG_RANGE_X_0 = MIN_Y_0;  				   
	    C->CPG_RANGE_X_1 = MAX_Y_1;
	    
	    printf("City: %s\t Year: %s\t Type of Hypothesis: %s\n",
		   City_Names[k], Year_List[n], FILE_LABEL[l]);
	    printf("The likelihood is between %g and %g\n", MIN_Y_0, MAX_Y_1); 
	    
	    if ( sn[l][k][n] > 1000 )                            n_BINS = 100;
	    else if ( sn[l][k][n] < 1000 && sn[l][k][n] > 100 )  n_BINS = 50;
	    else                                                 n_BINS = 20;
	    
	    C->CPG_SCALE_Y   = 0;                        
	    C->CPG_RANGE_Y_0 = 0.0;  				   
	    C->CPG_RANGE_Y_1 = (double)sn[l][k][n]/(double)n_BINS * 10.0;
	    
	    x_Data = (double *)calloc( sn[l][k][n], sizeof(double) );
	    y_Data = (double *)calloc( sn[l][k][n], sizeof(double) );
	    
	    for(j=0; j < sn[l][k][n]; j++) x_Data[j] = Likelihood[l][k][n][No_of_PARAMETERS][j];
	    
	    cpgslct(C->DEVICE_NUMBER);
	    CPGPLOT___X_Y___H_I_S_T_O_G_R_A_M ( C, sn[l][k][n], x_Data, n_BINS,
						C->X_label,
						"Frequency",
						C->Title,
						C->CPG_SCALE_X,
						C->CPG_SCALE_Y );
	    free(x_Data); free(y_Data);
	    SAME = 0;
	    
	  }
	  getchar();
	  P_A_R_A_M_E_T_E_R___C_P_G_P_L_O_T___F_R_E_E( C, 2 );
	}
      }
    }
  }
  /*   END : ------------------------------------------------------------------------
   */  
#endif

  /* BEGIN : Freeing All Memmory * * * * * * * * * * * * * * */

  #if defined CPGPLOT_REPRESENTATION
  P_A_R_A_M_E_T_E_R___C_P_G_P_L_O_T___F_R_E_E( Table.CPG, SUB_OUTPUT_VARIABLES );
  cpgclos();
  #endif

  #include <include.Parameter_Space.default.free.c>
  /* Parameter_Space_Free(Space, No_of_PARAMETERS); free(Space); */

  if( No_of_IC > 0 ) {
  #include <include.Initial_Conditions.default.free.c>
    Parameter_Space_Free(Initial_Condition_Space, No_of_IC); free(Initial_Condition_Space); 
  }
  free(Initial_Condition_Space);

  if( No_of_ERROR_PARAMETERS > 0 ) {
  #include <include.Error_Control.default.free.c>
    Parameter_Space_Free(Error_Space, No_of_IC); free(Error_Space); 
  }
  free(Error_Space);

  for (l=0; l<No_of_HYPOTHESIS; l++) {   
    for (i=0; i<No_of_CITIES; i++) {
      for(j=0; j<No_of_INITIAL_YEARS; j++) {
	for(k=0; k<MODEL_PARAMETERS_MAXIMUM+2 ; k++) free(Likelihood[l][i][j][k]);
	free( Likelihood[l][i][j]);
      }
      free(Likelihood[l][i]);
    }
    free(Likelihood[l]);
  }
  free(Likelihood);
  
  for (l=0; l<No_of_HYPOTHESIS; l++) { 
    for(k = 0; k<No_of_CITIES; k++) free( sn[l][k] );
    free(sn[l]);
  }
  free(sn);
  
  free(Year);
  free(Index_of_City);
  
  if(No_of_CITIES > 1) 
    for (i=0; i<No_of_CITIES_MAX; i++) free(City_Names[i]);
  else
    for (i=1; i<No_of_CITIES_MAX; i++) free(City_Names[i]);
  free(City_Names);

  free(AIC_FILE_NAME); 
  
  for (i=0; i<No_of_HYPOTHESIS; i++) free(FILE_LABEL[i]); 
  free( FILE_LABEL ); 
  free(Type_of_Hypothesis); 

  if(No_of_INITIAL_YEARS > 1) 
    for (i=0; i<No_of_INITIAL_YEARS_MAX; i++) free( Year_List[i] );
  else
    for (i=1; i<No_of_INITIAL_YEARS_MAX; i++) free( Year_List[i] );
  free(Year_List);

  for(i=0; i<No_of_SETS_MAX; i++) { free(Demo_Data[i]); free(Names_of_Rows[i]); }
  free(Demo_Data); free(Names_of_Rows); 
  
  for(k = 0; k<No_of_CITIES; k++) free(PARAMETER_SET_FILE[k]);
  free(PARAMETER_SET_FILE);
  
  free(Initial_Guess);

  
  P_A_R_A_M_E_T_E_R___T_A_B_L_E___F_R_E_E( &Table );
  /*  END : Freeing  All Memmory * * * * * * * * * * * * * * */

  printf("\nEnd of progam\n");
  return (0);
}
