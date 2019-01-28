#ifndef fgbg
#define fgbg

void bg(){
	FILE *fp = NULL;
	fp = fopen(paths,"r+");
	int calc,counter,status;
	counter = 0;
	status = 0;
	while (1 == 1){
		char st[1024];
		fgets(st,200,fp);
		if(st[0]!=0)
			counter++;
		else
			counter;
		if(feof(fp) != 0)
			break;
		char store[1024] = {'\0'};
		for(int i=1;st[i]!=' ';i++)
			store[i-1] = st[i];
        if (input[1][0]!=0)
			calc=input[1][0]-48;
		else 
			calc = 0;
		int val = calculater(store,strlen(store)+1);
        if (input[1][1]!=0) calc=(calc*10)+input[1][1]-48;
		if(counter==calc){
			kill(val,SIGCONT);
			break;
		}
	}
	if(counter == calc){
		int temp = 0;
	} else {
		perror("Number of inputs is invalid");
	}
	fclose(fp);
}

void fg(){
	int calc,counter,status;
	counter = 0;
	status = 0;
	FILE *fp = NULL;
	fp = fopen(paths,"r+");
	while(1 == 1){
		char st[1024];
		fgets(st,200,fp);
		if(st[0]!=0)
			counter++;
		else
			counter;
		if(feof(fp) != 0) 
			break;
		char store[1024] = {'\0'};
		for(int i=1;st[i]!=' ';i++){
			store[i-1] = st[i];
		}
		int val = calculater(store,strlen(store)+1);
        if (input[1][0]!=0)
			calc=input[1][0]-48;
		else 
			calc = 0;
        if (input[1][1])
			calc = ((calc*10) + input[1][1])-48;
		if(counter != calc){
			continue;	
		} else {
			printf("Transferred to foreground\n");
			kill(val,SIGCONT);
			int ret=waitpid(val,&status,WUNTRACED);
			break;
		}
	}
	if(counter == calc){
		int temp = 0;
	} else {
		perror("Number of inputs is invalid");
	}
	fclose(fp);
}

#endif
