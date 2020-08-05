#include <MODEL.h>

extern gsl_rng * r; /* Global generator defined in main.c */

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
					      Parameter_Table * Table)
{
  /* Input:
     . Table
     . TYPE_1_PARAMETERS, No of parameters to store in Data_Matrix (mo of rows)
     . No_of_TIMES, No of times for each parameter value (no of columns)

     Output:
     . Data_Matrix, Matrix containing the value of each parameter for each time:
     . Age_Death_Rates_Female, age specific mortality rates between 1983 and 2016 (matrix)
     . Year_1983_2016: {1983, ..., 2016}                                          (vector)
     . Urban_Population_Vector, city population for each city and year             (matrix)
     . Fecundity_Vector, total fecundity between 1983 and 2016.                   (vector)
  */
  int i, j, n; 
  int YEARS_BEFORE = 17;
  int YEARS_AFTER  = 17; 
  int No_of_Columns_Max = 200;
  int No_of_Columns = 34;
  int No_of_Rows_Max = 50;
  int No_of_Rows;
  int N_Dummy;
  double Sum;

  double c0, c1, cov00, cov01, cov11, chisq;
  double * x_Data;     double * y_Data;
  double * x_Data_0;   double * y_Data_0; 
  double * x_Data_Fit; double * y_Data_Fit;
  double * xf;         double * yf;
  double yf_err;       double y_Fit; 
  
  // char ** Names = (char **)calloc(No_of_Rows_Max, sizeof(char *) )
  double * Year_Vector = (double *)calloc(No_of_Columns_Max, sizeof(double) );
  double * Years = (double *)calloc(No_of_Columns_Max, sizeof(double) );
  

  for(i=0; i<No_of_Columns/2 + YEARS_BEFORE + YEARS_AFTER; i++) {
    Year_Vector[i] = 1983.0 + (double)i;
    printf("Year: %g\t", Year_Vector[i]);
  }
  printf("\n");
  
  /* --------------------    DEATH RATES  --------------------------------------------- */
  double ** Death_Rates = (double **)calloc(2, sizeof(double *) );
  Death_Rates[0] = (double *)calloc(No_of_Columns, sizeof(double) );
  Death_Rates[1] = (double *)calloc(No_of_Columns, sizeof(double) );

  Reading_Standard_Data_Matrix_from_File("life_expectancy_at_15-19_2016-2000.dat", Death_Rates,
					 &N_Dummy, No_of_Columns,
					 0, Names,
					 1, Years);

  double * Death_Rates_F = (double *)calloc(No_of_Columns/2+YEARS_BEFORE+YEARS_AFTER, sizeof(double) );
  double * Death_Rates_M = (double *)calloc(No_of_Columns/2+YEARS_BEFORE+YEARS_AFTER, sizeof(double) );
  double * Death_Rates_F_SHORT = (double *)calloc(No_of_Columns/2, sizeof(double) );
  double * Death_Rates_M_SHORT = (double *)calloc(No_of_Columns/2, sizeof(double) );
  double * Year_Vector_SHORT   = (double *)calloc(No_of_Columns/2, sizeof(double) );
  for(i=0; i<No_of_Columns/2; i++){
    Death_Rates_F[i+YEARS_BEFORE] = 1.0/Death_Rates[0][No_of_Columns-1-2*i];
    Death_Rates_M[i+YEARS_BEFORE] = 1.0/Death_Rates[0][No_of_Columns-2-2*i];
    Death_Rates_F_SHORT[i]        = 1.0/Death_Rates[0][No_of_Columns-1-2*i];
    Death_Rates_M_SHORT[i]        = 1.0/Death_Rates[0][No_of_Columns-2-2*i];
    Year_Vector_SHORT[i]          = Years[No_of_Columns-2-2*i];
    Year_Vector[i+YEARS_BEFORE]   = Years[No_of_Columns-2-2*i];
    printf("Year: %g\t Death Rate (F): %g\t Death Rate (M); %g\n",
	   Year_Vector[i+YEARS_BEFORE],
	   Death_Rates_F[i+YEARS_BEFORE], Death_Rates_M[i+YEARS_BEFORE]);
    
    Table->TDC->Time_Vector[i] = Year_Vector[i+YEARS_BEFORE];
  }

  /* Extrapolating Female and Male Death Rates for YEARS_AFTER (linearly)               */
  x_Data = (double *)calloc(No_of_Columns/2, sizeof(double));
  y_Data = (double *)calloc(No_of_Columns/2, sizeof(double));
  for(j = YEARS_BEFORE; j < No_of_Columns/2 + YEARS_BEFORE; j++) {
    x_Data[j-YEARS_BEFORE] = Year_Vector_SHORT[j-YEARS_BEFORE];
    y_Data[j-YEARS_BEFORE] = Death_Rates_F_SHORT[j-YEARS_BEFORE];
  }
  gsl_fit_linear(x_Data, 1, y_Data, 1, No_of_Columns/2,
		 &c0, &c1, &cov00, &cov01, &cov11, &chisq);

  n = No_of_Columns/2 + YEARS_BEFORE + YEARS_AFTER;

  x_Data_Fit = (double *)calloc(n , sizeof(double));
  y_Data_Fit = (double *)calloc(n , sizeof(double));
  for(j = 0; j < n ; j++) {
    x_Data_Fit[j] = Year_Vector[j];
    gsl_fit_linear_est (x_Data_Fit[j], c0, c1, cov00, cov01, cov11,
			&y_Fit, &yf_err);
    y_Data_Fit[j] = y_Fit + (gsl_rng_uniform(r)-1.0) * yf_err; 
  }
  printf("\n");
  for(j = 0; j < n; j++) {
    x_Data_Fit[j] = Year_Vector[j];
    
    if(j < YEARS_BEFORE || j >= (YEARS_BEFORE + No_of_Columns/2) ) 
      Death_Rates_F[j] = y_Data_Fit[j];
   
    printf("Delta_F[%g]=%g  ", Year_Vector[j], Death_Rates_F[j]);
  }
  free(x_Data_Fit); free(y_Data_Fit);
  free(x_Data); free(y_Data);

  x_Data = (double *)calloc(No_of_Columns/2, sizeof(double));
  y_Data = (double *)calloc(No_of_Columns/2, sizeof(double));
  for(j = YEARS_BEFORE; j < No_of_Columns/2 + YEARS_BEFORE; j++) {
    x_Data[j-YEARS_BEFORE] = Year_Vector_SHORT[j-YEARS_BEFORE];
    y_Data[j-YEARS_BEFORE] = Death_Rates_M_SHORT[j-YEARS_BEFORE];
  }
  gsl_fit_linear(x_Data, 1, y_Data, 1, No_of_Columns/2,
		 &c0, &c1, &cov00, &cov01, &cov11, &chisq);

  n = No_of_Columns/2 + YEARS_BEFORE + YEARS_AFTER;

  x_Data_Fit = (double *)calloc(n , sizeof(double));
  y_Data_Fit = (double *)calloc(n , sizeof(double));
  for(j = 0; j < n ; j++) {
    x_Data_Fit[j] = Year_Vector[j];
    gsl_fit_linear_est (x_Data_Fit[j], c0, c1, cov00, cov01, cov11,
			&y_Fit, &yf_err);
    y_Data_Fit[j] = y_Fit + (gsl_rng_uniform(r)-1.0) * yf_err; 
  }
  printf("\n");
  for(j = 0; j < n; j++) {
    x_Data_Fit[j] = Year_Vector[j];
    
    if(j < YEARS_BEFORE || j >= (YEARS_BEFORE + No_of_Columns/2) ) 
      Death_Rates_M[j] = y_Data_Fit[j];
   
    printf("Delta_M[%g]=%g  ", Year_Vector[j], Death_Rates_M[j]);
  }
  free(x_Data_Fit); free(y_Data_Fit);
  free(x_Data); free(y_Data);

  for(j = 0; j < YEARS_BEFORE+No_of_Columns/2 ; j++) {
    Data_Matrix[2][j]          = Death_Rates_F[j+YEARS_BEFORE];
    Data_Matrix[3][j]          = Death_Rates_M[j+YEARS_BEFORE];
  }
  /* ---------------------------------------------------------------------------------- */
  
  /* -------------------- AGE SPECIFIC DEATH RATES ------------------------------------ */
  double ** Age_Death_Rates = (double **)calloc(No_of_Rows_Max, sizeof(double *) );
  // double ** Age_Death_Rates_Female = (double **)calloc(No_of_Rows_Max, sizeof(double *) );
  // double ** Age_Death_Rates_Male   = (double **)calloc(No_of_Rows_Max, sizeof(double *) );
  for(i=0; i<No_of_Rows_Max; i++) {
    Age_Death_Rates[i] = (double *)calloc(No_of_Columns_Max, sizeof(double) );
    // Age_Death_Rates_Female[i] = (double *)calloc(No_of_Columns_Max, sizeof(double) );
    // Age_Death_Rates_Male[i] = (double *)calloc(No_of_Columns_Max, sizeof(double) );
    // Names[i] = (char *)calloc(50, sizeof(char) );
  }
  
  Reading_Standard_Data_Matrix_from_File("m_a.dat", Age_Death_Rates,
					 &No_of_Rows, No_of_Columns,
					 0, Names,
					 0, Years);
  for(i=0; i<No_of_Rows; i++) {
    for(j=0; j<No_of_Columns/2; j++) {
      Age_Death_Rates_Female[i][j+YEARS_BEFORE] = Age_Death_Rates[i][No_of_Columns-1-2*j];
      Age_Death_Rates_Male[i][j+YEARS_BEFORE]   = Age_Death_Rates[i][No_of_Columns-2-2*j];
      Year_Vector[j+YEARS_BEFORE]               = Years[No_of_Columns-2-2*j];
      printf("m_M[%d][%g]=%g\t\t m_F[%d][%g]=%g\n",
	     i, Year_Vector[j+YEARS_BEFORE], Age_Death_Rates_Male[i][j+YEARS_BEFORE],
	     i, Year_Vector[j+YEARS_BEFORE], Age_Death_Rates_Female[i][j+YEARS_BEFORE]);
    }
    printf("\n\n"); //getchar();
  }
  /* ---------------------------------------------------------------------------------- */

  /* ----------------- CITY POPULATIONS YEAR 2013 ------------------------------------- */
  double ** City_Population  = (double **)calloc(No_of_Rows_Max, sizeof(double *) );
  for(i=0; i<No_of_Rows_Max; i++) 
    City_Population[i] = (double *)calloc(1, sizeof(double) );
  double * Years_C = (double *)calloc(1, sizeof(double) );
  int No_of_CITIES;

  Reading_Standard_Data_Matrix_from_File("Madagascar_City_Populations.dat", City_Population,
					 &No_of_CITIES, 1,
					 1, Names,
					 1, Years_C);

  double * City_Population_2013 = (double *)calloc(No_of_CITIES, sizeof(double) );
  double  * City_Factor_2013 = (double *)calloc(No_of_Rows_Max, sizeof(double) );
  Sum = 0; 
  for(i=0; i<No_of_CITIES; i++){
    City_Population_2013[i] = City_Population[i][0];
    Sum += City_Population_2013[i]; 
    printf(" Year: %g\t City: %s\t Population: %g\n",
	   Years_C[0], Names[i], City_Population_2013[i]);
  }
  double Urban_Population_11_Cities_2013; 
  Urban_Population_11_Cities_2013 = Sum; 
  for(i=0; i<No_of_CITIES; i++) City_Factor_2013[i] = City_Population_2013[i]/Sum;
  /* ---------------------------------------------------------------------------------- */

  /* -------- TEMPORAL EVOLUTION Of POPULATIONS AND FECUNDITIES (1955-2018) ----------- */
  double ** Pop_Fecundity = (double **)calloc(No_of_Rows_Max, sizeof(double *) );
  for(i=0; i<No_of_Rows_Max; i++)
    Pop_Fecundity[i] = (double *)calloc(4, sizeof(double) );
  int No_of_Years_F = 16;
  double * Years_F;
  
  Reading_Standard_Data_Matrix_from_File("Madagascar_Population_Total_Fecundity.dat", 
					 Pop_Fecundity, &No_of_Years_F, 4, 
					 0, Names,
					 0, Years_F);
  
  Writing_Standard_Data_Matrix(Pop_Fecundity, No_of_Years_F, 4, 
			       0, Names,
			       0, Years_F); 
  
  Years_F = (double *)calloc(No_of_Years_F, sizeof(double) );
  double * Fecundity_F = (double *)calloc(No_of_Years_F, sizeof(double) );
  double * Population_F = (double *)calloc(No_of_Years_F, sizeof(double) );
  double * Urban_Population_F = (double *)calloc(No_of_Years_F, sizeof(double) );
  double ** Urban_Population_Cities_F = (double **)calloc(No_of_CITIES, sizeof(double *) );
  for(i=0; i<No_of_CITIES; i++)
    Urban_Population_Cities_F[i] = (double *)calloc(No_of_Years_F, sizeof(double) );
  for(i=0; i<No_of_Years_F; i++) {
    Years_F[i]            = Pop_Fecundity[No_of_Years_F-i-1][0];
    Population_F[i]       = Pop_Fecundity[No_of_Years_F-i-1][1];
    Fecundity_F[i]        = Pop_Fecundity[No_of_Years_F-i-1][2];
    Urban_Population_F[i] = Pop_Fecundity[No_of_Years_F-i-1][3];
    printf("Year: %g\t Total Urban Population: %g\n", Years_F[i], Urban_Population_F[i]);
  }
	
  for(i=0; i<No_of_CITIES; i++) {
    for(j=0; j<No_of_Years_F; j++) 
      Urban_Population_Cities_F[i][j] = Urban_Population_F[j] * City_Factor_2013[i];  
  }
  /* ---------------------------------------------------------------------------------- */
  
  /* B E G I N : Drawing the Function */
  /* B E G I N : Creating nice title with parameter values               */
  /* double Parameter_Value;                                             */
  char * pTitle;
  char * pValue = (char *)calloc(10, sizeof(char) );
  char * Title_Parameters = (char *)calloc(500, sizeof(char) );
  Title_Parameters[0]='\0';
  /* for(i=0; i<MODEL_PARAMETERS_MAXIMUM; i++) {                         */
  /*   pTitle = strcat(Title_Parameters, Table->Symbol_Parameters[i]);   */
  /*   pTitle = strcat(Title_Parameters, " = ");                         */
  /*   Parameter_Value  = AssignStructValue_to_VectorEntry ( i, Table ); */
  /*   pValue[0]='\0'; sprintf(pValue, "%4.3f", Parameter_Value);        */
  /*   pTitle = strcat(Title_Parameters, pValue);                        */
  /*   pTitle = strcat(Title_Parameters, "  ");                          */
  /* }                                                                   */
  /*     E N D : ------------------------------------------------------- */
  int SAME = 0;
  Table->CPG->color_Index = 3; //* 3: green *//
  Table->CPG->type_of_Line = 1;
  Table->CPG->type_of_Width = 7;
  Table->CPG->type_of_Symbol = 1;

  Table->CPG->CPG_SCALE_X   = 1;        Table->CPG->CPG_SCALE_Y   =  1;
  Table->CPG->CPG_RANGE_X_0 = 1983.0;   Table->CPG->CPG_RANGE_Y_0 =  0.0;
  Table->CPG->CPG_RANGE_X_1 = 2033.0;   Table->CPG->CPG_RANGE_Y_1 =  0.1;
  CPGPLOT___X_Y___P_L_O_T_T_I_N_G___S_A_M_E___P_L_O_T ( Table->CPG, SAME,
  							No_of_Columns/2 + YEARS_BEFORE + YEARS_AFTER,
  							Year_Vector, Death_Rates_F, 
  							"Year",
  							"Total Death Rate (F)",
  							Title_Parameters,
  							Table->CPG->CPG_SCALE_X,
  							Table->CPG->CPG_SCALE_Y );
  Table->CPG->color_Index = 5; //* 3: green *//
  Table->CPG->type_of_Symbol = 24;
  CPGPLOT___X_Y___S_C_A_T_T_E_R_E_D___S_A_M_E___P_L_O_T ( Table->CPG, 1,
							  No_of_Columns,
							  Year_Vector_SHORT, Death_Rates_F_SHORT, 
							  "Year",
							  "Death Rate (F)",
							  Title_Parameters,
							  Table->CPG->CPG_SCALE_X,
							  Table->CPG->CPG_SCALE_Y );
  getchar();
  Table->CPG->color_Index = 3; //* 3: green *//
  Table->CPG->type_of_Line = 1;
  Table->CPG->type_of_Width = 7;
  Table->CPG->type_of_Symbol = 1;
  
  Table->CPG->CPG_SCALE_X   = 1;        Table->CPG->CPG_SCALE_Y   =  1;
  Table->CPG->CPG_RANGE_X_0 = 1955.0;   Table->CPG->CPG_RANGE_Y_0 =  0.0;
  Table->CPG->CPG_RANGE_X_1 = 2033.0;   Table->CPG->CPG_RANGE_Y_1 =  1.0E+07;
  CPGPLOT___X_Y___P_L_O_T_T_I_N_G___S_A_M_E___P_L_O_T ( Table->CPG, SAME,
  							No_of_Years_F, 
  							Years_F, Urban_Population_F, 
  							"Year",
  							"Urban Population",
  							Title_Parameters,
  							Table->CPG->CPG_SCALE_X,
  							Table->CPG->CPG_SCALE_Y );
  getchar();
  Table->CPG->CPG_SCALE_X   = 1;        Table->CPG->CPG_SCALE_Y   =  1;
  Table->CPG->CPG_RANGE_X_0 = 1955.0;   Table->CPG->CPG_RANGE_Y_0 =  0.0;
  Table->CPG->CPG_RANGE_X_1 = 2033.0;   Table->CPG->CPG_RANGE_Y_1 =  8.0;
  CPGPLOT___X_Y___P_L_O_T_T_I_N_G___S_A_M_E___P_L_O_T ( Table->CPG, SAME,
							No_of_Years_F, 
  							Years_F, Fecundity_F,
  							"Year",
  							"Total Fertility Rate",
  							Title_Parameters,
  							Table->CPG->CPG_SCALE_X,
  							Table->CPG->CPG_SCALE_Y );
  /* In order to estimate to estimate the fraction of 
     the total urban population living in the 11 selected cities in year 
     2013, we need to interpolate Urban Total Population for Year 2013  
  */
  double Urban_Factor_11_Cities; 
  double Total_Urban_Population_2013;
  gsl_interp_accel * acc = gsl_interp_accel_alloc ();
  gsl_spline * spline    = gsl_spline_alloc (gsl_interp_cspline, No_of_Years_F);
  gsl_spline_init (spline, Years_F, Urban_Population_F, No_of_Years_F);
  
  Total_Urban_Population_2013 = gsl_spline_eval(spline, Year_Vector[30], acc); 
  Urban_Factor_11_Cities = Urban_Population_11_Cities_2013/Total_Urban_Population_2013;
  
  printf("Fraction of urban population in the 11 cities (2013): %g\n", Urban_Factor_11_Cities); 
  gsl_spline_free (spline);
  gsl_interp_accel_free (acc);
  
  /* Retropolating, Interpolating, and Extrapoplation Total Fecundities for Year_Vector Values */
  // double * Fecundity_Vector = (double *)calloc(No_of_Columns/2+YEARS_BEFORE, sizeof(double) );
  acc     = gsl_interp_accel_alloc ();
  spline  = gsl_spline_alloc (gsl_interp_cspline, No_of_Years_F);
  
  gsl_spline_init (spline, Years_F, Fecundity_F, No_of_Years_F);
  int j_First_Non_Estimated_Fecundity;
  j_First_Non_Estimated_Fecundity = 0; 
  for (j = 0; j < No_of_Columns/2+YEARS_BEFORE+YEARS_AFTER; j++) {
    if(Year_Vector[j] < Years_F[No_of_Years_F-1]) {
      Fecundity_Vector[j] =  gsl_spline_eval (spline, Year_Vector[j], acc);
      j_First_Non_Estimated_Fecundity = j+1; 
    } 
  }
  gsl_spline_free (spline);
  gsl_interp_accel_free (acc);

  x_Data = (double *)calloc(5, sizeof(double));
  y_Data = (double *)calloc(5, sizeof(double));
  for(j =  (j_First_Non_Estimated_Fecundity -5); j < j_First_Non_Estimated_Fecundity; j++) {
      x_Data[j-(j_First_Non_Estimated_Fecundity -5)] = Year_Vector[j];
      y_Data[j-(j_First_Non_Estimated_Fecundity -5)] = Fecundity_Vector[j];
  }
  gsl_fit_linear(x_Data, 1, y_Data, 1, 5,
		 &c0, &c1, &cov00, &cov01, &cov11, &chisq);

  n = No_of_Columns/2+YEARS_BEFORE+YEARS_AFTER; 
  for(j = (j_First_Non_Estimated_Fecundity -5); j < n ; j++) {
    gsl_fit_linear_est (Year_Vector[j], c0, c1, cov00, cov01, cov11,
			&y_Fit, &yf_err);
    
    Fecundity_Vector[j] = y_Fit + (gsl_rng_uniform(r)-1.0) * yf_err; 
  }
  
  for (j = 0; j < n; j++) 
    printf ("Fecundity[%g]  = %g\n", Year_Vector[j], Fecundity_Vector[j]);
  
  Table->CPG->color_Index = 2; //* 2: red *//
  Table->CPG->type_of_Symbol = 4;
  CPGPLOT___X_Y___P_L_O_T_T_I_N_G___S_A_M_E___P_L_O_T ( Table->CPG, 1,
							No_of_Columns/2+YEARS_BEFORE+YEARS_AFTER,
  							Year_Vector, Fecundity_Vector,
  							"Year",
  							"Total Fertility Rate",
  							Title_Parameters,
  							Table->CPG->CPG_SCALE_X,
  							Table->CPG->CPG_SCALE_Y );
  free(x_Data); free(y_Data); 
  getchar();

  // double ** Urban_Population_Vector = (double **)calloc(No_of_CITIES, sizeof(double *) );
  // for(i=0; i<No_of_CITIES; i++)
  // Urban_Population_Vector[i] = (double *)calloc(No_of_Columns/2+YEARS_BEFORE, sizeof(double) );

  for(i=0; i<No_of_CITIES; i++) {
    
    /* Interpolating City Population for Year_Vector values */
    int j_First_Non_Estimated_Population; 
    gsl_interp_accel * acc = gsl_interp_accel_alloc ();
    gsl_spline * spline    = gsl_spline_alloc (gsl_interp_cspline, No_of_Years_F);
    gsl_spline_init (spline, Years_F, Urban_Population_Cities_F[i], No_of_Years_F);
   
    for(j=0; j<No_of_Years_F; j++) 
      Urban_Population_Cities_F[i][j] = Urban_Factor_11_Cities * Urban_Population_F[j] * City_Factor_2013[i];  
    
    for (j = 0; j < No_of_Columns/2+YEARS_BEFORE+YEARS_AFTER; j++) {
      if(Year_Vector[j] < Years_F[No_of_Years_F-1]) {
        Urban_Population_Vector[i][j] =  Urban_Factor_11_Cities * gsl_spline_eval (spline, Year_Vector[j], acc);
	j_First_Non_Estimated_Population = j+1;
      }
    }
    gsl_spline_free (spline);
    gsl_interp_accel_free (acc);

    x_Data = (double *)calloc(No_of_Columns/2, sizeof(double));
    y_Data = (double *)calloc(No_of_Columns/2, sizeof(double));
    for(j = (j_First_Non_Estimated_Population -5); j < j_First_Non_Estimated_Population; j++) {
      x_Data[j-(j_First_Non_Estimated_Population -5)] = Year_Vector[j];
      y_Data[j-(j_First_Non_Estimated_Population -5)] = Urban_Population_Vector[i][j];
    }
    gsl_fit_linear(x_Data, 1, y_Data, 1, 5,
		   &c0, &c1, &cov00, &cov01, &cov11, &chisq);
    
    n = No_of_Columns/2 + YEARS_BEFORE + YEARS_AFTER; 
    for(j = j_First_Non_Estimated_Population; j < n ; j++) {
      
      gsl_fit_linear_est (Year_Vector[j], c0, c1, cov00, cov01, cov11,
			  &y_Fit, &yf_err);
      
      Urban_Population_Vector[i][j] = y_Fit + (gsl_rng_uniform(r)-1.0) * yf_err;
    }
    free(x_Data); free(y_Data); 

    for(j=0; j<n; j++)
      printf ("Estimated: Urban_Population[%s][%g]  = %g  [2013: %g]\n",
	      Names[i], Year_Vector[j], Urban_Population_Vector[i][j], City_Population_2013[i]);
    
    printf("City (Data): %s\t", Names[i]); 
    for(j=0; j<No_of_Years_F; j++) {
      printf("Population[%g] = %g  ", Years_F[j], Urban_Population_Cities_F[i][j]);
    }
    printf("\n\n");

    SAME = 0;
    Table->CPG->color_Index = 3; //* 3: green *//
    Table->CPG->type_of_Line = 1;
    Table->CPG->type_of_Width = 7;
    Table->CPG->type_of_Symbol = 1;

    Table->CPG->CPG_SCALE_X   = 1;            Table->CPG->CPG_SCALE_Y   =  1;
    Table->CPG->CPG_RANGE_X_0 = Years_F[0];   Table->CPG->CPG_RANGE_Y_0 =  0.0;
    Table->CPG->CPG_RANGE_X_1 = 2033.0;       Table->CPG->CPG_RANGE_Y_1 =  1.0E+07;
    CPGPLOT___X_Y___P_L_O_T_T_I_N_G___S_A_M_E___P_L_O_T ( Table->CPG, SAME,
							  No_of_Years_F, 
							  Years_F, Urban_Population_Cities_F[i],
							  "Year",
							  Names[i],
							  Title_Parameters,
							  Table->CPG->CPG_SCALE_X,
							  Table->CPG->CPG_SCALE_Y );

    Table->CPG->color_Index = 2; //* 2: red *//
    Table->CPG->type_of_Symbol = 4;
    CPGPLOT___X_Y___S_C_A_T_T_E_R_E_D___S_A_M_E___P_L_O_T ( Table->CPG, 1,
							    No_of_Columns/2+YEARS_BEFORE+YEARS_AFTER,
							    Year_Vector, Urban_Population_Vector[i],
							    "Year",
							    Names[i],
							    Title_Parameters,
							    Table->CPG->CPG_SCALE_X,
							    Table->CPG->CPG_SCALE_Y );
    Table->CPG->color_Index = 9; //* 2: red *//
    Table->CPG->type_of_Symbol = 26;
    CPGPLOT___X_Y___S_C_A_T_T_E_R_E_D___n_P_O_I_N_T_S ( Table->CPG, 1,  
							&Year_Vector[30], &City_Population_2013[i] );
    printf("City (Year: %g) %s\t Population Estimated: %g\t Population: %g", 
            Year_Vector[30], Names[i], Urban_Population_Vector[i][30], City_Population_2013[i]);   
    
    getchar();
  }
  
  int k0, k1;
  char * age_0 = (char *)calloc(10, sizeof(char) ); 
  char * age_1 = (char *)calloc(10, sizeof(char) );   
  
  /* B E G I N : Dealing with age-specific mortalities (MALES) */
  Table->CPG->color_Index = 3; //* 3: green *//
  Table->CPG->type_of_Line = 1;
  Table->CPG->type_of_Width = 7;
  Table->CPG->type_of_Symbol = 5;
  
  for(i=0; i<No_of_Rows; i++) {
    SAME = 0;
    Table->CPG->type_of_Symbol = 3;
    Table->CPG->color_Index    = 3; //* 3: green */

    Table->CPG->CPG_SCALE_X   = 1;                 Table->CPG->CPG_SCALE_Y   =  1;
    Table->CPG->CPG_RANGE_X_0 = Year_Vector[0];    Table->CPG->CPG_RANGE_Y_0 =  0.0;
    Table->CPG->CPG_RANGE_X_1 = 2033.0;            Table->CPG->CPG_RANGE_Y_1 =  0.1;
    
    Title_Parameters[0]='\0';
    if (i == 0) pTitle = strcat(Title_Parameters, "Age group (<1 years)");
    if (i == 1) pTitle = strcat(Title_Parameters, "Age group (1-4 years)");
    if (i > 1) { 
      k0 = (i-1)*5;
      k1 = i*5-1;
      sprintf( age_0, "%d", k0);
      sprintf( age_1, "%d", k1);
      pTitle = strcat(Title_Parameters, "Age group (");
      pTitle = strcat(Title_Parameters, age_0);
      pTitle = strcat(Title_Parameters, "-");
      pTitle = strcat(Title_Parameters, age_1);
      pTitle = strcat(Title_Parameters, " years)");
    }
    CPGPLOT___X_Y___S_C_A_T_T_E_R_E_D___S_A_M_E___P_L_O_T ( Table->CPG, SAME,
							    No_of_Columns/2 + YEARS_BEFORE + YEARS_AFTER,
							    Year_Vector, Age_Death_Rates_Male[i], 
							    "Year",
							    "Age Specific Male Mortality Rate",
							    Title_Parameters,
							    Table->CPG->CPG_SCALE_X,
							    Table->CPG->CPG_SCALE_Y );
    SAME = 1; 
    int j_Negative_Value;
    x_Data_0 = (double *)calloc(No_of_Columns/2, sizeof(double));
    y_Data_0 = (double *)calloc(No_of_Columns/2, sizeof(double));
    x_Data = (double *)calloc(5, sizeof(double));
    y_Data = (double *)calloc(5, sizeof(double));
    for(j = YEARS_BEFORE; j < No_of_Columns/2 + YEARS_BEFORE; j++) {
      x_Data_0[j-YEARS_BEFORE] = Year_Vector[j];
      y_Data_0[j-YEARS_BEFORE] = Age_Death_Rates_Male[i][j];
    }
    gsl_fit_linear(x_Data_0, 1, y_Data_0, 1, No_of_Columns/2,
		   &c0, &c1, &cov00, &cov01, &cov11, &chisq);
    
    n = No_of_Columns/2 + YEARS_BEFORE + YEARS_AFTER;

    x_Data_Fit = (double *)calloc(n , sizeof(double));
    y_Data_Fit = (double *)calloc(n , sizeof(double));
   
    j_Negative_Value = 0; 
    for(j = 0; j < n ; j++) {
      x_Data_Fit[j] = Year_Vector[j];
      gsl_fit_linear_est (x_Data_Fit[j], c0, c1, cov00, cov01, cov11,
			  &y_Fit, &yf_err);
      
      y_Data_Fit[j] = y_Fit + (gsl_rng_uniform(r)-1.0) * yf_err;
      
      if( y_Data_Fit[j] < 0.0001 ) j_Negative_Value = j; 
    }

    if(j_Negative_Value > 0) {
      for(j =  (No_of_Columns/2 +YEARS_BEFORE -5); j < (No_of_Columns/2 + YEARS_BEFORE); j++) {
	x_Data[j-(No_of_Columns/2 +YEARS_BEFORE -5)] = Year_Vector[j];
	y_Data[j-(No_of_Columns/2 +YEARS_BEFORE -5)] = Age_Death_Rates_Male[i][j];
      }
      gsl_fit_linear(x_Data, 1, y_Data, 1, 5,
		     &c0, &c1, &cov00, &cov01, &cov11, &chisq);
      
      for(j = (No_of_Columns/2 +YEARS_BEFORE -5); j < n ; j++) {
	x_Data_Fit[j] = Year_Vector[j];
	gsl_fit_linear_est (x_Data_Fit[j], c0, c1, cov00, cov01, cov11,
			    &y_Fit, &yf_err);
	
	y_Data_Fit[j] = y_Fit + (gsl_rng_uniform(r)-1.0) * yf_err;

	if( y_Data_Fit[j] < 0.0001 ) 
	  y_Data_Fit[j] = 0.0001; + 0.0001 * gsl_rng_uniform(r); 
      }
    }
    printf("\n");

    Table->CPG->color_Index = 2; //* 2: red *//
    Table->CPG->type_of_Symbol = 4;
    CPGPLOT___X_Y___P_L_O_T_T_I_N_G___S_A_M_E___P_L_O_T ( Table->CPG, SAME,
							  n, 
							  x_Data_Fit, y_Data_Fit, 
							  "Year",
							  "Age Specific Mortality Rates",
							  Title_Parameters,
							  Table->CPG->CPG_SCALE_X,
							  Table->CPG->CPG_SCALE_Y );
    getchar();
    
    printf("%d: %s: ", i, Title_Parameters); 
    for(j = 0; j < n; j++) {
      x_Data_Fit[j] = Year_Vector[j];

      if(j < YEARS_BEFORE || j >= (YEARS_BEFORE + No_of_Columns/2) ) {
	Age_Death_Rates_Male[i][j] = y_Data_Fit[j];
	assert(y_Data_Fit[j] > 0.0); 
      }

      printf("m_M[%d][%g]=%g  ",
	     i, Year_Vector[j], Age_Death_Rates_Male[i][j]);
    }
    
    free(x_Data_Fit); free(y_Data_Fit);
    free(x_Data_0); free(y_Data_0); 
    free(x_Data); free(y_Data);
    getchar();
  }
  /* E N D : Drawing the Function (MALES) */
  
  /* B E G I N : Dealing with age-specific mortalities (FEMALES) */
  Table->CPG->color_Index = 3; //* 3: green *//
  Table->CPG->type_of_Line = 1;
  Table->CPG->type_of_Width = 7;
  Table->CPG->type_of_Symbol = 5;

  for(i=0; i<No_of_Rows; i++) {
    SAME = 0;
    Table->CPG->type_of_Symbol = 3;
    Table->CPG->color_Index    = 3; //* 3: green */

    Table->CPG->CPG_SCALE_X   = 1;                 Table->CPG->CPG_SCALE_Y   =  1;
    Table->CPG->CPG_RANGE_X_0 = Year_Vector[0];    Table->CPG->CPG_RANGE_Y_0 =  0.0;
    Table->CPG->CPG_RANGE_X_1 = 2033.0;            Table->CPG->CPG_RANGE_Y_1 =  0.1;
    Title_Parameters[0]='\0';
    if (i == 0) pTitle = strcat(Title_Parameters, "Age group (<1 years)");
    if (i == 1) pTitle = strcat(Title_Parameters, "Age group (1-4 years)");
    if (i > 1) { 
      k0 = (i-1)*5;
      k1 = i*5-1;
      sprintf( age_0, "%d", k0);
      sprintf( age_1, "%d", k1);
      pTitle = strcat(Title_Parameters, "Age group (");
      pTitle = strcat(Title_Parameters, age_0);
      pTitle = strcat(Title_Parameters, "-");
      pTitle = strcat(Title_Parameters, age_1);
      pTitle = strcat(Title_Parameters, " years)");
    }
    CPGPLOT___X_Y___S_C_A_T_T_E_R_E_D___S_A_M_E___P_L_O_T ( Table->CPG, SAME,
							    No_of_Columns/2 + YEARS_BEFORE + YEARS_AFTER,
							    Year_Vector, Age_Death_Rates_Female[i], 
							    "Year",
							    "Age Specific Female Mortality Rates",
							    Title_Parameters,
							    Table->CPG->CPG_SCALE_X,
							    Table->CPG->CPG_SCALE_Y );
    SAME = 1;
    int j_Negative_Value; 
    x_Data_0 = (double *)calloc(No_of_Columns/2, sizeof(double));
    y_Data_0 = (double *)calloc(No_of_Columns/2, sizeof(double));
    x_Data = (double *)calloc(5, sizeof(double));
    y_Data = (double *)calloc(5, sizeof(double));
    for(j = YEARS_BEFORE; j < No_of_Columns/2 + YEARS_BEFORE; j++) {
      x_Data_0[j-YEARS_BEFORE] = Year_Vector[j];
      y_Data_0[j-YEARS_BEFORE] = Age_Death_Rates_Female[i][j];
    }
    gsl_fit_linear(x_Data_0, 1, y_Data_0, 1, No_of_Columns/2,
		   &c0, &c1, &cov00, &cov01, &cov11, &chisq);

    n = No_of_Columns/2 + YEARS_BEFORE + YEARS_AFTER;

    x_Data_Fit = (double *)calloc(n , sizeof(double));
    y_Data_Fit = (double *)calloc(n , sizeof(double));
    j_Negative_Value = 0; 
    for(j = 0; j < n ; j++) {
      x_Data_Fit[j] = Year_Vector[j];
      gsl_fit_linear_est (x_Data_Fit[j], c0, c1, cov00, cov01, cov11,
			  &y_Fit, &yf_err);

      y_Data_Fit[j] = y_Fit + (gsl_rng_uniform(r)-1.0) * yf_err;

      if( y_Data_Fit[j] < 0.0001) j_Negative_Value = j; 
    }

    if(j_Negative_Value > 0) {
      for(j =  (No_of_Columns/2 +YEARS_BEFORE -5); j < (No_of_Columns/2 + YEARS_BEFORE); j++) {
	x_Data[j-(No_of_Columns/2 +YEARS_BEFORE -5)] = Year_Vector[j];
	y_Data[j-(No_of_Columns/2 +YEARS_BEFORE -5)] = Age_Death_Rates_Female[i][j];
      }
      gsl_fit_linear(x_Data, 1, y_Data, 1, 5,
		     &c0, &c1, &cov00, &cov01, &cov11, &chisq);
      
      for(j = (No_of_Columns/2 +YEARS_BEFORE -5); j < n ; j++) {
	x_Data_Fit[j] = Year_Vector[j];
	gsl_fit_linear_est (x_Data_Fit[j], c0, c1, cov00, cov01, cov11,
			    &y_Fit, &yf_err);

	y_Data_Fit[j] = y_Fit + (gsl_rng_uniform(r)-1.0) * yf_err;
	
	if( y_Data_Fit[j] < 0.0001 ) 
	  y_Data_Fit[j] = 0.0001; + 0.0001 * gsl_rng_uniform(r);  
      }
    }
    printf("\n");

    Table->CPG->color_Index = 2; //* 2: red *//
    Table->CPG->type_of_Symbol = 4;
    CPGPLOT___X_Y___P_L_O_T_T_I_N_G___S_A_M_E___P_L_O_T ( Table->CPG, SAME,
							    n, 
							    x_Data_Fit, y_Data_Fit, 
							    "Year",
							    "Age Specific Mortality Rates",
							    Title_Parameters,
							    Table->CPG->CPG_SCALE_X,
							    Table->CPG->CPG_SCALE_Y );
    getchar();
    
    printf("%d: %s: ", i, Title_Parameters); 
    for(j = 0; j < n; j++) {
      x_Data_Fit[j] = Year_Vector[j];
      if(j < YEARS_BEFORE || j >= (YEARS_BEFORE + No_of_Columns/2) ) {
	Age_Death_Rates_Female[i][j] = y_Data_Fit[j];
	assert(y_Data_Fit[j] > 0.0); 
      }
      printf("m_F[%d][%g]=%g  ",
	     i, Year_Vector[j], Age_Death_Rates_Female[i][j]);
    }
    free(x_Data_Fit); free(y_Data_Fit);
    free(x_Data); free(y_Data);
    getchar();
  }
  /* E N D : Drawing the Function (FEMALES) */

  // double * Year_1983_2016 = (double *)calloc( n, sizeof(double) ); 
  for(j = 0; j < n; j++) Year_1983_2033[j] = Year_Vector[j];

  * No_1983_2033 = n;
  * No_of_Age_Groups = No_of_Rows;
  * No_of_Cities = No_of_CITIES; 
					       
  // for(i=0; i<No_of_CITIES; i++) free (Urban_Population_Vector[i]);
  // free (Urban_Population_Vector);
  // free (Fecundity_Vector); 

  free(Death_Rates[0]); free(Death_Rates[1]);
  free(Death_Rates); free(Death_Rates_F); free(Death_Rates_M);
  free(Death_Rates_F_SHORT);
  free(Death_Rates_M_SHORT);
  free(Year_Vector); free(Year_Vector_SHORT); free(Years);
  for(i=0; i<No_of_Rows_Max; i++) {
    free(Age_Death_Rates[i]); 
    free(City_Population[i]);
    free (Pop_Fecundity[i]);
  }
  free(Age_Death_Rates);
  free(City_Population);
  free(Pop_Fecundity);
  
  free (City_Population_2013);
  free (City_Factor_2013);    
  free (Years_C);

  free(Years_F);
  free(Fecundity_F);
  free(Population_F);
  free(Urban_Population_F); 
  for(i=0; i<No_of_CITIES; i++) free(Urban_Population_Cities_F[i]);
  free(Urban_Population_Cities_F); 
  
  free(pValue);
  free(Title_Parameters); 
}
