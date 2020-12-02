#include "../Include/MODEL.h"

#include "extern.h"

void Parameters_from_Command_Line(FILE *fp, Parameter_Table *P)
{
  //#include "include.printPar.fixPoints.c"
	      /* Human  parameters */

#include <include.fprintPar.Human.c>
#include <include.fprintPar.Cases.c>	 
#include <include.fprintPar.POPULATION.c>
              /* Mosquito (Adult) Parameters */
#include <include.fprintPar.MosAdult.c>
              /* Mosquito (Larva) Parameters */
#include <include.fprintPar.MosLarva.c>
              /* Mosquito (Plasmodium) Parameters */
#include <include.fprintPar.Plasmodium.c>
	      	      
}

void Parameters_ModelReport(char *File, Parameter_Table *P)
{
  FILE *fp;
  Parameters_from_Command_Line(stdout, P);  
  fp = fopen(File, "w");
  Parameters_from_Command_Line(fp, P);
  fclose(fp);
}

