/* This main function plots population data and future projections.
  
   Data are given as input files.    

   Compilation:
   ~$: make 
     
   Execution (if data files are read from directory, which is NOT the case in thi main code below unless you modify the program accordingly):

   ~$ ./PLOT -Fn 2 -F0 City_Population_Antananarivo_X_Y_File.dat -F1 Projected_City_Population_Antananarivo_X_Y_File.dat -G0 1 -G1 1 -G2 1 -G3 1950 -G4 2033 -G5 1 -G6 0.0 -G7 4.0E+06

   ~$ ./PLOT -Fn 3 -F0 City_Population_Antananarivo_X_Y_File.dat -F1 Adult_Population_Antananarivo_Deterministic_Evolution.dat -F2 Projected_City_Population_Antananarivo_X_Y_File.dat -G0 1 -G1 1 -G2 1 -G3 1950 -G4 2033 -G5 1 -G6 0.0 -G7 4.0E+06

   It is very important to establish the axis ranks through the corresponding command line arguments as in the example. Your ranks will be active as long as you also introduce -G2 1 (x axis) and G5 1 (y axis) --- as oposed to -G2 0 and -G5 0, which will shut down your axis rank choice. In this latter case, the program calculates rank axis automatically. 

*/
#include "main.h"

#include "global.h"

#define No_of_POINTS_MAX 10000

void Converting_Adult_Population_into_Total_Population_Extrapolated (double * Data_Adult,
								     double * Data_Total,
								     int N);

int main (int argc, char **argv)
{
  int i, n, N;
  Parameter_CPGPLOT * CPG;
  int colors[3] = {2,12,8};
  float x_SP[2], y_SP[2];
  float x, y, d;
  
#include "default.c"

 /* Command line arguments */
  if(argc>1) ArgumentControl(argc,argv);
  int No_of_PANELS = 1;
  int No_of_POINTS = 2;
  CPG = A_C_T_I_V_A_T_E___C_P_G_P_L_O_T ( No_of_PANELS, No_of_POINTS, 0,
                                          CPG_DRIVER_NAME );
  printf(" Parameter_CPGPLOT data structure has been allocated and initiated\n");

  double ** x_Data = (double **)calloc( 2, sizeof(double *) );
  double ** y_Data = (double **)calloc( 2, sizeof(double *) );
  for(i=0; i<2; i++) {
    x_Data[i] = (double *)calloc( No_of_POINTS_MAX, sizeof(double) );
    y_Data[i] = (double *)calloc( No_of_POINTS_MAX, sizeof(double) );
  }

  double ** x_Fit = (double **)calloc( 2, sizeof(double *) );
  double ** y_Fit = (double **)calloc( 2, sizeof(double *) );
  for(i=0; i<2; i++) {
    x_Fit[i] = (double *)calloc( No_of_POINTS_MAX, sizeof(double) );
    y_Fit[i] = (double *)calloc( No_of_POINTS_MAX, sizeof(double) );
  }

  int No_of_POINTS_Data_0, No_of_POINTS_Data_1;
  int No_of_POINTS_Fit_0, No_of_POINTS_Fit_1;

  X_Y___R_E_A_D ( CPG->CPG_File->Name_of_FILE[0],
  		  x_Data[0],
  		  y_Data[0],
  		  &No_of_POINTS_Data_0);

  X_Y___R_E_A_D ( CPG->CPG_File->Name_of_FILE[1],
  		  x_Fit[0],
  		  y_Fit[0],
  		  &No_of_POINTS_Fit_0);

  X_Y___R_E_A_D ( CPG->CPG_File->Name_of_FILE[2],
  		  x_Fit[1],
  		  y_Fit[1],
  		  &No_of_POINTS_Fit_1);

  assert(No_of_POINTS_Data_0 == 16);
  assert(No_of_POINTS_Fit_0  == 34);
  assert(No_of_POINTS_Fit_1  == 34);   
  /*     E N D :                         */

  CPG->Title[0] = '\0'; // Effectively deleting previsously defined title
  char * p = strcat(CPG->Title, "Antananarivo");
  /* char * Num = (char *)calloc( 10, sizeof(char) ); */
  /* sprintf(Num, "%7d", 5195769); */
  /* p = strcat(CPG->Title, Num); */
  /* free(Num); */

  /* Just checking data are correctly read... */
  printf("First Data Set\n");
  for(n=0; n<No_of_POINTS_Data_0; n++)
    printf( "Year: %g\t Frequency: %g\n",
  	        x_Data[0][n], y_Data[0][n]);              
  printf("\n");
  getchar();
  
  int SAME_PLOT = 0;   
  CPG->color_Index    = 1;
  CPG->type_of_Line   = 1;
  CPG->type_of_Width  = 8;  
  CPG->type_of_Symbol = 6;  
  CPGPLOT___X_Y___S_C_A_T_T_E_R_E_D___S_A_M_E___P_L_O_T ( CPG, SAME_PLOT,
							No_of_POINTS_Data_0,
							x_Data[0], y_Data[0],
							"Time", "Population",
							CPG->Title,
							CPG->CPG_SCALE_X,
							CPG->CPG_SCALE_Y );
  //getchar(); 
  /* SAME_PLOT = 1; */
  /* CPG->color_Index    = 2; */
  /* CPG->type_of_Line   = 1; */
  /* CPG->type_of_Width  = 8;   */
  /* CPG->type_of_Symbol = 1;  */
  /* CPGPLOT___X_Y___P_L_O_T_T_I_N_G___S_A_M_E___P_L_O_T ( CPG, SAME_PLOT, */
  /* 							No_of_POINTS_Fit_1, */
  /* 							x_Fit[1], y_Fit[1], */
  /* 							"Time", "Population", */
  /* 							CPG->Title, */
  /* 							CPG->CPG_SCALE_X, */
  /* 							CPG->CPG_SCALE_Y ); */
  
  double * Data_ODE = (double *)calloc(No_of_POINTS_Fit_0, sizeof(double) );
				       
  Converting_Adult_Population_into_Total_Population_Extrapolated (y_Fit[0],
								  Data_ODE,
								  No_of_POINTS_Fit_0);
  SAME_PLOT = 1;
  CPG->color_Index    = 3;
  CPG->type_of_Line   = 1;
  CPG->type_of_Width  = 8;  
  CPG->type_of_Symbol = 1; 
  CPGPLOT___X_Y___P_L_O_T_T_I_N_G___S_A_M_E___P_L_O_T ( CPG, SAME_PLOT,
							No_of_POINTS_Fit_0,
							x_Fit[0], Data_ODE,
							"Time", "Population",
							CPG->Title,
							CPG->CPG_SCALE_X,
							CPG->CPG_SCALE_Y );
  free(Data_ODE); 
  
  for(i=0; i<2; i++) {
    free(x_Data[i]);
    free(y_Data[i]);
    free(x_Fit[i]);
    free(y_Fit[i]);
  }
  free(x_Data); free(y_Data);
  free(x_Fit);  free(y_Fit); 
  
  P_A_R_A_M_E_T_E_R___C_P_G_P_L_O_T___F_R_E_E( CPG, No_of_PANELS );
  cpgclos();

  printf("\nEnd of progam\n");
  return(0);
}

void Converting_Adult_Population_into_Total_Population_Extrapolated (double * Data_Adult,
								     double * Data_Total,
								     int N)
{
  double c0, c1, cov00, cov01, cov11, chisq, y_Fit, yf_err, f;
  int j;
  int n;
 
  double * Year_Vector = (double *)calloc( N, sizeof(double) );

  for(j = 0; j<N; j++) Year_Vector[j] = 2000.0 + (double)j;
  
  double y[] = {44.4, 39.87, 39.55};
  double x[] = {1975.0, 2017.0, 2018};

  gsl_fit_linear(x, 1, y, 1, 3,
		   &c0, &c1, &cov00, &cov01, &cov11, &chisq);

  printf(" Fractions of Children Population (age < 15): f(year)\n");
  printf(" Total and Adult Population, P(year) and A(year), respectively\n");
  for(j = 0; j < N ; j++) {

      gsl_fit_linear_est (Year_Vector[j], c0, c1, cov00, cov01, cov11,
			  &y_Fit, &yf_err);

      f = y_Fit; // + (gsl_rng_uniform(r)-1.0) * yf_err;
      
      printf("f[%g] = %g\t", Year_Vector[j], f);

      Data_Total[j] = 1.0/(1.0 - 0.01 * f) * Data_Adult[j];

      printf("A(%g) = %g\t T(%g) = %g\n", Year_Vector[j], Data_Adult[j],
	     Year_Vector[j], Data_Total[j]);
  }

  free(Year_Vector);
}
