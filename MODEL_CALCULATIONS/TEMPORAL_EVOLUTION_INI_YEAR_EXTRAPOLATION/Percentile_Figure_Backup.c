/* Plotting ensamble of projected distributions (meadian and percentiles):
     . k: Cities
     . n: Initial "disease-invasion" year
     . j: Parametric configuration (over a No_of_Parameter_Sets for each city and invasion year)
  */

for(k = 0; k<No_of_CITIES; k++) {
    if ( City_Index[k] != 8 )
      for(n = 0; n<No_of_INITIAL_YEARS; n++) {

	I_Time = I_Time_Total - n;
	Time_0 = 2000.0 + (double)n; // Time_1 will be defined by command line argument!!!
	Ini_Year = Time_0;
	
	Replicates = REALIZATIONS[k][n];
	
	Variable_Per    = (double **)calloc(No_of_PERCENTILES, sizeof(double *) );
	for(j = 0; j < No_of_PERCENTILES; j++ )
	  Variable_Per[j] = (double *)calloc(I_Time, sizeof(double) );
	
	Variable = (double **)calloc(Replicates, sizeof(double *) );
	for(j = 0; j < Replicates; j++ )
	  Variable[j] = (double *)calloc(I_Time, sizeof(double) );
	
	for (i=0; i<SUB_OUTPUT_VARIABLES; i++) {
	  
	  SAME = 0;
	  
	  Table.CPG->CPG__PANEL__X =  1;
	  Table.CPG->CPG__PANEL__Y =  2;
	  
	  Table.CPG->type_of_Width =  5;
	  Table.CPG->color_Index   =  3;
	  Table.CPG->type_of_Symbol = 1;
	  Table.CPG->type_of_Line   = 1;
	  
	  key = Table.OUTPUT_VARIABLE_INDEX[i];
	  AssignCPGPLOT_Symbol_to_Output_Variables(key, Out_Var_Symbol, &Table);
	  
	  Table.CPG->CPG_SCALE_X   = 1;                     Table.CPG->CPG_SCALE_Y   =  0;
	  Table.CPG->CPG_RANGE_X_0 = CPG_RANGE_X_0;         Table.CPG->CPG_RANGE_Y_0 =  0.0;
	  Table.CPG->CPG_RANGE_X_1 = CPG_RANGE_X_1 + 0.5;   Table.CPG->CPG_RANGE_Y_1 =  1.0E+05;
	  
	  // Prevalences:
	  /* -v0 10   Total Female Sexual Worker Disease Prevalence     */
	  /* -v1  8   Total Female Disease Prevalence                   */
	  /* -v2  9   Total Male_Disease Prevalence                     */
	  /* -v3 11   Total Female Non Sexual Worker Disease Prevalence */
	  /* -v4 7    Total Prevalence                                  */
	  if( key == 7 || key == 8 || key == 9 || key == 10 || key == 11 ) {
	    Table.CPG->CPG_SCALE_Y   =  1;
	    Table.CPG->CPG_RANGE_Y_0 =  0.0;
	    Table.CPG->CPG_RANGE_Y_1 =  1.0; //0.5
	  }
	  if( key == 4 ) { /* Total Sex Worker Population: Observed Variable */ 
	    Table.CPG->CPG_SCALE_Y   =  1;
	    Table.CPG->CPG_RANGE_Y_0 =  0.0;
	    Table.CPG->CPG_RANGE_Y_1 =  7.0E+04; //0.5
	  }
	  if( key == 6 ) { /* Total Population: Observed Variables */
	    Table.CPG->CPG_SCALE_Y   =  1;
	    Table.CPG->CPG_RANGE_Y_0 =  0.0;
	    Table.CPG->CPG_RANGE_Y_1 =  4.0E+6; //0.5
	  }
	  if( key == 14 ) { /* Number of Infected Individuals within Sexual Workers */
	    Table.CPG->CPG_SCALE_Y   =  1;
	    Table.CPG->CPG_RANGE_Y_0 =  0.0;
	    Table.CPG->CPG_RANGE_Y_1 =  19000.0; //0.5
	  }

	  for(j=0; j < Replicates; j++) { 
	    for(l=0; l < I_Time; l++) {
	      Variable[j][l] = Temporal_Evolution[k][n][i][j][l];
	      x_Data[l] = Ini_Year + l;
	    }
	  }	  
	  
	  Percentile_Calculation_Simple(x_Data, Variable, I_Time, Replicates,
					Per, No_of_PERCENTILES,
					Variable_Per);

	  Saving_Percentile_Time_Series( x_Data, I_Time, Variable_Per, No_of_PERCENTILES,
					 key, City_Short_Names[k], 
					 &Table );

	  ///////////////////////////////////////////////////////////////////////////////
	  printf("No of Parametric Configiurations: %d: ", Replicates);
	  
	  Print_Percentile_Levels_Time_Series(No_of_PERCENTILES, I_Time,
					       Per, Variable_Per,
					       City_Short_Names[City_Index[k]]);
	  Press_Key(); 
	  ///////////////////////////////////////////////////////////////////////////////?
	  
	  if( key == 7 || key == 10 ) { 
	    Saving_2012_2016_2033_Percentiles (F,
					       x_Data, I_Time, Variable_Per, No_of_PERCENTILES,
					       key, City_Names[City_Index[k]],
					       &Table);
	  }

	  for( j = 0; j<No_of_PERCENTILES; j++ ) {

	    /*  0.50 Median */
	    Table.CPG->type_of_Width =  5;
	    Table.CPG->color_Index   =  4;
	    Table.CPG->type_of_Symbol = 1;
	    Table.CPG->type_of_Line   = 1;
	    /* 0.95 and 0.05 or extreme values */
	    if ( j == 0 || j == (No_of_PERCENTILES-1) ) {
		Table.CPG->type_of_Width =  3;
		Table.CPG->color_Index   =  11;
		Table.CPG->type_of_Symbol = 1;
		Table.CPG->type_of_Line   = 1;
	    }
	    if( No_of_PERCENTILES == 5 ){  
	      /* 0.25 and 0.75 or intermediate values */
	      if ( j == 1 || j == (No_of_PERCENTILES-2) ) { 	
		Table.CPG->type_of_Width =  1;
		Table.CPG->color_Index   =  11;
		Table.CPG->type_of_Symbol = 1;
		Table.CPG->type_of_Line   = 3;
	      }
	    }
	    
	    CPGPLOT___X_Y___P_L_O_T_T_I_N_G___S_A_M_E___P_L_O_T  ( Table.CPG, SAME,
								   I_Time,
								   x_Data, Variable_Per[j],
								   "Year",
								   Out_Var_Symbol,
								   City_Names[City_Index[k]],
								   Table.CPG->CPG_SCALE_X,
								   Table.CPG->CPG_SCALE_Y );
	    SAME = 1;
	  }

	  /* It the i-th SUB_OUTPUT_VARIABLES an OBSERVED VARIABLE??? */
	  if ( key == 4 || key == 6 || key == 14 ) {
	    for(l=0; l < I_Time; l++) {
	      x_Data[l] = Ini_Year + l;
	      if (l < I_Time_2000 - n)
	      y_Data[l] = Observed_Population_Data[k][n][i][l];
	    }
	    
	    Table.CPG->type_of_Symbol = 25;
	    Table.CPG->color_Index    = 1;
	    Table.CPG->type_of_Line   = 3;
	    
	    CPGPLOT___X_Y___S_C_A_T_T_E_R_E_D___S_A_M_E___P_L_O_T ( Table.CPG, SAME,
								    I_Time_2000 - n,
								    x_Data, y_Data,
								    "Year",
								    Out_Var_Symbol,
								    City_Names[City_Index[k]],
								    Table.CPG->CPG_SCALE_X,
								    Table.CPG->CPG_SCALE_Y );
	  }
	  
	  if ( key == 10 ) {
	    x_Data[0]     = 2005.0;            x_Data[1]     = 2007.0;
	    xn_Data[0][0] = 2005.0;            xn_Data[0][1] = 2007.0;
	    xn_Data[1][0] = 2005.0;            xn_Data[1][1] = 2007.0;

	    x_Data[2]     = 2010.0;            x_Data[3]     = 2012.0;
	    xn_Data[0][2] = 2010.0;            xn_Data[0][3] = 2012.0;
	    xn_Data[1][2] = 2010.0;            xn_Data[1][3] = 2012.0;

	    x_Data[4]     = 2016.0;            
	    xn_Data[0][4] = 2016.0;            
	    xn_Data[1][4] = 2016.0;            

	    for( s = 0; s<5; s++ ) {
	      y_Data[s]     = Prevalence[k][s];      
	      yn_Data[0][s] = Prevalence_Inf[k][s];  
	      yn_Data[1][s] = Prevalence_Sup[k][s];  
	    }
	    
	    /* y_Data[0]     = Prevalence[k][0];      y_Data[1]     = Prevalence[k][1];     */
	    /* yn_Data[0][0] = Prevalence_Inf[k][0];  yn_Data[0][1] = Prevalence_Inf[k][1]; */
	    /* yn_Data[1][0] = Prevalence_Sup[k][0];  yn_Data[1][1] = Prevalence_Sup[k][1]; */

	    /* y_Data[2]     = Prevalence[k][2];      y_Data[3]     = Prevalence[k][3];     */
	    /* yn_Data[0][2] = Prevalence_Inf[k][2];  yn_Data[0][3] = Prevalence_Inf[k][3]; */
	    /* yn_Data[1][2] = Prevalence_Sup[k][2];  yn_Data[1][3] = Prevalence_Sup[k][3]; */

	    /* y_Data[4]     = Prevalence[k][4];                                            */
	    /* yn_Data[0][4] = Prevalence_Inf[k][4];                                        */
	    /* yn_Data[1][4] = Prevalence_Sup[k][4];                                        */  
	  }
	  if ( key == 4 ) {
	    x_Data[0]     = 2014.0;            x_Data[1]     = 2017.0;
	    xn_Data[0][0] = 2014.0;            xn_Data[0][1] = 2017.0;
	    xn_Data[1][0] = 2014.0;            xn_Data[1][1] = 2017.0;
	    
	    y_Data[0]     = SexWorkers[k][0];      y_Data[1]     = SexWorkers[k][1];
	    yn_Data[0][0] = SexWorkers_Inf[k][0];  yn_Data[0][1] = SexWorkers_Inf[k][1];
	    yn_Data[1][0] = SexWorkers_Sup[k][0];  yn_Data[1][1] = SexWorkers_Sup[k][1];
	  }
	  if ( key == 10 || key == 4 ) {
	    Table.CPG->color_Index    = 8;
	    Table.CPG->type_of_Width  = 5;
	    Table.CPG->type_of_Symbol = 4;
	    Table.CPG->type_of_Line   = 1;
	    
	  int BAR_TIP_LENGTH = 5;
	  CPGPLOT___X_Y___P_L_O_T_T_I_N_G___2DIR___E_R_R_O_R___B_A_R_S ( Table.CPG, 2,
									 x_Data, xn_Data,
									 y_Data, yn_Data,
									 BAR_TIP_LENGTH,
									 0);
	  }
	}
	
	for(j = 0; j < No_of_PERCENTILES; j++ )
	  free(Variable_Per[j]);
	free(Variable_Per);
	
	for(j = 0; j < Replicates; j++ )
	  free(Variable[j]);
	free(Variable);
	
	getchar();
      }
  }
