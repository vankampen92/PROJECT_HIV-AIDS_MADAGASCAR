
case 'y': /* Type Control Definition */ 
	      if(argv[argcount][2]=='0')
		sscanf(argv[argcount+1],"%d",&TYPE_of_MODEL);
              else if(argv[argcount][2]=='1')
		sscanf(argv[argcount+1],"%d",&Growth_Function_Type);
              else exit(0);
	      skip++;
	      break;

