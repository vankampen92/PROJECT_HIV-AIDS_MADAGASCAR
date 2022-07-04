#include <MODEL.h>

void write_Parameter_Table___RANGES___VALUES___LATEX ( char * File_Model_Parameters,
						       char * Type_of_Boundary_Parameter_Space,
						       Parameter_Table * P,
						       double * Par_MAX, double * Par_min,
						       int no_Par )
{
  double Par_Value;
  int i, k;
  FILE *fp = fopen( File_Model_Parameters, "w" );
  char Parameter_Name[100];
  char Parameter_Symbol[50];

  printf(" Writing latex parameter table in %s\n",
	 File_Model_Parameters);
  printf(" Parameter Space Definition Code (Boundary File): %s\n",
	 Type_of_Boundary_Parameter_Space);
  
  fprintf(fp, "\\begin{table}\n");
  // fprintf(fp, "\\noindent\n");
  fprintf(fp, "\\rowcolors{1}{green}{pink}\n"); 
  fprintf(fp, "\\centering\n"); 
  fprintf(fp, "\\begin{tabular}{p{5cm}lcccc}\n");
  fprintf(fp, "{\\bf Model Parameter} & {\\bf Symbol} & {\\bf Min. Value} & {\\bf Max. Value} & {\\bf Value}""\\""""\\""\n");
  fprintf(fp, "\\hline");
  fprintf(fp, "\\hline\n");

  for ( i = 0; i < no_Par; i++){

    k = P->Index[i];

    Par_Value = AssignStructValue_to_VectorEntry (k, P);

    AssignLabel_to_Model_Parameters__LATEX(k , Parameter_Name, P);

    AssignLabel_to_Model_Parameters__LATEX__SYMBOL(k , Parameter_Symbol, P);

    fprintf(fp, "%s & %s & %4.2f & %4.2f & %4.2f""\\""""\\""\n", 
	    Parameter_Name, Parameter_Symbol, Par_min[i], Par_MAX[i], Par_Value);
  }

  fprintf(fp, "\\hline");
  fprintf(fp, "\\hline\n");
  

  fprintf(fp, "\\end{tabular}\n");

  //fprintf(fp, "\\vspace{1cm}\n");
  //fprintf(fp, "\\noindent");
  fprintf(fp, "\\caption{Model Parameters for the AIDS-HIV transmission model. Model parameters boundary values defined in a boundary file.}\n");

  fprintf(fp, "\\end{table}\n");
  fclose(fp);

  printf(" End writing latex parameter table!\n");
}

void write_Param_Table_PARAMETER_RANGES___LATEX ( char * File_Model_Parameters,
						  char * Type_of_Boundary_Parameter_Space,
						  Parameter_Table * P, 
						  double * Par_MAX, double * Par_min,
						  int no_Par )
{
  int i, k;
  FILE *fp = fopen( File_Model_Parameters, "w" );
  char Parameter_Name[100];
  char Parameter_Symbol[50];

  printf(" Writing latex parameter table in %s\n",
	 File_Model_Parameters);
  printf(" Parameter Space Definition Code (Boundary File): %s\n",
	 Type_of_Boundary_Parameter_Space);

  fprintf(fp, "\\begin{table}\n");
  // fprintf(fp, "\\noindent\n");
  fprintf(fp, "\\rowcolors{1}{green}{pink}\n"); 
  fprintf(fp, "\\centering\n"); 
  fprintf(fp, "\\begin{tabular}{lccc}\n");  
  fprintf(fp, "{\\bf Model Parameter} & {\\bf Symbol} & {\\bf Min. Value} & {\\bf Max. Value}""\\""""\\""\n"); 
  fprintf(fp, "\\hline");
  fprintf(fp, "\\hline\n");
  
  for ( i = 0; i < no_Par; i++){

    k = P->Index[i];
    
    AssignLabel_to_Model_Parameters__LATEX(k , Parameter_Name, P);

    AssignLabel_to_Model_Parameters__LATEX__SYMBOL(k , Parameter_Symbol, P);
    
    fprintf(fp, "%s & %s & %5.3f & %5.3f""\\""""\\""\n",
	    Parameter_Name, Parameter_Symbol, Par_min[i], Par_MAX[i]);
  }

  fprintf(fp, "\\hline");
  fprintf(fp, "\\hline\n");
  

  fprintf(fp, "\\end{tabular}\n");
  // fprintf(fp, "\\vspace{1cm}\n");
  // fprintf(fp, "\\noindent");

  fprintf(fp, "{\\caption Model Parameter Ranges for the AIDS-HIV transmission model. Model parameters boundary values defined in a boundary file.}\n");

  fprintf(fp, "\\end{table}\n");
  fclose(fp);
}

void write_Param_Table_AVE_STD___LATEX( char * File_Model_Parameters,
					Parameter_Table * P, 
					double * Par_AVE, double * Par_STD, int no_Par )
{
  int i, k;
  FILE *fp = fopen( File_Model_Parameters, "w" );
  char Parameter_Name[100];
  char Parameter_Symbol[50];

  fprintf(fp, "\\begin{table}\n");
  // fprintf(fp, "\\noindent\n");
  fprintf(fp, "\\rowcolors{1}{green}{pink}\n"); 
  fprintf(fp, "\\centering\n"); 
  fprintf(fp, "\\begin{tabular}{lccc}\n");  
  fprintf(fp, "{\\bf Model Parameter} & {\\bf Symbol} & {\\bf Average} & {\\bf Stardard Deviation}""\\""""\\""\n"); 
  fprintf(fp, "\\hline");
  fprintf(fp, "\\hline\n");
  
  for ( i = 0; i < no_Par; i++){

    k = P->Index[i];
    
    AssignLabel_to_Model_Parameters__LATEX(k , Parameter_Name, P);

    AssignLabel_to_Model_Parameters__LATEX__SYMBOL(k , Parameter_Symbol, P);
    
    fprintf(fp, "%s & %s & %5.3f & %5.3f""\\""""\\""\n", Parameter_Name, Parameter_Symbol, Par_AVE[i], Par_STD[i]);
  }

  fprintf(fp, "\\hline");
  fprintf(fp, "\\hline\n");
  

  fprintf(fp, "\\end{tabular}\n");
  //fprintf(fp, "\\vspace{1cm}\n");
  //fprintf(fp, "\\noindent");

  fprintf(fp, "\\caption{Model Parameter Average Values and Deviations for the AIDS-HIV transmission model.}\n");

  fprintf(fp, "\\end{table}\n");
  fclose(fp);
}

void write_Param_Table_AVE_CI___LATEX( char * File_Model_Parameters,
				       Parameter_Table * P, 
				       double * Par_AVE,
				       double ** Confidence_Interval,
				       int no_Par )
{
  int i, k;
  FILE *fp = fopen( File_Model_Parameters, "w" );
  char Parameter_Name[100];
  char Parameter_Symbol[50];

  fprintf(fp, "\\begin{table}\n");
  // fprintf(fp, "\\noindent\n");
  fprintf(fp, "\\rowcolors{1}{green}{pink}\n"); 
  fprintf(fp, "\\centering\n"); 
  fprintf(fp, "\\begin{tabular}{lccc}\n");  
  fprintf(fp, "{\\bf Model Parameter} & {\\bf Symbol} & {\\bf Average} & {\\bf Confidence Interval}""\\""""\\""\n"); 
  fprintf(fp, "\\hline");
  fprintf(fp, "\\hline\n");
  
  for ( i = 0; i < no_Par; i++){

    k = P->Index[i];
    
    AssignLabel_to_Model_Parameters__LATEX(k , Parameter_Name, P);

    AssignLabel_to_Model_Parameters__LATEX__SYMBOL(k , Parameter_Symbol, P);
    
    fprintf(fp, "%s & %s & %5.3f & (%5.3f, %5.3f)""\\""""\\""\n", Parameter_Name, Parameter_Symbol, 
	    Par_AVE[i], Confidence_Interval[i][0], Confidence_Interval[i][1]);
  }
  fprintf(fp, "\\hline");
  fprintf(fp, "\\hline\n");

  fprintf(fp, "\\end{tabular}\n");
  //fprintf(fp, "\\vspace{1cm}\n");
  //fprintf(fp, "\\noindent");

  fprintf(fp, "\\caption{Model Parameter Average Values and Confidence Intervals for the AIDS-HIV transmission model.}\n");

  fprintf(fp, "\\end{table}\n");
  fclose(fp);
}

void write_Param_Table_AVE_STD_per_CITY___LATEX_LANDSCAPE( char * File_Model_Parameters,
							   char ** CITY_NAMES, int No_of_CITIES,
							   double * City_R_0_AVE, double * City_R_0_STD, 
							   double ** City_Par_AVE, double ** City_Par_STD,
							   int no_Par,
							   Parameter_Table * P )
{
  /* Input: 
     . P, Parameter Table, 
     . City_R_0_AVE
     . City_R_0_STD
     . City_Par_AVE
     . City_Par_STD
     . No_of_CITIES 
     . no_Par, No of PARAMETERS that are requested to save in the LaTeX table. 
     
     Output: 
     . File_Model_Parameters, a file containing a LaTeX friendly table 
  */
  int i, k;
  FILE *fp = fopen( File_Model_Parameters, "w" );
  char Parameter_Name[100];
  char Parameter_Symbol[50];
  char cccc[MODEL_PARAMETERS_MAXIMUM];
  char * pF;
  
  cccc[0] = '\0';
  for(i=0; i < no_Par+1; i++)
    pF = strcat(cccc, "c");

  fprintf(fp, "\\begin{table}\n");
  // fprintf(fp, "\\noindent\n");
  fprintf(fp, "\\rowcolors{1}{green}{pink}\n"); 
  fprintf(fp, "\\centering\n"); 
  fprintf(fp, "\\begin{tabular}{l%s}\n", cccc);  
  fprintf(fp, "{\\bf City} & ");
  for (i=0; i < no_Par; i++) {
    k = P->Index[i];
    AssignLabel_to_Model_Parameters__LATEX__SYMBOL(k , Parameter_Symbol, P);
    fprintf(fp, "{\\bf %s} & ", Parameter_Symbol);
  }
  fprintf(fp, "{\\bf $R_0$} ""\\""""\\""\n"); 
  fprintf(fp, "\\hline");
  fprintf(fp, "\\hline\n");

  for (k=0; k < No_of_CITIES; k++) {
    
    fprintf(fp, "%s &", CITY_NAMES[k]); 
	    
    for (i=0; i < no_Par; i++){   
      fprintf(fp, "%5.3f $\\pm$ %5.3f & ", City_Par_AVE[k][i], City_Par_STD[k][i]);
    }

    fprintf(fp, "%5.3f $\\pm$ %5.3f", City_R_0_AVE[k], City_R_0_STD[k]);
    
    fprintf(fp, """\\""""\\""\n"); 
  }

  fprintf(fp, "\\hline");
  fprintf(fp, "\\hline\n");
  

  fprintf(fp, "\\end{tabular}\n");
  //fprintf(fp, "\\vspace{1cm}\n");
  //fprintf(fp, "\\noindent");

  fprintf(fp, "\\caption{Model Parameter average values, and $R_0$, and their standard deviations for the AIDS-HIV transmission model.}\n");

  fprintf(fp, "\\end{table}\n");
  fclose(fp);
}


void write_Param_Table_AVE_STD_per_CITY___LATEX_PORTRAIT( char * File_Model_Parameters,
							  char ** CITY_NAMES, int No_of_CITIES,
							  double * City_R_0_AVE, double * City_R_0_STD, 
							  double ** City_Par_AVE, double ** City_Par_STD,
							  int no_Par,
							  Parameter_Table * P )
{
  /* Input: 
     . P, Parameter Table, 
     . City_R_0_AVE[k],    R_0 value for k-th city 
     . City_R_0_STD[k],    R_0 STD value for k-th city 
     . City_Par_AVE[k][p], p-th Parameter value for k-th city 
     . City_Par_STD[k][p], p-th Parameter value STD for k-th city 
     . No_of_CITIES 
     . no_Par, No of PARAMETERS that are requested to save in the LaTeX table. 
     
     Output: 
     . File_Model_Parameters, a file containing a LaTeX friendly table 
  */
  int i, k, b;
  FILE *fp = fopen( File_Model_Parameters, "w" );
 
  char Parameter_Symbol[50];
  char * pF;

  char cccc[50];

  assert( (No_of_CITIES-1) < 50 );
  
  b = 0; 
  for (k=0; k < No_of_CITIES; k++)
    if(  strcmp(CITY_NAMES[k], "Aabe" ) == 0 ) b = 1;
  
  cccc[0] = '\0';
  if (b == 0) for(i=0; i < No_of_CITIES; i++) pF = strcat(cccc, "c");
  else        for(i=0; i < No_of_CITIES-1; i++) pF = strcat(cccc, "c"); 
  
  fprintf(fp, "\\begin{sidewaystable}\n");
  // fprintf(fp, "\\caption{Model Parameter average values, and $R_0$, and their standard deviations for the AIDS-HIV transmission model.}\n");
  // fprintf(fp, "\\smallskip\n");

  // fprintf(fp, "\\hline\n");
  // fprintf(fp, "\\hline\n");

  // fprintf(fp, "\\noindent\n");
  // fprintf(fp, "\\rowcolors{1}{green}{pink}\n");
  fprintf(fp, "\\rowcolors{1}{blue!15}{white}\n");
  fprintf(fp, "\\centering\n"); 
  fprintf(fp, "\\begin{tabular}{c%s}\n", cccc);  
  // fprintf(fp, "{\\bf Symbol} ");
  fprintf(fp, " ");
  for(k=0; k<No_of_CITIES; k++)   
    if(  strcmp(CITY_NAMES[k], "Aabe") != 0 ) fprintf(fp, "& {\\bf %s} ", CITY_NAMES[k]);
    // if( k != 8 ) fprintf(fp, "& {\\bf %s} ", CITY_NAMES[k]);
  
  fprintf(fp, """\\""""\\""\n"); 
  fprintf(fp, "\\hline");
  fprintf(fp, "\\hline\n");

  for (i=0; i < no_Par; i++) {
    
    AssignLabel_to_Model_Parameters__LATEX__SYMBOL(P->Index[i] , Parameter_Symbol, P);
    fprintf(fp, "{\\bf %s} ", Parameter_Symbol);
  
    for (k=0; k < No_of_CITIES; k++) 
      //if( k != 8 )
      if(  strcmp(CITY_NAMES[k], "Aabe") != 0 )
	fprintf(fp, "& %*.4f $\\pm$ %*.4f ", 4, City_Par_AVE[k][i], 4, City_Par_STD[k][i]);
    
    fprintf(fp, """\\""""\\""\n"); 
  }

  fprintf(fp, "{\\bf $R_0$} ");
  
  for (k=0; k < No_of_CITIES; k++)
    // if( k != 8 )
    if(  strcmp(CITY_NAMES[k], "Aabe") != 0 )
      fprintf(fp, "& %5.3f $\\pm$ %5.3f", City_R_0_AVE[k], City_R_0_STD[k]);

  fprintf(fp, """\\""""\\""\n"); 
      
  fprintf(fp, "\\hline");
  fprintf(fp, "\\hline\n");
  
  fprintf(fp, "\\end{tabular}\n");
  //fprintf(fp, "\\vspace{1cm}\n");
  //fprintf(fp, "\\noindent");
  fprintf(fp, "\\caption{Average model parameter values, and their corresponding values for $R_0$,  and their standard deviations.}\n");
  
  fprintf(fp, "\\label{Table:Parameter_Values}\n"); 

  fprintf(fp, "\\end{sidewaystable}\n");
  fclose(fp);
}

