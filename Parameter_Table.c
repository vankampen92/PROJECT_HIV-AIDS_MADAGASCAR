#include <MODEL.h>

#if defined CPGPLOT_REPRESENTATION
#include <include.CPG.extern.h>
#endif
// #include <include.Time_Control.extern.h>
#include <include.Parameter_Model.extern.h>
#include <include.Output_Variables.extern.h>
#include <include.Parameter_Space.extern.h>
#include <include.Time_Control.extern.h>
#include <include.Initial_Conditions.extern.h>
#include <include.Error_Control.extern.h>
#include <include.Type_of_Model.extern.h>

// #include "./Include/include.Stochastic_Control.extern.h"
extern int Realizations;

void P_A_R_A_M_E_T_E_R___T_A_B_L_E___A_L_L_O_C( Parameter_Table * Table )
{
  int i;
  int MODEL_OUTPUT_VARIABLES;   /* Actual no of MODEL (output) VARIABLES */
  int MODEL_INPUT_PARAMETERS;  /* Actual no of MODEL (input) PARAMETERS */

  MODEL_INPUT_PARAMETERS = MODEL_PARAMETERS_MAXIMUM;
  MODEL_OUTPUT_VARIABLES = OUTPUT_VARIABLES_MAXIMUM;
  // int MODEL_STATE_VARIABLES;  /* Actual no of MODEL (state) VARIABLES  */
  /* Model parameters are all input parameters defining and controling
     model dynamics (both through simulation and mathematically, in case
     the model has a mathematical description such as a system of ODEs)
  */
  Table->Code_Parameters = (char **)malloc( MODEL_INPUT_PARAMETERS * sizeof(char *) );
  Table->Symbol_Parameters = (char **)malloc( MODEL_INPUT_PARAMETERS * sizeof(char *) );
  Table->Symbol_Parameters_Greek_CPGPLOT = (char **)malloc( MODEL_INPUT_PARAMETERS * sizeof(char *));
  Table->Name_Parameters = (char **)malloc( MODEL_INPUT_PARAMETERS * sizeof(char *) );
  for (i=0; i<MODEL_INPUT_PARAMETERS; i++){
    Table->Code_Parameters[i] = (char *)malloc( 100 * sizeof(char) );
    Table->Name_Parameters[i] = (char *)malloc( 100 * sizeof(char) );
    Table->Symbol_Parameters[i] = (char *)malloc( 100 * sizeof(char) );
    Table->Symbol_Parameters_Greek_CPGPLOT[i] = (char *)malloc( 100 * sizeof(char) );
  }
  Table->Default_Vector_Parameters = (double *)malloc( MODEL_INPUT_PARAMETERS * sizeof(double) );

  Table->Index = (int *)malloc( MODEL_PARAMETERS_MAXIMUM * sizeof(int) );
  Table->Vector_Parameters = (double *)malloc( MODEL_PARAMETERS_MAXIMUM * sizeof(double) );

  /* Output Variables are any measure of the state model variables of any function of
     these at any given time:
     MODEL_OUTPUT_VARIABLES is the Total Number of Total Output Variables
     (as it appears in defintion_OutPut_Variables.c file)( )
   */
  Table->Output_Variable_Name = (char **)malloc( MODEL_OUTPUT_VARIABLES * sizeof(char *) );
  Table->Output_Variable_Symbol = (char **)malloc( MODEL_OUTPUT_VARIABLES * sizeof(char *) );
  for (i=0; i<MODEL_OUTPUT_VARIABLES; i++){
    Table->Output_Variable_Name[i] = (char *)malloc( 100 * sizeof(char) );
    Table->Output_Variable_Symbol[i] = (char *)malloc( 100 * sizeof(char) );
  }
  Table->OUTPUT_VARIABLE_INDEX = (int *)malloc( SUB_OUTPUT_VARIABLES * sizeof(int) );
  Table->Vector_Output_Variables = (double *)malloc( SUB_OUTPUT_VARIABLES * sizeof(double) );
  Table->Matrix_Output_Variables = (double **)malloc( SUB_OUTPUT_VARIABLES * sizeof(double *) );
  for (i=0; i<SUB_OUTPUT_VARIABLES; i++)
    Table->Matrix_Output_Variables[i] = (double *)malloc( I_Time * sizeof(double) );

  Table->Default_Vector_Output_Variables = (double *)malloc( MODEL_OUTPUT_VARIABLES * sizeof(double) );

  Table->Vector_Model_Variables_MultiStability =(double **)calloc( 3, sizeof(double *) );

  /* Model Variables represent only the state model variables, i.e., the set of variables
     completely defining the state of the system at any given time. Model Variables can be,
     of course, also output variables. They can be defined as output variables
     whose definition can be found at Definition_Output_Variables.c */

  /* Some implementations of this code require to alloc memmory according to
     a number of state variables that can change dynamically. In that case, this
     6 lines of code should be commented out. Notice alse the corresponding lines
     in void P_A_R_A_M_E_T_E_R___T_A_B_L_E___F_R_E_E( Parameter_Table * T )

     For most calculations, I opted for allocating this part of the data structure
     only if needed (see ./MODEL_CALCULATIONS/TIME_EVO_DETERMINISTIC/MODEL.c) regardless
     the number of MODEL STATE VARIABLES changing or not during execution. Essentially,
     the numerical integration of a system of ODEs relies on Table->Vector_Model_Variables.
     Therefore, a driver, usaully called void MODEL(Parameter_Table *), is in charge
     of doing this allocation previous to calling the numerical integration function,
     and deallocating this memmory right after.
  */
  // Table->Model_Variable_Name = (char **)malloc( MODEL_STATE_VARIABLES * sizeof(char *) );
  // for (i=0; i<MODEL_STATE_VARIABLES; i++){
  //   Table->Model_Variable_Name[i] = (char *)malloc( 100 * sizeof(char) );
  // }
  // Table->Vector_Model_Variables = (double *)malloc( MODEL_STATE_VARIABLES * sizeof(double) );
  // Table->Vector_Model_Variables_Stationarity = (double *)malloc( MODEL_STATE_VARIABLES * sizeof(double) );
}

void P_A_R_A_M_E_T_E_R___T_A_B_L_E___U_P_L_O_A_D( Parameter_Table * Table, int * Index_Output_Variables )
{
  int i;
  /* Stochastic Realizations */
  Table->Realizations = Realizations;

  /* Total number of potential input paramters */
  Table->MODEL_INPUT_PARAMETERS = MODEL_PARAMETERS_MAXIMUM;

  /* Parameter Model Upload */
  Parameter_Values_into_Parameter_Table(Table);

  /* Type of Model upload  */
  Table->TYPE_of_MODEL = TYPE_of_MODEL;  assert_right_model_definition( Table );
  Model_Variables_Code_into_Parameter_Table (Table);
  /* Total number of potential state variables */
  /* Total number of potential state variables */
  Table->MODEL_STATE_VARIABLES = Table->K + 1;
  /* Total number of potential output variables */
  Table->MODEL_OUTPUT_VARIABLES = OUTPUT_VARIABLES_GENUINE + Table->MODEL_STATE_VARIABLES;

  /* Total number of actual model output variables */
  Table->SUB_OUTPUT_VARIABLES   = SUB_OUTPUT_VARIABLES;
  /* Parameter Space Upload: PARAMETER SPACE             */
  /* Total number of actual input paramters              */
  /* Table->No_of_PARAMETERS = MODEL_PARAMETERS_MAXIMUM; */
  /* Table->A_n = A_n;                                   */
  /* Table->A_d = A_d;                                   */
  /* Table->No_of_POINTS    = No_of_POINTS;              */
  /* Table->Input_Parameter = Input_Parameter;           */
  /* Table->Value_0         = Value_0;                   */
  /* Table->Value_1         = Value_1;                   */

  int MODEL_STATE_VARIABLES    = Table->K + 1;
  Table->Model_Variable_Name   = (char **)malloc( MODEL_STATE_VARIABLES * sizeof(char *) );
  Table->Model_Variable_Symbol = (char **)malloc( MODEL_STATE_VARIABLES * sizeof(char *) );
  for (i=0; i<MODEL_STATE_VARIABLES; i++){
     Table->Model_Variable_Name[i] = (char *)malloc( 100 * sizeof(char) );
     Table->Model_Variable_Symbol[i] = (char *)malloc( 100 * sizeof(char) );
  }

  Table->Growth_Function_Type = Growth_Function_Type;
  /* BEGIN: Parameter default values into vector structure */
  for(i = 0; i<Table->MODEL_INPUT_PARAMETERS; i++){
    Table->Default_Vector_Parameters[i] = AssignStructValue_to_VectorEntry(i, Table);
  }
  /*   END: Parameter default values into vector structure */

  /* BEGIN: Names and codes for model parameters */
  for(i = 0; i<Table->MODEL_INPUT_PARAMETERS; i++){
    AssignLabel_to_Model_Parameters(i, Table->Name_Parameters[i], Table);
    AssignCodes_to_Model_Parameters(i, Table->Code_Parameters[i], Table);
    AssignSymbol_to_Model_Parameters(i, Table->Symbol_Parameters[i], Table);
    AssignCPGPLOT_Symbol_to_Model_Parameters(i, Table->Symbol_Parameters_Greek_CPGPLOT[i], Table); 
  }
  /*   END: Names and codes for model parameter  */

  /* BEGIN: Names and symbols for model variables */
  for(i = 0; i<Table->MODEL_STATE_VARIABLES; i++){
    AssignLabel_to_Model_Variables(i, Table->Model_Variable_Name[i], Table);
    AssignSymbol_to_Model_Variables(i, Table->Model_Variable_Symbol[i], Table);
  }
  /*   END: Names and codes for model variables  */

  /* BEGIN: Names and symbol for output variables           */
  for(i = 0; i<Table->MODEL_OUTPUT_VARIABLES; i++){
    AssignLabel_to_Output_Variables(i, Table->Output_Variable_Name[i], Table);
    AssignSymbol_to_Output_Variables(i, Table->Output_Variable_Symbol[i], Table);
  }
  /*   END: Names for output variables */

  /* BEGIN: Default model input parameters */
  i=0;
  while (i < MODEL_PARAMETERS_MAXIMUM) {
    Table->Index[i] = i;
    i++;
  }
  // This assignation will be overwritten when Parameter_Space structure is setup
  /*  END: Default model input parameters */

  
  /* BEGIN: Model output variables */
  i=0;
  while (i < SUB_OUTPUT_VARIABLES) {
    Table->OUTPUT_VARIABLE_INDEX[i] = Index_Output_Variables[i];
    i++;
    // Up to i=(SUB_OUTPUT_VARIABLES-1) are set through command line values:
    // -n [SUB_OUTPUT_VARIABLES] 
  }
  /*  END: Model output variables */
  
  /* Some implementations of this code require to alloc memmory according to
     a number of state variables that can change dynamically. In that case, this
     3 lines of code should be commented out. Notice alse the corresponding lines
     in the function below:
     void P_A_R_A_M_E_T_E_R___T_A_B_L_E___F_R_E_E( Parameter_Table * T )
     Only if the number of dynamic state model variables never cange during execution,
     these lines of code make sense here
  */
  /* Initial Conditions: MODEL STATE VARIABLES */
  // for (i=0; i < MODEL_STATE_VARIABLES; i++){
  //    AssignLabel_to_Model_Variables(i, Table->Model_Variable_Name[i], Table);
  // }
}

void P_A_R_A_M_E_T_E_R___T_A_B_L_E___F_R_E_E( Parameter_Table * Table )
{
  int i;

  for (i=0; i < Table->MODEL_INPUT_PARAMETERS; i++){
    free( Table->Code_Parameters[i] );
    free( Table->Name_Parameters[i] );
    free( Table->Symbol_Parameters[i] ); 
    free( Table->Symbol_Parameters_Greek_CPGPLOT[i] ); 
  }
  free(Table->Code_Parameters);
  free(Table->Name_Parameters);
  free(Table->Symbol_Parameters); 
  free(Table->Symbol_Parameters_Greek_CPGPLOT); 
  
  free(Table->Default_Vector_Parameters);

  free(Table->Index);
  free(Table->Vector_Parameters);

  for (i=0; i < OUTPUT_VARIABLES_MAXIMUM; i++){
    free(Table->Output_Variable_Name[i]);
    free(Table->Output_Variable_Symbol[i]);
  }
  free(Table->Output_Variable_Symbol);
  free(Table->Output_Variable_Name);

  for (i=0; i<Table->MODEL_STATE_VARIABLES; i++){
     free(Table->Model_Variable_Name[i]);
     free(Table->Model_Variable_Symbol[i]);
  }
  free(Table->Model_Variable_Name);
  free(Table->Model_Variable_Symbol);

  /* Some implementations of this code require to alloc memmory according to
     a number of model variables that can change dynamically.

     For most calculations,  I opted for allocating/de-allocating this part of
     the data structure only if needed
     (see, for instance, ./MODEL_CALCULATIONS/TIME_EVO_DETERMINISTIC/MODEL.c)
     regardless the number of MODEL STATE VARIABLES changing or not during execution.
  */

  // for (i=0; i<MODEL_STATE_VARIABLES; i++){
  //   free(Table->Model_Variable_Name[i]);
  // }
  // free(Table->Model_Variable_Name);
  // free( Table->Vector_Model_Variables );
  // free( Table->Vector_Model_Variables_Stationarity );
  // free( Table->Vector_Model_Variables_MultiStability[0] );
  // free( Table->Vector_Model_Variables_MultiStability[1] );
  // free( Table->Vector_Model_Variables_MultiStability[2] );
  free(Table->Vector_Model_Variables_MultiStability);

  free(Table->OUTPUT_VARIABLE_INDEX);
  free(Table->Vector_Output_Variables);
  for (i=0; i<Table->SUB_OUTPUT_VARIABLES; i++) free(Table->Matrix_Output_Variables[i]);
  free(Table->Matrix_Output_Variables);

  free(Table->Default_Vector_Output_Variables);
}

void Parameter_Table_Index_Update(int * Index, int N, Parameter_Table * P)
{
  int i;
  for(i=0; i<N; i++) P->Index[i] = Index[i];
}

/*
   The purpose of this simple function is just to upload
   ALL input parameters, controling both model definition
   and running simulations, which are defined as global variables,
   into the corresponding Parameter_Table Structure
*/
void Parameter_Values_into_Parameter_Table(Parameter_Table * P)
{
  P->Beta_Y = Beta_Y;   /* Total no of sexual contacts a male has per year     *//*  0 */
  P->p_XY    = p_XY;    /* Male-to-Female transmission probability T(Y--->X)   *//*  1 */
  P->F_Y    = F_Y;      /* Total no of males entering sexual age per year      *//*  2 */
  P->Delta_X  = Delta_X;    /* Natural mortility percapita rate                    *//*  3 */
  P->Delta_Y  = Delta_Y;    /* Natural mortility percapita rate                    *//*  4 */
  P->Gamma  = Gamma;    /* Recovery rate into the quasi-latent phase           *//*  5 */
  P->Mu     = Mu;       /* Break-down rate into the final phase (before death) *//*  6 */
  P->mDelta = mDelta;   /* Disease-induced mortility relative increase         *//*  7 */
  P->Beta_X = Beta_X;   /* Total no of sexual contacts a female has per year   *//*  8 */
  P->p_YX    = p_YX;      /* Female-to-Male transmission probability T(X--->Y) *//*  9 */
  P->Sigma_0  = Sigma_0;   /* Transitial rate into the sexual worker stage     *//* 10 */
  P->Sigma_0_r= Sigma_0_r; /* Reversal rate back into the regural female stage *//* 11 */
  P->Eta    = Eta;      /* Contact rate relative increase for sexual workers   *//* 12 */
  P->F_X    = F_X;      /* Total no of females entering sexual age per year    *//* 13 */
  P->n_Mu   = n_Mu;     /* No of latent subclasses during quasi-latent phase   *//* 14 */
  P->Xhi    = Xhi;      /* Transmision probability increase during acute phase *//* 15 */
  P->f_W    = f_W;      /* Fraction of male sexual contacts with female sexual workers *//* 16 */
  P->f_0    = f_0;      /* Fraction of male sexual contacts with young females *//* 17 */
  P->Sigma_1 = Sigma_1; /* Transition rate into the sexual worker stage        *//* 18 */
  P->Sigma_1_r = Sigma_1_r; /* Reversal rate back into the regural female stage *//* 19 */
  P->Alpha   = Alpha;   /* Transition rate from the young to the adult stage    *//* 20 */
  P->r_F     = r_F;     /* r_Factor: Population fraction of reprductive females  *//* 21 */

  P->D_Sigma  = D_Sigma;  /* Parameter introducing time-dependence in Sigma_0 and Sigma_1 */
  P->Sigmoidal_A0 = Sigmoidal_A0; /* Parameter introducing time-dependence in Sigma_0 and Sigma_1 */ 
  P->Sigmoidal_L0 = Sigmoidal_L0; /* Parameter introducing time-dependence in Sigma_0 and Sigma_1 */
  P->Sigmoidal_T0 = Sigmoidal_T0; /* Parameter introducing time-dependence in Sigma_0 and Sigma_1 */ 
  
  /* Parameters related to the initial conditions: */
  P->YS__0  = YS__0;
  P->YI__0  = YI__0;
  P->YL__0  = YL__0;
  P->YD__0  = YD__0;

  P->XS__0 = XS__0;
  P->XI__0 = XI__0;
  P->XL__0 = XL__0;
  P->XD__0 = XD__0;

  P->WS__0 = WS__0;
  P->WI__0 = WI__0;
  P->WL__0 = WL__0;
  P->WD__0 = WD__0;

  P->X0S__0 = X0S__0;
  P->X0I__0 = X0I__0;
  P->X0L__0 = X0L__0;
  P->X0D__0 = X0D__0;

  P->W0S__0 = W0S__0;
  P->W0I__0 = W0I__0;
  P->W0L__0 = W0L__0;
  P->W0D__0 = W0D__0;

  P->X1S__0 = X1S__0;
  P->X1I__0 = X1I__0;
  P->X1L__0 = X1L__0;
  P->X1D__0 = X1D__0;

  P->W1S__0 = W1S__0;
  P->W1I__0 = W1I__0;
  P->W1L__0 = W1L__0;
  P->W1D__0 = W1D__0;

  P->No_of_IC = No_of_IC;
  P->TYPE_of_INITIAL_CONDITION = TYPE_of_INITIAL_CONDITION;
  P->INITIAL_TOTAL_POPULATION  = INITIAL_TOTAL_POPULATION;
  P->RESCALING_INITIAL_TOTAL_POPULATION = RESCALING_INITIAL_TOTAL_POPULATION;


  P->TYPE_of_ERROR_FUNCTION = TYPE_of_ERROR_FUNCTION;
  P->No_of_ERROR_PARAMETERS = No_of_ERROR_PARAMETERS;

  P->Error_Parameter_0 = Error_Parameter_0;
  P->Error_Parameter_1 = Error_Parameter_1;

  P->Err_0 = Err_0;
  P->Err_1 = Err_1;
  P->Err_2 = Err_2;
  P->Err_3 = Err_3;
  P->Err_4 = Err_4;
  P->Err_5 = Err_5;
  P->Err_6 = Err_6;
  P->Err_7 = Err_7;
  P->Err_8 = Err_8;
  P->Err_9 = Err_9;
  P->Err_10 = Err_11;
  P->Err_11 = Err_11;
  P->Err_12 = Err_12;
  P->Err_13 = Err_13;
  P->Err_14 = Err_14;
  P->Err_15 = Err_15;
  P->Err_16 = Err_16; 
}
