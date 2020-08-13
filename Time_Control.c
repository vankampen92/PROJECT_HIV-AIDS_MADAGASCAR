#include <MODEL.h>

#include <include.Time_Control.extern.h>

void T_I_M_E___C_O_N_T_R_O_L___A_L_L_O_C( Time_Control * Time, Parameter_Table * P, int I_Time)
{
  int i;

#if defined VERBOSE
  printf(" Time_Control is being allocated: \n");
  printf(" Several sets of %d output variables of length %d points will allocated\n",
	 P->SUB_OUTPUT_VARIABLES, I_Time);
#endif

  Time->AVE = (double **)calloc(P->SUB_OUTPUT_VARIABLES, sizeof(double *));
  for(i = 0; i<P->SUB_OUTPUT_VARIABLES; i++){
    Time->AVE[i]       = (double *)calloc( I_Time, sizeof(double) );
  }


  Time->VAR = (double **)calloc(P->SUB_OUTPUT_VARIABLES, sizeof(double *));
  for(i = 0; i<P->SUB_OUTPUT_VARIABLES; i++){
    Time->VAR[i]       = (double *)calloc( I_Time, sizeof(double) );
  }

  Time->time_DEF = (double *)calloc( I_Time, sizeof(double) );

  Time->count = (int *)calloc( I_Time, sizeof( int ) );

  Time->Time_Vector = (double *)calloc( I_Time, sizeof(double) );

  Time->summ = (double **)calloc(P->SUB_OUTPUT_VARIABLES, sizeof(double *));
  for(i = 0; i<P->SUB_OUTPUT_VARIABLES; i++){
    Time->summ[i]       = (double *)calloc( I_Time, sizeof(double) );
  }

#if defined VERBOSE
  printf(" Time_Control is being allocated: \n");
  printf(" %d output variables of length %d points will allocated\n", P->SUB_OUTPUT_VARIABLES, I_Time);
#endif

  Time->summ_var   = (double **)calloc( P->SUB_OUTPUT_VARIABLES, sizeof(double *) );
  for (i=0; i<P->SUB_OUTPUT_VARIABLES; i++){
    Time->summ_var[i]   = (double *)calloc( I_Time, sizeof(double) );
  }

  // Time->Rate = (Stochastic_Rate *)calloc( 1, sizeof(Stochastic_Rate) );

#if defined VERBOSE
  printf(" Time_Control is being allocated: \n");
  printf(" %d stochastic realizations of length %d points will allocated\n", P->Realizations, I_Time);
#endif

  Time->Accumulated_Variable = (double **)calloc( P->Realizations, sizeof(double *) );
  for (i=0; i<P->Realizations; i++){
    Time->Accumulated_Variable[i] = (double *)calloc( I_Time, sizeof(double) );
  }
}

void  T_I_M_E___C_O_N_T_R_O_L___U_P_L_O_A_D( Time_Control * Time, Parameter_Table * Table,
					     int I_Time)
{
  /* Setup for the vector of sampling times */
  int i;

  Time->EPSILON = EPSILON;
  Time->I_Time  = I_Time;

  Time->Time_0  = Time_0;
  Time->Time_1  = Time_1;
  
  Time->TYPE_of_TIME_DEPENDENCE = TYPE_of_TIME_DEPENDENCE;
  Time->Time_Scale_Unit = Time_Scale_Unit;
  Time->Delta_T = Delta_T; 

  Time->Realizations = Realizations;
  
  for(i=0; i<I_Time; i++){
    Time->Time_Vector[i] = Time->Time_0 + (double)i * (Time->Time_1 - Time->Time_0)/(double)(I_Time-1);
    Time->count[i]       = 0;
  }
  /* so that Time_Vector[0] = Time_0 and  Time_Vector[I_Time-1] = Time_1. In this way, time series
     have I_Time points, where the first point always corresponds to Time_0 and the last to Time_1;
  */

  Table->T = Time;
}

void T_I_M_E___C_O_N_T_R_O_L___F_R_E_E( Time_Control * Time, Parameter_Table * P )
{
  int i;

  free (Time->time_DEF);

  for(i = 0; i<P->SUB_OUTPUT_VARIABLES; i++){
    free (Time->AVE[i]);
  }
  free (Time->AVE);
  for(i = 0; i<P->SUB_OUTPUT_VARIABLES; i++){
    free (Time->VAR[i]);
  }
  free (Time->VAR);

  free (Time->Time_Vector);

  free (Time->count );

  for(i = 0; i<P->SUB_OUTPUT_VARIABLES; i++){
    free (Time->summ[i]);
  }
  free (Time->summ);

  for (i=0; i<P->SUB_OUTPUT_VARIABLES; i++){
    free(Time->summ_var[i]);
  }
  free (Time->summ_var);

  for (i=0; i<P->Realizations; i++){
    free (Time->Accumulated_Variable[i]);
  }
  free (Time->Accumulated_Variable);

  // free (Time->Rate);
}
