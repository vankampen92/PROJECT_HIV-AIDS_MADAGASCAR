#include <MODEL.h>

#define EPSILON 1.0E-10

extern gsl_rng * r;

int Deterministic_Time_Dynamics_Two_Phases( Parameter_Table * Table, Parameter_Fitting * F );
void Fixing_System_State (double * Y, Parameter_Table * Table, double ** Data, int j);

int Model_Two_Phases( Parameter_Table * Table, Parameter_Fitting * F)
{
  double x;

  int i,k, n;
  int I_Time, no_Patch;
  int Bad_Times;

  I_Time    = Table->T->I_Time;

  Parameter_Model * P = (Parameter_Model *)malloc( 1 * sizeof(Parameter_Model) );
  P_A_R_A_M_E_T_E_R___I_N_I_T_I_A_L_I_Z_A_T_I_O_N (Table, P);
  Table->P  = P;

  /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
  /* Definition of the state vector numerical order, from 0 to K, of model variables */
  #include <Model_Variables_Code.Include.c>

  int MODEL_STATE_VARIABLES = K+1;
  Table->MODEL_STATE_VARIABLES = MODEL_STATE_VARIABLES;

  Table->Vector_Model_Variables_Time_0 = (double *)calloc( MODEL_STATE_VARIABLES, sizeof(double) );
  Table->Vector_Model_Variables = (double *)calloc( MODEL_STATE_VARIABLES, sizeof(double) );
  
  int State;
  if (F->TWO_PHASES == 1) State = Deterministic_Time_Dynamics_Two_Phases( Table, F ) ;
  else                    State = D_E_T_E_R_M_I_N_I_S_T_I_C___T_I_M_E___D_Y_N_A_M_I_C_S( Table ) ;
  
  free( Table->Vector_Model_Variables_Time_0);
  free( Table->Vector_Model_Variables );
  
  free ( P );

  return(State);
}

int Deterministic_Time_Dynamics_Two_Phases( Parameter_Table * Table, Parameter_Fitting * F )
{
  /* 
     This function makes two essential calls:

     1. Initial_Conditions_Numerical_Integration (...),
     which sets up initial conditions. In turn, this function, depending on the input parameter
     TYPE_of_INITIAL_CONDITION, sets up initial consitions in one way or another, by calling
     the functions:
     . Initial_Condition_from_Parameter_Table(P, y_INI);
     . Random_Initial_Condition(P, y_INI);
     . fixed_Points(P, y_INI, EPSILON);

     2. numerical_Integration_Driver(...), which performs the actual numerical integration

     In addition, it depends on the following functions:
     1. Time_Dependence_Apply (...), which, in turn, updates parameter table to include 
     temporal changes in parameter values depending on the value of the input parameter
     TYPE_of_TIME_DEPENDENCE

     2. definition_OutPut_Variables(...)
  */
  int i; int State;
  // FILE *FP; char file[50];
  int j, k, kk;
  int TIMES;
  Time_Control * Time;
  double Time_Current, value;

  Time         = Table->T;
  TIMES        = Table->T->I_Time;

  /* BEGIN : Initial Conditions * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
  // printf(" Before Initial_Conditions_Numerical_Integration (...)\n");
  Initial_Conditions_Numerical_Integration( Table, Table->Vector_Model_Variables );
  // printf(" After Initial_Conditions_Numerical_Integration (...). Initial Conditions:  ");

  for (k=0; k < Table->MODEL_STATE_VARIABLES; k++) {
       // printf("y[%d] = %g\t", k, Table->Vector_Model_Variables[k]);
    Table->Vector_Model_Variables_Time_0[k] = Table->Vector_Model_Variables[k];
  }
     // printf("\n");
     // Press_Key();

  Time_Current = Time->Time_Vector[0];
  if (Time->TYPE_of_TIME_DEPENDENCE > 0) Time_Dependence_Apply( Table, Time_Current );

#if defined CPGPLOT_REPRESENTATION
  Table->CPG->x_Time[0]      = Time->Time_Vector[0];
#endif

  for(k=0; k < Table->SUB_OUTPUT_VARIABLES; k++){
    kk = Table->OUTPUT_VARIABLE_INDEX[k];
    value = definition_OutPut_Variables(kk, Table->Vector_Model_Variables, Time->Time_Vector[0], Table);
#if defined CPGPLOT_REPRESENTATION
    Table->CPG->y_Time[k][0] = value;
#endif
    Table->Vector_Output_Variables[k]    = value;
    Table->Matrix_Output_Variables[k][0] = value;
  }
  /*   END : Initial Conditions - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#if defined VERBOSE
  printf("t=%g", Time_Current);
  for(k=0; k < Table->SUB_OUTPUT_VARIABLES; k++){
    printf("\ty[%d]=%g", k,Table->Vector_Output_Variables[k]);
  }
  printf("\n");
#endif

  //printf(" Initiating Numerical Integration\n");
  for( j = 1; j < TIMES; j++ ) {
    /* This loop advances the system sequentially from
       intitial time 0 to 1st time , ...,  from time (j-1) to j, and so on.
       Note: When the system is frozen (FROZEN_SYSTEM = 1), then
       this loop does not advance the system any more
    */
    if (j == 17) Fixing_System_State(Table->Vector_Model_Variables, Table, F->Data->N, j-1);  
    
    if (Table->T->TYPE_of_TIME_DEPENDENCE > 0) Time_Dependence_Apply( Table, Time_Current );
/*-------------------------------------------------------------------*/
/* B E G I N :
 *     CENTRAL POINT HERE: Numerical Integration up to the next time
 */
    State = numerical_Integration_Driver( Table, j, &Time_Current );
/*     E N D
 *-------------------------------------------------------------------*/

    if (State != GSL_SUCCESS) break;

#if defined CPGPLOT_REPRESENTATION
    Table->CPG->x_Time[j] = Time_Current;
#endif
    for(k=0; k < Table->SUB_OUTPUT_VARIABLES; k++){
      kk = Table->OUTPUT_VARIABLE_INDEX[k];
      value = definition_OutPut_Variables(kk, Table->Vector_Model_Variables,
					  Time_Current, Table);
#if defined CPGPLOT_REPRESENTATION
      Table->CPG->y_Time[k][j] = value;
#endif
      Table->Vector_Output_Variables[k]    = value;
      Table->Matrix_Output_Variables[k][j] = value;
    }
    
#if defined VERBOSE
    printf("t=%g\n", Time_Current);
    char * Label = (char *)calloc( 20, sizeof(char) );
    for (k=0; k < Table->MODEL_STATE_VARIABLES; k++) {
      AssignLabel_to_Model_Variables(k, Label, Table);
      printf("y[%s] = %g\n", Label, Table->Vector_Model_Variables[k]);
    }
    printf("\n");
    free(Label);
#endif
    /*   END: Writing costumized file        */

#if defined VERBOSE
      printf("t = %g\n", Current_Time);
      for(k=0; k < Table->SUB_OUTPUT_VARIABLES; k++){
	printf("\ty[%d]=%g", k,Table->Vector_Output_Variables[k]);
      }
      printf("\n"); Press_Key();
#endif
  }/* ------> go further to the next time step */

  if (State != GSL_SUCCESS) printf(" Numerical integration failed at the %dth time\n", j);

  return(State);
}

void Fixing_System_State (double * Y, Parameter_Table * Table, double ** Data, int j)
{
  int i;
  double g_H, E_x, x, y;

  /* Definition of the state vector numerical order, from 0 to K, of model variables */
#include <Model_Variables_Code.Include.c>

  /* Initial conditions from empirical data at the initial time ( -xn 0 ) */
  double Female_Sexual_Worker_Population; 
  double Female_Non_Sexual_Worker_Population;
  double Female_Sexual_Worker_Population_Infected;
  double Female_Sexual_Worker_Population_Non_Infected;
  double Male_Population_Infected;
  double Male_Population_Non_Infected; 
  
  Table->INITIAL_TOTAL_POPULATION          = Data[0][j];
  Female_Sexual_Worker_Population          = Data[1][j];
  Female_Sexual_Worker_Population_Infected = Data[2][j];
  
    
  Female_Non_Sexual_Worker_Population = Table->INITIAL_TOTAL_POPULATION/2.0 - Female_Sexual_Worker_Population; 

  Female_Sexual_Worker_Population_Non_Infected = Female_Sexual_Worker_Population - Female_Sexual_Worker_Population_Infected; 

  Male_Population_Infected = 0.1 * Female_Sexual_Worker_Population_Infected;
  
  Male_Population_Non_Infected = Table->INITIAL_TOTAL_POPULATION/2.0 - Male_Population_Infected;

  Y[YS] = Male_Population_Non_Infected; 
  Y[YI] = 1.0/3.0 * Male_Population_Infected;
  Y[YL] = 1.0/3.0 * Male_Population_Infected;
  Y[YD] = 1.0/3.0 * Male_Population_Infected;
  
  Y[X0S] = 0.9997 * 1.0/5.0 * Female_Non_Sexual_Worker_Population;
  Y[X0I] = 0.0001 * 1.0/5.0 * Female_Non_Sexual_Worker_Population;
  Y[X0L] = 0.0001 * 1.0/5.0 * Female_Non_Sexual_Worker_Population;
  Y[X0D] = 0.0001 * 1.0/5.0 * Female_Non_Sexual_Worker_Population;
  
  Y[W0S] = 1.0/5.0 * Female_Sexual_Worker_Population_Non_Infected; 
  Y[W0I] = 1.0/5.0 * 1.0/3.0 * Female_Sexual_Worker_Population_Infected;
  Y[W0L] = 1.0/5.0 * 1.0/3.0 * Female_Sexual_Worker_Population_Infected;
  Y[W0D] = 1.0/5.0 * 1.0/3.0 * Female_Sexual_Worker_Population_Infected;
  
  Y[X1S] = 0.9997 * 4.0/5.0 * Female_Non_Sexual_Worker_Population; 
  Y[X1I] = 0.0001 * 4.0/5.0 * Female_Non_Sexual_Worker_Population;
  Y[X1L] = 0.0001 * 4.0/5.0 * Female_Non_Sexual_Worker_Population;
  Y[X1D] = 0.0001 * 4.0/5.0 * Female_Non_Sexual_Worker_Population;
  
  Y[W1S] = 4.0/5.0 * Female_Sexual_Worker_Population_Non_Infected; 
  Y[W1I] = 4.0/5.0 * 1.0/3.0 * Female_Sexual_Worker_Population_Infected;
  Y[W1L] = 4.0/5.0 * 1.0/3.0 * Female_Sexual_Worker_Population_Infected;
  Y[W1D] = 4.0/5.0 * 1.0/3.0 * Female_Sexual_Worker_Population_Infected;
}
