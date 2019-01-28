
#ifndef ajsi
#define ajsi
int getwords(char *inpt){
	cnt=0;
	char *ch = strtok (inpt,"\" \t");
	while (ch){
		strcpy(input[cnt++],ch);
		ch = strtok (NULL, " \"\t");
	}
	return cnt;
}

void verify_cmd(char *inpt){
	cnt = getwords(inpt);
	int fd,i,pos1 =(-1),pos2=(-1);
	int fl = cnt;
	for(i=0;i<cnt;i++)
	{
		if(input[i][0] == '<')
		{
			fd=open(input[i+1], O_RDONLY);
			if(fd < 0) {
				perror("fd error");
				return ;
			} else if(dup2(fd,0) == -1) {
				perror("dup error");
				return ;
			}
			close(fd);
			pos1 = i;
			if(pos1 < fl)
				fl = pos1;
		}
		else if(input[i][0] == '>')
		{
			if(input[i][1] == '>')
				fd=open(input[i+1],O_CREAT | O_WRONLY |O_APPEND, 0666);
			else{
				fd=open(input[i+1], O_CREAT | O_WRONLY | O_TRUNC, 0666);
			}
			if(fd < 0) {
				perror("fd error");
				return ;
			} else if(dup2(fd,1) == -1) {
				perror("dup error");
				return ;
			}
			close(fd);
			pos2 = i;
			if(pos2 < fl)
				fl = pos2;
		}
	}
	if(pos1 != -1)
		memset(input[pos1],0,sizeof(input[pos1]));
	if(pos2 != -1)
		memset(input[pos2],0,sizeof(input[pos2]));
	cnt = fl;
	if (!strcmp(input[0], "cd")){
		implement_cd();
	}
	else if (!strcmp(input[0],"c")) {
        strcpy(input[0],"clear");execute(cnt);
    }
	else if (!strcmp(input[0],"echo")) {
		echo();
		printf("\n");
	}
	else if (!strcmp(input[0],"pwd")){
		char temp[1023] = {'\0'};
		getcwd(temp,sizeof (temp));
		printf("%s\n",temp);
	}
	else if (!strcmp(input[0],"ls")){
		ls();
	}
	else if(!strcmp(input[0],"pinfo")){
		if(!strlen(input[1])){
			pin(1);
		}
		else{
			pin(0);
		}
	}
	else if(!strcmp(input[0],"quit")){
		exit(0);
	}
	else if(!strcmp(input[0],"setenv")){
		if(cnt!=2 && cnt!=3){
			perror("input error");
			return;
		}
		else setenv(input[1],input[2],1);
	}
	else if(!strcmp(input[0],"unsetenv")){
			if(cnt!=2){
				perror("input error");
				return;
			}
			else unsetenv(input[1]);
	}
	else if(!strcmp(input[0],"jobs")){
		jobs();
	}
	else if(!strcmp(input[0],"overkill")){
		overkill();
	}
	else if(!strcmp(input[0],"kjob")){
		if(cnt!=3){
			perror("invalid input format");
			return;
		}
		kjob();
	}
	else if(!strcmp(input[0],"fg")){
		fg();
	}
	else if(!strcmp(input[0],"bg")){
		bg();
	}
	else{
		execute(cnt);
	}
	dup2(in,0);
	dup2(out,1);
}
#endif
