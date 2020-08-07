#include <MODEL.h>

extern gsl_rng * r; 

void Random_Initial_Guess_within_Boundaries_Model (Parameter_Model * Initial_Guess,
						   Parameter_Space * S )
{
  int i, key;
  double value, lo_P, hi_P;

  for ( i=0; i < S->No_of_PARAMETERS; i++ ) {
    key = S->Parameter_Index[i];
    lo_P = gsl_vector_get(S->P_min, i);
    hi_P = gsl_vector_get(S->P_MAX, i);

    value = lo_P + gsl_rng_uniform(r) * (hi_P - lo_P);
    
    Vector_Entry_into_Parameter_Model(value, key, Initial_Guess );
  }
}

void Random_Initial_Guess_within_Boundaries_Table (Parameter_Table * Initial_Guess,
						   Parameter_Space * S )
{
  int i, key;
  double value, lo_P, hi_P;

  for ( i=0; i < S->No_of_PARAMETERS; i++ ) {
    key = S->Parameter_Index[i];
    lo_P = gsl_vector_get(S->P_min, i);
    hi_P = gsl_vector_get(S->P_MAX, i);

    value = lo_P + gsl_rng_uniform(r) * (hi_P - lo_P);
    
    AssignVectorEntry_to_Structure(Initial_Guess, key, value);
  }
}

int Random_Initial_Guess_within_Boundaries_and_Data (Parameter_Table * Initial_Guess, 
						     Parameter_Space * S, double ** Data,
						     int Alpha_Index )
{
  /* Input Arguments: 
     
     . Parameter Table 'Initial Guess' 
     . Parameter Space 'S'
     . Empirical Data  'Data'
     . Alpha_Index is the position in the Parameter_Index vector reserved to the Alpha 
     parameter, usually, the last position in the vector. There is an assert here to 
     check this is so. 
  */
  
  int i, key, n;
  double value, lo_P, hi_P, Alpha, Alpha_0, Alpha_1, x_e;
  double Female_Sexual_Worker_Population;
  double Female_Population; 
  int Initial_Guess_is_Good;

  Female_Population                = Data[0][16]/2.0;
  Female_Sexual_Worker_Population  = Data[1][16];

  // assert( Alpha_Index == (S->No_of_PARAMETERS-1) ); 
  
  Alpha_0 = gsl_vector_get(S->P_min, Alpha_Index);  
  Alpha_1 = gsl_vector_get(S->P_MAX, Alpha_Index);
  
  x_e =  Female_Sexual_Worker_Population/Female_Population;   
  
  Initial_Guess_is_Good = 0; n=0;  
  while (Initial_Guess_is_Good == 0 && n < 1.0E+06) { 

    for ( i=0; i < S->No_of_PARAMETERS; i++ ) {
      key = S->Parameter_Index[i];
      lo_P = gsl_vector_get(S->P_min, i);
      hi_P = gsl_vector_get(S->P_MAX, i);
      
      value = lo_P + gsl_rng_uniform(r) * (hi_P - lo_P);
      
      AssignVectorEntry_to_Structure(Initial_Guess, key, value);
    }

    Alpha = Alpha_from_Sigma_Parameters ( x_e, Initial_Guess );

    if( Alpha > Alpha_0  &&  Alpha < Alpha_1 ) {
      Initial_Guess_is_Good = 1;
      Initial_Guess->Alpha = Alpha;
      printf("Initial Seed is a good solution\n"); //getchar();
    }
    n++;
  }

  return(Initial_Guess_is_Good);
}

double Alpha_from_Sigma_Parameters ( double x_e, Parameter_Table * Table )
{
  /* Input parameters:
     
     . x_e, total fraction of female sexual worked (empirical); 

     . Demo parameters: Sigma_0, Sigma_1, Sigma_0_r, and Sigma_1_r

     Output value: 

     . x, Alpha value necessary to maintain the observed fraction, x_e, constant through time, 
     give the values of the demo parameters Sigma_0, Sigma_1, Sigma_0_r, and Sigma_1_r. 

  */
  double x, b, c;
  double D0, A, B, C;
  
  D0 = (Table->Sigma_1_r+Table->Sigma_1+Table->Delta_X);

  A = Table->Sigma_1/D0;

  B = (Table->Sigma_0 - Table->Sigma_1)/D0;

  C = (Table->Sigma_1_r - Table->Sigma_0_r)/D0; 

  b   = x_e * (Table->Sigma_0 + Table->Sigma_0_r) - B * Table->Delta_X;

  c   = A + Table->Delta_X * (B * Table->Sigma_0_r + C * Table->Sigma_0);

  x   = ( -b + sqrt( b*b + 4 * x_e * c) ) /2.0 /x_e - Table->Delta_X;
  
  return (x);
}



