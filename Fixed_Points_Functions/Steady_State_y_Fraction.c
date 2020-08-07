#include <MODEL.h>

/* B E G I N :   y Effective Fraction for a given value of x Effective Fraction */
double Steady_State_y_Fraction(const double x, Parameter_Table *P)
{
  double y;

  double * Y = (double *)calloc(P->MODEL_STATE_VARIABLES, sizeof(double) );

  Stable_Solution_y(x, P, Y);

  y = Total_Effective_Fraction_of_Infectious_Males ( Y, P );

  free( Y );

  return (y);
}
/* E N D : -------------------------------------------------------------------- */

double Steady_State_y_Fraction_Assymptotic(Parameter_Table *P)
{
  double y;

  y = P->Xhi;

  return (y);
}
