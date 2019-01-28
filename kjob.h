#ifndef kj
#define kj

void kjob(){
	FILE *fp = NULL;
	fp = fopen(paths,"r+");
	int calc,counter;
	counter = 0;
	while(1 == 1){
		char st[1024];
		fgets(st,200,fp);
		if (st[0] != 0)
			counter++;
		if(feof(fp))
			break;
		int l = strlen(st+1);
		char store[1024] = {'\0'};
		for(int i=1;st[i]!=' ';i++){
			store[i-1] = st[i];
		}
		int val = calculater(store,strlen(store)+1);
        if (input[1][0])
			calc=input[1][0]-48;
		else
			calc=0;
        if (input[1][1])
			calc=(calc*10)+input[1][1]-48;
		if(counter == calc){
			int calcul;
        	if (input[2][0])
				calcul=input[2][0]-48;
			else
				calcul=0;
        	if (input[2][1])
				calcul=((calcul*10)+input[2][1])-48;
			printf("val:%d cal:%d\n",val,calcul);
			kill(val,calcul);
			break;
		}
	}
	if(counter != input[1][0]-'0'){
		perror("Invalid no of inputs");
	}
	fclose(fp);
}
#endif
