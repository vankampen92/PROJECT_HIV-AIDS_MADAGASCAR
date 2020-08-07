#include "HEADERS.h"
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                           */
/*                    HUMAN-VECTOR TRANSMITTED DISEASE DYNAMICS              */
/*	                                                                     */
/*                            David Alonso, 2011 (c)                         */
/*                                                                           */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#define HUMAN_CONSTANT_POPULATION

#define INTEGER_CODE_FOR_TIME_DIMENSION 0

#define DEPENDENT_PARAMETERS_MAXIMUM 26   /* Maximum number of potentially forced parameters */

#define MODEL_PARAMETERS_MAXIMUM 26       /* Maximum No of MODEL (input) PARAMETERS */

#define MODEL_PARAMETER_SPACE_MAXIMUM 26  /* Maximum Dimension for Parameter Space */

#define OUTPUT_VARIABLES_MAXIMUM 39

#define OUTPUT_VARIABLES_GENUINE 19  /* Number of Output Variables (besides MODEL_STATE_VARIABLES) */
                                     /* See definition_OutPut_Variables.c */
typedef struct totalRateinfo
{
  double Total_Rate;
  double max_Probability;
}Stochastic_Rate;

#include "MODEL_Trend_Control_STRUCT_DEF.h"

#include "MODEL_Time_Control_STRUCT_DEF.h"

#include "MODEL_Time_Dependence_Control_STRUCT_DEF.h"

#include "MODEL_Parameter_Model_STRUCT_DEF.h"

#include "MODEL_Parameter_Space_STRUCT_DEF.h"

#include "MODEL_Parameter_Table_STRUCT_DEF.h"

#include "MODEL_Generic_Root_Data_STRUCT_DEF.h"

#include "MODEL_Observed_Data_STRUCT_DEF.h"

#include "MODEL_Parameter_Fitting_STRUCT_DEF.h"

#include <Time_Control.h>

#include <Observed_Data.h>

#include <Parameter_Model.h>

#include <Parameter_Table.h>

/* Auxliary Libraries at ./Library common directory */
#include <GSL_Optimization.h>

#include <IO_Procedures.h>

#include <GSL_stat.h>

#include <Definition_Error_Model/Error_Library.h>

/* Auxiliary Functions */
#include "main.H"
#include <assign.h>
#include <Total_Population_Numbers.h>
#include <Total_Population_Fractions.h>
#include <Total_Disease_Prevalence.h>
#include <Total_Disease_Infection.h>
#include <Total_Effective_Fractions.h>
#include <Model_Variables_Code.h>
#include <definition_OutPut_Variables.h>
// #include <R_0.h>
#include <fprintf_Model_Parameters.h>
#include <fprintf_Output_Variables.h>
#include <Latex_Write_Parameter_Table.h>

// #include <Fixed_Points/parameter_Simple_Scan.h>
// #include <Fixed_Points/bifurcation_Diagram.h>
#include <Fixed_Points_Functions/Fixed_Points_Functions.h>

// #include <generic_Function_Parameter_Scan.h>
// #include <generic_Subregion_Parameter_Space.h>
// #include <generic_Random_Parameter_Space.h>
// #include <generic_Random_Parameter_Space_Plus.h>

// #include <eigen_Functions.h>
// #include <Eigenvalue_Calculation.h>

#include <Definition_Time_Trend_Dependence/Time_Dependence_Control.h>
#include <Definition_Time_Trend_Dependence/Trend_Control.h>
#include <Definition_Parameter_Space/Parameter_Space.h>
#include <Definition_Numerical_Integration/deterministic_time_dynamics.h>
#include <Definition_Numerical_Integration/numerical_Integration_Driver.h>
#include <Definition_Numerical_Integration/Initial_Conditions_Numerical_Integration.h>
#include <Definition_Numerical_Integration/ODE_Definitions/ODE_Definitions.h>

#if defined CPGPLOT_REPRESENTATION
/* Header file for Parameter Table dependent CPGPLOT plotting auxiliary functions */
#include <CPGPLOT_Parameter_Table/CPGPLOT___X_Y___Parameter_Table.h>
#else
#define MAX_No_of_FILES 20
#endif 
