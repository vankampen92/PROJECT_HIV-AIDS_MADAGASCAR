/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                            David Alonso, 2018 (c)                         */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#include <Include/MODEL.h>

#include "global.h"

gsl_rng * r; /* Global generator defined in main.c */

/* This code calculates ODE model temporal evolution of the whole disease
   model and extrapolates/predicts the evolution of disease incidence up to
   2033.  Here, the goal is only to graphically show the temporal evolution
   of the different parameter sets, which are read from corresponding files.

   Parameters have been estimated in three rounds. First, parameters F_X, F_Y,
   \delta_X and \delta_Y have been estimated from demographic data and play the
   role of time-dependent extern parameters driving the system. See directory:

   ./TEMPORAL_EVOLUTION_r_FACTOR_ESTIMATE

   F_X and F_Y are recruitment rates into adutl sexually active life, and
   \delta_X and \delta_Y are adult mortality rates. They change every year.
   They are given in 'Time_Dependent_Parameters_Corrected_[CITY_NAME].dat'
   files.

   Second, parametres controling the distribution of females in the different
   groups are estimated in the directory:

   ./TEMPORAL_EVOLUTION_DEMOGRAPHY_PARAMETERS

   Parameter configurations were then saved and now read from files of
   the type:

   Demo_Parameter_Set_[Name-of-the-City]_[Hypothesis]_Ordered.dat, i.e.,

   Demo_Parameter_Set_Antananarivo_Sigmoidal_Ordered.dat

   Finally, the disease-related parameters have been estimated with code
   in:

   ./TEMPORAL_EVOLUTION_INI_YEAR_CALCULATION

   or

   ./TEMPORAL_EVOLUTION_INI_YEAR_CBL-CLUSTER

   As a result of these estimating procedures, fitting parametric configurations
   are generated and saved in files of type:

   Full_Parameter_Set_[Name-of-the-City]_[Year]_[Hypothesis].dat

   This main code here read files of these kind, which have been ordered acording to
   their goodness-of-fit, and visually inspect the numerically generated, predicted
   solutions against observations.


   Compilation:

   . ~$ make X_MODEL=X2W2SILD Y_MODEL=YSILD

   We can inspect results from three different assumptions:

   A. Parameters are searched under the hypothesis of constant ratio of female
   sexual workers to total female population:

   B. Parameters are searched under the hypothesis of ratio of female
   sexual workers to total female population following a sigmoidal curve
   with a break point in 2011.0 and smoothness parameters 0.1.

   C. As B, but with much contrained parameter ranges.

   Both B and C hypothesis can be generated under different sigmoidal curves,
   this is, for different sigmoidal parameters (L_0 and T_0). This will define
   sub-hypothesis within each of them:

   B1 or C1: L_0 = 0.1 and T_0 = 2011
   B2 or C2: L_0 = 1.0 and T_0 = 2011

   Hypothesis A needs and generates files ending in *.dat, while hypothesis
   B requires files ending in *Sigmoidal.dat. This should be changed by hand
   in code. So, in order to generate results under the two hyphotheses,
   the program should be run twice by changing (and recompiling) the code
   accordingly. This is achieved just changing:

   L171: SIGMOIDAL == 1

   into

   L171: SIGMOIDAL = 0     (line L171 of code is only approx.)

   A. Parameters are searched under the hypothesis of constant ratio of female
   sexual workers to total female population:

   Exectution: (Time-dependent parameters: -t4 1)

   . ~$ ./X2W2SILD-YSILD -y0 1                // TYPE of MODEL
   / -sP 17 -sN 100   -sT 1.0E-06             // Parameter Space of Model Parameters:  [-sP : Dimension, Number of Model Parameters to be optimized]
   / -I0 21  -H21 1.0   -m0 0.0   -M0 2.0     -A0 0.01      // Parameter: r_R
   / -I1 0   -H0 100.0  -m1 0.0   -M1 200.0   -A1 0.1       // Parameter: Beta_Y
   / -I2 8   -H8  50.0  -m2 0.0   -M2 100.0   -A2 0.1       // Parameter: Beta_X
   / -I3 12  -H12   9   -m3 1.0   -M3 20.0    -A3 0.01      // Parameter: Eta
   / -I4 7   -H7  9.0   -m4 1.0   -M4 99.0    -A4 0.01      // Parameter: mDelta
   / -I5 16  -H16 0.2   -m5 0.0   -M5 0.99    -A5 0.01      // Parameter: f_W
   / -I6 17  -H17 0.5   -m6 0.0   -M6 0.99    -A6 0.01      // Parameter: f_0
   / -I7 1   -H1 0.03   -m7 0.0   -M7 0.10    -A7 0.001     // Parameter: p_XY
   / -I8 9   -H9 0.01   -m8 0.0   -M8 0.10    -A8 0.001     // Parameter: p_YX
   / -I9 5   -H5 1.5    -m9 0.0   -M9 10.0    -A9 0.1       // Parameter: Gamma
   / -I10 6  -H6 0.2    -m10 0.0  -M10 1.0    -A10 0.01     // Parameter: Mu
   / -I11 15 -H15 10.0  -m11 1.0  -M11 100.0  -A11 0.1      // Parameter: Xhi
   / -I12 10 -H10  0.01 -m12 0.0  -M12 0.05   -A12 0.01     // Parameter: Sigma_0
   / -I13 11 -H11  0.01 -m13 0.0  -M13 0.05   -A13 0.01     // Parameter: Sigam_0_r
   / -I14 18 -H18  0.01 -m14 0.0  -M14 0.05   -A14 0.01     // Parameter: Sigma_1
   / -I15 19 -H19  0.01 -m15 0.0  -M15 0.05   -A15 0.01     // Parameter: Sigma_1_r
   / -I16 20 -H20  0.1  -m16 0.08 -M16 0.12   -A16 0.01     // Parameter: Alpha

   / -en 0 -eP0 17 -eV 1.0              // Parameter Space of Error Model        [-en Number of Error Model-related parameters to be optimized: -eP0 17 [Error_Parameter_0]
   / -n 3  -v0 6 -v1 4 -v2 14           // Output/Observed Varables:             [-n  Number of Observed Variables]
   / -iP 0                              // Parameter Space of Initial Conditions [-iP Number of Initial Condition Variables to be optimized]
   / -i0  9 -u0 0.0 -U0 100.0
   /- i1 17 -u1 0.0 -U1 100.0
   / -G0 1  -G1 3 -tn 17 -t0 2000.0 -t1 2016.0 -t4 1 -xn 0 -xR 1  // Arguments Controling Numerical Integration
   / -DP 4  -DC 0 -D0 0 -D1 4 -D2 0 -P0 13 -a0 0  -P1 2 -a1 0  -P2 3 -a2 0  -P3 4 -a3 0 // Arguments controling type of time dependence of model parameters.

   . ~$ ./X2W2SILD-YSILD -y0 1 -sT 1.0E-04 -sN 100 -sP 17  -I0 21 -H21 1.0  -m0 0.5 -M0 1.5 -A0 0.01   -I1 0 -H0 100.0 -m1 0.0 -M1 200.0 -A1 0.1  -I2 8 -H8 50.0 -m2 0.0 -M2 100.0 -A2 0.1   -I3 12 -H12 9.0  -m3 1.0 -M3 20.0  -A3 0.01   -I4 7 -H7 9.0 -m4 1.0 -M4 99.0 -A4 0.01   -I5 16 -H16 0.2 -m5 0.0 -M5 0.99 -A5 0.01 -I6 17 -H17 0.6 -m6 0.0 -M6 0.99 -A6 0.01 -I7 1 -H1 0.03 -m7 0.0 -M7 0.1 -A7 0.001  -I8 9 -H9 0.01 -m8 0.0 -M8 0.1 -A8 0.001   -I9 5 -H5 1.5 -m9 0.0 -M9 10.0 -A9 0.1   -I10 6 -H6 0.2 -m10 0.0 -M10 1.0 -A10 0.01   -I11 15 -H15 10.0 -m11 1.0 -M11 100.0 -A11 0.1  -I12 10 -H10 0.01 -m12 0.0 -M12 0.05 -A12 0.01   -I13 11 -H11  0.01 -m13 0.0 -M13 0.05 -A13 0.01   -I14 18 -H18 0.01 -m14 0.0 -M14 0.05 -A14 0.01   -I15 19 -H19 0.01 -m15 0.0 -M15 0.05 -A15 0.01  -I16 20 -H20 0.1 -m16 0.08 -M16 0.12  -A16 0.01  -n 3 -v0 6 -v1 4 -v2 14 -en 0 -eP0 17 -eV 0.2 -iP 0 -i0 9 -u0 0.0 -U0 10000.0 -i1 17 -u1 0.0 -U1 10000.0 -i2 1 -u2 0.0 -U2 10000 -i3 2 -u3 0.0 -U3 10000 -i4 3 -u4 0.0 -U4 10000 -G0 1 -G1 3 -tn 34 -t0 2000.0 -t1 2033.0 -t4 1 -xn 0 -xR 1 -DP 4  -DC 0 -D0 0 -D1 4 -D2 0 -P0 13 -a0 0  -P1 2 -a1 0  -P2 3 -a2 0  -P3 4 -a3 0 -tE 2.0

   B. Parameters are searched under the hypothesis of ratio of female
   sexual workers to total female population following a sigmoidal curve
   with a break point in 2011.0 and smoothness parameters 0.1. This estimates
   are generated in ./OBSERVED_DATA_FILES_PREPARATION and resulting files
   are *_Sigmoidal.dat files.

   In this case, the set of demographic parameters include three new parameters controling
   a corresponding break point in parameters Sigma_0 and Sigma_1. In addition, a new
   parameters D_Sigma has a sigmoidal time dependence (parameters 22), which
   imposes a time dependence in Sigma_0 and Sigma_1 through:

   Sigma_0(t) = Sigma_0 + D_Sigma(t)
   Sigma_1(t) = Simga_1 + D_Sigma(t)

   . ~$ ./X2W2SILD-YSILD -y0 1                // TYPE of MODEL
   / -sP 20 -sN 100   -sT 1.0E-06             // Parameter Space of Model Parameters:  [-sP : Dimension, Number of Model Parameters to be optimized]
   / -I0 21  -H21 1.0   -m0 0.0   -M0 2.0     -A0 0.01      // Parameter: r_R
   / -I1 0   -H0 100.0  -m1 0.0   -M1 200.0   -A1 0.1       // Parameter: Beta_Y
   / -I2 8   -H8  50.0  -m2 0.0   -M2 100.0   -A2 0.1       // Parameter: Beta_X
   / -I3 12  -H12   9   -m3 1.0   -M3 20.0    -A3 0.01      // Parameter: Eta
   / -I4 7   -H7  9.0   -m4 1.0   -M4 99.0    -A4 0.01      // Parameter: mDelta
   / -I5 16  -H16 0.2   -m5 0.0   -M5 0.99    -A5 0.01      // Parameter: f_W
   / -I6 17  -H17 0.5   -m6 0.0   -M6 0.99    -A6 0.01      // Parameter: f_0
   / -I7 1   -H1 0.03   -m7 0.0   -M7 0.10    -A7 0.001     // Parameter: p_XY
   / -I8 9   -H9 0.01   -m8 0.0   -M8 0.10    -A8 0.001     // Parameter: p_YX
   / -I9 5   -H5 1.5    -m9 0.0   -M9 10.0    -A9 0.1       // Parameter: Gamma
   / -I10 6  -H6 0.2    -m10 0.0  -M10 1.0    -A10 0.01     // Parameter: Mu
   / -I11 15 -H15 10.0  -m11 1.0  -M11 100.0  -A11 0.1      // Parameter: Xhi
   / -I12 10 -H10  0.01 -m12 0.0  -M12 0.05   -A12 0.01     // Parameter: Sigma_0
   / -I13 11 -H11  0.01 -m13 0.0  -M13 0.05   -A13 0.01     // Parameter: Sigam_0_r
   / -I14 18 -H18  0.01 -m14 0.0  -M14 0.05   -A14 0.01     // Parameter: Sigma_1
   / -I15 19 -H19  0.01 -m15 0.0  -M15 0.05   -A15 0.01     // Parameter: Sigma_1_r
   / -I16 20 -H20  0.1  -m16 0.08 -M16 0.12   -A16 0.01     // Parameter: Alpha
   / -I17 23 -H23  0.4  -m17 0.0  -M17 5.0    -A17 0.01     // Parameter: A_0  Magnitud of the jump
   / -I18 24 -H24  3.0  -m18 0.0  -M18 5.0    -A18 0.01     // Parameter: L_0  Smoothness of the jump
   / -I19 25 -H25  2013 -m19 2009 -M19 2013.0 -A19 0.1      // Parameter: T_0  Time of the jump

   / -en 0 -eP0 17 -eV 0.2              // Parameter Space of Error Model        [-en Number of Error Model-related parameters to be optimized: -eP0 17 [Error_Parameter_0]
   / -n 3  -v0 6 -v1 4 -v2 14           // Output/Observed Varables:             [-n  Number of Observed Variables]
   / -iP 0                              // Parameter Space of Initial Conditions [-iP Number of Initial Condition Variables to be optimized]
   / -i0  9 -u0 0.0 -U0 100.0
   /- i1 17 -u1 0.0 -U1 100.0
   / -G0 1  -G1 3 -tn 17 -t0 2000.0 -t1 2016.0 -t4 1 -xn 0 -xR 1  // Arguments Controling Numerical Integration
   / -DP 4  -DC 0 -D0 0 -D1 4 -D2 0 -P0 13 -a0 0  -P1 2 -a1 0  -P2 3 -a2 0  -P3 4 -a3 0 // Arguments controling type of time dependence of model parameters.
   / -Fn 1 -F0 ../../DATA_FILES/2019.05.31_Demographic_Parameters_per_City_NLL.dat

   . ~$ ./X2W2SILD-YSILD -y0 1 -sT 1.0E-04 -sN 100 -sP 20  -I0 21 -H21 1.0  -m0 0.5 -M0 1.5 -A0 0.01   -I1 0 -H0 100.0 -m1 0.0 -M1 200.0 -A1 0.1  -I2 8 -H8 50.0 -m2 0.0 -M2 100.0 -A2 0.1   -I3 12 -H12 9.0  -m3 1.0 -M3 20.0  -A3 0.01   -I4 7 -H7 9.0 -m4 1.0 -M4 99.0 -A4 0.01   -I5 16 -H16 0.2 -m5 0.0 -M5 0.99 -A5 0.01 -I6 17 -H17 0.6 -m6 0.0 -M6 0.99 -A6 0.01 -I7 1 -H1 0.03 -m7 0.0 -M7 0.1 -A7 0.001  -I8 9 -H9 0.01 -m8 0.0 -M8 0.1 -A8 0.001   -I9 5 -H5 1.5 -m9 0.0 -M9 10.0 -A9 0.1   -I10 6 -H6 0.2 -m10 0.0 -M10 1.0 -A10 0.01   -I11 15 -H15 10.0 -m11 1.0 -M11 100.0 -A11 0.1  -I12 10 -H10 0.01 -m12 0.0 -M12 0.05 -A12 0.01   -I13 11 -H11  0.01 -m13 0.0 -M13 0.05 -A13 0.01   -I14 18 -H18 0.01 -m14 0.0 -M14 0.05 -A14 0.01   -I15 19 -H19 0.01 -m15 0.0 -M15 0.05 -A15 0.01  -I16 20 -H20 0.1 -m16 0.08 -M16 0.12  -A16 0.01  -I17 23 -H23 0.4 -m17 0.0 -M17 5.0 -A17 0.01  -I18 24 -H24 3.0 -m18 0.0 -M18 5.0 -A18 0.01   -I19 25 -H25 2013.0 -m19 2009.0 -M19 2013.0 -A19 0.1 -G0 2 -G1 2 -n 4 -v0 6 -v1 4 -v2 14 -v3 17  -en 0 -eP0 17 -eV 0.2 -iP 0 -i0 9 -u0 0.0 -U0 10000.0 -i1 17 -u1 0.0 -U1 10000.0 -i2 1 -u2 0.0 -U2 10000 -i3 2 -u3 0.0 -U3 10000 -i4 3 -u4 0.0 -U4 10000 -tn 34 -t0 2000.0 -t1 2033.0 -t4 1 -xn 0 -xR 1 -DP 5  -DC 0 -D0 0 -D1 4 -D2 1 -P0 13 -a0 0  -P1 2 -a1 0  -P2 3 -a2 0  -P3 4 -a3 0 -P4 22 -a4 0  -tE 2.0

   For both A and B hypothesis, it is possible to plot as output variables also other variables.
   For instance:

   -n 4 -v0 6 -v1 4 -v2 17 -v3 18

   Variable 17 and 18 will show the sigmoidal evolution of parameters Sigma_0 and Sigma_1 through time.

   To read the whole parameter list from a file, execute:

   . ~$ ./X2W2SILD-YSILD $(cat Arguments_Command_Line_Antananarivo.dat)

   -xn TYPE of INITIAL CONDITION (0 from default values in Parameter Table (Input Args); 1 at Random; 2 from fixed/stationary Point)
   -xN INITIAL TOTAL POPULATION SIZE
   -t4 TYPE of TIME DEPENDENCE (0, no parameter time dependence). If the TYPE of TIME DEPENDENCE input argument is greater than 0, time dependence parameters are at play and time dependence files are required. See also ./Definition_Numerical_Integration/XWSILD-YSILD/deterministic_time_dynamics.c

   See file denition_OutPut_Variables.c for full -v?? input argument code definitions. Examples are:

   -v0  0   Effective Average Fraction of Infectious Females
   -v1  1   Effective Average Fraction of Infectious Males
   -v1  4   Total Female Sexual Worker Population
   -v2  2   Total Female Population
   -v3  6   Total Population
   -v4  7   Total Disease Prevalence
   -v5  8   Total Female Disease Prevalence
   -v6  9   Total Male_Disease Prevalence
   -v7 10   Total Female Sexual Worker Disease Prevalence
   -v8 12   Female Sexual Worker Fraction

   C. Parameters are searched under the same hypothesis as B, but all parameter ranges are chosen
   to be maximally constrained in agreement with  the information we have about the behavior of
   the disease. As in B, parameters are searched under the hypothesis of ratio of female sexual
   workers to total female population following a sigmoidal curve with a break point in 2011.0
   and smoothness parameters 0.1. This pseudo-data are generated in

   ./OBSERVED_DATA_FILES_PREPARATION

   and resulting files are *_Sigmoidal.dat files.

   In this case, the set of demographic parameters include three new parameters controling
   a break point in parameters Sigma_0 and Sigma_1. These three parameters are A_0, L_0 and
   T_0, which are also object to search. In addition, a new parameters D_Sigma has a sigmoidal
   time dependence (parameter 22), which imposes a time dependence in Sigma_0 and Sigma_1
   through:

   Sigma_0(t) = Sigma_0 + D_Sigma(t)
   Sigma_1(t) = Simga_1 + D_Sigma(t)

   Exectution: (Time-dependent parameters: -t4 1)

   . ~$ ./X2W2SILD-YSILD -y0 1                // TYPE of MODEL
   / -sP 12 -sN 2500   -sT 1.0E-08            // Parameter Space of Model Parameters:  [-sP : Dimension, Number of Model Parameters to be optimized]
   / -I0 21 -H21 1.0   -m0 0.8  -M0 1.2     -A0 0.01      // Parameter: r_R
   / -I1 0  -H0 100.0  -m1 96.0 -M1 120.0   -A1 0.1       // Parameter: Beta_Y
   / -I2 8  -H8 100.0  -m2 96.0 -M2 120.0   -A2 0.1       // Parameter: Beta_X
   / -I3 12 -H12   9   -m3 1.0  -M3 19.0    -A3 0.01      // Parameter: Eta
   / -I4 7  -H7  9.0   -m4 0.0  -M4 99.0    -A4 0.01      // Parameter: mDelta
   / -I5 16 -H16 0.2   -m5 0.0  -M5 0.99    -A5 0.01      // Parameter: f_W
   / -I6 17 -H17 0.5   -m6 0.0  -M6 0.99    -A6 0.01      // Parameter: f_0
   / -I7 1  -H1 0.001  -m7 0.0  -M7 0.005   -A7 0.0001    // Parameter: p_XY
   / -I8 9  -H9 0.0005 -m8 0.0  -M8 0.001   -A8 0.0001    // Parameter: p_YX
   / -I9 5  -H5 1.5    -m9 0.5  -M9 4.0     -A9 0.01      // Parameter: Gamma
   / -I10 6 -H6 0.1    -m10 0.05 -M10 0.20  -A10 0.01     // Parameter: Mu
   / -I11 15 -H15 10.0 -m11 1.0 -M11 50.0   -A11 0.1      // Parameter: Xhi
   / -I12 10 -H10  0.01 -m12 0.0  -M12 0.05   -A12 0.01     // Parameter: Sigma_0
   / -I13 11 -H11  0.01 -m13 0.0  -M13 0.05   -A13 0.01     // Parameter: Sigam_0_r
   / -I14 18 -H18  0.01 -m14 0.0  -M14 0.05   -A14 0.01     // Parameter: Sigma_1
   / -I15 19 -H19  0.01 -m15 0.0  -M15 0.05   -A15 0.01     // Parameter: Sigma_1_r
   / -I16 20 -H20  0.1  -m16 0.08 -M16 0.12   -A16 0.01     // Parameter: Alpha                        In ./TEMPORAL_EVOLUTION_DEMOGRAPHY_PARAMETERS:
   / -I17 23 -H23  0.4  -m17 0.0  -M17 5.0    -A17 0.01     // Parameter: A_0  Magnitud of the jump    // -I5 23 -H23  0.01 -m5 0.0  -M5 0.5  -A5 0.01           // Parameter: A_0
   / -I18 24 -H24  3.0  -m18 0.0  -M18 5.0    -A18 0.01     // Parameter: L_0  Smoothness of the jump  // -I6 24 -H24  0.01 -m6 0.0  -M6 2.0  -A6 0.01           // Parameter: L_0
   / -I19 25 -H25  2013 -m19 2009 -M19 2013.0 -A19 0.1      // Parameter: T_0  Time of the jump        // -I7 25 -H25  2011.0 -m7 2009.0 -M7 2013.0 -A7 0.1      // Parameter: T_0

   // City-specific demographic parameters (Antananarivo):
   / -H10  0.0325332                          // Parameter: Sigma_0
   / -H11  0.704745                           // Parameter: Sigma_0_r
   / -H18  0.0265231                          // Parameter: Sigma_1
   / -H19  0.550609                           // Parameter: Sigma_1_r
   / -H20  0.056651                           // Parameter: Alpha
   / -H23  0.48356                            // Parameter: A_0  Magnitud of the jump
   / -H24  3.02678                            // Parameter: L_0  Smoothness of the jump
   / -H25  2013                               // Parameter: T_0  Time of the jump

   / -en 0 -eP0 17 -eV 0.2                    // Parameter Space of Error Model        [-en Number of Error Model-related parameters to be optimized: -eP0 17 [Error_Parameter_0]
   / -n 3  -v0 6 -v1 4 -v2 14                 // Output/Observed Varables:             [-n  Number of Observed Variables]
   / -iP 2                                    // Parameter Space of Initial Conditions [-iP Number of Initial Condition Variables to be optimized]
   / -i0  9 -u0 0.0 -U0 100.0
   /- i1 17 -u1 0.0 -U1 100.0
   / -G0 1  -G1 3 -tn 17 -t0 2000.0 -t1 2016.0 -t4 1 -xn 0 -xR 1  // Arguments Controling Numerical Integration
   / -DP 5  -DC 0 -D0 0 -D1 4 -D2 1 -P0 13 -a0 0  -P1 2 -a1 0  -P2 3 -a2 0  -P3 4 -a3 0 -P4 22 -a4 0 // Arguments controling type of time dependence of model parameters.

   . ~$ ./X2W2SILD-YSILD -y0 1 -sT 1.0E-04 -sN 300 -sP 20 -I0 21 -H21 1.0 -m0 0.8  -M0 1.2 -A0 0.01 -I1 0 -H0 100.0  -m1 96.0 -M1 120.0 -A1 0.1  -I2 8 -H8 100.0  -m2 96.0 -M2 120.0  -A2 0.1  -I3 12 -H12   9  -m3 1.0 -M3 19.0  -A3 0.01  -I4 7  -H7  9.0  -m4 0.0 -M4 99.0 -A4 0.01  -I5 16 -H16 0.2   -m5 0.0  -M5 0.99 -A5 0.01  -I6 17 -H17 0.5 -m6 0.0 -M6 0.99 -A6 0.01   -I7 1 -H1 0.001  -m7 0.0 -M7 0.005 -A7 0.0001   -I8 9 -H9 0.0005 -m8 0.0 -M8 0.001 -A8 0.0001   -I9 5 -H5 1.5  -m9 0.5 -M9 4.0 -A9 0.01     -I10 6 -H6 0.1   -m10 0.05 -M10 0.20 -A10 0.01   -I11 15 -H15 10.0 -m11 1.0 -M11 50.0 -A11 0.1  -I12 10 -H10 0.01 -m12 0.0 -M12 0.05 -A12 0.01   -I13 11 -H11  0.01 -m13 0.0 -M13 0.05 -A13 0.01   -I14 18 -H18 0.01 -m14 0.0 -M14 0.05 -A14 0.01   -I15 19 -H19 0.01 -m15 0.0 -M15 0.05 -A15 0.01  -I16 20 -H20 0.1 -m16 0.08 -M16 0.12  -A16 0.01  -I17 23 -H23 0.4 -m17 0.0 -M17 5.0 -A17 0.01  -I18 24 -H24 3.0 -m18 0.0 -M18 5.0 -A18 0.01   -I19 25 -H25 2013.0 -m19 2009.0 -M19 2013.0 -A19 0.1 -G0 2 -G1 3 -n 6 -v0 6 -v1 4 -v2 14 -v3 9 -v4 10 -v5 11  -en 0 -eP0 17 -eV 0.2 -iP 0 -i0 9 -u0 0.0 -U0 10000.0 -i1 17 -u1 0.0 -U1 10000.0 -i2 1 -u2 0.0 -U2 10000 -i3 2 -u3 0.0 -U3 10000 -i4 3 -u4 0.0 -U4 10000 -tn 34 -t0 2000.0 -t1 2033.0 -t4 1 -xn 0 -xR 1 -DP 5  -DC 0 -D0 0 -D1 4 -D2 1 -P0 13 -a0 0  -P1 2 -a1 0  -P2 3 -a2 0  -P3 4 -a3 0 -P4 22 -a4 0 -tE 2.0

   -v4 17 -v5 18  are sigma_0 and sigma_1 time-dependent parameters

   -v3 9 -v4 10 -v5 11 are prevanlences in male, sw female and nsw female populations, respectively.

   If some of the observed variables are not to be represented, then redefine the list of output
   variables. IMPORTANT: Recall that the observed output variables should occupied always the first positions
   in the output vaiable list.  Example:

   . ~$ ./X2W2SILD-YSILD -y0 1 -sT 1.0E-04 -sN 300 -sP 20 -I0 21 -H21 1.0 -m0 0.8  -M0 1.2 -A0 0.01 -I1 0 -H0 100.0  -m1 96.0 -M1 120.0 -A1 0.1  -I2 8 -H8 100.0  -m2 96.0 -M2 120.0  -A2 0.1  -I3 12 -H12   9  -m3 1.0 -M3 19.0  -A3 0.01  -I4 7  -H7  9.0  -m4 0.0 -M4 99.0 -A4 0.01  -I5 16 -H16 0.2   -m5 0.0  -M5 0.99 -A5 0.01  -I6 17 -H17 0.5 -m6 0.0 -M6 0.99 -A6 0.01   -I7 1 -H1 0.001  -m7 0.0 -M7 0.005 -A7 0.0001   -I8 9 -H9 0.0005 -m8 0.0 -M8 0.001 -A8 0.0001   -I9 5 -H5 1.5  -m9 0.5 -M9 4.0 -A9 0.01     -I10 6 -H6 0.1   -m10 0.05 -M10 0.20 -A10 0.01   -I11 15 -H15 10.0 -m11 1.0 -M11 50.0 -A11 0.1  -I12 10 -H10 0.01 -m12 0.0 -M12 0.05 -A12 0.01   -I13 11 -H11  0.01 -m13 0.0 -M13 0.05 -A13 0.01   -I14 18 -H18 0.01 -m14 0.0 -M14 0.05 -A14 0.01   -I15 19 -H19 0.01 -m15 0.0 -M15 0.05 -A15 0.01  -I16 20 -H20 0.1 -m16 0.08 -M16 0.12  -A16 0.01  -I17 23 -H23 0.4 -m17 0.0 -M17 5.0 -A17 0.01  -I18 24 -H24 3.0 -m18 0.0 -M18 5.0 -A18 0.01   -I19 25 -H25 2013.0 -m19 2009.0 -M19 2013.0 -A19 0.1 -G0 2 -G1 2 -n 4 -v0 10 -v1 8 -v2 9 -v3 11 -en 0 -eP0 17 -eV 0.2 -iP 0 -i0 9 -u0 0.0 -U0 10000.0 -i1 17 -u1 0.0 -U1 10000.0 -i2 1 -u2 0.0 -U2 10000 -i3 2 -u3 0.0 -U3 10000 -i4 3 -u4 0.0 -U4 10000 -tn 34 -t0 2000.0 -t1 2033.0 -t4 1 -xn 0 -xR 1 -DP 5  -DC 0 -D0 0 -D1 4 -D2 1 -P0 13 -a0 0  -P1 2 -a1 0  -P2 3 -a2 0  -P3 4 -a3 0 -P4 22 -a4 0 -tE 2.0

   where the following prevalences are shown:
   -n   4   Number of output variables
   -v0 10   Total Female Sexual Worker Disease Prevalence
   -v1  8   Total Female Disease Prevalence
   -v2  9   Total Male_Disease Prevalence
   -v3 11   Total Female Non Sexual Worker Disease Prevalence
*/

double Determine_Turning_Point(double * x_Time, double * y_Time, int N);

void Reading_Sexual_Workers_Numbers_and_Prevalences(double ** , double ** , double ** ,
						    double ** , double ** , double ** );
int main(int argc, char **argv)
{
  float x_Position, y_Position; 
  int No_of_PARAMETER_SETS;
  int i, j, k, kk, l, m, n, z, p, key;
  double value, Min_Value, Min_Value_0, Data_Value, Theory_Value;
  double Likelihood_Value, Average_Likelihood_Value, Standard_Error_Value, Ave, Var;
  Parameter_Table Table;
  Time_Control Time;
  Time_Dependence_Control Time_Dependence;
  Observed_Data * Data;
  double Initial_Observed_Adult_Population, Initial_Observed_Female_Sexual_Workers, Initial_Observed_Female_Sexual_Workers_Infected;
  double ** Variable;
  double ** Variable_Per;
  int No_of_PERCENTILES = 5;
  double Per[] = {0.05, 0.25, 0.5, 0.75, 0.95};
  
  P_ARG = &Table;
  int SIGMOIDAL;

  SIGMOIDAL = 1;

#include "default.c"

  /* Command line arguments */
  if(argc>1) ArgumentControl(argc, argv);

  #include "include.Output_Variables.default.aux.c"
  P_A_R_A_M_E_T_E_R___T_A_B_L_E___A_L_L_O_C(   &Table );
  P_A_R_A_M_E_T_E_R___T_A_B_L_E___U_P_L_O_A_D( &Table, Index_Output_Variables );
  printf(" Parameter_Table structure has been correctly allocated and initiated\n");

  Parameter_Model * Initial_Guess = (Parameter_Model *)malloc( 1 * sizeof(Parameter_Model) );
  P_A_R_A_M_E_T_E_R___I_N_I_T_I_A_L_I_Z_A_T_I_O_N (&Table, Initial_Guess);
  printf(" Parameter_Model structure 'Initial_Guess' has been correctly allocated and initiated\n");

  /* B E G I N : Reserving memmory for Error Model Parameter Space */
  Parameter_Space * Error_Space = (Parameter_Space *)calloc(1, sizeof(Parameter_Space));
  if( No_of_ERROR_PARAMETERS > 0 ) {
#include <include.Error_Control.default.aux.c>
    Parameter_Space_Alloc( Error_Space, No_of_ERROR_PARAMETERS, d_Error);
    Parameter_Table_Copy_into_Parameter_Model(Error_Space->Parameter_min, &Table);
    Model_Variables_Code_into_Parameter_Model(Error_Space->Parameter_min);
    Parameter_Table_Copy_into_Parameter_Model(Error_Space->Parameter_MAX, &Table);
    Model_Variables_Code_into_Parameter_Model(Error_Space->Parameter_MAX);
    Parameter_Table_Copy_into_Parameter_Model(Error_Space->Parameter_Acc, &Table);
    Model_Variables_Code_into_Parameter_Model(Error_Space->Parameter_Acc);
    Parameter_Space_Error_Initialization( Error_Space,
					  No_of_ERROR_PARAMETERS, d_Error,
					  Index_Error, Ranges_Error, Acc_Error );
    //Parameter_Space_fprintf( Initial_Condition_Space, stdout );
    printf("Initial Condition Parameter_Space structure has been correctly allocated and initiated\n");
  }
  Table.E_Space = Error_Space;
  /*     E N D : ------------------------------------- */

  /* B E G I N : Reserving memmory for Initial Conditions Parameter Space */
  Parameter_Space * Initial_Condition_Space = (Parameter_Space *)calloc(1, sizeof(Parameter_Space));
  if( No_of_IC > 0 ) {
#include <include.Initial_Conditions.default.aux.c>
    Parameter_Space_Alloc( Initial_Condition_Space, No_of_IC, d_IC );
    Parameter_Table_Copy_into_Parameter_Model(Initial_Condition_Space->Parameter_min, &Table);
    Model_Variables_Code_into_Parameter_Model(Initial_Condition_Space->Parameter_min);
    Parameter_Table_Copy_into_Parameter_Model(Initial_Condition_Space->Parameter_MAX, &Table);
    Model_Variables_Code_into_Parameter_Model(Initial_Condition_Space->Parameter_MAX);
    Parameter_Table_Copy_into_Parameter_Model(Initial_Condition_Space->Parameter_Acc, &Table);
    Model_Variables_Code_into_Parameter_Model(Initial_Condition_Space->Parameter_Acc);
    Parameter_Space_IC_Initialization( Initial_Condition_Space,
				       No_of_IC, d_IC, Index_IC, Ranges_IC, Acc_IC );
    //Parameter_Space_fprintf( Initial_Condition_Space, stdout );
    printf("Initial Condition Parameter_Space structure has been correctly allocated and initiated\n");
  }
  Table.IC_Space = Initial_Condition_Space;
  /*     E N D : ------------------------------------- */

  /* B E G I N : Reserving memmory for Parameter Space */
  #include <include.Parameter_Space.default.aux.c>
  Parameter_Space * Space = (Parameter_Space *)calloc(1, sizeof(Parameter_Space));
  Parameter_Space_Alloc( Space, No_of_PARAMETERS, d);
  Parameter_Space_Initialization( Space, No_of_PARAMETERS, TOLERANCE, MAX_No_of_ITERATIONS,
				  d, Index, Ranges, Acc);
  Parameter_Table_Index_Update(Index, No_of_PARAMETERS, &Table);
  Table.S = Space;
  printf("Parameter_Space structure has been correctly allocated and initiated\n");
  /*     E N D : ------------------------------------- */

#if defined CPGPLOT_REPRESENTATION
  Table.CPG = A_C_T_I_V_A_T_E___C_P_G_P_L_O_T ( SUB_OUTPUT_VARIABLES, I_Time, 0, CPG_DRIVER_NAME);
  printf(" Parameter_CPGPLOT plotting structure has been correctly allocated and initiated\n");
#endif

#include <gsl_random_number_Setup.c>
#if defined VERBOSE
  /* BEGIN: Checking Random Number Generator Setup */
  for(i=0; i<10; i++){
    printf( "f(%d)=%g, ", i, gsl_rng_uniform(r) );
    printf( "f_GAUS(%d)=%g\n", i, gsl_ran_gaussian(r, 1.0) );
  }
  printf("\n");//Press_Key();
  /*   END: Checking Random Number Generator Setup */
#endif

  int No_of_SETS_MAX  = 35000;
  int No_of_INITIAL_YEARS = 1; // 11; (3 different initial years: 2000, 2001, and 2002)
  int No_of_CITIES = 11;       // 11;

  char * City_Names[] = { "Antananarivo", "Antsiranana",
			  "Mahajanga",    "Toamasina",
			  "Fianarantsoa", "Toliary",
			  "Taolagnaro",   "Moramanga",
			  "Antsirabe",    "Morondava",  
			  "Nosy_Be" };

  char * City_Short_Names[] = { "Anta",  "Ants",
				"Maha",  "Toam",
				"Fian",  "Toli",
				"Taol",  "Mora",
				"Aabe",  "Moro",
				"Nosy" };

  char ** City_Short_Names_2nd = (char **)calloc(No_of_CITIES, sizeof(char *) );
  for(k=0; k<No_of_CITIES; k++)
    City_Short_Names_2nd[k] = (char *)calloc(10, sizeof(char) );
 
  /* B E G I N : Time Dependent Parameters, Observed Data, and Demo Parameters File Names */
  char * pF;
  char ** TIME_PARAMETERS_FILE = (char **)calloc(No_of_CITIES, sizeof(char *) ); /* Input files  */
  char ** OBSERVED_DATA_FILE   = (char **)calloc(No_of_CITIES, sizeof(char *) ); /* Input files  */
  char ** PARAMETER_SET_FILE   = (char **)calloc(No_of_CITIES, sizeof(char *) ); /* Input files */
  char *** TIME_EVOLUTION_FILE_NAME = (char ***)calloc(No_of_CITIES, sizeof(char **) ); /* Output files */

  for(k = 0; k<No_of_CITIES; k++) {
    TIME_PARAMETERS_FILE[k] = (char *)calloc( 100, sizeof(char) );  /* Input file  */
    OBSERVED_DATA_FILE[k]   = (char *)calloc( 100, sizeof(char) );  /* Input file  */
    PARAMETER_SET_FILE[k]   = (char *)calloc( 100, sizeof(char) );  /* Input file  */

    TIME_EVOLUTION_FILE_NAME[k] = (char **)calloc( SUB_OUTPUT_VARIABLES, sizeof(char *) );
    for(i = 0; i<SUB_OUTPUT_VARIABLES; i++)
      TIME_EVOLUTION_FILE_NAME[k][i] = (char *)calloc( 100, sizeof(char) ); /* Output file */
  }
  /*     E N D : ------------------------------------------------------------------------ */

  FILE **** TEMPORAL_EVOLUTION_FILE;
  TEMPORAL_EVOLUTION_FILE = (FILE ****)calloc( No_of_CITIES, sizeof(FILE ***) );
  for(k = 0; k<No_of_CITIES; k++) {
    TEMPORAL_EVOLUTION_FILE[k] = (FILE ***)calloc( No_of_INITIAL_YEARS, sizeof(FILE **) );
    for(n = 0; n < No_of_INITIAL_YEARS; n++ ){
      TEMPORAL_EVOLUTION_FILE[k][n] = (FILE **)calloc( SUB_OUTPUT_VARIABLES, sizeof(FILE *) );
    }
  }

  double ** Demo_Data = (double **)calloc(No_of_SETS_MAX, sizeof(double *));
  for(i=0; i<No_of_SETS_MAX; i++)
    Demo_Data[i] = (double *)calloc(No_of_PARAMETERS, sizeof(double)); //5 Demographic Parameters
  
  char * Year = (char *)calloc(30, sizeof(char));

  // If No_of_OBSERVED_VARIABLES = 0, then none observed variables will be read from files!!!
  int No_of_OBSERVED_VARIABLES;
  int No_of_OBSERVED_VARIABLES_MAX;
  No_of_OBSERVED_VARIABLES     = 3;
  No_of_OBSERVED_VARIABLES_MAX = 3;
  double **** Observed_Population_Data;
  double ***** Temporal_Evolution;

  Observed_Population_Data = (double ****)calloc(No_of_CITIES, sizeof(double ***) );
  for(k = 0; k<No_of_CITIES; k++) {
    Observed_Population_Data[k] = (double ***)calloc(No_of_INITIAL_YEARS, sizeof(double **) );
    for(n = 0; n < No_of_INITIAL_YEARS; n++ ){
      Observed_Population_Data[k][n] = (double **)calloc(No_of_OBSERVED_VARIABLES_MAX,
							 sizeof(double *) );
      for(i = 0; i < No_of_OBSERVED_VARIABLES_MAX; i++)
	Observed_Population_Data[k][n][i] = (double *)calloc(I_Time, sizeof(double) );
    }
  }

  char   ** Name_of_Rows          = (char **)calloc(No_of_OBSERVED_VARIABLES_MAX, sizeof(char *));
  double ** Empirical_Data_Matrix = (double **)calloc(No_of_OBSERVED_VARIABLES_MAX, sizeof(double*));

  for (i=0; i<No_of_OBSERVED_VARIABLES_MAX; i++) {
    key = Table.OUTPUT_VARIABLE_INDEX[i];
    Name_of_Rows[i]         = Table.Output_Variable_Symbol[key];
    Empirical_Data_Matrix[i] = (double *)calloc( I_Time, sizeof(double) );
  }

  double *** R_0_Value = (double ***)calloc(No_of_CITIES, sizeof(double **) );
  for(k = 0; k < No_of_CITIES; k++) {
    R_0_Value[k] = (double **)calloc(No_of_INITIAL_YEARS, sizeof(double *) );
    for(n = 0; n < No_of_INITIAL_YEARS; n++ ) 
      R_0_Value[k][n] = (double *)calloc(No_of_SETS_MAX, sizeof(double) );
  }

  double **** Parameter_Value = (double ****)calloc(No_of_CITIES, sizeof(double ***) );
  for(k = 0; k < No_of_CITIES; k++) {
    Parameter_Value[k] = (double ***)calloc(No_of_INITIAL_YEARS, sizeof(double **) );
    for(n = 0; n < No_of_INITIAL_YEARS; n++ ) {
      Parameter_Value[k][n] = (double **)calloc(No_of_PARAMETERS, sizeof(double *) );
      for(p = 0; p<No_of_PARAMETERS; p++)
	Parameter_Value[k][n][p] = (double *)calloc(No_of_SETS_MAX, sizeof(double) );
    }
  }
  
  Temporal_Evolution = (double *****)calloc(No_of_CITIES, sizeof(double ****) );
  for(k = 0; k < No_of_CITIES; k++) {
    Temporal_Evolution[k] = (double ****)calloc(No_of_INITIAL_YEARS, sizeof(double ***) );
    for(n = 0; n < No_of_INITIAL_YEARS; n++ ) {
      Temporal_Evolution[k][n] = (double ***)calloc(SUB_OUTPUT_VARIABLES, sizeof(double **) );
      for(i = 0; i < SUB_OUTPUT_VARIABLES; i++) {
	Temporal_Evolution[k][n][i] = (double **)calloc(No_of_SETS_MAX, sizeof(double *) );
	for(j = 0; j < No_of_SETS_MAX; j++)
	  Temporal_Evolution[k][n][i][j] = (double *)calloc(I_Time, sizeof(double) );
      }
    }
  }

  int ** REALIZATIONS = (int **)calloc( No_of_CITIES, sizeof(int *) );
  for(k = 0; k<No_of_CITIES; k++ )
    REALIZATIONS[k] = (int *)calloc( No_of_INITIAL_YEARS, sizeof(int) );

  int I_Time_Total = I_Time;
  int I_Time_2000 = 17;

  /* Main Numerical Integration loop starts here. It is a three level loop over:
     . k: Cities
     . n: Initial "disease-invasion" year
     . j: Parametric configuration (over a No_of_Parameter_Sets for each city and invasion year)
  */
  for(k = 0; k<No_of_CITIES; k++)
  // k=8 is a city with no infection ("Antsirabe")
  if ( k != 8 ) {

    for(n=0; n < No_of_INITIAL_YEARS; n++) { // For each introduction time

      Year[0]='\0'; sprintf( Year, "%d", n+2000 );
      printf("Initial Year: %s\n", Year);

      PARAMETER_SET_FILE[k][0] = '\0';
      pF = strcat(PARAMETER_SET_FILE[k], "Full_Parameter_Set_");
      pF = strcat(PARAMETER_SET_FILE[k], City_Names[k]);
      pF = strcat(PARAMETER_SET_FILE[k], "_");
      pF = strcat(PARAMETER_SET_FILE[k], Year);
      if (SIGMOIDAL == 1) pF = strcat(PARAMETER_SET_FILE[k], "_Sigmoidal_Ordered.dat");
      else                pF = strcat(PARAMETER_SET_FILE[k], "_Ordered.dat");

      for(i=0; i<SUB_OUTPUT_VARIABLES; i++) {
	TIME_EVOLUTION_FILE_NAME[k][i][0] = '\0';
	pF = strcat(TIME_EVOLUTION_FILE_NAME[k][i], "Time_Evolution_Extrapolated_");
	pF = strcat(TIME_EVOLUTION_FILE_NAME[k][i], City_Names[k]);
	pF = strcat(TIME_EVOLUTION_FILE_NAME[k][i], "_");
	pF = strcat(TIME_EVOLUTION_FILE_NAME[k][i], Year);
	pF = strcat(TIME_EVOLUTION_FILE_NAME[k][i], "_");
	key = Table.OUTPUT_VARIABLE_INDEX[i];
	pF = strcat(TIME_EVOLUTION_FILE_NAME[k][i], Table.Output_Variable_Symbol[key]);
	if( SIGMOIDAL == 1 ) pF = strcat(TIME_EVOLUTION_FILE_NAME[k][i], "_Sigmoidal.dat");
	else                 pF = strcat(TIME_EVOLUTION_FILE_NAME[k][i], ".dat");
      }

      Reading_Model_Parameters_from_File(PARAMETER_SET_FILE[k], Demo_Data,
					 &No_of_PARAMETER_SETS, No_of_PARAMETERS);

      assert( No_of_PARAMETER_SETS < No_of_SETS_MAX );

      printf("Full of Parameters (City: %s):\n", City_Names[k]);
      Writing_Model_Parameters_Matrix(&Table, City_Names[k],
				      Demo_Data, No_of_PARAMETER_SETS, No_of_PARAMETERS);

      TIME_PARAMETERS_FILE[k][0] = '\0';
      pF = strcat(TIME_PARAMETERS_FILE[k], "Time_Dependent_Parameters_Extrapolated_Corrected_");
      pF = strcat(TIME_PARAMETERS_FILE[k], City_Names[k]);
      pF = strcat(TIME_PARAMETERS_FILE[k], "_");
      pF = strcat(TIME_PARAMETERS_FILE[k], Year);
      pF = strcat(TIME_PARAMETERS_FILE[k], ".dat");

      OBSERVED_DATA_FILE[k][0] = '\0';
      pF = strcat(OBSERVED_DATA_FILE[k], "Observed_Data_File_");
      pF = strcat(OBSERVED_DATA_FILE[k], City_Names[k]);
      pF = strcat(OBSERVED_DATA_FILE[k], "_");
      pF = strcat(OBSERVED_DATA_FILE[k], Year);
      if( SIGMOIDAL == 1)  pF = strcat(OBSERVED_DATA_FILE[k], "_Sigmoidal_Exponential.dat");
      else                 pF = strcat(OBSERVED_DATA_FILE[k], "_Exponential.dat");

      Reading_Observed_Data(OBSERVED_DATA_FILE[k], Empirical_Data_Matrix,
			    No_of_OBSERVED_VARIABLES_MAX, I_Time_2000 - n,
			    &No_of_OBSERVED_VARIABLES,
			    Table.OUTPUT_VARIABLE_INDEX, SUB_OUTPUT_VARIABLES,
			    &Initial_Observed_Adult_Population,
			    &Initial_Observed_Female_Sexual_Workers,
			    &Initial_Observed_Female_Sexual_Workers_Infected);

      if (No_of_OBSERVED_VARIABLES > 0 ) {

	Writing_Standard_Data_Matrix( Empirical_Data_Matrix,
				      No_of_OBSERVED_VARIABLES, I_Time_2000 - n,
				      1, Name_of_Rows,
				      0, Time.Time_Vector);

	printf(" Observe_Data type of structure will be allocated and initiated\n");
	printf(" Number of observed variables: %d\n", No_of_OBSERVED_VARIABLES);
	assert( No_of_OBSERVED_VARIABLES <= 3);
      }
      /* B E G I N : Reserving memmory for Observed Data  */
      Data = (Observed_Data *)calloc(1, sizeof(Observed_Data));
      Observed_Data_Alloc( Data, No_of_OBSERVED_VARIABLES_MAX, I_Time_2000 - n);
      Observed_Data_Initialization( Data, No_of_OBSERVED_VARIABLES, I_Time_2000 - n,
				    Empirical_Data_Matrix,
				    City_Names[k] );
      printf(" Observe_Data type of structure has been correctly allocated and initiated\n");
      // getchar();
      /*     E N D : ------------------------------------- */

      I_Time = I_Time_Total - n;
      Time_0 = 2000.0 + (double)n;  // Time_1 will be defined by command line argument!!!

      printf(" %d output variables of length %d points will be allocated\n",
	     SUB_OUTPUT_VARIABLES, I_Time);

      if (TYPE_of_TIME_DEPENDENCE == 0) {
        printf(" No Time Dependence!!!\n");
        printf(" Check -t4 argument. It should be: -t4 1, but it is: -t4 %d\n",
        TYPE_of_TIME_DEPENDENCE);
        printf(" The program will exit.\n");
        exit(0);
      }
      else {
        #include <include.Time_Dependence_Control.default.aux.c>
        printf(" Time_Dependence_Control and Time_Control structures will be allocated: \n");
        Time_Dependence_Control_Alloc(&Time, &Time_Dependence, &Table,
          I_Time, TIME_DEPENDENT_PARAMETERS, No_of_COVARIATES);
          printf(" Both Time_Control and Time_Dependence_Control structures have been\n");
          printf(" correctly allocated\n");
      }

      for(i=0; i<SUB_OUTPUT_VARIABLES; i++) {
      	TEMPORAL_EVOLUTION_FILE[k][n][i] = fopen(TIME_EVOLUTION_FILE_NAME[k][i], "w");
      	for(j = 0; j<I_Time; j++)
      	  fprintf(TEMPORAL_EVOLUTION_FILE[k][n][i], "%g\t", Time.Time_Vector[j]);
      	fprintf(TEMPORAL_EVOLUTION_FILE[k][n][i], "\n");
      }

      int s_Attemps = 0;
      int No_of_Parameter_Sets = No_of_PARAMETER_SETS;
      int Total_Tries;

      if( No_of_PARAMETER_SETS > 2000 ) No_of_Parameter_Sets = 2000;

      REALIZATIONS[k][n] = No_of_Parameter_Sets;
      Total_Tries        = No_of_Parameter_Sets;

      for(j=0; j<No_of_Parameter_Sets; j++) {

        Parameter_Model_Copy_into_Parameter_Table(&Table, Initial_Guess);
        Uploading_Model_Parameters_into_Parameter_Table(&Table, Demo_Data, j);
	Time_Dependence_Control_Upload(&Time, &Time_Dependence, &Table,
				       I_Time, I_Time,
				       TIME_DEPENDENT_PARAMETERS,
				       TYPE_of_TIME_DEPENDENCE,
				       TYPE_0_PARAMETERS,
				       TYPE_1_PARAMETERS,
				       TYPE_2_PARAMETERS,
				       No_of_COVARIATES,
				       dependent_parameter, forcing_pattern,
				       "File_of_Covariates.dat",
				       TIME_PARAMETERS_FILE[k]);
	assert( Time_Dependence.No_of_TIMES == I_Time );
	/* Initial conditions from empirical data at the initial time ( -xn 0 ) */
	Initial_Condition_from_Initial_Values_into_Parameter_Table (&Table,
								    Initial_Observed_Adult_Population,
								    Initial_Observed_Female_Sexual_Workers,
								    Initial_Observed_Female_Sexual_Workers_Infected );

        Parameter_Fitting * F = (Parameter_Fitting*)calloc(1,sizeof(Parameter_Fitting));
        F->Data                  = Data;
        F->Space                 = Space;
        F->Table                 = &Table;
        F->Verbose               = 0;     // 1: Verbose                // 0: Non Verbose
        F->Minimization          = 0;     // 1: Function Minimization  // 0: Function Evaluation
        F->Bounded_Parameter_Set = 1;
	      F->TWO_PHASES            = 0;
        F->Function              = GSL_Function_to_Minimize;

        if(F->Verbose == 1) {
          if(No_of_IC > 0)
          Parameter_Space_Write_Min_Max_IC_Values (Initial_Condition_Space, &Table );
          printf("\n");
          if(No_of_ERROR_PARAMETERS > 0)
          Parameter_Space_Write_Min_Max_Error_Values (Error_Space, &Table );
          printf("\n");
          Parameter_Space_Write_Min_Max_Values (Space, &Table );
          printf("\n");
        }

	/* R_0 estimation at the begining of the period for the j-th parametric configuration */
	if (Time.TYPE_of_TIME_DEPENDENCE > 0) Time_Dependence_Apply( &Table, Time.Time_Vector[0] );
	R_0_Value[k][n][j] = R_0_Function(&Table);
	/* Storing parameter values for every city and initial year */
	for(p = 0; p<No_of_PARAMETERS; p++) 
	  Parameter_Value[k][n][p][j] = Demo_Data[j][p];
	
	/* Main procedure is here:                  */
	Min_Value   = Inspecting_Solution_Driver( F );

        printf(" City: %s [Year: %s]:\t", City_Names[k], Year);
	printf(" NLL(%d) = %g\t", j, Min_Value);
	printf(" R_0(%d) = %g\t", j, R_0_Value[k][n][j]);
        printf(" Parameter Set Attemp No: %d\t Remaining Attemps: %d\n",
	       s_Attemps, Total_Tries-s_Attemps );
	// Press_Key();
	
        if (F->Bounded_Parameter_Set == 1 ) {

          for(i=0; i<No_of_PARAMETERS; i++) {
            key = Space->Parameter_Index[i];
            value = AssignStructValue_to_VectorEntry(key, &Table);
            printf("%s = %g  ", Table.Symbol_Parameters[key], value);

          }
          for(i=0; i<No_of_IC; i++) {
            key = Initial_Condition_Space->Parameter_Index[i];
            value = Model_Variable_Initial_Condition_into_Vector_Entry_Table( key, &Table );
            printf("%s = %g  ", Table.Model_Variable_Symbol[key], value);

          }
          for(i=0; i<No_of_ERROR_PARAMETERS; i++) {
            key = Error_Space->Parameter_Index[i];
            value = Error_Model_into_Vector_Entry_Table( key, &Table );
            if(key < OUTPUT_VARIABLES_GENUINE)
            printf("%s = %g  ", Table.Output_Variable_Symbol[key], value);
            else
            printf("Error_Parameter_%d = %g  ", i, value);

          }

	  /* Saving Temporal Evolutions */
	  for(i = 0;  i < SUB_OUTPUT_VARIABLES; i++) {
	    for( l = 0; l < I_Time; l++ ) {
	      Temporal_Evolution[k][n][i][j][l]      = Table.Matrix_Output_Variables[i][l];

	      if (i < No_of_OBSERVED_VARIABLES && l < I_Time_2000 - n)
		Observed_Population_Data[k][n][i][l] = F->Data->N[i][l];

	      fprintf(TEMPORAL_EVOLUTION_FILE[k][n][i], "%g\t",
		      Table.Matrix_Output_Variables[i][l]);
	    }
	    fprintf(TEMPORAL_EVOLUTION_FILE[k][n][i], "\n");
	  }

        }
	else break;

	printf("\n"); // getchar();

        free(F);

        s_Attemps++;
      }

      for( i=0; i<SUB_OUTPUT_VARIABLES; i++ ) fclose(TEMPORAL_EVOLUTION_FILE[k][n][i]);

      Observed_Data_Free(Data);
      free(Data);

      Time_Dependence_Control_Free( &Time_Dependence, &Table );
    }
  }

  I_Time = I_Time_Total;

#if defined CPGPLOT_REPRESENTATION
  int SAME;
  double Ini_Year;
  double * x_Data = (double *)calloc( I_Time, sizeof(double) );
  double * y_Data = (double *)calloc( I_Time, sizeof(double) );
  double ** xn_Data = (double **)calloc( I_Time, sizeof(double *) );
  double ** yn_Data = (double **)calloc( 2, sizeof(double *) );
  xn_Data[0] = (double *)calloc( I_Time, sizeof(double) );
  yn_Data[0] = (double *)calloc( I_Time, sizeof(double) );
  xn_Data[1] = (double *)calloc( I_Time, sizeof(double) );
  yn_Data[1] = (double *)calloc( I_Time, sizeof(double) );
  double ** Prevalence = (double **)calloc( No_of_CITIES, sizeof(double *) );
  double ** Prevalence_Inf = (double **)calloc( No_of_CITIES, sizeof(double *) );
  double ** Prevalence_Sup = (double **)calloc( No_of_CITIES, sizeof(double *) );
  double ** SexWorkers = (double **)calloc( No_of_CITIES, sizeof(double *) );
  double ** SexWorkers_Inf = (double **)calloc( No_of_CITIES, sizeof(double *) );
  double ** SexWorkers_Sup = (double **)calloc( No_of_CITIES, sizeof(double *) );
  for (k = 0; k < No_of_CITIES; k++) { // only two times
    Prevalence[k] = (double *)calloc( 2, sizeof(double) );
    Prevalence_Inf[k] = (double *)calloc( 2, sizeof(double) );
    Prevalence_Sup[k] = (double *)calloc( 2, sizeof(double) );

    SexWorkers[k] = (double *)calloc( 2, sizeof(double) );
    SexWorkers_Inf[k] = (double *)calloc( 2, sizeof(double) );
    SexWorkers_Sup[k] = (double *)calloc( 2, sizeof(double) );
  }

  Reading_Sexual_Workers_Numbers_and_Prevalences(Prevalence, Prevalence_Inf, Prevalence_Sup,
						 SexWorkers, SexWorkers_Inf, SexWorkers_Sup);
  getchar();

  char * Out_Var_Symbol = (char *)calloc(10, sizeof(char) );
  char * Out_Var_Label = (char *)calloc(100, sizeof(char) );

  /* Main CPGPLOT representaiton loop starts here. Again, it is a three level loop over:
     . k: Cities
     . n: Initial "disease-invasion" year
     . j: Parametric configuration (over a No_of_Parameter_Sets for each city and invasion year)
  */
  // Plotting esamble of projected trajectories:
  for(k = 0; k<No_of_CITIES; k++) {
    if ( k != 8 )
      for(n = 0; n<No_of_INITIAL_YEARS; n++) {

      Realizations = REALIZATIONS[k][n];

      I_Time = I_Time_Total - n;
      Time_0 = 2000.0 + (double)n; // Time_1 will be defined by command line argument!!!
      Ini_Year = Time_0;

      for (i=0; i<SUB_OUTPUT_VARIABLES; i++) {

	SAME = 0;

	Table.CPG->CPG__PANEL__X =  1; //
	Table.CPG->CPG__PANEL__Y =  2; // Aquestes dues lines fora???
	
	Table.CPG->type_of_Width =  5;
	Table.CPG->color_Index   =  3;
	Table.CPG->type_of_Symbol = 1;
	Table.CPG->type_of_Line   = 1;

	key = Table.OUTPUT_VARIABLE_INDEX[i];
	AssignCPGPLOT_Symbol_to_Output_Variables(key, Out_Var_Symbol, &Table);

	Table.CPG->CPG_SCALE_X   = 1;              Table.CPG->CPG_SCALE_Y   =  0;
	Table.CPG->CPG_RANGE_X_0 = 1999.5;         Table.CPG->CPG_RANGE_Y_0 =  0.0;
	Table.CPG->CPG_RANGE_X_1 = Time_1 + 0.5;   Table.CPG->CPG_RANGE_Y_1 =  1.0E+05;

	// Prevalences:
	/* -v0 10   Total Female Sexual Worker Disease Prevalence     */
	/* -v1  8   Total Female Disease Prevalence                   */
	/* -v2  9   Total Male_Disease Prevalence                     */
	/* -v3 11   Total Female Non Sexual Worker Disease Prevalence */
	/* -v4 7    Total Prevalence                                  */
	if( key == 7 || key == 8 || key == 9 || key == 10 || key == 11 ) {

	  Table.CPG->CPG_SCALE_Y   =  1;
	  Table.CPG->CPG_RANGE_Y_0 =  0.0;
	  Table.CPG->CPG_RANGE_Y_1 =  1.0; //0.5
	}

	printf("City: %s:\t Output Variable: %s\n", City_Names[k], Out_Var_Symbol);
	for( j = 0; j<Realizations; j++ ) {

	  //printf("Set IDE: %d\n", j);

	  for(l=0; l < I_Time; l++) {

	    y_Data[l] = Temporal_Evolution[k][n][i][j][l];
	    x_Data[l] = Ini_Year + l;
	  }

	  CPGPLOT___X_Y___P_L_O_T_T_I_N_G___S_A_M_E___P_L_O_T  ( Table.CPG, SAME,
								 I_Time,
								 x_Data, y_Data,
								 "Year",
								 Out_Var_Symbol,
								 City_Names[k],
								 Table.CPG->CPG_SCALE_X,
								 Table.CPG->CPG_SCALE_Y );
	  SAME = 1;
	}

	if ( i < No_of_OBSERVED_VARIABLES ) {
	  for(l=0; l < I_Time; l++) {
	    x_Data[l] = Ini_Year + l;
	    if (l < I_Time_2000 - n)
	      y_Data[l] = Observed_Population_Data[k][n][i][l];
	  }

	  Table.CPG->type_of_Symbol = 8;
	  Table.CPG->color_Index    = 1;
	  Table.CPG->type_of_Line   = 1;

	  CPGPLOT___X_Y___S_C_A_T_T_E_R_E_D___S_A_M_E___P_L_O_T ( Table.CPG, SAME,
								  I_Time_2000 - n,
								  x_Data, y_Data,
								  "Year",
								  Out_Var_Symbol,
								  City_Names[k],
								  Table.CPG->CPG_SCALE_X,
								  Table.CPG->CPG_SCALE_Y );
	}

	if ( key == 10 ) {
	  x_Data[0]     = 2012.0;            x_Data[1]     = 2016.0;
	  xn_Data[0][0] = 2012.0;            xn_Data[0][1] = 2016.0;
	  xn_Data[1][0] = 2012.0;            xn_Data[1][1] = 2016.0;

	  y_Data[0]     = Prevalence[k][0];      y_Data[1]     = Prevalence[k][1];
	  yn_Data[0][0] = Prevalence_Inf[k][0];  yn_Data[0][1] = Prevalence_Inf[k][1];
	  yn_Data[1][0] = Prevalence_Sup[k][0];  yn_Data[1][1] = Prevalence_Sup[k][1];
	}
	if ( key == 4 ) {
	  x_Data[0]     = 2014.0;            x_Data[1]     = 2017.0;
	  xn_Data[0][0] = 2014.0;            xn_Data[0][1] = 2017.0;
	  xn_Data[1][0] = 2014.0;            xn_Data[1][1] = 2017.0;

	  y_Data[0]     = SexWorkers[k][0];      y_Data[1]     = SexWorkers[k][1];
	  yn_Data[0][0] = SexWorkers_Inf[k][0];  yn_Data[0][1] = SexWorkers_Inf[k][1];
	  yn_Data[1][0] = SexWorkers_Sup[k][0];  yn_Data[1][1] = SexWorkers_Sup[k][1];
	}
	if ( key == 10 || key == 4 ) {
	  Table.CPG->color_Index    = 8;
	  Table.CPG->type_of_Width  = 5;
	  Table.CPG->type_of_Symbol = 4;
	  Table.CPG->type_of_Line   = 1;

	  int BAR_TIP_LENGTH = 5;
	  CPGPLOT___X_Y___P_L_O_T_T_I_N_G___2DIR___E_R_R_O_R___B_A_R_S ( Table.CPG, 2,
									 x_Data, xn_Data,
									 y_Data, yn_Data,
									 BAR_TIP_LENGTH,
									 0);
	}
      }
      getchar();
    }
  }

  // Plotting esamble of projected distributions (meadian and percentiles):
  for(k = 0; k<No_of_CITIES; k++) {
    if ( k != 8 )
      for(n = 0; n<No_of_INITIAL_YEARS; n++) {

	I_Time = I_Time_Total - n;
	Time_0 = 2000.0 + (double)n; // Time_1 will be defined by command line argument!!!
	Ini_Year = Time_0;
	
	Realizations = REALIZATIONS[k][n];
	
	Variable_Per    = (double **)calloc(No_of_PERCENTILES, sizeof(double *) );
	for(j = 0; j < No_of_PERCENTILES; j++ )
	  Variable_Per[j] = (double *)calloc(I_Time, sizeof(double) );
	
	Variable = (double **)calloc(Realizations, sizeof(double *) );
	for(j = 0; j < Realizations; j++ )
	  Variable[j] = (double *)calloc(I_Time, sizeof(double) );
	
	for (i=0; i<SUB_OUTPUT_VARIABLES; i++) {
	  
	  SAME = 0;
	  
	  Table.CPG->CPG__PANEL__X =  1;
	  Table.CPG->CPG__PANEL__Y =  2;
	  
	  Table.CPG->type_of_Width =  5;
	  Table.CPG->color_Index   =  3;
	  Table.CPG->type_of_Symbol = 1;
	  Table.CPG->type_of_Line   = 1;
	  
	  key = Table.OUTPUT_VARIABLE_INDEX[i];
	  AssignCPGPLOT_Symbol_to_Output_Variables(key, Out_Var_Symbol, &Table);
	  
	  Table.CPG->CPG_SCALE_X   = 1;              Table.CPG->CPG_SCALE_Y   =  0;
	  Table.CPG->CPG_RANGE_X_0 = 1999.5;         Table.CPG->CPG_RANGE_Y_0 =  0.0;
	  Table.CPG->CPG_RANGE_X_1 = Time_1 + 0.5;   Table.CPG->CPG_RANGE_Y_1 =  1.0E+05;
	  
	  // Prevalences:
	  /* -v0 10   Total Female Sexual Worker Disease Prevalence     */
	  /* -v1  8   Total Female Disease Prevalence                   */
	  /* -v2  9   Total Male_Disease Prevalence                     */
	  /* -v3 11   Total Female Non Sexual Worker Disease Prevalence */
	  /* -v4 7    Total Prevalence                                  */
	  if( key == 7 || key == 8 || key == 9 || key == 10 || key == 11 ) {
	    Table.CPG->CPG_SCALE_Y   =  1;
	    Table.CPG->CPG_RANGE_Y_0 =  0.0;
	    Table.CPG->CPG_RANGE_Y_1 =  1.0; //0.5
	  }

	  for(j=0; j < Realizations; j++) { 
	    for(l=0; l < I_Time; l++) {
	      Variable[j][l] = Temporal_Evolution[k][n][i][j][l];
	      x_Data[l] = Ini_Year + l;
	    }
	  }	  
	  
	  Percentile_Calculation_Simple(x_Data, Variable, I_Time, Realizations,
					Per, No_of_PERCENTILES,
					Variable_Per);

	  for( j = 0; j<No_of_PERCENTILES; j++ ) {

	    /*  0.50 Median */
	    Table.CPG->type_of_Width =  5;
	    Table.CPG->color_Index   =  4;
	    Table.CPG->type_of_Symbol = 1;
	    Table.CPG->type_of_Line   = 1;
	    /* 0.95 and 0.05 or extreme values */
	    if ( j == 0 || j == (No_of_PERCENTILES-1) ) {
		Table.CPG->type_of_Width =  3;
		Table.CPG->color_Index   =  11;
		Table.CPG->type_of_Symbol = 1;
		Table.CPG->type_of_Line   = 1;
	    }
	    if( No_of_PERCENTILES == 5 ){  
	      /* 0.25 and 0.75 or intermediate values */
	      if ( j == 1 || j == (No_of_PERCENTILES-2) ) { 	
		Table.CPG->type_of_Width =  1;
		Table.CPG->color_Index   =  11;
		Table.CPG->type_of_Symbol = 1;
		Table.CPG->type_of_Line   = 3;
	      }
	    }
	    CPGPLOT___X_Y___P_L_O_T_T_I_N_G___S_A_M_E___P_L_O_T  ( Table.CPG, SAME,
								   I_Time,
								   x_Data, Variable_Per[j],
								   "Year",
								   Out_Var_Symbol,
								   City_Names[k],
								   Table.CPG->CPG_SCALE_X,
								   Table.CPG->CPG_SCALE_Y );
	    SAME = 1;
	  }

	  if ( key == 10 ) {
	    x_Data[0]     = 2012.0;            x_Data[1]     = 2016.0;
	    xn_Data[0][0] = 2012.0;            xn_Data[0][1] = 2016.0;
	    xn_Data[1][0] = 2012.0;            xn_Data[1][1] = 2016.0;
	    
	    y_Data[0]     = Prevalence[k][0];      y_Data[1]     = Prevalence[k][1];
	    yn_Data[0][0] = Prevalence_Inf[k][0];  yn_Data[0][1] = Prevalence_Inf[k][1];
	    yn_Data[1][0] = Prevalence_Sup[k][0];  yn_Data[1][1] = Prevalence_Sup[k][1];
	  }
	  if ( key == 4 ) {
	    x_Data[0]     = 2014.0;            x_Data[1]     = 2017.0;
	    xn_Data[0][0] = 2014.0;            xn_Data[0][1] = 2017.0;
	    xn_Data[1][0] = 2014.0;            xn_Data[1][1] = 2017.0;
	    
	    y_Data[0]     = SexWorkers[k][0];      y_Data[1]     = SexWorkers[k][1];
	    yn_Data[0][0] = SexWorkers_Inf[k][0];  yn_Data[0][1] = SexWorkers_Inf[k][1];
	    yn_Data[1][0] = SexWorkers_Sup[k][0];  yn_Data[1][1] = SexWorkers_Sup[k][1];
	  }
	  if ( key == 10 || key == 4 ) {
	    Table.CPG->color_Index    = 8;
	    Table.CPG->type_of_Width  = 5;
	    Table.CPG->type_of_Symbol = 4;
	    Table.CPG->type_of_Line   = 1;
	    
	  int BAR_TIP_LENGTH = 5;
	  CPGPLOT___X_Y___P_L_O_T_T_I_N_G___2DIR___E_R_R_O_R___B_A_R_S ( Table.CPG, 2,
									 x_Data, xn_Data,
									 y_Data, yn_Data,
									 BAR_TIP_LENGTH,
									 0);
	  }
	}
	
	for(j = 0; j < No_of_PERCENTILES; j++ )
	  free(Variable_Per[j]);
	free(Variable_Per);
	
	for(j = 0; j < Realizations; j++ )
	  free(Variable[j]);
	free(Variable);
	
	getchar();
      }
  }

  // Plotting box plots of turning points and total prevalences
  // Activating another window...
  CPG__PANEL__X =  1;
  CPG__PANEL__Y =  1;
  Parameter_CPGPLOT * C = A_C_T_I_V_A_T_E___C_P_G_P_L_O_T ( SUB_OUTPUT_VARIABLES,
							    No_of_CITIES, 0, CPG_DRIVER_NAME);
  printf(" Parameter_CPGPLOT plotting structure has been correctly allocated and initiated\n");
  
  Variable_Per    = (double **)calloc(No_of_PERCENTILES, sizeof(double *) );
  for(j = 0; j < No_of_PERCENTILES; j++ )
    Variable_Per[j] = (double *)calloc(No_of_CITIES, sizeof(double) );
  
  Variable = (double **)calloc(No_of_SETS_MAX, sizeof(double *) );
  for(j = 0; j <  No_of_SETS_MAX; j++ )
    Variable[j] = (double *)calloc(No_of_CITIES, sizeof(double) );

  for (i=0; i<SUB_OUTPUT_VARIABLES; i++) {
    key = Table.OUTPUT_VARIABLE_INDEX[i];
    AssignCPGPLOT_Symbol_to_Output_Variables(key, Out_Var_Symbol, &Table);
    AssignLabel_to_Output_Variables(key, Out_Var_Label, &Table);
    
    if( key == 7 || key == 8 || key == 9 || key == 10 || key == 11 ) {
      
      for(n = 0; n<No_of_INITIAL_YEARS; n++) {

	I_Time = I_Time_Total - n;
	Time_0 = 2000.0 + (double)n; // Time_1 will be defined by command line argument!!!
	Ini_Year = Time_0;
	    
	for(kk=0; kk<2; kk++) {
	  
	  m = 0; SAME = 0; 
	  for(k = 0; k<No_of_CITIES; k++) {
	    if ( k != 8 ) {

	      Realizations = REALIZATIONS[k][n];

	      for(l=0; l < I_Time; l++) x_Data[l] = Ini_Year + l;
	      
	      for(j=0; j < Realizations; j++) { 
		if (kk == 0 ) 
		  Variable[j][0] = Determine_Turning_Point(x_Data,
							   Temporal_Evolution[k][n][i][j],
							   I_Time);
		else
		  Variable[j][0] = Temporal_Evolution[k][n][i][j][I_Time-1];
	      }
	      
	      City_Short_Names_2nd[0][0]  = '\0';
	      pF = strcat(City_Short_Names_2nd[0], City_Short_Names[k]);
	 
	      x_Data[0] = m + 1;
	      Percentile_Calculation_Simple(x_Data, Variable, 1, Realizations,
					    Per, No_of_PERCENTILES,
					    Variable_Per);
	      C->CPG_SCALE_X   = 1;              
	      C->CPG_RANGE_X_0 = 0.5;            
	      C->CPG_RANGE_X_1 = (double)No_of_CITIES - 0.5; 
	      
	      C->CPG_SCALE_Y   =  1;
	      if(kk == 0) {    
		C->CPG_RANGE_Y_0 =  2000.0;
		C->CPG_RANGE_Y_1 =  2033.0;
	      }
	      else {
		C->CPG_RANGE_Y_0 =  0.0;
		C->CPG_RANGE_Y_1 =  1.0; //0.5
	      }
	      
	      y_Position = C->CPG_RANGE_Y_0 - 0.19 * (C->CPG_RANGE_Y_1 - C->CPG_RANGE_Y_0);
	      
	      C->color_Index = 4; // blue
	      
	      if (kk == 0) {  
		CPGPLOT___B_O_X___P_L_O_T_T_I_N_G___S_A_M_E___P_L_O_T ( C, SAME, 1,
									x_Data, Variable_Per,
									No_of_PERCENTILES,
									"City",
									"Turning Point",
									Out_Var_Label, 
									C->CPG_SCALE_X,
									C->CPG_SCALE_Y );
	      }
	      else {  
		CPGPLOT___B_O_X___P_L_O_T_T_I_N_G___S_A_M_E___P_L_O_T ( C, SAME, 1,
									x_Data, Variable_Per,
									No_of_PERCENTILES,
									"City",
									Out_Var_Symbol,
									Out_Var_Label,  
									C->CPG_SCALE_X,
									C->CPG_SCALE_Y );
	      }
	      /* Annotating Short City Names */
	      cpgsch(2.0);
	      x_Position = x_Data[0];
	      cpgptxt (x_Position, y_Position, 0.0, 0.5, City_Short_Names_2nd[0]);
	      cpgsch(1.0);
	      Press_Key(); 
	      m++;
	      SAME = 1; 
	    }
	  }
	}	
      }	
    }
  }

  for(j = 0; j < No_of_PERCENTILES; j++ )
    free(Variable_Per[j]);
  free(Variable_Per);
  
  for(j = 0; j < Realizations; j++ )
    free(Variable[j]);
  free(Variable);
  
  #if defined CPGPLOT_REPRESENTATION
  P_A_R_A_M_E_T_E_R___C_P_G_P_L_O_T___F_R_E_E( C, SUB_OUTPUT_VARIABLES ); 
  #endif

  /* -------------- Saving LaTeX table of model parameters and R_0 ----------- */
  char ** File_Model_Parameters = (char **)calloc( 2, sizeof(char *) );
  File_Model_Parameters[0] = (char *)calloc( 50, sizeof(char) );
  File_Model_Parameters[1] = (char *)calloc( 50, sizeof(char) );
    
  for(n=0; n<No_of_INITIAL_YEARS; n++) {
    
    double * City_R_0_AVE = (double *)calloc(No_of_CITIES, sizeof(double) );
    double * City_R_0_STD = (double *)calloc(No_of_CITIES, sizeof(double) );
    
    double ** City_Par_AVE = (double **)calloc(No_of_CITIES, sizeof(double *) );
    double ** City_Par_STD = (double **)calloc(No_of_CITIES, sizeof(double *) );
    for(p=0; p<No_of_CITIES; p++) {
      City_Par_AVE[p] = (double *)calloc(No_of_PARAMETERS, sizeof(double) );
      City_Par_STD[p] = (double *)calloc(No_of_PARAMETERS, sizeof(double) );
    }
    
    Year[0]='\0'; sprintf( Year, "%d", n+2000 );
    
    File_Model_Parameters[0][0] = '\0';
    pF = strcat(File_Model_Parameters[0], "Parameter_R_0_Values_1st_Table");
    pF = strcat(File_Model_Parameters[0], "_");
    pF = strcat(File_Model_Parameters[0], Year);
    pF = strcat(File_Model_Parameters[0], ".tex");

    File_Model_Parameters[1][0] = '\0';
    pF = strcat(File_Model_Parameters[1], "Parameter_R_0_Values_2nd_Table");
    pF = strcat(File_Model_Parameters[1], "_");
    pF = strcat(File_Model_Parameters[1], Year);
    pF = strcat(File_Model_Parameters[1], ".tex");
    
    for(k=0; k<5; k++) {
      Average_and_Variance_double_Vector(R_0_Value[k][n],
					 REALIZATIONS[k][n], &Ave, &Var);
      City_R_0_AVE[k] = Ave;
      City_R_0_STD[k] = sqrt(Var);   //STD = sqrt(Var)

      for(p=0; p<No_of_PARAMETERS; p++) {  
	Average_and_Variance_double_Vector(Parameter_Value[k][n][p],
					   REALIZATIONS[k][n], &Ave, &Var);
	City_Par_AVE[k][p] = Ave;
	City_Par_STD[k][p] = sqrt(Var);  
      }
    }
    
    write_Param_Table_AVE_STD_per_CITY___LATEX_PORTRAIT( File_Model_Parameters[0],
							 City_Short_Names, 5, // No_of_CITIES,
							 City_R_0_AVE, City_R_0_STD, 
							 City_Par_AVE, City_Par_STD,
							 No_of_PARAMETERS,
							 &Table );
    kk = 0; 
    for(k=5; k<No_of_CITIES; k++) {
      Average_and_Variance_double_Vector(R_0_Value[k][n],
					 REALIZATIONS[k][n], &Ave, &Var);
      City_R_0_AVE[kk] = Ave;
      City_R_0_STD[kk] = sqrt(Var);   //STD = sqrt(Var)

      for(p=0; p<No_of_PARAMETERS; p++) {  
	Average_and_Variance_double_Vector(Parameter_Value[k][n][p],
					   REALIZATIONS[k][n], &Ave, &Var);
	City_Par_AVE[kk][p] = Ave;
	City_Par_STD[kk][p] = sqrt(Var);  
      }

      City_Short_Names_2nd[kk][0]  = '\0';
      pF = strcat(City_Short_Names_2nd[kk], City_Short_Names[k]);
      
      kk++;      
    }  
    write_Param_Table_AVE_STD_per_CITY___LATEX_PORTRAIT( File_Model_Parameters[1],
							 City_Short_Names_2nd, kk, //No_of_CITIES,
							 City_R_0_AVE, City_R_0_STD, 
							 City_Par_AVE, City_Par_STD,
							 No_of_PARAMETERS,
							 &Table );
    for(p=0; p<No_of_CITIES; p++) {
      free(City_Par_AVE[p]);
      free(City_Par_STD[p]);
    }
    free(City_R_0_AVE);
    free(City_R_0_STD);
    
    free(City_Par_AVE);
    free(City_Par_STD);
  }
  
  for(k=0; k<No_of_CITIES; k++) 
    free(City_Short_Names_2nd[k]);
  free(City_Short_Names_2nd); 

  free(File_Model_Parameters[0]);
  free(File_Model_Parameters[1]);
  free(File_Model_Parameters);
  /* ------------ End of Saving LaTeX table of model parameters and R_0 ---------- */
  
  for (k = 0; k < No_of_CITIES; k++) { // only two times
    free( Prevalence[k] );
    free( Prevalence_Inf[k] );
    free( Prevalence_Sup[k] );

    free( SexWorkers[k] );
    free( SexWorkers_Inf[k] );
    free( SexWorkers_Sup[k] );
  }
  free(Prevalence); free(Prevalence_Inf); free(Prevalence_Sup);
  free(SexWorkers); free(SexWorkers_Inf); free(SexWorkers_Sup);

  free(xn_Data[0]); free(yn_Data[0]);
  free(xn_Data[1]); free(yn_Data[1]);
  free(xn_Data);    free(yn_Data);

  free(x_Data); free(y_Data); free(Out_Var_Symbol); free(Out_Var_Label);

  I_Time = I_Time_Total;
#endif
  /* BEGIN : Freeing All Memmory * * * * * * * * * * * * * * */

  for(k=0; k<No_of_CITIES; k++) free(REALIZATIONS[k]);
  free(REALIZATIONS);

  for(k = 0; k<No_of_CITIES; k++) {
    for(n = 0; n<No_of_INITIAL_YEARS; n++) {
      for(i = 0; i < SUB_OUTPUT_VARIABLES; i++) {
	for(j = 0; j < No_of_SETS_MAX; j++) free( Temporal_Evolution[k][n][i][j] );
	free(Temporal_Evolution[k][n][i]);
      }
      for(i = 0; i < No_of_OBSERVED_VARIABLES_MAX; i++)
	free(Observed_Population_Data[k][n][i]);

      free(Observed_Population_Data[k][n]);
      free(Temporal_Evolution[k][n]);
      free(TEMPORAL_EVOLUTION_FILE[k][n]);
    }
    for(i = 0; i<SUB_OUTPUT_VARIABLES; i++) free(TIME_EVOLUTION_FILE_NAME[k][i]);
    free(TIME_EVOLUTION_FILE_NAME[k]);

    free(Temporal_Evolution[k]);
    free(Observed_Population_Data[k]);
    free(TEMPORAL_EVOLUTION_FILE[k] );
  }
  free(Temporal_Evolution);
  free(Observed_Population_Data);
  free(TIME_EVOLUTION_FILE_NAME);
  free(TEMPORAL_EVOLUTION_FILE);

#if defined CPGPLOT_REPRESENTATION
  P_A_R_A_M_E_T_E_R___C_P_G_P_L_O_T___F_R_E_E( Table.CPG, SUB_OUTPUT_VARIABLES );
  cpgclos();
#endif

  #include <include.Parameter_Space.default.free.c>
  Parameter_Space_Free(Space, No_of_PARAMETERS); free( Space );

  if( No_of_IC > 0 ) {
  #include <include.Initial_Conditions.default.free.c>
    Parameter_Space_Free(Initial_Condition_Space, No_of_IC);
  }
  free(Initial_Condition_Space);

  if( No_of_ERROR_PARAMETERS > 0 ) {
  #include <include.Error_Control.default.free.c>
    Parameter_Space_Free(Error_Space, No_of_IC);
  }
  free(Error_Space);

  #include <include.Output_Variables.default.free.c>

  #include <include.Time_Dependence_Control.default.free.c>

  for (i=0; i<No_of_OBSERVED_VARIABLES_MAX; i++) free(Empirical_Data_Matrix[i]);
  free(Empirical_Data_Matrix);
  free(Name_of_Rows);

  free(Year);

  for(i=0; i<No_of_SETS_MAX; i++) free(Demo_Data[i]);
  free(Demo_Data);

  for(k = 0; k<No_of_CITIES; k++) {
    free(TIME_PARAMETERS_FILE[k]);
    free(OBSERVED_DATA_FILE[k]);
    free(PARAMETER_SET_FILE[k]);
  }
  free(TIME_PARAMETERS_FILE);
  free(OBSERVED_DATA_FILE);
  free(PARAMETER_SET_FILE);

  free(Initial_Guess);
  
  for(k = 0; k < No_of_CITIES; k++) {
    for(n = 0; n < No_of_INITIAL_YEARS; n++ ) 
      free(R_0_Value[k][n]);
    free(R_0_Value[k]);
  }
  free(R_0_Value);
  
  for(k = 0; k < No_of_CITIES; k++) {
    for(n = 0; n < No_of_INITIAL_YEARS; n++ ) {
      for(p = 0; p<No_of_PARAMETERS; p++)
	free(Parameter_Value[k][n][p]);
      free(Parameter_Value[k][n]);
    }
    free(Parameter_Value[k]);
  }
  free(Parameter_Value);
  
  P_A_R_A_M_E_T_E_R___T_A_B_L_E___F_R_E_E( &Table );
  /*  END : Freeing  All Memmory * * * * * * * * * * * * * * */

  printf("\nEnd of progam\n");
  return (0);
}

void Reading_Sexual_Workers_Numbers_and_Prevalences(double ** Prevalence,
						    double ** Prevalence_Inf,
						    double ** Prevalence_Sup,
						    double ** SexWorkers,
						    double ** SexWorkers_Inf,
						    double ** SexWorkers_Sup)
{
    int k;
    int No_of_CITIES;
    int No_of_COLUMNS;

    No_of_CITIES  = 12;
    No_of_COLUMNS = 10;

    double ** Data_Matrix = (double **)calloc(No_of_CITIES, sizeof(double *) );
    double * Time = (double *)calloc(No_of_COLUMNS, sizeof(double) );
    char ** CITY_NAMES = (char **)calloc( No_of_CITIES, sizeof(char *) );
    for( k = 0; k<No_of_CITIES; k++) {
      CITY_NAMES[k]  = (char *)calloc( 100, sizeof(char) );
      Data_Matrix[k] = (double *)calloc(No_of_COLUMNS, sizeof(double) );
    }

    Reading_Standard_Data_Matrix_from_File( "Sexual-Workers_2014-2017_and_Prevalence-2012-2016.dat",
					    Data_Matrix,
					    &No_of_CITIES, No_of_COLUMNS,
					    1, CITY_NAMES,
					    0, Time );
    assert(No_of_CITIES == 11);

    for (k = 0; k<No_of_CITIES; k++ ) {
      SexWorkers_Inf[k][0] = Data_Matrix[k][0];
      SexWorkers_Sup[k][0] = Data_Matrix[k][1];
      SexWorkers[k][0]     = (Data_Matrix[k][0] + Data_Matrix[k][1])/2.0;

      SexWorkers_Inf[k][1] = Data_Matrix[k][2];
      SexWorkers_Sup[k][1] = Data_Matrix[k][3];
      SexWorkers[k][1]     = (Data_Matrix[k][2] + Data_Matrix[k][3])/2.0;

      printf("%s: SexWorkers(2014) = %g\t [ SexWorkers_Inf(2014)=%g, SexWorkers_Sup(2014)=%g ]\n",
	     CITY_NAMES[k], SexWorkers[k][0], SexWorkers_Inf[k][0], SexWorkers_Sup[k][0]);
      printf("%s: SexWorkers(2017) = %g\t [ SexWorkers_Inf(2017)=%g, SexWorkers_Sup(2017)=%g ]\n",
	     CITY_NAMES[k], SexWorkers[k][1], SexWorkers_Inf[k][1], SexWorkers_Sup[k][1]);
      printf("\n");

      Prevalence_Inf[k][0] = 0.01 * Data_Matrix[k][5];
      Prevalence_Sup[k][0] = 0.01 * Data_Matrix[k][6];
      Prevalence[k][0]     = 0.01 * Data_Matrix[k][4];

      Prevalence_Inf[k][1] = 0.01 * Data_Matrix[k][8];
      Prevalence_Sup[k][1] = 0.01 * Data_Matrix[k][9];
      Prevalence[k][1]     = 0.01 * Data_Matrix[k][7];

      printf("%s: Prevalence(2012) = %g\t [ Prevalence_Inf(2012)=%g, Prevalence_Sup(2012)=%g ]\n",
	     CITY_NAMES[k], Prevalence[k][0], Prevalence_Inf[k][0], Prevalence_Sup[k][0]);
      printf("%s: Prevalence(2016) = %g\t [ Prevalence_Inf(2016)=%g, Prevalence_Sup(2016)=%g ]\n",
	     CITY_NAMES[k], Prevalence[k][1], Prevalence_Inf[k][1], Prevalence_Sup[k][1]);
      printf("\n");
    }

    free(Time);
    for( k = 0; k<No_of_CITIES; k++) free( CITY_NAMES[k] );
    free(CITY_NAMES);
    for( k = 0; k<No_of_CITIES; k++) free( Data_Matrix[k] );
    free(Data_Matrix);
}

double Determine_Turning_Point(double * x_Time, double * y_Time, int N)
{
  double x_Turning_Point;
  
  int i, i_Index; 
  
  double * Delta_Value = (double *)calloc( N, sizeof(double) );

  for(i=0; i<N-1; i++)
    Delta_Value[i] = (y_Time[i+1] - y_Time[i])/(x_Time[i+1] - x_Time[i]);

  double Max_Delta = vector_MAX_Index_double(Delta_Value, 0, N-1, &i_Index); 
  x_Turning_Point  = x_Time[i_Index];

  free(Delta_Value);

  return(x_Turning_Point); 
}
