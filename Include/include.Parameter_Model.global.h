double Beta_Y;   /* Total no of sexual contacts a male has per year     *//*  0 */
double p_XY;      /* Male-to-Female transmission probability T(Y--->X)   *//*  1 */
double F_Y;      /* Total no of males entering sexual age per year      *//*  2 */
double Delta_X;    /* Natural mortility percapita rate                    *//*  3 */
double Delta_Y;    /* Natural mortility percapita rate                    *//*  4 */
double Gamma;    /* Recovery rate into the quasi-latent phase           *//*  5 */
double Mu;       /* Break-down rate into the final phase (before death) *//*  6 */
double mDelta;   /* Disease-induced mortility relative increase         *//*  7 */
double Beta_X;   /* Total no of sexual contacts a female has per year   *//*  8 */
double p_YX;      /* Female-to-Male transmission probability T(X--->Y)   *//* 9 */
double Sigma_0;    /* Transitional rate into the sexual worker stage      *//* 10 */
double Sigma_0_r;  /* Reversal rate back into the regural female stage    *//* 11 */
double Eta;      /* Contact rate relative increase for sexual workers   *//* 12 */
double F_X;      /* Total no of females entering sexual age per year    *//* 13 */
int    n_Mu;     /* No of latent subclasses during quasi-latent phase   *//* 14 */
double Xhi;      /* Transmision probability increase during acute phase *//* 15 */
double f_W;      /* Fraction of male sexual contacts with female sexual workers *//* 16 */
double f_0;      /* Fraction of male sexual contacts with young females *//* 17 */
double Sigma_1;    /* Transition rate into the sexual worker stage for adult females     *//* 18 */
double Sigma_1_r;  /* Reversal rate back into the regural female stage for adult females *//* 19 */
double Alpha;      /* Transition rate into the adult stage from the young state *//*/ 20 */
double r_F;       /* r Factor: population fraction of reproductive females  *//*/ 21 */
double NX;       /* Total Females */
double NY;       /* Total Males   */

double D_Sigma;
double Sigmoidal_A0;
double Sigmoidal_L0;
double Sigmoidal_T0;

/* Type of model */
#include <include.Type_of_Model.global.h>
