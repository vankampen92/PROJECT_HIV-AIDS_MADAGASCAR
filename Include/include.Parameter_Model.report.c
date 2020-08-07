/* Initial Conditions parameters */
fprintf(fp, "\n");
fprintf(fp, " M O D E L   ( C O R E )   P A R A M E T E R S :\n");
fprintf(fp, " Total no of sexual contacts a male has per year                ...> -H0   %g\n", Beta_Y); /*  0 */
fprintf(fp, " Male-to-Female transmission probability T(Y--->X)              ...> -H1   %g\n", p_XY);    /*  1 */
fprintf(fp, " Total no of males entering sexual age per year                 ...> -H2   %g\n", F_Y);    /*  2 */
fprintf(fp, " Natural mortility percapita rate (females)                     ...> -H3   %g\n", Delta_X);  /*  3 */
fprintf(fp, " Natural mortility percapita rate (males)                       ...> -H4   %g\n", Delta_Y);  /*  4 */
fprintf(fp, " Recovery rate into the quasi-latent phase                      ...> -H5   %g\n", Gamma);  /*  5 */
fprintf(fp, " Break-down rate into the final phase (before death)            ...> -H6   %g\n", Mu);     /*  6 */
fprintf(fp, " Disease-induced mortility relative increase                    ...> -H7   %g\n", mDelta); /*  7 */
fprintf(fp, " Total no of sexual contacts a female has per year              ...> -H8   %g\n", Beta_X); /*  8 */
fprintf(fp, " Female-to-Male transmission probability T(X--->Y)              ...> -H9   %g\n", p_YX);    /* 9 */
fprintf(fp, " Transitional rate into the sexual worker stage                 ...> -H10   %g\n", Sigma_0);  /* 10 */
fprintf(fp, " Reversak rate back into the regular female stage               ...> -H11  %g\n", Sigma_0_r);/* 11 */
fprintf(fp, " Contact rate relative increase for sexual workers              ...> -H12  %g\n", Eta);    /* 12 */
fprintf(fp, " Total no of females entering sexual age per year               ...> -H13  %g\n", F_X);    /* 13 */
fprintf(fp, " No of latent subclasses during quasi-latent phase              ...> -H14  %d\n", n_Mu);   /* 14 */
fprintf(fp, " Transmision probability increase during acute phase            ...> -H15  %g\n", Xhi);    /* 15 */
fprintf(fp, " Fraction of male sexual contacts with female sexual workers    ---> -H16  %g\n", f_W);    /* 16 */
fprintf(fp, " Fraction of male sexual contacts with young female             ---> -H17  %g\n", f_0);    /* 17 */
fprintf(fp, " Transition rate into the sexual worker stage (adult women)     ...> -H18  %g\n", Sigma_1);  /* 18 */
fprintf(fp, " Reversak rate back into the regular female stage (adult women) ...> -H19  %g\n", Sigma_1_r); /* 19 */
fprintf(fp, " Transition rate from young to adult stage                      ---> -H20  %g\n", Alpha);    /* 20   */
fprintf(fp, " r_Factor: population fraction of reproductive females          ---> -H21  %g\n", r_F);     /*  21  */
fprintf(fp, " Parameter introducing time-dependence in Sigma_0 and Sigma_1   ---> -H22  %g\n", D_Sigma);     /*  22  */
fprintf(fp, " Sigmoidal Parameter in Sigma_0 and Sigma_1 (A_0)               ---> -H23  %g\n", Sigmoidal_A0);     /*  23  */
fprintf(fp, " Sigmoidal Parameter in Sigma_0 and Sigma_1 (L_0)               ---> -H24  %g\n", Sigmoidal_L0);  /*  24  */
fprintf(fp, " Sigmoidal Parameter in Sigma_0 and Sigma_1 (T_0)               ---> -H25  %g\n", Sigmoidal_T0);     /*  25  */
