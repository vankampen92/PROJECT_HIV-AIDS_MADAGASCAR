#include <MODEL.h>

void Vector_Entry_into_Model_Variable_Initial_Condition_Table(double Value,
							      int j, Parameter_Table * Table)
{
  
  /* Definition of the state vector numerical order, from 0 to K, of model variables */
  #include <Model_Variables_Code.Include.c>
  
  if(j == X0S)         Table->X0S__0 = Value;
  else if (j == X0I )  Table->X0I__0 = Value;
  else if (j == X0L )  Table->X0L__0 = Value;
  else if (j == X0D )  Table->X0D__0 = Value;
  else if (j == W0S )  Table->W0S__0 = Value;
  else if (j == W0I )  Table->W0I__0 = Value;
  else if (j == W0L )  Table->W0L__0 = Value;
  else if (j == W0D )  Table->W0D__0 = Value;
  else if (j == X1S )  Table->X1S__0 = Value;
  else if (j == X1I )  Table->X1I__0 = Value;
  else if (j == X1L )  Table->X1L__0 = Value;
  else if (j == X1D )  Table->X1D__0 = Value;
  else if (j == W1S )  Table->W1S__0 = Value;
  else if (j == W1I )  Table->W1I__0 = Value;
  else if (j == W1L )  Table->W1L__0 = Value;
  else if (j == W1D )  Table->W1D__0 = Value;

  else if (j == YS )   Table->YS__0 = Value;
  else if (j == YI )   Table->YI__0 = Value;
  else if (j == YL )   Table->YL__0 = Value;
  else if (j == YD )   Table->YD__0 = Value;
  else{
    printf(".... INVALID VARIABLE KEY [key = %d]\n", j);
    printf(".... Provided Model Variable Codes have been correcly defined,\n");
    printf(".... the permited correspondences are:\n");
    printf(".... from key = 0 to key = %d\n", Table->MODEL_STATE_VARIABLES-1);
    printf(".... The program will exit\n");
    exit(0);
  }
}

void Vector_Entry_into_Model_Variable_Initial_Condition_Model(double Value,
							      int j, Parameter_Model * Table)
{
  
  /* Definition of the state vector numerical order, from 0 to K, of model variables */
  #include <Model_Variables_Code.Include.c>
  
  if(j == X0S)         Table->X0S__0 = Value;
  else if (j == X0I )  Table->X0I__0 = Value;
  else if (j == X0L )  Table->X0L__0 = Value;
  else if (j == X0D )  Table->X0D__0 = Value;
  else if (j == W0S )  Table->W0S__0 = Value;
  else if (j == W0I )  Table->W0I__0 = Value;
  else if (j == W0L )  Table->W0L__0 = Value;
  else if (j == W0D )  Table->W0D__0 = Value;
  else if (j == X1S )  Table->X1S__0 = Value;
  else if (j == X1I )  Table->X1I__0 = Value;
  else if (j == X1L )  Table->X1L__0 = Value;
  else if (j == X1D )  Table->X1D__0 = Value;
  else if (j == W1S )  Table->W1S__0 = Value;
  else if (j == W1I )  Table->W1I__0 = Value;
  else if (j == W1L )  Table->W1L__0 = Value;
  else if (j == W1D )  Table->W1D__0 = Value;

  else if (j == YS )   Table->YS__0 = Value;
  else if (j == YI )   Table->YI__0 = Value;
  else if (j == YL )   Table->YL__0 = Value;
  else if (j == YD )   Table->YD__0 = Value;
  else{
    printf(".... INVALID VARIABLE KEY [key = %d]\n", j);
    printf(".... Provided Model Variable Codes have been correcly defined,\n");
    printf(".... the permited correspondences are:\n");
    printf(".... from key = 0 to key = %d\n", Table->MODEL_STATE_VARIABLES-1);
    printf(".... The program will exit\n");
    exit(0);
  }
}
