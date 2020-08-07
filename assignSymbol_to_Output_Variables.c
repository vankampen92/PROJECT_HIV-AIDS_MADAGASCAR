#include <MODEL.h>

void AssignSymbol_to_Output_Variables(int j, char * Label, Parameter_Table * Table)
{
  char * p;
  Label[0] = '\0';
  if (j >= OUTPUT_VARIABLES_GENUINE) {
    j -= OUTPUT_VARIABLES_GENUINE;
    /* The first output variables are the model variables */
    AssignSymbol_to_Model_Variables(j, Label, Table);
  }
  else {
    switch(j)
      {
      case  0: p = strcat(Label , "x_eff"); /*  0 */
        break;
      case  1:  p = strcat(Label , "y_eff");    /*  1 */
        break;
      case  2:  p = strcat(Label , "XX");       /*  2 */
        break;
      case  3:  p = strcat(Label , "XY");       /*  3 */
        break;
      case  4:  p = strcat(Label , "XXSW");     /*  4 */
        break;
      case  5:  p = strcat(Label , "XXNSW");    /*  5 */
        break;
      case  6:  p = strcat(Label , "N");        /*  6 */
        break;
      case  7:  p = strcat(Label , "P");        /*  7 */
        break;
      case  8:  p = strcat(Label , "P_XX");     /*  8 */
        break;
      case  9:  p = strcat(Label , "P_XY");     /*  9 */
        break;
      case 10:  p = strcat(Label , "P_XXSW");   /*  10 */
        break;
      case 11:  p = strcat(Label , "P_XXNSW");  /*  11 */
        break;
      case 12:  p = strcat(Label , "F_XXSW");   /*  12 */
        break;
      case 13:  p = strcat(Label , "F_XXNSW");  /*  13 */
        break;
      case 14:  p = strcat(Label , "I_XXSW");   /* 14 */
        break;
      case 15:  p = strcat(Label , "I_XXNSW");  /* 15 */
  	     break;
      case 16:  p = strcat(Label , "I_XY");     /* 16 */
        break;
      case 17:  p = strcat(Label , "Sigma_0(t)");  /* 15 */
        break;
      case 18:  p = strcat(Label , "Sigma_1(t)");     /* 16 */
        break;
      default:
        printf(".... INVALID OUTPUT VARIABLE KEY [key = %d]\n", j);
        printf(".... The permited correspondences are:\n");
        printf(".... from 0 to 16\n");
        exit(0);
      }
  }
}

void AssignCPGPLOT_Symbol_to_Output_Variables(int j, char * Label, Parameter_Table * Table)
{
  char * p;
  Label[0] = '\0';
  if (j >= OUTPUT_VARIABLES_GENUINE) {
    j -= OUTPUT_VARIABLES_GENUINE;
    /* The first output variables are the model variables */
    AssignSymbol_to_Model_Variables(j, Label, Table);
  }
  else {
    switch(j)
      {
      case  0: p = strcat(Label , "x\\deff\\u"); /*  0 */
        break;
      case  1:  p = strcat(Label , "y\\deff\\u");    /*  1 */
        break;
      case  2:  p = strcat(Label , "X");       /*  2 */
        break;
      case  3:  p = strcat(Label , "Y");       /*  3 */
        break;
      case  4:  p = strcat(Label , "X\\dSW\\u");     /*  4 */
        break;
      case  5:  p = strcat(Label , "X\\dNSW\\u");    /*  5 */
        break;
      case  6:  p = strcat(Label , "N");        /*  6 */
        break;
      case  7:  p = strcat(Label , "P");        /*  7 */
        break;
      case  8:  p = strcat(Label , "P\\dX\\u");     /*  8 */
        break;
      case  9:  p = strcat(Label , "P\\dY\\u");     /*  9 */
        break;
      case 10:  p = strcat(Label , "P\\dSW\\u");   /*  10 */
        break;
      case 11:  p = strcat(Label , "P\\dNSW\\u");  /*  11 */
        break;
      case 12:  p = strcat(Label , "F\\dSW\\u");   /*  12 */
        break;
      case 13:  p = strcat(Label , "F\\dNSW\\u");  /*  13 */
        break;
      case 14:  p = strcat(Label , "I\\dSW\\u");   /* 14 */
        break;
      case 15:  p = strcat(Label , "I\\dNSW\\u");  /* 15 */
  	     break;
      case 16:  p = strcat(Label , "I\\dY\\u");     /* 16 */
        break;
      case 17:  p = strcat(Label , "\\gs\\d0\\u(t)");  /* 15 */
        break;
      case 18:  p = strcat(Label , "\\gs\\d1\\u(t)");     /* 16 */
        break;
      default:
        printf(".... INVALID OUTPUT VARIABLE KEY [key = %d]\n", j);
        printf(".... The permited correspondences are:\n");
        printf(".... from 0 to 16\n");
        exit(0);
      }
  }
}
