#ifndef za
#define za  

int implement_cd(){
    char ch[100]={'\0'};
    char save[1024];
    save[1023] = '\0';
    strcpy(ch,input[1]);
    if(!strlen(ch)){
		if(chdir(cwd) < 0)
			perror("cd failed");
        return 1;
    } else if(ch[0] == '~'){
        strcpy(save,cwd);
        strcat(save,"/");
        strcat(save,ch+1);
		if(chdir(save) < 0)
			perror("cd failed");
        return 1;
    }
    if(ch[0]!='/'){
        getcwd(save,sizeof(save));
        strcat(save,"/");
        strcat(save,ch);
		if(chdir(save) < 0)
			perror("cd failed");
        return 1;
    } else {
		if(chdir(ch) < 0)
			perror("cd failed");
        return 1;
    }
}
#endif
