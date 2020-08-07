#include <MODEL.h>

extern gsl_rng * r;

void Initial_Condition_from_Parameter_Table(Parameter_Table * Table, double *Y)
{
 
  /* Definition of the state vector numerical order, from 0 to K, of model variables */
#include <Model_Variables_Code.Include.c>
  
  Y[XS] = Table->XS__0; 
  Y[XI] = Table->XI__0;
  Y[XL] = Table->XL__0;
  Y[XD] = Table->XD__0;
  
  Y[WS] = Table->WS__0; 
  Y[WI] = Table->WI__0; 
  Y[WL] = Table->WL__0;
  Y[WD] = Table->WD__0;
  
  Y[YS]  = Table->YS__0;
  Y[YI]  = Table->YI__0;
  Y[YL]  = Table->YL__0;
  Y[YD]  = Table->YD__0;

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
    Table->XS__0 = Y[XS]; 
    Table->XI__0 = Y[XI];
    Table->XL__0 = Y[XL];
    Table->XD__0 = Y[XD];
  
    Table->WS__0 = Y[WS]; 
    Table->WI__0 = Y[WI]; 
    Table->WL__0 = Y[WL];
    Table->WD__0 = Y[WD];
  
    Table->YS__0 = Y[YS];
    Table->YI__0 = Y[YI];
    Table->YL__0 = Y[YL];
    Table->YD__0 = Y[YD];
}

void Initial_Condition_from_Data_into_Parameter_Table (Parameter_Table * Table, double ** Data)
{
  /* Initial conditions from empirical data at the initial time ( -xn 0 ) */
  
    Table->INITIAL_TOTAL_POPULATION = Data[0][0];

    Table->YS__0 = Table->INITIAL_TOTAL_POPULATION/2.0;
    Table->YI__0 = 0.0;
    Table->YL__0 = 0.0;
    Table->YD__0 = 0.0;

    Table->XS__0 = 0.9999 * Table->INITIAL_TOTAL_POPULATION/2.0;
    Table->XI__0 = 1.0/3.0 * 0.0001 * Table->INITIAL_TOTAL_POPULATION/4.0;;
    Table->XL__0 = 1.0/3.0 * 0.0001 * Table->INITIAL_TOTAL_POPULATION/4.0;;
    Table->XD__0 = 1.0/3.0 * 0.0001 * Table->INITIAL_TOTAL_POPULATION/4.0;;

    Table->WS__0 = 0.9999 * Table->INITIAL_TOTAL_POPULATION/4.0;
    Table->WI__0 = 1.0/3.0 * 0.0001 * Table->INITIAL_TOTAL_POPULATION/4.0;;
    Table->WL__0 = 1.0/3.0 * 0.0001 * Table->INITIAL_TOTAL_POPULATION/4.0;;
    Table->WD__0 = 1.0/3.0 * 0.0001 * Table->INITIAL_TOTAL_POPULATION/4.0;;
}


