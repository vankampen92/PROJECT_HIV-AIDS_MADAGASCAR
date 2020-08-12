#include "./Include/MODEL.h"

void AssignLabel_to_Model_Parameters(int j, char * Label, Parameter_Table *P)
{
  char * p;
  Label[0] = '\0';

  switch(j)
    {
    case  0:  p = strcat(Label , "Total no of sexual contacts a male has per year");               /*  0 */
	break;
    case  1:  p = strcat(Label , "Male-to-Female transmission probability T(Y--->X)");             /*  1 */
      break;
    case  2:  p = strcat(Label , "Total no of males entering sexual age per year");                /*  2 */
      break;
    case  3:  p = strcat(Label , "Natural mortility percapita rate (females)");                    /*  3 */
      break;
    case  4:  p = strcat(Label , "Natural mortility percapita rate (males)");                      /*  4 */
      break;
    case  5:  p = strcat(Label , "Recovery rate into the quasi-latent phase");                     /*  5 */
      break;
    case  6:  p = strcat(Label , "Break-down rate into the final phase (before death)");           /*  6 */
      break;
    case  7:  p = strcat(Label , "Disease-induced mortility relative increase");                   /*  7 */
      break;
    case  8:  p = strcat(Label , "Total no of sexual contacts a female has per year");             /*  8 */
      break;
    case  9:  p = strcat(Label , "Female-to-Male transmission probability T(X--->Y)");             /*  9 */
      break;
    case 10:  p = strcat(Label , "Transition rate into the sexual worker stage");                  /* 10 */
      break;
    case 11:  p = strcat(Label , "Reversal rate back into the regular female stage");              /* 11 */
      break;
    case 12:  p = strcat(Label , "Contact rate relative increase for sexual workers");             /* 12 */
      break;
    case 13:  p = strcat(Label , "Total no of females entering sexual age per year");              /* 13 */
      break;
    case 14:  p = strcat(Label , "No of latent subclasses during quasi-latent phase");             /* 14 */
      break;
    case 15:  p = strcat(Label , "Transmision probability increase during acute phase");           /* 15 */
      break;
    case 16:  p = strcat(Label , "Fraction of male sexual contacts with female sexual workers");   /* 16 */
      break;
    case 17:  p = strcat(Label , "Fraction of male sexual contacts with young females");           /* 17 */
      break;
    case 18:  p = strcat(Label , "Transition rate into the sexual worker stage for old females)"); /* 18 */
      break;
    case 19:  p = strcat(Label , "Reversal rate back into the regular stage for old females");     /* 19 */
      break;
    case 20:  p = strcat(Label , "Transition rate into adult stage");                              /* 20 */
      break;
    case 21:  p = strcat(Label , "r_Factor: Population fraction of reprductive females");          /* 21 */
      break;
    case 22:  p = strcat(Label , "Parameter Incrementing Sigma_0 and Sigma_1 values ");          /* 22 */
        break;
    case 23:  p = strcat(Label , "A_0, Sigmoidal Parameter (Amplitud)");          /* 23 */
        break;
    case 24:  p = strcat(Label , "L_0, Sigmoidal Parameter (Smoothness)");          /* 24 */
        break;
    case 25:  p = strcat(Label , "T_0, Sigmoidal Parameter (Threshold)");          /* 25 */
        break;
    default:
      printf(".... INVALID PARAMETER KEY [key = %d]\n", j);
      printf(".... The permited correspondences are:\n");
      printf("\n");
      fprintf_Model_Parameters(stdout, P);
      exit(0);
    }
}
