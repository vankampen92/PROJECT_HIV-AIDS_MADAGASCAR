/* Notice that Parameter_Table Struct depends and relies
   on the correct previous defintion of the structures
   Time_Control, Parameter_Model, and Parameter_Space
*/
typedef struct Parameter_Tableinfo
{
  /* Boolean Variable (see Time_Dependence_Control.c) */
  bool x_Bool; 

  /* Stochastic Realizations */
  int Realizations;

  /* * * Parameter Time Dependence Driven Dynamics * * */
  //#include "include.global.RainTemp.h"
  // RainTemp * R_T;

  //"include.Trend_Control.global.h"
  Trend_Control * Tr;

  /* * * Time_Control * * * */
  Time_Control * T;

  /* * * Time_Dependence_Control * * * */
  Time_Dependence_Control * TDC;

  /* * * Parameter_Model * * * */
  #include "include.Parameter_Model.global.h"
  Parameter_Model * P;
  //#include "include.Type_of_Model.global.h" /* Included within include.Parameter_Model.global.h" */

  #include "include.Initial_Conditions.global.h"
  Parameter_Space * IC_Space;

  #include "include.Error_Control.global.h"
  Parameter_Space * E_Space; 

  /* * * Parameter_Space * * * */
  /* Total Number of Input Model Parameters (as in assign....c and boundary_*.c functions) */
  int MODEL_INPUT_PARAMETERS;
  char ** Name_Parameters; // Name_Parameters  : Name Model Input Parameters
  char ** Code_Parameters;
  char ** Symbol_Parameters;
  char ** Symbol_Parameters_Greek_CPGPLOT;
  
  double * Default_Vector_Parameters;

  /* What follows defines a parameter sub-space within
     the whole parameter space
  */
  int * Index;             // Vector defining the parameter subset to explore   */
  double * Vector_Parameters;
  //#include <include.PARAMETER_SPACE.global.h>
  Parameter_Space * S;
  /* * * * * * * * * */

  /* Total Number of Model Output Variables (in defintion_OutPut_Variables.c file) */
  int MODEL_OUTPUT_VARIABLES;
  char ** Output_Variable_Name;
  char ** Output_Variable_Symbol;
  double * Default_Vector_Output_Variables;
  /* Subset of Output Variables */
  /* What follows defines a subset of output variables that will be saved, represented, etc
   */
  int SUB_OUTPUT_VARIABLES;
  int * OUTPUT_VARIABLE_INDEX;
  double * Vector_Output_Variables;
  double ** Matrix_Output_Variables;
  /* * * * * * * * * */

  /* Model Dynamic Variables */
  int MODEL_STATE_VARIABLES;
  char ** Model_Variable_Name;
  char ** Model_Variable_Symbol;

  int YS;
  int YI;
  int YL;
  int YD;
  int XS;  int XTS;
  int XI;  int XTI;
  int XL;  int XTL;
  int XD;  int XTD;
  int WS;
  int WI;
  int WL;
  int WD;

  int X0S; int X0TS;
  int X0I; int X0TI;
  int X0L; int X0TL;
  int X0D; int X0TD;
  int W0S;
  int W0I;
  int W0L;
  int W0D;
  int X1S; int X1TS;
  int X1I; int X1TI;
  int X1L; int X1TL;
  int X1D; int X1TD;
  int W1S;
  int W1I;
  int W1L;
  int W1D;

  int K;  /* Label Last Class        */
  int XX; /* Label Last Female Class */
  int YY; /* Label Last Male   Class */
  int XX0; /* Label First Female Class */
  int YY0; /* Label First Male   Class */

  double * Vector_Model_Variables;
  double * Vector_Model_Variables_Time_0;
  double * Vector_Model_Variables_Stationarity;
  double ** Vector_Model_Variables_MultiStability;
  int * Vector_Model_Int_Variables;               /* Stochastic Dynamics */
  int * Vector_Model_Int_Variables_Time_0;        /* Stochastic Dynamics */

  /*
     Evaluation of the largest (xmax) and the tiniest (xmin)
     numbers my machine can handle
  */
  float nr___x_min;
  float nr___x_MAX;

  double DETERMINISTIC_CASES; // Need by Error_Function.c 
  /* * * C P G   P L O T * * */
#if defined CPGPLOT_REPRESENTATION
#include <include.CPG.global.h>
  Parameter_CPGPLOT * CPG;
#endif
}Parameter_Table;

void P_A_R_A_M_E_T_E_R___T_A_B_L_E___A_L_L_O_C( Parameter_Table * );

void P_A_R_A_M_E_T_E_R___T_A_B_L_E___U_P_L_O_A_D( Parameter_Table *, int * );

void Parameter_Values_into_Parameter_Table(Parameter_Table * );
void values_TempDependency(double Temp, Parameter_Table *);

void P_A_R_A_M_E_T_E_R___T_A_B_L_E___F_R_E_E( Parameter_Table * );
