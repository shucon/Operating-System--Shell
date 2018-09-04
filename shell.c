#include "display.h"
#include "input.h"
#include "cd.h"
#include "pwd.h"
#include "ls.h"
#include "echo.h"
#include "pinfo.h"
#include "global.h"

int pid = 0;

int main (void) {
    int status;
    while(1) {
        char *home = shellPrompt();
        input();
    }
    return 0;
}