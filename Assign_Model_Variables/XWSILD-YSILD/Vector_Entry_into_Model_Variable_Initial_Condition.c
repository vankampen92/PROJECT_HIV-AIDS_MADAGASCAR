#include <MODEL.h>

void Vector_Entry_into_Model_Variable_Initial_Condition_Table(double Value,
							      int j, Parameter_Table * Table)
{
  
  /* Definition of the state vector numerical order, from 0 to K, of model variables */
  #include <Model_Variables_Code.Include.c>
  
  if(j == XS)          Table->XS__0 = Value;
  else if (j == XI )   Table->XI__0 = Value;
  else if (j == XL )   Table->XL__0 = Value;
  else if (j == XD )   Table->XD__0 = Value;
  else if (j == WS )   Table->WS__0 = Value;
  else if (j == WI )   Table->WI__0 = Value;
  else if (j == WL )   Table->WL__0 = Value;
  else if (j == WD )   Table->WD__0 = Value;
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
  
  if(j == XS)          Table->XS__0 = Value;
  else if (j == XI )   Table->XI__0 = Value;
  else if (j == XL )   Table->XL__0 = Value;
  else if (j == XD )   Table->XD__0 = Value;
  else if (j == WS )   Table->WS__0 = Value;
  else if (j == WI )   Table->WI__0 = Value;
  else if (j == WL )   Table->WL__0 = Value;
  else if (j == WD )   Table->WD__0 = Value;

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
