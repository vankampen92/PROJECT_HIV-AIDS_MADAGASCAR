#include <MODEL.h>

void Model_Variables_Code_into_Parameter_Table (Parameter_Table * P)
{
  int TYPE_of_MODEL;

  TYPE_of_MODEL = P->TYPE_of_MODEL;

  switch( TYPE_of_MODEL )
    {
      /* XWSILD-YSILD models * * * * * * * * * * * * * * * * * * * * * * */
    case 0:

        P->YS =  0;                P->XTS = 0;
        P->YI =  1;                P->XTI = 1;
        P->YL =  2;                P->XTL = 2;
        P->YD =  P->YL+P->n_Mu;    P->XTD = P->XTL+P->n_Mu; //(3 if n_Mu = 1)

        P->XS =  4;
        P->XI =  5;
        P->XL =  6;
        P->XD =  P->XL+P->n_Mu;

        P->WS =  8;
        P->WI =  9;
        P->WL = 10;
        P->WD = P->WL+P->n_Mu;

        /* Conventions */
        P->K   = 11;      /* Label last class        */
        P->XX  = 11;      /* Label last female class */
        P->YY  =  3;      /* Label last male class   */
        P->XX0  = 4;      /* Label first female class */
        P->YY0  = 0;      /* Label first male class   */
    break;
     /* X2W2SILD-YSILD models * * * * * * * * * * * * * * * * * * * * * * */
    case 1:
        P->YS =  0;              P->X0TS = 0;               P->X1TS = 0;
        P->YI =  1;              P->X0TI = 1;               P->X1TI = 1;
        P->YL =  2;              P->X0TL = 2;               P->X1TL = 2;
        P->YD =  P->YL+P->n_Mu;  P->X0TD = P->X0TL+P->n_Mu; P->X1TD = P->X1TL+P->n_Mu;
        //(3 if n_Mu = 1)
        //(3 if n_Mu = 1)

        P->X0S =  4;               P->XS =  4;
        P->X0I =  5;               P->XI =  5;
        P->X0L =  6;               P->XL =  6;
        P->X0D =  P->X0L+P->n_Mu;  P->XD =  P->XL+P->n_Mu;
        P->W0S =  8;               P->WS =  8;
        P->W0I =  9;               P->WI =  9;
        P->W0L = 10;               P->WL = 10;
        P->W0D =  P->W0L+P->n_Mu;  P->WD =  P->WL+P->n_Mu;

        P->X1S = 12;
        P->X1I = 13;
        P->X1L = 14;
        P->X1D =  P->X1L+P->n_Mu;
        P->W1S = 16;
        P->W1I = 17;
        P->W1L = 18;
        P->W1D =  P->W1L+P->n_Mu;

        /* Conventions */
        P->K   = 19;      /* Label last class        */
        P->XX  = 19;      /* Label last female class */
        P->YY  =  3;      /* Label last male class   */
        P->XX0  = 4;      /* Label first female class */
        P->YY0  = 0;      /* Label first male class   */
    break;
    /* X-Y models (only demography)* * * * * * * * * * * * * * * * * * * * * * */
    case 2:

      P->YS =  0;                P->XTS = 1;
      P->YI =  0;                P->XTI = 0;
      P->YL =  0;                P->XTL = 0;
      P->YD =  0;                P->XTD = 0;

      P->XS =  1;
      P->XI =  0;
      P->XL =  0;
      P->XD =  0;

      P->WS =  0;
      P->WI =  0;
      P->WL =  0;
      P->WD =  0;

      /* Conventions */
      P->K    = 1;      /* Label last class        */
      P->XX   = 1;      /* Label last female class */
      P->YY   = 0;      /* Label last male class   */
      P->XX0  = 1;      /* Label first female class */
      P->YY0  = 0;      /* Label first male class   */
   break;
   /* X2W2-Y_ models (demography + females groups) * * * * * * * * * * * * * * * */
    case 3:
      P->YS =  0;                P->X0TS = 0;               P->X1TS = 0;
      P->YI =  0;                P->X0TI = 0;               P->X1TI = 0;
      P->YL =  0;                P->X0TL = 0;               P->X1TL = 0;
      P->YD =  0;                P->X0TD = 0;               P->X1TD = 0;
        //(3 if n_Mu = 1)
      P->X0S =  1;               P->XS =  1;
      P->X0I =  0;               P->XI =  0;
      P->X0L =  0;               P->XL =  0;
      P->X0D =  0;               P->XD =  0;

      P->W0S =  2;               P->WS =  2;
      P->W0I =  0;               P->WI =  0;
      P->W0L =  0;               P->WL =  0;
      P->W0D =  0;               P->WD =  0;

      P->X1S =  3;
      P->X1I =  0;
      P->X1L =  0;
      P->X1D =  0;

      P->W1S =  4;
      P->W1I =  0;
      P->W1L =  0;
      P->W1D =  0;

      /* Conventions */
      P->K   =  4;      /* Label last class        */
      P->XX  =  4;      /* Label last female class */
      P->YY  =  0;      /* Label last male class   */
      P->XX0  = 1;      /* Label first female class */
      P->YY0  = 0;      /* Label first male class   */
    break;
    /* X2W2-Y_ models * * * * * * * * * * * * * * * * * * * * * * */

   default:
     printf(" This TYPE_of_MODEL (%d) code is not defined.\n", TYPE_of_MODEL);
     printf("Check input argument list\n");
     exit(0);
   }
  /* Conventionally, the last label in the argument list of

     Model_Variables_Code_into_Parameter_Table (...),

     (*K), should be the label of the last model state variable.
     Then ( * K) + 1 becomes de total number of dynamic variables.
  */
}

void Model_Variables_Code_into_Parameter_Model (Parameter_Model * P)
{
  int TYPE_of_MODEL;

  TYPE_of_MODEL = P->TYPE_of_MODEL;

  switch( TYPE_of_MODEL )
    {
      /* XWSILD-YSILD models * * * * * * * * * * * * * * * * * * * * * * */
    case 0:

        P->YS =  0;                P->XTS = 0;
        P->YI =  1;                P->XTI = 1;
        P->YL =  2;                P->XTL = 2;
        P->YD =  P->YL+P->n_Mu;    P->XTD = P->XTL+P->n_Mu; //(3 if n_Mu = 1)

        P->XS =  4;
        P->XI =  5;
        P->XL =  6;
        P->XD =  P->XL+P->n_Mu;

        P->WS =  8;
        P->WI =  9;
        P->WL = 10;
        P->WD = P->WL+P->n_Mu;

        /* Conventions */
        P->K   = 11;      /* Label last class        */
        P->XX  = 11;      /* Label last female class */
        P->YY  =  3;      /* Label last male class   */
        P->XX0  = 4;      /* Label first female class */
        P->YY0  = 0;      /* Label first male class   */
    break;
     /* X2W2SILD-YSILD models * * * * * * * * * * * * * * * * * * * * * * */
    case 1:
        P->YS =  0;              P->X0TS = 0;               P->X1TS = 0;
        P->YI =  1;              P->X0TI = 1;               P->X1TI = 1;
        P->YL =  2;              P->X0TL = 2;               P->X1TL = 2;
        P->YD =  P->YL+P->n_Mu;  P->X0TD = P->X0TL+P->n_Mu; P->X1TD = P->X1TL+P->n_Mu;
        //(3 if n_Mu = 1)
        //(3 if n_Mu = 1)

        P->X0S =  4;               P->XS =  4;
        P->X0I =  5;               P->XI =  5;
        P->X0L =  6;               P->XL =  6;
        P->X0D =  P->X0L+P->n_Mu;  P->XD =  P->XL+P->n_Mu;
        P->W0S =  8;               P->WS =  8;
        P->W0I =  9;               P->WI =  9;
        P->W0L = 10;               P->WL = 10;
        P->W0D =  P->W0L+P->n_Mu;  P->WD =  P->WL+P->n_Mu;

        P->X1S = 12;
        P->X1I = 13;
        P->X1L = 14;
        P->X1D =  P->X1L+P->n_Mu;
        P->W1S = 16;
        P->W1I = 17;
        P->W1L = 18;
        P->W1D =  P->W1L+P->n_Mu;

        /* Conventions */
        P->K   = 19;      /* Label last class        */
        P->XX  = 19;      /* Label last female class */
        P->YY  =  3;      /* Label last male class   */
        P->XX0  = 4;      /* Label first female class */
        P->YY0  = 0;      /* Label first male class   */
    break;
    /* X-Y models (only demography)* * * * * * * * * * * * * * * * * * * * * * */
    case 2:

      P->YS =  0;                P->XTS = 1;
      P->YI =  0;                P->XTI = 0;
      P->YL =  0;                P->XTL = 0;
      P->YD =  0;    P->XTD = 0;

      P->XS =  1;
      P->XI =  0;
      P->XL =  0;
      P->XD =  0;

      P->WS =  0;
      P->WI =  0;
      P->WL =  0;
      P->WD =  0;

      /* Conventions */
      P->K    = 1;      /* Label last class        */
      P->XX   = 1;      /* Label last female class */
      P->YY   = 0;      /* Label last male class   */
      P->XX0  = 1;      /* Label first female class */
      P->YY0  = 0;      /* Label first male class   */
   break;
   /* X2W2-Y_ models (demography + females groups) * * * * * * * * * * * * * * * */
    case 3:
      P->YS =  0;                P->X0TS = 0;               P->X1TS = 0;
      P->YI =  0;                P->X0TI = 0;               P->X1TI = 0;
      P->YL =  0;                P->X0TL = 0;               P->X1TL = 0;
      P->YD =  0;                P->X0TD = 0;               P->X1TD = 0;
        //(3 if n_Mu = 1)
      P->X0S =  1;               P->XS =  1;
      P->X0I =  0;               P->XI =  0;
      P->X0L =  0;               P->XL =  0;
      P->X0D =  0;               P->XD =  0;

      P->W0S =  2;               P->WS =  2;
      P->W0I =  0;               P->WI =  0;
      P->W0L =  0;               P->WL =  0;
      P->W0D =  0;               P->WD =  0;

      P->X1S =  3;
      P->X1I =  0;
      P->X1L =  0;
      P->X1D =  0;

      P->W1S =  4;
      P->W1I =  0;
      P->W1L =  0;
      P->W1D =  0;

      /* Conventions */
      P->K   =  4;      /* Label last class        */
      P->XX  =  4;      /* Label last female class */
      P->YY  =  0;      /* Label last male class   */
      P->XX0  = 1;      /* Label first female class */
      P->YY0  = 0;      /* Label first male class   */
    break;
    /* X2W2-Y_ models * * * * * * * * * * * * * * * * * * * * * * */
   default:
     printf(" This TYPE_of_MODEL (%d) code is not defined.\n", TYPE_of_MODEL);
     printf("Check input argument list\n");
     exit(0);
   }
  /* Conventionally, the last label in the argument list of

     Model_Variables_Code_into_Parameter_Table (...),

     (*K), should be the label of the last model state variable.
     Then ( * K) + 1 becomes de total number of dynamic variables.
  */
}
