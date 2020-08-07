#include <MODEL.h>

void AssignLabel_to_Model_Variables(int j, char * Label, Parameter_Table * Table)
{
  char *pFile;
  Label[0]='\0';

  /* Definition of the state vector numerical order, from 0 to K, of model variables */
  #include <Model_Variables_Code.Include.c>

  if(j == X0S)         pFile = strcat(Label, "X0S");
  else if (j == X0I )  pFile = strcat(Label, "X0I");
  else if (j == X0L )  pFile = strcat(Label, "X0L");
  else if (j == X0D )  pFile = strcat(Label, "X0D");
  else if (j == W0S )  pFile = strcat(Label, "W0S");
  else if (j == W0I )  pFile = strcat(Label, "W0I");
  else if (j == W0L )  pFile = strcat(Label, "W0L");
  else if (j == W0D )  pFile = strcat(Label, "W0D");
  else if (j == X1S )  pFile = strcat(Label, "X1S");
  else if (j == X1I )  pFile = strcat(Label, "X1I");
  else if (j == X1L )  pFile = strcat(Label, "X1L");
  else if (j == X1D )  pFile = strcat(Label, "X1D");
  else if (j == W1S )  pFile = strcat(Label, "W1S");
  else if (j == W1I )  pFile = strcat(Label, "W1I");
  else if (j == W1L )  pFile = strcat(Label, "W1L");
  else if (j == W1D )  pFile = strcat(Label, "W1D");

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
