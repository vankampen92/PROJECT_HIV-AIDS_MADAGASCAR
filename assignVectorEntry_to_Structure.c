#include <MODEL.h>

void Vector_Entries_into_Parameter_Table ( const gsl_vector * X, Parameter_Table * P,
					   int * Parameter_Index, int No_of_PARAMETERS )
{
  int i;
  int key;
  double value;

  for( i=0; i<No_of_PARAMETERS; i++) {
    key = Parameter_Index[i];
    value = gsl_vector_get(X, i);
    AssignVectorEntry_to_Structure( P, key, value );
  }
}

void Vector_Entries_into_Parameter_Table_Initial_Condition ( const gsl_vector * X,
							     Parameter_Table * P,
							     int * Index,
							     int No_of_PARAMETERS,
							     int No_of_IC)
{
  int i;
  int key;
  double value;

  for( i=0; i<No_of_IC; i++) {
    key = Index[i];
    value = gsl_vector_get(X, i+No_of_PARAMETERS);
    Vector_Entry_into_Model_Variable_Initial_Condition_Table( value, key, P );
  }
}

void AssignVectorEntry_to_Structure(Parameter_Table * P, int j, double value)
{

  switch(j)
    {
    case  0: P->Beta_Y = value;  /* Total no of sexual contacts a male has per year   *//*  0 */
      break;
    case  1: P->p_XY = value;     /* Male-to-Female transmission probability T(Y--->X) *//*  1 */
      break;
    case  2: P->F_Y = value;     /* Total no of males entering sexual age per year    *//*  2 */
      break;
    case  3: P->Delta_X = value;   /* Natural mortility percapita rate                  *//*  3 */
      break;
    case  4: P->Delta_Y = value;   /* Natural mortility percapita rate                  *//*  4 */
      break;
    case  5: P->Gamma = value;   /* Recovery rate into the quasi-latent phase         *//*  5 */
      break;
    case  6: P->Mu = value;     /* Break-down rate into the final phase (before death) *//*  6 */
      break;
    case  7: P->mDelta = value; /* Disease-induced mortility relative increase         *//*  7 */
      break;
    case  8: P->Beta_X = value; /* Total no of sexual contacts a female has per year   *//*  8 */
      break;
    case  9: P->p_YX = value;    /* Female-to-Male transmission probability T(X--->Y)   *//*  9 */
      break;
    case 10: P->Sigma_0 = value;  /* Transitional rate into the sexual worker stage      *//*  10 */
      break;
    case 11: P->Sigma_0_r = value; /* Reversal rate back into the regural female stage    *//* 11 */
      break;
    case 12: P->Eta = value;    /* Contact rate relative increase for sexual workers   *//* 12 */
      break;
    case 13: P->F_X = value;    /* Total no of females entering sexual age per year    *//* 13 */
      break;
    case 14: P->n_Mu = (int)value; /* No of latent subclasses during quasi-latent phase   *//* 14 */
      break;
    case 15: P->Xhi = value;    /* Transmision probability increase during acute phase *//* 15 */
      break;
    case 16: P->f_W = value;    /* Fraction of male sexual contacts with female sexual workers*//* 16 */
      break;
    case 17: P->f_0 = value;    /* Fraction of male sexual contacts with young females *//* 17 */
      break;
    case 18: P->Sigma_1 = value;  /* Transition rate into the sexual worker stage for old females *//*  18 */
      break;
    case 19: P->Sigma_1_r = value; /* Reversal rate back into the regural female stage for old females *//* 19 */
      break;
    case 20: P->Alpha = value;    /* Transition rate into the adult stage from young stage *//* 20 */
      break;
    case 21: P->r_F = value;  /*  r_Factor: Population fraction of reprductive females *//* 21 */
      break;
    case 22: P->D_Sigma = value;  
      break;
    case 23: P->Sigmoidal_A0 = value;  
      break;
    case 24: P->Sigmoidal_L0 = value;  
      break;
    case 25: P->Sigmoidal_T0 = value;  
      break;
    default:
      printf(".... INVALID PARAMETER KEY (key = %d)\n", j);

      printf(".... The permited correspondences are:\n");
      printf("\n");
      fprintf_Model_Parameters(stdout, P);

      printf(" The maximum number of parameters is Number_PAR_MAX\n");
      printf(" The permited number of keys go from 0, to %d\n", MODEL_PARAMETERS_MAXIMUM-1);

      exit(0);
    }
}
