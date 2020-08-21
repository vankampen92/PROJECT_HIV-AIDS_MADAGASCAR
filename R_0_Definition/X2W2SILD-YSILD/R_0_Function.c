#include <MODEL.h>

double R_0_Function (Parameter_Table * P)
{
  double R_0;
  double k13, k31, k14, k41, k15, k51, k16, k61;
  double Beta_YX, Beta_XY, Beta_XYW;
  double f_0, f_1, f_X, f_W;
  double TYI, TYL, TXI0, TXI1, TWI0, TWI1, TXL0, TXL1, TWL0, TWL1; 
  double Pi_Y, Pi_X;
  double Sigma_0, Sigma_1, Sigma_0_r, Sigma_1_r;

  Sigma_0   = P->D_Sigma + P->Sigma_0;
  
  Sigma_1   = P->D_Sigma + P->Sigma_1;

  Sigma_0_r = P->Sigma_0_r;

  Sigma_1_r = P->Sigma_1_r; 
  
  TYI = 1.0/(P->Gamma+P->Delta_Y);
  
  TYL = 1.0/(P->Mu+P->Delta_Y);

  TXI0 = 1.0/(P->Gamma+P->Alpha+Sigma_0+P->Delta_X);

  TXI1 = 1.0/(P->Gamma+Sigma_1+P->Delta_X);

  TWI0 = 1.0/(P->Gamma+P->Alpha+Sigma_0_r+P->Delta_X);

  TWI1 = 1.0/(P->Gamma+Sigma_1_r+P->Delta_X);

  TXL0 = 1.0/(P->Mu+P->Alpha+Sigma_0+P->Delta_X);

  TXL1 = 1.0/(P->Mu+Sigma_1+P->Delta_X);
  
  TWL0 = 1.0/(P->Mu+P->Alpha+Sigma_0_r+P->Delta_X);
  
  TWL1 = 1.0/(P->Mu+Sigma_1_r+P->Delta_X);

  Pi_Y  = P->F_Y / P->F_X * P->Delta_X / P->Delta_Y;
  
  Pi_X  = P->F_X / P->F_Y * P->Delta_Y / P->Delta_X;

  Beta_YX   =  P->Beta_Y * P->p_YX * Pi_Y; 

  Beta_XY   =  P->Beta_X * P->p_XY * Pi_X; 

  Beta_XYW  =  P->Beta_X * (1.0+P->Eta)* P->p_XY * Pi_X; 
  
  f_0 = P->f_0;
  
  f_1 = 1.0 - P->f_0;

  f_W = P->f_W; 

  f_X = 1.0 - P->f_W; 

  k13 = Beta_YX*f_0*f_X*P->Xhi*TXI0 + Beta_YX*f_0*f_W*P->Xhi*Sigma_0*TXI0*TWI0 + Beta_YX*f_1*f_X*P->Xhi*P->Alpha*TXI0*TXI1 + Beta_YX*f_0*f_X*P->Gamma*TXI0*TXL0;

  k31 = Beta_XY*P->Xhi*TYI + Beta_XY*P->Gamma*TYI*TYL;

  k14 = Beta_YX*f_0*f_X*P->Xhi*Sigma_0_r*TWI0 + Beta_YX*f_0*f_W*P->Xhi*TWI0 + Beta_YX*f_1*f_W*P->Xhi*P->Alpha*TWI0*TWI1 + Beta_YX*f_0*f_W*P->Gamma*TWI0*TWL0;

  k41 = Beta_XYW*P->Xhi*TYI + Beta_XYW*P->Gamma*TYI*TYL;

  k15 = Beta_YX*f_1*f_X*P->Xhi*TXI1 + Beta_YX*f_1*f_W*P->Xhi*Sigma_1*TXI1*TWI1 + Beta_YX*f_1*f_X*P->Gamma*TXI1*TXL1;

  k51 = Beta_XY*P->Xhi*TYI + Beta_XY*P->Gamma*TYI*TYL;

  k16 = Beta_YX*f_1*f_X*P->Xhi*Sigma_1_r*TWI1*TXI1 + Beta_YX*f_1*f_W*P->Xhi*TWI1 + Beta_YX*f_1*f_W*P->Gamma*TXI1*TWL1;

  k61 = Beta_XYW*P->Xhi*TYI + Beta_XYW*P->Gamma*TYI*TYL;
  
  R_0 = sqrt( k13*k31 + k14*k41 + k15*k51 + k16*k61 ); 
     
  return(R_0); 
}
