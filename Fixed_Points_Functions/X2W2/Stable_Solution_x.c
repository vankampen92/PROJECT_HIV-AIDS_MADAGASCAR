#include <MODEL.h>

void Stable_Solution_x(const double y, Parameter_Table *Table, double *Y)
{
  /*
     This function returns the solution for the female submodel for a given
     fraction of effective infectiouso males, y
  */
  int i;
  double r; 
  double D0, D;
  double x0s, x1s, w0s, w1s;
  
  /* Definition of the state vector numerical order, from 0 to K, of model variables */
  #include <Model_Variables_Code.Include.c>
  
  D = (Table->Delta_X+Table->Alpha)/(Table->Sigma_0+Table->Sigma_0_r+Table->Delta_X+Table->Alpha);

  Y[X0S] = (Table->Delta_X+Table->Sigma_0_r+Table->Alpha)/D * Table->F_X;

  Y[W0S] = Table->Sigma_0/D * Table->F_X; 

  x0s = Table->Delta_X * (Table->Delta_X+Table->Sigma_0_r+Table->Alpha)/D;

  w0s = Table->Delta_X * Table->Sigma_0/D;

  D0  = (Table->Sigma_1_r+Table->Sigma_1+Table->Delta_X);
  
  w1s = Table->Sigma_1/D0 + (Table->Sigma_0-Table->Sigma_1)/D0 * x0s - (Table->Delta_X+Table->Sigma_1+Table->Sigma_0_r)/D0 * w0s;

  x1s = 1.0 - x0s - w0s - w1s;

  Y[X1S] = x1s * Table->F_X/Table->Delta_X;

  Y[W1S] = w1s * Table->F_X/Table->Delta_X; 
}

void Stable_Solution_x_Free_Disease(Parameter_Table *Table, double *Y)
{
  int i;
  double r; 
  double D0, D;
  double x0s, x1s, w0s, w1s;
  
  /* Definition of the state vector numerical order, from 0 to K, of model variables */
  #include <Model_Variables_Code.Include.c>
  
  D = (Table->Delta_X+Table->Alpha)/(Table->Sigma_0+Table->Sigma_0_r+Table->Delta_X+Table->Alpha);

  Y[X0S] = (Table->Delta_X+Table->Sigma_0_r+Table->Alpha)/D * Table->F_X;

  Y[W0S] = Table->Sigma_0/D * Table->F_X; 

  x0s = Table->Delta_X * (Table->Delta_X+Table->Sigma_0_r+Table->Alpha)/D;

  w0s = Table->Delta_X * Table->Sigma_0/D;

  D0  = (Table->Sigma_1_r+Table->Sigma_1+Table->Delta_X);
  
  w1s = Table->Sigma_1/D0 + (Table->Sigma_0-Table->Sigma_1)/D0 * x0s - (Table->Delta_X+Table->Sigma_1+Table->Sigma_0_r)/D0 * w0s;

  x1s = 1.0 - x0s - w0s - w1s;

  Y[X1S] = x1s * Table->F_X/Table->Delta_X;

  Y[W1S] = w1s * Table->F_X/Table->Delta_X;
}
