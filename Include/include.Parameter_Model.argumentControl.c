/* Human Parameters */

	    case 'H': /* Maximum and Minimum Transmission Rate */
	      if(argv[argcount][2]=='0')         sscanf(argv[argcount+1],"%lf",&Beta_Y);
	      else if(argv[argcount][2]=='1') {
		if(argv[argcount][3]=='0') 	 sscanf(argv[argcount+1],"%lf",&Sigma_0);
		else if(argv[argcount][3]=='1')  sscanf(argv[argcount+1],"%lf",&Sigma_0_r);
		else if(argv[argcount][3]=='2')  sscanf(argv[argcount+1],"%lf",&Eta);
		else if(argv[argcount][3]=='3')  sscanf(argv[argcount+1],"%lf",&F_X);
		else if(argv[argcount][3]=='4')  sscanf(argv[argcount+1],"%d",&n_Mu);
		else if(argv[argcount][3]=='5')  sscanf(argv[argcount+1],"%lf",&Xhi);
		else if(argv[argcount][3]=='6')  sscanf(argv[argcount+1],"%lf",&f_W);
		else if(argv[argcount][3]=='7')  sscanf(argv[argcount+1],"%lf",&f_0);
		else if(argv[argcount][3]=='8')  sscanf(argv[argcount+1],"%lf",&Sigma_1);
		else if(argv[argcount][3]=='9')  sscanf(argv[argcount+1],"%lf",&Sigma_1_r);
		else if(argv[argcount][3]=='\0') sscanf(argv[argcount+1],"%lf",&p_XY);
		else {
		  printf(" Error at reading input arguments: -  %s  \n", argv[argcount]);
		  exit(0);
		}
	      }
	      else if(argv[argcount][2]=='2') {
		if(argv[argcount][3]=='0')       sscanf(argv[argcount+1],"%lf",&Alpha);
		else if(argv[argcount][3]=='1')  sscanf(argv[argcount+1],"%lf", &r_F);
		else if(argv[argcount][3]=='2')  sscanf(argv[argcount+1],"%lf", &D_Sigma);
		else if(argv[argcount][3]=='3')  sscanf(argv[argcount+1],"%lf", &Sigmoidal_A0);
		else if(argv[argcount][3]=='4')  sscanf(argv[argcount+1],"%lf", &Sigmoidal_L0);
		else if(argv[argcount][3]=='5')  sscanf(argv[argcount+1],"%lf", &Sigmoidal_T0);
		else if(argv[argcount][3]=='\0') sscanf(argv[argcount+1],"%lf", &F_Y);
		else {
		  printf(" Error at reading input arguments: -  %s  \n", argv[argcount]);
		  exit(0);
		}
	      }
	      else if(argv[argcount][2]=='3')    sscanf(argv[argcount+1],"%lf",&Delta_X);
	      else if(argv[argcount][2]=='4')    sscanf(argv[argcount+1],"%lf",&Delta_Y);
	      else if(argv[argcount][2]=='5')    sscanf(argv[argcount+1],"%lf",&Gamma);
	      else if(argv[argcount][2]=='6')    sscanf(argv[argcount+1],"%lf",&Mu);
	      else if(argv[argcount][2]=='7')    sscanf(argv[argcount+1],"%lf",&mDelta);
	      else if(argv[argcount][2]=='8')    sscanf(argv[argcount+1],"%lf",&Beta_X);
	      else if(argv[argcount][2]=='9')    sscanf(argv[argcount+1],"%lf",&p_YX);
	      else {
		printf(" Error at reading input arguments: -  %s  \n", argv[argcount]);
		exit(0);
	      }
	      skip++;
	      break;

#include <include.Type_of_Model.argumentControl.c>
