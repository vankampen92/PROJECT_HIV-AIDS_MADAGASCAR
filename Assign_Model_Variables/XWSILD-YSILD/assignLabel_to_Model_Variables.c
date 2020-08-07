#include <MODEL.h>

void AssignLabel_to_Model_Variables(int j, char * Label, Parameter_Table * Table)
{
  char *pFile;
  Label[0]='\0';

  /* Definition of the state vector numerical order, from 0 to K, of model variables */
  #include <Model_Variables_Code.Include.c>

  if(j == XS)         pFile = strcat(Label, "XS");
  else if (j == XI )  pFile = strcat(Label, "XI");
  else if (j == XL )  pFile = strcat(Label, "XL");
  else if (j == XD )  pFile = strcat(Label, "XD");
  else if (j == WS )  pFile = strcat(Label, "WS");
  else if (j == WI )  pFile = strcat(Label, "WI");
  else if (j == WL )  pFile = strcat(Label, "WL");
  else if (j == WD )  pFile = strcat(Label, "WD");
  else if (j == YS )   pFile = strcat(Label, "YS");
  else if (j == YI )   pFile = strcat(Label, "YI");
  else if (j == YL )   pFile = strcat(Label, "YL");
  else if (j == YD )   pFile = strcat(Label, "YD");
  else{
    printf(".... INVALID VARIABLE KEY [key = %d]\n", j);
    printf(".... Provided Model Variable Codes have been correcly defined,\n");
    printf(".... the permited correspondences are:\n");
    printf(".... from key = 0 to key = %d\n", Table->MODEL_STATE_VARIABLES-1);
    printf(".... The program will exit\n");
    exit(0);
  }
}
