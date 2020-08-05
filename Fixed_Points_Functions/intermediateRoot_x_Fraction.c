/* Main driver to Root finding */
#include <MODEL.h>

double y_Function (const double x, void *params)
{
  double y, y_x, yI_x;

  Generic_Root_Data * G  = (Generic_Root_Data *)params;
  Parameter_Table   * P  = G->P;

  y_x  = Steady_State_y_Fraction(x, P);
  yI_x = Inverted_Steady_State_x_Fraction(x, P);

  y = y_x - yI_x;

  return(y);
}

double intermediateRoot_x_Fraction(Parameter_Table * P, double x_lo, double x_hi)
{
  double y;

  Generic_Root_Data * G = (Generic_Root_Data *)calloc(1, sizeof(Generic_Root_Data));

  G->P = P;
  G->Function = y_Function; // &y_Function;

  G->x_0 = x_lo;
  G->x_1 = x_hi;

  y = Generic_Root_Finder( P, G );

  free(G);
  
  return(y);
}

