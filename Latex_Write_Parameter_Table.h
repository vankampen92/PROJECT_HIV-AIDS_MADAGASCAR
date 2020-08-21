void write_Parameter_Table___RANGES___VALUES___LATEX ( char * File_Model_Parameters,
						       char * Type_of_Boundary_Parameter_Space,
						       Parameter_Table * P,
						       double * Par_MAX, double * Par_min,
						       int no_Par ); 

void write_Param_Table_PARAMETER_RANGES___LATEX ( char * File_Model_Parameters,
						  char * Type_of_Boundary_Parameter_Space,
						  Parameter_Table * P, 
						  double * Par_MAX, double * Par_min,
						  int no_Par );

void write_Param_Table_AVE_STD___LATEX( char * File_Model_Parameters,
					Parameter_Table * P, 
					double * Par_AVE, double * Par_STD, int no_Par ); 

void write_Param_Table_AVE_CI___LATEX( char * File_Model_Parameters,
				       Parameter_Table * P, 
				       double * Par_AVE,
				       double ** Confidence_Interval,
				       int no_Par );

void write_Param_Table_AVE_STD_per_CITY___LATEX_LANDSCAPE( char * File_Model_Parameters,
							   char ** CITY_NAMES, int No_of_CITIES,
							   double * City_R_0_AVE, double * City_R_0_STD, 
							   double ** City_Par_AVE, double ** City_Par_STD,
							   int no_Par,
							   Parameter_Table * P );

void write_Param_Table_AVE_STD_per_CITY___LATEX_PORTRAIT( char * File_Model_Parameters,
							  char ** CITY_NAMES, int No_of_CITIES,
							  double * City_R_0_AVE, double * City_R_0_STD, 
							  double ** City_Par_AVE, double ** City_Par_STD,
							  int no_Par,
							  Parameter_Table * P );
