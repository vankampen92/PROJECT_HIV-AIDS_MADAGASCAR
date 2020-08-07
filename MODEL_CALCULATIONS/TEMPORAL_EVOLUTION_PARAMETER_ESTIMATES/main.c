/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                            David Alonso, 2018 (c)                         */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#include <Include/MODEL.h>

#include "global.h"

gsl_rng * r; /* Global generator defined in main.c */

/* This code calculates ODE model temporal evolution of the whole disease
   model. Here, the goal is to estimate diseasea parameters from data, once
   Sigma (and Alpha) parameters have been estimated for each city. Parameters
   F_X, F_Y, \delta_X and \delta_Y have been already estimated from demographic
   data. See directory:

   ./TEMPORAL_EVOLUTION_r_FACTOR_ESTIMATE

   F_X and F_Y are recruitment rates into adult sexually active life, and
   \delta_X and \delta_Y are adult mortality rates. They change every year.
   They are given in 'Time_Dependent_Parameters_Corrected_[CITY_NAME].dat'
   files.

   Compilation:

   . ~$ make X_MODEL=X2W2SILD Y_MODEL=Y_SILD

   Exectution: (Time-dependent parameters: -t4 1)

   . ~$ ./X2W2SILD-YSILD -y0 1          // TYPE of MODEL
   / -sP 12 -sN 2500   -sT 1.0E-08      // Parameter Space of Model Parameters: [-sP: Dimension, Number of Model Parameters to be optimized]
   / -I0 21 -H21 1.0   -m0 0.0  -M0 2.0     -A0 0.01      // Parameter: r_R
   / -I1 0  -H0 3000.0 -m1 0.0  -M1 10000.0 -A1 0.1       // Parameter: Beta_Y
   / -I2 8  -H8 1000.0 -m2 0.0  -M2 10000.0 -A2 0.1       // Parameter: Beta_X
   / -I3 12 -H12   9   -m3 1.0  -M3 20.0    -A3 0.01      // Parameter: Eta
   / -I4 7  -H7  9.0   -m4 1.0  -M4 99.0    -A4 0.01      // Parameter: mDelta
   / -I5 16 -H16 0.2   -m5 0.01 -M5 0.99    -A5 0.01      // Parameter: f_W
   / -I6 17 -H17 0.5   -m6 0.01 -M6 0.99    -A6 0.01      // Parameter: f_0
   / -I7 1  -H1 0.03   -m7 0.0  -M7 1.0     -A7 0.001     // Parameter: p_XY
   / -I8 9  -H9 0.01   -m8 0.0  -M8 1.0     -A8 0.001     // Parameter: p_YX
   / -I9 5  -H5 1.5    -m9 0.0  -M9 10.0    -A9 0.1       // Parameter: Gamma
   / -I10 6 -H6 0.2   -m10 0.0 -M10 1.0    -A10 0.01      // Parameter: Mu
   / -I11 15 -H15 10.0 -m11 1.0 -M11 100.0 -A15 0.1       // Parameter: Xhi

                                              // City-specific parameters (Antananarivo):
   / -H10  0.0325332                          // Parameter: Sigma_0
   / -H11  0.704745                           // Parameter: Sigma_0_r
   / -H18  0.0265231                          // Parameter: Sigma_1
   / -H19  0.550609                           // Parameter: Sigma_1_r
   / -H20  0.056651                           // Parameter: Alpha

   / -en 0 -eP0 17 -eV 0.0103805              // Parameter Space of Error Model        [-en Number of Error Model-related parameters to be optimized: -eP0 17 [Error_Parameter_0]
   / -n 3  -v0 6 -v1 4 -v2 14                 // Output/Observed Varables:             [-n  Number of Observed Variables]
   / -iP 2                                    // Parameter Space of Initial Conditions [-iP Number of Initial Condition Variables to be optimized]
   / -i0  9 -u0 0.0 -U0 100.0
   /- i1 17 -u1 0.0 -U1 100.0
   / -G0 1  -G1 3 -tn 17 -t0 2000.0 -t1 2016.0 -t4 1 -xn 0 -xR 1  // Arguments Controling Numerical Integration
   / -DP 4  -DC 0 -D0 0 -D1 4 -D2 0 -P0 13 -a0 0  -P1 2 -a1 0  -P2 3 -a2 0  -P3 4 -a3 0 // Arguments controling type of time dependence of model parameters.
   / -Fn 1 -F0 ../../DATA_FILES/2019.05.31_Demographic_Parameters_per_City_NLL.dat

   . ~$ ./X2W2SILD-YSILD -y0 1 -sT 1.0E-08 -sN 550 -sP 12 -I0 21 -H21 1.0 -m0 0.0 -M0 2.0 -A0 0.01  -I1 0 -H0 300.0 -m1 0.0  -M1 500.0 -A1 0.1  -I2 8  -H8 100.0 -m2 0.0 -M2 5000.0 -A2 0.1 -I3 12 -H12 9.0 -m3 1.0 -M3 20.0 -A3 0.01  -I4 7 -H7 9.0 -m4 1.0 -M4 99.0 -A4 0.01 -I5 16 -H16 0.2 -m5 0.01 -M5 0.9 -A5 0.01 -I6 17 -H17 0.6 -m6 0.01 -M6 0.9 -A6 0.01 -I7 1 -H1 0.03 -m7 0.0 -M7 1.0 -A7 0.01 -I8 9 -H9 0.01 -m8 0.0 -M8 1.0 -A8 0.01 -I9 5 -H5 1.5 -m9 0.0 -M9 10.0 -A9 0.1 -I10 6 -H6 0.2 -m10 0.0 -M10 1.0 -A10 0.01 -I11 15 -H15 10.0 -m11 1.0 -M11 100.0 -A15 0.1  -n 3 -v0 6 -v1 4 -v2 14 -en 0 -eP0 17 -eV 10.0 -iP 0 -i0 9 -u0 0.0 -U0 10000.0 -i1 17 -u1 0.0 -U1 10000.0 -i2 1 -u2 0.0 -U2 10000 -i3 2 -u3 0.0 -U3 10000 -i4 3 -u4 0.0 -U4 10000 -G0 1  -G1 3 -tn 17 -t0 2000.0 -t1 2016.0 -t4 1 -xn 0 -xR 1 -DP 4  -DC 0 -D0 0 -D1 4 -D2 0 -P0 13 -a0 0  -P1 2 -a1 0  -P2 3 -a2 0  -P3 4 -a3 0 -tE 1.0 -Fn 1 -F0 ../../DATA_FILES/2019.05.31_Demographic_Parameters_per_City_NLL.dat

   Data Files:
   . ~$ ../../DATA_FILES/2019.05.31_Demographic_Parameters_per_City_Alpha_0.1_BIS.dat
   . ~$ ../../DATA_FILES/2019.05.31_Demographic_Parameters_per_City_NLL.dat

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
*/

int main(int argc, char **argv)
{
  int i, k, key;
  double value, Min_Value;
  Parameter_Table Table;
  Time_Control Time;
  Time_Dependence_Control Time_Dependence;
  P_ARG = &Table;
  int Demographic_Parameters_Index[5] = {10,11,18,19,20};

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
  `
  /* B E G I N : Time Dependent Parameters and Observed Data File Names */
  char * pF;
  char ** TIME_PARAMETERS_FILE = (char **)calloc(No_of_CITIES, sizeof(char *) );
  char ** OBSERVED_DATA_FILE   = (char **)calloc(No_of_CITIES, sizeof(char *) );
  char ** ARGUMENTS_RESULT_FILE = (char **)calloc(No_of_CITIES, sizeof(char *) );
  FILE ** p_ARGUMENTS           = (FILE **)calloc(No_of_CITIES, sizeof(FILE *) );

  for(k = 0; k<No_of_CITIES; k++) {
    TIME_PARAMETERS_FILE[k] = (char *)calloc( 100, sizeof(char) );
    OBSERVED_DATA_FILE[k]     = (char *)calloc( 100, sizeof(char) );
    ARGUMENTS_RESULT_FILE[k] = (char *)calloc( 100, sizeof(char) );
  }
  for(k = 0; k<No_of_CITIES; k++) {
    TIME_PARAMETERS_FILE[k][0] = '\0';
    pF = strcat(TIME_PARAMETERS_FILE[k], "Time_Dependent_Parameters_Corrected_");
    pF = strcat(TIME_PARAMETERS_FILE[k], City_Names[k]);
    pF = strcat(TIME_PARAMETERS_FILE[k], ".dat");

    OBSERVED_DATA_FILE[k][0] = '\0';
    pF = strcat(OBSERVED_DATA_FILE[k], "Observed_Data_File_");
    pF = strcat(OBSERVED_DATA_FILE[k], City_Names[k]);
    pF = strcat(OBSERVED_DATA_FILE[k], "_1");
    pF = strcat(OBSERVED_DATA_FILE[k], ".dat");

    ARGUMENTS_RESULT_FILE[k][0] = '\0';
    pF = strcat(ARGUMENTS_RESULT_FILE[k], "Arguments_Command_Line_");
    pF = strcat(ARGUMENTS_RESULT_FILE[k], City_Names[k]);
    pF = strcat(ARGUMENTS_RESULT_FILE[k], ".dat");
    p_ARGUMENTS[k] = fopen(ARGUMENTS_RESULT_FILE[k], "w");
  }
  /*     E N D : ------------------------------------------------------ */
  double ** Demo_Data = (double **)calloc(No_of_CITIES, sizeof(double *));
  for(i=0; i<No_of_CITIES; i++)
    Demo_Data[i] = (double *)calloc(No_of_CITIES, sizeof(double));

  Reading_Demographic_Parameters_from_File(Name_of_FILE[0], Demo_Data,
					   &No_of_CITIES, No_of_PARAMETERS);
  printf("\n Demographic parameters:\n");
  Writing_Standard_Data_Matrix(Demo_Data,
			       No_of_CITIES, 5,
			       1, City_Names,
			       0, Time.Time_Vector);
  printf("\n");

  for(k = 0; k<No_of_CITIES; k++) {

    int No_of_EMPIRICAL_TIMES = 17;
    // Number of columns in the data files of time-dependent parameters
    Time_Dependence_Control_Upload(&Time, &Time_Dependence, &Table,
				   I_Time, No_of_EMPIRICAL_TIMES,
           TIME_DEPENDENT_PARAMETERS, TYPE_of_TIME_DEPENDENCE,
				   TYPE_0_PARAMETERS, TYPE_1_PARAMETERS, TYPE_2_PARAMETERS,
				   No_of_COVARIATES,
				   dependent_parameter, forcing_pattern,
				   "File_of_Covariates.dat", TIME_PARAMETERS_FILE[k]);

    Reading_Standard_Data_Matrix_from_File( OBSERVED_DATA_FILE[k],
					    Empirical_Data_Matrix,
					    &SUB_OUTPUT_VARIABLES, I_Time,
					    0, Name_of_Rows,
					    0, Time.Time_Vector );

    Writing_Standard_Data_Matrix( Empirical_Data_Matrix,
				  3, I_Time,
				  1, Name_of_Rows,
				  0, Time.Time_Vector);

    assert( SUB_OUTPUT_VARIABLES == 3);
    assert( Time_Dependence.No_of_TIMES == I_Time );

    /* B E G I N : Reserving memmory for Observed Data and Fitting Structure */
    Observed_Data * Data = (Observed_Data *)calloc(1, sizeof(Observed_Data));
    Observed_Data_Alloc( Data, SUB_OUTPUT_VARIABLES, I_Time);
    Observed_Data_Initialization( Data, SUB_OUTPUT_VARIABLES, I_Time, Empirical_Data_Matrix,
				  City_Names[k] );
    printf(" Observe_Data structure has been correctly allocated and initiated\n");
    /*     E N D : ------------------------------------- */

    Parameter_Fitting * F = (Parameter_Fitting*)calloc(1,sizeof(Parameter_Fitting));
    F->Data         = Data;
    F->Space        = Space;
    F->Table        = &Table;
    F->Verbose      = 1; // 1: Verbose                // 0: Non Verbose
    F->Minimization = 1; // 1: Function Minimization  // 0: Function Evaluation
    F->Bounded_Parameter_Set = 1;
    F->Function     = GSL_Function_to_Minimize;

    /* Initial conditions from empirical data at the initial time ( -xn 0 ) */
    Parameter_Model_Copy_into_Parameter_Table(&Table, Initial_Guess);
    Uploading_Demographic_Parameters_into_Parameter_Table(&Table, Demo_Data, k);
    Initial_Condition_from_Data_into_Parameter_Table (&Table, Empirical_Data_Matrix);

    printf("\n... ... ... calculating city: %s\n", City_Names[k]);
    if(No_of_IC > 0)
      Parameter_Space_Write_Min_Max_IC_Values (Initial_Condition_Space, &Table );
    printf("\n");
    if(No_of_ERROR_PARAMETERS > 0)
      Parameter_Space_Write_Min_Max_Error_Values (Error_Space, &Table );
    printf("\n");
    Parameter_Space_Write_Min_Max_Values (Space, &Table );
    printf("\n");

    printf("... Simplex bounded optimization starts right at this point within the\n");
    printf("... parameter space boundaries given above\n");
    getchar();

    if (k != 8 ) Min_Value = GSL_Minimization_Driver( F );

    printf("City %s:\t Min Value: NLL=%g\tBest Estimates: \n", City_Names[k], Min_Value);

    for(i=0; i<No_of_PARAMETERS; i++) {
      key = Space->Parameter_Index[i];
      value = AssignStructValue_to_VectorEntry(key, &Table);
      printf("%s = %g  ", Table.Symbol_Parameters[key], value);
    }
    for(i=0; i<5; i++) {
      key = Demographic_Parameters_Index[i];
      value = AssignStructValue_to_VectorEntry(key, &Table);
      printf("%s = %g  ", Table.Symbol_Parameters[key], value);
    }
    for(i=0; i<No_of_IC; i++) {
	key = Initial_Condition_Space->Parameter_Index[i];
	value = Model_Variable_Initial_Condition_into_Vector_Entry_Table( key, &Table );
	printf("%s = %g  ", Table.Model_Variable_Symbol[key], value);
    }
    for(i=0; i<No_of_ERROR_PARAMETERS; i++) {
      key = Error_Space->Parameter_Index[i];
      value = Error_Model_into_Vector_Entry_Table( key, &Table );
      if(key < OUTPUT_VARIABLES_GENUINE)
	printf("%s = %g  ", Table.Output_Variable_Symbol[key], value);
      else
	printf("Error_Parameter_%d = %g  ", i, value);
    }

    printf("\n\n");
    if(argc > 1) ArgumentControl_fprintf(p_ARGUMENTS[k], &Table, argc, argv);
    fclose(p_ARGUMENTS[k]);
    printf(" %s: Population at year 2000: %g\n", City_Names[k], Table.INITIAL_TOTAL_POPULATION);
    printf("\n\n");

    Observed_Data_Free(Data);
    free(Data);
    free(F);
  }

  /* BEGIN : -------------------------------------------------------------------------
     Redimensioning Index vector to include and save the full list of model parameters
     Redefinition of Parameter Space structure to allocate the whole parameter space
     This operation can only be done at the end of a main file (before freeing memmory
     and ending).
  */
  Parameter_Space_Free(Space, No_of_PARAMETERS); free(Space);

  No_of_PARAMETERS = MODEL_PARAMETERS_MAXIMUM;
  for(i=0; i<No_of_PARAMETERS; i++) Table.Index[i] = i;

  Space = (Parameter_Space *)calloc(1, sizeof(Parameter_Space));
  Parameter_Space_Alloc( Space, No_of_PARAMETERS, d);
  Parameter_Space_Initialization( Space, No_of_PARAMETERS, TOLERANCE, MAX_No_of_ITERATIONS,
				  d, Index, Ranges, Acc);
  printf(" Parameter_Space structure has been correctly allocated and initiated\n");

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

  if( No_of_IC > 0 ) {
  #include <include.Initial_Conditions.default.free.c>
    Parameter_Space_Free(Initial_Condition_Space, No_of_IC);
  }
  free(Initial_Condition_Space);

  if( No_of_ERROR_PARAMETERS > 0 ) {
  #include <include.Error_Control.default.free.c>
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

  for(i=0; i<No_of_CITIES; i++) free(Demo_Data[i]);
  free(Demo_Data);

  for(k = 0; k<No_of_CITIES; k++) {
    free(TIME_PARAMETERS_FILE[k]);
    free(OBSERVED_DATA_FILE[k]);
    free(ARGUMENTS_RESULT_FILE[k]);
  }
  free(TIME_PARAMETERS_FILE);
  free(OBSERVED_DATA_FILE);
  free(ARGUMENTS_RESULT_FILE);
  free(p_ARGUMENTS);

  free(Initial_Guess);

  P_A_R_A_M_E_T_E_R___T_A_B_L_E___F_R_E_E( &Table );
  /*  END : Freeing  All Memmory * * * * * * * * * * * * * * */

  printf("\nEnd of progam\n");
  return (0);
}
