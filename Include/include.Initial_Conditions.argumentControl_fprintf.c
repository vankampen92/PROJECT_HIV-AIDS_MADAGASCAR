/* Scan Parameters */

/* Initial Conditions */
	case 'x':
	      if(argv[argcount][2]=='0')
		fprintf(fp, "-x0  %g  ",Table->YS__0);
	      else if(argv[argcount][2]=='1') {
		if(argv[argcount][3]=='0')       fprintf(fp, "-x10  %g  ",Table->WL__0);
		else if(argv[argcount][3]=='1')  fprintf(fp, "-x11  %g  ",Table->WD__0);
		else if(argv[argcount][3]=='2')  fprintf(fp, "-x12  %g  ",Table->X0S__0);
		else if(argv[argcount][3]=='3')  fprintf(fp, "-x13  %g  ",Table->X0I__0);
		else if(argv[argcount][3]=='4')  fprintf(fp, "-x14  %g  ",Table->X0L__0);
		else if(argv[argcount][3]=='5')  fprintf(fp, "-x15  %g  ",Table->X0D__0);
		else if(argv[argcount][3]=='6')  fprintf(fp, "-x16  %g  ",Table->W0S__0);
		else if(argv[argcount][3]=='7')  fprintf(fp, "-x17  %g  ",Table->W0I__0);
		else if(argv[argcount][3]=='8')  fprintf(fp, "-x18  %g  ",Table->W0L__0);
		else if(argv[argcount][3]=='9')  fprintf(fp, "-x19  %g  ",Table->W0D__0);
		else if(argv[argcount][3]=='\0') fprintf(fp,  "-x1  %g  ",Table->YI__0);
		else {
		  printf(" Error at reading input arguments:\n");
		  printf("-X0 to -WL are the only allowable keys. You have typed %s",
		       argv[argcount]);
		  exit(0);
		}
	      }
              else if(argv[argcount][2]=='2') {
		if(argv[argcount][3]=='0')       fprintf(fp, "-x20  %g  ",Table->X1S__0);
		else if(argv[argcount][3]=='1')  fprintf(fp, "-x21  %g  ",Table->X1I__0);
		else if(argv[argcount][3]=='2')  fprintf(fp, "-x22  %g  ",Table->X1L__0);
		else if(argv[argcount][3]=='3')  fprintf(fp, "-x23  %g  ",Table->X1D__0);
		else if(argv[argcount][3]=='4')  fprintf(fp, "-x24  %g  ",Table->W1S__0);
		else if(argv[argcount][3]=='5')  fprintf(fp, "-x25  %g  ",Table->W1I__0);
		else if(argv[argcount][3]=='6')  fprintf(fp, "-x26  %g  ",Table->W1L__0);
		else if(argv[argcount][3]=='7')  fprintf(fp, "-x27  %g  ",Table->W1D__0);
		else if(argv[argcount][3]=='\0') fprintf(fp,  "-x2  %g  ",Table->YL__0);
		else {
		  printf(" Error at reading input arguments:\n");
		  printf("-X0 to -WL are the only allowable keys. You have typed %s",
		       argv[argcount]);
		  exit(0);
		}
	      }
	      else if(argv[argcount][2]=='3')    fprintf(fp, "-x3  %g  ",Table->YD__0);
              else if(argv[argcount][2]=='4')    fprintf(fp, "-x4  %g  ",Table->XS__0);
              else if(argv[argcount][2]=='5')    fprintf(fp, "-x5  %g  ",Table->XI__0);
	      else if(argv[argcount][2]=='6')    fprintf(fp, "-x6  %g  ",Table->XL__0);
	      else if(argv[argcount][2]=='7')    fprintf(fp, "-x7  %g  ",Table->XD__0);
              else if(argv[argcount][2]=='8')    fprintf(fp, "-x8  %g  ",Table->WS__0);
              else if(argv[argcount][2]=='9')    fprintf(fp, "-x9  %g  ",Table->WI__0);

	      else if(argv[argcount][2]=='n') 
		fprintf(fp, "-xn %d  ",Table->TYPE_of_INITIAL_CONDITION);
		
	      else if(argv[argcount][2]=='R') 
		fprintf(fp, "-xR %d  ",Table->RESCALING_INITIAL_TOTAL_POPULATION);
	     
	      else if(argv[argcount][2]=='N') 
		fprintf(fp, "-xN  %g  ",Table->INITIAL_TOTAL_POPULATION);
		
	      else{
		printf("-xn -xN -xR -x0 to -x27 are the only allowable keys.\n");
		printf("Something goes very wrong (in an argumentfprintf function)\n");
		exit(0);
	      }
        skip++;
        break;

	case 'i':
              if(argv[argcount][2]=='P')        fprintf(fp, "-iP  %d  ",  Table->No_of_IC);
              else if (argv[argcount][2]=='0')  fprintf(fp, "-i0  %d  ",  IC_0);
	      else if(argv[argcount][2]=='1') {
		if(argv[argcount][3]=='0')      fprintf(fp, "-i10  %d  ", IC_10);
		else if(argv[argcount][3]=='1') fprintf(fp, "-i11  %d  ", IC_11);
                else if(argv[argcount][3]=='2') fprintf(fp, "-i12  %d  ", IC_12);
		else if(argv[argcount][3]=='3') fprintf(fp, "-i13  %d  ", IC_13);
		else if(argv[argcount][3]=='4') fprintf(fp, "-i14  %d  ", IC_14);
		else if(argv[argcount][3]=='5') fprintf(fp, "-i15  %d  ", IC_15);
		else if(argv[argcount][3]=='6') fprintf(fp, "-i16  %d  ", IC_16);
		else if(argv[argcount][3]=='7') fprintf(fp, "-i17  %d  ", IC_17);
		else if(argv[argcount][3]=='8') fprintf(fp, "-i18  %d  ", IC_18);
		else if(argv[argcount][3]=='9') fprintf(fp, "-i19  %d  ", IC_19);
		else if(argv[argcount][3]=='\0') fprintf(fp, "-i1  %d  ", IC_1);
		else {
		  printf(" Error at reading input arguments:\n");
		  printf("-iP -i0 to -i10 are the only allowable keys. You have typed %s",
		       argv[argcount]);
		  exit(0);
		}
	      }
	      else if(argv[argcount][2]=='2') {
		if(argv[argcount][3]=='0')      fprintf(fp, "-i20  %d  ", IC_20);
		else if(argv[argcount][3]=='1') fprintf(fp, "-i21  %d  ", IC_21);
		else                            fprintf(fp, "-i2  %d  ", IC_2);
	      }
	      else if(argv[argcount][2]=='3')   fprintf(fp, "-i3  %d  ", IC_3);
	      else if(argv[argcount][2]=='4')   fprintf(fp, "-i4  %d  ", IC_4);
	      else if(argv[argcount][2]=='5')   fprintf(fp, "-i5  %d  ", IC_5);
	      else if(argv[argcount][2]=='6')   fprintf(fp, "-i6  %d  ", IC_6);
	      else if(argv[argcount][2]=='7')   fprintf(fp, "-i7  %d  ", IC_7);
	      else if(argv[argcount][2]=='8')   fprintf(fp, "-i8  %d  ", IC_8);
	      else if(argv[argcount][2]=='9')   fprintf(fp, "-i9  %d  ", IC_9);
	      else {
		printf("**invalid command line argument: %s%c\n",
		       "-i...", argv[argcount][2]);
		exit(0);
	      }
        skip++;
        break;

        case 'u': //Minimum values 
        if(argv[argcount][2]=='0')              fprintf(fp, "-u0  %g  ", IC_min_0);
        else if(argv[argcount][2]=='1') {
          if(argv[argcount][3]=='0')            fprintf(fp, "-u10  %g  ", IC_min_10);
          else if(argv[argcount][3]=='1')       fprintf(fp, "-u11  %g  ", IC_min_11);
          else if(argv[argcount][3]=='2')       fprintf(fp, "-u12  %g  ", IC_min_12);
          else if(argv[argcount][3]=='3')       fprintf(fp, "-u13  %g  ", IC_min_13);
          else if(argv[argcount][3]=='4')       fprintf(fp, "-u14  %g  ", IC_min_14);
          else if(argv[argcount][3]=='5')       fprintf(fp, "-u15  %g  ", IC_min_15);
          else if(argv[argcount][3]=='6')       fprintf(fp, "-u16  %g  ", IC_min_16);
          else if(argv[argcount][3]=='7')       fprintf(fp, "-u17  %g  ", IC_min_17);
          else if(argv[argcount][3]=='8')       fprintf(fp, "-u18  %g  ", IC_min_18);
          else if(argv[argcount][3]=='9')       fprintf(fp, "-u19  %g  ", IC_min_19);
          else if(argv[argcount][3]=='\0')      fprintf(fp, "-u1  %g  ", IC_min_1);
	  else {
	    printf(" Error at reading input arguments:\n");
	    printf("-u0 to -u10 are the only allowable keys. You have typed %s",
		   argv[argcount]);
	    exit(0);
	  }
        }
        else if(argv[argcount][2]=='2') { 
          if(argv[argcount][3]=='0')            fprintf(fp, "-u20  %g  ", IC_min_20);
          else if(argv[argcount][3]=='1')       fprintf(fp, "-u21  %g  ", IC_min_21);
          else if(argv[argcount][3]=='\0')      fprintf(fp, "-u2  %g  ", IC_min_2);
	  else {
	    printf(" Error at reading input arguments:\n");
	    printf("-u2 -u20 -u21 are the only allowable keys. You have typed %s",
		   argv[argcount]);
	    exit(0);
	  }
        }
        else if(argv[argcount][2]=='3')         fprintf(fp, "-u3  %g  ", IC_min_3);
        else if(argv[argcount][2]=='4')         fprintf(fp, "-u4  %g  ", IC_min_4);
        else if(argv[argcount][2]=='5')         fprintf(fp, "-u5  %g  ", IC_min_5);
        else if(argv[argcount][2]=='6')         fprintf(fp, "-u6  %g  ", IC_min_6);
        else if(argv[argcount][2]=='7')         fprintf(fp, "-u7  %g  ", IC_min_7);
        else if(argv[argcount][2]=='8')         fprintf(fp, "-u8  %g  ", IC_min_8);
        else if(argv[argcount][2]=='9')         fprintf(fp, "-u9  %g  ", IC_min_9);
        else {
          printf("**invalid command line argument: %s%c\n",
          "-u...", argv[argcount][2]);
          exit(0);
        }
        skip++;
        break;


        case 'U':  //Maximum values
        if(argv[argcount][2]=='0')              fprintf(fp, "-U0  %g  ", IC_MAX_0);
        else if(argv[argcount][2]=='1'){
          if(argv[argcount][3]=='0')            fprintf(fp, "-U10  %g  ", IC_MAX_10);
          else if(argv[argcount][3]=='1')       fprintf(fp, "-U11  %g  ", IC_MAX_11);
          else if(argv[argcount][3]=='2')       fprintf(fp, "-U12  %g  ", IC_MAX_12);
          else if(argv[argcount][3]=='3')       fprintf(fp, "-U13  %g  ", IC_MAX_13);
          else if(argv[argcount][3]=='4')       fprintf(fp, "-U14  %g  ", IC_MAX_14);
          else if(argv[argcount][3]=='5')       fprintf(fp, "-U15  %g  ", IC_MAX_15);
          else if(argv[argcount][3]=='6')       fprintf(fp, "-U16  %g  ", IC_MAX_16);
          else if(argv[argcount][3]=='7')       fprintf(fp, "-U17  %g  ", IC_MAX_17);
          else if(argv[argcount][3]=='8')       fprintf(fp, "-U18  %g  ", IC_MAX_18);
          else if(argv[argcount][3]=='9')       fprintf(fp, "-U19  %g  ", IC_MAX_19);
          else if(argv[argcount][3]=='\0')      fprintf(fp, "-U1  %g  ", IC_MAX_1);
	  else {
	    printf(" Error at reading input arguments:\n");
	    printf("-U0  -U1 -U10 to U19 are the only allowable keys. You have typed %s",
		   argv[argcount]);
	    exit(0);
	  }
        }
        else if(argv[argcount][2]=='2') {
          if(argv[argcount][3]=='0')            fprintf(fp, "-U20  %g  ", IC_MAX_20);
          else if(argv[argcount][3]=='1')       fprintf(fp, "-U21  %g  ", IC_MAX_21);
          else if(argv[argcount][3]=='\0')      fprintf(fp, "-U2  %g  ", IC_MAX_2);
	  else {
	    printf(" Error at reading input arguments:\n");
	    printf("-U2  -U20 -U21 to U19 are the only allowable keys. You have typed %s",
		   argv[argcount]);
	    exit(0);
	  }
        }
        else if(argv[argcount][2]=='3')         fprintf(fp, "-U3  %g  ", IC_MAX_3);
        else if(argv[argcount][2]=='4')         fprintf(fp, "-U4  %g  ", IC_MAX_4);
        else if(argv[argcount][2]=='5')         fprintf(fp, "-U5 %g  ", IC_MAX_5);
        else if(argv[argcount][2]=='6')         fprintf(fp, "-U6  %g  ", IC_MAX_6);
        else if(argv[argcount][2]=='7')         fprintf(fp, "-U7  %g  ", IC_MAX_7);
        else if(argv[argcount][2]=='8')         fprintf(fp, "-U8  %g  ", IC_MAX_8);
        else if(argv[argcount][2]=='9')         fprintf(fp, "-U9  %g  ", IC_MAX_9);
        else {
          printf("**invalid command line argument: %s%c\n",
          "-U...", argv[argcount][2]);
          exit(0);
        }
        skip++;
        break;
