#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include <sys/utsname.h>
#include <string.h>
#include <fcntl.h>
#include <pwd.h>

#include "../headerfile.h"

void killemall(char ** args)
{
    if(args[1]!=NULL)
    {
        printf("Too many argiments\n");
        exst=1;
        return;
    }
    int i;
    for (i=0;i<backpointer;i++)
    {
        backarray[i].status=0;
        kill(backarray[i].pid,9);
    }
    backpointer=0;
    exst=0;
}
