#include <MODEL.h>

void Vector_Entry_into_Model_Variable_Initial_Condition_Table(double Value, 
								int j, Parameter_Table * Table)
{
 
  /* Definition of the state vector numerical order, from 0 to K, of model variables */
  #include <Model_Variables_Code.Include.c>

  if(j == XS)          Table->XS__0 = Value; 
  else if (j == YS )   Table->YS__0 = Value; 
  else{
    printf(".... INVALID VARIABLE KEY [key = %d]\n", j);
    printf(".... If Model Variable Codes have been correcly defined,\n");
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

  if(j == XS)          Table->XS__0 = Value; 
  else if (j == YS )   Table->YS__0 = Value;  
  else{
    printf(".... INVALID VARIABLE KEY [key = %d]\n", j);
    printf(".... If Model Variable Codes have been correcly defined,\n");
    printf(".... the permited correspondences are:\n");
    printf(".... from key = 0 to key = %d\n", Table->MODEL_STATE_VARIABLES-1);
    printf(".... The program will exit\n");
    exit(0);
  }
}
