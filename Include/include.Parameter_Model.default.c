 Beta_Y = 50.0;    /* Total no of sexual contacts a male has per year      *//*  0 */
 p_XY    = 0.03;      /* Male-to-Female transmission probability T(Y--->X) *//*  1 */
 F_Y    = 10000.0;    /* Total no of males entering sexual age per year     *//*  2 */
 Delta_X  = 1.0/50.0; /* Natural mortality percapita rate                  *//*  3 */
 Delta_Y  = 1.0/50.0; /* Natural mortality percapita rate                  *//*  4 */
 Gamma  = 12.0;     /* Recovery rate from the acute infectious phase       *//*  5 */
 Mu     = 1.0/10.0; /* Break-down rate into the final phase (before death) *//*  6 */
 mDelta = 9.0;     /* Disease-induced mortility relative increase          *//*  7 */
 Beta_X = 10.0;     /* Total no of sexual contacts a female has per year   *//*  8 */
 p_YX    = 0.01;     /* Female-to-Male transmission probability T(X--->Y)  *//*  9 */
 Sigma_0  = 1.0/10.0; /* Transitional rate into the sexual worker stage    *//* 10 */
 Sigma_0_r= 1.0/2.0;  /* Reversal rate back into the regural female stage  *//* 11 */
 Eta    = 49.0;      /* Contact rate relative increase for sexual workers  *//* 12 */
 F_X    = 10000.0;    /* Total no of females entering sexual age per year   *//* 13 */
 n_Mu   = 1;        /* No of latent subclasses during quasi-latent phase   *//* 14 */
 Xhi    = 9.0;      /* Transmision probability increase during acute phase *//* 15 */
 f_W    = 0.01;     /* Fraction of male sexual contacts with females sexual workers *//* 16 */
 f_0    = 0.7;     /* Fraction of male sexual contacts with females young  *//* 17 */
 Sigma_1  = 1.0/10.0; /* Transitional rate into the sexual worker stage    *//* 18 */
 Sigma_1_r= 1.0/2.0;  /* Reversal rate back into the regural female stage  *//* 19 */
 Alpha    = 1.0/15.0; /* Transition rate from the young to adult stage     *//* 20 */
 r_F     = 1.0;    /* r Factor: population fraction of reproductive females *//*/ 21 */

 D_Sigma  = 0.0;   /* Parameter introducing time-dependence in Sigma_0 and Sigma_1 */
 Sigmoidal_A0 = 0.0;   /* Parameter introducing time-dependence in Sigma_0 and Sigma_1 */;  
 Sigmoidal_L0 = 0.0;   /* Parameter introducing time-dependence in Sigma_0 and Sigma_1 */
 Sigmoidal_T0 = 0.0;   /* Parameter introducing time-dependence in Sigma_0 and Sigma_1 */

#include <include.Type_of_Model.default.c>
