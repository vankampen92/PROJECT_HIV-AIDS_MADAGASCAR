#include <MODEL.h>

/* B E G I N :   x Effective Fraction for a given value of y Effective Fraction */
double Steady_State_x_Fraction(const double y, Parameter_Table *P)
{
  //Given y, easily returns x, this is, x = F(y)
  double x;

  double * Y = (double *)calloc(P->MODEL_STATE_VARIABLES, sizeof(double) );

  Stable_Solution_x( y, P, Y );

  x = Total_Effective_Fraction_of_Infectious_Females ( Y, P );

  free ( Y );

  return (x);
}
/* E N D : -------------------------------------------------------------------- */

double Test_Function (const double y, void *params)
{
  double y_Test;

  Generic_Root_Data * G = (Generic_Root_Data *)params;
  Parameter_Table * P  = G->P;
  double x             = G->x;

  y_Test = x - Steady_State_x_Fraction(y, P);

  return(y_Test);
}

double Inverted_Steady_State_x_Fraction(const double x, Parameter_Table *P)
{
  // This function is only the inversion of the previous one.
  // It finds y for a given x such that F(x)=y, this is, y = F^{-1} (x)
  // Inversion is found through a bisection method that uses the Generic_Root_Finder
  ///functions (see corresponding file).
  // Failure may happen when when y_0 and y_1 fail to bracket the solution y or when
  // the function to invert itself, x = F(y), is ill-behaved.

  double y, y_0, y_1;

  Generic_Root_Data * G = (Generic_Root_Data *)calloc(1, sizeof(Generic_Root_Data));;

  G->x = x;
  G->P = P;
  
  G->Function = Test_Function;

  G->x_0 = 0.0;
  G->x_1 = P->Xhi;

  y = Generic_Root_Finder( P, G );

  free(G);
  
  return (y);
}


double Steady_State_x_Fraction_Assymptotic(Parameter_Table *P)
{
  double x;
  // In progress... (This function is not required)
  x = P->Xhi;

  return (x);
}
