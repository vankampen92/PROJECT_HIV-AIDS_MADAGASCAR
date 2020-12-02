/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                           */
/*                         Recursive Calculation of Fixed Points             */
/*                                                                           */
/*                                 David Alonso, 2006 (c)                    */
/*                                                                           */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#include <MODEL.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_vector.h>

void Fixed_Point_Lower(Parameter_Table *P, double *y_Sol, double EPSILON)
{
  double x, y;
  x_y_fixed_Points_Lower(P, EPSILON, &x, &y);
  Stable_Solution(y, x, P, y_Sol);
}

void Fixed_Point_Upper(Parameter_Table *P, double *y_Sol, double EPSILON)
{
  double x, y;
  x_y_fixed_Points_Upper(P, EPSILON, &x, &y);
  Stable_Solution(y, x, P, y_Sol);
}

void Fixed_Point_Intermediate(Parameter_Table *P,
			      double x_l,double x_u, double y_l,double y_u,
			      double *y_Sol, double EPSILON)
{
  double x, y;
  x_y_fixed_Points_Intermediate(P, x_l,x_u, y_l,y_u, EPSILON, &x, &y);
  Stable_Solution(y, x, P, y_Sol);
}

void Fixed_Points_All(Parameter_Table * Table,
		      double *y_Sol_Lower, double *y_Sol_Inter, double *y_Sol_Upper,
		      double EPSILON)
{
  int i;
  double x_l, y_l;
  double x_u, y_u;
  double x, y_C, y_I;

  #include <Model_Variables_Code.Include.c>

  if (Feasibility_Condition(Table) == 1) {

    printf("LOWER: ");
    printf("Calculating Fixed Point from below (LOWER)...\n");
    Fixed_Point_Lower(Table, y_Sol_Lower, EPSILON);

    printf("UPPER: ");
    printf("Calculating Fixed Point from above (UPPER)...\n");
    Fixed_Point_Upper(Table, y_Sol_Upper, EPSILON);

    x_l = Total_Effective_Fraction_of_Infectious_Females ( y_Sol_Lower, Table );
    x_u = Total_Effective_Fraction_of_Infectious_Females ( y_Sol_Upper, Table );

    y_l = Total_Effective_Fraction_of_Infectious_Males ( y_Sol_Lower, Table );
    y_u = Total_Effective_Fraction_of_Infectious_Males ( y_Sol_Upper, Table );

    printf(" Difference between lower and upper solution (EPSILON = %g)...\n", EPSILON);
    printf(" X:         Lower: %g\tUpper: %g\tDifference: %g\n", x_l, x_u, fabs(x_l - x_u));
    printf(" Y:         Lower: %g\tUpper: %g\tDifference: %g\n", y_l, y_u, fabs(y_l - y_u));

    if (fabs(x_u - x_l) > EPSILON || fabs(y_u - y_l) > EPSILON){
      printf("INTERMEDIATE: ");
      printf("Calculating Intermediate Fixed Point (if it exists)...\n");
      Fixed_Point_Intermediate(Table, x_l,x_u, y_l,y_u, y_Sol_Inter, EPSILON);
    }
    else{
      for(i = 0; i<Table->MODEL_STATE_VARIABLES; i++){
				y_Sol_Inter[i] = y_Sol_Lower[i];
      }
    }

  }
  else{

    /* All three solutions are actually the same (free disease equilibrium) */
    printf("Free-disease equilibrium\n");
    Stable_Solution_Free_Disease(Table, y_Sol_Lower);
    Stable_Solution_Free_Disease(Table, y_Sol_Inter);
    Stable_Solution_Free_Disease(Table, y_Sol_Upper);

  }
}
