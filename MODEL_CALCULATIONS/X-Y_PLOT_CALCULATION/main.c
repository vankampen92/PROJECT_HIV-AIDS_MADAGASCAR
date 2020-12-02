/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                            David Alonso, 2018 (c)                         */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#include <Include/MODEL.h>

#include "global.h"

gsl_rng * r; /* Global generator defined in main.c */

/* This code calculates and plots the intersection between two curves: 

   y = F_1(x), this is, the effective infectious fraction for males (y) that 
   would be produced by a given, but constant, effective infectious fraction 
   for females (x). 

   y = F_2^{-1}(x), where x = F_2(y) would the effective infectious fraction 
   for females (x) that would be produced by a given (and constant) effective 
   infectious fraction for males, (x).

   Compilation:

   . ~$ make X_MODEL=X2W2SILD Y_MODEL=YSILD
   
   Execution:

   . ~S ./X2W2SILD-YSILD -y0 1 -H15 1000.0 -G0 1 -G1 1 -G5 1 -G6 0.0 -G7 10 

   . ~$   
*/ 

int main(int argc, char **argv)
{
  int i, j, k, kk, l, m, n, z, p;
  Parameter_Table Table;
  
  P_ARG = &Table;
  
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

  int No = 1000;

  double * x_Data = (double *)calloc( No, sizeof(double));
  double ** y     = (double **)calloc(2, sizeof(double *));
            y[0]  = (double *)calloc( No, sizeof(double));
            y[1]  = (double *)calloc( No, sizeof(double));
	    
  x_y_Intersection_Functions( &Table, No, 
			      x_Data, y[0], y[1] );
  
#if defined CPGPLOT_REPRESENTATION
  int SAME = 0;
  
  Table.CPG->type_of_Width =  15;
  Table.CPG->color_Index   =  3;
  Table.CPG->type_of_Symbol = 1;
  Table.CPG->type_of_Line   = 1;
 
  char * Title = (char *)malloc( sizeof(char) * 500 );
  Title[0] = '\0';
  char * p_DUMMY = strcat( Title, "Intersection Plot");
  
  I_N_T_E_R_S_E_C_T_I_O_N___x_y___D_I_A_G_R_A_M___S_I_N_G_L_E___P_L_O_T ( &Table,
									  No,
									  x_Data,
									  y,
									  Title );
  
  P_A_R_A_M_E_T_E_R___C_P_G_P_L_O_T___F_R_E_E( Table.CPG, SUB_OUTPUT_VARIABLES ); 

  free(Title); 
#endif

  free(x_Data); free(y[0]); free(y[1]);
  free(y); 

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

  free(Initial_Guess);
  
  P_A_R_A_M_E_T_E_R___T_A_B_L_E___F_R_E_E( &Table );
  /*  END : Freeing  All Memmory * * * * * * * * * * * * * * */

  printf("\nEnd of progam\n");
  return (0);
}

