#ifndef aa
#define aa 

void ls(){
    int hide=0,det=0,files=0;
    for (int i=1;i<cnt;i++){
        if (input[i][0]=='&'){
            execute(cnt);
            return ;
        }
        if (input[i][0]=='-'){
            for(int j=0;j<strlen(input[i]);j++){
                if (input[i][j]=='a') hide=1;
                if (input[i][j]=='l') det=1;
            }
        }
        else files++;
    }
    DIR *mydir,*mydir1;
    struct dirent *myfile;
    struct stat mystat;

    char buf[512];
    long int mx=0;
    int total=0;
    if (!files){
        mydir = opendir(".");
        while(myfile = readdir(mydir)){
            char *temp=myfile->d_name;
            if (temp[0]=='.' && !hide) continue;
            sprintf(buf, "%s/%s", ".", myfile->d_name);
            stat(buf, &mystat);
            mx=mx>mystat.st_size?mx:mystat.st_size;
            total = total + mystat.st_blocks;
        }
        if (det)
            printf("total %d\n",total/2);
        int ln=0;
        while(mx != 0){
            ln++;
            mx/=10;
        }
        if (ln > 6)
            ln=ln;
        else 
            ln = 6;
        mydir = opendir(".");
        while((myfile = readdir(mydir)) != NULL){
            char *temp=myfile->d_name;
            if (temp[0]=='.' && !hide) continue;
            if (det != 0){
                sprintf(buf, "%s/%s", ".", myfile->d_name);
                stat(buf, &mystat);
                if ((S_ISDIR(mystat.st_mode)))
                    printf("d");
                else
                    printf("-");
                if ((mystat.st_mode & S_IRUSR))
                    printf("r");
                else
                    printf("-");
                if ((mystat.st_mode & S_IWUSR))
                    printf("w");
                else
                    printf("-");
                if ((mystat.st_mode & S_IXUSR))
                    printf("x");
                else
                    printf("-");
                if ((mystat.st_mode & S_IRGRP))
                    printf("r");
                else
                    printf("-");
                if ((mystat.st_mode & S_IWGRP))
                    printf("w");
                else
                    printf("-");
                if ((mystat.st_mode & S_IXGRP))
                    printf("x");
                else
                    printf("-");
                if ((mystat.st_mode & S_IROTH))
                    printf("r");
                else
                    printf("-");
                if ((mystat.st_mode & S_IWOTH))
                    printf("w");
                else
                    printf("-");
                if ((mystat.st_mode & S_IXOTH))
                    printf("x");
                else
                    printf("-");

                nlink_t hdlink=mystat.st_nlink;
                printf("%lu ",hdlink);

                struct passwd *pw = getpwuid(mystat.st_uid);
                struct group  *gr = getgrgid(mystat.st_gid);
                printf("%s %s ", pw->pw_name, gr->gr_name);

                char *date=ctime(&mystat.st_mtime);
                len=strlen(date);
                for(int i=0;i<9;i++)
                    date[len-1-i]='\0';
                long int val=mystat.st_size;

                char sz[20];
                memset(sz,' ',sizeof(sz));
                sz[20]='\0';

                len=19;
                fz(sz,val);
                printf("%s %s ",sz+20-ln,date+4);
                printf(" %s\n", myfile->d_name);
            }
            else printf("%s\t", myfile->d_name);
        }
        if (!det) printf("\n");
        closedir(mydir);
    }
    else {
        for (int i=1;i<cnt;i++)
            if (input[i][0]!='-'){
                int flag=0;
                mydir = opendir(".");
                while(myfile = readdir(mydir)){
                    char *temp=myfile->d_name;
                    if (strcmp(temp,input[i]))
                        continue;
                    if (temp[0]=='.' && !hide) 
                        continue;
                    flag=1;
                    if (det != 0){
                        sprintf(buf, "%s/%s", ".", myfile->d_name);
                        stat(buf, &mystat);
                        if ((S_ISDIR(mystat.st_mode)))
                            printf("d");
                        else
                            printf("-");
                        if ((mystat.st_mode & S_IRUSR))
                            printf("r");
                        else
                            printf("-");
                        if ((mystat.st_mode & S_IWUSR))
                            printf("w");
                        else
                            printf("-");
                        if ((mystat.st_mode & S_IXUSR))
                            printf("x");
                        else
                            printf("-");
                        if ((mystat.st_mode & S_IRGRP))
                            printf("r");
                        else
                            printf("-");
                        if ((mystat.st_mode & S_IWGRP))
                            printf("w");
                        else
                            printf("-");
                        if ((mystat.st_mode & S_IXGRP))
                            printf("x");
                        else
                            printf("-");
                        if ((mystat.st_mode & S_IROTH))
                            printf("r");
                        else
                            printf("-");
                        if ((mystat.st_mode & S_IWOTH))
                            printf("w");
                        else
                            printf("-");
                        if ((mystat.st_mode & S_IXOTH))
                            printf("x");
                        else
                            printf("-");

                        nlink_t hdlink=mystat.st_nlink;
                        printf("%lu ",hdlink);

                        struct passwd *pw = getpwuid(mystat.st_uid);
                        struct group  *gr = getgrgid(mystat.st_gid);
                        printf("%s %s ", pw->pw_name, gr->gr_name);

                        char *date=ctime(&mystat.st_mtime);
                        len=strlen(date);
                        for(int i=0;i<9;i++)
                            date[len-1-i]='\0';
                        long int val=mystat.st_size;

                        char sz[20];
                        memset(sz,' ',sizeof(sz));
                        sz[20]='\0';

                        len=19;
                        fz(sz,val);
                        printf("%s %s ",sz+20-10,date+4);
                        printf(" %s\n", myfile->d_name);
                    }
                    else printf("%s\t", myfile->d_name);
                    break;
                }
                if (!flag)
                    fprintf(stderr,"ls: cannot access '%s': No such file or directory\n",input[i]);
                closedir(mydir);
            }
        if (det == 0)
            printf("\n");
    }
}
#endif
