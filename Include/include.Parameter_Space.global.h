  int No_of_PARAMETERS; /* No of parameters defining the actual dimension of
			                     the subparameter space */

  int I0, I1, I2, I3, I4, I5, I6, I7, I8, I9;
  int d0, d1, d2, d3, d4, d5, d6, d7, d8, d9;
  double MAX_P0, MAX_P1, MAX_P2, MAX_P3, MAX_P4, MAX_P5, MAX_P6, MAX_P7, MAX_P8, MAX_P9;
  double min_P0, min_P1, min_P2, min_P3, min_P4, min_P5, min_P6, min_P7, min_P8, min_P9;
  double Acc_P0, Acc_P1, Acc_P2, Acc_P3, Acc_P4, Acc_P5, Acc_P6, Acc_P7, Acc_P8, Acc_P9;

  int I10, I11, I12, I13, I14, I15, I16, I17, I18, I19;
  int d10, d11, d12, d13, d14, d15, d16, d17, d18, d19;
  double MAX_P10, MAX_P11, MAX_P12, MAX_P13, MAX_P14, MAX_P15, MAX_P16, MAX_P17, MAX_P18, MAX_P19;
  double min_P10, min_P11, min_P12, min_P13, min_P14, min_P15, min_P16, min_P17, min_P18, min_P19;
  double Acc_P10, Acc_P11, Acc_P12, Acc_P13, Acc_P14, Acc_P15, Acc_P16, Acc_P17, Acc_P18, Acc_P19;

  int I20, I21;
  int d20, d21;
  double MAX_P20, MAX_P21;
  double min_P20, min_P21;
  double Acc_P20, Acc_P21;

  double TOLERANCE;
  int MAX_No_of_ITERATIONS;

  double ** Ranges;
  double * Acc;     //Accuracy for each parameter dimension
  int    * d;       //Discretization for each parameter dimension
  int    * Index;
