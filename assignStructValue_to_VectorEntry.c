#include <MODEL.h>

void Parameter_Table_into_Vector_Entries ( Parameter_Table * P, gsl_vector * X,
					   int * Parameter_Index, int No_of_PARAMETERS )
{
  int i;
  int key;
  double value;

  for( i=0; i<No_of_PARAMETERS; i++) {
    key = Parameter_Index[i];
    value = AssignStructValue_to_VectorEntry( key, P );
    gsl_vector_set(X, i, value);
  }
}

void Parameter_Table_into_Vector_Entries_Initial_Condition ( Parameter_Table * P, gsl_vector * X,
							     int * Index,
							     int No_of_PARAMETERS,
							     int No_of_IC)
{
  int i;
  int key;
  double value;

  for( i=0; i<No_of_IC; i++) {
    key = Index[i];
    value = Model_Variable_Initial_Condition_into_Vector_Entry_Table( key, P );
    gsl_vector_set(X, i+No_of_PARAMETERS, value);
  }
}

double AssignStructValue_to_VectorEntry(int j, Parameter_Table * P)
{
  double value;

  switch(j)
    {
    case  0: value = P->Beta_Y; /* Total no of sexual contacts a male has per year   *//*  0 */
      break;
    case  1: value = P->p_XY;    /* Male-to-Female transmission probability T(Y--->X) *//*  1 */
      break;
    case  2: value = P->F_Y;    /* Total no of males entering sexual age per year    *//*  2 */
      break;
    case  3: value = P->Delta_X;  /* Natural mortility percapita rate                *//*  3 */
      break;
    case  4: value = P->Delta_Y;  /* Natural mortility percapita rate                *//*  4 */
      break;
    case  5: value = P->Gamma;  /* Recovery rate into the quasi-latent phase         *//*  5 */
      break;
    case  6: value = P->Mu;    /* Break-down rate into the final phase (before death) *//*  6 */
      break;
    case  7: value = P->mDelta;/* Disease-induced mortility relative increase         *//*  7 */
      break;
    case  8: value = P->Beta_X;/* Total no of sexual contacts a female has per year   *//*  8 */
      break;
    case  9: value = P->p_YX;   /* Female-to-Male transmission probability T(X--->Y)   *//*  9 */
      break;
    case 10: value = P->Sigma_0; /* Transitional rate into the sexual worker stage      *//*  10 */
      break;
    case 11: value = P->Sigma_0_r;/* Reversal rate back into the regural female stage    *//* 11 */
      break;
    case 12: value = P->Eta;   /* Contact rate relative increase for sexual workers   *//* 12 */
      break;
    case 13: value = P->F_X;   /* Total no of females entering sexual age per year    *//* 13 */
      break;
    case 14: value = (double)P->n_Mu;/* No of latent subclasses during quasi-latent phase *//* 14 */
      break;
    case 15: value = P->Xhi;   /* Transmision probability increase during acute phase *//* 15 */
      break;
    case 16: value = P->f_W;/* Fraction of male sexual contacts with female sexual workers*//* 16 */
      break;
    case 17: value = P->f_0;/* Fraction of male sexual contacts with young females *//* 17 */
      break;
    case 18: value = P->Sigma_1; /* Transition rate into the sexual worker stage      *//*  18 */
      break;
    case 19: value = P->Sigma_1_r;/* Reversal rate back into the regural female stage    *//* 19 */
      break;
    case 20: value = P->Alpha; /* Transition rate from the young to the adult stage  *//* 20 */
      break;
    case 21: value = P->r_F; /* r_Factor: Population fraction of reprductive females  *//* 21 */
      break;
    case 22: value = P->D_Sigma;  
      break;
    case 23: value = P->Sigmoidal_A0;  
      break;
    case 24: value = P->Sigmoidal_L0;  
      break;
    case 25: value = P->Sigmoidal_T0;  
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

  return(value);
}
