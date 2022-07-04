/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                            David Alonso, 2011 (c)                         */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#include <MODEL.h>

#include "global.h"

/* This code scans R_0 as a function depending on model parameters as specified
   in Parameter_Table Structure.  Parameter ranges are defined in Parameter_Space
   structure. Parameters to scan are defined as input arguments: 

   -sP 2 -I0 1 -H1 0.005 -m0 0.001  -M0 0.01    -d0 100     // Parameter: p_XY
         -I1 0 -H0 100.0 -m1 50.0 -M1 200.0     -d1 100     // Parameter: Beta_Y

   / -I0 21  -H21 1.0   -m0 0.0   -M0 2.0     -d0 0.01      // Parameter: r_R
   / -I1 0   -H0 100.0  -m1 0.0   -M1 200.0   -d1 0.1       // Parameter: Beta_Y
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

   -G0 1 -G1 1 -n 1 -v0 0 -en 0 -iP 0 

   Optimal Average Paremters (Noyse Be): 
   / -H21 1.01   // Parameter: r_R
   / -H0  108.14 // Parameter: Beta_Y
   / -H8  108.19 // Parameter: Beta_X
   / -H12 7.27   // Parameter: Eta
   / -H7  50.53  // Parameter: mDelta
   / -H16 0.235  // Parameter: f_W
   / -H17 0.398  // Parameter: f_0
   / -H1  0.002  // Parameter: p_XY
   / -H9  0.001  // Parameter: p_YX
   / -H5  2.02   // Parameter: Gamma
   / -H6  0.103  // Parameter: Mu
   / -H15 36.538 // Parameter: Xhi
   / -H10 0.040  // Parameter: Sigma_0
   / -H11 0.021  // Parameter: Sigam_0_r
   / -H18 0.035  // Parameter: Sigma_1
   / -H19 0.016  // Parameter: Sigma_1_r
   / -H20 0.101  // Parameter: Alpha
   / -H2  717.14 // Parameter: F_Y  at year 2000
   / -H13 828.07 // Parameter: F_X  at year 2000
   / -H4 0.01965 // Parameter: Delta_Y at year 2000
   / -H3 0.01901 // Parameter: Delta_X at year 2000 

   -H21 1.01 -H0 108.14 -H8 108.19 -H12 7.27 -H7 50.53 -H16 0.235 -H17 0.398 -H1 0.002 -H9 0.001 -H5 2.02 -H6 0.103 -H15 36.538 -H10 0.040  -H11 0.021 -H18 0.035 -H19 0.016 -H20 0.101 -H2 717.14 -H13 828.07 -H4 0.01965 -H3 0.01901 

   Any parametric function should be generically defined as:
   
   double Function (Parameter_Table * Table); 
  
   Compilation:
   
   . ~$ make 
   
   Execution:
                                                       
   . ~$ ./X2W2SILD-YSILD  -y0 1 -H21 1.01 -H0 108.14 -H8 108.19 -H12 7.27 -H7 50.53 -H16 0.235 -H17 0.398 -H1 0.002 -H9 0.001 -H5 2.02 -H6 0.103 -H15 36.538 -H10 0.040  -H11 0.021 -H18 0.035 -H19 0.016 -H20 0.101 -H2 717.14 -H13 828.07 -H4 0.01965 -H3 0.01901 -sP 2 -I0 9 -m0 0.00001 -M0 0.001 -d0 400 -I1 0 -m1 50.0 -M1 120.0 -d1 400 -G0 1 -G1 1 -G14 R\\d\\fs0\\fn\\u -n 1 -v0 0 -en 0 -iP 0

   . ~$  ./X2W2SILD-YSILD -y0 1 -sP 2 -I0 9 -m0 0.0 -M0 0.0006 -d0 400 -I1 0 -m1 60.0 -M1 120.0 -d1 400 -G0 2 -G1 2 -n 1 -v0 0 -en 0 -iP 0 -G29 /CPS -G30 R

   The execution of this requires the presence of these files that will be read by the code: 
   
   -rw-rw-r-- 1 dalonso dalonso 3600 ene 11 15:21 Command_String_All_Cties_Sigmoidal_C5.dat
   -rw-rw-r-- 1 dalonso dalonso  362 ene 12 01:40 Command_String_Anta_Sigmoidal_C5.dat
   -rw-rw-r-- 1 dalonso dalonso  356 ene 11 15:19 Command_String_Anta_Sigmoidal.dat
   -rw-rw-r-- 1 dalonso dalonso  359 ene 12 01:40 Command_String_Ants_Sigmoidal_C5.dat
   -rw-rw-r-- 1 dalonso dalonso  358 ene 11 15:19 Command_String_Ants_Sigmoidal.dat
   -rw-rw-r-- 1 dalonso dalonso  361 ene 12 01:40 Command_String_Fian_Sigmoidal_C5.dat
   -rw-rw-r-- 1 dalonso dalonso  357 ene 11 15:19 Command_String_Fian_Sigmoidal.dat
   -rw-rw-r-- 1 dalonso dalonso  361 ene 12 01:40 Command_String_Maha_Sigmoidal_C5.dat
   -rw-rw-r-- 1 dalonso dalonso  359 ene 11 15:19 Command_String_Maha_Sigmoidal.dat
   -rw-rw-r-- 1 dalonso dalonso  361 ene 12 01:40 Command_String_Mora_Sigmoidal_C5.dat
   -rw-rw-r-- 1 dalonso dalonso  362 ene 11 15:19 Command_String_Mora_Sigmoidal.dat
   -rw-rw-r-- 1 dalonso dalonso  362 ene 12 01:40 Command_String_Moro_Sigmoidal_C5.dat
   -rw-rw-r-- 1 dalonso dalonso  357 ene 11 15:19 Command_String_Moro_Sigmoidal.dat
   -rw-rw-r-- 1 dalonso dalonso  360 ene 12 01:40 Command_String_Nosy_Sigmoidal_C5.dat
   -rw-rw-r-- 1 dalonso dalonso  353 ene 11 15:19 Command_String_Nosy_Sigmoidal.dat
   -rw-rw-r-- 1 dalonso dalonso  360 ene 12 01:40 Command_String_Taol_Sigmoidal_C5.dat
   -rw-rw-r-- 1 dalonso dalonso  356 ene 11 15:19 Command_String_Taol_Sigmoidal.dat
   -rw-rw-r-- 1 dalonso dalonso  359 ene 12 01:40 Command_String_Toam_Sigmoidal_C5.dat
   -rw-rw-r-- 1 dalonso dalonso  359 ene 11 15:19 Command_String_Toam_Sigmoidal.dat
   -rw-rw-r-- 1 dalonso dalonso  355 ene 12 01:40 Command_String_Toli_Sigmoidal_C5.dat
   -rw-rw-r-- 1 dalonso dalonso  360 ene 11 15:19 Command_String_Toli_Sigmoidal.dat
 
   These files are created at ./TEMPORAL_EVOLUTION_INI_YEAR_EXTRAPOLATION/ when average 
   parameter configurations (per city) are saved in latex formatted tables 
*/

gsl_rng * r; /* Global generator defined in main.c */

void String_Command_File_Read(char * File, int * count, char ** array) ;

void Updating_Parameter_Table_from_Command_String_File(char * ,  Parameter_Table * ); 

float * customized_contour_levels( Parameter_CPGPLOT * C )
{
    int i;

    /* Four contour levels */
    C->NC = 4;
    float * clevels = (float *)calloc( C->NC, sizeof(float) );
    clevels[0] = 1.0;
    clevels[1] = 2.5;
    clevels[2] = 5.0;
    clevels[3] =10.0; 
    
    return(clevels);
}

int main(int argc, char **argv)
{
  int i, k;
  char * pF; 
  Parameter_Table Table;
  double Value_0, Value_1; 
  
  P_ARG = &Table;

#include "default.c"
  
  /* Extra default values */
  int No_of_POINTS_1    = 400;
  int Input_Parameter_1 = 12; 
  int No_of_POINTS_2    = 400;
  int Input_Parameter_2 = 25;

  /* Command line arguments */
  if(argc>1) ArgumentControl(argc,argv);
  
  #include "include.Output_Variables.default.aux.c"
  P_A_R_A_M_E_T_E_R___T_A_B_L_E___A_L_L_O_C(   &Table );
  P_A_R_A_M_E_T_E_R___T_A_B_L_E___U_P_L_O_A_D( &Table, Index_Output_Variables );
  printf(" Parameter_Table structure has been correctly allocated and initiated\n");

  Parameter_Model * City_Par_Values = (Parameter_Model *)malloc( 1 * sizeof(Parameter_Model) );
  P_A_R_A_M_E_T_E_R___I_N_I_T_I_A_L_I_Z_A_T_I_O_N (&Table, City_Par_Values);
  printf(" Parameter_Model structure 'City_Par_Values' has been correctly allocated and initiated\n");
  
  /* B E G I N : Reserving memmory for Parameter Space */
  Parameter_Space * Error_Space = (Parameter_Space *)calloc(1, sizeof(Parameter_Space));
  assert( No_of_ERROR_PARAMETERS == 0 );
  Table.E_Space = Error_Space;
 
  Parameter_Space * Initial_Condition_Space = (Parameter_Space *)calloc(1,
									sizeof(Parameter_Space));
  assert( No_of_IC == 0 );
  Table.IC_Space = Initial_Condition_Space;
  
  #include <include.Parameter_Space.default.aux.c>
  Parameter_Space * Space = (Parameter_Space *)calloc(1, sizeof(Parameter_Space));
  Parameter_Space_Alloc( Space, No_of_PARAMETERS, d);
  Parameter_Space_Initialization( Space, No_of_PARAMETERS, TOLERANCE, MAX_No_of_ITERATIONS,
				  d, Index, Ranges, Acc);
  Parameter_Table_Index_Update(Index, No_of_PARAMETERS, &Table);
  Table.S = Space;
  printf("Parameter_Space structure has been correctly allocated and initiated\n");
  /*     E N D : ------------------------------------- */

  No_of_POINTS_1    = Space->N[0];
  Input_Parameter_1 = Space->Parameter_Index[0]; 
  No_of_POINTS_2    = Space->N[1];
  Input_Parameter_2 = Space->Parameter_Index[1];
  
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
  printf("\n"); //Press_Key();
  /*   END: Checking Random Number Generator Setup */
#endif
  
  int No_of_CITIES = 1;        // 11;
  int City_Index[11] = { 0, 9, 10, 2, 3, 4, 1, 5, 6, 7, 8 };    //Full
  char * City_Names[] = { "Antananarivo", "Antsiranana",
			  "Mahajanga",    "Toamasina",
			  "Fianarantsoa", "Toliary",
			  "Taolagnaro",   "Moramanga",
			  "Antsirabe",    "Morondava",  
			  "Nosy_Be" };

  char * City_Short_Names[] = { "Anta",  "Ants",
				"Maha",  "Toam",
				"Fian",  "Toli",
				"Taol",  "Mora",
				"Aabe",  "Moro",
				"Nosy" };
  
  char ** City_Short_Names_2nd = (char **)calloc(No_of_CITIES, sizeof(char *) );
  for(k=0; k<No_of_CITIES; k++) 
    City_Short_Names_2nd[k] = (char *)calloc(10, sizeof(char) );
  
  for(k = 0; k<No_of_CITIES; k++) {
    // k=8 is a city with no infection ("Antsirabe")
    if ( City_Index[k] != 8 ) {

      City_Short_Names_2nd[k][0]  = '\0';
      pF = strcat(City_Short_Names_2nd[k], City_Short_Names[City_Index[k]]);
      Updating_Parameter_Table_from_Command_String_File(City_Short_Names_2nd[k], &Table);
      P_A_R_A_M_E_T_E_R___I_N_I_T_I_A_L_I_Z_A_T_I_O_N ( &Table, City_Par_Values) ;
      
      double * W_GRID = (double *)malloc( No_of_POINTS_1 * No_of_POINTS_2 * sizeof(double) );
      int Status =  generic_Function_Parameter_2Dim_Scan(&Table, 
							 No_of_POINTS_1, Input_Parameter_1,
							 No_of_POINTS_2, Input_Parameter_2,
							 R_0_Function, 
							 W_GRID, "R_0.dat");
#if defined CPGPLOT_REPRESENTATION
      /* BEGIN : 2D GRID cpgplot representation */
      /*********************************************************************/
      Table.CPG->X_label   = Table.Symbol_Parameters_Greek_CPGPLOT[Input_Parameter_1]; 
      Table.CPG->Y_label   = Table.Symbol_Parameters_Greek_CPGPLOT[Input_Parameter_2]; 
      /*********************************************************************/
      // Boundary(Input_Parameter_1, &Value_0, &Value_1);
      Value_0 = Parameter_Model_into_Vector_Entry( Input_Parameter_1, Space->Parameter_min );
      Value_1 = Parameter_Model_into_Vector_Entry( Input_Parameter_1, Space->Parameter_MAX );
      
      Table.CPG->ORIGIN_X    = Value_0;
      Table.CPG->X_Dimension = (Value_1 - Value_0);
      
      // Boundary(Input_Parameter_2, &Value_0, &Value_1);
      Value_0 = Parameter_Model_into_Vector_Entry( Input_Parameter_2, Space->Parameter_min );
      Value_1 = Parameter_Model_into_Vector_Entry( Input_Parameter_2, Space->Parameter_MAX );
      
      Table.CPG->ORIGIN_Y = Value_0;
      Table.CPG->Y_Dimension = (Value_1 - Value_0);
      
      Table.CPG->x_GRID  = No_of_POINTS_1; 
      Table.CPG->y_GRID  = No_of_POINTS_2;
      
      int Output_Variable  = Table.OUTPUT_VARIABLE_INDEX[0];
      Table.CPG->W_label   = Table.Output_Variable_Name[Output_Variable];

      Table.CPG->Title[0]='\0';  
      pF = strcat(Table.CPG->Title, "R\\d\\fs0\\fn\\u: ");
      pF = strcat(Table.CPG->Title, City_Names[City_Index[k]]);
      
      int FIRST_PLOT = 0;
      double i_PLOT  = 0.0;
      C_P_G___P_L_O_T_T_I_N_G___2d___G_R_I_D___S_H_A_D_E_S( Table.CPG,
							    W_GRID, 
							    FIRST_PLOT,
							    Table.CPG->CPG_SCALE_W, 
							    Table.CPG->CPG_RANGE_W_0,
							    Table.CPG->CPG_RANGE_W_1,
							    i_PLOT );
      
      FIRST_PLOT = 1;
      Table.CPG->AUTOMATIC_CONTOUR = 0;
      /* If AUTOMATIC_CONTOUR is 0, the user should customized contours through
	 the function customized_contour_levels(...);
      */
      Table.CPG->contour_level = customized_contour_levels ( Table.CPG );
      C_P_G___P_L_O_T_T_I_N_G___2d___G_R_I_D___C_O_N_T_O_U_R( Table.CPG,
							      W_GRID, 
							      FIRST_PLOT,
							      Table.CPG->CPG_SCALE_W, 
							      Table.CPG->CPG_RANGE_W_0,
							      Table.CPG->CPG_RANGE_W_1,
							      i_PLOT );
      
      /* Annotating the countours by hand */
      // cpgptxt(float x, float y, float angle, float fjust,  const char *text);
      
      cpgslw(2);
      cpgptxt(0.00002, 62.0, 0.0, 0.0,  "1.0");
      cpgptxt(0.0001, 78.0, 0.0, 0.0,   "2.5");
      cpgptxt(0.0003, 92.0, 0.0, 0.0,  "5.0");
      
      /* Drawing arrow to emulate 0.6 reduction in 
	 p_YX transmission probability (from infecious female to male)
      */
      float x_Value = Parameter_Model_into_Vector_Entry(Input_Parameter_1, City_Par_Values);
      float y_Value = Parameter_Model_into_Vector_Entry(Input_Parameter_2, City_Par_Values);

      printf("City: %s\t", City_Short_Names_2nd[k]); 
      printf("%s=%f\t", Table.Symbol_Parameters[Input_Parameter_1], x_Value);
      printf("%s=%f\n", Table.Symbol_Parameters[Input_Parameter_2], y_Value);

      cpgslw(3);  /* Line width changing to 3     */
      cpgsci(12); /* Color Index changing to 12   */
      cpgpt1(x_Value, y_Value, 23);  /* Symbol 23 */
      
      float * xs = (float *)calloc(2, sizeof(float) );
      float * ys = (float *)calloc(2, sizeof(float) );
      xs[0] = x_Value;  xs[1] = 0.4 * x_Value; /* A 40 % reduction */ 
      ys[0] = y_Value;  ys[1] = y_Value;

      cpg_XY_same_arrow( 2, xs, ys, 4, 1, 4);
      // cpg_XY_same_arrow( N, xs, ys, CPG->color_Index, CPG->type_of_Line, CPG->type_of_Width );
      
      free(xs);
      free(ys); 
#endif  	
      
      free (W_GRID);
    }
  }
#if defined CPGPLOT_REPRESENTATION
  P_A_R_A_M_E_T_E_R___C_P_G_P_L_O_T___F_R_E_E( Table.CPG, SUB_OUTPUT_VARIABLES );
  cpgclos();
#endif  

  #include <include.Parameter_Space.default.free.c>
  Parameter_Space_Free(Space, No_of_PARAMETERS); free( Space );
  free(Initial_Condition_Space);  
  free(Error_Space);

  #include <include.Output_Variables.default.free.c>
  free(City_Par_Values);

  for(k=0; k<No_of_CITIES; k++) 
    free(City_Short_Names_2nd[k]);
  free(City_Short_Names_2nd); 
  
  P_A_R_A_M_E_T_E_R___T_A_B_L_E___F_R_E_E( &Table );
  /*  END : Freeing  All Memmory * * * * * * * * * * * * * * */
  
  printf("\nEnd of progam\n");
  return (0);
}

void String_Command_File_Read(char * File, int * count, char ** array) 
{ 
  FILE *fp; 
  int c; 
  int i=0, j=0; 
  
  fp=fopen(File,"r");
  
  while((c = fgetc(fp)) !=EOF) 
    {
      if(c == ' ') 
	{ 
	  array[i][j]='\0'; 
	  j=0;
	  // printf("array[%d] = %s\n", i, array[i]); 
	  i++; 
	  continue; 
	} 
      array[i][j++] = (char)c; 
    }

  * count = i; 
  
  fclose(fp); 
}

void Updating_Parameter_Table_from_Command_String_File(char * City_Short_Name,
						       Parameter_Table * Table)
{
  int i;
  int count;
  
  char ** array = (char **)calloc( 1000, sizeof(char *) );
  for (i = 0; i < 1000; i++ )
    array[i] = (char *)calloc( 10000, sizeof(char) );
	
  char * p;
  char * Command_String_File = (char *)calloc( 200, sizeof(char) );
  p = strcat(Command_String_File, "Command_String_");
  p = strcat(Command_String_File, City_Short_Name);
  p = strcat(Command_String_File, "_Sigmoidal_C5.dat");
  
  String_Command_File_Read(Command_String_File, &count, array);
  
  // printf(" City: %s %s %s\n", array[0], array[1], array[2] );
  
  ArgumentControl(count, array); 
  
  Parameter_Values_into_Parameter_Table(Table); 
  
  for (i = 0; i < 1000; i++ ) free(array[i]); 
  free(array);

  free(Command_String_File); 
}
							
      

