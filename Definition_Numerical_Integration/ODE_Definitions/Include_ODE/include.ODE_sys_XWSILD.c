/* Y: Effective Average Fraction of Infectious Males */
/* X: Regular Females */
  dydt[XS] = -Table->Beta_X*Table->p_XY* Y *y[XS] +Table->F_X -Table->r_F*Table->Delta_X*y[XS] -(Table->D_Sigma*Table->Sigma_0)*y[XS] +Table->Sigma_0_r*y[WS];                          /* XS */

  dydt[XI] =  Table->Beta_X*Table->p_XY* Y *y[XS] -Table->Gamma*y[XI] -Table->r_F*Table->Delta_X*y[XI] -(Table->D_Sigma*Table->Sigma_0)*y[XI] +Table->Sigma_0_r*y[WI];                  /* XI */

  dydt[XL] = Table->Gamma*y[XI] -Table->r_F*Table->Delta_X*y[XL] -Table->Mu*y[XL] -(Table->D_Sigma*Table->Sigma_0)*y[XL] +Table->Sigma_0_r*y[WL];                                       /* XL */

  dydt[XD] = Table->Mu*y[XL] - Table->r_F*Table->Delta_X*(1.0+Table->mDelta)*y[XD] -(Table->D_Sigma*Table->Sigma_0)*y[XD] +Table->Sigma_0_r*y[WD];                                      /* XD */

/* W: Female Sexual Workers */
  dydt[WS] = -Table->Beta_X*(1.0+Table->Eta)*Table->p_XY* Y *y[WS] -Table->r_F*Table->Delta_X*y[WS] +(Table->D_Sigma*Table->Sigma_0)*y[XS] -Table->Sigma_0_r*y[WS];                     /* WS */

  dydt[WI] =  Table->Beta_X*(1.0+Table->Eta)*Table->p_XY* Y *y[WS] -Table->r_F*Table->Delta_X*y[WI] -Table->Gamma*y[WI] +(Table->D_Sigma*Table->Sigma_0)*y[XI] -Table->Sigma_0_r*y[WI]; /* WI */

  dydt[WL] = Table->Gamma*y[WI] -Table->r_F*Table->Delta_X*y[WL] -Table->Mu*y[WL] +(Table->D_Sigma*Table->Sigma_0)*y[XL] -Table->Sigma_0_r*y[WL];                                       /* WL */

  dydt[WD] = Table->Mu*y[WL] - Table->r_F*Table->Delta_X*(1.0+Table->mDelta)*y[WD] +(Table->D_Sigma*Table->Sigma_0)*y[XD] -Table->Sigma_0_r*y[WD];                                      /* WD */
