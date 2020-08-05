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

  // Z is an array representing total women at each stage
  double * Z = (double *)calloc(3 + Table->n_Mu, sizeof(double));

  // Solving for Z[XTS], Y[XS], and Y[WS]
  double * p0  = (double *)calloc(2, sizeof(double));
  double * p1  = (double *)calloc(2, sizeof(double));
  double * p2  = (double *)calloc(2, sizeof(double));
  double * Sol = (double *)calloc(2, sizeof(double));
  // p0[0] = p1[0] * x + p2[0] * y;   x = Sol[0];
  // p0[1] = p1[1] * x + p2[1] * y;   y = Sol[1];
  p0[0]=  Table->F_X;                                   p0[1]=  Table->F_X;
  p1[0]=  Table->Beta_X*Table->p_XY*(1.0+Table->Eta)*y + Table->Delta_X; p1[1]= -Table->Sigma_0_r;
  p2[0]= -Table->Beta_X*Table->p_XY*Table->Eta*y;       p2[1]=  Table->Beta_X*Table->p_XY*y + Table->Delta_X + Table->Sigma_0 + Table->Sigma_0_r;

  linearEqSystem_2dim(p0, p1, p2, Sol);
  Z[XTS] = Sol[0];  Y[XS] = Sol[1]; Y[WS] = Z[XTS] - Y[XS];

  // Solving for Z[XTI], Y[XI], and Y[WI]
  Z[XTI] = (Table->Beta_X*Table->p_XY*(1.0+Table->Eta)*y*Z[XTS]-Table->Beta_X*Table->p_XY*Table->Eta*y*Y[XS])/(Table->Delta_X+Table->Gamma);
  Y[XI]  = (Table->Beta_X*Table->p_XY*y*Y[XS] + Table->Sigma_0_r*Z[XTI])/(Table->Delta_X+Table->Sigma_0+Table->Sigma_0_r+Table->Gamma);
  Y[WI] = Z[XTI] - Y[XI];

  r =  Table->Mu*Table->n_Mu / (Table->Mu*Table->n_Mu + Table->Delta_X);
  for( i = 1; i<=Table->n_Mu; i++) {
    Z[i+XTI]= pow(r, (double)i) * Table->Gamma/Table->Mu/Table->n_Mu * Z[XTI];
  }
  Z[XTD] = pow(r, (double)Table->n_Mu) * Table->Gamma/(1.0+Table->mDelta)/Table->Delta_X * Z[XTI];

  Y[1+XI] = (Table->Sigma_0_r*Z[1+XTI]+Table->Gamma*Y[XI])/(Table->Delta_X+Table->Sigma_0+Table->Sigma_0_r+Table->n_Mu*Table->Mu);
  for(i = 2; i<=Table->n_Mu; i++)
     Y[i+XI]= (Table->Sigma_0_r*Z[i+XTI]+Table->n_Mu*Table->Mu*Y[i-1+XI])/(Table->Delta_X+Table->Sigma_0+Table->Sigma_0_r+Table->n_Mu*Table->Mu);
  Y[XD] = (Table->Sigma_0_r*Z[XTD]+Table->n_Mu*Table->Mu*Y[Table->n_Mu+XI])/(Table->Delta_X*(1.0+Table->mDelta)+Table->Sigma_0+Table->Sigma_0_r);

  // Sexual Working (W) from total values (Z) and non-sexual workers (X)
  for(i = 1; i<=Table->n_Mu; i++) Y[i+WI] = Z[i+XTI] - Y[i+XI];
  Y[WD] = Z[XTD] - Y[XD];

  free(p0); free(p1); free(p2); free(Sol);
  free(Z);
}

void Stable_Solution_x_Free_Disease(Parameter_Table *Table, double *Y)
{
  int i;
  /* Definition of the state vector numerical order, from 0 to K, of model variables */
  #include <Model_Variables_Code.Include.c>

  /* In progress... */
  Y[XS] = (Table->Sigma_0+Table->Sigma_0_r) / (Table->Sigma_0+Table->Sigma_0_r+Table->Delta_X) * Table->F_X/Table->Delta_X;  Y[XI] = 0.0;
  for( i = 1; i<=Table->n_Mu; i++)  Y[i+XI]= 0.0;
  Y[XD] = 0.0;

  Y[WS] = Table->Sigma_0 / (Table->Sigma_0+Table->Sigma_0_r+Table->Delta_X) * Table->F_X/Table->Delta_X;  Y[WI] = 0.0;
  for( i = 1; i<=Table->n_Mu; i++)  Y[i+WI]= 0.0;
  Y[WD] = 0.0;

}
