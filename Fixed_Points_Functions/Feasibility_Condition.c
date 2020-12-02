#include <MODEL.h>

int Feasibility_Condition (Parameter_Table * Table)
{
  int F;

  F = 1;

  if (Table->TYPE_of_MODEL == 2 || Table->TYPE_of_MODEL == 3) F = 0; 

  return(F);
}
