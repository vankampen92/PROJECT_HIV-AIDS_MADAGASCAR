typedef struct Parameter_Modelinfo
{
  int MODEL_INPUT_PARAMETERS;
  int MODEL_OUTPUT_VARIABLES;
  int MODEL_STATE_VARIABLES;

  /* * * Model Parameters  * * */
#include <include.Parameter_Model.global.h>
  
  /* * * Initial Conditions  * */
#include <include.Initial_Conditions.global.h>

  /* * * Error Model * * * */
#include "include.Error_Control.global.h"

  Trend_Control * Tr;

#if defined CPGPLOT_REPRESENTATION
  Parameter_CPGPLOT * CPG;
#endif

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
  
}Parameter_Model;
