/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                            David Alonso, 2018 (c)                         */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#include <Include/MODEL.h>

#include "global.h"

gsl_rng * r; /* Global generator defined in main.c */

/* This code calculates ODE model temporal evolution of the whole disease
   model. Here, the goal is to estimate disease parameters from data, once
   Sigma (and Alpha) parameters have been estimated for each city. This is 
   done in directory:

	./TEMPORAL_EVOLUTION_DEMOGRAPHY_PARAMETERS

   These parameter configurations were then saved and will be now read from 
   files of the type:

   Demo_Parameter_Set_[Name-of-the-City]_[Hypothesis]_Ordered.dat, i.e.,

   Demo_Parameter_Set_Antananarivo_Sigmoidal_Ordered.dat 
	
   Parameters F_X, F_Y, \delta_X and \delta_Y have been already estimated from demographic
   data and play the role of extern parameters driving the system. See directory:

   	./TEMPORAL_EVOLUTION_r_FACTOR_ESTIMATE

   F_X and F_Y are recruitment rates into adutl sexually active life, and
   \delta_X and \delta_Y are adult mortality rates. They change every year.
   They are given in 'Time_Dependent_Parameters_Corrected_[CITY_NAME].dat'
   files.

   Compilation:

   . ~$ make X_MODEL=X2W2SILD Y_MODEL=YSILD

   We can make different assumptions:

   A. Parameters are searched under the hypothesis of constant ratio of female
   sexual workers to total female population:

   B. Parameters are searched under the hypothesis of ratio of female
   sexual workers to total female population following a sigmoidal curve
   with a break point in 2011.0 and smoothness parameters 0.1.

   C. Parameters are searched under the same hypothesis as B, but all
   parameter ranges are chosen to be maximally constrained in agreement with
   the information we have about the behavior of the disease.

   Hypothesis A needs and generates files ending in *.dat, while hypotheses
   B and C require files ending in *Sigmoidal.dat. This should be changed by hand
   in code. So, in order to generate results under the two constrasting hyphotheses
   (A vs B/C) the program should be run twice by changing (and recompiling) the code
   accordingly. This is achieved just changing:

   L171: SIGMOIDAL == 1

   into

   L171: SIGMOIDAL = 0     (line L171 of code is only approx.)

   A. Parameters are searched under the hypothesis of constant ratio of female
   sexual workers to total female population:

   Exectution: (Time-dependent parameters: -t4 1)

   . ~$ ./X2W2SILD-YSILD -y0 1                // TYPE of MODEL
   / -sP 12 -sN 2500   -sT 1.0E-08            // Parameter Space of Model Parameters:  [-sP : Dimension, Number of Model Parameters to be optimized]
   / -I0 21 -H21 1.0   -m0 0.0  -M0 2.0     -A0 0.01      // Parameter: r_R
   / -I1 0  -H0 100.0  -m1 0.0  -M1 200.0   -A1 0.1       // Parameter: Beta_Y
   / -I2 8  -H8  50.0  -m2 0.0  -M2 100.0   -A2 0.1       // Parameter: Beta_X
   / -I3 12 -H12   9   -m3 1.0  -M3 20.0    -A3 0.01      // Parameter: Eta
   / -I4 7  -H7  9.0   -m4 1.0  -M4 99.0    -A4 0.01      // Parameter: mDelta
   / -I5 16 -H16 0.2   -m5 0.0  -M5 0.99    -A5 0.01      // Parameter: f_W
   / -I6 17 -H17 0.5   -m6 0.0  -M6 0.99    -A6 0.01      // Parameter: f_0
   / -I7 1  -H1 0.03   -m7 0.0  -M7 0.10    -A7 0.001     // Parameter: p_XY
   / -I8 9  -H9 0.01   -m8 0.0  -M8 0.10    -A8 0.001     // Parameter: p_YX
   / -I9 5  -H5 1.5    -m9 0.0  -M9 10.0    -A9 0.1       // Parameter: Gamma
   / -I10 6 -H6 0.2    -m10 0.0 -M10 1.0    -A10 0.01     // Parameter: Mu
   / -I11 15 -H15 10.0 -m11 1.0 -M11 100.0  -A11 0.1      // Parameter: Xhi

   // City-specific parameters (Antananarivo):
   / -H10  0.0325332                          // Parameter: Sigma_0
   / -H11  0.704745                           // Parameter: Sigma_0_r
   / -H18  0.0265231                          // Parameter: Sigma_1
   / -H19  0.550609                           // Parameter: Sigma_1_r
   / -H20  0.056651                           // Parameter: Alpha

   / -en 0 -eP0 17 -eV 0.0103805              // Parameter Space of Error Model        [-en Number of Error Model-related parameters to be optimized: -eP0 17 [Error_Parameter_0]
   / -n 3  -v0 6 -v1 4 -v2 14                 // Output/Observed Varables:             [-n  Number of Observed Variables]
   / -iP 2                                    // Parameter Space of Initial Conditions [-iP Number of Initial Condition Variables to be optimized]
   / -i0  9 -u0 0.0 -U0 100.0
   /- i1 17 -u1 0.0 -U1 100.0
   / -G0 1  -G1 3 -tn 17 -t0 2000.0 -t1 2016.0 -t4 1 -xn 0 -xR 1  // Arguments Controling Numerical Integration
   / -DP 4  -DC 0 -D0 0 -D1 4 -D2 0 -P0 13 -a0 0  -P1 2 -a1 0  -P2 3 -a2 0  -P3 4 -a3 0 // Arguments controling type of time dependence of model parameters.
   / -Fn 1 -F0 ../../DATA_FILES/2019.05.31_Demographic_Parameters_per_City_NLL.dat

   . ~$ ./X2W2SILD-YSILD -y0 1 -sT 1.0E-04 -sN 100 -sP 12  -I0 21 -H21 1.0  -m0 0.5 -M0 1.5 -A0 0.01   -I1 0 -H0 100.0 -m1 0.0 -M1 200.0 -A1 0.1  -I2 8 -H8 50.0 -m2 0.0 -M2 100.0 -A2 0.1   -I3 12 -H12 9.0  -m3 1.0 -M3 20.0  -A3 0.01   -I4 7 -H7 9.0 -m4 1.0 -M4 99.0 -A4 0.01   -I5 16 -H16 0.2 -m5 0.0 -M5 0.99 -A5 0.01 -I6 17 -H17 0.6 -m6 0.0 -M6 0.99 -A6 0.01 -I7 1 -H1 0.03 -m7 0.0 -M7 0.1 -A7 0.001  -I8 9 -H9 0.01 -m8 0.0 -M8 0.1 -A8 0.001   -I9 5 -H5 1.5 -m9 0.0 -M9 10.0 -A9 0.1   -I10 6 -H6 0.2 -m10 0.0 -M10 1.0 -A10 0.01   -I11 15 -H15 10.0 -m11 1.0 -M11 100.0 -A11 0.1  -n 3 -v0 6 -v1 4 -v2 14 -en 0 -eP0 17 -eV 0.01 -iP 0 -i0 9 -u0 0.0 -U0 10000.0 -i1 17 -u1 0.0 -U1 10000.0 -i2 1 -u2 0.0 -U2 10000 -i3 2 -u3 0.0 -U3 10000 -i4 3 -u4 0.0 -U4 10000 -G0 1 -G1 3 -tn 17 -t0 2000.0 -t1 2016.0 -t4 1 -xn 0 -xR 1 -DP 4  -DC 0 -D0 0 -D1 4 -D2 0 -P0 13 -a0 0  -P1 2 -a1 0  -P2 3 -a2 0  -P3 4 -a3 0 -tE 2.0 -tR 15

   B. Parameters are searched under the hypothesis of ratio of female
   sexual workers to total female population following a sigmoidal curve
   with a break point in 2011.0 and smoothness parameters 0.1. This estimates
   are generated in ./OBSERVED_DATA_FILES_PREPARATION and resulting files
   are *_Sigmoidal.dat files.

   In this case, the set of demographic parameters include three new parameters controling
   a break point in parameters Sigma_0 and Sigma_1. These three parameters are A_0, L_0 and
   T_0, which are also object to search. In addition, a new parameters D_Sigma has a sigmoidal
   time dependence (parameters 22), which imposes a time dependence in Sigma_0 and Sigma_1
   through:

   Sigma_0(t) = Sigma_0 + D_Sigma(t)
   Sigma_1(t) = Simga_1 + D_Sigma(t)

   Exectution: (Time-dependent parameters: -t4 1)

   . ~$ ./X2W2SILD-YSILD -y0 1                // TYPE of MODEL
   / -sP 12 -sN 2500   -sT 1.0E-08            // Parameter Space of Model Parameters:  [-sP : Dimension, Number of Model Parameters to be optimized]
   / -I0 21 -H21 1.0   -m0 0.0  -M0 2.0     -A0 0.01      // Parameter: r_R
   / -I1 0  -H0 100.0  -m1 0.0  -M1 200.0   -A1 0.1       // Parameter: Beta_Y
   / -I2 8  -H8  50.0  -m2 0.0  -M2 100.0   -A2 0.1       // Parameter: Beta_X
   / -I3 12 -H12   9   -m3 1.0  -M3 20.0    -A3 0.01      // Parameter: Eta
   / -I4 7  -H7  9.0   -m4 1.0  -M4 99.0    -A4 0.01      // Parameter: mDelta
   / -I5 16 -H16 0.2   -m5 0.0  -M5 0.99    -A5 0.01      // Parameter: f_W
   / -I6 17 -H17 0.5   -m6 0.0  -M6 0.99    -A6 0.01      // Parameter: f_0
   / -I7 1  -H1 0.03   -m7 0.0  -M7 0.10    -A7 0.001     // Parameter: p_XY
   / -I8 9  -H9 0.01   -m8 0.0  -M8 0.10    -A8 0.001     // Parameter: p_YX
   / -I9 5  -H5 1.5    -m9 0.0  -M9 10.0    -A9 0.1       // Parameter: Gamma
   / -I10 6 -H6 0.2    -m10 0.0 -M10 1.0    -A10 0.01     // Parameter: Mu
   / -I11 15 -H15 10.0 -m11 1.0 -M11 100.0  -A11 0.1      // Parameter: Xhi

   // City-specific demographic parameters (Antananarivo):
   / -H10  0.0325332                          // Parameter: Sigma_0
   / -H11  0.704745                           // Parameter: Sigma_0_r
   / -H18  0.0265231                          // Parameter: Sigma_1
   / -H19  0.550609                           // Parameter: Sigma_1_r
   / -H20  0.056651                           // Parameter: Alpha
   / -H23  0.48356                            // Parameter: A_0  Magnitud of the jump
   / -H24  3.02678                            // Parameter: L_0  Smoothness of the jump
   / -H25  2013                               // Parameter: T_0  Time of the jump

   / -en 0 -eP0 17 -eV 0.0103805              // Parameter Space of Error Model        [-en Number of Error Model-related parameters to be optimized: -eP0 17 [Error_Parameter_0]
   / -n 3  -v0 6 -v1 4 -v2 14                 // Output/Observed Varables:             [-n  Number of Observed Variables]
   / -iP 2                                    // Parameter Space of Initial Conditions [-iP Number of Initial Condition Variables to be optimized]
   / -i0  9 -u0 0.0 -U0 100.0
   /- i1 17 -u1 0.0 -U1 100.0
   / -G0 1  -G1 3 -tn 17 -t0 2000.0 -t1 2016.0 -t4 1 -xn 0 -xR 1  // Arguments Controling Numerical Integration
   / -DP 5  -DC 0 -D0 0 -D1 4 -D2 1 -P0 13 -a0 0  -P1 2 -a1 0  -P2 3 -a2 0  -P3 4 -a3 0 -P4 22 -a4 0 // Arguments controling type of time dependence of model parameters.

   . ~$ ./X2W2SILD-YSILD -y0 1 -sT 1.0E-04 -sN 300 -sP 12  -I0 21 -H21 1.0  -m0 0.5 -M0 1.5 -A0 0.01   -I1 0 -H0 100.0 -m1 0.0 -M1 200.0 -A1 0.1  -I2 8 -H8 50.0 -m2 0.0 -M2 100.0 -A2 0.1   -I3 12 -H12 9.0  -m3 1.0 -M3 20.0  -A3 0.01   -I4 7 -H7 9.0 -m4 1.0 -M4 99.0 -A4 0.01   -I5 16 -H16 0.2 -m5 0.0 -M5 0.99 -A5 0.01 -I6 17 -H17 0.6 -m6 0.0 -M6 0.99 -A6 0.01 -I7 1 -H1 0.03 -m7 0.0 -M7 0.1 -A7 0.001  -I8 9 -H9 0.01 -m8 0.0 -M8 0.1 -A8 0.001   -I9 5 -H5 1.5 -m9 0.0 -M9 10.0 -A9 0.1   -I10 6 -H6 0.2 -m10 0.0 -M10 1.0 -A10 0.01   -I11 15 -H15 10.0 -m11 1.0 -M11 100.0 -A11 0.1  -n 3 -v0 6 -v1 4 -v2 14 -en 0 -eP0 17 -eV 0.01 -iP 0 -i0 9 -u0 0.0 -U0 10000.0 -i1 17 -u1 0.0 -U1 10000.0 -i2 1 -u2 0.0 -U2 10000 -i3 2 -u3 0.0 -U3 10000 -i4 3 -u4 0.0 -U4 10000 -G0 1 -G1 3 -tn 17 -t0 2000.0 -t1 2016.0 -t4 1 -xn 0 -xR 1 -DP 5  -DC 0 -D0 0 -D1 4 -D2 1 -P0 13 -a0 0  -P1 2 -a1 0  -P2 3 -a2 0  -P3 4 -a3 0 -P4 22 -a4 0 -tE 2.0 -tR 15

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
   / -I7 1  -H1 0.001  -m7 0.0  -M7 0.005   -A7 0.0001     // Parameter: p_XY
   / -I8 9  -H9 0.0005 -m8 0.0  -M8 0.001   -A8 0.0001     // Parameter: p_YX
   / -I9 5  -H5 1.5    -m9 0.5  -M9 4.0     -A9 0.01       // Parameter: Gamma
   / -I10 6 -H6 0.1    -m10 0.05 -M10 0.20  -A10 0.01     // Parameter: Mu
   / -I11 15 -H15 10.0 -m11 1.0 -M11 50.0   -A11 0.1      // Parameter: Xhi

   // City-specific demographic parameters (Antananarivo):
   / -H10  0.0325332                          // Parameter: Sigma_0
   / -H11  0.704745                           // Parameter: Sigma_0_r
   / -H18  0.0265231                          // Parameter: Sigma_1
   / -H19  0.550609                           // Parameter: Sigma_1_r
   / -H20  0.056651                           // Parameter: Alpha
   / -H23  0.48356                            // Parameter: A_0  Magnitud of the jump
   / -H24  3.02678                            // Parameter: L_0  Smoothness of the jump
   / -H25  2013                               // Parameter: T_0  Time of the jump

   / -en 0 -eP0 17 -eV 0.0103805              // Parameter Space of Error Model        [-en Number of Error Model-related parameters to be optimized: -eP0 17 [Error_Parameter_0]
   / -n 3  -v0 6 -v1 4 -v2 14                 // Output/Observed Varables:             [-n  Number of Observed Variables]
   / -iP 2                                    // Parameter Space of Initial Conditions [-iP Number of Initial Condition Variables to be optimized]
   / -i0  9 -u0 0.0 -U0 100.0
   /- i1 17 -u1 0.0 -U1 100.0
   / -G0 1  -G1 3 -tn 17 -t0 2000.0 -t1 2016.0 -t4 1 -xn 0 -xR 1  // Arguments Controling Numerical Integration
   / -DP 5  -DC 0 -D0 0 -D1 4 -D2 1 -P0 13 -a0 0  -P1 2 -a1 0  -P2 3 -a2 0  -P3 4 -a3 0 -P4 22 -a4 0 // Arguments controling type of time dependence of model parameters.

   . ~$ ./X2W2SILD-YSILD -y0 1 -sT 1.0E-04 -sN 300 -sP 12  -I0 21 -H21 1.0 -m0 0.8  -M0 1.2 -A0 0.01 -I1 0 -H0 100.0  -m1 96.0 -M1 120.0 -A1 0.1  -I2 8 -H8 100.0  -m2 96.0 -M2 120.0  -A2 0.1  -I3 12 -H12   9  -m3 1.0 -M3 19.0  -A3 0.01  -I4 7  -H7  9.0  -m4 0.0 -M4 99.0 -A4 0.01  -I5 16 -H16 0.2   -m5 0.0  -M5 0.99 -A5 0.01  -I6 17 -H17 0.5 -m6 0.0 -M6 0.99 -A6 0.01   -I7 1 -H1 0.001  -m7 0.0 -M7 0.005 -A7 0.0001   -I8 9 -H9 0.0005 -m8 0.0 -M8 0.001 -A8 0.0001   -I9 5 -H5 1.5  -m9 0.5 -M9 4.0 -A9 0.01     -I10 6 -H6 0.1   -m10 0.05 -M10 0.20 -A10 0.01   -I11 15 -H15 10.0 -m11 1.0 -M11 50.0 -A11 0.1   -n 3 -v0 6 -v1 4 -v2 14 -en 0 -eP0 17 -eV 0.2 -iP 0 -i0 9 -u0 0.0 -U0 10000.0 -i1 17 -u1 0.0 -U1 10000.0 -i2 1 -u2 0.0 -U2 10000 -i3 2 -u3 0.0 -U3 10000 -i4 3 -u4 0.0 -U4 10000 -G0 1 -G1 3 -tn 17 -t0 2000.0 -t1 2016.0 -t4 1 -xn 0 -xR 1 -DP 5  -DC 0 -D0 0 -D1 4 -D2 1 -P0 13 -a0 0  -P1 2 -a1 0  -P2 3 -a2 0  -P3 4 -a3 0 -P4 22 -a4 0 -tE 2.0 -tR 15

   Command to order resuling files from the search:

   ~$ for f in Full_Parameter_Set_*_20??_Sigmoidal.dat; do awk '{ if ($22 < 1.0E+20) { print } }' $f | sort -n -k 22 > ${f/%.dat/_Ordered.dat}; done

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

   IMPORTANT CONSISTENCY TEST: If r_F = 1.0 and mDelta = 0.0 (-H21 1.0 -H7 0.0), then the temporal evolution of total sexual workers should be identical to the one obtained with the simplified demographic model X2W2-Y_2:

   . ~$ ./X2W2SILD-YSILD -y0 1                // TYPE of MODEL
   / -sP 10 -sN 300   -sT 1.0E-08            // Parameter Space of Model Parameters:  [-sP : Dimension, Number of Model Parameters to be optimized]

   / -I0 0  -H0 100.0  -m0 0.0  -M0 200.0   -A0 0.1       // Parameter: Beta_Y
   / -I1 15 -H15 10.0  -m1 1.0  -M1 100.0   -A1 0.1      // Parameter: Xhi
   / -I2 8  -H8  50.0  -m2 0.0  -M2 100.0   -A2 0.1       // Parameter: Beta_X
   / -I3 12 -H12   9   -m3 1.0  -M3 20.0    -A3 0.01      // Parameter: Eta
   / -I4 16 -H16 0.2   -m4 0.0  -M4 0.99    -A4 0.01      // Parameter: f_W
   / -I5 17 -H17 0.5   -m5 0.0  -M5 0.99    -A5 0.01      // Parameter: f_0
   / -I6 1  -H1 0.03   -m6 0.0  -M6 0.10    -A6 0.001     // Parameter: p_XY
   / -I7 9  -H9 0.01   -m7 0.0  -M7 0.10    -A7 0.001     // Parameter: p_YX
   / -I8 5  -H5 1.5    -m8 0.0  -M8 10.0    -A8 0.1       // Parameter: Gamma
   / -I9 6  -H6 0.2    -m9 0.0  -M9 1.0     -A9 0.01     // Parameter: Mu

   / -H21 1.0                                             // Parameter: r_R
   / -H7  0.0                                             // Parameter: mDelta

   // City-specific demographic parameters (Antananarivo):
   / -H10  0.0325332                          // Parameter: Sigma_0
   / -H11  0.704745                           // Parameter: Sigma_0_r
   / -H18  0.0265231                          // Parameter: Sigma_1
   / -H19  0.550609                           // Parameter: Sigma_1_r
   / -H20  0.056651                           // Parameter: Alpha
   / -H23  0.48356                            // Parameter: A_0  Magnitud of the jump
   / -H24  3.02678                            // Parameter: L_0  Smoothness of the jump
   / -H25  2013                               // Parameter: T_0  Time of the jump

   / -en 0 -eP0 17 -eV 0.0103805              // Parameter Space of Error Model        [-en Number of Error Model-related parameters to be optimized: -eP0 17 [Error_Parameter_0]
   / -n 3  -v0 6 -v1 4 -v2 14                 // Output/Observed Varables:             [-n  Number of Observed Variables]
   / -iP 2                                    // Parameter Space of Initial Conditions [-iP Number of Initial Condition Variables to be optimized]
   / -i0  9 -u0 0.0 -U0 100.0
   /- i1 17 -u1 0.0 -U1 100.0
   / -G0 1  -G1 3 -tn 17 -t0 2000.0 -t1 2016.0 -t4 1 -xn 0 -xR 1  // Arguments Controling Numerical Integration
   / -DP 5  -DC 0 -D0 0 -D1 4 -D2 1 -P0 13 -a0 0  -P1 2 -a1 0  -P2 3 -a2 0  -P3 4 -a3 0 -P4 22 -a4 0 // Arguments controling type of time dependence of model parameters.

   . ~$ ./X2W2SILD-YSILD -y0 1 -sT 1.0E-04 -sN 300 -sP 10  -H21 1.0 -H7 0.0 -I0 0 -H0 100.0 -m0 0.0 -M0 200.0 -A0 0.1  -I1 15 -H15 10.0 -m1 1.0 -M1 100.0 -A1 0.1   -I2 8 -H8 50.0 -m2 0.0 -M2 100.0 -A2 0.1   -I3 12 -H12 9.0  -m3 1.0 -M3 20.0  -A3 0.01   -I4 16 -H16 0.2   -m4 0.0  -M4 0.99    -A4 0.01   -I5 17 -H17 0.5   -m5 0.0  -M5 0.99    -A5 0.01  -I6 1  -H1 0.03   -m6 0.0  -M6 0.10    -A6 0.001  -I7 9  -H9 0.01   -m7 0.0  -M7 0.10    -A7 0.001  -I8 5  -H5 1.5    -m8 0.0  -M8 10.0    -A8 0.1   -I9 6  -H6 0.2    -m9 0.0  -M9 1.0     -A9 0.01   -n 3 -v0 6 -v1 4 -v2 14 -en 0 -eP0 17 -eV 0.01 -iP 0 -i0 9 -u0 0.0 -U0 10000.0 -i1 17 -u1 0.0 -U1 10000.0 -i2 1 -u2 0.0 -U2 10000 -i3 2 -u3 0.0 -U3 10000 -i4 3 -u4 0.0 -U4 10000 -G0 1 -G1 3 -tn 17 -t0 2000.0 -t1 2016.0 -t4 1 -xn 0 -xR 1 -DP 5  -DC 0 -D0 0 -D1 4 -D2 1 -P0 13 -a0 0  -P1 2 -a1 0  -P2 3 -a2 0  -P3 4 -a3 0 -P4 22 -a4 0 -tE 2.0 -tR 15

*/

int main(int argc, char **argv)
{
  int i, j, k, n, s, z, key;
  double value, Min_Value, Data_Value, Theory_Value;
  double Likelihood_Value, Average_Likelihood_Value, Standard_Error_Value, Ave, Var;
  Parameter_Table Table;
  Time_Control Time;
  Time_Dependence_Control Time_Dependence;
  P_ARG = &Table;
  int SIGMOIDAL;
  int No_of_PARAMETER_SETS;
  int * Demographic_Parameters_Index;
  int  No_of_DEMOGRAPHIC_PARAMETERS;
  
  SIGMOIDAL = 1;

  if( SIGMOIDAL == 1 ) {
    No_of_DEMOGRAPHIC_PARAMETERS = 8;
    Demographic_Parameters_Index = (int *)calloc(No_of_DEMOGRAPHIC_PARAMETERS, sizeof(int) );
    Demographic_Parameters_Index[0] = 10;
    Demographic_Parameters_Index[1] = 11;
    Demographic_Parameters_Index[2] = 18;
    Demographic_Parameters_Index[3] = 19;
    Demographic_Parameters_Index[4] = 20;
    Demographic_Parameters_Index[5] = 23;
    Demographic_Parameters_Index[6] = 24;
    Demographic_Parameters_Index[7] = 25;
  }
  else {
    No_of_DEMOGRAPHIC_PARAMETERS = 5;
    Demographic_Parameters_Index = (int *)calloc(No_of_DEMOGRAPHIC_PARAMETERS, sizeof(int) );
    Demographic_Parameters_Index[0] = 10;
    Demographic_Parameters_Index[1] = 11;
    Demographic_Parameters_Index[2] = 18;
    Demographic_Parameters_Index[3] = 19;
    Demographic_Parameters_Index[4] = 20;
  }
  
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

  char   ** Name_of_Rows          = (char **)calloc(SUB_OUTPUT_VARIABLES, sizeof(char *) );
  double ** Empirical_Data_Matrix = (double **)calloc( SUB_OUTPUT_VARIABLES, sizeof(double *) );
  for (i=0; i<SUB_OUTPUT_VARIABLES; i++) {
    key = Table.OUTPUT_VARIABLE_INDEX[i];
    Name_of_Rows[i]         = Table.Output_Variable_Symbol[key];
    Empirical_Data_Matrix[i] = (double *)calloc( I_Time, sizeof(double) );
  }

  int No_of_CITIES = 11;
  const char * City_Names[] = { "Antananarivo",  "Antsiranana",
				"Mahajanga",     "Toamasina",
				"Fianarantsoa",  "Toliary",
				"Taolagnaro",    "Moramanga",
				"Antsirabe",     "Morondava",
				"Nosy_Be" };

  /* B E G I N : Time Dependent Parameters, Observed Data, and Demo Parameters File Names */
  char * pF;
  char ** TIME_PARAMETERS_FILE = (char **)calloc(No_of_CITIES, sizeof(char *) ); /* Input files  */
  char ** OBSERVED_DATA_FILE   = (char **)calloc(No_of_CITIES, sizeof(char *) ); /* Input files  */
  char ** DEMO_PARAMETER_SET   = (char **)calloc(No_of_CITIES, sizeof(char *) ); /* Input files  */
  char ** PARAMETER_SET_FILE   = (char **)calloc(No_of_CITIES, sizeof(char *) ); /* Output files */
  char ** LIKELIHOOD_VALUES    = (char **)calloc(No_of_CITIES, sizeof(char *) ); /* Output files */

  for(k = 0; k<No_of_CITIES; k++) {
    TIME_PARAMETERS_FILE[k]   = (char *)calloc( 1000, sizeof(char) );
    OBSERVED_DATA_FILE[k]     = (char *)calloc( 1000, sizeof(char) );
    DEMO_PARAMETER_SET[k]     = (char *)calloc( 1000, sizeof(char) );
    PARAMETER_SET_FILE[k]     = (char *)calloc( 1000, sizeof(char) );
    LIKELIHOOD_VALUES[k]      = (char *)calloc( 1000, sizeof(char) );
  }
  for(k = 0; k<No_of_CITIES; k++) {
    DEMO_PARAMETER_SET[k][0] = '\0';
    pF = strcat(DEMO_PARAMETER_SET[k], "Demo_Parameter_Set_");
    pF = strcat(DEMO_PARAMETER_SET[k], City_Names[k]);
    if( SIGMOIDAL == 1 ) pF = strcat(DEMO_PARAMETER_SET[k], "_Sigmoidal_Ordered.dat");
    else                 pF = strcat(DEMO_PARAMETER_SET[k], "_Ordered.dat");
  }
  /*     E N D : ------------------------------------------------------------------------ */

  FILE ** DEMO       = (FILE **)calloc( No_of_CITIES, sizeof(FILE *) );
  FILE ** LIKELIHOOD = (FILE **)calloc( No_of_CITIES, sizeof(FILE *) );

  FILE * f = fopen("Introduction_Year_Likelihood.dat", "w");

  int No_of_SETS_MAX  = 5000;
  double ** Demo_Data = (double **)calloc(No_of_SETS_MAX, sizeof(double *));
  for(i=0; i<No_of_SETS_MAX; i++)
    Demo_Data[i] = (double *)calloc(No_of_DEMOGRAPHIC_PARAMETERS, sizeof(double));

  char * Year = (char *)calloc(30, sizeof(char));
  int No_of_INITIAL_YEARS = 15;

  double *** Likelihood = (double ***)calloc(No_of_CITIES, sizeof(double **) );
  for (i=0; i<No_of_CITIES; i++) {
    Likelihood[i] = (double **)calloc(No_of_INITIAL_YEARS, sizeof(double *) );
    for(j=0; j<No_of_INITIAL_YEARS; j++)
      Likelihood[i][j] = (double *)calloc(No_of_SETS_MAX * Realizations, sizeof(double) );
  }

  int I_Time_Total = I_Time;
  for(k = 0; k<No_of_CITIES; k++)
    // k=8 is a city with no infection ("Antsirabe")
    if ( k != 8 ) {

    Reading_Demographic_Parameters_from_File(DEMO_PARAMETER_SET[k], Demo_Data,
					     &No_of_PARAMETER_SETS,
					     No_of_DEMOGRAPHIC_PARAMETERS);

    assert( No_of_PARAMETER_SETS < No_of_SETS_MAX );

    printf("Set of Demographic Parameters (City: %s):\n", City_Names[k]);
    Writing_Demographic_Parameters_Matrix(&Table, City_Names[k],
					  Demo_Data, No_of_PARAMETER_SETS,
					  Demographic_Parameters_Index,
					  No_of_DEMOGRAPHIC_PARAMETERS );

    for(n=0; n < No_of_INITIAL_YEARS; n++) { // For each introduction time

      Year[0]='\0'; sprintf( Year, "%d", n+2000 );
      printf("Initial Year: %s\n", Year);

      LIKELIHOOD_VALUES[k][0] = '\0';
      pF = strcat(LIKELIHOOD_VALUES[k], "Likelihood_Values_2016_");
      pF = strcat(LIKELIHOOD_VALUES[k], City_Names[k]);
      pF = strcat(LIKELIHOOD_VALUES[k], "_");
      pF = strcat(LIKELIHOOD_VALUES[k], Year);
      if( SIGMOIDAL == 1 ) pF = strcat(LIKELIHOOD_VALUES[k], "_Sigmoidal.dat");
      else                 pF = strcat(LIKELIHOOD_VALUES[k], ".dat");
      LIKELIHOOD[k] = fopen(LIKELIHOOD_VALUES[k], "w");

      PARAMETER_SET_FILE[k][0] = '\0';
      pF = strcat(PARAMETER_SET_FILE[k], "Full_Parameter_Set_");
      pF = strcat(PARAMETER_SET_FILE[k], City_Names[k]);
      pF = strcat(PARAMETER_SET_FILE[k], "_");
      pF = strcat(PARAMETER_SET_FILE[k], Year);
      if( SIGMOIDAL == 1 ) pF = strcat(PARAMETER_SET_FILE[k], "_Sigmoidal.dat");
      else                 pF = strcat(PARAMETER_SET_FILE[k], ".dat");
      DEMO[k]       = fopen(PARAMETER_SET_FILE[k], "w");

      fprintf(DEMO[k], "City\t");
      for(i=0; i<No_of_PARAMETERS; i++) {
	key = Space->Parameter_Index[i];
	fprintf(DEMO[k], "%s\t", Table.Symbol_Parameters[key]);
      }
      for(i=0; i<No_of_DEMOGRAPHIC_PARAMETERS; i++) {
	key = Demographic_Parameters_Index[i];
	fprintf(DEMO[k], "%s\t", Table.Symbol_Parameters[key]);
      }
      for(i=0; i<No_of_IC; i++) {
	key = Initial_Condition_Space->Parameter_Index[i];
	fprintf(DEMO[k], "%s\t", Table.Model_Variable_Symbol[key]);
      }
      for(i=0; i<No_of_ERROR_PARAMETERS; i++) {
	key = Error_Space->Parameter_Index[i];
	if(key < OUTPUT_VARIABLES_GENUINE)
	  fprintf(DEMO[k], "Error(%s)\t", Table.Output_Variable_Symbol[key]);
	else
	  fprintf(DEMO[k], "Error_Parameter_%d\t", i);
      }
      fprintf(DEMO[k], "NegLogLike\t"); fprintf(DEMO[k], "Deviation\n");
      /*     E N D ----------------------------------------------------------------
       */
      TIME_PARAMETERS_FILE[k][0] = '\0';
      pF = strcat(TIME_PARAMETERS_FILE[k], "Time_Dependent_Parameters_Corrected_");
      pF = strcat(TIME_PARAMETERS_FILE[k], City_Names[k]);
      pF = strcat(TIME_PARAMETERS_FILE[k], "_");
      pF = strcat(TIME_PARAMETERS_FILE[k], Year);
      pF = strcat(TIME_PARAMETERS_FILE[k], ".dat");

      OBSERVED_DATA_FILE[k][0] = '\0';
      pF = strcat(OBSERVED_DATA_FILE[k], "Observed_Data_File_");
      pF = strcat(OBSERVED_DATA_FILE[k], City_Names[k]);
      pF = strcat(OBSERVED_DATA_FILE[k], "_");
      pF = strcat(OBSERVED_DATA_FILE[k], Year);
      if( SIGMOIDAL == 1 ) pF = strcat(OBSERVED_DATA_FILE[k], "_Sigmoidal_Exponential.dat");
      else                 pF = strcat(OBSERVED_DATA_FILE[k], "_Exponential.dat");

      I_Time = I_Time_Total - n;
      Time_0 = 2000.0 + n;
      Time_1 = 2016.0;

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
	printf(" %d output variables of length %d points will be allocated\n",
	       SUB_OUTPUT_VARIABLES, I_Time);
	Time_Dependence_Control_Alloc(&Time, &Time_Dependence, &Table,
				      I_Time, TIME_DEPENDENT_PARAMETERS, No_of_COVARIATES);
	printf(" Both Time_Control and Time_Dependence_Control structures have been\n");
	printf(" correctly allocated\n");
      }

      Reading_Standard_Data_Matrix_from_File( OBSERVED_DATA_FILE[k],
					      Empirical_Data_Matrix,
					      &SUB_OUTPUT_VARIABLES, I_Time,
					      0, Name_of_Rows,
					      0, Time.Time_Vector );

      Writing_Standard_Data_Matrix( Empirical_Data_Matrix,
				    3, I_Time,
				    1, Name_of_Rows,
				    0, Time.Time_Vector);

      assert( SUB_OUTPUT_VARIABLES == 3);

      /* B E G I N : Reserving memmory for Observed Data and Fitting Structure */
      Observed_Data * Data = (Observed_Data *)calloc(1, sizeof(Observed_Data));
      Observed_Data_Alloc( Data, SUB_OUTPUT_VARIABLES, I_Time);
      Observed_Data_Initialization( Data, SUB_OUTPUT_VARIABLES, I_Time, Empirical_Data_Matrix,
				    City_Names[k] );
      printf(" Observe_Data structure has been correctly allocated and initiated\n");
	/*     E N D : ------------------------------------- */

      s = 0;
      int s_Attemps = 0;
      int No_of_Parameter_Sets = 10; // No_of_PARAMETER_SETS; // = 10;
      int Total_Tries          = No_of_Parameter_Sets * Realizations;
      int j_Random = 0;

      for(j=0; j<No_of_Parameter_Sets; j++) {
	for(z=0; z<Realizations; z++) {

	  /* Initial conditions from empirical data at the initial time ( -xn 0 ) */
	  Parameter_Model_Copy_into_Parameter_Table(&Table, Initial_Guess);
	  Random_Initial_Guess_within_Boundaries_Table(&Table, Space);
	  // j_Random = gsl_rng_uniform_int(r, No_of_PARAMETER_SETS);
	  j_Random    = j;
	  Uploading_Demographic_Parameters_into_Parameter_Table(&Table, Demo_Data,
								j_Random,
								Demographic_Parameters_Index,
								No_of_DEMOGRAPHIC_PARAMETERS );

	  int No_of_EMPIRICAL_TIMES = I_Time; // No of Cols in time-dependent parameter files
	  Time_Dependence_Control_Upload(&Time, &Time_Dependence, &Table,
					 I_Time, No_of_EMPIRICAL_TIMES,
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

	  Initial_Condition_from_Data_into_Parameter_Table (&Table,
							    Empirical_Data_Matrix);

	  Parameter_Fitting * F = (Parameter_Fitting*)calloc(1,sizeof(Parameter_Fitting));
	  F->Data                  = Data;
	  F->Space                 = Space;
	  F->Table                 = &Table;
	  F->Verbose               = 1;     // 1: Verbose                // 0: Non Verbose
	  F->Minimization          = 1;     // 1: Function Minimization  // 0: Function Evaluation
	  F->Bounded_Parameter_Set = 1;
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

	  printf("... Simplex bounded optimization starts right at this point within the\n");
	  printf("... parameter space boundaries given above\n");
	  // getchar();

	  Min_Value = GSL_Minimization_Driver( F );

	  printf(" City: %s [Year: %s]:\t", City_Names[k], Year);
	  printf(" Parameter Set Attemp No: %d\t Remaining Attemps: %d\t Successful Attemps: %d\n",
		 s_Attemps, Total_Tries-s_Attemps, s );

	  if (F->Bounded_Parameter_Set == 1) {
	    printf(" Min Value: NLL=%g\t Best Estimates: ", Min_Value);

	    fprintf(DEMO[k], "%s\t", City_Names[k]);

	    for(i=0; i<No_of_PARAMETERS; i++) {
	      key = Space->Parameter_Index[i];
	      value = AssignStructValue_to_VectorEntry(key, &Table);
	      printf("%s = %g  ", Table.Symbol_Parameters[key], value);
	      fprintf(DEMO[k], "%g\t", value);
	    }
	    for(i=0; i<No_of_DEMOGRAPHIC_PARAMETERS; i++) {
	      key = Demographic_Parameters_Index[i];
	      value = AssignStructValue_to_VectorEntry(key, &Table);
	      printf("%s = %g  ", Table.Symbol_Parameters[key], value);
	      fprintf(DEMO[k], "%g\t", value);
	    }
	    for(i=0; i<No_of_IC; i++) {
	      key = Initial_Condition_Space->Parameter_Index[i];
	      value = Model_Variable_Initial_Condition_into_Vector_Entry_Table( key, &Table );
	      printf("%s = %g  ", Table.Model_Variable_Symbol[key], value);
	      fprintf(DEMO[k], "%g\t", value);
	    }
	    for(i=0; i<No_of_ERROR_PARAMETERS; i++) {
	      key = Error_Space->Parameter_Index[i];
	      value = Error_Model_into_Vector_Entry_Table( key, &Table );
	      if(key < OUTPUT_VARIABLES_GENUINE)
		printf("%s = %g  ", Table.Output_Variable_Symbol[key], value);
	      else
		printf("Error_Parameter_%d = %g  ", i, value);
	      fprintf(DEMO[k], "%g\t", value);
	    }
	    fprintf(DEMO[k], "%g\t", Min_Value);

	    /* Accummulating Likelihood of Disease Introduction at Year 'Year' */
	    Data_Value    = Empirical_Data_Matrix[2][Table.T->I_Time-1];
	    Theory_Value  = Table.Matrix_Output_Variables[2][Table.T->I_Time-1];

	    assert ( Table.T->Time_Vector[Table.T->I_Time-1] == 2016.0 );

	    Likelihood_Value=GSL_neglog_Error_Probability_Model_Gaussian(Data_Value,
									 Theory_Value, F);
	    assert( s < No_of_SETS_MAX * Realizations);

	    if (Likelihood_Value > 0.0) {
	      Likelihood[k][n][s++] = Likelihood_Value;
	      fprintf(LIKELIHOOD[k], "%g\n", Likelihood_Value);
	      fprintf(DEMO[k], "%g\n", Likelihood_Value);
	    }
	    else fprintf(DEMO[k], "%g\n", Min_Value);

	  }
	  printf("\n");

	  free(F);

	  s_Attemps++;

	}
      }
      fclose(DEMO[k]); fclose(LIKELIHOOD[k]);

      if( s > 0 )
	Average_and_Variance_double_Vector(Likelihood[k][n], s, &Ave, &Var);

      Average_Likelihood_Value = Ave;
      Standard_Error_Value     = sqrt(Var);

      printf("City: %s\t Introduction Year: %s\t Likelihood +/- Std Error: %g +/- %g\n",
	     City_Names[k], Year, Average_Likelihood_Value, Standard_Error_Value);

      fprintf(f, "City: %s\t Introduction Year: %s\t Likelihood +/- Std Error: %g +/- %g\n",
	     City_Names[k], Year, Average_Likelihood_Value, Standard_Error_Value);

      Observed_Data_Free(Data);
      free(Data);

      Time_Dependence_Control_Free( &Time_Dependence, &Table );
    }
  }
  I_Time = I_Time_Total;
  fclose(f);

  /* BEGIN : ------------------------------------------------------------------------
   * Likelihood distributions at each introduction year for each and every city
   */

  /*   END : ------------------------------------------------------------------------
   */

  /* BEGIN : Freeing All Memmory * * * * * * * * * * * * * * */
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

  free(Name_of_Rows);
  for (i=0; i<SUB_OUTPUT_VARIABLES; i++)  free(Empirical_Data_Matrix[i]);
  free(Empirical_Data_Matrix);

  for (i=0; i<No_of_CITIES; i++) {
    for(j=0; j<No_of_INITIAL_YEARS; j++) free(Likelihood[i][j]);
    free(Likelihood[i]);
  }
  free(Likelihood);

  free(Year);

  for(i=0; i<No_of_CITIES; i++) free(Demo_Data[i]);
  free(Demo_Data);

  for(k = 0; k<No_of_CITIES; k++) {
    free(TIME_PARAMETERS_FILE[k]);
    free(OBSERVED_DATA_FILE[k]);
    free(DEMO_PARAMETER_SET[k]);
    free(PARAMETER_SET_FILE[k]);
  }
  free(TIME_PARAMETERS_FILE);
  free(OBSERVED_DATA_FILE);
  free(DEMO_PARAMETER_SET);
  free(PARAMETER_SET_FILE);

  free(DEMO);
  free(LIKELIHOOD);

  free(Initial_Guess);

  free(Demographic_Parameters_Index);

  P_A_R_A_M_E_T_E_R___T_A_B_L_E___F_R_E_E( &Table );
  /*  END : Freeing  All Memmory * * * * * * * * * * * * * * */

  printf("\nEnd of progam\n");
  return (0);
}
