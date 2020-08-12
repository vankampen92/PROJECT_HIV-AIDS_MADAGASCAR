/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                            David Alonso, 2018 (c)                         */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#include <Include/MODEL.h>

#include "global.h"

gsl_rng * r; /* Global generator defined in main.c */

/* This code calculates ODE model temporal evolution for a range of sexual-transmitted AIDS-HIV models

   Compilation (example 1):

   . ~$ make X_MODEL=X2W2SILD Y_MODEL=YSILD

   Typical Parameters Values:

   / -I0 21  -H21 1.0   -m0 0.8   -M0 1.2     -A0 0.01      // Parameter: r_R
   / -I1 0   -H0 100.0  -m1 96.0  -M1 120.0   -A1 0.1       // Parameter: Beta_Y
   / -I2 8   -H8 100.0  -m2 96.0  -M2 120.0   -A2 0.1       // Parameter: Beta_X
   / -I3 12  -H12 9.0   -m3 0.0   -M3 19.0    -A3 0.01      // Parameter: Eta
   / -I4 7   -H7  9.0   -m4 0.0   -M4 100.0   -A4 0.01      // Parameter: mDelta
   / -I5 16  -H16 0.1   -m5 0.0   -M5 0.99    -A5 0.01      // Parameter: f_W
   / -I6 17  -H17 0.7   -m6 0.0   -M6 0.99    -A6 0.01      // Parameter: f_0
   / -I7 1   -H1 0.003  -m7 0.0   -M7 0.015   -A7 0.0001    // Parameter: p_XY
   / -I8 9   -H9 0.001  -m8 0.0   -M8 0.005   -A8 0.0001    // Parameter: p_YX
   / -I9 5   -H5 2.0    -m9 0.5   -M9 4.0     -A9 0.1       // Parameter: Gamma
   / -I10 6  -H6 0.2    -m10 0.05 -M10 0.2    -A10 0.01     // Parameter: Mu
   / -I11 15 -H15 5.0   -m11 1.0  -M11 50.0   -A11 0.1      // Parameter: Xhi
   / -I12 10 -H10  0.01 -m12 0.0  -M12 0.05   -A12 0.01     // Parameter: Sigma_0
   / -I13 11 -H11  0.02 -m13 0.0  -M13 0.05   -A13 0.01     // Parameter: Sigam_0_r
   / -I14 18 -H18  0.01 -m14 0.0  -M14 0.05   -A14 0.01     // Parameter: Sigma_1
   / -I15 19 -H19  0.02 -m15 0.0  -M15 0.05   -A15 0.01     // Parameter: Sigma_1_r
   / -I16 20 -H20  0.1  -m16 0.08 -M16 0.12   -A16 0.01     // Parameter: Alpha
   / -I17 23 -H23  0.1  -m17 0.01 -M17 5.0    -A17 0.01     // Parameter: A_0  Magnitud of the jump
   / -I18 24 -H24  0.1  -m18 0.01 -M18 5.0    -A18 0.01     // Parameter: L_0  Smoothness of the jump
   / -I19 25 -H25  2011 -m19 2009 -M19 2013.0 -A19 0.1      // Parameter: T_0  Timing of the jump

   Exectution:

   a. No time dependence (-t4 0):
 
   . ~$ ./X2W2SILD-YSILD -y0 1 -n 1 -v0 7 -G0 1 -G1 1 -tn 5000 -t0 0.0 -t1 75.0 -t4 0 -xn 0 -xN 1000000 -H2 25000 -H13 2500
                         
   . ~$ ./X2W2SILD-YSILD -y0 1 -n 9 -v0 0 -v1 1 -v2 2 -v3 6 -v4 7 -v5 8 -v6 9 -v7 10 -v8 12 -G0 3 -G1 3 -tn 5000 -t0 0.0 -t1 50.0 -t4 0 -xn 0 -xN 1000000 -H2 25000 -H13 25000

   . ~$ ./X2W2SILD-YSILD -y0 1 -n 6 -v0 0 -v1 1 -v2 8 -v3 9 -v4 10 -v5 12 -G0 3 -G1 2 -tn 5000 -t0 0.0 -t1 50.0 -t4 0 -xn 0 -xN 1000000 -H2 25000 -H13 25000 -G5 1 -G6 0.0 -G7 1.0
                          
   . ~$ ./X2W2SILD-YSILD -y0 1 -n 6 -v0 7 -v1 8 -v2 9 -v3 10 -v4 11 -v5 12 -G0 3 -G1 2 -tn 5000 -t0 0.0 -t1 50.0 -t4 0 -xn 0 -xN 1000000 -H2 25000 -H13 25000 -G5 1 -G6 0.0 -G7 1.0

   . ~$ ./X2W2SILD-YSILD -y0 1 -sP 20 -I0 21 -H21 1.0 -m0 0.8 -M0 1.2 -A0 0.01  -I1 0 -H0 100.0 -m1 96.0 -M1 120.0 -A1 0.1  -I2 8 -H8 100.0 -m2 96.0 -M2 120.0 -A2 0.1  -I3 12 -H12 9  -m3 1.0 -M3 20.0  -A3 0.01  -I4 7  -H7  9.0  -m4 0.0 -M4 100.0 -A4 0.01  -I5 16 -H16 0.2  -m5 0.0 -M5 0.99  -A5 0.01  -I6 17 -H17 0.5  -m6 0.0 -M6 0.99  -A6 0.01  -I7 1 -H1 0.002  -m7 0.0 -M7 0.005 -A7 0.001  -I8 9 -H9 0.001 -m8 0.0 -M8 0.005 -A8 0.001   -I9 5 -H5 1.5  -m9 0.5 -M9 12.0  -A9 0.1  -I10 6  -H6 0.2  -m10 0.1 -M10 1.0 -A10 0.01  -I11 15 -H15 10.0  -m11 1.0 -M11 100.0  -A11 0.1  -I12 10 -H10  0.01 -m12 0.0 -M12 0.05 -A12 0.01  -I13 11 -H11 0.02 -m13 0.0 -M13 0.05  -A13 0.01   -I14 18 -H18 0.01 -m14 0.0 -M14 0.05  -A14 0.01  -I15 19 -H19  0.02 -m15 0.0 -M15 0.05 -A15 0.01  -I16 20 -H20  0.1 -m16 0.08 -M16 0.12 -A16 0.01  -I17 23 -H23 0.5  -m17 0.01 -M17 5.0 -A17 0.01  -I18 24 -H24  0.1  -m18 0.01 -M18 5.0 -A18 0.01  -I19 25 -H25  2013 -m19 2008.9 -M19 2013.0 -A19 0.1  -y0 1 -n 6 -v0 7 -v1 8 -v2 9 -v3 10 -v4 11 -v5 12 -G0 3 -G1 2 -tn 17 -t0 2000.0 -t1 2016 -t4 0 -xn 0 -xN 1.0E+05 -G5 1 -G6 0.0 -G7 1.0

   . ~S ./X2W2SILD-YSILD -y0 1 -sP 20 -I0 21 -H21 1.0 -m0 0.8 -M0 1.2 -A0 0.01  -I1 0 -H0 90.0 -m1 96.0 -M1 120.0 -A1 0.1  -I2 8 -H8 100.0 -m2 96.0 -M2 120.0 -A2 0.1  -I3 12 -H12 9  -m3 1.0 -M3 20.0  -A3 0.01  -I4 7  -H7  9.0  -m4 0.0 -M4 100.0 -A4 0.01  -I5 16 -H16 0.2  -m5 0.0 -M5 0.99  -A5 0.01  -I6 17 -H17 0.5  -m6 0.0 -M6 0.99  -A6 0.01  -I7 1 -H1 0.002  -m7 0.0 -M7 0.005 -A7 0.001  -I8 9 -H9 0.001 -m8 0.0 -M8 0.005 -A8 0.001   -I9 5 -H5 1.5  -m9 0.5 -M9 12.0  -A9 0.1  -I10 6  -H6 0.2  -m10 0.1 -M10 1.0 -A10 0.01  -I11 15 -H15 10.0  -m11 1.0 -M11 100.0  -A11 0.1  -I12 10 -H10  0.01 -m12 0.0 -M12 0.05 -A12 0.01  -I13 11 -H11 0.01 -m13 0.0 -M13 0.05  -A13 0.01   -I14 18 -H18 0.01 -m14 0.0 -M14 0.05  -A14 0.01  -I15 19 -H19  0.01 -m15 0.0 -M15 0.05 -A15 0.01  -I16 20 -H20  0.1 -m16 0.08 -M16 0.12 -A16 0.01  -I17 23 -H23 0.5  -m17 0.01 -M17 5.0 -A17 0.01  -I18 24 -H24  0.1  -m18 0.01 -M18 5.0 -A18 0.01  -I19 25 -H25  2013 -m19 2008.9 -M19 2013.0 -A19 0.1  -y0 1 -n 6 -v0 7 -v1 8 -v2 9 -v3 10 -v4 11 -v5 12 -G0 3 -G1 2 -tn 100 -t0 2000.0 -t1 2250 -t4 0 -xn 0 -xN 1.0E+05 -G5 1 -G6 0.0 -G7 0.3

   b. Time-dependent parameters (-t4 1):

   . ~$ ./X2W2SILD-YSILD -y0 1 -I0 21 -H21 1.0 -m0 0.8 -M0 1.2 -A0 0.01  -I1 0 -H0 100.0 -m1 96.0 -M1 120.0 -A1 0.1  -I2 8 -H8 100.0 -m2 96.0 -M2 120.0 -A2 0.1  -I3 12 -H12 9  -m3 1.0 -M3 20.0  -A3 0.01  -I4 7  -H7  9.0  -m4 0.0 -M4 100.0 -A4 0.01  -I5 16 -H16 0.2  -m5 0.0 -M5 0.99  -A5 0.01  -I6 17 -H17 0.5  -m6 0.0 -M6 0.99  -A6 0.01  -I7 1 -H1 0.002  -m7 0.0 -M7 0.005 -A7 0.001  -I8 9 -H9 0.001 -m8 0.0 -M8 0.005 -A8 0.001   -I9 5 -H5 1.5  -m9 0.5 -M9 12.0  -A9 0.1  -I10 6  -H6 0.2  -m10 0.1 -M10 1.0 -A10 0.01  -I11 15 -H15 10.0  -m11 1.0 -M11 100.0  -A11 0.1  -I12 10 -H10  0.01 -m12 0.0 -M12 0.05 -A12 0.01  -I13 11 -H11 0.02 -m13 0.0 -M13 0.05  -A13 0.01   -I14 18 -H18 0.01 -m14 0.0 -M14 0.05  -A14 0.01  -I15 19 -H19  0.02 -m15 0.0 -M15 0.05 -A15 0.01  -I16 20 -H20  0.1 -m16 0.08 -M16 0.12 -A16 0.01  -I17 23 -H23 0.5  -m17 0.01 -M17 5.0 -A17 0.01  -I18 24 -H24  0.1  -m18 0.01 -M18 5.0 -A18 0.01  -I19 25 -H25  2013 -m19 2008.9 -M19 2013.0 -A19 0.1  -n 6 -v0 7 -v1 8 -v2 9 -v3 10 -v4 11 -v5 12 -G0 3 -G1 2 -tn 17 -t0 2000.0 -t1 2016 -t4 1 -xn 0 -xN 1.0E+05 -DP 5 -DC 0 -D0 0 -D1 4 -D2 1 -P0 13 -a0 0  -P1 2 -a1 0  -P2 3 -a2 0  -P3 4 -a3 0 -P4 22 -a4 0 -G5 1 -G6 0.0 -G7 1.0 -Fn 1 -F0 Time_Dependent_Parameters_Corrected_Antananarivo.dat

    . ~$ ./X2W2SILD-YSILD -y0 1 -I0 21 -H21 1.0 -m0 0.8 -M0 1.2 -A0 0.01  -I1 0 -H0 100.0 -m1 96.0 -M1 120.0 -A1 0.1  -I2 8 -H8 100.0 -m2 96.0 -M2 120.0 -A2 0.1  -I3 12 -H12 9  -m3 1.0 -M3 20.0  -A3 0.01  -I4 7  -H7  9.0  -m4 0.0 -M4 100.0 -A4 0.01  -I5 16 -H16 0.2  -m5 0.0 -M5 0.99  -A5 0.01  -I6 17 -H17 0.5  -m6 0.0 -M6 0.99  -A6 0.01  -I7 1 -H1 0.002  -m7 0.0 -M7 0.005 -A7 0.001  -I8 9 -H9 0.001 -m8 0.0 -M8 0.005 -A8 0.001   -I9 5 -H5 1.5  -m9 0.5 -M9 12.0  -A9 0.1  -I10 6  -H6 0.2  -m10 0.1 -M10 1.0 -A10 0.01  -I11 15 -H15 10.0  -m11 1.0 -M11 100.0  -A11 0.1  -I12 10 -H10  0.01 -m12 0.0 -M12 0.05 -A12 0.01  -I13 11 -H11 0.02 -m13 0.0 -M13 0.05  -A13 0.01   -I14 18 -H18 0.01 -m14 0.0 -M14 0.05  -A14 0.01  -I15 19 -H19  0.02 -m15 0.0 -M15 0.05 -A15 0.01  -I16 20 -H20  0.1 -m16 0.08 -M16 0.12 -A16 0.01  -I17 23 -H23 0.1  -m17 0.01 -M17 5.0 -A17 0.01  -I18 24 -H24  0.1  -m18 0.01 -M18 5.0 -A18 0.01  -I19 25 -H25  2013 -m19 2008.9 -M19 2013.0 -A19 0.1  -n 6 -v0 7 -v1 8 -v2 9 -v3 10 -v4 11 -v5 12 -G0 3 -G1 2 -tn 34 -t0 2000.0 -t1 2033 -t4 1 -xn 0 -xN 1.0E+05 -DP 5 -DC 0 -D0 0 -D1 4 -D2 1 -P0 13 -a0 0  -P1 2 -a1 0  -P2 3 -a2 0  -P3 4 -a3 0 -P4 22 -a4 0 -G5 1 -G6 0.0 -G7 1.0 -Fn 1 -F0 Time_Dependent_Parameters_Extrapolated_Corrected_Antananarivo.dat

   Compilation (example 2):

   . ~$ make X_MODEL=XWSILD Y_MODEL=YSILD

   Execution:

   . ~$ ./XWSILD-YSILD -y0 1 -n 9 -v0 0 -v1 1 -v2 2 -v3 6 -v4 7 -v5 8 -v6 9 -v7 10 -v8 12 -G0 3 -G1 3 -tn 5000 -t0 0.0 -t1 50.0 -t4 0 -xn 0 -xN 1000000 -H2 25000 -H13 25000
   . ~$ ./XWSILD-YSILD -y0 1 -n 4 -v0 0 -v1 1 -v2 8 -v3 9  -G0 2 -G1 2 -tn 5000 -t0 0.0 -t1 50.0 -t4 0 -xn 0 -xN 1000000 -H2 25000 -H13 25000 -G5 1 -G6 0.0 -G7 1.0

   Compilation (exemple 3):

   . ~$ make X_MODEL=X_ Y_MODEL=Y_

   Exectution:

   a. No time dependence:

   . ~$ ./X_-Y_ -y0 2 -n 1 -v0 6 -G0 2 -G1 1 -tn 5000 -t0 0.0 -t1 50.0 -t4 0 -xn 0 -xN 1000000 -H2 25000 -H13 25000 -G5 1 -G6 0.0 -G7 1000000

   b. Time-dependent parameters:

   . ~$ ./X_-Y_ -y0 2 -Fn 1 -F0 "Time_Dependent_Parameters_Corrected_Antananarivo.dat" -n 1 -v0 6 -G0 1 -G1 1 -tn 17 -t0 2000.0 -t1 2016.0 -t4 1 -xn 0 -xN 715506 -G0 1 -G1 1 -G2 1 -G3 1990.0 -G4 2019 -G5 1 -G6 0.0 -G7 2000000 -DP 4 -DC 0 -D0 0 -D1 4 -D2 0 -P0 13 -a0 0  -P1 2 -a1 0  -P2 3 -a2 0  -P3 4 -a3 0

   Compilation (example 3):

   . ~$ make X_MODEL=X2W2 Y_MODEL=Y_

   Exectution:

   a. No time dependence:

   . ~$ ./X2W2-Y_ -y0 3 -n 2 -v0 2 -v1 12 -G0 1 -G1 2 -tn 5000 -t0 0.0 -t1 50.0 -t4 0 -xn 0 -xN 1000000 -H2 25000 -H13 25000

   -xn TYPE of INITIAL CONDITION (0 from default values or Input Args; 1 at Random; 2 from fixed/stationary Point)
   -xN INITIAL TOTAL POPULATION SIZE at t0.
   -t4 TYPE of TIME DEPENDENCE (0, no parameter time dependence). If the TYPE of TIME DEPENDENCE input argument is greater than 0, time dependence parameters are at play.
   See, for instance, ./Definition_Numerical_Integration/XWSILD-YSILD/deterministic_time_dynamics.c

   See file denition_OutPut_Variables.c for full -v?? input argument code definitions. Examples are:

    -v0  0   Effective Average Fraction of Infectious Females
    -v1  1   Effective Average Fraction of Infectious Males
    -v2  2   Total Female Population
    -v3  6   Total Population
    -v4  7   Total Disease Prevalence
    -v5  8   Total Female Disease Prevalence
    -v6  9   Total Male_Disease Prevalence
    -v7 10   Total Female Sexual Worker Disease Prevalence
    -v8 12   Female Sexual Worker Fraction
*/

void Determine_Threshold_Points(double * x_Time, double * y_Time, int N,
				double * x_Turning_Point,
				double * x_Low,
				double * x_High); 

int main(int argc, char **argv)
{
  int i;
  Parameter_Table Table;
  Time_Control Time;
  Time_Dependence_Control Time_Dependence;
  P_ARG = &Table;

#include "default.c"

  /* Command line arguments */
  if(argc>1) ArgumentControl(argc,argv);

  #include "include.Output_Variables.default.aux.c"
  P_A_R_A_M_E_T_E_R___T_A_B_L_E___A_L_L_O_C(   &Table );
  P_A_R_A_M_E_T_E_R___T_A_B_L_E___U_P_L_O_A_D( &Table, Index_Output_Variables );
  printf(" Parameter_Table structure has been correctly allocated and initiated\n");

  /* B E G I N : Reserving memmory for Parameter Space */
  #include <include.Parameter_Space.default.aux.c>
  Parameter_Space * Space = (Parameter_Space *)calloc(1, sizeof(Parameter_Space));
  Parameter_Space_Alloc( Space, No_of_PARAMETERS, d);
  Parameter_Space_Initialization( Space, No_of_PARAMETERS, TOLERANCE, MAX_No_of_ITERATIONS,
    d, Index, Ranges, Acc);
  Parameter_Table_Index_Update(Index, No_of_PARAMETERS, &Table);
  Table.S = Space;
  printf(" Parameter_Space structure has been correctly allocated and initiated\n");
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

    int No_of_EMPIRICAL_TIMES = 17;
    // Number of columns in the data files of time-dependent parameters
    Time_Dependence_Control_Upload(&Time, &Time_Dependence, &Table,
				   I_Time, No_of_EMPIRICAL_TIMES,
                                   TIME_DEPENDENT_PARAMETERS, TYPE_of_TIME_DEPENDENCE,
				   TYPE_0_PARAMETERS, TYPE_1_PARAMETERS, TYPE_2_PARAMETERS,
				   No_of_COVARIATES,
				   dependent_parameter, forcing_pattern,
				   "File_of_Covariates.dat", Name_of_FILE[0] );
    printf(" Borth Time_Control and Time_Dependence_Control structures have been\n");
    printf(" correctly allocated and set up\n");
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

  /* Initial conditions from values at the initial time ( -xn 0 ) */

  if ( TYPE_of_MODEL == 1 ) {
    double Initial_Adult_Population = INITIAL_TOTAL_POPULATION;
    double Initial_Female_Sexual_Workers = 1000.0;
    double Initial_Female_Sexual_Workers_Infected = 10.0;

    Initial_Condition_from_Initial_Values_into_Parameter_Table (&Table,
								Initial_Adult_Population,
								Initial_Female_Sexual_Workers,
								Initial_Female_Sexual_Workers_Infected);
  }
  else {
    double Female_Sexual_Worker_Population = 1000.0;
    Initial_Condition_from_Value_into_Parameter_Table (&Table,
						       Female_Sexual_Worker_Population);
  }

  M_O_D_E_L( &Table );

#if defined X_  // or Y_ (this is, when MODEL is X_-Y_)
  /* BEGIN : -------------------------------------------------------------------------
     Reading and plotting empirical population evolution
  */
  int No_of_Rows;
  char ** Name_of_Rows;
  double ** City_Data  = (double **)calloc(1,  sizeof(double *) );
         City_Data[0]  = (double * )calloc(16,  sizeof(double  ) );
  double * Time_Vector = (double * )calloc(16, sizeof(double  ) );
  Reading_Standard_Data_Matrix_from_File( "City_Population_1955_2018_Antananarivo.dat",
					  City_Data,
					  &No_of_Rows, 16,
					  0, Name_of_Rows,
					  1, Time_Vector );
  Table.CPG->type_of_Symbol = 24;
  Table.CPG->color_Index    = 3;  /* 3: green */
  int SAME = 1;
  CPGPLOT___X_Y___S_C_A_T_T_E_R_E_D___S_A_M_E___P_L_O_T ( Table.CPG, SAME,
							  16, Time_Vector, City_Data[0],
							  "Year",
							  "Total Population",
							  "",
							  Table.CPG->CPG_SCALE_X,
							  Table.CPG->CPG_SCALE_Y );
  free(Time_Vector); free(City_Data[0]); free(City_Data);
  /* END: ----------------------------------------------------------------------------
   */
#endif

  if( SUB_OUTPUT_VARIABLES == 1 && variable_0 == 7) {// Only when Total Prevalence
                                                     // is the plotted output variable
  /* BEGIN : -------------------------------------------------------------------------
     Annotating sigmoidal function (only if -n 1, this is, SUB_OUTPUT_VARIABLES == 1)
  */
    double x_Turning_Point;
    double x_Low, x_High, y_Range_0, y_Range_1;
    int color_Index, type_of_Line, type_of_Width, type_of_Symbol;
    
    Determine_Threshold_Points(Table.CPG->x_Time, Table.CPG->y_Time[0], I_Time,
			       &x_Turning_Point, &x_Low, &x_High);

    y_Range_0  = Table.CPG->CPG_RANGE_Y_0; 
    y_Range_1 = Table.CPG->CPG_RANGE_Y_1;

    color_Index    = 1; /* 3: green */
    type_of_Line   = 2;
    type_of_Width  = 8;
    type_of_Symbol = 0;
    C_P_G___P_L_O_T_T_I_N_G___E_X_T_R_A___L_I_N_E (x_Low, y_Range_0, 
                                                   x_Low, y_Range_1,
                                                   color_Index,
                                                   type_of_Line,
                                                   type_of_Width,
                                                   type_of_Symbol); 
    color_Index    = 2; /* 2: red */
    type_of_Line   = 2;
    type_of_Width  = 4;
    type_of_Symbol = 0;
    C_P_G___P_L_O_T_T_I_N_G___E_X_T_R_A___L_I_N_E (x_Turning_Point, y_Range_0, 
                                                   x_Turning_Point, y_Range_1,
                                                   color_Index,
                                                   type_of_Line,
                                                   type_of_Width,
                                                   type_of_Symbol);
    color_Index    = 1; /* 3: green */
    type_of_Line   = 2;
    type_of_Width  = 8;
    type_of_Symbol = 0;
    C_P_G___P_L_O_T_T_I_N_G___E_X_T_R_A___L_I_N_E (x_High, y_Range_0, 
                                                   x_High, y_Range_1,
                                                   color_Index,
                                                   type_of_Line,
                                                   type_of_Width,
                                                   type_of_Symbol);

    cpgtext(0.0, 0.7, "Initial Phase");
    cpgtext(x_Low, 0.7, "Transition");
    cpgtext(x_High, 0.7, "Establishment");
    /* END: ----------------------------------------------------------------------------
     */
  }
  
  /* BEGIN : -------------------------------------------------------------------------
     Redimensioning Index vector to include and save the full list of model parameters
     Redefinition of Parameter Space structure to allocate the whole parameter space
     This operation can only be done at the end of a main file (before freeing memmory
     and ending).
  */
  /* Parameter_Space_Free(Space, No_of_PARAMETERS); free(Space);  */

  /* No_of_PARAMETERS = MODEL_PARAMETERS_MAXIMUM; */
  /* for(i=0; i<No_of_PARAMETERS; i++) Table.Index[i] = i; */

  /* Space = (Parameter_Space *)calloc(1, sizeof(Parameter_Space)); */
  /* Parameter_Space_Alloc( Space, No_of_PARAMETERS, d); */
  /* Parameter_Space_Initialization( Space, No_of_PARAMETERS, TOLERANCE, MAX_No_of_ITERATIONS, */
  /* 				  d, Index, Ranges, Acc); */
  /* printf(" Parameter_Space structure has been correctly allocated and initiated\n"); */

  char boundary_File[80];
  sprintf(boundary_File, "Parameter_Model_Boundary.c");
  write_Parameter_Table___RANGES___VALUES___LATEX ( "Latex_Parameter_Table.tex",
                                                    boundary_File,
                                                    &Table,
                                                    Space->P_MAX->data,
                                                    Space->P_min->data, Space->No_of_PARAMETERS );
  /*  END : ------------------------------------------------------------------------*/

  /* BEGIN : Freeing All Memmory * * * * * * * * * * * * * * */
#if defined CPGPLOT_REPRESENTATION
  P_A_R_A_M_E_T_E_R___C_P_G_P_L_O_T___F_R_E_E( Table.CPG, SUB_OUTPUT_VARIABLES );
  cpgclos();
#endif

  #include <include.Parameter_Space.default.free.c>
  Parameter_Space_Free(Space, No_of_PARAMETERS); free( Space );

#include <include.Output_Variables.default.free.c>

  #include <include.Time_Dependence_Control.default.free.c>
  if (TYPE_of_TIME_DEPENDENCE == 0) T_I_M_E___C_O_N_T_R_O_L___F_R_E_E( &Time, &Table );
  else                        Time_Dependence_Control_Free( &Time_Dependence, &Table );

  P_A_R_A_M_E_T_E_R___T_A_B_L_E___F_R_E_E( &Table );
  /*  END : Freeing  All Memmory * * * * * * * * * * * * * * */

  printf("\nEnd of progam\n");
  return (0);
}


void Determine_Threshold_Points(double * x_Time, double * y_Time, int N,
				double * x_Turning_Point,
				double * x_Low,
				double * x_High)
{
  int i, i_Index; 
  double Max_y_Value = y_Time[N-1];
  double T_0 = 0.1;
  double T_1 = 0.9;

  i=0;
  while (y_Time[i] < T_0 * Max_y_Value) i_Index = i++;
  (* x_Low) = x_Time[i_Index];
  
  i=0;
  while (y_Time[i] < T_1 * Max_y_Value) i_Index = i++;
  (* x_High) = x_Time[i_Index];
  
  double * Delta_Value = (double *)calloc( N, sizeof(double) );

  for(i=0; i<N-1; i++)
    Delta_Value[i] = (y_Time[i+1] - y_Time[i])/(x_Time[i+1] - x_Time[i]);

  double Max_Delta = vector_MAX_Index_double(Delta_Value, 0, N-1, &i_Index); 
  (* x_Turning_Point) = x_Time[i_Index];

  free(Delta_Value); 
}
