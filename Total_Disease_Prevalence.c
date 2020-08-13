#include <MODEL.h>

double total_Female_Sexual_Workers_Prevalence  ( const double * y, Parameter_Table * Table )
{
  double X, Y, y_0, y_1;
  double Prevalence;

  X = total_Female_Sexual_Workers( y, Table );

  /* Definition of the state vector numerical order, from 0 to K, of model variables */
  #include <Model_Variables_Code.Include.c>

  if( Table->n_Mu == 1 ) {
    if (Table->TYPE_of_MODEL == 0) {
      Y = y[WI] + y[WL] + y[WD];
    }
    else if (Table->TYPE_of_MODEL == 1) {
      y_0 = total_Female_Sexual_Workers_Infection_Type_0 (y, Table);
      y_1 = total_Female_Sexual_Workers_Infection_Type_1 (y, Table);
      Y   = y_0 + y_1;
    }
    else {
      printf("TYPE_of_MODEL out of range!!!");
      printf("This model identifier has not been setup");
      printf(" The program will exit\n");
      exit(0);
    }

    Prevalence = Y/X;
  }
  else {
    printf(" Number of substages for the low-infectivity, quasi-latent stage (n_Mu) is %d\n",
	   Table->n_Mu);
    printf(" n_Mu > 1 requires a carefull code implementation (which is in-progress)\n");
    printf(" The program will exit\nm");
    exit(0);
  }

  return(Prevalence);
}

double total_Female_Non_Sexual_Workers_Prevalence  ( const double * y, Parameter_Table * Table )
{
  double X, Y, y_0, y_1;
  double Prevalence;

  X = total_Female_Non_Sexual_Workers( y, Table );

  /* Definition of the state vector numerical order, from 0 to K, of model variables */
  #include <Model_Variables_Code.Include.c>

  if( Table->n_Mu == 1 ) {
    if (Table->TYPE_of_MODEL == 0) {
      Y = y[XI] + y[XL] + y[XD];
    }
    else if (Table->TYPE_of_MODEL == 1) {
      y_0 = total_Female_Non_Sexual_Workers_Infection_Type_0 (y, Table);
      y_1 = total_Female_Non_Sexual_Workers_Infection_Type_1 (y, Table);
      Y   = y_0 + y_1;
    }
    else {
      printf("TYPE_of_MODEL out of range!!!");
      printf("This model identifier has not been setup");
      printf(" The program will exit\n");
      exit(0);
    }

    Prevalence = Y/X;
  }
  else {
    printf(" Number of substages for the low-infectivity, quasi-latent stage (n_Mu) is %d\n",
	   Table->n_Mu);
    printf(" n_Mu > 1 requires a carefull code implementation (which is in-progress)\n");
    printf(" The program will exit\nm");
    exit(0);
  }

  return(Prevalence);
}

double total_Female_Sexual_Workers_Prevalence_Type_0  ( const double * y, Parameter_Table * Table )
{
  double X, Y;
  double Prevalence;

  X = total_Female_Sexual_Workers_Type_0( y, Table );

  Y = total_Female_Sexual_Workers_Infection_Type_0 (y, Table);

  Prevalence = Y/X;

  return(Prevalence);
}

double total_Female_Sexual_Workers_Prevalence_Type_1  ( const double * y, Parameter_Table * Table )
{
  double X, Y;
  double Prevalence;

  X = total_Female_Sexual_Workers_Type_1( y, Table );

  Y = total_Female_Sexual_Workers_Infection_Type_1(y, Table);

  Prevalence = Y/X;

  return(Prevalence);
}

double total_Female_Non_Sexual_Workers_Prevalence_Type_0  ( const double * y, Parameter_Table * Table )
{
  double X, Y;
  double Prevalence;

  X = total_Female_Non_Sexual_Workers_Type_0( y, Table );

  Y = total_Female_Non_Sexual_Workers_Infection_Type_0 (y, Table);

  Prevalence = Y/X;

  return(Prevalence);
}

double total_Female_Non_Sexual_Workers_Prevalence_Type_1  ( const double * y, Parameter_Table * Table )
{
  double X, Y;
  double Prevalence;

  X = total_Female_Non_Sexual_Workers_Type_1( y, Table );

  Y = total_Female_Non_Sexual_Workers_Infection_Type_1 (y, Table);

  Prevalence = Y/X;

  return(Prevalence);
}

double total_Female_Disease_Prevalence  ( const double * y, Parameter_Table * Table )
{
  double X, Y;
  double Prevalence;

  X = total_Females( y, Table );
  Y = total_Female_Non_Sexual_Workers_Infection (y, Table) + total_Female_Sexual_Workers_Infection (y, Table);

  Prevalence = Y/X;
  return(Prevalence);
}

double total_Male_Disease_Prevalence ( const double * y, Parameter_Table * Table )
{
  double X, Y;
  double Prevalence;

  X = total_Males( y, Table );

  /* Definition of the state vector numerical order, from 0 to K, of model variables */
  #include <Model_Variables_Code.Include.c>

  if( Table->n_Mu == 1 ) {
    Y = y[YI] + y[YL] + y[YD];

    Prevalence = Y/X;
  }
  else {
    printf(" Number of substages for the low-infectivity, quasi-latent stage (n_Mu) is %d\n",
	   Table->n_Mu);
    printf(" n_Mu > 1 requires a carefull code implementation (which in-progress)\n");
    printf(" The program will exit\nm");
    exit(0);
  }

  return(Prevalence);
}

double total_Disease_Prevalence ( const double * y, Parameter_Table * Table)
{
  double X, Y;
  double Prevalence;

  X = total_Males(y, Table) + total_Females(y, Table);

  Y  = total_Disease_Infection (y, Table);

  Prevalence = Y/X;

  return(Prevalence);
}
