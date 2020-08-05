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

  // Z is an array representing total YOUNG women at each stage
  double * Z0 = (double *)calloc(3 + Table->n_Mu, sizeof(double));

  // Solving for Z[XTS], Y[XS], and Y[WS]
  double * p0  = (double *)calloc(2, sizeof(double));
  double * p1  = (double *)calloc(2, sizeof(double));
  double * p2  = (double *)calloc(2, sizeof(double));
  double * Sol = (double *)calloc(2, sizeof(double));
  // p0[0] = p1[0] * x + p2[0] * y;   x = Sol[0];
  // p0[1] = p1[1] * x + p2[1] * y;   y = Sol[1];
  p0[0]=  Table->F_X;                                   p0[1]=  Table->F_X;
  p1[0]=  Table->Beta_X*Table->p_XY*(1.0+Table->Eta)*y + Table->Delta_X + Table->Alpha; p1[1]= -Table->Sigma_0_r;
  p2[0]= -Table->Beta_X*Table->p_XY*Table->Eta*y;       p2[1]=  Table->Beta_X*Table->p_XY*y + Table->Delta_X + Table->Alpha + Table->Sigma_0 + Table->Sigma_0_r;

  linearEqSystem_2dim(p0, p1, p2, Sol);
  Z0[X0TS] = Sol[0];  Y[X0S] = Sol[1]; Y[W0S] = Z0[X0TS] - Y[X0S];

  // Solving for Z0[XTI], Y[XI], and Y[WI]
  Z0[X0TI] = (Table->Beta_X*Table->p_XY*(1.0+Table->Eta)*y*Z0[X0TS]-Table->Beta_X*Table->p_XY*Table->Eta*y*Y[X0S])/(Table->Delta_X+Table->Alpha+Table->Gamma);
  Y[X0I]  = (Table->Beta_X*Table->p_XY*y*Y[X0S] + Table->Sigma_0_r*Z0[X0TI])/(Table->Delta_X+Table->Alpha+Table->Sigma_0+Table->Sigma_0_r+Table->Gamma);
  Y[W0I] = Z0[X0TI] - Y[X0I];

  r =  Table->Mu*Table->n_Mu / (Table->Mu*Table->n_Mu + Table->Delta_X + Table->Alpha);
  for( i = 1; i<=Table->n_Mu; i++) {
    Z0[i+X0TI]= pow(r, (double)i) * Table->Gamma/Table->Mu/Table->n_Mu * Z0[X0TI];
  }
  Z0[X0TD] = pow(r, (double)Table->n_Mu) * Table->Gamma/((1.0+Table->mDelta)*Table->Delta_X + Table->Alpha) * Z0[X0TI];

  Y[1+X0I] = (Table->Sigma_0_r*Z0[1+X0TI]+Table->Gamma*Y[X0I])/(Table->Delta_X+Table->Alpha+Table->Sigma_0+Table->Sigma_0_r+Table->n_Mu*Table->Mu);
  for(i = 2; i<=Table->n_Mu; i++)
    Y[i+X0I]= (Table->Sigma_0_r*Z0[i+X0TI]+Table->n_Mu*Table->Mu*Y[i-1+X0I])/(Table->Delta_X+Table->Alpha+Table->Sigma_0+Table->Sigma_0_r+Table->n_Mu*Table->Mu);
  Y[X0D] = (Table->Sigma_0_r*Z0[X0TD]+Table->n_Mu*Table->Mu*Y[Table->n_Mu+X0I])/(Table->Delta_X*(1.0+Table->mDelta)+Table->Alpha+Table->Sigma_0+Table->Sigma_0_r);

  // Sexual Working (W) from total values (Z) and non-sexual workers (X)
  for(i = 1; i<=Table->n_Mu; i++) Y[i+W0I] = Z0[i+X0TI] - Y[i+X0I];
  Y[W0D] = Z0[X0TD] - Y[X0D];

  // Z is an array representing total OLD women at each stage
  double * Z1 = (double *)calloc(3 + Table->n_Mu, sizeof(double));

  // p0[0] = p1[0] * x + p2[0] * y;   x = Sol[0];
  // p0[1] = p1[1] * x + p2[1] * y;   y = Sol[1];
  p0[0]=  Table->Alpha*Z0[X0TS];                        p0[1]=  Table->Alpha*Y[X0S];
  p1[0]=  Table->Beta_X*Table->p_XY*(1.0+Table->Eta)*y + Table->Delta_X; p1[1]= -Table->Sigma_1_r;
  p2[0]= -Table->Beta_X*Table->p_XY*Table->Eta*y;       p2[1]=  Table->Beta_X*Table->p_XY*y + Table->Delta_X + Table->Sigma_1 + Table->Sigma_1_r;

  linearEqSystem_2dim(p0, p1, p2, Sol);
  Z1[X1TS] = Sol[0];  Y[X1S] = Sol[1]; Y[W1S] = Z1[X1TS] - Y[X1S];

  // Solving for Z1[X1TI], Y[X1I], and Y[W1I]
  Z1[X1TI] = (Table->Alpha*Z0[X0TI]+Table->Beta_X*Table->p_XY*(1.0+Table->Eta)*y*Z1[X1TS]-Table->Beta_X*Table->p_XY*Table->Eta*y*Y[X1S])/(Table->Delta_X+Table->Gamma);
  Y[X1I]  = (Table->Alpha*Y[X0I]+Table->Beta_X*Table->p_XY*y*Y[X1S] + Table->Sigma_1_r*Z1[X1TI])/(Table->Delta_X+Table->Sigma_1+Table->Sigma_1_r+Table->Gamma);
  Y[W1I] = Z1[X1TI] - Y[X1I];

  Z1[1+X1TI] = (Table->Alpha*Z0[1+X0TI] + Table->Gamma*Z1[X1TI]) / (Table->Delta_X + Table->Mu*Table->n_Mu);
  for(i = 2; i<=Table->n_Mu; i++)
    Z1[i+X1TI] = (Table->Alpha*Z0[i+X0TI] + Table->Mu*Table->n_Mu*Z1[i-1+X1TI])/(Table->Delta_X + Table->Mu*Table->n_Mu);
  Z1[X1TD] = (Table->Alpha*Z0[X0TD] + Table->Mu*Table->n_Mu*Z1[Table->n_Mu+X1TI])/(Table->Delta_X*(1.0+Table->mDelta));

  Y[1+X1I] = (Table->Alpha*Y[1+X0I]+Table->Sigma_1_r*Z1[1+X1TI]+Table->Gamma*Y[X1I])/(Table->Delta_X+Table->Sigma_1+Table->Sigma_1_r+Table->n_Mu*Table->Mu);
  for(i = 2; i<=Table->n_Mu; i++)
    Y[i+X1I]= (Table->Alpha*Y[i+X0I]+Table->Sigma_1_r*Z1[i+X1TI]+Table->n_Mu*Table->Mu*Y[i-1+X1I])/(Table->Delta_X+Table->Sigma_1+Table->Sigma_1_r+Table->n_Mu*Table->Mu);
  Y[X1D] = (Table->Alpha*Y[X0D]+Table->Sigma_1_r*Z1[X1TD]+Table->n_Mu*Table->Mu*Y[Table->n_Mu+X1I])/(Table->Delta_X*(1.0+Table->mDelta)+Table->Sigma_1+Table->Sigma_1_r);

  for(i = 1; i<=Table->n_Mu; i++) Y[i+W1I] = Z1[i+X1TI] - Y[i+X1I];
  Y[W1D] = Z1[X1TD] - Y[X1D];

  free(Z0);  free(Z1);
  free(p0); free(p1); free(p2); free(Sol);
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
