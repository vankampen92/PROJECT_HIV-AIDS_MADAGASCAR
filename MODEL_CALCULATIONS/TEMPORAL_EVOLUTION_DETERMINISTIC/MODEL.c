#include <MODEL.h>

#define EPSILON 1.0E-06

extern gsl_rng * r;

int M_O_D_E_L( Parameter_Table * Table )
{
  double x;

  int i,k, n;
  int I_Time, no_Patch;
  int Bad_Times;
  Parameter_Model * P;

  I_Time    = Table->T->I_Time;

  P = (Parameter_Model *)malloc( 1 * sizeof(Parameter_Model) );
  P_A_R_A_M_E_T_E_R___I_N_I_T_I_A_L_I_Z_A_T_I_O_N (Table, P);
  Table->P  = P;
  printf(" Parameter_Model structure has been correctly allocated and initiated\n");

  /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
  /* Definition of the state vector numerical order, from 0 to K, of model variables */
  #include <Model_Variables_Code.Include.c>

  int MODEL_STATE_VARIABLES = K+1;
  Table->MODEL_STATE_VARIABLES = MODEL_STATE_VARIABLES;

  Table->Vector_Model_Variables_Time_0 = (double *)calloc( MODEL_STATE_VARIABLES, sizeof(double) );
  Table->Vector_Model_Variables = (double *)calloc( MODEL_STATE_VARIABLES, sizeof(double) );
  Table->Vector_Model_Variables_Stationarity = (double *)calloc( MODEL_STATE_VARIABLES,
								 sizeof(double) );
  Table->Vector_Model_Variables_MultiStability[0] = (double *)calloc( MODEL_STATE_VARIABLES,
								   sizeof(double) );
  Table->Vector_Model_Variables_MultiStability[1] = (double *)calloc( MODEL_STATE_VARIABLES,
								   sizeof(double) );
  Table->Vector_Model_Variables_MultiStability[2] = (double *)calloc( MODEL_STATE_VARIABLES,
								   sizeof(double) );

#if defined STATIONARY_POINT_REPRESENTATION
  /* B E G I N : Calculation of Stationary Points */
  Fixed_Points_All( Table,
		    Table->Vector_Model_Variables_MultiStability[0],
		    Table->Vector_Model_Variables_MultiStability[1],
		    Table->Vector_Model_Variables_MultiStability[2],
		    EPSILON );

  printf("Lower Fixed Point (model variables):\t");
  for (k=0; k < Table->MODEL_STATE_VARIABLES; k++)
    printf("y_LOWER[%d] = %g\t", k, Table->Vector_Model_Variables_MultiStability[0][k]);
  printf("\n");
  printf("Inter Fixed Point (model variables):\t");
  for (k=0; k < Table->MODEL_STATE_VARIABLES; k++)
    printf("y_INTER[%d] = %g\t", k, Table->Vector_Model_Variables_MultiStability[1][k]);
  printf("\n");
  printf("Upper Fixed Point (model variables):\t");
  for (k=0; k < Table->MODEL_STATE_VARIABLES; k++)
    printf("y_UPPER[%d] = %g\t", k, Table->Vector_Model_Variables_MultiStability[2][k]);
  printf("\n");
  /*    E N D : --------------------------------- */
#endif

  printf(" Entering deterministic dynamics. Parameter time dependencies will be\n");
  printf(" de-activated if -t4 0 (TYPE_of_TIME_DEPENDENCE = 0).\n");

  D_E_T_E_R_M_I_N_I_S_T_I_C___T_I_M_E___D_Y_N_A_M_I_C_S( Table ) ;

#if defined CPGPLOT_REPRESENTATION
  /* Notice that j = TIMES now, as expected, since the program is just out
     from the loop:
        for( j = 1; j < TIMES; j++ ) { ... }
  */

  //  Parameter Table dependent costumized plotting is defined in ~/CPGPLOT/CPGPLOT_Parameter_Table/ files
  int TIMES           = Table->T->I_Time;
  int Input_Parameter = 0; /* The value of this model parameter appears in the title */
  // C_P_G___S_U_B___P_L_O_T_T_I_N_G ( Table, TIMES, Table->CPG->x_Time, Table->CPG->y_Time );
  C_P_G___S_U_B___P_L_O_T_T_I_N_G___C_U_S_T_O_M_I_Z_E_D___T_I_T_L_E ( Table,
   								      TIMES,
   								      Table->CPG->x_Time,
   								      Table->CPG->y_Time,
   								      Input_Parameter );

#endif
  free( Table->Vector_Model_Variables_Time_0);
  free( Table->Vector_Model_Variables );
  free( Table->Vector_Model_Variables_MultiStability[0] );
  free( Table->Vector_Model_Variables_MultiStability[1] );
  free( Table->Vector_Model_Variables_MultiStability[2] );
  free( Table->Vector_Model_Variables_Stationarity );

  free ( P );
  return(0);
}
