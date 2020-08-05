#include <MODEL.h>

extern gsl_rng * r;

void Initial_Condition_from_Parameter_Table(Parameter_Table * Table, double *Y)
{
 
  /* Definition of the state vector numerical order, from 0 to K, of model variables */
#include <Model_Variables_Code.Include.c>
  
  Y[XS]  = Table->XS__0; 
    
  Y[YS]  = Table->YS__0;

  if(Table->RESCALING_INITIAL_TOTAL_POPULATION == 1)
    R_E_S_C_A_L_I_N_G___I_N_I_T_I_A_L___C_O_N_D_I_T_I_O_N_S ( Table, Y );
}
  
void R_E_S_C_A_L_I_N_G___I_N_I_T_I_A_L___C_O_N_D_I_T_I_O_N_S ( Parameter_Table * Table, 
							       double * Y)
{
    int i;
    double g_H, E_x, x, y;
   
    /* Definition of the state vector numerical order, from 0 to K, of model variables */
#include <Model_Variables_Code.Include.c>
    
    y = 0.0;
    for( i = 0; i <= K; i++ ) y += Y[i]; 
    for( i = 0; i <= K; i++ ) Y[i] = Y[i]/y * Table->INITIAL_TOTAL_POPULATION;
    
    /* g_H  = Table->n_H * Table->H_Gamma /(Table->n_H * Table->H_Gamma + Table->H_Delta);             */
    /* x    = ( 1.0 - g_H) / ( 1.0 - pow(g_H, (double)(Table->n_H)) ) ;                */
    /* E_x  = Y[E] * x;                                                            */
    
    /* Y[E] = E_x;                                                    /\* E_1 *\/  */
    /* for(i=1+E; i < I; i++) Y[i] = pow(g_H, (double)(i-1)) * E_x;  /\* E_n *\/   */
    
    /* Rescaled (Corrected) Initial Conditions */
    Table->XS__0 = Y[XS]; 
    
    Table->YS__0 = Y[YS];
}

void Initial_Condition_from_Data_into_Parameter_Table (Parameter_Table * Table, double ** Data)
{
  /* Initial conditions from empirical data at the initial time ( -xn 0 ) */
  
    Table->INITIAL_TOTAL_POPULATION = Data[0][0];
    
    Table->XS__0 = Data[0][0]/2.0;
    Table->YS__0 = Data[0][0]/2.0; 
}

void Initial_Condition_from_Sex_Biased_Data_into_Parameter_Table (Parameter_Table * Table,
								  double ** Data,
								  double x0_Factor,
								  double y0_Factor )
{
  /* Initial conditions from empirical data at the initial time ( -xn 0 ) */
  
    Table->INITIAL_TOTAL_POPULATION = Data[0][0];
    
    Table->XS__0 = Data[0][0] * x0_Factor;
    Table->YS__0 = Data[0][0] * y0_Factor;  
}

void Initial_Condition_from_Value_into_Parameter_Table (Parameter_Table * Table, double Value)
{
  /* Initial conditions from empirical data at the initial time ( -xn 0 ) */
  
    Table->INITIAL_TOTAL_POPULATION = Value;
    
    Table->XS__0 = Value/2.0;
    Table->YS__0 = Value/2.0; 
}
