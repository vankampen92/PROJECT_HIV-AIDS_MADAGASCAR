#include <MODEL.h>

double total_Female_Sexual_Workers_Infection  ( const double * y, Parameter_Table * Table ) 
{
  double X, Y, y_0, y_1;
  double Infection;

  // X = total_Female_Sexual_Workers( y, Table );

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

    Infection = Y;
  }
  else {
    printf(" Number of substages for the low-infectivity, quasi-latent stage (n_Mu) is %d\n",
	   Table->n_Mu);
    printf(" n_Mu > 1 requires a carefull code implementation (which is in-progress)\n");
    printf(" The program will exit\nm");
    exit(0);
  }

  return(Infection);
}

double total_Female_Sexual_Workers_Infection_Type_0  ( const double * y, Parameter_Table * Table )
{
  double X, Y;
  double Infection;

  //X = total_Female_Sexual_Workers( y, Table );

  /* Definition of the state vector numerical order, from 0 to K, of model variables */
  #include <Model_Variables_Code.Include.c>

  if( Table->n_Mu == 1 ) {
    Y = y[W0I] + y[W0L] + y[W0D];
    Infection = Y;
    //Infection = Y/X;
  }
  else {
    printf(" Number of substages for the low-infectivity, quasi-latent stage (n_Mu) is %d\n",
	   Table->n_Mu);
    printf(" n_Mu > 1 requires a carefull code implementation (which in-progress)\n");
    printf(" The program will exit\nm");
    exit(0);
  }

  return(Infection);
}

double total_Female_Sexual_Workers_Infection_Type_1  ( const double * y, Parameter_Table * Table )
{
  double X, Y;
  double Infection;

  // X = total_Female_Sexual_Workers( y, Table );

  /* Definition of the state vector numerical order, from 0 to K, of model variables */
  #include <Model_Variables_Code.Include.c>

  if( Table->n_Mu == 1 ) {
    Y = y[W1I] + y[W1L] + y[W1D];
    Infection = Y;
    // Infection = Y/X;
  }
  else {
    printf(" Number of substages for the low-infectivity, quasi-latent stage (n_Mu) is %d\n",
	   Table->n_Mu);
    printf(" n_Mu > 1 requires a carefull code implementation (which in-progress)\n");
    printf(" The program will exit\nm");
    exit(0);
  }

  return(Infection);
}

double total_Female_Non_Sexual_Workers_Infection  ( const double * y, Parameter_Table * Table )
{
  double X, Y, y_0, y_1;
  double Infection;

  // X = total_Female_Non_Sexual_Workers( y, Table );

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
    Infection = Y;
    // Infection = Y/X;
  }
  else {
    printf(" Number of substages for the low-infectivity, quasi-latent stage (n_Mu) is %d\n",
	   Table->n_Mu);
    printf(" n_Mu > 1 requires a carefull code implementation (which in-progress)\n");
    printf(" The program will exit\nm");
    exit(0);
  }

  return(Infection);
}

double total_Female_Non_Sexual_Workers_Infection_Type_0  ( const double * y, Parameter_Table * Table )
{
  double X, Y;
  double Infection;

  // X = total_Female_Non_Sexual_Workers( y, Table );

  /* Definition of the state vector numerical order, from 0 to K, of model variables */
  #include <Model_Variables_Code.Include.c>

  if( Table->n_Mu == 1 ) {
    Y = y[X0I] + y[X0L] + y[X0D];
    Infection = Y;
    // Infection = Y/X;
  }
  else {
    printf(" Number of substages for the low-infectivity, quasi-latent stage (n_Mu) is %d\n",
	   Table->n_Mu);
    printf(" n_Mu > 1 requires a carefull code implementation (which in-progress)\n");
    printf(" The program will exit\nm");
    exit(0);
  }

  return(Infection);
}

double total_Female_Non_Sexual_Workers_Infection_Type_1  ( const double * y, Parameter_Table * Table )
{
  double X, Y;
  double Infection;

  // X = total_Female_Non_Sexual_Workers( y, Table );

  /* Definition of the state vector numerical order, from 0 to K, of model variables */
  #include <Model_Variables_Code.Include.c>

  if( Table->n_Mu == 1 ) {
    Y = y[X1I] + y[X1L] + y[X1D];
    Infection = Y;
    // Infection = Y/X;
  }
  else {
    printf(" Number of substages for the low-infectivity, quasi-latent stage (n_Mu) is %d\n",
	   Table->n_Mu);
    printf(" n_Mu > 1 requires a carefull code implementation (which in-progress)\n");
    printf(" The program will exit\nm");
    exit(0);
  }

  return(Infection);
}

double total_Female_Disease_Infection  ( const double * y, Parameter_Table * Table )
{
  double X, Y;
  double Infection;

  // X = total_Females( y, Table );
  Y = total_Female_Non_Sexual_Workers_Infection (y, Table) + total_Female_Sexual_Workers_Infection (y, Table);

  Infection = Y;
  // Infection = Y/X
  return(Infection);
}

double total_Male_Disease_Infection ( const double * y, Parameter_Table * Table )
{
  double X, Y;
  double Infection;

  // X = total_Males( y, Table );

  /* Definition of the state vector numerical order, from 0 to K, of model variables */
  #include <Model_Variables_Code.Include.c>

  if( Table->n_Mu == 1 ) {
    Y = y[YI] + y[YL] + y[YD];

    Infection = Y;
    // Infection = Y/X;
  }
  else {
    printf(" Number of substages for the low-infectivity, quasi-latent stage (n_Mu) is %d\n",
	   Table->n_Mu);
    printf(" n_Mu > 1 requires a carefull code implementation (which in-progress)\n");
    printf(" The program will exit\nm");
    exit(0);
  }

  return(Infection);
}

double total_Disease_Infection ( const double * y, Parameter_Table * Table)
{
  double X, Y;
  double Infection;

  // X = total_Males(y, Table) + total_Females(y, Table);

  Y  = total_Male_Disease_Infection (y, Table) + total_Female_Disease_Infection (y, Table);

  Infection = Y;
  //  Infection = Y/X;

  return(Infection);
}
