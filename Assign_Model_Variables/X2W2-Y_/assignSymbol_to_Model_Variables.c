#include <MODEL.h>

void AssignSymbol_to_Model_Variables(int j, char * Label, Parameter_Table * Table)
{
  char *pFile;
  Label[0]='\0';

  /* Definition of the state vector numerical order, from 0 to K, of model variables */
  #include <Model_Variables_Code.Include.c>

  if(j == X0S)         pFile = strcat(Label, "X0S");

  else if (j == W0S )  pFile = strcat(Label, "W0S");

  else if (j == X1S )  pFile = strcat(Label, "X1S");

  else if (j == W1S )  pFile = strcat(Label, "W1S");

  else if (j == YS )   pFile = strcat(Label, "YS");
  
  else{
    printf(".... INVALID VARIABLE KEY [key = %d]\n", j);
    printf(".... Provided Model Variable Codes have been correcly defined,\n");
    printf(".... the permited correspondences are:\n");
    printf(".... from key = 0 to key = %d\n", Table->MODEL_STATE_VARIABLES-1);
    printf(".... The program will exit\n");
    exit(0);
  }
}
