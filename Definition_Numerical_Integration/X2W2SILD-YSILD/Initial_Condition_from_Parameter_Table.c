#include <MODEL.h>

extern gsl_rng * r;

void Initial_Condition_from_Parameter_Table(Parameter_Table * Table, double *Y)
{

  /* Definition of the state vector numerical order, from 0 to K, of model variables */
  #include <Model_Variables_Code.Include.c>

  Y[YS]  = Table->YS__0;
  Y[YI]  = Table->YI__0;
  Y[YL]  = Table->YL__0;
  Y[YD]  = Table->YD__0;

  Y[X0S] = Table->X0S__0;
  Y[X0I] = Table->X0I__0;
  Y[X0L] = Table->X0L__0;
  Y[X0D] = Table->X0D__0;

  Y[W0S] = Table->W0S__0;
  Y[W0I] = Table->W0I__0;
  Y[W0L] = Table->W0L__0;
  Y[W0D] = Table->W0D__0;

  Y[X1S] = Table->X1S__0;
  Y[X1I] = Table->X1I__0;
  Y[X1L] = Table->X1L__0;
  Y[X1D] = Table->X1D__0;

  Y[W1S] = Table->W1S__0;
  Y[W1I] = Table->W1I__0;
  Y[W1L] = Table->W1L__0;
  Y[W1D] = Table->W1D__0;

  if(Table->RESCALING_INITIAL_TOTAL_POPULATION == 1)
    R_E_S_C_A_L_I_N_G___I_N_I_T_I_A_L___C_O_N_D_I_T_I_O_N_S ( Table, Y );

}

void R_E_S_C_A_L_I_N_G___I_N_I_T_I_A_L___C_O_N_D_I_T_I_O_N_S ( Parameter_Table * Table, double * Y)
{
    int i;
    double g_H, E_x, x, y;

    /* Definition of the state vector numerical order, from 0 to K, of model variables */
    #include <Model_Variables_Code.Include.c>

    assert(Table->n_Mu == 1);

    y = 0.0;
    for( i = 0; i <= K; i++ ) y += Y[i];
    for( i = 0; i <= K; i++ ) Y[i] = Y[i]/y * Table->INITIAL_TOTAL_POPULATION;

    /* g_H  = Table->n_H * Table->H_Gamma /(Table->n_H * Table->H_Gamma + Table->H_Delta);             */
    /* x    = ( 1.0 - g_H) / ( 1.0 - pow(g_H, (double)(Table->n_H)) ) ;                */
    /* E_x  = Y[E] * x;                                                            */

    /* Y[E] = E_x;                                                    /\* E_1 *\/  */
    /* for(i=1+E; i < I; i++) Y[i] = pow(g_H, (double)(i-1)) * E_x;  /\* E_n *\/   */

    /* Rescaled (Corrected) Initial Conditions */
    Table->YS__0 = Y[YS];
    Table->YI__0 = Y[YI];
    Table->YL__0 = Y[YL];
    Table->YD__0 = Y[YD];

    Table->X0S__0 = Y[X0S];
    Table->X0I__0 = Y[X0I];
    Table->X0L__0 = Y[X0L];
    Table->X0D__0 = Y[X0D];

    Table->W0S__0 = Y[W0S];
    Table->W0I__0 = Y[W0I];
    Table->W0L__0 = Y[W0L];
    Table->W0D__0 = Y[W0D];

    Table->X1S__0 = Y[X1S];
    Table->X1I__0 = Y[X1I];
    Table->X1L__0 = Y[X1L];
    Table->X1D__0 = Y[X1D];

    Table->W1S__0 = Y[W1S];
    Table->W1I__0 = Y[W1I];
    Table->W1L__0 = Y[W1L];
    Table->W1D__0 = Y[W1D];
}
     
void Initial_Condition_from_Data_into_Parameter_Table (Parameter_Table * Table, double ** Data)
{
  /* Initial conditions from empirical data at the initial time ( -xn 0 ) */
  double Female_Sexual_Worker_Population; 
  double Female_Non_Sexual_Worker_Population;
  double Female_Sexual_Worker_Population_Infected;
  double Female_Sexual_Worker_Population_Non_Infected;
  double Male_Population_Infected;
  double Male_Population_Non_Infected; 
  
    Table->INITIAL_TOTAL_POPULATION          = Data[0][0];
    Female_Sexual_Worker_Population          = Data[1][0];
    Female_Sexual_Worker_Population_Infected = Data[2][0];

    
    Female_Non_Sexual_Worker_Population = Table->INITIAL_TOTAL_POPULATION/2.0 - Female_Sexual_Worker_Population; 

    Female_Sexual_Worker_Population_Non_Infected = Female_Sexual_Worker_Population - Female_Sexual_Worker_Population_Infected; 

    Male_Population_Infected = 0.1 * Female_Sexual_Worker_Population_Infected;

    Male_Population_Non_Infected = Table->INITIAL_TOTAL_POPULATION/2.0 - Male_Population_Infected;

    Table->YS__0 = Male_Population_Non_Infected; 
    Table->YI__0 = 1.0/3.0 * Male_Population_Infected;
    Table->YL__0 = 1.0/3.0 * Male_Population_Infected;
    Table->YD__0 = 1.0/3.0 * Male_Population_Infected;
    
    Table->X0S__0 = 0.9997 * 1.0/5.0 * Female_Non_Sexual_Worker_Population;
    Table->X0I__0 = 0.0001 * 1.0/5.0 * Female_Non_Sexual_Worker_Population;
    Table->X0L__0 = 0.0001 * 1.0/5.0 * Female_Non_Sexual_Worker_Population;
    Table->X0D__0 = 0.0001 * 1.0/5.0 * Female_Non_Sexual_Worker_Population;

    Table->W0S__0 = 1.0/5.0 * Female_Sexual_Worker_Population_Non_Infected; 
    Table->W0I__0 = 1.0/5.0 * 1.0/3.0 * Female_Sexual_Worker_Population_Infected;
    Table->W0L__0 = 1.0/5.0 * 1.0/3.0 * Female_Sexual_Worker_Population_Infected;
    Table->W0D__0 = 1.0/5.0 * 1.0/3.0 * Female_Sexual_Worker_Population_Infected;

    Table->X1S__0 = 0.9997 * 4.0/5.0 * Female_Non_Sexual_Worker_Population; 
    Table->X1I__0 = 0.0001 * 4.0/5.0 * Female_Non_Sexual_Worker_Population;
    Table->X1L__0 = 0.0001 * 4.0/5.0 * Female_Non_Sexual_Worker_Population;
    Table->X1D__0 = 0.0001 * 4.0/5.0 * Female_Non_Sexual_Worker_Population;

    Table->W1S__0 = 4.0/5.0 * Female_Sexual_Worker_Population_Non_Infected; 
    Table->W1I__0 = 4.0/5.0 * 1.0/3.0 * Female_Sexual_Worker_Population_Infected;
    Table->W1L__0 = 4.0/5.0 * 1.0/3.0 * Female_Sexual_Worker_Population_Infected;
    Table->W1D__0 = 4.0/5.0 * 1.0/3.0 * Female_Sexual_Worker_Population_Infected;
}
     
void Initial_Condition_from_Initial_Values_into_Parameter_Table (Parameter_Table * Table,
								 double Initial_Adult_Population, double Initial_Female_Sexual_Workers, double Initial_Female_Sexual_Workers_Infected )
{
  /* Initial conditions from empirical data at the initial time ( -xn 0 ) */
  double Female_Sexual_Worker_Population; 
  double Female_Non_Sexual_Worker_Population;
  double Female_Sexual_Worker_Population_Infected;
  double Female_Sexual_Worker_Population_Non_Infected;
  double Male_Population_Infected;
  double Male_Population_Non_Infected; 
 
    Table->INITIAL_TOTAL_POPULATION          = Initial_Adult_Population;
    Female_Sexual_Worker_Population          = Initial_Female_Sexual_Workers;
    Female_Sexual_Worker_Population_Infected = Initial_Female_Sexual_Workers_Infected;

    
    Female_Non_Sexual_Worker_Population = Table->INITIAL_TOTAL_POPULATION/2.0 - Female_Sexual_Worker_Population; 

    Female_Sexual_Worker_Population_Non_Infected = Female_Sexual_Worker_Population - Female_Sexual_Worker_Population_Infected; 

    Male_Population_Infected = 0.1 * Female_Sexual_Worker_Population_Infected;

    Male_Population_Non_Infected = Table->INITIAL_TOTAL_POPULATION/2.0 - Male_Population_Infected;

    Table->YS__0 = Male_Population_Non_Infected; 
    Table->YI__0 = 1.0/3.0 * Male_Population_Infected;
    Table->YL__0 = 1.0/3.0 * Male_Population_Infected;
    Table->YD__0 = 1.0/3.0 * Male_Population_Infected;
    
    Table->X0S__0 = 0.9997 * 1.0/5.0 * Female_Non_Sexual_Worker_Population;
    Table->X0I__0 = 0.0001 * 1.0/5.0 * Female_Non_Sexual_Worker_Population;
    Table->X0L__0 = 0.0001 * 1.0/5.0 * Female_Non_Sexual_Worker_Population;
    Table->X0D__0 = 0.0001 * 1.0/5.0 * Female_Non_Sexual_Worker_Population;

    Table->W0S__0 = 1.0/5.0 * Female_Sexual_Worker_Population_Non_Infected; 
    Table->W0I__0 = 1.0/5.0 * 1.0/3.0 * Female_Sexual_Worker_Population_Infected;
    Table->W0L__0 = 1.0/5.0 * 1.0/3.0 * Female_Sexual_Worker_Population_Infected;
    Table->W0D__0 = 1.0/5.0 * 1.0/3.0 * Female_Sexual_Worker_Population_Infected;

    Table->X1S__0 = 0.9997 * 4.0/5.0 * Female_Non_Sexual_Worker_Population; 
    Table->X1I__0 = 0.0001 * 4.0/5.0 * Female_Non_Sexual_Worker_Population;
    Table->X1L__0 = 0.0001 * 4.0/5.0 * Female_Non_Sexual_Worker_Population;
    Table->X1D__0 = 0.0001 * 4.0/5.0 * Female_Non_Sexual_Worker_Population;

    Table->W1S__0 = 4.0/5.0 * Female_Sexual_Worker_Population_Non_Infected; 
    Table->W1I__0 = 4.0/5.0 * 1.0/3.0 * Female_Sexual_Worker_Population_Infected;
    Table->W1L__0 = 4.0/5.0 * 1.0/3.0 * Female_Sexual_Worker_Population_Infected;
    Table->W1D__0 = 4.0/5.0 * 1.0/3.0 * Female_Sexual_Worker_Population_Infected;
}

void Initial_Condition_from_Value_into_Parameter_Table (Parameter_Table * Table, double Value)
{
  /* Initial conditions from empirical data at the initial time ( -xn 0 ) */
  double Female_Sexual_Worker_Population; 
  double Female_Non_Sexual_Worker_Population;
  double Female_Sexual_Worker_Population_Infected;
  double Female_Sexual_Worker_Population_Non_Infected;
  double Male_Population_Infected;
  double Male_Population_Non_Infected; 

  Female_Sexual_Worker_Population = Value;
    
  Female_Non_Sexual_Worker_Population = Table->INITIAL_TOTAL_POPULATION/2.0 - Female_Sexual_Worker_Population; 

  Female_Sexual_Worker_Population_Infected = 0.001 * Value;

  Female_Sexual_Worker_Population_Non_Infected = Female_Sexual_Worker_Population - Female_Sexual_Worker_Population_Infected; 

  Male_Population_Infected = 0.01 * Female_Sexual_Worker_Population_Infected;

  Male_Population_Non_Infected = Table->INITIAL_TOTAL_POPULATION/2.0 - Male_Population_Infected;

  Table->YS__0 = Male_Population_Non_Infected; 
  Table->YI__0 = 1.0/3.0 * Male_Population_Infected;
  Table->YL__0 = 1.0/3.0 * Male_Population_Infected;
  Table->YD__0 = 1.0/3.0 * Male_Population_Infected;
    
  Table->X0S__0 = 0.9997 * 1.0/5.0 * Female_Non_Sexual_Worker_Population;
  Table->X0I__0 = 0.0001 * 1.0/5.0 * Female_Non_Sexual_Worker_Population;
  Table->X0L__0 = 0.0001 * 1.0/5.0 * Female_Non_Sexual_Worker_Population;
  Table->X0D__0 = 0.0001 * 1.0/5.0 * Female_Non_Sexual_Worker_Population;

  Table->W0S__0 = 1.0/5.0 * Female_Sexual_Worker_Population_Non_Infected; 
  Table->W0I__0 = 1.0/5.0 * 1.0/3.0 * Female_Sexual_Worker_Population_Infected;
  Table->W0L__0 = 1.0/5.0 * 1.0/3.0 * Female_Sexual_Worker_Population_Infected;
  Table->W0D__0 = 1.0/5.0 * 1.0/3.0 * Female_Sexual_Worker_Population_Infected;

  Table->X1S__0 = 0.9997 * 4.0/5.0 * Female_Non_Sexual_Worker_Population; 
  Table->X1I__0 = 0.0001 * 4.0/5.0 * Female_Non_Sexual_Worker_Population;
  Table->X1L__0 = 0.0001 * 4.0/5.0 * Female_Non_Sexual_Worker_Population;
  Table->X1D__0 = 0.0001 * 4.0/5.0 * Female_Non_Sexual_Worker_Population;

  Table->W1S__0 = 4.0/5.0 * Female_Sexual_Worker_Population_Non_Infected; 
  Table->W1I__0 = 4.0/5.0 * 1.0/3.0 * Female_Sexual_Worker_Population_Infected;
  Table->W1L__0 = 4.0/5.0 * 1.0/3.0 * Female_Sexual_Worker_Population_Infected;
  Table->W1D__0 = 4.0/5.0 * 1.0/3.0 * Female_Sexual_Worker_Population_Infected;
}

