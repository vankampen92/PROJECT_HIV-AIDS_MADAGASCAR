/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                            David Alonso, 2018 (c)                         */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#include <Include/MODEL.h>
#include <gsl/gsl_fit.h>

#include "global.h"

gsl_rng * r; /* Global generator defined in main.c */

/* This code calculates ODE model temporal evolution of the simple demographic model:

   dX
   -- = r_F * F_X - \delta_X X
   dt

   dY
   -- = r_F * F_Y - \delta_Y Y
   dt

   where X and Y represent the populations of sexually active females and males,
   respectively. F_X and F_Y are recruitment rates into the sexually active life,
   r_F is an empirical factor to be determined to fit the temporal evolution of
   total popualtion in every city. Here, the goal is to estimate it from data.

   Compilation:

   . ~$ make X_MODEL=X_ Y_MODEL=Y_

   Exectution: (Time-dependent parameters: -t4 1)

   . ~$ ./X_-Y_ -y0 2 -sP 1 -I0 21 -H21 1.0 -m0 0.001 -M0 2.0 -n 1 -v0 6 -G0 1 -G1 1 -tn 17 -t0 2000.0 -t1 2016.0 -t4 1 -xn 0 -G5 1 -G6 0.0 -G7 1000000 -DP 4 -DC 0 -D0 0 -D1 4 -D2 0 -P0 13 -a0 0  -P1 2 -a1 0  -P2 3 -a2 0  -P3 4 -a3 0 -en 0 -eP0 17 -eV 0.01 -tE 2.0

   Exectution: (Time-dependent parameters: -t4 1, and initial conditions as searcheable parameters:  -iP 2 -i0 0 -i1 1)

   . ~$ ./X_-Y_ -y0 2 -sT 1.0E-05 -sN 100 -sP 1 -I0 21 -H21 1.0 -m0 0.001 -M0 2.0 -n 1 -v0 6 -G0 1 -G1 1 -tn 17 -t0 2000.0 -t1 2016.0 -t4 1 -xn 0 -G5 1 -G6 0.0 -G7 1000000 -DP 4 -DC 0 -D0 0 -D1 4 -D2 0 -P0 13 -a0 0  -P1 2 -a1 0  -P2 3 -a2 0  -P3 4 -a3 0 -en 0 -eP0 17 -eV 0.01 -tE 2.0 -iP 2 -i0 0 -i1 1

   -xn TYPE of INITIAL CONDITION (0 from default values in Parameter Table (Input Args); 1 at Random; 2 from fixed/stationary Point)
   -xN INITIAL TOTAL POPULATION SIZE
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

void Converting_Total_Population_into_Adult_Population ( const char * ,
							 double * ,
							 double ** , int );

void Converting_Total_Population_into_Adult_Population_Extrapolated (const char * );

int main(int argc, char **argv)
{
  int i, k, key;
  double value, Min_Value;
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

  /* B E G I N : Reserving memmory for Error Model Parameter Space        */
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
  /*     E N D : -------------------------------------------------------- */
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
				       No_of_IC, d_IC, Index_IC, Ranges_IC, Acc_IC);
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
  const char * City_Names[] = { "Antananarivo",
				"Antsiranana",
				"Mahajanga",
				"Toamasina",
				"Fianarantsoa",
				"Toliary",
				"Taolagnaro",
				"Moramanga",
				"Antsirabe",
				"Morondava",
				"Nosy_Be" };
  /* B E G I N : Time Dependent Parameters and Observed Data File Names */
  char * pF;
  char ** TIME_PARAMETERS_FILE = (char **)calloc(No_of_CITIES, sizeof(char *) );
  char ** TIME_PARAMETERS_FILE_CORRECTED = (char **)calloc(No_of_CITIES, sizeof(char *) );
  char ** OBSERVED_DATA_FILE   = (char **)calloc(No_of_CITIES, sizeof(char *) );
  for(k = 0; k<No_of_CITIES; k++) {
    TIME_PARAMETERS_FILE[k] = (char *)calloc( 100, sizeof(char) );
    TIME_PARAMETERS_FILE_CORRECTED[k] = (char *)calloc( 100, sizeof(char) );
    OBSERVED_DATA_FILE[k]     = (char *)calloc( 100, sizeof(char) );
  }
  for(k = 0; k<No_of_CITIES; k++) {
    TIME_PARAMETERS_FILE[k][0] = '\0';
    pF = strcat(TIME_PARAMETERS_FILE[k], "Time_Dependent_Parameters_");
    pF = strcat(TIME_PARAMETERS_FILE[k], City_Names[k]);
    pF = strcat(TIME_PARAMETERS_FILE[k], ".dat");

    TIME_PARAMETERS_FILE_CORRECTED[k][0] = '\0';
    pF = strcat(TIME_PARAMETERS_FILE_CORRECTED[k], "Time_Dependent_Parameters_Corrected_");
    pF = strcat(TIME_PARAMETERS_FILE_CORRECTED[k], City_Names[k]);
    pF = strcat(TIME_PARAMETERS_FILE_CORRECTED[k], ".dat");

    OBSERVED_DATA_FILE[k][0] = '\0';
    pF = strcat(OBSERVED_DATA_FILE[k], "Total_City_Population_");
    pF = strcat(OBSERVED_DATA_FILE[k], City_Names[k]);
    pF = strcat(OBSERVED_DATA_FILE[k], ".dat");
  }
  /*     E N D : ------------------------------------------------------ */

  FILE * DEMO      = fopen("Initial_Conditions_per_City.dat", "w");
  fprintf(DEMO, "City\t");
  for(i=0; i<No_of_PARAMETERS; i++) {
    key = Space->Parameter_Index[i];
    fprintf(DEMO, "%s\t", Table.Symbol_Parameters[key]);
  }
  for(i=0; i<No_of_IC; i++) {
    key = Initial_Condition_Space->Parameter_Index[i];
    fprintf(DEMO, "%s\t", Table.Model_Variable_Symbol[key]);
  }
  fprintf(DEMO, "NegLogLike\n");

  double * r_Factor  = (double *)calloc( No_of_CITIES, sizeof(double) );
  double * x0_Factor = (double *)calloc( No_of_CITIES, sizeof(double) );
  double * y0_Factor = (double *)calloc( No_of_CITIES, sizeof(double) );

  for(k = 0; k<No_of_CITIES; k++) {
    printf("... calculating city: %s\n", City_Names[k]);

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

    Converting_Total_Population_into_Adult_Population( City_Names[k], Time.Time_Vector,
     						       Empirical_Data_Matrix, I_Time );

    assert( SUB_OUTPUT_VARIABLES == 1);
    assert( Time_Dependence.No_of_TIMES == I_Time );

    /* B E G I N : Reserving memmory for Observed Data and Fitting Structure */
    Observed_Data * Data = (Observed_Data *)calloc(1, sizeof(Observed_Data));
    Observed_Data_Alloc( Data, SUB_OUTPUT_VARIABLES, I_Time);
    Observed_Data_Initialization( Data, SUB_OUTPUT_VARIABLES, I_Time,
				  Empirical_Data_Matrix, City_Names[k] );
    printf(" Observe_Data structure has been correctly allocated and initiated\n");
    /*     E N D : ------------------------------------- */

    Parameter_Fitting * F = (Parameter_Fitting*)calloc(1,sizeof(Parameter_Fitting));
    F->Data         = Data;
    F->Space        = Space;
    F->Table        = &Table;
    F->Verbose      = 1; // 1: Verbose                // 0: Non Verbose
    F->Minimization = 1; // 1: Function Minimization  // 0: Function Evalution
    F->Bounded_Parameter_Set = 1;
    F->Function     = GSL_Function_to_Minimize;

    Initial_Condition_from_Data_into_Parameter_Table (&Table, Empirical_Data_Matrix);
    printf("Initial Guess (%s): r_F = %g\n", City_Names[k], r_F);  Table.r_F = r_F;
    getchar();
    Min_Value = GSL_Minimization_Driver( F );

    printf("City %s:\t Min Value: D=%g\tBest Estimates: \n", City_Names[k], Min_Value);
    r_Factor[k]  = Table.r_F;
    x0_Factor[k] = Table.XS__0/(Table.XS__0 + Table.YS__0);
    y0_Factor[k] = Table.YS__0/(Table.XS__0 + Table.YS__0);

    fprintf(DEMO, "%s\t", City_Names[k]);
    for(i=0; i<No_of_PARAMETERS; i++) {
      key = Space->Parameter_Index[i];
      value = AssignStructValue_to_VectorEntry(key, &Table);
      printf("%s = %g  ", Table.Symbol_Parameters[key], value);
      fprintf(DEMO, "%g\t", value);
    }
    for(i=0; i<No_of_IC; i++) {
      key = Initial_Condition_Space->Parameter_Index[i];
      value = Model_Variable_Initial_Condition_into_Vector_Entry_Table( key, &Table );
      printf("%s = %g  ", Table.Model_Variable_Symbol[key], value);
    }
    fprintf(DEMO, "%g\t%g\t", x0_Factor[k], y0_Factor[k]);
    fprintf(DEMO, "%g\n", Min_Value);
    printf("\n\n");

    /* Rewriting Corrected Time Dependent File for each City */
    for(i=0; i<I_Time; i++) {
      Time_Dependence.Dependent_Parameter[0][i] *= Table.r_F;
      Time_Dependence.Dependent_Parameter[1][i] *= Table.r_F;
    }
    Writing_Standard_Data_Matrix_to_File(TIME_PARAMETERS_FILE_CORRECTED[k],
					 Time_Dependence.Dependent_Parameter,
					 4, I_Time,
					 0, Name_of_Rows,
					 1, Time_Dependence.Time_Vector);


    Observed_Data_Free(Data);
    free(Data);
    free(F);
  }
  fclose(DEMO);

  /* BEGIN : -------------------------------------------------------------------------
   * Correcting extrapolated data
   */
  int No_of_TIMES = 34;
  double ** Type_1_Parameter_Values = (double **)calloc( TYPE_1_PARAMETERS, sizeof(double *));
  for(i = 0; i<TYPE_1_PARAMETERS; i++)
    Type_1_Parameter_Values[i] = (double *)calloc( No_of_TIMES, sizeof(double));
  double * Time_Vector         = (double *)calloc( No_of_TIMES, sizeof(double));
  char ** TIME_FILE_EXTRAPOLATED_CORRECTED = (char **)calloc(No_of_CITIES, sizeof(char *) );
  char ** TIME_FILE_EXTRAPOLATED           = (char **)calloc(No_of_CITIES, sizeof(char *) );
  for(k = 0; k<No_of_CITIES; k++) {

    TIME_FILE_EXTRAPOLATED[k] = (char *)calloc( 100, sizeof(char) );
    pF = strcat(TIME_FILE_EXTRAPOLATED[k], "Time_Dependent_Parameters_Extrapolated_");
    pF = strcat(TIME_FILE_EXTRAPOLATED[k], City_Names[k]);
    pF = strcat(TIME_FILE_EXTRAPOLATED[k], ".dat");

    TIME_FILE_EXTRAPOLATED_CORRECTED[k] = (char *)calloc( 200, sizeof(char) );
    pF = strcat(TIME_FILE_EXTRAPOLATED_CORRECTED[k],
		"Time_Dependent_Parameters_Extrapolated_Corrected_");
    pF = strcat(TIME_FILE_EXTRAPOLATED_CORRECTED[k], City_Names[k]);
    pF = strcat(TIME_FILE_EXTRAPOLATED_CORRECTED[k], ".dat");

    Reading_Standard_Data_Matrix_from_File( TIME_FILE_EXTRAPOLATED[k],
					    Type_1_Parameter_Values,
					    &TYPE_1_PARAMETERS, No_of_TIMES,
					    0, Name_of_Rows,
					    1, Time_Vector );

    assert(TYPE_1_PARAMETERS == 4);

    for(i=0; i<No_of_TIMES; i++) {
      Type_1_Parameter_Values[0][i] *= r_Factor[k];
      Type_1_Parameter_Values[1][i] *= r_Factor[k];
    }

    Writing_Standard_Data_Matrix_to_File(TIME_FILE_EXTRAPOLATED_CORRECTED[k],
					 Type_1_Parameter_Values,
					 TYPE_1_PARAMETERS, No_of_TIMES,
					 0, Name_of_Rows,
					 1, Time_Vector);

    free(TIME_FILE_EXTRAPOLATED_CORRECTED[k]);
    free(TIME_FILE_EXTRAPOLATED[k]);

    Converting_Total_Population_into_Adult_Population_Extrapolated (City_Names[k]);
    /*   END : -------------------------------------------------------------------------
     */
  }
  free(TIME_FILE_EXTRAPOLATED_CORRECTED);
  free(TIME_FILE_EXTRAPOLATED );
  for(i = 0; i<TYPE_1_PARAMETERS; i++) free (Type_1_Parameter_Values[i]);
  free (Type_1_Parameter_Values);
  free(Time_Vector); free(r_Factor); free(x0_Factor); free(y0_Factor);

  /* BEGIN : -------------------------------------------------------------------------
     Redimensioning Index vector to include and save the full list of model parameters
     Redefinition of Parameter Space structure to allocate the whole parameter space
     This operation can only be done at the end of a main file (before freeing memmory
     and ending).
  */
  Parameter_Space_Free(Space, No_of_PARAMETERS);

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

  for(k = 0; k<No_of_CITIES; k++) {
    free(TIME_PARAMETERS_FILE[k]);
    free(TIME_PARAMETERS_FILE_CORRECTED[k]);
    free(OBSERVED_DATA_FILE[k]);
  }
  free(TIME_PARAMETERS_FILE);
  free(TIME_PARAMETERS_FILE_CORRECTED);
  free(OBSERVED_DATA_FILE);

  P_A_R_A_M_E_T_E_R___T_A_B_L_E___F_R_E_E( &Table );
  /*  END : Freeing  All Memmory * * * * * * * * * * * * * * */

  printf("\nEnd of progam\n");
  return (0);
}

void Converting_Total_Population_into_Adult_Population (const char * City_Name,
							double * Year_Vector,
							double ** Data, int N)
{
  char ** Dummy_Name_of_Rows;
  double c0, c1, cov00, cov01, cov11, chisq, y_Fit, yf_err, f;
  int j;
  char * pF;
  char * OBSERVED_DATA_FILE = (char *)calloc( 100, sizeof(char) );

  pF = strcat(OBSERVED_DATA_FILE, "Adult_City_Population_");
  pF = strcat(OBSERVED_DATA_FILE, City_Name);
  pF = strcat(OBSERVED_DATA_FILE, ".dat");

  FILE  * fp = fopen(OBSERVED_DATA_FILE, "w");

  double y[] = {44.4, 39.87, 39.55};
  double x[] = {1975.0, 2017.0, 2018};

  gsl_fit_linear(x, 1, y, 1, 3,
		   &c0, &c1, &cov00, &cov01, &cov11, &chisq);

  printf(" Fractions of Children Population (age < 15): f(year)\n");
  printf(" Total and Adult Population, P(year) and A(year), respectively\n");
  for(j = 0; j < N ; j++) {

      gsl_fit_linear_est (Year_Vector[j], c0, c1, cov00, cov01, cov11,
			  &y_Fit, &yf_err);

      f = y_Fit + (gsl_rng_uniform(r)-1.0) * yf_err;
      printf("f[%g] = %g\t", Year_Vector[j], f);

      printf("P(%g) = %g\t", Year_Vector[j], Data[0][j]);

      Data[0][j] = (1.0 - 0.01 * f) * Data[0][j];

      printf("A(%g) = %g\n", Year_Vector[j], Data[0][j]);
  }

  Writing_Standard_Data_Matrix_to_File( OBSERVED_DATA_FILE,
					Data,
					1, N,
					0, Dummy_Name_of_Rows,
					0, Year_Vector );
  fclose(fp);

  free(OBSERVED_DATA_FILE);

  getchar();
}

void Converting_Total_Population_into_Adult_Population_Extrapolated (const char * City_Name)
{
  char ** Dummy_Name_of_Rows;
  double c0, c1, cov00, cov01, cov11, chisq, y_Fit, yf_err, f;
  int j;
  int n;
  char * pF;
  char * OBSERVED_DATA_FILE            = (char *)calloc( 100, sizeof(char) );
  char * TOTAL_POPULATION_EXTRAPOLATED = (char *)calloc( 100, sizeof(char) );

  int N = 34;
  double * Year_Vector = (double *)calloc( N, sizeof(double) );
  double ** Data   = (double **)calloc( 1, sizeof(double *) );
  Data[0] =  (double *)calloc( N, sizeof(double) );

  for(j = 0; j<N; j++) Year_Vector[j] = 2000.0 + (double)j;

  pF = strcat(TOTAL_POPULATION_EXTRAPOLATED, "Total_City_Population_Extrapolated_");
  pF = strcat(TOTAL_POPULATION_EXTRAPOLATED, City_Name);
  pF = strcat(TOTAL_POPULATION_EXTRAPOLATED, ".dat");

  Reading_Standard_Data_Matrix_from_File( TOTAL_POPULATION_EXTRAPOLATED,
					  Data,
					  &n, N,
					  0, Dummy_Name_of_Rows,
					  0, Year_Vector );
  assert( n == 1);

  pF = strcat(OBSERVED_DATA_FILE, "Adult_City_Population_Extrapolated_");
  pF = strcat(OBSERVED_DATA_FILE, City_Name);
  pF = strcat(OBSERVED_DATA_FILE, ".dat");

  FILE  * fp = fopen(OBSERVED_DATA_FILE, "w");

  double y[] = {44.4, 39.87, 39.55};
  double x[] = {1975.0, 2017.0, 2018};

  gsl_fit_linear(x, 1, y, 1, 3,
		   &c0, &c1, &cov00, &cov01, &cov11, &chisq);

  printf(" Fractions of Children Population (age < 15): f(year)\n");
  printf(" Total and Adult Population, P(year) and A(year), respectively\n");
  for(j = 0; j < N ; j++) {

      gsl_fit_linear_est (Year_Vector[j], c0, c1, cov00, cov01, cov11,
			  &y_Fit, &yf_err);

      f = y_Fit + (gsl_rng_uniform(r)-1.0) * yf_err;
      printf("f[%g] = %g\t", Year_Vector[j], f);

      printf("P(%g) = %g\t", Year_Vector[j], Data[0][j]);

      Data[0][j] = (1.0 - 0.01 * f) * Data[0][j];

      printf("A(%g) = %g\n", Year_Vector[j], Data[0][j]);
  }

  Writing_Standard_Data_Matrix_to_File( OBSERVED_DATA_FILE,
					Data,
					1, N,
					0, Dummy_Name_of_Rows,
					0, Year_Vector );
  fclose(fp);

  free(OBSERVED_DATA_FILE);
  free(TOTAL_POPULATION_EXTRAPOLATED);
  free(Year_Vector);
  free(Data[0]);
  free(Data);

  getchar();
}
