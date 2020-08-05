#include <MODEL.h>

double Model_Variable_Initial_Condition_into_Vector_Entry_Table(int j, Parameter_Table * Table)
{
  double Value;
  /* Definition of the state vector numerical order, from 0 to K, of model variables */
  #include <Model_Variables_Code.Include.c>

  if(j == XS)         Value = Table->XS__0 ;
  else if (j == XI )  Value = Table->XI__0 ;
  else if (j == XL )  Value = Table->XL__0 ;
  else if (j == XD )  Value = Table->XD__0 ;
  else if (j == WS )  Value = Table->WS__0 ;
  else if (j == WI )  Value = Table->WI__0 ;
  else if (j == WL )  Value = Table->WL__0 ;
  else if (j == WD )  Value = Table->WD__0 ;


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

  if(j == XS)         Value = Table->XS__0 ;
  else if (j == XI )  Value = Table->XI__0 ;
  else if (j == XL )  Value = Table->XL__0 ;
  else if (j == XD )  Value = Table->XD__0 ;
  else if (j == WS )  Value = Table->WS__0 ;
  else if (j == WI )  Value = Table->WI__0 ;
  else if (j == WL )  Value = Table->WL__0 ;
  else if (j == WD )  Value = Table->WD__0 ;

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
