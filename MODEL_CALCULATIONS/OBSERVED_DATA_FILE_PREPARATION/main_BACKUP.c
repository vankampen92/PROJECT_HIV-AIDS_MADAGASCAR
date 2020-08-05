/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                            David Alonso, 2018 (c)                         */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <IO_Procedures_Standard.h>

/* This code prepares observed data file for each city of five different types:

   1. Observed_Data_File_[City_Name].dat is a three row file containing:

      1st Row: Population data from 2000 to 2016 (Adult Population)
      2on Row: Women Sexual Worker Population data from 2000 to 2016
      3rd Row: Total Number of Infected SW Women data from 2000 to 2016

      These files are created under three different assumptions about the prevalence
      of the disesase in 2000, 1%, 5%, 25%, 50% and 100% of that in 2016. These
      creates 5 different observed data file per city:

      . Observed_Data_File_[City_Name].dat (same prevalence levels as those in 2016)
      . Observed_Data_File_[City_Name]_1.dat (1% of prevalence levels in 2016)
      . Observed_Data_File_[City_Name]_5.dat (1% of prevalence levels in 2016)
      . Observed_Data_File_[City_Name]_25.dat (1% of prevalence levels in 2016)
      . Observed_Data_File_[City_Name]_50.dat (1% of prevalence levels in 2016)

   2. Observed_Data_File_2Rows_[City_Name].dat is a two row file containing:

      1st Row: Population data from 2000 to 2016
      2on Row: Women Sexual Worker Population data from 2000 to 2016

   3. Observed_Data_[City_Name]_[n].dat are files where [n] is the initial year.
      So, n spans from initial year to 2014. These are also three row files with:

      1st Row: Population data from n to 2016 (Adult Population)
      2on Row: Women Sexual Worker Population data from n to 2016
      3rd Row: Total Number of Infected Women data from n to 2016

      The number of infected women (out of the total of sexual workers) at the
      initial year is fixed to 1% of the level in 2016.

   Observed SW women from 2000 to 2016 are estimated from data under two hyphotesis:

   A. The ratio of SW women to the total female population, XX, Ratio = SWXX/XX remains constant;
   B. The ratio of SW women to the total female population follows a sigmoidal curve with parameters
   A_0, L_0, and T_0, where A_0 is calculated to match the SW women observed in 2014.

   In case A, observed files will end as follows:

   . Observed_Data_File_2Rows_[City_Name].dat
   . Observed_Data_File_[City_Name]_Exponential.dat

   are saved, while in case B, we save files as follows:

   . Observed_Data_File_2Rows_[City_Name]_Sigmoidal.dat
   . Observed_Data_File_[City_Name]_Sigmoidal_Exponential.dat

   where the 2nd row of the last type of files contain a sigmoidal temporal evolution
   of the number of sexual workers across years.

   To cover case A and B, you need to change the name of the files to save, which you should
   do it manually by chaging the code. So you need to run the program twice to generate
   files under either type of hypothesis.

   4. Time_Dependent_Parameters_Corrected_[City_Name]_[n].dat are files of time dependent
   parameters starting at n as the initial year up to year 2014 for each city.

   5. Time_Dependent_Parameters_Extrapolated_Corrected_[City_Name]_[n].dat are files
   of time dependent parameters starting at n as the initial year upto year 2033
   for each city.

   Compilation:

   . ~$ make

   Exectution: (Time-dependent parameters: -t4 1)

   . ~$ ./Data_File_Generation

*/

void Defining_Sigmoidal_Ratio(double *, const int , const double , const double, double , double);

double Increasing_Exponential_Function(double , double , int , int );

int main(int argc, char **argv)
{
  int i, j, k, n, I_Time, I_Time_34;
  double Ratio, x_0, x_1;
  int No_of_OBSERVED_VARIABLES, No_of_Rows;
  int SIGMOIDAL; 

  I_Time                   = 17;
  I_Time_34                = 34;
  No_of_OBSERVED_VARIABLES =  3;
  No_of_Rows               =  4;

  SIGMOIDAL = 0; 
  /* Estimated HIV infection prevalence in 2012 and 2016 among SWs in the main cities of Madagascar */
  double Percentage_Prevalence_SW_2012[11] = {0.2, 0.0, 3.0, 1.8, 0.9, 1.2, 0.0, 0.3, 0.0, 6.5, 0.0};

  double * Sigmoidal_Ratio = (double *)calloc(34, sizeof(double));

  double const Break_Point       = 2011.0;
  double const Smoothness_Rate   = 0.1;
  double Assymptotic_Ratio       = 0.5; // Dummy Value: Determined in Defining_Sigmoidal_Ratio();

  double Time_Vector[17]      = {2000, 2001, 2002, 2003, 2004, 2005, 2006, 2007, 2008, 2009, 2010,
				 2011, 2012, 2013, 2014, 2015, 2016};

  double Time_Vector_Extrapolated[34] = {2000, 2001, 2002, 2003, 2004, 2005, 2006, 2007, 2008, 2009,
					 2010, 2011, 2012, 2013, 2014, 2015, 2016, 2017, 2018, 2019,
					 2020, 2021, 2022, 2023, 2024, 2025, 2026, 2027, 2028, 2029,
					 2030, 2031, 2032, 2033};

  char * Name_of_Rows[] = { "Total Population",
			    "Total Sexual Worker Population",
			    "Disease Prevalence (in numbers) in Sexual Worker Population" };

  double * Year_Vector = (double *)calloc(34, sizeof(double) );

  char * Year = (char *)calloc(10, sizeof(char) );

  double ** Empirical_Data_Matrix = (double **)calloc( No_of_OBSERVED_VARIABLES, sizeof(double *) );
  for (i=0; i<No_of_OBSERVED_VARIABLES; i++)
    Empirical_Data_Matrix[i] = (double *)calloc( I_Time, sizeof(double) );

  double ** Empirical_Short_Matrix = (double **)calloc( No_of_OBSERVED_VARIABLES, sizeof(double *) );
  for (i=0; i<No_of_OBSERVED_VARIABLES; i++)
    Empirical_Short_Matrix[i] = (double *)calloc( I_Time, sizeof(double) );

  double ** Time_Dependent_Parameter_Values = (double **)calloc( 4, sizeof(double *) );
  for (i=0; i<4; i++)
    Time_Dependent_Parameter_Values[i] = (double *)calloc( I_Time, sizeof(double) );

  double ** Time_Dependent_Shortened_Values = (double **)calloc( 4, sizeof(double *) );
  for (i=0; i<4; i++)
    Time_Dependent_Shortened_Values[i] = (double *)calloc( I_Time, sizeof(double) );

  double ** Time_Extrapolated_Parameter_Values = (double **)calloc( 4, sizeof(double *) );
  for (i=0; i<4; i++)
    Time_Extrapolated_Parameter_Values[i] = (double *)calloc( I_Time_34, sizeof(double) );

  double ** Time_Extrapolated_Shortened_Values = (double **)calloc( 4, sizeof(double *) );
  for (i=0; i<4; i++)
    Time_Extrapolated_Shortened_Values[i] = (double *)calloc( I_Time_34, sizeof(double) );

  int No_of_CITIES = 11;
  char ** City_Names = (char **)calloc(No_of_CITIES, sizeof(char *) );
  double ** Population_Data = (double **)calloc(No_of_CITIES, sizeof(double *) );
  for(k = 0; k<No_of_CITIES; k++) {
    City_Names[k] = (char *)calloc(100, sizeof(char) );
    Population_Data[k]= (double *)calloc(6, sizeof(double) );
  }

  Reading_Standard_Data_Matrix_from_File( "Population-2013-Sexual-Workers_and_Prevalence-2016.dat",
					  Population_Data,
					  &No_of_CITIES, 6,
					  1, City_Names,
					  0, Time_Vector );
  assert( No_of_CITIES == 11);

  /* B E G I N : Time Dependent Parameters and Observed Data File Names */
  char * pF;
  char ** OBSERVED_DATA_FILE_3_ROWS = (char **)calloc(No_of_CITIES, sizeof(char *) );
  char ** OBSERVED_DATA_FILE_2_ROWS = (char **)calloc(No_of_CITIES, sizeof(char *) );
  char ** OBSERVED_DATA_FILE   = (char **)calloc(No_of_CITIES, sizeof(char *) );
  char ** TIME_DEPENDENT_FILE  = (char **)calloc(No_of_CITIES, sizeof(char *) );
  char ** TIME_DEPENDENT_EXTRAPOLATED  = (char **)calloc(No_of_CITIES, sizeof(char *) );
  for(k = 0; k<No_of_CITIES; k++) {
    OBSERVED_DATA_FILE_3_ROWS[k]   = (char *)calloc( 100, sizeof(char) );
    OBSERVED_DATA_FILE_2_ROWS[k]   = (char *)calloc( 100, sizeof(char) );
    OBSERVED_DATA_FILE[k]          = (char *)calloc( 100, sizeof(char) );
    TIME_DEPENDENT_FILE[k]         = (char *)calloc( 100, sizeof(char) );
    TIME_DEPENDENT_EXTRAPOLATED[k] = (char *)calloc( 100, sizeof(char) );
  }

  for(k = 0; k<No_of_CITIES; k++) {
    OBSERVED_DATA_FILE_3_ROWS[k][0] = '\0';
    pF = strcat(OBSERVED_DATA_FILE_3_ROWS[k], "Observed_Data_File_");
    pF = strcat(OBSERVED_DATA_FILE_3_ROWS[k], City_Names[k]);
    if (SIGMOIDAL == 1) pF = strcat(OBSERVED_DATA_FILE_3_ROWS[k], "_Sigmoidal.dat");
    else                pF = strcat(OBSERVED_DATA_FILE_3_ROWS[k], ".dat");

    OBSERVED_DATA_FILE_2_ROWS[k][0] = '\0';
    pF = strcat(OBSERVED_DATA_FILE_2_ROWS[k], "Observed_Data_File_2Rows_");
    pF = strcat(OBSERVED_DATA_FILE_2_ROWS[k], City_Names[k]);
    if (SIGMOIDAL == 1) pF = strcat(OBSERVED_DATA_FILE_2_ROWS[k], "_Sigmoidal.dat");
    else                pF = strcat(OBSERVED_DATA_FILE_2_ROWS[k], ".dat");

    OBSERVED_DATA_FILE[k][0] = '\0';
    pF = strcat(OBSERVED_DATA_FILE[k], "Adult_City_Population_");
    pF = strcat(OBSERVED_DATA_FILE[k], City_Names[k]);
    pF = strcat(OBSERVED_DATA_FILE[k], ".dat");

    TIME_DEPENDENT_FILE[k][0] = '\0';
    pF = strcat(TIME_DEPENDENT_FILE[k], "Time_Dependent_Parameters_Corrected_");
    pF = strcat(TIME_DEPENDENT_FILE[k], City_Names[k]);
    pF = strcat(TIME_DEPENDENT_FILE[k], ".dat");

    TIME_DEPENDENT_EXTRAPOLATED[k][0] = '\0';
    pF = strcat(TIME_DEPENDENT_EXTRAPOLATED[k], "Time_Dependent_Parameters_Extrapolated_Corrected_");
    pF = strcat(TIME_DEPENDENT_EXTRAPOLATED[k], City_Names[k]);
    pF = strcat(TIME_DEPENDENT_EXTRAPOLATED[k], ".dat");
  }
  /*     E N D : ------------------------------------------------------ */

  for(k = 0; k<No_of_CITIES; k++) {
    printf("... calculating city: %s\n", City_Names[k]);

    Reading_Standard_Data_Matrix_from_File( OBSERVED_DATA_FILE[k],
					    Empirical_Data_Matrix,
					    &No_of_OBSERVED_VARIABLES, I_Time,
					    0, Name_of_Rows,
					    0, Time_Vector );

    assert( No_of_OBSERVED_VARIABLES ==  1 );
    assert( I_Time                   == 17 );

    No_of_OBSERVED_VARIABLES = 3;

    Empirical_Data_Matrix[1][16] = (Population_Data[k][1] + Population_Data[k][2])/2.0;
    Empirical_Data_Matrix[2][16] = 0.01 * (Population_Data[k][4] + Population_Data[k][5])/2.0 * Empirical_Data_Matrix[1][16];

    Writing_Standard_Data_Matrix_to_File(OBSERVED_DATA_FILE_3_ROWS[k],
					 Empirical_Data_Matrix,
					 No_of_OBSERVED_VARIABLES, I_Time,
					 0, Name_of_Rows,
					 0, Time_Vector);

    Reading_Standard_Data_Matrix_from_File( OBSERVED_DATA_FILE_3_ROWS[k],
					    Empirical_Data_Matrix,
					    &No_of_OBSERVED_VARIABLES, I_Time,
					    0, Name_of_Rows,
					    0, Time_Vector );

    Ratio = Empirical_Data_Matrix[1][16]/(Empirical_Data_Matrix[0][16]/2.0);

    printf("Sexual Worker Population to Total Population: %g\n", Ratio);
    if (SIGMOIDAL == 1) {
    // Sigmoidal Hypothesis (with parameters: Break_Point and Smoothness_Rate):
      Defining_Sigmoidal_Ratio (Sigmoidal_Ratio, 34, Break_Point, Smoothness_Rate, Assymptotic_Ratio, Ratio);
      for (i=0; i<I_Time; i++)
	Empirical_Data_Matrix[1][i] = Sigmoidal_Ratio[i] * Empirical_Data_Matrix[0][i]/2.0;
    }
    else {
      for (i=0; i<I_Time; i++)
	Empirical_Data_Matrix[1][i] = Ratio * Empirical_Data_Matrix[0][i]/2.0;
    }
      
    Writing_Standard_Data_Matrix_to_File(OBSERVED_DATA_FILE_3_ROWS[k],
					 Empirical_Data_Matrix,
					 No_of_OBSERVED_VARIABLES, I_Time,
					 0, Name_of_Rows,
					 0, Time_Vector);

    Writing_Standard_Data_Matrix_to_File(OBSERVED_DATA_FILE_2_ROWS[k],
					 Empirical_Data_Matrix,
					 2, I_Time,
					 0, Name_of_Rows,
					 0, Time_Vector);

    Ratio = Empirical_Data_Matrix[2][16]/Empirical_Data_Matrix[1][16];
    
    printf("Prevalence of the disease within sexual worker population: %g\n", Ratio);

    for (i=0; i<I_Time; i++)
      Empirical_Data_Matrix[2][i] = Ratio * Empirical_Data_Matrix[1][i];

    // Correction of the observation of prevalence in 2012:
    Empirical_Data_Matrix[2][12] = 0.01 * Percentage_Prevalence_SW_2012[k] * Empirical_Data_Matrix[1][12];

    Writing_Standard_Data_Matrix_to_File(OBSERVED_DATA_FILE_3_ROWS[k],
					 Empirical_Data_Matrix,
					 No_of_OBSERVED_VARIABLES, I_Time,
					 0, Name_of_Rows,
					 0, Time_Vector);

    x_0 = 0.01; x_1 = 1.00;
    for (i=0; i<I_Time; i++)
      // Empirical_Data_Matrix[2][i] = (x_0+(double)i*(x_1-x_0)/(double)(I_Time-1)) * Ratio * Empirical_Data_Matrix[1][i];
      Empirical_Data_Matrix[2][i] = Empirical_Data_Matrix[1][i] * Increasing_Exponential_Function (Ratio, 
												   x_0, i, I_Time-1);

    // Correctioin of the observation of prevalence in 2012:
    Empirical_Data_Matrix[2][12] = 0.01 * Percentage_Prevalence_SW_2012[k] * Empirical_Data_Matrix[1][12];

    OBSERVED_DATA_FILE_3_ROWS[k][0] = '\0';
    pF = strcat(OBSERVED_DATA_FILE_3_ROWS[k], "Observed_Data_File_");
    pF = strcat(OBSERVED_DATA_FILE_3_ROWS[k], City_Names[k]);
    if (SIGMOIDAL == 1) pF = strcat(OBSERVED_DATA_FILE_3_ROWS[k], "_1_Sigmoidal_Exponential.dat");
    else                pF = strcat(OBSERVED_DATA_FILE_3_ROWS[k], "_1_Exponential.dat");

    Writing_Standard_Data_Matrix_to_File(OBSERVED_DATA_FILE_3_ROWS[k],
					 Empirical_Data_Matrix,
					 No_of_OBSERVED_VARIABLES, I_Time,
					 0, Name_of_Rows,
					 0, Time_Vector);

    x_0 = 0.05; x_1 = 1.00;
    for (i=0; i<I_Time; i++)
      // Empirical_Data_Matrix[2][i] = (x_0+(double)i*(x_1-x_0)/(double)(I_Time-1)) * Ratio * Empirical_Data_Matrix[1][i];
      Empirical_Data_Matrix[2][i] = Empirical_Data_Matrix[1][i] * Increasing_Exponential_Function (Ratio, 
												   x_0, i, I_Time-1);
                                                                 
    // Correctioin of the observation of prevalence in 2012:
    Empirical_Data_Matrix[2][12] = 0.01 * Percentage_Prevalence_SW_2012[k] * Empirical_Data_Matrix[1][12];

    OBSERVED_DATA_FILE_3_ROWS[k][0] = '\0';
    pF = strcat(OBSERVED_DATA_FILE_3_ROWS[k], "Observed_Data_File_");
    pF = strcat(OBSERVED_DATA_FILE_3_ROWS[k], City_Names[k]);
    if (SIGMOIDAL == 1) pF = strcat(OBSERVED_DATA_FILE_3_ROWS[k], "_5_Sigmoidal_Exponential.dat");
    else                pF = strcat(OBSERVED_DATA_FILE_3_ROWS[k], "_5_Exponential.dat");

    Writing_Standard_Data_Matrix_to_File(OBSERVED_DATA_FILE_3_ROWS[k],
					 Empirical_Data_Matrix,
					 No_of_OBSERVED_VARIABLES, I_Time,
					 0, Name_of_Rows,
					 0, Time_Vector);

    x_0 = 0.25; x_1 = 1.00;
    for (i=0; i<I_Time; i++)
      // Empirical_Data_Matrix[2][i] = (x_0+(double)i*(x_1-x_0)/(double)(I_Time-1)) * Ratio * Empirical_Data_Matrix[1][i];
      Empirical_Data_Matrix[2][i] = Empirical_Data_Matrix[1][i] * Increasing_Exponential_Function (Ratio, 
												   x_0, i, I_Time-1);
      
    // Correctioin of the observation of prevalence in 2012:
    Empirical_Data_Matrix[2][12] = 0.01 * Percentage_Prevalence_SW_2012[k] * Empirical_Data_Matrix[1][12];

    OBSERVED_DATA_FILE_3_ROWS[k][0] = '\0';
    pF = strcat(OBSERVED_DATA_FILE_3_ROWS[k], "Observed_Data_File_");
    pF = strcat(OBSERVED_DATA_FILE_3_ROWS[k], City_Names[k]);
    if (SIGMOIDAL == 1) pF = strcat(OBSERVED_DATA_FILE_3_ROWS[k], "_25_Sigmoidal_Exponential.dat");
    else                pF = strcat(OBSERVED_DATA_FILE_3_ROWS[k], "_25_Exponential.dat");

    Writing_Standard_Data_Matrix_to_File(OBSERVED_DATA_FILE_3_ROWS[k],
					 Empirical_Data_Matrix,
					 No_of_OBSERVED_VARIABLES, I_Time,
					 0, Name_of_Rows,
					 0, Time_Vector);

    x_0 = 0.50; x_1 = 1.00;
    for (i=0; i<I_Time; i++)
      // Empirical_Data_Matrix[2][i] = (x_0+(double)i*(x_1-x_0)/(double)(I_Time-1)) * Ratio * Empirical_Data_Matrix[1][i];
      Empirical_Data_Matrix[2][i] = Empirical_Data_Matrix[1][i] * Increasing_Exponential_Function (Ratio, 
												   x_0, i, I_Time-1);
      
    // Correctioin of the observation of prevalence in 2012:
    Empirical_Data_Matrix[2][12] = 0.01 * Percentage_Prevalence_SW_2012[k] * Empirical_Data_Matrix[1][12];

    OBSERVED_DATA_FILE_3_ROWS[k][0] = '\0';
    pF = strcat(OBSERVED_DATA_FILE_3_ROWS[k], "Observed_Data_File_");
    pF = strcat(OBSERVED_DATA_FILE_3_ROWS[k], City_Names[k]);
    if (SIGMOIDAL == 1)  pF = strcat(OBSERVED_DATA_FILE_3_ROWS[k], "_50_Sigmoidal_Exponential.dat");
    else                 pF = strcat(OBSERVED_DATA_FILE_3_ROWS[k], "_50_Exponential.dat");

    Writing_Standard_Data_Matrix_to_File(OBSERVED_DATA_FILE_3_ROWS[k],
					 Empirical_Data_Matrix,
					 No_of_OBSERVED_VARIABLES, I_Time,
					 0, Name_of_Rows,
					 0, Time_Vector);

    Reading_Standard_Data_Matrix_from_File( TIME_DEPENDENT_FILE[k],
					    Time_Dependent_Parameter_Values,
					    &No_of_Rows, I_Time,
					    0, Name_of_Rows,
					    1, Year_Vector);

    Reading_Standard_Data_Matrix_from_File( TIME_DEPENDENT_EXTRAPOLATED[k],
					    Time_Extrapolated_Parameter_Values,
					    &No_of_Rows, I_Time_34,
					    0, Name_of_Rows,
					    1, Year_Vector);
    assert(No_of_Rows == 4);

    int No_of_INITIAL_YEARS = 15;

    for (i=0; i<No_of_INITIAL_YEARS; i++) {
      OBSERVED_DATA_FILE_3_ROWS[k][0] = '\0';
      pF = strcat(OBSERVED_DATA_FILE_3_ROWS[k], "Observed_Data_File_");
      pF = strcat(OBSERVED_DATA_FILE_3_ROWS[k], City_Names[k]);
      pF = strcat(OBSERVED_DATA_FILE_3_ROWS[k], "_");
      sprintf( Year, "%d", i+2000 );
      pF = strcat(OBSERVED_DATA_FILE_3_ROWS[k], Year);
      if (SIGMOIDAL == 1) pF = strcat(OBSERVED_DATA_FILE_3_ROWS[k], "_Sigmoidal_Exponential.dat");
      else                pF = strcat(OBSERVED_DATA_FILE_3_ROWS[k], "_Exponential.dat");

      for (j=i; j<I_Time; j++) {
        Year_Vector[j-i] = Time_Vector[j];
        Empirical_Short_Matrix[0][j-i] = Empirical_Data_Matrix[0][j];
        Empirical_Short_Matrix[1][j-i] = Empirical_Data_Matrix[1][j];
      }

      x_0 = 0.01; x_1 = 1.00;
      for (j=i; j<I_Time; j++)
         // Empirical_Short_Matrix[2][j-i] = (x_0+(double)(j-i)*(x_1-x_0)/(double)(I_Time-i-1)) * Ratio * Empirical_Short_Matrix[1][j-i];
         Empirical_Short_Matrix[2][j-i] = Empirical_Short_Matrix[1][j-i]* Increasing_Exponential_Function (Ratio,
													   x_0, j-i, I_Time-1-i);

      // Correctioin of the observation of prevalence in 2012:
      if (i <= 12)
      Empirical_Short_Matrix[2][12-i] = 0.01 * Percentage_Prevalence_SW_2012[k] * Empirical_Data_Matrix[1][12];

      Writing_Standard_Data_Matrix_to_File(OBSERVED_DATA_FILE_3_ROWS[k],
					   Empirical_Short_Matrix,
					   No_of_OBSERVED_VARIABLES, I_Time-i,
					   0, Name_of_Rows,
					   0, Year_Vector);

      for (j=i; j<I_Time; j++)
      for (n=0; n<4; n++)
      Time_Dependent_Shortened_Values[n][j-i] = Time_Dependent_Parameter_Values[n][j];

      TIME_DEPENDENT_FILE[k][0] = '\0';
      pF = strcat(TIME_DEPENDENT_FILE[k], "Time_Dependent_Parameters_Corrected_");
      pF = strcat(TIME_DEPENDENT_FILE[k], City_Names[k]);
      pF = strcat(TIME_DEPENDENT_FILE[k], "_");
      pF = strcat(TIME_DEPENDENT_FILE[k], Year);
      pF = strcat(TIME_DEPENDENT_FILE[k], ".dat");

      Writing_Standard_Data_Matrix_to_File( TIME_DEPENDENT_FILE[k],
					    Time_Dependent_Shortened_Values,
					    No_of_Rows, I_Time-i,
					    0, Name_of_Rows,
					    1, Year_Vector);

      for (j=i; j<I_Time_34; j++){
        Year_Vector[j-i] = Time_Vector_Extrapolated[j];

      for (n=0; n<4; n++)
      Time_Extrapolated_Shortened_Values[n][j-i] = Time_Extrapolated_Parameter_Values[n][j];
      }

      TIME_DEPENDENT_EXTRAPOLATED[k][0] = '\0';
      pF = strcat(TIME_DEPENDENT_EXTRAPOLATED[k], "Time_Dependent_Parameters_Extrapolated_Corrected_");
      pF = strcat(TIME_DEPENDENT_EXTRAPOLATED[k], City_Names[k]);
      pF = strcat(TIME_DEPENDENT_EXTRAPOLATED[k], "_");
      pF = strcat(TIME_DEPENDENT_EXTRAPOLATED[k], Year);
      pF = strcat(TIME_DEPENDENT_EXTRAPOLATED[k], ".dat");

      Writing_Standard_Data_Matrix_to_File( TIME_DEPENDENT_EXTRAPOLATED[k],
					    Time_Extrapolated_Shortened_Values,
					    No_of_Rows, I_Time_34-i,
					    0, Name_of_Rows,
					    1, Year_Vector);
    }
  }

  for (i=0; i<4; i++) {
    free(Time_Dependent_Parameter_Values[i]);
    free(Time_Dependent_Shortened_Values[i]);
    free(Time_Extrapolated_Parameter_Values[i]);
    free(Time_Extrapolated_Shortened_Values[i]);
  }
  free(Time_Dependent_Parameter_Values);
  free(Time_Dependent_Shortened_Values);
  free(Time_Extrapolated_Parameter_Values);
  free(Time_Extrapolated_Shortened_Values);

  for (i=0; i<No_of_OBSERVED_VARIABLES; i++)  {
    free(Empirical_Short_Matrix[i]);
    free(Empirical_Data_Matrix[i]);
  }
  free(Empirical_Data_Matrix); free(Empirical_Short_Matrix);

  for(k = 0; k<No_of_CITIES; k++) {
    free( OBSERVED_DATA_FILE_3_ROWS[k] );
    free(OBSERVED_DATA_FILE_2_ROWS[k] );
    free(OBSERVED_DATA_FILE[k] );
    free(TIME_DEPENDENT_FILE[k] );
    free(TIME_DEPENDENT_EXTRAPOLATED[k] );
  }
  free( OBSERVED_DATA_FILE_3_ROWS );
  free( OBSERVED_DATA_FILE_2_ROWS );
  free( OBSERVED_DATA_FILE );
  free( TIME_DEPENDENT_FILE );
  free( TIME_DEPENDENT_EXTRAPOLATED );

  free(Sigmoidal_Ratio);

  printf("\nEnd of progam\n");
  return (0);
}

double Increasing_Exponential_Function(double A, double x_0, int i, int i_Years)
{
  /* Input Arguments:

     . A, fraction of infected women (total sexual workers) at year 2016 (observed)
     . x_0, factor determining this fraction at year 2000 (x_0 * A)
     . i, year i, which corresponed to the 2000 + i year.

     Output Arguments:

     . Corresponding number of infected women (total sexual workers) at year i
     under the assumption of expontial increase:

     fI_XXSW(t) = x_0 * A * exp( k * (t-2000))

     Therefore, we need to solve for an exponential increase in infected cases
     starting at year 2000, from x_0 times the number observed in 2016. Therefore,
     we require:

	 f(0)  = x_0 * A                  = X_0;      //  0 corresponds to year 2000

	 f(16) = X_0 * exp( k * i_Years)  = A;        // 16 corresponds to year 2016

     which allows to find the rate 'k':

	                         k = 1/log(A/X_0)/i_Years;
     The solution is:
	                         k = -log(x_0)/i_Years;
  */
  double X_0, k, Value;

  k  = -log(x_0)/(double)i_Years;

  X_0 = A * x_0;

  Value = X_0 * exp( (double)i * k);

  return (Value);
}

void Defining_Sigmoidal_Ratio(double * Ratio, const int N, const double T_0, const double L_0, double A_0, const double Ratio_2016)
{
  /* Input Arguments:

     . T_0, Break Point
     . L_0, Smoothness rate
     . A_0, Assymptotic value.
     . N, length of Ratio vector.
     . Ratio_2012, ratio value constraining the sigmoidal curve. We require:

                           Ratio[16] = Ratio_2016;

     Notice that we decide to adjust A_0, the assymtotic value, to match this constraint, this is,
     A_0 is not a free parameter any more.

     Output Arguments:

     . Ratio[i] is the fraction of Sex Workers with respect total female population at year
     2000 + i under the assumption of a sigmoidal increase with parameters T_0, L_0, A_0

     I_XXSW(t) = Ratio[t-2000] * XXSW(t);

     with Ratio[t-2000] = Ratio_2016 for t = 2016.
  */
  int i;
  double i_0;

  i_0 = (int)(T_0 - 2000.0);

  A_0 = Ratio_2016 * (1.0 + exp(-L_0 *(16.0-i_0)));

  for (i = 0; i<N; i++) Ratio[i] = A_0 /(1.0 + exp(-L_0 *((double)i-i_0)));
}
