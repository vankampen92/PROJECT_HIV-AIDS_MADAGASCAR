int Feasibility_Condition (Parameter_Table * Table);

void Fixed_Points_All(Parameter_Table * Table,
		      double *y_Sol_Lower, double *y_Sol_Inter, double *y_Sol_Upper,
		      double EPSILON);
void Fixed_Point_Lower(Parameter_Table *P, double *y_Sol, double EPSILON);
void Fixed_Point_Upper(Parameter_Table *P, double *y_Sol, double EPSILON);
void Fixed_Point_Intermediate(Parameter_Table *P,
			      double x_l,double x_u, double y_l,double y_u,
			      double *y_Sol, double EPSILON);

void Stable_Solution(double y, double x, Parameter_Table *P, double *Y);
void Stable_Solution_Free_Disease(Parameter_Table *P, double *Y);

void Stable_Solution_y(double x, Parameter_Table *Table, double *Y);
void Stable_Solution_y_Free_Disease(Parameter_Table *Table, double *Y);

void Stable_Solution_x(const double y, Parameter_Table *Table, double *Y);
void Stable_Solution_x_Free_Disease(Parameter_Table *Table, double *Y);

double Steady_State_x_Fraction(const double y, Parameter_Table *P);
double Steady_State_x_Fraction_Assymptotic(Parameter_Table *P);

double Steady_State_y_Fraction(const double x, Parameter_Table *P);
double Steady_State_y_Fraction_Assymptotic(Parameter_Table *P);
double Inverted_Steady_State_x_Fraction(const double W, Parameter_Table *P);

double Generic_Root_Finder( Parameter_Table *P, Generic_Root_Data *G );
double intermediateRoot_x_Fraction(Parameter_Table *P, double x_lo, double x_hi);

void x_y_fixed_Points_Upper(Parameter_Table *P, double EPSILON, double *x, double *y);
void x_y_fixed_Points_Lower(Parameter_Table *P, double EPSILON, double *x, double *y);
void x_y_fixed_Points_Intermediate(Parameter_Table *P,
				   double x_l,double x_u, double y_l,double y_u,
				   double EPSILON, double *x, double *y);

void x_y_Intersection_Function_Save_File(int k_File, int No, Parameter_Table *P);

double x_y_Intersection_Functions( Parameter_Table * P, int No, 
				   double *x_Data, double *y_1, double *y_2 );

#if defined CPGPLOT_REPRESENTATION
void I_N_T_E_R_S_E_C_T_I_O_N___x_y___D_I_A_G_R_A_M___S_I_N_G_L_E___P_L_O_T ( Parameter_Table * P,
                                                                             int N,
									     double * x_Data,
									     double ** y,
                                                                             char * Title_In );

void P_L_O_T_T_I_N_G___I_N_T_E_R_S_E_C_T_I_O_N___x_y___D_I_A_G_R_A_M( Parameter_Table * P, 
								      int N, 
								      int No_of_POINTS,
								      int Input_Parameter );
#endif
