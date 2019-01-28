#ifndef ba
#define ba  


void foreground_proc()
{
    int pid = fork();
	pname = pid;
    if(!pid) {
		pname=getpid();
        if(execvp(input2[0],input2) < 0){
            perror("Can't execute");
        }
    } else
        wait(NULL);
}

void background_proc()
{
    int pid = fork();
    if(!pid){
        int fd = open(paths,O_RDWR | O_APPEND);
        int i=0;
        char save[1024] = {'\0'};
        char store[1024] = {'\0'};
        while(input2[i]){
            strcat(store,input2[i++]);
            strcat(store," ");
        }
        sprintf(save,"1%d %s[%d]\n",getpid(),store,getpid());
        write(fd,save,strlen(save));
        close(fd);
        if(execvp(input2[0],input2) < 0){
            perror("Can't execute");
        }
    } else{
        fprintf(stderr,"[%d]\n",pid);
    }
}

void execute(int len)
{
    int length = strlen(input[0]);
    if (length > 1){
        int i = 0;
        for(i=0;i<len;i++){
            if(input[i][0]=='&'){
                input2[i] = NULL;
                background_proc();
                return;
            }
            else{
                input2[i] = input[i];
            }
        }
        input2[len] = NULL;
        foreground_proc();
    }
}
#endif
