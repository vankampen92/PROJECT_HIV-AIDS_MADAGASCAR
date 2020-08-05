#include <MODEL.h>

void Stable_Solution_x(const double y, Parameter_Table *Table, double *Y)
{
  /*
     This function returns the solution for the female submodel for a given
     fraction of effective infectiouso males, y
  */
  double r; int i;

  /* Definition of the state vector numerical order, from 0 to K, of model variables */
  #include <Model_Variables_Code.Include.c>
  assert( Table->n_Mu == 1);

  Y[XS] = Table->F_X / Table->Delta_X;
}

void Stable_Solution_x_Free_Disease(Parameter_Table *Table, double *Y)
{
  int i;
  /* Definition of the state vector numerical order, from 0 to K, of model variables */
  #include <Model_Variables_Code.Include.c>
  
  Y[XS] = Table->F_X / Table->Delta_X;
}
