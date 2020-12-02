#include <MODEL.h>

void Saving_Percentile_Time_Series(double * x_Data, int N,
				   double ** Variable_Per, int No_of_PERCENTILES,
				   int key,
				   char * Short_Name,
				   Parameter_Table * Table )
{
  int i,j;

  FILE * fp;
  //char * pf;

  char * File_Name = (char *)calloc(500, sizeof(char) );

  File_Name[0]='\0';
  strcat(File_Name, "Percentiles_");
  strcat(File_Name, Short_Name);
  strcat(File_Name, "_");
  strcat(File_Name, Table->Output_Variable_Symbol[key]);
  strcat(File_Name, ".dat");

  fp = fopen(File_Name, "w");

  for(i=0; i<N; i++){
    fprintf(fp, "%g\t", x_Data[i]);
    for(j=0; j<No_of_PERCENTILES; j++)
      if (j < (No_of_PERCENTILES-1)) fprintf(fp, "%g\t", Variable_Per[j][i]);
      else                           fprintf(fp, "%g\n", Variable_Per[j][i]);
  }
  
  fclose(fp); 
  free(File_Name); 
}
				   
