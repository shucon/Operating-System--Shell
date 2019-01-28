void child_handler(int sig) {
	pid_t pid;
	int status;
	while((pid = waitpid(-1, &status, WNOHANG)) > 0); 
}
void sighandler(int sig_num) {
	if (pname) {
		kill(pname,SIGTSTP);
        int fd = open(paths,O_RDWR | O_APPEND);
        int i=0;
        char store[1024] = {'\0'};
        char save[1024] = {'\0'};
        while(input2[i]){
            strcat(store,input2[i++]);
            strcat(store," ");
        }
        sprintf(save,"1%d %s[%d]\n",pname,store,pname);
		pname=0;
        write(fd,save,strlen(save));
        close(fd);
		kill(pname,SIGCONT);
	}
}
void handle_signals(int signo) {
	if (signo == SIGINT) {   
		printf("\n");
		siglongjmp(ctrlc_buf, 1); 
	}   
}