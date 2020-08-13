#include <MODEL.h>

double Total_Effective_Fraction_of_Infectious_Males  ( const double * y, Parameter_Table * Table )
{
  double x;
  int i;
  double N;

  /* Definition of the state vector numerical order, from 0 to n, of model variables */
#include <Model_Variables_Code.Include.c>

  if( Table->n_Mu == 1 ) {
    N = total_Males (y, Table);
    x = (Table->Xhi*y[YI] + y[YL])/N;
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

double Total_Effective_Fraction_of_Infectious_Females ( const double * y, Parameter_Table * Table )
{
  double x, x_0, x_1;
  int i;
  double N;

  /* Definition of the state vector numerical order, from 0 to n, of model variables */
  #include <Model_Variables_Code.Include.c>

  if( Table->n_Mu == 1 ) {
    if (Table->TYPE_of_MODEL == 0) {
      N = total_Females (y, Table);
      x = (Table->f_W*(Table->Xhi*y[WI] + y[WL]) + (1.0-Table->f_W)*(Table->Xhi*y[XI] + y[XL]))/N;
    }
    else if (Table->TYPE_of_MODEL == 1) {
      x_0 = Total_Effective_Fraction_of_Infectious_Females_Type_0 (y, Table);
      x_1 = Total_Effective_Fraction_of_Infectious_Females_Type_1 (y, Table);
      x   = Table->f_0 * x_0 + (1.0 - Table->f_0) * x_1;
    }
    else {
      printf("TYPE_of_MODEL out of range!!!");
      printf("This model identifier has not been setup");
      printf(" The program will exit\n");
      exit(0);
    }
  }
  else {
    printf(" Number of substages for the low-infectivity, quasi-latent stage (n_Mu) is %d\n",
	   Table->n_Mu);
    printf(" n_Mu > 1 requires a carefull code implementation (which in-progress)\n");
    printf(" The program will exit\n");
    exit(0);
  }

  return (x);
}

double Total_Effective_Fraction_of_Infectious_Females_Type_0 ( const double * y,
							       Parameter_Table * Table )
{
  double x;
  int i;
  double N;
  /* Young Females */
  /* Definition of the state vector numerical order, from 0 to n, of model variables */
  #include <Model_Variables_Code.Include.c>

  if( Table->n_Mu == 1 ) {
    N = total_Females (y, Table);
    x = (Table->f_W*(Table->Xhi*y[W0I] + y[W0L]) + (1.0-Table->f_W)*(Table->Xhi*y[X0I] + y[X0L]))/N;
  }
  else {
    printf(" Number of substages for the low-infectivity, quasi-latent stage (n_Mu) is %d\n",
	   Table->n_Mu);
    printf(" n_Mu > 1 requires a carefull code implementation (which in-progress)\n");
    printf(" The program will exit\n");
    exit(0);
  }

  return (x);
}

double Total_Effective_Fraction_of_Infectious_Females_Type_1 ( const double * y, Parameter_Table * Table )
{
  double x;
  int i;
  double N;
  /* Older Females */
  /* Definition of the state vector numerical order, from 0 to n, of model variables */
  #include <Model_Variables_Code.Include.c>

  if( Table->n_Mu == 1 ) {
    N = total_Females (y, Table);
    x = (Table->f_W*(Table->Xhi*y[W1I] + y[W1L]) + (1.0-Table->f_W)*(Table->Xhi*y[X1I] + y[X1L]))/N;
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
