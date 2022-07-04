/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                            David Alonso, 2018 (c)                         */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#include <Include/MODEL.h>

#include "global.h"

gsl_rng * r; /* Global generator defined in main.c */

/* This code reads population data (for every city). Then, plot out a bunch of
   empirical temporal evolutions, but the central focus of the code is to 
   estimate recruitment rates, F_X, F_Y, and sex-specific mortalities from 
   life table, fecundity and population data for each city.

   Estimated parameters and then organized in four-row matrices of time dependent 
   parameters that span either the fitting period (2000-2016) or the whole period
   (2000-2033). These are saved in files of two types:

   	. Time_Dependent_Parameters_[City_Name].dat (2000-2016)
 
	. Time_Dependent_Parameters_Extrapolated_[City_Name].dat (2000-2033)

   Time dependent parameter files are used all over for parameter
   estimation procedure through random searches, but first recruitment ratess are 
   corrected by a constat fittet parameters, r. This is done in:

   . ~/PROJECT_HIV-AIDS_MADAGASCAR/MODEL_CALCULATIONS/TEMPORAL_EVOLUTION_r_FACTOR_ESTIMATE$   

   where the corresponding corrected final files are saved: 

   	. Time_Dependent_Parameters_Corrected_[City_Name].dat (2000-2016)
 
        . Time_Dependent_Parameters_Extrapolated_Corrected_[City_Name].dat (2000-2033)

   Compilation (example 1):

   . ~$ make X_MODEL=X_ Y_MODEL=Y_

   Execution:

   . ~$ ./X_-Y_ -y0 2 -G0 3 -G1 3 -tn 34 -t0 2000.0 -t1 2033.0 -t4 1 -xn 0 -xN 1000000 -H2 25000 -H13 25000 -G5 1 -G6 0.0 -G7 1000000

   -xn TYPE of INITIAL CONDITION (0 from default values or Input Args; 1 at Random; 2 from fixed Point)
   -xN INITIAL TOTAL POPULATION SIZE
   -t4 TYPE of TIME DEPENDENCE (0, no parameter time dependence). If the TYPE of TIME DEPENDENCE input argument is greater than 0, time dependence parameters are at play.
   See, for instance, ./Definition_Numerical_Integration/XWSILD-YSILD/deterministic_time_dynamics.c

   See file denition_OutPut_Variables.c for full -v?? codes definition. Examples are:

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

void Fecundity_Estimation( double ** M_a, int N,
			   double * X,
			   double * b,
			   int N_1,
			   double f,
			   int a_0, double RLS,
			   double * F0,
			   int N_0 );

void Build_File_of_Time_Parameters_2000_2016 (double ** Data_Matrix,
                                              double ** Age_Death_Rates_Female,
                                              double ** Age_Death_Rates_Male,
                                              int * No_of_Age_Groups,
                                              double ** Urban_Population_Vector,
                                              double *  Fecundity_Vector,
                                              double *  Year_1983_2016,
                                              char   **  Names,
                                              int * No_of_Cities,
                                              int * No_1983_2016,
                                              Parameter_Table * Table);

void Build_File_of_Time_Parameters_2000_2033 (double ** Data_Matrix,
                                              double ** Age_Death_Rates_Female,
                                              double ** Age_Death_Rates_Male,
                                              int * No_of_Age_Groups,
                                              double ** Urban_Population_Vector,
                                              double *  Fecundity_Vector,
                                              double *  Year_1983_2033,
                                              char   **  Names,
                                              int * No_of_Cities,
                                              //int TYPE_1_PARAMETERS,
                                              //int No_of_TIMES,
                                              int * No_1983_2033,
                                              Parameter_Table * Table);
int main(int argc, char **argv)
{
  int i, j, k, n;
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
				   "File_of_Covariates.dat", "File_of_Time_Parameters.dat" );
    printf(" Both Time_Control and Time_Dependence_Control structures have been\n");
    printf(" correctly allocated and initiated\n");
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

  char * FILE_of_TIME_PARAMETERS = "File_of_Time_Parameters.dat"; char * pF;
  char * CITY_FILE_of_PARAMETERS = (char *)calloc(100, sizeof(char));

  int No_of_TIMES = I_Time;
  No_of_COVARIATES = 0;
  TYPE_0_PARAMETERS = 0;
  TYPE_1_PARAMETERS = 4;   /* F_X, F_Y, delta_X, delta_Y */
  TYPE_2_PARAMETERS = 0;
  TIME_DEPENDENT_PARAMETERS = TYPE_0_PARAMETERS + TYPE_1_PARAMETERS + TYPE_2_PARAMETERS;

  double ** Data_Matrix = (double **)calloc(TIME_DEPENDENT_PARAMETERS, sizeof(double *));
  char ** Name_of_Rows  = (char **)calloc(TIME_DEPENDENT_PARAMETERS, sizeof(char *));
  for(i=0; i<TIME_DEPENDENT_PARAMETERS; i++) {
    Data_Matrix[i] = (double *)calloc(No_of_TIMES, sizeof(double));
    Name_of_Rows[i] = (char *)calloc(50, sizeof(char) );
    k = Table.TDC->Index_Dependent_Parameters[i];
    pF = strcat(Name_of_Rows[i], Table.Symbol_Parameters[k]);
  }

  printf("Checking time vector [%d years]:\n", No_of_TIMES);
  for(i=0; i<No_of_TIMES; i++)
    printf("Time[%d] = %g  ", i, Table.TDC->Time_Vector[i]);
  printf("\n");

  char ** Name_Dummy;
  int No_of_Rows_Max    =  50;
  int No_of_Columns_Max = 200;
  int No_of_CITIES      =  11;
  double ** Age_Death_Rates_Female = (double **)calloc(No_of_Rows_Max, sizeof(double *) );
  double ** Age_Death_Rates_Male = (double **)calloc(No_of_Rows_Max, sizeof(double *) );
  for(i=0; i<No_of_Rows_Max; i++) {
    Age_Death_Rates_Female[i] = (double *)calloc(No_of_Columns_Max, sizeof(double) );
    Age_Death_Rates_Male[i] = (double *)calloc(No_of_Columns_Max, sizeof(double) );
  }
  double ** Urban_Population_Vector = (double **)calloc(No_of_CITIES, sizeof(double *) );
  for(i=0; i<No_of_CITIES; i++)
    Urban_Population_Vector[i] = (double *)calloc(No_of_Columns_Max, sizeof(double) );
  double * Fecundity_Vector = (double *)calloc(No_of_Columns_Max, sizeof(double) );
  double *  Year_1983_2016  = (double *)calloc(No_of_Columns_Max, sizeof(double) );
  double *  Year_1983_2033  = (double *)calloc(No_of_Columns_Max, sizeof(double) );
  char ** City_Names = (char **)calloc(No_of_Rows_Max, sizeof(char *) );
  for(i=0; i<No_of_Rows_Max; i++)
    City_Names[i] = (char *)calloc(50, sizeof(char) );

  int No_of_TIMES_1983_2016; int No_of_Age_Groups; int No_of_Cities;
  Build_File_of_Time_Parameters_2000_2016 (Data_Matrix,
					   Age_Death_Rates_Female,
					   Age_Death_Rates_Male,
					   &No_of_Age_Groups,
					   Urban_Population_Vector,
					   Fecundity_Vector,
					   Year_1983_2016,
					   City_Names,
					   &No_of_Cities,
					   &No_of_TIMES_1983_2016,
					   &Table);
  assert(No_of_CITIES == No_of_Cities);
  printf("\n");

  printf(" Build of File Time Parameters (2000-2016) has been done!!!\n"); getchar();

  printf("Writing Female Age Specific Mortality Rates:\n");
  Writing_Standard_Data_Matrix(Age_Death_Rates_Female,
			       No_of_Age_Groups, No_of_TIMES_1983_2016,
			       0, Name_Dummy,
			       1, Year_1983_2016);
  printf("\n");

  printf("Printing out and saving Urban Populations:\n");
  Writing_Standard_Data_Matrix(Urban_Population_Vector,
			       No_of_CITIES, No_of_TIMES_1983_2016,
			       1, City_Names,
			       1, Year_1983_2016);

  printf("Checking time vector [%d years] (after Build File of Parameters 2000-2016):\n", No_of_TIMES);
  for(i=0; i<No_of_TIMES; i++)
    printf("Time[%d] = %g  ", i, Table.TDC->Time_Vector[i]);
  printf("\n");

  {
    char * OBSERVED_DATA_FILE = (char *)calloc( 100, sizeof(char) );
    FILE * fp;
    char * pf;
    for(k = 0; k<No_of_CITIES; k++) {

      OBSERVED_DATA_FILE[0] = '\0';
      pF = strcat(OBSERVED_DATA_FILE, "Total_City_Population_");
      pF = strcat(OBSERVED_DATA_FILE, City_Names[k]);
      pF = strcat(OBSERVED_DATA_FILE, ".dat");

      fp = fopen(OBSERVED_DATA_FILE, "w");

      for(i=No_of_TIMES/2; i<No_of_TIMES_1983_2016; i++)
	fprintf(fp, "%g\t", Urban_Population_Vector[k][i] );

      fclose(fp);
    }
    free( OBSERVED_DATA_FILE );
    printf("\n");
  }

  int No_of_TIMES_1983_2033;
  Build_File_of_Time_Parameters_2000_2033 (Data_Matrix,
					   Age_Death_Rates_Female,
					   Age_Death_Rates_Male,
					   &No_of_Age_Groups,
					   Urban_Population_Vector,
					   Fecundity_Vector,
					   Year_1983_2033,
					   City_Names,
					   &No_of_Cities,
					   &No_of_TIMES_1983_2033,
					   &Table);
  assert(No_of_CITIES == No_of_Cities);

  printf("\n");
  printf("Writing Female Age Specific Mortality Rates:\n");
  Writing_Standard_Data_Matrix(Age_Death_Rates_Female,
			       No_of_Age_Groups, No_of_TIMES_1983_2033,
			       0, Name_Dummy,
			       1, Year_1983_2033);
  printf("\n");

  printf("Printing out and saving Urban Populations:\n");
  Writing_Standard_Data_Matrix(Urban_Population_Vector,
			       No_of_CITIES, No_of_TIMES_1983_2033,
			       1, City_Names,
			       1, Year_1983_2033);

  printf("Checking time vector [%d years] (after filling Data_Matrix):\n", No_of_TIMES);
  for(i=0; i<No_of_TIMES; i++)
    printf("Time[%d] = %g  ", i, Table.TDC->Time_Vector[i]);
  printf("\n");

  {
    char * OBSERVED_DATA_FILE = (char *)calloc( 100, sizeof(char) );
    FILE * fp;
    char * pf;
    for(k = 0; k<No_of_CITIES; k++) {

      OBSERVED_DATA_FILE[0] = '\0';
      pF = strcat(OBSERVED_DATA_FILE, "Total_City_Population_Extrapolated_");
      pF = strcat(OBSERVED_DATA_FILE, City_Names[k]);
      pF = strcat(OBSERVED_DATA_FILE, ".dat");

      fp = fopen(OBSERVED_DATA_FILE, "w");

      for(i=No_of_TIMES/2; i<No_of_TIMES_1983_2033; i++)
	fprintf(fp, "%g\t", Urban_Population_Vector[k][i] );

      fclose(fp);
    }
    free( OBSERVED_DATA_FILE );
    printf("\n");
  }

  for(i=0; i<No_of_TIMES_1983_2016; i++)
    printf("Year: %g\t Total Fecundity: %g\n", Year_1983_2016[i], Fecundity_Vector[i]);

  for(i=0; i<No_of_TIMES_1983_2033; i++)
    printf("Year: %g\t Total Fecundity: %g\n", Year_1983_2033[i], Fecundity_Vector[i]);

  /* Determining F_X and F_Y model parameters for every city for a period between
     2000 and 2016 (No_of_TIMES) for a given r factor (Table.r_F) as a function of:
     . Age Dependent Mortality Rates, which define survival,
     . Urban Populations,
     . Total Fecundities (and a_0 and a_1, i. e., ages defining the female fertile life span),
     . sex ratio at birth, and
     . the r Factor (empirical value to be determined, stored in Table.r_F)
  */
  double ** F_X0 = (double **)calloc(No_of_CITIES, sizeof(double *));
  double ** F_Y0 = (double **)calloc(No_of_CITIES, sizeof(double *));
  for(i = 0; i<No_of_CITIES; i++) {
    F_X0[i] = (double *)calloc(No_of_TIMES, sizeof(double));
    F_Y0[i] = (double *)calloc(No_of_TIMES, sizeof(double));
  }

  int a_0_X; // Age of entrance in sexual adult life (adulthood) for females
  int a_0_Y; // Age of entrance in sexual adult life (adulthood) for males
  int a_1_X; // RLS : a_1_X - a_0_X: the reproductive life span (20 years)

  a_0_X = 15;
  a_1_X = 50; // Children bearing age is between 15 and 45.
  a_0_Y = 17;

  double RLS, Sex_Ratio;

  // Sex ratio at birth (ratio of males to females at birth) positively biased towards males.
  // 1.02 in Madagascar

  Sex_Ratio = 1.02 / (1.0 + 1.02);

  RLS = (double)(a_1_X - a_0_X);

  for(i = 0; i<No_of_CITIES; i++) {

      Fecundity_Estimation ( Age_Death_Rates_Female, No_of_Age_Groups,
			     Urban_Population_Vector[i],
			     Fecundity_Vector,
			     No_of_TIMES_1983_2016,
			     1.0 - Sex_Ratio,
			     a_0_X, RLS,
			     F_X0[i],
			     No_of_TIMES/2 );

      Fecundity_Estimation ( Age_Death_Rates_Male, No_of_Age_Groups,
			     Urban_Population_Vector[i],
			     Fecundity_Vector,
			     No_of_TIMES_1983_2016,
			     Sex_Ratio,
			     a_0_Y, RLS,
			     F_Y0[i],
			     No_of_TIMES/2 );

      printf("\n");
      printf(" City: %s\n", City_Names[i]);
      for(j=0; j<No_of_TIMES/2; j++)
	printf("F_X0[%g] = %g\t F_Y0[%g] = %g\n",
	       Table.TDC->Time_Vector[j], F_X0[i][j],
	       Table.TDC->Time_Vector[j], F_Y0[i][j] );

      for(j=0; j<No_of_TIMES/2; j++) {
	Data_Matrix[0][j] = F_X0[i][j];
	Data_Matrix[1][j] = F_Y0[i][j];
      }

      CITY_FILE_of_PARAMETERS[0] = '\0';
      pF = strcat(CITY_FILE_of_PARAMETERS, "Time_Dependent_Parameters_");
      pF = strcat(CITY_FILE_of_PARAMETERS, City_Names[i]);
      pF = strcat(CITY_FILE_of_PARAMETERS, ".dat");
      Writing_Standard_Data_Matrix_to_File(CITY_FILE_of_PARAMETERS,
					   Data_Matrix,
					   4, No_of_TIMES/2,
					   0, Name_of_Rows,
					   1, Table.TDC->Time_Vector);
  }

  /* Determining F_X and F_Y model parameters for every city for a period between
     2000 and 2033 (No_of_TIMES) for a given r factor (Table.r_F) as a function of:
     . Age Dependent Mortality Rates, which define survival,
     . Urban Populations,
     . Total Fecundities (and a_0 and a_1, i. e., ages defining the female fertile life span),
     . sex ratio at birth, and
     . the r Factor (empirical value to be determined, stored in Table.r_F)
  */

  for(i = 0; i<No_of_CITIES; i++) {

      Fecundity_Estimation ( Age_Death_Rates_Female, No_of_Age_Groups,
			     Urban_Population_Vector[i],
			     Fecundity_Vector,
			     No_of_TIMES_1983_2033,
			     1.0 - Sex_Ratio,
			     a_0_X, RLS,
			     F_X0[i],
			     No_of_TIMES/2 );

      Fecundity_Estimation ( Age_Death_Rates_Male, No_of_Age_Groups,
			     Urban_Population_Vector[i],
			     Fecundity_Vector,
			     No_of_TIMES_1983_2033,
			     Sex_Ratio,
			     a_0_Y, RLS,
			     F_Y0[i],
			     No_of_TIMES/2 );

      printf("\n");
      printf(" City: %s\n", City_Names[i]);
      for(j=0; j<No_of_TIMES; j++)
	printf("F_X0[%g] = %g\t F_Y0[%g] = %g\n",
	       Table.TDC->Time_Vector[j], F_X0[i][j],
	       Table.TDC->Time_Vector[j], F_Y0[i][j] );

      for(j=0; j<No_of_TIMES; j++) {
	Data_Matrix[0][j] = F_X0[i][j];
	Data_Matrix[1][j] = F_Y0[i][j];
      }

      CITY_FILE_of_PARAMETERS[0] = '\0';
      pF = strcat(CITY_FILE_of_PARAMETERS, "Time_Dependent_Parameters_Extrapolated_");
      pF = strcat(CITY_FILE_of_PARAMETERS, City_Names[i]);
      pF = strcat(CITY_FILE_of_PARAMETERS, ".dat");
      Writing_Standard_Data_Matrix_to_File(CITY_FILE_of_PARAMETERS,
					   Data_Matrix,
					   4, No_of_TIMES,
					   0, Name_of_Rows,
					   1, Table.TDC->Time_Vector);
  }

  /* BEGIN : Freeing All Memmory * * * * * * * * * * * * * * */
  free(CITY_FILE_of_PARAMETERS);

  for(i = 0; i<No_of_CITIES; i++) {
    free(F_X0[i]);
    free(F_Y0[i]);
  }
  free(F_X0); free(F_Y0);

  for(i=0; i<No_of_Rows_Max; i++) {
    free(Age_Death_Rates_Female[i]);
    free(Age_Death_Rates_Male[i]);
    free(City_Names[i]);
  }
  free(Age_Death_Rates_Female);
  free(Age_Death_Rates_Male);
  free(City_Names);
  for(i=0; i<No_of_CITIES; i++) free(Urban_Population_Vector[i]);
  free (Urban_Population_Vector);
  free (Fecundity_Vector);
  free (Year_1983_2016);

  for(i=0; i<TIME_DEPENDENT_PARAMETERS; i++) {
    free( Data_Matrix[i] );
    free( Name_of_Rows[i] );
  }
  free(Data_Matrix);
  free(Name_of_Rows);

  // M_O_D_E_L( &Table );

#if defined CPGPLOT_REPRESENTATION
  P_A_R_A_M_E_T_E_R___C_P_G_P_L_O_T___F_R_E_E( Table.CPG, SUB_OUTPUT_VARIABLES );
  cpgclos();
#endif

  #include <include.Parameter_Space.default.free.c>
  Parameter_Space_Free(Space, No_of_PARAMETERS);

   #include <include.Output_Variables.default.free.c>

  #include <include.Time_Dependence_Control.default.free.c>
  if (TYPE_of_TIME_DEPENDENCE == 0) T_I_M_E___C_O_N_T_R_O_L___F_R_E_E( &Time, &Table );
  else                        Time_Dependence_Control_Free( &Time_Dependence, &Table );

  P_A_R_A_M_E_T_E_R___T_A_B_L_E___F_R_E_E( &Table );
  /*  END : Freeing  All Memmory * * * * * * * * * * * * * * */

  printf("\nEnd of progam\n");
  return (0);
}

void Fecundity_Estimation( double ** M_a, int N,
			   double * X,
			   double * b,
			   int N_1,
			   double f,
			   int a_0, double RLS,
			   double * F0,
			   int N_0 )
  {
    /* See Eq. B15-B16, appendix B of the paper */

    int i, j, n, m, t;
    double LogF0;

    double ** s = (double **)calloc(5, sizeof(double *));
    for(i = 0; i<5; i++) s[i] = (double *)calloc(N_1, sizeof(double));

    assert( a_0 < 20 );

    for(i = 0; i<5; i++)
      for(j=0; j<N_1; j++)
	s[i][j] = (1.0 - M_a[i][j]) / (1.0 + M_a[i][j]); /* Survival Probability Rates (per year) */
                                                         /* for every age group and year          */
    for (j = N_0; j < N_1; j++) {

      LogF0 = 0.0;
      n  = a_0-1;
      t  = j-1;
      while ( n >= 0 ) {

	if( n == 0 )            m = 0;
	if( n >=  1  && n < 5)  m = 1;
	if( n >=  5  && n < 10) m = 2;
	if( n >= 10  && n < 15) m = 3;
	if( n >= 15  && n < 20) m = 4;

	LogF0 += log(s[m][t]);
	n--;
	t--;
      }

      F0[j-N_0] = f * (b[t+1]/RLS) * X[t+1]/2.0 * exp(LogF0);
    }


    for(i = 0; i<5; i++) free(s[i]);
    free(s);
}
