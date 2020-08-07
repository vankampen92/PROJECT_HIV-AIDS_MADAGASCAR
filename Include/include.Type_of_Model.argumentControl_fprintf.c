
case 'y': /* Type Control Definition */
	      if(argv[argcount][2]=='0')
		fprintf(fp,"-y0  %d  ",Table->TYPE_of_MODEL);
              else if(argv[argcount][2]=='1')
		fprintf(fp,"-y1  %d  ",Table->Growth_Function_Type);
              else exit(0);
	      skip++;
	      break;
