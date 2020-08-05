#include <MODEL.h>

double total_Female_Sexual_Workers  ( const double * y, Parameter_Table * Table )
{
  double x, x_0, x_1;
  int i;

  /* Definition of the state vector numerical order, from 0 to K, of model variables */
  #include <Model_Variables_Code.Include.c>

  if( Table->n_Mu == 1 ) {
    if (Table->TYPE_of_MODEL == 0) {
      x = y[WS] + y[WI] + y[WL] + y[WD];
    }
    else {
      x_0 = total_Female_Sexual_Workers_Type_0 (y, Table);
      x_1 = total_Female_Sexual_Workers_Type_1 (y, Table);
      x   = x_0 + x_1;
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

double total_Female_Sexual_Workers_Type_0  ( const double * y, Parameter_Table * Table )
{
  double x;
  int i;

  /* Definition of the state vector numerical order, from 0 to K, of model variables */
  #include <Model_Variables_Code.Include.c>

  #if defined X2W2
  if( Table->TYPE_of_MODEL == 3 ) x = y[W0S];  
  #else
  if( Table->n_Mu == 1 ) {
    x = y[W0S] + y[W0I] + y[W0L] + y[W0D];
  }
  else {
    printf(" Number of substages for the low-infectivity, quasi-latent stage (n_Mu) is %d\n",
	   Table->n_Mu);
    printf(" n_Mu > 1 requires a carefull code implementation (which in-progress)\n");
    printf(" The program will exit\nm");
    exit(0);
  }
  #endif
  
  return (x);
}

double total_Female_Sexual_Workers_Type_1  ( const double * y, Parameter_Table * Table )
{
  double x;
  int i;

  /* Definition of the state vector numerical order, from 0 to K, of model variables */
  #include <Model_Variables_Code.Include.c>

  #if defined X2W2
  if( Table->TYPE_of_MODEL == 3 ) x = y[W1S];  
  #else
  if( Table->n_Mu == 1 ) {
    x = y[W1S] + y[W1I] + y[W1L] + y[W1D];
  }
  else {
    printf(" Number of substages for the low-infectivity, quasi-latent stage (n_Mu) is %d\n",
	   Table->n_Mu);
    printf(" n_Mu > 1 requires a carefull code implementation (which in-progress)\n");
    printf(" The program will exit\nm");
    exit(0);
  }
  #endif
  
  return (x);
}

double total_Female_Non_Sexual_Workers  ( const double * y, Parameter_Table * Table )
{
  double x, x_0, x_1;
  int i;

  /* Definition of the state vector numerical order, from 0 to K, of model variables */
  #include <Model_Variables_Code.Include.c>

  if( Table->n_Mu == 1 ) {
    if (Table->TYPE_of_MODEL == 0) {
      x = y[XS] + y[XI] + y[XL] + y[XD];
    }
    else {
      x_0 = total_Female_Non_Sexual_Workers_Type_0 (y, Table);
      x_1 = total_Female_Non_Sexual_Workers_Type_1 (y, Table);
      x   = x_0 + x_1;
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

double total_Female_Non_Sexual_Workers_Type_0  ( const double * y, Parameter_Table * Table )
{
  double x;
  int i;

  /* Definition of the state vector numerical order, from 0 to K, of model variables */
  #include <Model_Variables_Code.Include.c>

  #if defined X2W2
  if( Table->TYPE_of_MODEL == 3 ) x = y[X0S];  
  #else
  if( Table->n_Mu == 1 ) {
    x = y[X0S] + y[X0I] + y[X0L] + y[X0D];
  }
  else {
    printf(" Number of substages for the low-infectivity, quasi-latent stage (n_Mu) is %d\n",
	   Table->n_Mu);
    printf(" n_Mu > 1 requires a carefull code implementation (which in-progress)\n");
    printf(" The program will exit\nm");
    exit(0);
  }
  #endif
  
  return (x);
}

double total_Female_Non_Sexual_Workers_Type_1  ( const double * y, Parameter_Table * Table )
{
  double x;
  int i;

  /* Definition of the state vector numerical order, from 0 to K, of model variables */
  #include <Model_Variables_Code.Include.c>

  #if defined X2W2
  if( Table->TYPE_of_MODEL == 3 ) x = y[X1S];  
  #else
  if( Table->n_Mu == 1 ) {
    x = y[X1S] + y[X1I] + y[X1L] + y[X1D];
  }
  else {
    printf(" Number of substages for the low-infectivity, quasi-latent stage (n_Mu) is %d\n",
	   Table->n_Mu);
    printf(" n_Mu > 1 requires a carefull code implementation (which in-progress)\n");
    printf(" The program will exit\nm");
    exit(0);
  }
  #endif
  
  return (x);
}

double total_Population ( const double * y, Parameter_Table * Table)
{
  double x;

  x = total_Males(y, Table) + total_Females(y, Table);

  return(x);
}

double total_Males ( const double * y, Parameter_Table * Table )
{
  double x;
  int i;

  /* Definition of the state vector numerical order, from 0 to K, of model variables */
  #include <Model_Variables_Code.Include.c>

  /* YY0: Label of First Male Class; YY: Label of Last Male Class */
  x = 0.0;
  for(i = YY0; i <= YY; i++) x += y[i];

  return (x);
}

double total_Females  ( const double * y, Parameter_Table * Table )
{
  double x;
  int i;

  /* Definition of the state vector numerical order, from 0 to K, of model variables */
  #include <Model_Variables_Code.Include.c>
  /* XX0: Label of First Female Class; XX: Label of Last Female Class */
  x = 0.0;
  for(i = XX0; i <= XX; i++) x += y[i];

  return (x);
}

double total_Females_Type_0  ( const double * y, Parameter_Table * Table )
{
  double x, x_0, x_1;
  int i;

  /* Definition of the state vector numerical order, from 0 to K, of model variables */
  #include <Model_Variables_Code.Include.c>
  x_0 = total_Female_Sexual_Workers_Type_0 (y, Table);
  x_1 = total_Female_Non_Sexual_Workers_Type_0 (y, Table);

  x = x_0 + x_1;

  return (x);
}

double total_Females_Type_1  ( const double * y, Parameter_Table * Table )
{
  double x, x_0, x_1;
  int i;

  /* Definition of the state vector numerical order, from 0 to K, of model variables */
  #include <Model_Variables_Code.Include.c>

  x_0 = total_Female_Sexual_Workers_Type_1 (y, Table);
  x_1 = total_Female_Non_Sexual_Workers_Type_1 (y, Table);

  x = x_0 + x_1;

  return (x);
}
