#include <MODEL.h>

void Initial_Condition_Boundary_Values(int j, double *value_0, double *value_1,
                                Parameter_Table * Table)
{
/* Definition of the state vector numerical order, from 0 to K, of model variables */
   #include <Model_Variables_Code.Include.c>

   if ( j < Table->MODEL_STATE_VARIABLES ) {
     (*value_1) = 1000000.0; /* 1000000 individual in this class */
     (*value_0) = 0.0;       /* 0 */
   }
   // if(j == XS) {
   //   (*value_1) = 1000000.0; /* 1000000 individual in this class */
   //   (*value_0) = 0.0;       /* 0 */
   // }
   // else if (j == XI ) {
   //   (*value_1) = 1000000.0; /* 1000000 individual in this class */
   //   (*value_0) = 0.0;       /* 0 */
   // }
   // else if (j == XL ) {
   //   (*value_1) = 1000000.0; /* 1000000 individual in this class */
   //   (*value_0) = 0.0;       /* 0 */
   // }
   // else if (j == XD ) {
   //   (*value_1) = 1000000.0; /* 1000000 individual in this class */
   //   (*value_0) = 0.0;       /* 0 */
   // }
   // else if (j == WS ) {
   //   (*value_1) = 1000000.0; /* 1000000 individual in this class */
   //   (*value_0) = 0.0;       /* 0 */
   // }
   // else if (j == WI ) {
   //   (*value_1) = 1000000.0; /* 1000000 individual in this class */
   //   (*value_0) = 0.0;       /* 0 */
   // }
   // else if (j == WL ) {
   //   (*value_1) = 1000000.0; /* 1000000 individual in this class */
   //   (*value_0) = 0.0;       /* 0 */
   // }
   // else if (j == WD ) {
   //   (*value_1) = 1000000.0; /* 1000000 individual in this class */
   //   (*value_0) = 0.0;       /* 0 */
   // }
   // else if (j == YS )  {
   //   (*value_1) = 1000000.0; /* 1000000 individual in this class */
   //   (*value_0) = 0.0;       /* 0 */
   // }
   // else if (j == YI )  {
   //   (*value_1) = 1000000.0; /* 1000000 individual in this class */
   //   (*value_0) = 0.0;       /* 0 */
   // }
   // else if (j == YL )  {
   //   (*value_1) = 1000000.0; /* 1000000 individual in this class */
   //   (*value_0) = 0.0;       /* 0 */
   // }
   // else if (j == YD )  {
   //   (*value_1) = 1000000.0; /* 1000000 individual in this class */
   //   (*value_0) = 0.0;       /* 0 */
   // }
   else{
     printf(".... INVALID VARIABLE KEY [key = %d]\n", j);
     printf(".... The permited correspondences are:\n");
     printf(".... The program will exit\n");
     exit(0);
   }
}
