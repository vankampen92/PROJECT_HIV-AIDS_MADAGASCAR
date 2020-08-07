#include <MODEL.h>

double fraction_Female_Sexual_Workers ( const double * y, Parameter_Table * Table )
{
  double x, x_0;
  double N;
  int i;

  /* Definition of the state vector numerical order, from 0 to K, of model variables */
  #include <Model_Variables_Code.Include.c>

  N = total_Females (y, Table);

  if( Table->n_Mu == 1 ) {
    if (Table->TYPE_of_MODEL == 0) {
      x = (y[WS] + y[WI] + y[WL] + y[WD])/N;
    }
    else {
      x_0 = total_Female_Sexual_Workers (y, Table);
      x   = x_0 / N;
    }
  }
  else {
    printf(" Number of substages for the low-infectivity, quasi-latent stage (n_Mu) is %d\n",
	   Table->n_Mu);
    printf(" n_Mu > 1 requires a carefull code implementation (which in in-progress)\n");
    printf(" The program will exit\nm");
    exit(0);
  }

  return (x);
}

double fraction_Female_Non_Sexual_Workers  ( const double * y, Parameter_Table * Table )
{
  double x, x_0;
  double N;
  int i;

  /* Definition of the state vector numerical order, from 0 to K, of model variables */
  #include <Model_Variables_Code.Include.c>

  N = total_Females (y, Table);

  if( Table->n_Mu == 1 ) {
    if (Table->TYPE_of_MODEL == 0) {
      x = (y[XS] + y[XI] + y[XL] + y[XD])/N;
    }
    else  {
      x_0 = total_Female_Non_Sexual_Workers (y, Table);
      x   = x_0 / N;
    }
  }
  else {
    printf(" Number of substages for the low-infectivity, quasi-latent stage (n_Mu) is %d\n",
	   Table->n_Mu);
    printf(" n_Mu > 1 requires a carefull code implementation (which in-progress)\n");
    printf(" The program will exit\nm");
    exit(0);
  }

  return (x);
}

double fraction_Female_Sexual_Workers_at_Stationarity_Free_Disease ( Parameter_Table * Table )
{
  /* Output: 

     . x = w0s + w1s, at stationarity.  
  
  */
  double x;

  int i;
  double D0, D, A, B, C;
  double x0s, w0s;

  D  = (Table->Delta_X+Table->Alpha)/(Table->Sigma_0+Table->Sigma_0_r+Table->Delta_X+Table->Alpha);

  D0 = (Table->Sigma_1_r+Table->Sigma_1+Table->Delta_X);

  A = Table->Sigma_1/D0;

  B = (Table->Sigma_0 - Table->Sigma_1)/D0;

  C = (Table->Sigma_1_r - Table->Sigma_0_r)/D0; 

  x0s = Table->Delta_X * (Table->Delta_X+Table->Sigma_0_r+Table->Alpha)/D;

  w0s = Table->Delta_X * Table->Sigma_0/D;

  x   = A + B * x0s - C * w0s;

  return (x);
}
