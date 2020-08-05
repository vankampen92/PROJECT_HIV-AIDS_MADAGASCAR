/* Y: Effective Average Fraction of Infectious Males */
/* X: Regular Females (young) */
  dydt[X0S] = -Table->Beta_X*Table->p_XY*Y*y[X0S] +Table->F_X -Table->r_F*Table->Delta_X*y[X0S] -Table->Alpha*y[X0S] -(Table->D_Sigma+Table->Sigma_0)*y[X0S] +Table->Sigma_0_r*y[W0S];          /* X0S */

  dydt[X0I] =  Table->Beta_X*Table->p_XY*Y*y[X0S] -Table->Gamma*y[X0I] -Table->r_F*Table->Delta_X*y[X0I] -Table->Alpha*y[X0I] -(Table->D_Sigma+Table->Sigma_0)*y[X0I] +Table->Sigma_0_r*y[W0I]; /* X0I */

  dydt[X0L] = Table->Gamma*y[X0I] -Table->r_F*Table->Delta_X*y[X0L] -Table->Alpha*y[X0L] -Table->Mu*y[X0L] -(Table->D_Sigma+Table->Sigma_0)*y[X0L] +Table->Sigma_0_r*y[W0L];                    /* X0L */

  dydt[X0D] = Table->Mu*y[X0L] - Table->r_F*Table->Delta_X*(1.0+Table->mDelta)*y[X0D] -Table->Alpha*y[X0D] -(Table->D_Sigma+Table->Sigma_0)*y[X0D] +Table->Sigma_0_r*y[W0D];                    /* X0D */

/* W: Female Sexual Workers (young) */
  dydt[W0S] = -Table->Beta_X*(1.0+Table->Eta)*Table->p_XY*Y*y[W0S] -Table->r_F*Table->Delta_X*y[W0S] -Table->Alpha*y[W0S] +(Table->D_Sigma+Table->Sigma_0)*y[X0S] -Table->Sigma_0_r*y[W0S];     /* W0S */

  dydt[W0I] =  Table->Beta_X*(1.0+Table->Eta)*Table->p_XY*Y*y[W0S] -Table->r_F*Table->Delta_X*y[W0I] -Table->Alpha*y[W0I] -Table->Gamma*y[W0I] +(Table->D_Sigma+Table->Sigma_0)*y[X0I] -Table->Sigma_0_r*y[W0I]; /* W0I */

  dydt[W0L] = Table->Gamma*y[W0I] -Table->r_F*Table->Delta_X*y[W0L] -Table->Alpha*y[W0L] -Table->Mu*y[W0L] +(Table->D_Sigma+Table->Sigma_0)*y[X0L] -Table->Sigma_0_r*y[W0L];                    /* W0L */

  dydt[W0D] = Table->Mu*y[W0L] - Table->r_F*Table->Delta_X*(1.0+Table->mDelta)*y[W0D] -Table->Alpha*y[W0D] +(Table->D_Sigma+Table->Sigma_0)*y[X0D] -Table->Sigma_0_r*y[W0D];                    /* W0D */

/* X: Regular Females (old) */
  dydt[X1S] = Table->Alpha*y[X0S] -Table->Beta_X*Table->p_XY*Y*y[X1S] -Table->r_F*Table->Delta_X*y[X1S] -(Table->D_Sigma+Table->Sigma_1)*y[X1S] +Table->Sigma_1_r*y[W1S];                       /* X1S */

  dydt[X1I] = Table->Alpha*y[X0I] +Table->Beta_X*Table->p_XY*Y*y[X1S] -Table->Gamma*y[X1I] -Table->r_F*Table->Delta_X*y[X1I] -(Table->D_Sigma+Table->Sigma_1)*y[X1I] +Table->Sigma_1_r*y[W1I];  /* X1I */

  dydt[X1L] = Table->Alpha*y[X0L] +Table->Gamma*y[X1I] -Table->r_F*Table->Delta_X*y[X1L] -Table->Mu*y[X1L] -(Table->D_Sigma+Table->Sigma_1)*y[X1L] +Table->Sigma_1_r*y[W1L];                    /* X1L */

  dydt[X1D] = Table->Alpha*y[X0D] +Table->Mu*y[X1L] - Table->r_F*Table->Delta_X*(1.0+Table->mDelta)*y[X1D] -(Table->D_Sigma+Table->Sigma_1)*y[X1D] +Table->Sigma_1_r*y[W1D];                    /* X1D */

/* W: Female Sexual Workers (old) */
  dydt[W1S] = Table->Alpha*y[W0S] -Table->Beta_X*(1.0+Table->Eta)*Table->p_XY*Y*y[W1S] -Table->r_F*Table->Delta_X*y[W1S] +(Table->D_Sigma+Table->Sigma_1)*y[X1S] -Table->Sigma_1_r*y[W1S];      /* W1S */

  dydt[W1I] = Table->Alpha*y[W0I] +Table->Beta_X*(1.0+Table->Eta)*Table->p_XY*Y*y[W1S] -Table->r_F*Table->Delta_X*y[W1I] -Table->Gamma*y[W1I] +(Table->D_Sigma+Table->Sigma_1)*y[X1I] -Table->Sigma_1_r*y[W1I];  /* W1I */

  dydt[W1L] = Table->Alpha*y[W0L] +Table->Gamma*y[W1I] -Table->r_F*Table->Delta_X*y[W1L] -Table->Mu*y[W1L] +(Table->D_Sigma+Table->Sigma_1)*y[X1L] -Table->Sigma_1_r*y[W1L];                    /* W1L */

  dydt[W1D] = Table->Alpha*y[W0D] +Table->Mu*y[W1L] - Table->r_F*Table->Delta_X*(1.0+Table->mDelta)*y[W1D] +(Table->D_Sigma+Table->Sigma_1)*y[X1D] -Table->Sigma_1_r*y[W1D];                    /* W1D */
