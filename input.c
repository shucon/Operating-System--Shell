#include "input.h"

void Ctoken (char* string, char** output, char* omitter) {
	char* token;
	token=strtok(string,omitter);
	int lp=0;
	while ((token)!=NULL) {
		output[lp]=token;
		token=strtok(NULL,omitter);
		lp=lp+1;
	}
}

extern int pid;

void input() {
	int sts = 0;
	pid_t p;
	if (pid != 0) {
		if ((p=waitpid(-1, &sts, WNOHANG)) == -1) {
			printf("pid %d exited normally \n",pid);
			pid = 0;
		}
	}
	int temp;
	int background = 0;
	int counter = 0;
    char command[500];
	char* storeColon[100]={NULL};
	fgets(command,500,stdin);
    // Tokenize commands seperated by ';'
	Ctoken(command,storeColon,";");
    while (storeColon[counter] != NULL) {
		char array[500];
		strcpy(array,storeColon[counter]);
		if (array[strlen(array)-1] == '\n')    
			array[strlen(array)-1] = '\0';
		char* new_str[100]={NULL};
		Ctoken(array,new_str," \t\n");
		int t=0;
        // Calculate number of commands after tokenising tabs
		while (new_str[t])
			t++;
        // Check if the commands should be running in background
		if (new_str[t-1]) {
		    if(new_str[0] != '\0' && (!strcmp(new_str[t-1] ,"&"))) {
		    	new_str[t-1] = NULL ; 			
		    	background = 1;
		    }
        }
		if (background){
			pid = fork();
			if(pid != 0 ) {
				printf ("Waiting on child (%d).\n", pid);
			}
			else if (pid <0) {
				exit (1);
			}
			else {	
				execvp(*new_str , new_str);
				exit(1);
			}
	    } else if(new_str[0]!='\0') {
			if (!strcmp(new_str[0], "exit"))
                exit(0);
			else if(!strcmp(new_str[0],"cd"))
				checkCd(new_str);
			else if(!strcmp(new_str[0],"pwd"))
				checkPwd();
			else if(!strcmp(new_str[0],"ls"))
				checkLs(new_str);					
			else if(!strcmp(new_str[0],"echo"))
				checkEcho(new_str);					
			else if(!strcmp(new_str[0],"pinfo"))
				CheckPinfo(new_str);
			else {
				temp = fork(); 
				int status;
				if(temp == 0) { 
					if(execvp(*new_str, new_str) < 0) 
						printf("Input error: Command not found!\n");
				}
				else 
					waitpid(temp,&status,WUNTRACED);
			}   
		}
        counter++;
    }
}