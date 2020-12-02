#include <MODEL.h>

double Generic_Root_Finder( Parameter_Table * P, Generic_Root_Data * G )
{
  //   Input:
  //   . P,  full table of parameters
  //   . G,  data structure containing the definition of the test function and all parameters
  ///  required for function evaluations and root finding.
  //
  //   Output:
  //   . y such that H_x(y) = 0 where x = G->x, and H_x is defined as H_x(y) = x - F(y);
  //   Notice that H_x(.) is defined as the member 'Function' of the Generic_Root_Data structure.
  //   This member is a pointer to function that must have been initialized before. This function
  //   should have the right dependencies. An example would be:
  //   double Test_Function (const double y, void * params)
  //
       int status;
       int iter = 0, max_iter = 100;
       const gsl_root_fsolver_type * T;
       gsl_root_fsolver *s;
       double r = 0;
       double x_lo, x_hi; //. [x_lo, x_hi], brackting values
       gsl_function F;

       F.function = G->Function;
       F.params   = (void *)G;
       
       x_lo  = G->x_0;
       x_hi  = G->x_1;

       // T = gsl_root_fsolver_brent;
       T = gsl_root_fsolver_bisection; 
       s = gsl_root_fsolver_alloc (T);
       gsl_root_fsolver_set (s, &F, x_lo, x_hi);

       printf ("using %s method\n",
               gsl_root_fsolver_name (s));

       printf ("%5s [%9s, %9s] %9s %9s\n",
               "iter", "lower", "upper", "root", "err(est)");
       do
         {
           iter++;
           status = gsl_root_fsolver_iterate (s);
           r = gsl_root_fsolver_root (s);
           x_lo = gsl_root_fsolver_x_lower (s);
           x_hi = gsl_root_fsolver_x_upper (s);
           status = gsl_root_test_interval (x_lo, x_hi,
                                            0, 0.001);

           if (status == GSL_SUCCESS)
             printf ("Converged:\n");

           printf ("%5d [%.4f, %.4f] %.4f %.4f\n",
                   iter, x_lo, x_hi,
                   r,
                   x_hi - x_lo);
         }
       while (status == GSL_CONTINUE && iter < max_iter);

       gsl_root_fsolver_free (s);

       return (r);
}
