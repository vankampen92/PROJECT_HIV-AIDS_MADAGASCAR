#include "./Include/MODEL.h"

void AssignCPGPLOT_Symbol_to_Model_Parameters(int j, char * Label, Parameter_Table *P)
{
  /* Short Labels for Model Parameters */

  char * p;
  Label[0] = '\0';

  switch(j)
    {
    case  0: p=strcat(Label,"\\gb\\dY\\u");/* Total no of sexual contacts a male has per year   *//*  0 */
      break;
    case  1: p=strcat(Label,"p\\dXY\\u");     /* Male-to-Female transmission probability T(Y--->X) *//*  1 */
      break;
    case  2: p=strcat(Label,"F\\dY\\u");      /* Total no of males entering sexual age per year    *//*  2 */
      break;
    case  3: p=strcat(Label,"\\gd\\dX\\u");    /* Natural mortility percapita rate                  *//*  3 */
      break; 
    case  4: p=strcat(Label,"\\gd\\dY\\u");    /* Natural mortility percapita rate                  *//*  4 */
      break;
    case  5: p=strcat(Label,"\\gg");    /* Recovery rate into the quasi-latent phase         *//*  5 */
      break;
    case  6: p=strcat(Label,"\\gm");       /* Break-down rate into the final phase (before death) *//*  6 */
      break;
    case  7: p=strcat(Label,"m");   /* Disease-induced mortility relative increase         *//*  7 */
      break;
    case  8: p=strcat(Label,"\\gb\\dX\\u");   /* Total no of sexual contacts a female has per year   *//*  8 */
      break;
    case  9: p=strcat(Label,"p\\dYX\\u");     /* Female-to-Male transmission probability T(X--->Y)   *//*  9 */
      break;
    case 10: p=strcat(Label,"\\gs\\d0\\u");  /* Transitional rate into the sexual worker stage      *//* 10 */
      break;
    case 11: p=strcat(Label,"\\gs\\u0\\d\\dr\\u");/* Reversal rate back into the regural female stage    *//* 11 */
      break;
    case 12: p=strcat(Label,"\\gy");      /* Contact rate relative increase for sexual workers   *//* 12 */
      break;
    case 13: p=strcat(Label,"F\\dY\\u");      /* Total no of females entering sexual age per year    *//* 13 */
      break;
    case 14: p=strcat(Label,"n\\d\\gm\\u");     /* No of latent subclasses during quasi-latent phase   *//* 14 */
      break;
    case 15: p=strcat(Label,"\\gx");      /* Transmision probability increase during acute phase *//* 15 */
      break;
    case 16: p=strcat(Label,"f\\dW\\u");      /* Fraction of male sexual contacts with female sexual workers*//* 16 */
      break;
    case 17: p=strcat(Label,"f\\d0\\u");      /* Fraction of male sexual contacts with young female *//* 17 */
      break;
    case 18: p=strcat(Label,"\\gs\\d1\\u");  /* Transition rate into the sexual worker stage for old females  *//* 18 */
      break;
    case 19: p=strcat(Label,"\\gs\\u1\\d\\dr\\u");/* Reversal rate back into the regural female stage for old females *//* 19 */
      break;
    case 20: p=strcat(Label,"\\ga");     /* Transition rate into the old stage (aging)  *//* 20 */
      break;
    case 21: p=strcat(Label ,"r\\dF\\u");     /* r_Factor: Dummy Factor / Population fraction of reprductive females */ /* 21 */
      break;
    case 22: p = strcat(Label , "\\gDs");          /* 22 */
      break;
    case 23:  p = strcat(Label , "A\\d0\\u");          /* 23 */
      break;
    case 24:  p = strcat(Label , "L\\d0\\u");          /* 24 */
      break;
    case 25:  p = strcat(Label , "T\\d0\\u");      /* 25 */       
      break;
    default:
      printf(".... INVALID PARAMETER KEY [key=%d]\n", j);
      printf(".... The permited correspondences are:\n");
      printf("\n");
      fprintf_Model_Parameters(stdout, P);
      exit(0);
    }
}


void AssignSymbol_to_Model_Parameters(int j, char * Label, Parameter_Table *P)
{
  /* Short Labels for Model Parameters */

  char * p;
  Label[0] = '\0';

  switch(j)
    {
    case  0: p=strcat(Label,"Beta_Y");/* Total no of sexual contacts a male has per year   *//*  0 */
      break;
    case  1: p=strcat(Label,"p_XY");     /* Male-to-Female transmission probability T(Y--->X) *//*  1 */
      break;
    case  2: p=strcat(Label,"F_Y");      /* Total no of males entering sexual age per year    *//*  2 */
      break;
    case  3: p=strcat(Label,"Delta_X");    /* Natural mortility percapita rate                  *//*  3 */
      break; 
    case  4: p=strcat(Label,"Delta_Y");    /* Natural mortility percapita rate                  *//*  4 */
      break;
    case  5: p=strcat(Label,"Gamma");    /* Recovery rate into the quasi-latent phase         *//*  5 */
      break;
    case  6: p=strcat(Label,"Mu");       /* Break-down rate into the final phase (before death) *//*  6 */
      break;
    case  7: p=strcat(Label,"mDelta");   /* Disease-induced mortility relative increase         *//*  7 */
      break;
    case  8: p=strcat(Label,"Beta_X");   /* Total no of sexual contacts a female has per year   *//*  8 */
      break;
    case  9: p=strcat(Label,"p_YX");     /* Female-to-Male transmission probability T(X--->Y)   *//*  9 */
      break;
    case 10: p=strcat(Label,"Sigma_0");  /* Transitional rate into the sexual worker stage      *//* 10 */
      break;
    case 11: p=strcat(Label,"Sigma_0_r");/* Reversal rate back into the regural female stage    *//* 11 */
      break;
    case 12: p=strcat(Label,"Eta");      /* Contact rate relative increase for sexual workers   *//* 12 */
      break;
    case 13: p=strcat(Label,"F_X");      /* Total no of females entering sexual age per year    *//* 13 */
      break;
    case 14: p=strcat(Label,"n_Mu");     /* No of latent subclasses during quasi-latent phase   *//* 14 */
      break;
    case 15: p=strcat(Label,"Xhi");      /* Transmision probability increase during acute phase *//* 15 */
      break;
    case 16: p=strcat(Label,"f_W");      /* Fraction of male sexual contacts with female sexual workers*//* 16 */
      break;
    case 17: p=strcat(Label,"f_0");      /* Fraction of male sexual contacts with young female *//* 17 */
      break;
    case 18: p=strcat(Label,"Sigma_1");  /* Transition rate into the sexual worker stage for old females  *//* 18 */
      break;
    case 19: p=strcat(Label,"Sigma_1_r");/* Reversal rate back into the regural female stage for old females *//* 19 */
      break;
    case 20: p=strcat(Label,"Alpha");     /* Transition rate into the old stage (aging)  *//* 20 */
      break;
    case 21: p=strcat(Label ,"r_F");      /* r_Factor: Population fraction of reprductive females */ /* 21 */
      break;
    case 22:  p = strcat(Label , "D_Sigma");      /* 22 */
      break;
    case 23:  p = strcat(Label , "A_0");          /* 23 */
      break;
    case 24:  p = strcat(Label , "L_0");          /* 24 */
      break;
    case 25:  p = strcat(Label , "T_0");          /* 25 */
      break;
    default:
      printf(".... INVALID PARAMETER KEY [key=%d]\n", j);
      printf(".... The permited correspondences are:\n");
      printf("\n");
      fprintf_Model_Parameters(stdout, P);
      exit(0);
    }
}
