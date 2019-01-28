int pipeLoop(char *inpt) {
    char *comms[1024];
    for(int i=0;i<1024;i++){
        comms[i] = (char *)malloc(sizeof(char) * 1024);
        memset(comms[i],0,sizeof(comms[i]));
    }
    int cntr=0;
    cnt = getwords(inpt);
    for(int i=0;i<cnt;i++){
        if(input[i][0]!='|'){
            char buff[105]={'\0'};
            sprintf(buff," %s",input[i]);
            strcat(comms[cntr],buff);
        } else
            cntr++;
    }
    int sttarr[cntr+1];
    int status; 
    int pipfsz = (cntr) * 2; 
    int pipes[pipfsz];
    int return_value = -1;

    pid_t waitresult;
    pid_t forkArr[cntr+1];

    for (int i = 0; i < pipfsz; i += 2)
        pipe(pipes + i);
    
    for (int i = 0; i < cntr+1; i++) {
        if ((forkArr[i] = fork()) == -1) {
            perror("Pipes fork error ");
            exit(-1);
        }
        if (!forkArr[i]) {
            if (!i) {
                dup2(pipes[1], 1);
            } else if (i == cntr) {
                dup2(pipes[2 * cntr - 2], 0);
            } else {
                dup2(pipes[2 * (i - 1)], 0);
                dup2(pipes[(2 * i) + 1], 1);
            }
            for(int i=0;i<pipfsz;i++)
                close(pipes[i]); 
            verify_cmd(comms[i]);
            exit(0);
        }
    }
    for(int i=0;i<pipfsz;i++)
        close(pipes[i]); 
    for (int i = 0; i < cntr+1; i++) {
        waitresult = waitpid(forkArr[i], &status, WUNTRACED);
        sttarr[i] = status;
    }
    if (!sttarr[cntr]) {
        return_value = 0;
    }
    return 0;
}
