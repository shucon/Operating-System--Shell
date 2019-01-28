#ifndef ya
#define ya  

void pin(int self){
	FILE * fp=NULL;
	char save[1024]={'\0'};
	char str[1024] = "/proc";
	char pid[20];		
	if(self!=1){
		sprintf(pid,"/%s",input[1]);
	}
	else{
		sprintf(pid,"/%d",getpid());
	}
	char buff[2000];
	strcat(str,pid); // /proc/<pid>
	strcpy(save,str); // /proc/<pid>
	strcat(save,"/status"); // /proc/<pid>/status
	strcat(str,"/exe"); // str = /proc/<pid>/exe
	fp = fopen(save,"r");
	if(!fp){
		perror("File Not Opened");
		return;
	}
	char store[200],scanner[200],proc_status[200],virt_mem[200];;
	int len = 0;
	while(1 == 1){
		fgets(store,200,fp);
		if(strstr(store,"State")){
			sprintf(proc_status,"%s",store+7);
		}
		else if(strstr(store,"VmSize")){
			sprintf(virt_mem,"%s",store+8);
			break;
		}
	}
	ssize_t ret = readlink(str, buff, 512);
	if (ret < 0){
		perror("readlink");
	}
	else 
		buff[ret] = 0;
	printf("pid -- %d\n",getpid());
	printf("Process Status -- %s",proc_status);
	printf("Virtual Memory -- %s",virt_mem);
	if(strstr(buff,cwd)!=NULL){
		int cwdlen = strlen(cwd);
		printf("Executable Path -- %s\n",buff+cwdlen);
	}
	else {
		printf("Executable Path -- ~%s\n",buff);
	}
	if(fp){
		fclose(fp);
		fp = NULL;
	}
}
#endif
