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

  r =  Table->Mu*Table->n_Mu / (Table->Mu*Table->n_Mu + Table->Delta_Y);

  Y[YS] = Table->F_Y / (Table->Beta_Y * Table->p_YX * x + Table->Delta_Y);

  Y[YI] = Table->Beta_Y * Table->p_YX * x / (Table->Delta_Y + Table->Gamma) * Y[YS];

  for( i = 1; i<=Table->n_Mu; i++) {
    Y[i+YI]= pow(r, (double)i) * Table->Gamma/Table->Mu/Table->n_Mu * Y[YI];
  }

  Y[YD] = pow(r, (double)Table->n_Mu) * Table->Gamma/(1.0+Table->mDelta)/Table->Delta_Y * Y[YI];
}

void Stable_Solution_y_Free_Disease(Parameter_Table *Table, double *Y)
{
  int i;
  /* Definition of the state vector numerical order, from 0 to K, of model variables */
  #include <Model_Variables_Code.Include.c>

  //Table->MODEL_STATE_VARIABLES
  Y[YS] = Table->F_Y / Table->Delta_Y;

  Y[YI] = 0.0;

  for( i = 1; i<=Table->n_Mu; i++) {
    Y[i+YI]= 0.0;
  }

  Y[YD] = 0.0;
}
