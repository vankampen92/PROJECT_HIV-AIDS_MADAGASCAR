void Initial_Conditions_Numerical_Integration( Parameter_Table * P, double * y_INI );

void Initial_Condition_from_Parameter_Table(Parameter_Table * P, double *Y);

void Random_Initial_Condition(Parameter_Table * P, double * Y);

void R_E_S_C_A_L_I_N_G___I_N_I_T_I_A_L___C_O_N_D_I_T_I_O_N_S ( Parameter_Table * P,
							       double * Y);

void Initial_Condition_from_Data_into_Parameter_Table (Parameter_Table * Table, double ** Data);

void Initial_Condition_from_Value_into_Parameter_Table (Parameter_Table * Table, double Value); 

void Initial_Condition_from_Initial_Values_into_Parameter_Table (Parameter_Table * Table,
								 double Initial_Adult_Population, double Initial_Female_Sexual_Workers, double Initial_Female_Sexual_Workers_Infected ); 
