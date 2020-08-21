#include <MODEL.h>

#include <gsl/gsl_errno.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_odeiv.h>

int function (double t, const double y[], double dydt[], void *params)
{
  int i,k;
  double X, Y;

  Parameter_Table * Table = (Parameter_Table *)params;

  /* Definition of the state vector numerical order, from 0 to K, of model variables */
  #include <Model_Variables_Code.Include.c>

  /* Total human population */
  Table->NX = total_Females( y, Table );
  Table->NY = total_Males( y, Table );

  /* X : Effective Average Fraction of Infectious Females */
  X = Total_Effective_Fraction_of_Infectious_Females ( y, Table );
  #include <include.ODE_sys_YSILD.c>
  
  /* Y: Effective Average Fraction of Infectious Males */
  Y = Total_Effective_Fraction_of_Infectious_Males ( y, Table );
  #include <include.ODE_sys_XWSILD.c>
  

  return GSL_SUCCESS;
}
