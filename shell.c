#include <syscall.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <pwd.h>
#include <string.h>
#include <limits.h>
#include <netdb.h>

int shellPrompt () {
    struct passwd *pw = getpwuid(getuid());
    const char *homedir = pw->pw_dir;
    int lenHome = strlen(homedir);
    char hostname[HOST_NAME_MAX];
    gethostname(hostname, HOST_NAME_MAX);
    char cwd[100];
    getcwd(cwd, sizeof(cwd));
    int i, flag = 0;
    for (i = 0; i < lenHome; i++) {
        if (homedir[i] != cwd[i])
            flag = 1;
    }
    if  (flag == 0) {
        int cwdLen = strlen(cwd);
        char temp[100];
        temp[0] = 126;
        for (i = lenHome; i < cwdLen; i++) {
            temp[i - lenHome + 1] = cwd[i];
        }
        strcpy(cwd, temp);
    }
    if (cwd != NULL) {
        printf("<%s@%s:%s>\n", pw->pw_name, hostname, cwd);
    } else {
        perror("getcwd() error");
        return 1;
    }
}

int main (void) {
    shellPrompt();
    return 0;
}