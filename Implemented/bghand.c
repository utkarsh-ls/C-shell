#include <string.h>
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

void bghand(char **args)
{
    int jobid;
    if (args[1]==NULL)
        jobid = backpointer-1;
    else if (args[2]==NULL)
        jobid = atoi(args[1]);
    else
    {
        printf("Too many arguments\n");
        // printf(":'(");
        exst=1;
        return;
    }
    if (jobid >= backpointer)
    {
        printf("No such job exists\n");
        exst=1;
        // printf(":'(");
    }
    else if (jobid < 0)
    {
        printf("No such job exists\n");
        exst=1;
        // printf(":'(");
    }
    else if (backarray[jobid].status == 0)
    {
        printf("No such job exists \n");
        exst=1;
        // printf(":'(");
    }
    else
    {
        if (kill(backarray[jobid].pid, 18) == -1)
        {
            perror("Error");
            exst=1;
            // printf(":'(");
        }
        else
        {
            backarray[jobid].status = 1;
            exst=0;
            // printf(":')");
        }
    }
}
