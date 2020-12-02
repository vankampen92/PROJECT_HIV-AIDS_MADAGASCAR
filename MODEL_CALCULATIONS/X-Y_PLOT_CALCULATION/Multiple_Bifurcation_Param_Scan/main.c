/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                           */
/*                             MALARIA ODE with "Gamma" DELAYS               */
/*                                                                           */
/*                         Recursive Calculation of Fixed Points             */
/*                                                                           */
/*                                 David Alonso, 2006 (c)                    */
/*                                                                           */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#include <MODEL.h>

#include "global.h"

/* This code calculates bifurcation diagrams for human-mosquito coupled models 
   of malaria transmission. This code is compiled without graphical output. 
   For graphical output, please look at directory:
   
   ./MODEL_CALCULATIONS/VISUAL_SCAN_BIFUCATION

   Compiation:

   . ~$ make H_MODEL=CASES_1 M_MODEL=LXVnW JACOBIAN=ODE

   Exectution

   . ~$ ./CASES_1-LXVnW -H2 5.4E-5 -H3 6.7E-4 -H4 6.3E-3 -H5 1 -H6 0.05 -H7 0.00001 -C0 0.2 -C1 0.2 -C2 0.01 -C3 0.1  -M0 0.3 -M1 0.1 -M2 0.2 -M3 0.04 -L2 3.0E4 -P0 1 -P1 0.05
*/
   

gsl_rng * r; /* Global generator defined in main.c */

#define EPSILON 1.e-8

int main(int argc, char **argv)
{
  int i;
  int S, E, I, R, C, S1, I1, S2, I2, S3, I3, L, X, U, W, A, K;
  Parameter_Table P;
  FILE *fp;

  /* Default vaules */

#include "default.c"

  P_ARG = &P;
 
  /* Command line arguments */
  if(argc>1) ArgumentControl(argc,argv);
  
  values_HumanMos(&P);
  
#if defined CASES_33
  P.TYPE_of_MODEL        = 0;
  printf(" This code cannot be compiled with this option\n");
  printf(" Use the equivalent CASES_1 option instead\n");
  printf(" The program will exit\n");
  exit(0);
#endif

  #if defined CASES_1
  P.TYPE_of_MODEL        = 11;
#endif
#if defined CASES_1LXVnW
  P.TYPE_of_MODEL        = 11;
#endif
#if defined CASES_1XkVnW
  P.TYPE_of_MODEL        = 12;
#endif
#if defined CASES_1XVnW
  P.TYPE_of_MODEL        = 13;
#endif
#if defined CASES_1XW
  P.TYPE_of_MODEL        = 14;
#endif

#if defined NO_CASES
  P.TYPE_of_MODEL        = 21;
#endif
#if defined NO_CASESLXVnW
  P.TYPE_of_MODEL        = 21;
#endif
#if defined NO_CASESXkVnW
  P.TYPE_of_MODEL        = 22;
#endif
#if defined NO_CASESXVnW
  P.TYPE_of_MODEL        = 23;
#endif
#if defined NO_CASESXW
  P.TYPE_of_MODEL        = 24;
#endif

#if defined SEnI
  P.TYPE_of_MODEL        = 31;
#endif
#if defined SEnILXVnW
  P.TYPE_of_MODEL        = 31;
#endif
#if defined SEnIXkVnW
  P.TYPE_of_MODEL        = 32;
#endif
#if defined SEnIXVnW
  P.TYPE_of_MODEL        = 33;
#endif
#if defined SEnIXW
  P.TYPE_of_MODEL        = 34;
#endif

#if defined SI
  P.TYPE_of_MODEL        = 41;
#endif
#if defined SILXVnW
  P.TYPE_of_MODEL        = 41;
#endif
#if defined SIXkVnW
  P.TYPE_of_MODEL        = 42;
#endif
#if defined SIXVnW
  P.TYPE_of_MODEL        = 43;
#endif
#if defined SIXW
  P.TYPE_of_MODEL        = 44;
#endif

#if defined SnInR
  T->TYPE_of_MODEL        = 51;
#endif
#if defined SnInRLXVnW
  T->TYPE_of_MODEL        = 51;
#endif
#if defined SnInRXkVnW /* None of these following SnInR models are unpacked anywhere else yet */
  T->TYPE_of_MODEL        = 52;
#endif
#if defined SnInRint
  T->TYPE_of_MODEL        = 53;
#endif
#if defined SnInRXW
  T->TYPE_of_MODEL        = 54;
#endif
  
  M_O_D_E_L___V_A_R_I_A_B_L_E_S___C_O_D_E (&P, 
					   &S, &E, &I, &R, &C, &S1, &I1, &S2, &I2, &S3, &I3,  
					   &L, &X, &U, &W, &A, 
					   &K);
  
  int No_of_POINTS = 1000;
  int Output_Variable = 3;  /* Fraction of infectious humans */
  // int Output_Variable = 5;      /* Total number of infectious mosquitoes per human */
  int Input_Parameter = 12;
  
  int Status_0 = B_I_F_U_R_C_A_T_I_O_N___D_I_A_G_R_A_M___S_I_M_P_L_E___S_C_A_N( &P, 
										No_of_POINTS, 
										Output_Variable, Input_Parameter, 
										EPSILON );
  Parameters_ModelReport("report.txt", P_ARG);

  fprintf_Input_Parameters(stdout, P_ARG); 

  printf("\nEnd of progam\n");
  return (0);
}

