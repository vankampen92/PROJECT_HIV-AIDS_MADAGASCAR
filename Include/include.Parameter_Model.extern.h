extern double Beta_Y;   /* Total no of sexual contacts a male has per year     *//*  0 */
extern double p_XY;      /* Male-to-Female transmission probability T(Y--->X)   *//*  1 */
extern double F_Y;      /* Total no of males entering sexual age per year      *//*  2 */
extern double Delta_X;    /* Natural mortility percapita rate                    *//*  3 */
extern double Delta_Y;    /* Natural mortility percapita rate                    *//*  4 */
extern double Gamma;    /* Recovery rate into the quasi-latent phase           *//*  5 */
extern double Mu;       /* Break-down rate into the final phase (before death) *//*  6 */
extern double mDelta;   /* Disease-induced mortility relative increase         *//*  7 */
extern double Beta_X;   /* Total no of sexual contacts a female has per year   *//*  8 */
extern double p_YX;      /* Female-to-Male transmission probability T(X--->Y)   *//*  9 */
extern double Sigma_0;    /* Transitial rate into the sexual worker stage        *//* 10 */
extern double Sigma_0_r;  /* Reversal rate back into the regural female stage    *//* 11 */
extern double Eta;      /* Contact rate relative increase for sexual workers   *//* 12 */
extern double F_X;      /* Total no of females entering sexual age per year    *//* 13 */
extern int    n_Mu;     /* No of latent subclasses during quasi-latent phase   *//* 14 */
extern double Xhi;      /* Transmision relative increase during acute phase    *//* 15 */
extern double f_W;      /* Fraction of male sexual contacts with females sexual workers *//* 16 */
extern double f_0;      /* Fraction of male sexual contacts with young females *//* 17 */
extern double Sigma_1;    /* Transition rate into the sexual worker stage for adult females     *//* 18 */
extern double Sigma_1_r;  /* Reversal rate back into the regural female stage for adult females *//* 19 */
extern double Alpha;      /* Transition rate into the adult stage from the young state *//*/ 20 */
extern double r_F;      /* r Factor: population fraction of reproductive females  *//*/ 21 */
extern double NX;       /* Total Females */
extern double NY;       /* Total Males   */

extern double D_Sigma;   /* Parameter introducing time-dependence in Sigma_0 and Sigma_1 */
extern double Sigmoidal_A0;  
extern double Sigmoidal_L0;
extern double Sigmoidal_T0;

/* Type of model */
#include <include.Type_of_Model.extern.h>
