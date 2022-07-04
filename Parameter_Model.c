#include "./Include/MODEL.h"

void Parameter_Model_Copy (Parameter_Model * P_Destination, Parameter_Model * P_Source)
{

  P_Destination->Beta_Y = P_Source->Beta_Y;   /* Total no of sexual contacts a male has per year     *//*  0 */
  P_Destination->p_XY    = P_Source->p_XY;      /* Male-to-Female transmission probability T(Y--->X)   *//*  1 */
  P_Destination->F_Y    = P_Source->F_Y;      /* Total no of males entering sexual age per year      *//*  2 */
  P_Destination->Delta_X  = P_Source->Delta_X;    /* Natural mortility percapita rate                    *//*  3 */
  P_Destination->Delta_Y  = P_Source->Delta_Y;    /* Natural mortility percapita rate                    *//*  4 */
  P_Destination->Gamma  = P_Source->Gamma;    /* Recovery rate into the quasi-latent phase           *//*  5 */
  P_Destination->Mu     = P_Source->Mu;       /* Break-down rate into the final phase (before death) *//*  6 */
  P_Destination->mDelta = P_Source->mDelta;   /* Disease-induced mortility relative increase         *//*  7 */
  P_Destination->Beta_X = P_Source->Beta_X;   /* Total no of sexual contacts a female has per year   *//*  8 */
  P_Destination->p_YX    = P_Source->p_YX;      /* Female-to-Male transmission probability T(X--->Y)   *//*  9 */
  P_Destination->Sigma_0 = P_Source->Sigma_0;    /* Transitial rate into the sexual worker stage        *//* 10 */
  P_Destination->Sigma_0_r= P_Source->Sigma_0_r;  /* Reversal rate back into the regural female stage    *//* 11 */
  P_Destination->Eta    = P_Source->Eta;      /* Contact rate relative increase for sexual workers   *//* 12 */
  P_Destination->F_X    = P_Source->F_X;      /* Total no of females entering sexual age per year    *//* 13 */
  P_Destination->n_Mu   = P_Source->n_Mu;     /* No of latent subclasses during quasi-latent phase   *//* 14 */
  P_Destination->Xhi    = P_Source->Xhi;      /* Transmision probability increase during acute phase *//* 15 */
  P_Destination->f_W    = P_Source->f_W;      /* Fraction of male sexual contacts with female sexual workers *//* 16 */
  P_Destination->f_0    = P_Source->f_0;      /* Fraction of male sexual contacts with young female *//* 17 */
  P_Destination->Sigma_1   = P_Source->Sigma_1;  /* Transition rate into the sexual worker stage (adult women)*//* 18 */
  P_Destination->Sigma_1_r = P_Source->Sigma_1_r; /* Reversak rate back into the regular female stage (adult women) *//* 19 */
  P_Destination->Alpha = P_Source->Alpha;     /* Transition rate from young to adult stage */ /* 20 */
  P_Destination->r_F   = P_Source->r_F;     /* r_Factor: Population fraction of reprductive females  *//* 21 */
  
  P_Destination->D_Sigma  = P_Source->D_Sigma;  /* Parameter introducing time-dependence in Sigma_0 and Sigma_1 */
  P_Destination->Sigmoidal_A0 = P_Source->Sigmoidal_A0; /* Parameter introducing time-dependence in Sigma_0 and Sigma_1 */ 
  P_Destination->Sigmoidal_L0 = P_Source->Sigmoidal_L0; /* Parameter introducing time-dependence in Sigma_0 and Sigma_1 */
  P_Destination->Sigmoidal_T0 = P_Source->Sigmoidal_T0; /* Parameter introducing time-dependence in Sigma_0 and Sigma */

  
  /* Parameters related to the initial conditions: */
  P_Destination->YS__0  = P_Source->YS__0;
  P_Destination->YI__0  = P_Source->YI__0;
  P_Destination->YL__0  = P_Source->YL__0;
  P_Destination->YD__0  = P_Source->YD__0;

  P_Destination->XS__0 = P_Source->XS__0;
  P_Destination->XI__0 = P_Source->XI__0;
  P_Destination->XL__0 = P_Source->XL__0;
  P_Destination->XD__0 = P_Source->XD__0;

  P_Destination->WS__0 = P_Source->WS__0;
  P_Destination->WI__0 = P_Source->WI__0;
  P_Destination->WL__0 = P_Source->WL__0;
  P_Destination->WD__0 = P_Source->WD__0;

  P_Destination->X0S__0 = P_Source->X0S__0;
  P_Destination->X0I__0 = P_Source->X0I__0;
  P_Destination->X0L__0 = P_Source->X0L__0;
  P_Destination->X0D__0 = P_Source->X0D__0;

  P_Destination->W0S__0 = P_Source->W0S__0;
  P_Destination->W0I__0 = P_Source->W0I__0;
  P_Destination->W0L__0 = P_Source->W0L__0;
  P_Destination->W0D__0 = P_Source->W0D__0;

  P_Destination->X1S__0 = P_Source->X1S__0;
  P_Destination->X1I__0 = P_Source->X1I__0;
  P_Destination->X1L__0 = P_Source->X1L__0;
  P_Destination->X1D__0 = P_Source->X1D__0;

  P_Destination->W1S__0 = P_Source->W1S__0;
  P_Destination->W1I__0 = P_Source->W1I__0;
  P_Destination->W1L__0 = P_Source->W1L__0;
  P_Destination->W1D__0 = P_Source->W1D__0;

  P_Destination->No_of_IC = P_Source->No_of_IC;
  P_Destination->TYPE_of_INITIAL_CONDITION = P_Source->TYPE_of_INITIAL_CONDITION;
  P_Destination->INITIAL_TOTAL_POPULATION  = P_Source->INITIAL_TOTAL_POPULATION;
  P_Destination->RESCALING_INITIAL_TOTAL_POPULATION = P_Source->RESCALING_INITIAL_TOTAL_POPULATION;


  P_Destination->TYPE_of_ERROR_FUNCTION = P_Source->TYPE_of_ERROR_FUNCTION;
  P_Destination->No_of_ERROR_PARAMETERS = P_Source->No_of_ERROR_PARAMETERS;

  P_Destination->Error_Parameter_0 = P_Source->Error_Parameter_0;
  P_Destination->Error_Parameter_1 = P_Source->Error_Parameter_1;

  P_Destination->Err_0 = P_Source->Err_0;
  P_Destination->Err_1 = P_Source->Err_1;
  P_Destination->Err_2 = P_Source->Err_2;
  P_Destination->Err_3 = P_Source->Err_3;
  P_Destination->Err_4 = P_Source->Err_4;
  P_Destination->Err_5 = P_Source->Err_5;
  P_Destination->Err_6 = P_Source->Err_6;
  P_Destination->Err_7 = P_Source->Err_7;
  P_Destination->Err_8 = P_Source->Err_8;
  P_Destination->Err_9 = P_Source->Err_9;
  P_Destination->Err_10 = P_Source->Err_11;
  P_Destination->Err_11 = P_Source->Err_11;
  P_Destination->Err_12 = P_Source->Err_12;
  P_Destination->Err_13 = P_Source->Err_13;
  P_Destination->Err_14 = P_Source->Err_14;
  P_Destination->Err_15 = P_Source->Err_15;
  P_Destination->Err_16 = P_Source->Err_16;

  
  P_Destination->MODEL_OUTPUT_VARIABLES = P_Source->MODEL_OUTPUT_VARIABLES;   /* Actual no of MODEL (output) VARIABLES */
  P_Destination->MODEL_INPUT_PARAMETERS = P_Source->MODEL_INPUT_PARAMETERS;  /* Actual no of MODEL (input) PARAMETERS */
  P_Destination->MODEL_STATE_VARIABLES  = P_Source->MODEL_STATE_VARIABLES;  /* Actual no of MODEL (state) VARIABLES  */

  P_Destination->TYPE_of_MODEL        = P_Source->TYPE_of_MODEL;
  P_Destination->Growth_Function_Type = P_Source->Growth_Function_Type;

  //P_Destination->Time_Scale_Unit      = Table->T->Time_Scale_Unit;
}

void  P_A_R_A_M_E_T_E_R___I_N_I_T_I_A_L_I_Z_A_T_I_O_N ( Parameter_Table * Table,
							Parameter_Model * P )
{
  /* This function transfer a subset of table parameters
     into the Parameter_Model structure. Parameter_Model parameters
     control the dynamical model.
  */
  P->Beta_Y = Table->Beta_Y;   /* Total no of sexual contacts a male has per year     *//*  0 */
  P->p_XY    = Table->p_XY;      /* Male-to-Female transmission probability T(Y--->X)   *//*  1 */
  P->F_Y    = Table->F_Y;      /* Total no of males entering sexual age per year      *//*  2 */
  P->Delta_X  = Table->Delta_X;    /* Natural mortility percapita rate                    *//*  3 */
  P->Delta_Y  = Table->Delta_Y;    /* Natural mortility percapita rate                    *//*  4 */
  P->Gamma  = Table->Gamma;    /* Recovery rate into the quasi-latent phase           *//*  5 */
  P->Mu     = Table->Mu;       /* Break-down rate into the final phase (before death) *//*  6 */
  P->mDelta = Table->mDelta;   /* Disease-induced mortility relative increase         *//*  7 */
  P->Beta_X = Table->Beta_X;   /* Total no of sexual contacts a female has per year   *//*  8 */
  P->p_YX    = Table->p_YX;      /* Female-to-Male transmission probability T(X--->Y)   *//*  9 */
  P->Sigma_0  = Table->Sigma_0;    /* Transitial rate into the sexual worker stage        *//* 10 */
  P->Sigma_0_r= Table->Sigma_0_r;  /* Reversal rate back into the regural female stage    *//* 11 */
  P->Eta    = Table->Eta;      /* Contact rate relative increase for sexual workers   *//* 12 */
  P->F_X    = Table->F_X;      /* Total no of females entering sexual age per year    *//* 13 */
  P->n_Mu   = Table->n_Mu;     /* No of latent subclasses during quasi-latent phase   *//* 14 */
  P->Xhi    = Table->Xhi;      /* Transmision probability increase during acute phase *//* 15 */
  P->f_W    = Table->f_W;      /* Fraction of male sexual contacts with female sexual workers *//* 16 */
  P->f_0    = Table->f_0;      /* Fraction of male sexual contacts with young female *//* 17 */
  P->Sigma_1   = Table->Sigma_1;  /* Transition rate into the sexual worker stage (adult women)*//* 18 */
  P->Sigma_1_r = Table->Sigma_1_r; /* Reversak rate back into the regular female stage (adult women) *//* 19 */
  P->Alpha = Table->Alpha;     /* Transition rate from young to adult stage */ /* 20 */
  P->r_F   = Table->r_F;     /* r_Factor: Population fraction of reprductive females  *//* 21 */

  P->D_Sigma  = Table->D_Sigma;  /* Parameter introducing time-dependence in Sigma_0 and Sigma_1 */
  P->Sigmoidal_A0 = Table->Sigmoidal_A0; /* Parameter introducing time-dependence in Sigma_0 and Sigma_1 */ 
  P->Sigmoidal_L0 = Table->Sigmoidal_L0; /* Parameter introducing time-dependence in Sigma_0 and Sigma_1 */
  P->Sigmoidal_T0 = Table->Sigmoidal_T0; /* Parameter introducing time-dependence in Sigma_0 and Sigma_1*/
  
  /* Parameters related to the initial conditions: */
  P->XS__0 = Table->XS__0;
  P->XI__0 = Table->XI__0;
  P->XL__0 = Table->XL__0;
  P->XD__0 = Table->XD__0;

  P->WS__0 = Table->WS__0;
  P->WI__0 = Table->WI__0;
  P->WL__0 = Table->WL__0;
  P->WD__0 = Table->WD__0;

  P->YS__0  = Table->YS__0;
  P->YI__0  = Table->YI__0;
  P->YL__0  = Table->YL__0;
  P->YD__0  = Table->YD__0;

  P->X0S__0 = Table->X0S__0;
  P->X0I__0 = Table->X0I__0;
  P->X0L__0 = Table->X0L__0;
  P->X0D__0 = Table->X0D__0;

  P->W0S__0 = Table->W0S__0;
  P->W0I__0 = Table->W0I__0;
  P->W0L__0 = Table->W0L__0;
  P->W0D__0 = Table->W0D__0;

  P->X1S__0 = Table->X1S__0;
  P->X1I__0 = Table->X1I__0;
  P->X1L__0 = Table->X1L__0;
  P->X1D__0 = Table->X1D__0;

  P->W1S__0 = Table->W1S__0;
  P->W1I__0 = Table->W1I__0;
  P->W1L__0 = Table->W1L__0;
  P->W1D__0 = Table->W1D__0;

  P->No_of_IC = Table->No_of_IC;
  P->TYPE_of_INITIAL_CONDITION = Table->TYPE_of_INITIAL_CONDITION;
  P->INITIAL_TOTAL_POPULATION  = Table->INITIAL_TOTAL_POPULATION;
  P->RESCALING_INITIAL_TOTAL_POPULATION = Table->RESCALING_INITIAL_TOTAL_POPULATION;


  P->TYPE_of_ERROR_FUNCTION = Table->TYPE_of_ERROR_FUNCTION;
  P->No_of_ERROR_PARAMETERS = Table->No_of_ERROR_PARAMETERS;
  P->Error_Parameter_0 = Table->Error_Parameter_0;
  P->Error_Parameter_1 = Table->Error_Parameter_1;
  
  P->Err_0 = Table->Err_0;
  P->Err_1 = Table->Err_1;
  P->Err_2 = Table->Err_2;
  P->Err_3 = Table->Err_3;
  P->Err_4 = Table->Err_4;
  P->Err_5 = Table->Err_5;
  P->Err_6 = Table->Err_6;
  P->Err_7 = Table->Err_7;
  P->Err_8 = Table->Err_8;
  P->Err_9 = Table->Err_9;
  P->Err_10 = Table->Err_11;
  P->Err_11 = Table->Err_11;
  P->Err_12 = Table->Err_12;
  P->Err_13 = Table->Err_13;
  P->Err_14 = Table->Err_14;
  P->Err_15 = Table->Err_15;
  P->Err_16 = Table->Err_16;


  P->MODEL_OUTPUT_VARIABLES = Table->MODEL_OUTPUT_VARIABLES;   /* Actual no of MODEL (output) VARIABLES */
  P->MODEL_INPUT_PARAMETERS = Table->MODEL_INPUT_PARAMETERS;  /* Actual no of MODEL (input) PARAMETERS */
  P->MODEL_STATE_VARIABLES  = Table->MODEL_STATE_VARIABLES;  /* Actual no of MODEL (state) VARIABLES  */

  P->TYPE_of_MODEL        = Table->TYPE_of_MODEL;
  P->Growth_Function_Type = Table->Growth_Function_Type;

  //P->Time_Scale_Unit      = Table->T->Time_Scale_Unit;
}

void Parameter_Model_Copy_into_Parameter_Table (Parameter_Table * P_Destination, Parameter_Model * P_Source)
{

  P_Destination->Beta_Y = P_Source->Beta_Y;   /* Total no of sexual contacts a male has per year     *//*  0 */
  P_Destination->p_XY    = P_Source->p_XY;      /* Male-to-Female transmission probability T(Y--->X)   *//*  1 */
  P_Destination->F_Y    = P_Source->F_Y;      /* Total no of males entering sexual age per year      *//*  2 */
  P_Destination->Delta_X  = P_Source->Delta_X;    /* Natural mortility percapita rate                    *//*  3 */
  P_Destination->Delta_Y  = P_Source->Delta_Y;    /* Natural mortility percapita rate                    *//*  4 */
  P_Destination->Gamma  = P_Source->Gamma;    /* Recovery rate into the quasi-latent phase           *//*  5 */
  P_Destination->Mu     = P_Source->Mu;       /* Break-down rate into the final phase (before death) *//*  6 */
  P_Destination->mDelta = P_Source->mDelta;   /* Disease-induced mortility relative increase         *//*  7 */
  P_Destination->Beta_X = P_Source->Beta_X;   /* Total no of sexual contacts a female has per year   *//*  8 */
  P_Destination->p_YX    = P_Source->p_YX;      /* Female-to-Male transmission probability T(X--->Y)   *//*  9 */
  P_Destination->Sigma_0  = P_Source->Sigma_0;    /* Transitial rate into the sexual worker stage        *//* 10 */
  P_Destination->Sigma_0_r= P_Source->Sigma_0_r;  /* Reversal rate back into the regural female stage    *//* 11 */
  P_Destination->Eta    = P_Source->Eta;      /* Contact rate relative increase for sexual workers   *//* 12 */
  P_Destination->F_X    = P_Source->F_X;      /* Total no of females entering sexual age per year    *//* 13 */
  P_Destination->n_Mu   = P_Source->n_Mu;     /* No of latent subclasses during quasi-latent phase   *//* 14 */
  P_Destination->Xhi    = P_Source->Xhi;      /* Transmision probability increase during acute phase *//* 15 */
  P_Destination->f_W    = P_Source->f_W;      /* Fraction of male sexual contacts with female sexual workers *//* 16 */
  P_Destination->f_0    = P_Source->f_0;      /* Fraction of male sexual contacts with young female *//* 17 */
  P_Destination->Sigma_1   = P_Source->Sigma_1;  /* Transition rate into the sexual worker stage (adult women)*//* 18 */
  P_Destination->Sigma_1_r = P_Source->Sigma_1_r; /* Reversak rate back into the regular female stage (adult women) *//* 19 */
  P_Destination->Alpha = P_Source->Alpha;     /* Transition rate from young to adult stage */ /* 20 */
  P_Destination->r_F   = P_Source->r_F;     /* r_Factor: Population fraction of reprductive females  *//* 21 */
  P_Destination->D_Sigma  = P_Source->D_Sigma;  /* Parameter introducing time-dependence in Sigma_0 and Sigma_1 */
  P_Destination->Sigmoidal_A0 = P_Source->Sigmoidal_A0; /* Parameter introducing time-dependence in Sigma_0 and Sigma_1 */ 
  P_Destination->Sigmoidal_L0 = P_Source->Sigmoidal_L0; /* Parameter introducing time-dependence in Sigma_0 and Sigma_1 */
  P_Destination->Sigmoidal_T0 = P_Source->Sigmoidal_T0; /* Parameter introducing time-dependence in Sigma_0 and Sigma_1 */

  
  /* Parameters related to the initial conditions: */
  P_Destination->XS__0 = P_Source->XS__0;
  P_Destination->XI__0 = P_Source->XI__0;
  P_Destination->XL__0 = P_Source->XL__0;
  P_Destination->XD__0 = P_Source->XD__0;

  P_Destination->WS__0 = P_Source->WS__0;
  P_Destination->WI__0 = P_Source->WI__0;
  P_Destination->WL__0 = P_Source->WL__0;
  P_Destination->WD__0 = P_Source->WD__0;

  P_Destination->YS__0  = P_Source->YS__0;
  P_Destination->YI__0  = P_Source->YI__0;
  P_Destination->YL__0  = P_Source->YL__0;
  P_Destination->YD__0  = P_Source->YD__0;

  P_Destination->X0S__0 = P_Source->X0S__0;
  P_Destination->X0I__0 = P_Source->X0I__0;
  P_Destination->X0L__0 = P_Source->X0L__0;
  P_Destination->X0D__0 = P_Source->X0D__0;

  P_Destination->W0S__0 = P_Source->W0S__0;
  P_Destination->W0I__0 = P_Source->W0I__0;
  P_Destination->W0L__0 = P_Source->W0L__0;
  P_Destination->W0D__0 = P_Source->W0D__0;

  P_Destination->X1S__0 = P_Source->X1S__0;
  P_Destination->X1I__0 = P_Source->X1I__0;
  P_Destination->X1L__0 = P_Source->X1L__0;
  P_Destination->X1D__0 = P_Source->X1D__0;

  P_Destination->W1S__0 = P_Source->W1S__0;
  P_Destination->W1I__0 = P_Source->W1I__0;
  P_Destination->W1L__0 = P_Source->W1L__0;
  P_Destination->W1D__0 = P_Source->W1D__0;

  P_Destination->No_of_IC = P_Source->No_of_IC;
  P_Destination->TYPE_of_INITIAL_CONDITION = P_Source->TYPE_of_INITIAL_CONDITION;
  P_Destination->INITIAL_TOTAL_POPULATION  = P_Source->INITIAL_TOTAL_POPULATION;
  P_Destination->RESCALING_INITIAL_TOTAL_POPULATION = P_Source->RESCALING_INITIAL_TOTAL_POPULATION;


  P_Destination->TYPE_of_ERROR_FUNCTION = P_Source->TYPE_of_ERROR_FUNCTION;
  P_Destination->No_of_ERROR_PARAMETERS = P_Source->No_of_ERROR_PARAMETERS;
  P_Destination->Error_Parameter_0 = P_Source->Error_Parameter_0;
  P_Destination->Error_Parameter_1 = P_Source->Error_Parameter_1;
  
  P_Destination->Err_0 = P_Source->Err_0;
  P_Destination->Err_1 = P_Source->Err_1;
  P_Destination->Err_2 = P_Source->Err_2;
  P_Destination->Err_3 = P_Source->Err_3;
  P_Destination->Err_4 = P_Source->Err_4;
  P_Destination->Err_5 = P_Source->Err_5;
  P_Destination->Err_6 = P_Source->Err_6;
  P_Destination->Err_7 = P_Source->Err_7;
  P_Destination->Err_8 = P_Source->Err_8;
  P_Destination->Err_9 = P_Source->Err_9;
  P_Destination->Err_10 = P_Source->Err_11;
  P_Destination->Err_11 = P_Source->Err_11;
  P_Destination->Err_12 = P_Source->Err_12;
  P_Destination->Err_13 = P_Source->Err_13;
  P_Destination->Err_14 = P_Source->Err_14;
  P_Destination->Err_15 = P_Source->Err_15;
  P_Destination->Err_16 = P_Source->Err_16; 
  
  P_Destination->MODEL_OUTPUT_VARIABLES = P_Source->MODEL_OUTPUT_VARIABLES;   /* Actual no of MODEL (output) VARIABLES */
  P_Destination->MODEL_INPUT_PARAMETERS = P_Source->MODEL_INPUT_PARAMETERS;  /* Actual no of MODEL (input) PARAMETERS */
  P_Destination->MODEL_STATE_VARIABLES  = P_Source->MODEL_STATE_VARIABLES;  /* Actual no of MODEL (state) VARIABLES  */

  P_Destination->TYPE_of_MODEL        = P_Source->TYPE_of_MODEL;
  P_Destination->Growth_Function_Type = P_Source->Growth_Function_Type;

  //P->Time_Scale_Unit      = Table->T->Time_Scale_Unit;
}

void Parameter_Table_Copy_into_Parameter_Model (Parameter_Model * P_Destination, Parameter_Table * P_Source)
{

  P_Destination->Beta_Y = P_Source->Beta_Y;   /* Total no of sexual contacts a male has per year     *//*  0 */
  P_Destination->p_XY    = P_Source->p_XY;      /* Male-to-Female transmission probability T(Y--->X)   *//*  1 */
  P_Destination->F_Y    = P_Source->F_Y;      /* Total no of males entering sexual age per year      *//*  2 */
  P_Destination->Delta_X  = P_Source->Delta_X;    /* Natural mortility percapita rate                    *//*  3 */
  P_Destination->Delta_Y  = P_Source->Delta_Y;    /* Natural mortility percapita rate                    *//*  4 */
  P_Destination->Gamma  = P_Source->Gamma;    /* Recovery rate into the quasi-latent phase           *//*  5 */
  P_Destination->Mu     = P_Source->Mu;       /* Break-down rate into the final phase (before death) *//*  6 */
  P_Destination->mDelta = P_Source->mDelta;   /* Disease-induced mortility relative increase         *//*  7 */
  P_Destination->Beta_X = P_Source->Beta_X;   /* Total no of sexual contacts a female has per year   *//*  8 */
  P_Destination->p_YX    = P_Source->p_YX;      /* Female-to-Male transmission probability T(X--->Y)   *//*  9 */
  P_Destination->Sigma_0  = P_Source->Sigma_0;    /* Transitial rate into the sexual worker stage        *//* 10 */
  P_Destination->Sigma_0_r= P_Source->Sigma_0_r;  /* Reversal rate back into the regural female stage    *//* 11 */
  P_Destination->Eta    = P_Source->Eta;      /* Contact rate relative increase for sexual workers   *//* 12 */
  P_Destination->F_X    = P_Source->F_X;      /* Total no of females entering sexual age per year    *//* 13 */
  P_Destination->n_Mu   = P_Source->n_Mu;     /* No of latent subclasses during quasi-latent phase   *//* 14 */
  P_Destination->Xhi    = P_Source->Xhi;      /* Transmision probability increase during acute phase *//* 15 */
  P_Destination->f_W    = P_Source->f_W;      /* Fraction of male sexual contacts with female sexual workers *//* 16 */
  P_Destination->f_0    = P_Source->f_0;      /* Fraction of male sexual contacts with young female *//* 17 */
  P_Destination->Sigma_1   = P_Source->Sigma_1;  /* Transition rate into the sexual worker stage (adult women)*//* 18 */
  P_Destination->Sigma_1_r = P_Source->Sigma_1_r; /* Reversak rate back into the regular female stage (adult women) *//* 19 */
  P_Destination->Alpha = P_Source->Alpha;     /* Transition rate from young to adult stage */ /* 20 */
  P_Destination->r_F   = P_Source->r_F;     /* r_Factor: Population fraction of reprductive females  *//* 21 */
  P_Destination->D_Sigma  = P_Source->D_Sigma;  /* Parameter introducing time-dependence in Sigma_0 and Sigma_1 */
  P_Destination->Sigmoidal_A0 = P_Source->Sigmoidal_A0; /* Parameter introducing time-dependence in Sigma_0 and Sigma_1 */ 
  P_Destination->Sigmoidal_L0 = P_Source->Sigmoidal_L0; /* Parameter introducing time-dependence in Sigma_0 and Sigma_1 */
  P_Destination->Sigmoidal_T0 = P_Source->Sigmoidal_T0; /* Parameter introducing time-dependence in Sigma_0 and Sigma_1 */
  
  /* Parameters related to the initial conditions: */
  P_Destination->XS__0 = P_Source->XS__0;
  P_Destination->XI__0 = P_Source->XI__0;
  P_Destination->XL__0 = P_Source->XL__0;
  P_Destination->XD__0 = P_Source->XD__0;

  P_Destination->WS__0 = P_Source->WS__0;
  P_Destination->WI__0 = P_Source->WI__0;
  P_Destination->WL__0 = P_Source->WL__0;
  P_Destination->WD__0 = P_Source->WD__0;

  P_Destination->YS__0  = P_Source->YS__0;
  P_Destination->YI__0  = P_Source->YI__0;
  P_Destination->YL__0  = P_Source->YL__0;
  P_Destination->YD__0  = P_Source->YD__0;

  P_Destination->X0S__0 = P_Source->X0S__0;
  P_Destination->X0I__0 = P_Source->X0I__0;
  P_Destination->X0L__0 = P_Source->X0L__0;
  P_Destination->X0D__0 = P_Source->X0D__0;

  P_Destination->W0S__0 = P_Source->W0S__0;
  P_Destination->W0I__0 = P_Source->W0I__0;
  P_Destination->W0L__0 = P_Source->W0L__0;
  P_Destination->W0D__0 = P_Source->W0D__0;

  P_Destination->X1S__0 = P_Source->X1S__0;
  P_Destination->X1I__0 = P_Source->X1I__0;
  P_Destination->X1L__0 = P_Source->X1L__0;
  P_Destination->X1D__0 = P_Source->X1D__0;

  P_Destination->W1S__0 = P_Source->W1S__0;
  P_Destination->W1I__0 = P_Source->W1I__0;
  P_Destination->W1L__0 = P_Source->W1L__0;
  P_Destination->W1D__0 = P_Source->W1D__0;

  P_Destination->No_of_IC = P_Source->No_of_IC;
  P_Destination->TYPE_of_INITIAL_CONDITION = P_Source->TYPE_of_INITIAL_CONDITION;
  P_Destination->INITIAL_TOTAL_POPULATION  = P_Source->INITIAL_TOTAL_POPULATION;
  P_Destination->RESCALING_INITIAL_TOTAL_POPULATION = P_Source->RESCALING_INITIAL_TOTAL_POPULATION;


  P_Destination->TYPE_of_ERROR_FUNCTION = P_Source->TYPE_of_ERROR_FUNCTION;
  P_Destination->No_of_ERROR_PARAMETERS = P_Source->No_of_ERROR_PARAMETERS;
  P_Destination->Error_Parameter_0 = P_Source->Error_Parameter_0;
  P_Destination->Error_Parameter_1 = P_Source->Error_Parameter_1;

  P_Destination->Err_0 = P_Source->Err_0;
  P_Destination->Err_1 = P_Source->Err_1;
  P_Destination->Err_2 = P_Source->Err_2;
  P_Destination->Err_3 = P_Source->Err_3;
  P_Destination->Err_4 = P_Source->Err_4;
  P_Destination->Err_5 = P_Source->Err_5;
  P_Destination->Err_6 = P_Source->Err_6;
  P_Destination->Err_7 = P_Source->Err_7;
  P_Destination->Err_8 = P_Source->Err_8;
  P_Destination->Err_9 = P_Source->Err_9;
  P_Destination->Err_10 = P_Source->Err_11;
  P_Destination->Err_11 = P_Source->Err_11;
  P_Destination->Err_12 = P_Source->Err_12;
  P_Destination->Err_13 = P_Source->Err_13;
  P_Destination->Err_14 = P_Source->Err_14;
  P_Destination->Err_15 = P_Source->Err_15;
  P_Destination->Err_16 = P_Source->Err_16;

  P_Destination->MODEL_OUTPUT_VARIABLES = P_Source->MODEL_OUTPUT_VARIABLES;   /* Actual no of MODEL (output) VARIABLES */
  P_Destination->MODEL_INPUT_PARAMETERS = P_Source->MODEL_INPUT_PARAMETERS;  /* Actual no of MODEL (input) PARAMETERS */
  P_Destination->MODEL_STATE_VARIABLES  = P_Source->MODEL_STATE_VARIABLES;  /* Actual no of MODEL (state) VARIABLES  */

  P_Destination->TYPE_of_MODEL        = P_Source->TYPE_of_MODEL;
  P_Destination->Growth_Function_Type = P_Source->Growth_Function_Type;

  //P->Time_Scale_Unit      = Table->T->Time_Scale_Unit;
}

void Vector_Entries_into_Parameter_Model ( const gsl_vector * X, Parameter_Model * P,
					   int * Parameter_Index, int No_of_PARAMETERS )
{
  int i;
  int key;
  double value;

  for( i=0; i<No_of_PARAMETERS; i++) {
    key = Parameter_Index[i];
    value = gsl_vector_get(X, i);
    Vector_Entry_into_Parameter_Model ( value, key, P );
  }
}

void Vector_Entry_into_Parameter_Model ( double value, int key, Parameter_Model * P )
{

  switch (key) {
    case  0: P->Beta_Y = value;  /* Total no of sexual contacts a male has per year   *//*  0 */
      break;
    case  1: P->p_XY = value;     /* Male-to-Female transmission probability T(Y--->X) *//*  1 */
      break;
    case  2: P->F_Y = value;     /* Total no of males entering sexual age per year    *//*  2 */
      break;
    case  3: P->Delta_X = value;   /* Natural mortility percapita rate                  *//*  3 */
      break;
    case  4: P->Delta_Y = value;   /* Natural mortility percapita rate                  *//*  4 */
      break;
    case  5: P->Gamma = value;   /* Recovery rate into the quasi-latent phase         *//*  5 */
      break;
    case  6: P->Mu = value;     /* Break-down rate into the final phase (before death) *//*  6 */
      break;
    case  7: P->mDelta = value; /* Disease-induced mortility relative increase         *//*  7 */
      break;
    case  8: P->Beta_X = value; /* Total no of sexual contacts a female has per year   *//*  8 */
      break;
    case  9: P->p_YX = value;    /* Female-to-Male transmission probability T(X--->Y)   *//*  9 */
      break;
    case 10: P->Sigma_0 = value;  /* Transitional rate into the sexual worker stage      *//*  10 */
      break;
    case 11: P->Sigma_0_r = value; /* Reversal rate back into the regural female stage    *//* 11 */
      break;
    case 12: P->Eta = value;    /* Contact rate relative increase for sexual workers   *//* 12 */
      break;
    case 13: P->F_X = value;    /* Total no of females entering sexual age per year    *//* 13 */
      break;
    case 14: P->n_Mu = (int)value; /* No of latent subclasses during quasi-latent phase   *//* 14 */
      break;
    case 15: P->Xhi = value;    /* Transmision probability increase during acute phase *//* 15 */
      break;
    case 16: P->f_W = value;    /* Fraction of male sexual contacts with female sexual workers*//* 16 */
      break;
    case 17: P->f_0 = value;    /* Fraction of male sexual contacts with young females *//* 17 */
      break;
    case 18: P->Sigma_1 = value;  /* Transition rate into the sexual worker stage for old females *//*  18 */
      break;
    case 19: P->Sigma_1_r = value; /* Reversal rate back into the regural female stage for old females *//* 19 */
      break;
    case 20: P->Alpha = value;    /* Transition rate into the adult stage from young stage *//* 20 */
      break;
    case 21: P->r_F = value;    /* r_Factor: Population fraction of reprductive females *//* 21 */
      break;
    case 22: P->D_Sigma = value;    
      break;
    case 23: P->Sigmoidal_A0 = value;    
      break;
    case 24: P->Sigmoidal_L0 = value;    
      break;
    case 25: P->Sigmoidal_T0 = value;    
      break;
      
    default:
      printf(".... INVALID PARAMETER KEY (key = %d)\n", key);
      printf(" The maximum number of parameters is Number_PAR_MAX\n");
      printf(" The permited number of keys go from 0, to %d\n", MODEL_PARAMETERS_MAXIMUM-1);

      exit(0);
  }
}

void Parameter_Model_into_Vector_Entries ( Parameter_Model * P, gsl_vector * X,
					   int * Parameter_Index, int No_of_PARAMETERS )
{
  int i;
  int key;
  double value;

  for( i=0; i<No_of_PARAMETERS; i++) {
    key = Parameter_Index[i];
    value = Parameter_Model_into_Vector_Entry( key, P );
    gsl_vector_set(X, i, value);
  }
}

double Parameter_Model_into_Vector_Entry ( int key, Parameter_Model * P )
{
  double value;

  switch (key) {
    case  0: value = P->Beta_Y; /* Total no of sexual contacts a male has per year   *//*  0 */
      break;
    case  1: value = P->p_XY;    /* Male-to-Female transmission probability T(Y--->X) *//*  1 */
      break;
    case  2: value = P->F_Y;    /* Total no of males entering sexual age per year    *//*  2 */
      break;
    case  3: value = P->Delta_X;  /* Natural mortility percapita rate                  *//*  3 */
      break;
    case  4: value = P->Delta_Y;  /* Natural mortility percapita rate                  *//*  4 */
      break;
    case  5: value = P->Gamma;  /* Recovery rate into the quasi-latent phase         *//*  5 */
      break;
    case  6: value = P->Mu;    /* Break-down rate into the final phase (before death) *//*  6 */
      break;
    case  7: value = P->mDelta;/* Disease-induced mortility relative increase         *//*  7 */
      break;
    case  8: value = P->Beta_X;/* Total no of sexual contacts a female has per year   *//*  8 */
      break;
    case  9: value = P->p_YX;   /* Female-to-Male transmission probability T(X--->Y)   *//*  9 */
      break;
    case 10: value = P->Sigma_0; /* Transitional rate into the sexual worker stage      *//*  10 */
      break;
    case 11: value = P->Sigma_0_r;/* Reversal rate back into the regural female stage    *//* 11 */
      break;
    case 12: value = P->Eta;   /* Contact rate relative increase for sexual workers   *//* 12 */
      break;
    case 13: value = P->F_X;   /* Total no of females entering sexual age per year    *//* 13 */
      break;
    case 14: value = (double)P->n_Mu;/* No of latent subclasses during quasi-latent phase *//* 14 */
      break;
    case 15: value = P->Xhi;   /* Transmision probability increase during acute phase *//* 15 */
      break;
    case 16: value = P->f_W;/* Fraction of male sexual contacts with female sexual workers*//* 16 */
      break;
    case 17: value = P->f_0;/* Fraction of male sexual contacts with young females *//* 17 */
      break;
    case 18: value = P->Sigma_1; /* Transition rate into the sexual worker stage      *//*  18 */
      break;
    case 19: value = P->Sigma_1_r;/* Reversal rate back into the regural female stage    *//* 19 */
      break;
    case 20: value = P->Alpha; /* Transition rate from the young to the adult stage  *//* 20 */
      break;
    case 21: value = P->r_F; /* r_Factor: Population fraction of reprductive females *//* 21 */
      break;
    case 22: value = P->D_Sigma;    
      break;
    case 23: value = P->Sigmoidal_A0;    
      break;
    case 24: value = P->Sigmoidal_L0;    
      break;
    case 25: value = P->Sigmoidal_T0;    
      break;
      
    default:
      printf(".... INVALID PARAMETER KEY (key = %d)\n", key);
      printf(" The maximum number of parameters is Number_PAR_MAX\n");
      printf(" The permited number of keys go from 0, to %d\n", MODEL_PARAMETERS_MAXIMUM-1);

      exit(0);
  }

  return(value);
}

void P_A_R_A_M_E_T_E_R___M_O_D_E_L___F_R_E_E( Parameter_Model * P)
{
  free ( P );
}
