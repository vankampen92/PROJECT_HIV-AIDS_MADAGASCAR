/* Y: Effective Average Fraction of Infectious Males */
/* X: Regular Females (young) */
dydt[X0S] = Table->F_X -Table->Delta_X*y[X0S] -Table->Alpha*y[X0S] -(Table->D_Sigma+Table->Sigma_0) *y[X0S] +Table->Sigma_0_r*y[W0S];          /* X0S */

/* W: Female Sexual Workers (young) */
dydt[W0S] = -Table->Delta_X*y[W0S] -Table->Alpha*y[W0S] + (Table->D_Sigma+Table->Sigma_0) *y[X0S] -Table->Sigma_0_r*y[W0S];                      /* W0S */

/* X: Regular Females (old) */
dydt[X1S] = Table->Alpha*y[X0S] -Table->Delta_X*y[X1S] - (Table->D_Sigma+Table->Sigma_1) *y[X1S] +Table->Sigma_1_r*y[W1S];                       /* X1S */

/* W: Female Sexual Workers (old) */
dydt[W1S] = Table->Alpha*y[W0S] -Table->Delta_X*y[W1S] + (Table->D_Sigma+Table->Sigma_1) *y[X1S] -Table->Sigma_1_r*y[W1S];                       /* W1S */
