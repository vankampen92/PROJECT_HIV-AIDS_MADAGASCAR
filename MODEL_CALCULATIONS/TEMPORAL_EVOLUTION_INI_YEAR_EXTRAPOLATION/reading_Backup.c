void Reading_Sexual_Workers_Numbers_and_Prevalences(double ** Prevalence,
						    double ** Prevalence_Inf,
						    double ** Prevalence_Sup,
						    double ** SexWorkers,
						    double ** SexWorkers_Inf,
						    double ** SexWorkers_Sup,
						    int No_of_CITIES,
						    int * City_Index )
{
  int k, key;
    int No_of_CITIES_MAX;
    int No_of_COLUMNS;

    No_of_CITIES_MAX  = 12;
    No_of_COLUMNS = 19;

    double ** Data_Matrix = (double **)calloc(No_of_CITIES_MAX, sizeof(double *) );
    double * Time = (double *)calloc(No_of_COLUMNS, sizeof(double) );
    char ** CITY_NAMES = (char **)calloc( No_of_CITIES_MAX, sizeof(char *) );
    for( k = 0; k<No_of_CITIES_MAX; k++) {
      CITY_NAMES[k]  = (char *)calloc( 100, sizeof(char) );
      Data_Matrix[k] = (double *)calloc(No_of_COLUMNS, sizeof(double) );
    }

  Reading_Standard_Data_Matrix_from_File( "Sexual-Workers_2014-2017_and_Prevalence-2012-2016.dat",
					  Data_Matrix,
					  &No_of_CITIES_MAX, No_of_COLUMNS,
					  1, CITY_NAMES,
					  0, Time );
    assert(No_of_CITIES_MAX == 11);

    for (k = 0; k<No_of_CITIES; k++ ) {
      key = City_Index[k];
      
      SexWorkers_Inf[k][0] = Data_Matrix[key][0];
      SexWorkers_Sup[k][0] = Data_Matrix[key][1];
      SexWorkers[k][0]     = (Data_Matrix[key][0] + Data_Matrix[key][1])/2.0;

      SexWorkers_Inf[k][1] = Data_Matrix[key][2];
      SexWorkers_Sup[k][1] = Data_Matrix[key][3];
      SexWorkers[k][1]     = (Data_Matrix[key][2] + Data_Matrix[key][3])/2.0;

      printf("%s: SexWorkers(2014) = %g\t [ SexWorkers_Inf(2014)=%g, SexWorkers_Sup(2014)=%g ]\n",
	     CITY_NAMES[key],
	     SexWorkers[k][0], SexWorkers_Inf[k][0], SexWorkers_Sup[k][0]);
      printf("%s: SexWorkers(2017) = %g\t [ SexWorkers_Inf(2017)=%g, SexWorkers_Sup(2017)=%g ]\n",
	     CITY_NAMES[key],
	     SexWorkers[k][1], SexWorkers_Inf[k][1], SexWorkers_Sup[k][1]);
      printf("\n");

      Prevalence_Inf[k][0] = 0.01 * Data_Matrix[key][5];   /* 2005 */
      Prevalence_Sup[k][0] = 0.01 * Data_Matrix[key][6];
      Prevalence[k][0]     = 0.01 * Data_Matrix[key][4];

      Prevalence_Inf[k][1] = 0.01 * Data_Matrix[key][8];   /* 2007 */
      Prevalence_Sup[k][1] = 0.01 * Data_Matrix[key][9];
      Prevalence[k][1]     = 0.01 * Data_Matrix[key][7];

      Prevalence_Inf[k][2] = 0.01 * Data_Matrix[key][11];  /* 2010 */
      Prevalence_Sup[k][2] = 0.01 * Data_Matrix[key][12];
      Prevalence[k][2]     = 0.01 * Data_Matrix[key][10];

      Prevalence_Inf[k][3] = 0.01 * Data_Matrix[key][14];  /* 2012 */
      Prevalence_Sup[k][3] = 0.01 * Data_Matrix[key][15];
      Prevalence[k][3]     = 0.01 * Data_Matrix[key][13];

      Prevalence_Inf[k][4] = 0.01 * Data_Matrix[key][17];  /* 2016 */
      Prevalence_Sup[k][4] = 0.01 * Data_Matrix[key][18];
      Prevalence[k][4]     = 0.01 * Data_Matrix[key][16];

      printf("%s: Prevalence(2005) = %g\t [ Prevalence_Inf(2005)=%g, Prevalence_Sup(2005)=%g ]\n",
	     CITY_NAMES[key],
	     Prevalence[k][0], Prevalence_Inf[k][0], Prevalence_Sup[k][0]);
      printf("%s: Prevalence(2007) = %g\t [ Prevalence_Inf(2007)=%g, Prevalence_Sup(2007)=%g ]\n",
	     CITY_NAMES[key],
	     Prevalence[k][1], Prevalence_Inf[k][1], Prevalence_Sup[k][1]);
      printf("%s: Prevalence(2010) = %g\t [ Prevalence_Inf(2010)=%g, Prevalence_Sup(2010)=%g ]\n",
	     CITY_NAMES[key],
	     Prevalence[k][2], Prevalence_Inf[k][2], Prevalence_Sup[k][2]);
      printf("%s: Prevalence(2012) = %g\t [ Prevalence_Inf(2012)=%g, Prevalence_Sup(2012)=%g ]\n",
	     CITY_NAMES[key],
	     Prevalence[k][3], Prevalence_Inf[k][3], Prevalence_Sup[k][3]);
      printf("%s: Prevalence(2016) = %g\t [ Prevalence_Inf(2016)=%g, Prevalence_Sup(2016)=%g ]\n",
	     CITY_NAMES[key],
	     Prevalence[k][4], Prevalence_Inf[k][4], Prevalence_Sup[k][4]);
      
      printf("\n");
    }

    free(Time);
    for( k = 0; k<No_of_CITIES_MAX; k++) free( CITY_NAMES[k] );
    free(CITY_NAMES);
    for( k = 0; k<No_of_CITIES_MAX; k++) free( Data_Matrix[k] );
    free(Data_Matrix);
}
