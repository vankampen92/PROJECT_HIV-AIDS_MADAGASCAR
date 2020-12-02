/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                           */
/*                             MALARIA ODE with "Gamma" DELAYS               */
/*                                                                           */
/*                         Recursive Calculation of Fixed Points             */
/*                                                                           */
/*                                 David Alonso, 2006 (c)                    */
/*                                                                           */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#include <MODEL.h>

void x_y_Intersection_Function_Save_File(int k_File, int No, Parameter_Table *P)
{
  int i;
  double x, y_1,y_2;
  double x_Max;
  double *y_Sol;
  FILE *fp;
  char file[100];
  /* 
     This function saves a number of files with the data:
     
                                            x , y_1, y_2

     representing the two curves that visually intersect to define the pair (x, y) that
     defines the stationry state for the full system
  */
  
  x_Max = 5.0;
  x = 0.0; 
  
  file[0]='\0';    
  fitxer(file, "x_y_", k_File, ".dat");
  fp = fopen(file, "w");
  for(i=0; i < No; i++){
 
    x = (double)i * x_Max/ (double)No; 

    y_1 = Inverted_Steady_State_x_Fraction(x, P); 
    y_2 = Steady_State_y_Fraction(x, P); 

    fprintf(fp, "%g\t%g\t%g\n", x, y_1, y_2);

  }
  fclose(fp);
}

double x_y_Intersection_Functions( Parameter_Table * P, int No, 
				   double *x_Data, double *y_1, double *y_2 )
{
  double x, x_Max, w;
  int i;
  /* 
     This function calculates the two curves (x_Data, y_1) and (x_Data, y_1) 
     that visually intersect to define the pair (x, y) that defines the stationry state 
     for the full system
  */

  x = 0.0;
  x_Max = 4.75;
  
  for(i=0; i < No; i++){

    x = (double)i * x_Max/ (double)No;
    
    x_Data[i] = x; 

    y_1[i] = Steady_State_y_Fraction(x, P); 
    y_2[i] = Inverted_Steady_State_x_Fraction(x, P); 

    printf("%g\t%g\t%g\n", x, y_1[i], y_2[i]);
  }

  getchar();
  
  return(x);
}

#if defined CPGPLOT_REPRESENTATION
void I_N_T_E_R_S_E_C_T_I_O_N___x_y___D_I_A_G_R_A_M___S_I_N_G_L_E___P_L_O_T ( Parameter_Table * P,
                                                                             int N,
									     double * x_Data,
									     double ** y,
                                                                             char * Title )
{
      char * p_DUMMY;
      char * X_label  = (char *)malloc( sizeof(char) * 500 );
      char * Y_label  = (char *)malloc( sizeof(char) * 500 );
      char * Title_In = (char *)malloc( sizeof(char) * 500 );
      /*********************************************************************/
      X_label[0] = '\0';
      p_DUMMY = strcat( X_label, "  Female Infectious Effective Fraction (x) ");
      Y_label[0] = '\0';
      p_DUMMY = strcat( Y_label, "  Male Infectious Effective Fraction (y) ");

      Title_In[0] = '\0';
      p_DUMMY = strcat( Title_In, Title );
      /*********************************************************************/
      CPGPLOT___X_Y_n___P_L_O_T_T_I_N_G ( P->CPG,
                                          N, 2,
                                          x_Data, y,
                                          X_label, Y_label, Title_In,
                                          P->CPG->CPG_SCALE_X, P->CPG->CPG_SCALE_Y );

      free(X_label); free(Y_label); free(Title_In); 
}


void P_L_O_T_T_I_N_G___I_N_T_E_R_S_E_C_T_I_O_N___x_y___D_I_A_G_R_A_M( Parameter_Table * P, 
								      int N, 
								      int No_of_POINTS,
								      int Input_Parameter )
{
  char * p_DUMMY;
  char * X_label  = (char *)malloc( sizeof(char) * 500 );
  char * Y_label  = (char *)malloc( sizeof(char) * 500 );
  char * Title_In = (char *)malloc( sizeof(char) * 500 );
  char * Number   = (char *)malloc( sizeof(char) * 50  );
  Parameter_Space * S = P->S; 

  double x, Value, Value_0, Value_1;
  int j, key;
  
  /*********************************************************************/
  X_label[0] = '\0';
  p_DUMMY = strcat( X_label, " Female Infectious Effective Fraction (x) ");
  Y_label[0] = '\0';
  p_DUMMY = strcat( Y_label, " Male Infectious Effective Fraction (y) ");
  /*********************************************************************/

  double * x_Data = (double *)calloc( N, sizeof(double) );
  double ** y     = (double **)calloc( 2, sizeof(double) );
  y[0]            = (double *)calloc( N, sizeof(double) );
  y[1]            = (double *)calloc( N, sizeof(double) );
  
  Value_0 = Parameter_Model_into_Vector_Entry( Input_Parameter, S->Parameter_min );
  Value_1 = Parameter_Model_into_Vector_Entry( Input_Parameter, S->Parameter_MAX );
  
  for( j = 0; j < No_of_POINTS; j++ ){
      
    Value = Value_0 + j * (Value_1 - Value_0)/(double)(No_of_POINTS - 1);
    
    AssignVectorEntry_to_Structure(P, Input_Parameter, Value);  
  
    x = x_y_Intersection_Functions( P, N, x_Data, y[0], y[1]);
    
    Title_In[0] = '\0';
    p_DUMMY = strcat( Title_In, " Stationary Fractions:   ");
    p_DUMMY = strcat( Title_In, P->Name_Parameters[Input_Parameter] );
    p_DUMMY = strcat( Title_In, "  =  ");
    
    // doubletochar( Value, Number );
    sprintf(Number, "%g", Value);
    p_DUMMY = strcat( Title_In, Number);
    
    CPGPLOT___X_Y_n___P_L_O_T_T_I_N_G ( P->CPG, N, 2, x_Data, y, 
					X_label, Y_label, Title_In,
					P->CPG->CPG_SCALE_X, 
					P->CPG->CPG_SCALE_Y );
  }

  free (Title_In); free(X_label); free(Y_label); free (Number);
  free (x_Data); free (y[0]); free (y[1]); free(y); 
}
#endif
