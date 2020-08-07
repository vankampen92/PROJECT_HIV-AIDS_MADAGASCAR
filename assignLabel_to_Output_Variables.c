#include <MODEL.h>

void AssignLabel_to_Output_Variables(int j, char * Label, Parameter_Table * P)
{
  char * p;
  Label[0] = '\0';
  if (j >= OUTPUT_VARIABLES_GENUINE) {
    j -= OUTPUT_VARIABLES_GENUINE;
    /* The first output variables are the model variables */
    AssignLabel_to_Model_Variables(j, Label, P);
  }
  else {
    switch(j)
      {
      case  0:  p = strcat(Label , "Effective Average Fraction of Infectious Females"); /*  0 */
        break;
      case  1:  p = strcat(Label , "Effective Average Fraction of Infectious Males");   /*  1 */
        break;
      case  2:  p = strcat(Label , "Total Female Population");                          /*  2 */
        break;
      case  3:  p = strcat(Label , "Total Male Population");                            /*  3 */
        break;
      case  4:  p = strcat(Label , "Female Sexual Worker");            /*  4 */
        break;
      case  5:  p = strcat(Label , "Total Female Non Sexual Worker Population");        /*  5 */
        break;
      case  6:  p = strcat(Label , "Total Population");                                 /*  6 */
        break;
      case  7:  p = strcat(Label , "Total Disease Prevalence");                         /*  7 */
        break;
      case  8:  p = strcat(Label , "Total Female Disease Prevalence");                  /*  8 */
        break;
      case  9:  p = strcat(Label , "Total Male Disease Prevalence");                    /*  9 */
        break;
      case 10:  p = strcat(Label , "Total Female Sexual Worker Prevalence");            /* 10 */
        break;
      case 11:  p = strcat(Label , "Total Female Non-Sexual Worker Prevalence");        /* 11 */
        break;
      case 12:  p = strcat(Label , "Female Sexual Worker Fraction");                    /* 12 */
        break;
      case 13:  p = strcat(Label , "Female Non-Sexual Worker Fraction");                /* 13 */
        break;
      case 14:  p = strcat(Label , "Female Sexual Worker (Infected)");        /* 14 */
        break;
      case 15:  p = strcat(Label , "Total No of Female Non-Sexual Worker Infected");    /* 15 */
	      break;
      case 16:  p = strcat(Label , "Total No of Male Infected");                        /* 16 */
          break;
      case 17:  p = strcat(Label , "Sigma_0(t)");                        /* 17*/
          break;
      case 18:  p = strcat(Label , "Sigma_1(t)");                        /* 18 */
          break;
      default:
        printf(".... INVALID OUTPUT VARIABLE KEY [key = %d]\n", j);
        printf(".... The permited correspondences are:\n");
        printf(".... from 0 to 18\n");
        exit(0);
      }
  }
}
