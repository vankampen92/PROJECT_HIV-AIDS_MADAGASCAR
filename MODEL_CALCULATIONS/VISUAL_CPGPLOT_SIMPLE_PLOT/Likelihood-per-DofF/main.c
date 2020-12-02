/* This main function plots the likelihood per dgr of freedom.
  
   Data are given as input files.    

   Compilation:
   ~$: make 
     
   Execution (if data files are read from directory, which is NOT the case in thi main code below unless you modify the program accordingly):

   ~$ ./PLOT -Fn 1 -F0 Likelihood_per_Degree_of_Freedom_Toamasina_Sigmoidal.dat -G0 1 -G1 1 -G2 1 -G3 1999 -G4 2010 -G5 1 -G6 0.0 -G7 15

   ~$ ./PLOT -Fn 2 -F0 Likelihood_per_Degree_of_Freedom_Toamasina_Sigmoidal.dat -F1 Likelihood_per_Degree_of_Freedom_Antananarivo_Sigmoidal.dat -G0 2 -G1 1 -G2 1 -G3 1999 -G4 2010 -G5 1 -G6 0.0 -G7 22

 It is very important to establish the axis ranks through the corresponding command line arguments as in the example. Your ranks will be active as long as you also introduce -G2 1 (x axis) and G5 1 (y axis) --- as oposed to -G2 0 and -G5 0, which will shut down your axis rank choice. In this latter case, the program calculates rank axis automatically. 

*/
#include "main.h"

#include "global.h"

#define No_of_POINTS_MAX 1000000

int main (int argc, char **argv)
{
  int i, n, N;
  Parameter_CPGPLOT * CPG;
  int colors[3] = {2,12,8};
  float x_SP[2], y_SP[2];
  float x, y, d;
  char * p; 
  
#include "default.c"

 /* Command line arguments */
  if(argc>1) ArgumentControl(argc,argv);
  int No_of_PANELS = No_of_FILES; 
  int No_of_POINTS = 2;
  CPG = A_C_T_I_V_A_T_E___C_P_G_P_L_O_T ( No_of_PANELS, No_of_POINTS, 0,
                                          CPG_DRIVER_NAME );
  printf(" Parameter_CPGPLOT data structure has been allocated and initiated\n");

  No_of_FILES = CPG->CPG_File->No_of_FILES; 
  
  double ** x_Data = (double **)calloc( 2, sizeof(double *) );
  double ** y_Data = (double **)calloc( 2, sizeof(double *) );
  for(i=0; i<No_of_FILES; i++) {
    x_Data[i] = (double *)calloc( No_of_POINTS_MAX, sizeof(double) );
    y_Data[i] = (double *)calloc( No_of_POINTS_MAX, sizeof(double) );
  }
  int * No_of_DATA_POINTS = (int *)calloc( No_of_FILES, sizeof(int) ); 

  int SAME_PLOT = 0;   
  for(i=0; i<No_of_FILES; i++) { 
   
    X_Y___R_E_A_D ( CPG->CPG_File->Name_of_FILE[i],
  		  x_Data[i],
  		  y_Data[i],
  		  &No_of_DATA_POINTS[i]);

    /* Just checking data are correctly read... */
    printf("First Data Set\n");
    for(n=0; n<No_of_DATA_POINTS[i]; n++)
      printf( "Year: %g\t Frequency: %g\n",
	      x_Data[i][n], y_Data[i][n]);              
    printf("\n");
    getchar();

    CPG->Title[0] = '\0'; // Effectively deleting previsously defined title
    if (i == 0) p = strcat(CPG->Title, "Toamasina");
    if (i == 1) p = strcat(CPG->Title, "Antananarivo");
    
    /* char * Num = (char *)calloc( 10, sizeof(char) ); */
    /* sprintf(Num, "%7d", 5195769); */
    /* p = strcat(CPG->Title, Num); */
    /* free(Num); */

    SAME_PLOT = 0;   
    CPG->color_Index    = 3;
    CPG->type_of_Line   = 1;
    CPG->type_of_Width  = 8;  
    CPG->type_of_Symbol = 6;  
    CPGPLOT___X_Y___S_C_A_T_T_E_R_E_D___S_A_M_E___P_L_O_T ( CPG, SAME_PLOT,
							    No_of_DATA_POINTS[i],
							    x_Data[i], y_Data[i],
							    "Introduction Year",
							    "NLL (per dgr of freedom)",
							    CPG->Title,
							    CPG->CPG_SCALE_X,
							    CPG->CPG_SCALE_Y );
    //getchar(); 
    /* SAME_PLOT = 1; */
    /* CPG->color_Index    = 2; */
    /* CPG->type_of_Line   = 1; */
    /* CPG->type_of_Width  = 8;   */
    /* CPG->type_of_Symbol = 1;  */
    /* CPGPLOT___X_Y___P_L_O_T_T_I_N_G___S_A_M_E___P_L_O_T ( CPG, SAME_PLOT,       */
    /* 							     No_of_DATA_POINTS[i], */
    /*							     x_Data[i], y_Data[i], */
    /* 							     "Time", "NLL",        */
    /* 							     CPG->Title,           */
    /* 							     CPG->CPG_SCALE_X,     */
    /* 							     CPG->CPG_SCALE_Y );   */
  }
  
  for(i=0; i<No_of_FILES; i++) {
    free(x_Data[i]);
    free(y_Data[i]);
  }
  free(x_Data); free(y_Data);
  
  P_A_R_A_M_E_T_E_R___C_P_G_P_L_O_T___F_R_E_E( CPG, No_of_PANELS );
  cpgclos();

  printf("\nEnd of progam\n");
  return(0);
}
