#include <MODEL.h>

double Model_Variable_Initial_Condition_into_Vector_Entry_Table(int j, Parameter_Table * Table)
{
  double Value; 
  /* Definition of the state vector numerical order, from 0 to K, of model variables */
  #include <Model_Variables_Code.Include.c>
  
  if(j == X0S)         Value = Table->X0S__0 ;
  else if (j == X0I )  Value = Table->X0I__0 ;
  else if (j == X0L )  Value = Table->X0L__0 ;
  else if (j == X0D )  Value = Table->X0D__0 ;
  else if (j == W0S )  Value = Table->W0S__0 ;
  else if (j == W0I )  Value = Table->W0I__0 ;
  else if (j == W0L )  Value = Table->W0L__0 ;
  else if (j == W0D )  Value = Table->W0D__0 ;
  else if (j == X1S )  Value = Table->X1S__0 ;
  else if (j == X1I )  Value = Table->X1I__0 ;
  else if (j == X1L )  Value = Table->X1L__0 ;
  else if (j == X1D )  Value = Table->X1D__0 ;
  else if (j == W1S )  Value = Table->W1S__0 ;
  else if (j == W1I )  Value = Table->W1I__0 ;
  else if (j == W1L )  Value = Table->W1L__0 ;
  else if (j == W1D )  Value = Table->W1D__0 ;

  else if (j == YS )   Value = Table->YS__0 ;
  else if (j == YI )   Value = Table->YI__0 ;
  else if (j == YL )   Value = Table->YL__0 ;
  else if (j == YD )   Value = Table->YD__0 ;
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
  else if (j == X0I )  Value = Table->X0I__0 ;
  else if (j == X0L )  Value = Table->X0L__0 ;
  else if (j == X0D )  Value = Table->X0D__0 ;
  else if (j == W0S )  Value = Table->W0S__0 ;
  else if (j == W0I )  Value = Table->W0I__0 ;
  else if (j == W0L )  Value = Table->W0L__0 ;
  else if (j == W0D )  Value = Table->W0D__0 ;
  else if (j == X1S )  Value = Table->X1S__0 ;
  else if (j == X1I )  Value = Table->X1I__0 ;
  else if (j == X1L )  Value = Table->X1L__0 ;
  else if (j == X1D )  Value = Table->X1D__0 ;
  else if (j == W1S )  Value = Table->W1S__0 ;
  else if (j == W1I )  Value = Table->W1I__0 ;
  else if (j == W1L )  Value = Table->W1L__0 ;
  else if (j == W1D )  Value = Table->W1D__0 ;

  else if (j == YS )   Value = Table->YS__0 ;
  else if (j == YI )   Value = Table->YI__0 ;
  else if (j == YL )   Value = Table->YL__0 ;
  else if (j == YD )   Value = Table->YD__0 ;
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
