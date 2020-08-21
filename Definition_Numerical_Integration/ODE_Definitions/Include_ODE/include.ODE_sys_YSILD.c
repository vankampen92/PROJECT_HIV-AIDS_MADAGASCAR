dydt[YS] = -Table->Beta_Y*Table->p_YX* X *y[YS] +Table->F_Y -Table->r_F*Table->Delta_Y*y[YS];          /* YS */

dydt[YI] =  Table->Beta_Y*Table->p_YX* X *y[YS] -Table->Gamma*y[YI] -Table->r_F*Table->Delta_Y*y[YI];  /* YI */

dydt[YL] = Table->Gamma*y[YI] -Table->r_F*Table->Delta_Y*y[YL] -Table->Mu*y[YL];                       /* YL */

dydt[YD] = Table->Mu*y[YL] - Table->r_F*Table->Delta_Y*(1.0+Table->mDelta)*y[YD];                      /* YD */
