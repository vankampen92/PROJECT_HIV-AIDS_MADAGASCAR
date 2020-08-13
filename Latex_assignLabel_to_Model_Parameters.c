#include "./Include/MODEL.h"

void AssignLabel_to_Model_Parameters__LATEX(int j, char * Label, Parameter_Table *P)
{
  char * p;
  Label[0] = '\0';

  switch(j)
    {
    case  0:  p = strcat(Label , "Total no of sexual contacts a male has per year"); /*  0 */
      break;
    case  1:  p = strcat(Label , "Male-to-Female transmission probability $T(Y\\rightarrow X)$"); /*  1 */
      break;
    case  2:  p = strcat(Label , "Total no of males entering sexual age per year"); /*  2 */
      break;
    case  3:  p = strcat(Label , "Natural mortility percapita rate (females)"); /*  3 */
      break;
    case  4:  p = strcat(Label , "Natural mortility percapita rate (males)"); /*  4 */
      break;
    case  5:  p = strcat(Label , "Recovery rate into the quasi-latent phase"); /*  5 */
      break;
    case  6:  p = strcat(Label , "Break-down rate into the terminal phase (before death)"); /*  6 */
      break;
    case  7:  p = strcat(Label , "Disease-induced mortility relative increase"); /*  7 */
      break;
    case  8:  p = strcat(Label , "Total no of sexual contacts a female has per year"); /*  8 */
      break;
    case  9:  p = strcat(Label , "Female-to-Male transmission probability $T(X\\rightarrow Y)$"); /*  9 */
      break;
    case 10:  p = strcat(Label , "Transition rate into the sexual worker stage"); /*  10 */
      break;
    case 11:  p = strcat(Label , "Reversal rate back into the regular female stage"); /* 11 */
      break;
    case 12:  p = strcat(Label , "Contact rate relative increase for sexual workers"); /* 12 */
      break;
    case 13:  p = strcat(Label , "Total no of females entering sexual age per year"); /* 13 */
      break;
    case 14:  p = strcat(Label , "No of latent subclasses during quasi-latent phase"); /* 14 */
      break;
    case 15:  p = strcat(Label , "Transmision probability increase during acute phase"); /* 15 */
      break;
    case 16:  p = strcat(Label , "Fraction of male sexual contacts with female sexual workers"); /* 16 */
      break;
    case 17:  p = strcat(Label , "Fraction of male sexual contacts with young females"); /* 17 */
      break;
    case 18:  p = strcat(Label , "Transition rate into the sexual worker stage (old females)"); /*  18 */
      break;
    case 19:  p = strcat(Label , "Reversal rate back into the regular female stage (old females)"); /* 19 */
      break;
    case 20:  p = strcat(Label , "Transition rate into the old women stage $T(0\\rightarrow 1)$"); /* 20 */
      break;
    case 21:  p = strcat(Label , "r factor determining the fraction of reproducing females"); /* 21 */
      break;
    case 22:  p = strcat(Label , "Parameter Incrementing Sigma_0 and Sigma_1 values ");          /* 21 */
      break;
    case 23:  p = strcat(Label , "A0, Sigmoidal Parameter (Amplitud)");          /* 21 */
      break;
    case 24:  p = strcat(Label , "L0, Sigmoidal Parameter (Smoothness)");          /* 21 */
      break;
    case 25:  p = strcat(Label , "T0, Sigmoidal Parameter (Threshold)");          /* 21 */
      break;
   default:
      printf(".... INVALID PARAMETER KEY [key = %d]\n", j);
      printf(".... The permited correspondences are:\n");
      printf("\n");
      fprintf_Model_Parameters(stdout, P);
      exit(0);
    }
}

void AssignLabel_to_Model_Parameters__LATEX__SYMBOL(int j, char * Label, Parameter_Table *P)
{
  char * p;
  Label[0] = '\0';

  switch(j)
    {
    case  0: /* Total no of sexual contacts a male has per year   *//*  0 */
      p = strcat(Label, "$\\beta_Y$");
	break;
    case  1: /* Male-to-Female transmission probability T(Y--->X) *//*  1 */
      p = strcat(Label, "$p_{XY}$");
      break;
    case  2: /* Total no of males entering sexual age per year    *//*  2 */
      p = strcat(Label, "$F_Y$");
      break;
    case  3: /* Natural mortility percapita rate                  *//*  3 */
      p = strcat(Label, "$\\delta_X$");
      break;
    case  4: /* Natural mortility percapita rate                  *//*  4 */
      p = strcat(Label, "$\\delta_Y$");
      break;
    case  5: /* Recovery rate into the quasi-latent phase         *//*  5 */
      p = strcat(Label, "$\\gamma$");
      break;
    case  6: /* Break-down rate into the terminal phase (before death) *//* 6 */
      p = strcat(Label, "$\\mu$");
      break;
    case  7: /* Disease-induced mortility relative increase         *//*  7 */
      p = strcat(Label, "$m_{\\delta}$");
      break;
    case  8: /* Total no of sexual contacts a female has per year   *//*  8 */
      p = strcat(Label, "$\\beta_X$");
      break;
    case  9: /* Female-to-Male transmission probability T(X--->Y)   *//*  9 */
      p = strcat(Label, "$p_{YX}$");
      break;
    case 10: /* Transitional rate into the sexual worker stage      *//* 10 */
      p = strcat(Label, "$\\sigma^0$");
      break;
    case 11: /* Reversal rate back into the regural female stage    *//* 11 */
      p = strcat(Label, "$\\sigma^0_r$");
      break;
    case 12: /* Contact rate relative increase for sexual workers   *//* 12 */
      p = strcat(Label, "$\\eta$");
      break;
    case 13: /* Total no of females entering sexual age per year    *//* 13 */
      p = strcat(Label, "$F_X$");
      break;
    case 14: /* No of latent subclasses during quasi-latent phase   *//* 14 */
      p = strcat(Label, "$n$");
      break;
    case 15: /* Transmision probability increase during acute phase *//* 15 */
      p = strcat(Label, "$\\chi$");
      break;
    case 16: /* Fraction of male sexual contacts with female sexual workers*/ /*16*/
      p = strcat(Label, "$f_W$");
      break;
    case 17: /* Fraction of male sexual contacts with young females*/   /* 17 */
      p = strcat(Label, "$f_0$");
      break;
    case 18: /* Transition rate into the sexual worker stage (old females)      *//*  18 */
      p = strcat(Label, "$\\sigma^1$");
      break;
    case 19: /* Reversal rate back into the regural female stage (old females)  *//* 19 */
      p = strcat(Label, "$\\sigma^1_r$");
      break;
    case 20: /* Transition rate into the old women stage   *//* 20 */
      p = strcat(Label, "$\\alpha$");
      break;
    case 21: /* r factor determining the fraction of reproducing females"   */ /* 21 */
      p = strcat(Label, "$r$");
      break;
    case 22:  p = strcat(Label , "$\\Delta\\sigma$");          /* 21 */
      break;
    case 23:  p = strcat(Label , "$A_0$");          /* 21 */
      break;
    case 24:  p = strcat(Label , "$L_0$");          /* 21 */
      break;
    case 25:  p = strcat(Label , "$T_0$");          /* 21 */
      break;
    default:
      printf(".... INVALID PARAMETER KEY [key = %d]\n", j);
      printf(".... The permited correspondences are:\n");
      printf("\n");
      fprintf_Model_Parameters(stdout, P);
      exit(0);
    }
}
