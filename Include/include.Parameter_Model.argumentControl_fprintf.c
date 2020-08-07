/* Human Parameters */

	    case 'H': /* Maximum and Minimum Transmission Rate */
	      if(argv[argcount][2]=='0')
		fprintf(fp,"-H0  %g  ",Table->Beta_Y);
	      else if(argv[argcount][2]=='1') {
				 if(argv[argcount][3]=='0'){
					 fprintf(fp,"-H10  %g  ",Table->Sigma_0);
	       }
		     else if(argv[argcount][3]=='1'){
		       fprintf(fp,"-H11  %g  ",Table->Sigma_0_r);
		     }
		     else if(argv[argcount][3]=='2'){
		       fprintf(fp,"-H12  %g  ",Table->Eta);
		     }
		     else if(argv[argcount][3]=='3'){
		       fprintf(fp,"-H13  %g  ",Table->F_X);
		     }
		     else if(argv[argcount][3]=='4'){
		       fprintf(fp,"-H14  %d  ",Table->n_Mu);
		     }
		     else if(argv[argcount][3]=='5'){
		       fprintf(fp,"-H15  %g  ",Table->Xhi);
		     }
		     else if(argv[argcount][3]=='6'){
		       fprintf(fp,"-H16  %g  ",Table->f_W);
		     }
		     else if(argv[argcount][3]=='7'){
		       fprintf(fp,"-H17  %g  ",Table->f_0);
		     }
		     else if(argv[argcount][3]=='8'){
		       fprintf(fp,"-H18  %g  ",Table->Sigma_1);
		     }
		     else if(argv[argcount][3]=='9'){
		       fprintf(fp,"-H19  %g  ",Table->Sigma_1_r);
		     }
				 else if(argv[argcount][3]=='\0'){
		       fprintf(fp,"-H1  %g  ",Table->p_XY);
		     }
		     else {
		       printf(" Error at reading input arguments: -  %s  \n", argv[argcount]);
		       exit(0);
		     }
	      }
        else if(argv[argcount][2]=='2') {
	             if(argv[argcount][3]=='0'){
 		       fprintf(fp,"-H20  %g  ",Table->Alpha);
				  }
		       else if(argv[argcount][3]=='1'){
 		       fprintf(fp,"-H21  %g  ", Table->r_F);
		       }
		       else if(argv[argcount][3]=='2'){
 		       fprintf(fp,"-H22  %g  ", Table->D_Sigma);
		       }
		       else if(argv[argcount][3]=='3'){
		       fprintf(fp,"-H23  %g  ", Table->Sigmoidal_A0); 
		       }
		       else if(argv[argcount][3]=='4'){
 		       fprintf(fp,"-H24  %g  ", Table->Sigmoidal_L0); 
		       }
		       else if(argv[argcount][3]=='5'){
 		       fprintf(fp,"-H25  %g  ", Table->Sigmoidal_T0); 
		       }
		       else if(argv[argcount][3]=='\0'){
 		       fprintf(fp,"-H2  %g  ", Table->F_Y);
				  }
 		       else {
 		       printf(" Error at reading input arguments: -  %s  \n", argv[argcount]);
 		       exit(0);
 		     }
	}
	      else if(argv[argcount][2]=='3')
		fprintf(fp,"-H3  %g  ",Table->Delta_X);
		    else if(argv[argcount][2]=='4')
		fprintf(fp,"-H4  %g  ",Table->Delta_Y);
				else if(argv[argcount][2]=='5')
		fprintf(fp,"-H5  %g  ",Table->Gamma);
        else if(argv[argcount][2]=='6')
		fprintf(fp,"-H6  %g  ",Table->Mu);
	      else if(argv[argcount][2]=='7')
		fprintf(fp,"-H7  %g  ",Table->mDelta);
	      else if(argv[argcount][2]=='8')
		fprintf(fp,"-H8  %g  ",Table->Beta_X);
        else if(argv[argcount][2]=='9')
		fprintf(fp,"-H9  %g  ",Table->p_YX);
	      else {
		printf(" Error at reading input arguments: -  %s  \n", argv[argcount]);
		exit(0);
	      }
	      skip++;
	      break;

#include <include.Type_of_Model.argumentControl_fprintf.c>
