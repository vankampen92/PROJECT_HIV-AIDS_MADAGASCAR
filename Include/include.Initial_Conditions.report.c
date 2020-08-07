/* Initial Conditions parameters: Model Variables Initial Conditions */
fprintf(fp, "\n");
fprintf(fp, " M O D E L   V A R I A B L E S   I N I T I A L   C O N D I T I O N S :\n");

fprintf(fp, " Susceptible males      ...> -x0   %g\n", YS__0);  /*  8 */
fprintf(fp, " Infectious males       ...> -x1   %g\n", YI__0);  /*  9 */
fprintf(fp, " Less Infectious males  ...> -x2  %g\n", YL__0);  /* 10 */
fprintf(fp, " Last-stage males       ...> -x3  %g\n", YD__0);  /* 11 */

#if defined XWSILD
fprintf(fp, " Susceptible females             ...> -x4   %g\n", XS__0); /*  0 */
fprintf(fp, " Infectious females              ...> -x5   %g\n", XI__0); /*  1 */
fprintf(fp, " Less infectious females         ...> -76   %g\n", XL__0); /*  2 */
fprintf(fp, " Last-stage females              ...> -x7   %g\n", XD__0); /*  3 */

fprintf(fp, " Sexual workers susceptible females     ...> -x8   %g\n", WS__0); /*  4 */
fprintf(fp, " Sexual workers infectious females      ...> -x9   %g\n", WI__0); /*  5 */
fprintf(fp, " Sexual workers less infectious females ...> -x10   %g\n", WL__0); /*  6 */
fprintf(fp, " Sexual workers last-stage females      ...> -x11  %g\n", WD__0); /*  7 */
#endif

#if defined X2W2SILD
fprintf(fp, " Susceptible young females             ...> -x4   %g\n", X0S__0); /*  0 */
fprintf(fp, " Infectious young females              ...> -x5   %g\n", X0I__0); /*  1 */
fprintf(fp, " Less infectious females         ...> -76   %g\n", X0L__0); /*  2 */
fprintf(fp, " Last-stage females              ...> -x7   %g\n", X0D__0); /*  3 */

fprintf(fp, " Sexual workers young susceptible females     ...> -x8   %g\n", W0S__0); /*  4 */
fprintf(fp, " Sexual workers young infectious females      ...> -x9   %g\n", W0I__0); /*  5 */
fprintf(fp, " Sexual workers young less infectious females ...> -x10   %g\n", W0L__0); /*  6 */
fprintf(fp, " Sexual workers young last-stage females      ...> -x11  %g\n", W0D__0); /*  7 */

fprintf(fp, " Susceptible old females             ...> -x4   %g\n", X1S__0); /*  0 */
fprintf(fp, " Infectious old females              ...> -x5   %g\n", X1I__0); /*  1 */
fprintf(fp, " Less infectious old females         ...> -76   %g\n", X1L__0); /*  2 */
fprintf(fp, " Last-stage olf emales              ...> -x7   %g\n", X1D__0); /*  3 */

fprintf(fp, " Sexual workers susceptible old females     ...> -x8   %g\n", W1S__0); /*  4 */
fprintf(fp, " Sexual workers infectious old females      ...> -x9   %g\n", W1I__0); /*  5 */
fprintf(fp, " Sexual workers less infectious old females ...> -x10   %g\n", W1L__0); /*  6 */
fprintf(fp, " Sexual workers last-stage old females      ...> -x11  %g\n", W1D__0); /*  7 */
#endif

fprintf(fp, " Type of Initial Conditions: ...> -xn %d\n", TYPE_of_INITIAL_CONDITION);

fprintf(fp, " Initial Total Population: ...> -xN %g\n", INITIAL_TOTAL_POPULATION);

fprintf(fp, " Rescaling Initial Total Population: ...> -xR %d\n", RESCALING_INITIAL_TOTAL_POPULATION);

fprintf(fp, "-i0 0: Variable Index (%s) 0: \n", Table->Model_Variable_Symbol[0]);
fprintf(fp, "[Index of the 1st Variable (initial condition): 0]: -u0 %g -U0 %g\t [ min_Value[0] = %g, MAX_Value[0] = %g ]\t Accuracy[0] = %g, No of Points (along this axis) = %d\n",
	IC_min_0, IC_MAX_0, IC_min_0, IC_MAX_0, IC_Acc_0, IC_d0);
fprintf(fp, "-i1 1: Variable Index (%s) 1: \n", Table->Model_Variable_Symbol[1]);
fprintf(fp, "[Index of the 2nd Variable (initial condition): 1]: -u0 %g -U0 %g\t [ min_Value[0] = %g, MAX_Value[0] = %g ]\t Accuracy[0] = %g, No of Points (along this axis) = %d\n",
	IC_min_1, IC_MAX_1, IC_min_1, IC_MAX_1, IC_Acc_1, IC_d1);

if(Table->MODEL_STATE_VARIABLES > 2) { 
fprintf(fp, "-i2 2: Variable Index (%s) 2: \n", Table->Model_Variable_Symbol[2]);
fprintf(fp, "[Index of the 3rd Variable (initial condition): 2]: -u0 %g -U0 %g\t [ min_Value[0] = %g, MAX_Value[0] = %g ]\t Accuracy[0] = %g, No of Points (along this axis) = %d\n",
	IC_min_0, IC_MAX_0, IC_min_0, IC_MAX_0, IC_Acc_0, IC_d0);
}
if(Table->MODEL_STATE_VARIABLES > 3) { 
fprintf(fp, "-i3 3: Variable Index (%s) 3: \n", Table->Model_Variable_Symbol[3]);
fprintf(fp, "[Index of the 4th Variable (initial condition): 3]: -u0 %g -U0 %g\t [ min_Value[0] = %g, MAX_Value[0] = %g ]\t Accuracy[0] = %g, No of Points (along this axis) = %d\n",
	IC_min_1, IC_MAX_1, IC_min_1, IC_MAX_1, IC_Acc_1, IC_d1);
}
if(Table->MODEL_STATE_VARIABLES > 4) { 
fprintf(fp, "-i4 4: Variable Index (%s) 4: \n", Table->Model_Variable_Symbol[4]);
fprintf(fp, "[Index of the 5thVariable (initial condition): 4]: -u0 %g -U0 %g\t [ min_Value[0] = %g, MAX_Value[0] = %g ]\t Accuracy[0] = %g, No of Points (along this axis) = %d\n",
	IC_min_0, IC_MAX_0, IC_min_0, IC_MAX_0, IC_Acc_0, IC_d0);
}
if(Table->MODEL_STATE_VARIABLES > 5) { 
 fprintf(fp, "-i5 5: Variable Index (%s) 5: \n", Table->Model_Variable_Symbol[5]);
 fprintf(fp, "[Index of the 6th Variable (initial condition): 5]: -u0 %g -U0 %g\t [ min_Value[0] = %g, MAX_Value[0] = %g ]\t Accuracy[0] = %g, No of Points (along this axis) = %d\n",
	IC_min_1, IC_MAX_1, IC_min_1, IC_MAX_1, IC_Acc_1, IC_d1);
}
fprintf(fp, "Note that accuracies and number of points along the axis can not be be changed from the command line, but modifying the corresponding default file!!!\n"); 

fprintf(fp, "Also, more initial conditions can be included... \n"); 

