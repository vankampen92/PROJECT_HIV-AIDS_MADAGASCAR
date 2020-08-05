#include <MODEL.h>

double definition_Scan_Function( Parameter_Table * P )
{
  double x;
  double * y;

  int j = P->OUTPUT_VARIABLE_INDEX[0];

  x = definition_OutPut_Variables( j, y, 0.0, P );

  return (x);
}

double definition_OutPut_Variables(int j, double * y, const double t, Parameter_Table * Table)
{
  int i;
  double x = 0.0;

  /* Definition of the numerical order, from 0 to n, of model variables */
  #include <Model_Variables_Code.Include.c>

  /* Genuine output variables are those that derive from the state of the system and,
   * therefore, should be evaluated as a funcion of system state variables
   */
  if (j < OUTPUT_VARIABLES_GENUINE) {
    /* Derived output variables from model dynamic variables and parameters */
    switch(j)
    {
    case 0: /* X : Effective Average Fraction of Infectious Females */
      x = Total_Effective_Fraction_of_Infectious_Females ( y, Table );
      break;
    case 1: /* Y: Effective Average Fraction of Infectious Males */
      x = Total_Effective_Fraction_of_Infectious_Males ( y, Table );
      break;
    case 2: /* X: Total Female Population */
      x = total_Females( y, Table );
      break;
    case 3: /* Y: Total Male Population */
      x = total_Males( y, Table );
      break;
    case 4: /* X: Total Female Sexual Worker Population */
      x = total_Female_Sexual_Workers( y, Table );
      break;
    case 5: /* Y: Total Female Non Sexual Worker Population */
      x = total_Female_Non_Sexual_Workers( y, Table );
      break;
    case 6: /* Total Population */
      x = total_Population( y, Table );
      break;
    case 7: /* Total Disease Prevalence */
      x = total_Disease_Prevalence( y, Table );
      break;
    case 8: /* Total_Female_Disease Prevalence */
      x = total_Female_Disease_Prevalence( y, Table );
      break;
    case 9: /* Total_Male_Disease Prevalence */
      x = total_Male_Disease_Prevalence( y, Table );
      break;
    case 10: /* Total Female Sexual Worker Prevalence (as a fraction) */
      x = total_Female_Sexual_Workers_Prevalence( y, Table );
      break;
    case 11: /* Total Female Non-Sexual Worker Prevalence */
      x = total_Female_Non_Sexual_Workers_Prevalence( y, Table );
      break;
    case 12: /* Female Sexual Worker Fraction */
      x = fraction_Female_Sexual_Workers( y, Table );
      break;
    case 13: /* Female Worker Fraction */
      x = fraction_Female_Non_Sexual_Workers( y, Table );
      break;
    case 14: /* Total Number of Female Sexual Worker Infected (like Prevalence, but in numbers) */
      x = total_Female_Sexual_Workers_Infection( y, Table );
      break;
    case 15: /* Total Number of Female Non-Sexual Worker Infected (like Prevalence, but in numbers) */
      x = total_Female_Non_Sexual_Workers_Infection( y, Table );
      break;
    case 16: /* Total Number of Male Infected */
      x = total_Male_Disease_Infection( y, Table );
      break;
    case 17: /* Time-dependent Sigma_0 parameter *//* 10 */
      x = Table->Sigma_0 + Time_Dependence_Sigmoidal_Function (Table, 10, t);
      break;
    case 18: /* Time-dependent Sigma_1 parameter *//* 18 */
      x = Table->Sigma_1 + Time_Dependence_Sigmoidal_Function (Table, 18, t);
      break;
    default:
      printf(" INVALID VARIABLE CODE in ./definition_OutPut_Variables.c (variable = %d)\n", j);
      printf(" Output Variables range from 0 to 18: Program will exit!  ");
      printf(" Press any key..."); getchar();
      exit(0);
    }
  }
  /* The last MODEL_STATE_VARIABLES output variables are the MODEL_STATE_VARIABLES */
  else {
    j -= OUTPUT_VARIABLES_GENUINE; /* #defined in MODEL.h */
    assert( j < Table->MODEL_STATE_VARIABLES );
    x = y[j];
  }

  return (x);
}
