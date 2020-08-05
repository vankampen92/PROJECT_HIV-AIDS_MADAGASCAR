 
    x_Data = (double *)calloc(No_of_Columns/2, sizeof(double));
    y_Data = (double *)calloc(No_of_Columns/2, sizeof(double));
    for(j = (No_of_Columns/2 +YEARS_BEFORE -5); j < (No_of_Columns/2 + YEARS_BEFORE); j++) {
      x_Data[j-(No_of_Columns/2 +YEARS_BEFORE -5)] = Year_Vector[j];
      y_Data[j-(No_of_Columns/2 +YEARS_BEFORE -5)] = Age_Death_Rates_Male[i][j];
    }
    gsl_fit_linear(x_Data, 1, y_Data, 1, 5,
		   &c0, &c1, &cov00, &cov01, &cov11, &chisq);
    
    n = No_of_Columns/2 + YEARS_BEFORE + YEARS_AFTER; 
    for(j = j_First_Non_; j < n ; j++) {
      
      gsl_fit_linear_est (Year_Vector[j], c0, c1, cov00, cov01, cov11,
			  &y_Fit, &yf_err);
      City_Population[j] = y_Fit + (gsl_rng_uniform(r)-1.0) * yf_err;
    }
    free(x_Data); free(y_Data); 
