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

  #include <include.ODE_sys_Y_.c>
  
  #include <include.ODE_sys_X2W2.c>
  
  return GSL_SUCCESS;
}
