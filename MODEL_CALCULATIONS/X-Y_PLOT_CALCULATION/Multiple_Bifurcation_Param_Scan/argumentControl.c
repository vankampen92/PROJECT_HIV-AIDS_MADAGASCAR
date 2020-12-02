#include "../Include/MODEL.h" 
/* Global Shared parameters main Program <---> ArgumentControl() */
#include "extern.h"

void ArgumentControl(int argc, char **argv)
{
  int argcount, skip;
  
  for(argcount=1; argcount<argc; argcount+=skip)
    {
      if(argv[argcount][0] == '-')
	{
	  skip = 1;
	  switch(argv[argcount][1])
	    {

	    #include <include.Parameter_Model.argumentControl.c>
	    
	    default:
	      printf("**invalid command line argument >%c< \n",
		     argv[argcount][1]);
	    case 'h':
	      Parameters_from_Command_Line(stdout, P_ARG);
	      printf("\n"); 
	      printf(" As an example,\n"); 
	      printf("        >> SIC -m 0.1 -R 100000 -d 0.01 -b 20.\n\n");
	      exit(0);
	    }
	}
      else
	{
	  printf("**invalid command line flag >%c<\n",argv[argcount][0]);
	  printf("try -h for help.\n");
	  exit(0);
	}
    }
}	




