#include <MODEL.h>

void Stable_Solution_y(double x, Parameter_Table *Table, double *Y)
{
  /*
     This function returns the solution for the male submodel for a given
     fraction of effective infectious females
  */
  double r; int i;
  /* Definition of the state vector numerical order, from 0 to K, of model variables */
  #include <Model_Variables_Code.Include.c>

  assert( Table->n_Mu == 1);

  Y[YS] = Table->F_Y / Table->Delta_Y;
}

void Stable_Solution_y_Free_Disease(Parameter_Table *Table, double *Y)
{
  int i;

  /* Definition of the state vector numerical order, from 0 to K, of model variables */
  #include <Model_Variables_Code.Include.c>

  //Table->MODEL_STATE_VARIABLES
  Y[YS] = Table->F_Y / Table->Delta_Y;
}
