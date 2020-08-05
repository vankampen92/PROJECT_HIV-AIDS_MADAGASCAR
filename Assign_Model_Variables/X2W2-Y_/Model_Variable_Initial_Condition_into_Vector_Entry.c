#include <MODEL.h>

double Model_Variable_Initial_Condition_into_Vector_Entry_Table(int j, Parameter_Table * Table)
{
  double Value; 
  /* Definition of the state vector numerical order, from 0 to K, of model variables */
  #include <Model_Variables_Code.Include.c>
  
  if(j == X0S)         Value = Table->X0S__0 ;

  else if (j == W0S )  Value = Table->W0S__0 ;

  else if (j == X1S )  Value = Table->X1S__0 ;

  else if (j == W1S )  Value = Table->W1S__0 ;
  
  else if (j == YS )   Value = Table->YS__0 ;

  else{
    printf(".... INVALID VARIABLE KEY [key = %d]\n", j);
    printf(".... Provided Model Variable Codes have been correcly defined,\n");
    printf(".... the permited correspondences are:\n");
    printf(".... from key = 0 to key = %d\n", Table->MODEL_STATE_VARIABLES-1);
    printf(".... The program will exit\n");
    exit(0);
  }

  return(Value); 
}

double Model_Variable_Initial_Condition_into_Vector_Entry_Model(int j, Parameter_Model * Table)
{
  double Value; 
  
  /* Definition of the state vector numerical order, from 0 to K, of model variables */
  #include <Model_Variables_Code.Include.c>
  
  if(j == X0S)         Value = Table->X0S__0 ;

  else if (j == W0S )  Value = Table->W0S__0 ;

  else if (j == X1S )  Value = Table->X1S__0 ;

  else if (j == W1S )  Value = Table->W1S__0 ;
  
  else if (j == YS )   Value = Table->YS__0 ;
  
  else{
    printf(".... INVALID VARIABLE KEY [key = %d]\n", j);
    printf(".... Provided Model Variable Codes have been correcly defined,\n");
    printf(".... the permited correspondences are:\n");
    printf(".... from key = 0 to key = %d\n", Table->MODEL_STATE_VARIABLES-1);
    printf(".... The program will exit\n");
    exit(0);
  }

  return(Value); 
}
