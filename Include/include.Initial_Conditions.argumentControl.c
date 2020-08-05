/* Scan Parameters */

/* Initial Conditions */
	case 'x':
	      if(argv[argcount][2]=='0')
		sscanf(argv[argcount+1], "%lf",&YS__0);
	      else if(argv[argcount][2]=='1') {
		if(argv[argcount][3]=='0')       sscanf(argv[argcount+1], "%lf",&WL__0);
		else if(argv[argcount][3]=='1')  sscanf(argv[argcount+1], "%lf",&WD__0);
		else if(argv[argcount][3]=='2')  sscanf(argv[argcount+1], "%lf",&X0S__0);
		else if(argv[argcount][3]=='3')  sscanf(argv[argcount+1], "%lf",&X0I__0);
		else if(argv[argcount][3]=='4')  sscanf(argv[argcount+1], "%lf",&X0L__0);
		else if(argv[argcount][3]=='5')  sscanf(argv[argcount+1], "%lf",&X0D__0);
		else if(argv[argcount][3]=='6')  sscanf(argv[argcount+1], "%lf",&W0S__0);
		else if(argv[argcount][3]=='7')  sscanf(argv[argcount+1], "%lf",&W0I__0);
		else if(argv[argcount][3]=='8')  sscanf(argv[argcount+1], "%lf",&W0L__0);
		else if(argv[argcount][3]=='9')  sscanf(argv[argcount+1], "%lf",&W0D__0);
		else if(argv[argcount][3]=='\0') sscanf(argv[argcount+1],  "%lf",&YI__0);
		else {
		  printf(" Error at reading input arguments:\n");
		  printf("X0 to -WL are the only allowable keys. You have typed %s",
		       argv[argcount]);
		  exit(0);
		}
	      }
              else if(argv[argcount][2]=='2') {
		if(argv[argcount][3]=='0')       sscanf(argv[argcount+1], "%lf",&X1S__0);
		else if(argv[argcount][3]=='1')  sscanf(argv[argcount+1], "%lf",&X1I__0);
		else if(argv[argcount][3]=='2')  sscanf(argv[argcount+1], "%lf",&X1L__0);
		else if(argv[argcount][3]=='3')  sscanf(argv[argcount+1], "%lf",&X1D__0);
		else if(argv[argcount][3]=='4')  sscanf(argv[argcount+1], "%lf",&W1S__0);
		else if(argv[argcount][3]=='5')  sscanf(argv[argcount+1], "%lf",&W1I__0);
		else if(argv[argcount][3]=='6')  sscanf(argv[argcount+1], "%lf",&W1L__0);
		else if(argv[argcount][3]=='7')  sscanf(argv[argcount+1], "%lf",&W1D__0);
		else if(argv[argcount][3]=='\0') sscanf(argv[argcount+1],  "%lf",&YL__0);
		else {
		  printf(" Error at reading input arguments:\n");
		  printf("X0 to -WL are the only allowable keys. You have typed %s",
		       argv[argcount]);
		  exit(0);
		}
	      }
	      else if(argv[argcount][2]=='3')    sscanf(argv[argcount+1], "%lf",&YD__0);
              else if(argv[argcount][2]=='4')    sscanf(argv[argcount+1], "%lf",&XS__0);
              else if(argv[argcount][2]=='5')    sscanf(argv[argcount+1], "%lf",&XI__0);
	      else if(argv[argcount][2]=='6')    sscanf(argv[argcount+1], "%lf",&XL__0);
	      else if(argv[argcount][2]=='7')    sscanf(argv[argcount+1], "%lf",&XD__0);
              else if(argv[argcount][2]=='8')    sscanf(argv[argcount+1], "%lf",&WS__0);
              else if(argv[argcount][2]=='9')    sscanf(argv[argcount+1], "%lf",&WI__0);

	      else if(argv[argcount][2]=='n') 
		sscanf(argv[argcount+1], "%d",&TYPE_of_INITIAL_CONDITION);
		
	      else if(argv[argcount][2]=='R') 
		sscanf(argv[argcount+1], "%d",&RESCALING_INITIAL_TOTAL_POPULATION);
	     
	      else if(argv[argcount][2]=='N') 
		sscanf(argv[argcount+1], "%lf",&INITIAL_TOTAL_POPULATION);
		
	      else{
		printf("xn -xN -xR -x0 to -x27 are the only allowable keys.\n");
		printf("Something goes very wrong (in an argumentsscanf function)\n");
		exit(0);
	      }
        skip++;
        break;

	case 'i':
              if(argv[argcount][2]=='P')        sscanf(argv[argcount+1], "%d", &No_of_IC);
              else if (argv[argcount][2]=='0')  sscanf(argv[argcount+1], "%d", &IC_0);
	      else if(argv[argcount][2]=='1') {
		if(argv[argcount][3]=='0')      sscanf(argv[argcount+1], "%d", &IC_10);
		else if(argv[argcount][3]=='1') sscanf(argv[argcount+1], "%d", &IC_11);
                else if(argv[argcount][3]=='2') sscanf(argv[argcount+1], "%d", &IC_12);
		else if(argv[argcount][3]=='3') sscanf(argv[argcount+1], "%d", &IC_13);
		else if(argv[argcount][3]=='4') sscanf(argv[argcount+1], "%d", &IC_14);
		else if(argv[argcount][3]=='5') sscanf(argv[argcount+1], "%d", &IC_15);
		else if(argv[argcount][3]=='6') sscanf(argv[argcount+1], "%d", &IC_16);
		else if(argv[argcount][3]=='7') sscanf(argv[argcount+1], "%d", &IC_17);
		else if(argv[argcount][3]=='8') sscanf(argv[argcount+1], "%d", &IC_18);
		else if(argv[argcount][3]=='9') sscanf(argv[argcount+1], "%d", &IC_19);
		else if(argv[argcount][3]=='\0') sscanf(argv[argcount+1], "%d", &IC_1);
		else {
		  printf(" Error at reading input arguments:\n");
		  printf("iP -i0 to -i10 are the only allowable keys. You have typed %s",
		       argv[argcount]);
		  exit(0);
		}
	      }
	      else if(argv[argcount][2]=='2') {
		if(argv[argcount][3]=='0')      sscanf(argv[argcount+1], "%d", &IC_20);
		else if(argv[argcount][3]=='1') sscanf(argv[argcount+1], "%d", &IC_21);
		else                            sscanf(argv[argcount+1], "%d", &IC_2);
	      }
	      else if(argv[argcount][2]=='3')   sscanf(argv[argcount+1], "%d", &IC_3);
	      else if(argv[argcount][2]=='4')   sscanf(argv[argcount+1], "%d", &IC_4);
	      else if(argv[argcount][2]=='5')   sscanf(argv[argcount+1], "%d", &IC_5);
	      else if(argv[argcount][2]=='6')   sscanf(argv[argcount+1], "%d", &IC_6);
	      else if(argv[argcount][2]=='7')   sscanf(argv[argcount+1], "%d", &IC_7);
	      else if(argv[argcount][2]=='8')   sscanf(argv[argcount+1], "%d", &IC_8);
	      else if(argv[argcount][2]=='9')   sscanf(argv[argcount+1], "%d", &IC_9);
	      else {
		printf("**invalid command line argument: %s%c\n",
		       "i...", argv[argcount][2]);
		exit(0);
	      }
        skip++;
        break;

        case 'u': //Minimum values 
        if(argv[argcount][2]=='0')              sscanf(argv[argcount+1], "%lf", &IC_min_0);
        else if(argv[argcount][2]=='1') {
          if(argv[argcount][3]=='0')            sscanf(argv[argcount+1], "%lf", &IC_min_10);
          else if(argv[argcount][3]=='1')       sscanf(argv[argcount+1], "%lf", &IC_min_11);
          else if(argv[argcount][3]=='2')       sscanf(argv[argcount+1], "%lf", &IC_min_12);
          else if(argv[argcount][3]=='3')       sscanf(argv[argcount+1], "%lf", &IC_min_13);
          else if(argv[argcount][3]=='4')       sscanf(argv[argcount+1], "%lf", &IC_min_14);
          else if(argv[argcount][3]=='5')       sscanf(argv[argcount+1], "%lf", &IC_min_15);
          else if(argv[argcount][3]=='6')       sscanf(argv[argcount+1], "%lf", &IC_min_16);
          else if(argv[argcount][3]=='7')       sscanf(argv[argcount+1], "%lf", &IC_min_17);
          else if(argv[argcount][3]=='8')       sscanf(argv[argcount+1], "%lf", &IC_min_18);
          else if(argv[argcount][3]=='9')       sscanf(argv[argcount+1], "%lf", &IC_min_19);
          else if(argv[argcount][3]=='\0')      sscanf(argv[argcount+1], "%lf", &IC_min_1);
	  else {
	    printf(" Error at reading input arguments:\n");
	    printf("u0 to -u10 are the only allowable keys. You have typed %s",
		   argv[argcount]);
	    exit(0);
	  }
        }
        else if(argv[argcount][2]=='2') { 
          if(argv[argcount][3]=='0')            sscanf(argv[argcount+1], "%lf", &IC_min_20);
          else if(argv[argcount][3]=='1')       sscanf(argv[argcount+1], "%lf", &IC_min_21);
          else if(argv[argcount][3]=='\0')      sscanf(argv[argcount+1], "%lf", &IC_min_2);
	  else {
	    printf(" Error at reading input arguments:\n");
	    printf("u2 -u20 -u21 are the only allowable keys. You have typed %s",
		   argv[argcount]);
	    exit(0);
	  }
        }
        else if(argv[argcount][2]=='3')         sscanf(argv[argcount+1], "%lf", &IC_min_3);
        else if(argv[argcount][2]=='4')         sscanf(argv[argcount+1], "%lf", &IC_min_4);
        else if(argv[argcount][2]=='5')         sscanf(argv[argcount+1], "%lf", &IC_min_5);
        else if(argv[argcount][2]=='6')         sscanf(argv[argcount+1], "%lf", &IC_min_6);
        else if(argv[argcount][2]=='7')         sscanf(argv[argcount+1], "%lf", &IC_min_7);
        else if(argv[argcount][2]=='8')         sscanf(argv[argcount+1], "%lf", &IC_min_8);
        else if(argv[argcount][2]=='9')         sscanf(argv[argcount+1], "%lf", &IC_min_9);
        else {
          printf("**invalid command line argument: %s%c\n",
          "u...", argv[argcount][2]);
          exit(0);
        }
        skip++;
        break;


        case 'U':  //Maximum values
        if(argv[argcount][2]=='0')              sscanf(argv[argcount+1], "%lf", &IC_MAX_0);
        else if(argv[argcount][2]=='1'){
          if(argv[argcount][3]=='0')            sscanf(argv[argcount+1], "%lf", &IC_MAX_10);
          else if(argv[argcount][3]=='1')       sscanf(argv[argcount+1], "%lf", &IC_MAX_11);
          else if(argv[argcount][3]=='2')       sscanf(argv[argcount+1], "%lf", &IC_MAX_12);
          else if(argv[argcount][3]=='3')       sscanf(argv[argcount+1], "%lf", &IC_MAX_13);
          else if(argv[argcount][3]=='4')       sscanf(argv[argcount+1], "%lf", &IC_MAX_14);
          else if(argv[argcount][3]=='5')       sscanf(argv[argcount+1], "%lf", &IC_MAX_15);
          else if(argv[argcount][3]=='6')       sscanf(argv[argcount+1], "%lf", &IC_MAX_16);
          else if(argv[argcount][3]=='7')       sscanf(argv[argcount+1], "%lf", &IC_MAX_17);
          else if(argv[argcount][3]=='8')       sscanf(argv[argcount+1], "%lf", &IC_MAX_18);
          else if(argv[argcount][3]=='9')       sscanf(argv[argcount+1], "%lf", &IC_MAX_19);
          else if(argv[argcount][3]=='\0')      sscanf(argv[argcount+1], "%lf", &IC_MAX_1);
	  else {
	    printf(" Error at reading input arguments:\n");
	    printf("U0  -U1 -U10 to U19 are the only allowable keys. You have typed %s",
		   argv[argcount]);
	    exit(0);
	  }
        }
        else if(argv[argcount][2]=='2') {
          if(argv[argcount][3]=='0')            sscanf(argv[argcount+1], "%lf", &IC_MAX_20);
          else if(argv[argcount][3]=='1')       sscanf(argv[argcount+1], "%lf", &IC_MAX_21);
          else if(argv[argcount][3]=='\0')      sscanf(argv[argcount+1], "%lf", &IC_MAX_2);
	  else {
	    printf(" Error at reading input arguments:\n");
	    printf("U2  -U20 -U21 to U19 are the only allowable keys. You have typed %s",
		   argv[argcount]);
	    exit(0);
	  }
        }
        else if(argv[argcount][2]=='3')         sscanf(argv[argcount+1], "%lf", &IC_MAX_3);
        else if(argv[argcount][2]=='4')         sscanf(argv[argcount+1], "%lf", &IC_MAX_4);
        else if(argv[argcount][2]=='5')         sscanf(argv[argcount+1], "%lf", &IC_MAX_5);
        else if(argv[argcount][2]=='6')         sscanf(argv[argcount+1], "%lf", &IC_MAX_6);
        else if(argv[argcount][2]=='7')         sscanf(argv[argcount+1], "%lf", &IC_MAX_7);
        else if(argv[argcount][2]=='8')         sscanf(argv[argcount+1], "%lf", &IC_MAX_8);
        else if(argv[argcount][2]=='9')         sscanf(argv[argcount+1], "%lf", &IC_MAX_9);
        else {
          printf("**invalid command line argument: %s%c\n",
          "U...", argv[argcount][2]);
          exit(0);
        }
        skip++;
        break;
