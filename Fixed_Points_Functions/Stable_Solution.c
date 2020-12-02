#include <MODEL.h>

void Stable_Solution(double y, double x, Parameter_Table *P, double *Y)
{
  /*
     This function build the full solution for given effective fractions
     of males and females, y, x, respectively.
  */
  Stable_Solution_y(x, P, Y);

  Stable_Solution_x(y, P, Y);
}

void Stable_Solution_Free_Disease(Parameter_Table *P, double *Y)
{

  Stable_Solution_y_Free_Disease(P, Y);

  Stable_Solution_x_Free_Disease(P, Y);
}
