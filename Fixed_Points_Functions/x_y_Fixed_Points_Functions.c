#include <MODEL.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_vector.h>

void x_y_fixed_Points_Upper(Parameter_Table *P, double EPSILON, double *x, double *y)
{
  double x_0, y_0, x_1, y_1;
  double err_y, err_x;
  int No_Count;

  /* Solution by default */
  (*x) = 0.0;
  (*y) = 0.0;

  if (Feasibility_Condition(P) == 1) {

    No_Count = 0;
    y_0 = Steady_State_y_Fraction_Assymptotic(P);
    x_0 = Steady_State_x_Fraction(y_0, P);

    do{

      y_1 = Steady_State_y_Fraction(x_0, P);
      x_1 = Steady_State_x_Fraction(y_1, P);

      err_y = fabs(y_0 - y_1);
      err_x = fabs(x_0 - x_1);

      x_0 = x_1;
      y_0 = y_1;

      No_Count++;
      if ( No_Count > 100000) break;

    }
    while( (err_y > EPSILON) || (err_x > EPSILON) );

    if( (x_1 > EPSILON) && (y_1 > EPSILON) ){
      /* The solution has converged to something greater than
         (x,y) = (0,0) */
      (*y) = y_1;
      (*x) = x_1;
    }

    if ( No_Count > 100000) {
      /* The solution has NOT converged after 100000 spteps */
      (*y) = 0.0;
      (*x) = 0.0;
    }

  }

  assert( (*x) >= 0.0 ); // Non-negative values are expected!!!
  assert( (*y) >= 0.0 );
}

void x_y_fixed_Points_Lower(Parameter_Table *P, double EPSILON, double *x, double *y)
{
  double x_0, y_0, x_1, y_1;
  double err_y, err_x;
  int No_Count;

  /* Solution by default */
  (*x) = 0.0;
  (*y) = 0.0;

  if (Feasibility_Condition(P) == 1) {

    No_Count = 0;
    y_0 = EPSILON; //Infectious_Human_asymptotic_Fraction(P);
    x_0 = Steady_State_x_Fraction(y_0, P);

    do{

      y_1 = Steady_State_y_Fraction(x_0, P);
      x_1 = Steady_State_x_Fraction(y_1, P);

      err_y = fabs(y_0 - y_1);
      err_x = fabs(x_0 - x_1);

      x_0 = x_1;
      y_0 = y_1;

      No_Count++;
      if ( No_Count > 100000) break;

    }
    while( (err_y > EPSILON) || (err_x > EPSILON) );

    if( (x_1 > EPSILON) && (y_1 > EPSILON) ){
      /* The solution has converged to something greater than
         (x,y) = (0,0) */
      (*y) = y_1;
      (*x) = x_1;
    }
    if ( No_Count > 100000) {
      /* The solution has NOT converged after 100000 spteps */
      (*y) = 0.0;
      (*x) = 0.0;
    }
  }

  assert( (*x) >= 0.0 ); // Non-negative values are expected
  assert( (*y) >= 0.0 );

}

void x_y_fixed_Points_Intermediate(Parameter_Table *P,
				   double x_l,double x_u, double y_l,double y_u,
				   double EPSILON, double *x, double *y)
{
  double y_1, x_1;
  double y_0, x_0;
  int No_Count;

  /* Upper Solution */
  (*x) = x_u;
  (*y) = y_u;

  No_Count = 0;

  y_1 = y_u - EPSILON;
  x_1 = Steady_State_x_Fraction(y_1, P);

  y_0 = y_l + EPSILON;
  x_0 = Steady_State_x_Fraction(y_0, P);

  /* The pairs (x_1, y_1) and (x_0, y_0) are my first guesses */
  /* In fact, I am taking x_0, x_1 to bracket the intermediate
     root that will be my result (*x)
  */
  (*x) = intermediateRoot_x_Fraction (P, x_0, x_1);

  (*y) = Steady_State_y_Fraction((*x), P);
}
