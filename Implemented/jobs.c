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

void checkallkill()
{
    int i = 0, flag = 0;
    char str[hsiz];
    while ((backpointer - i) > 0)
    {
        sprintf(str, "/proc/%d/status", backarray[i].pid);
        i++;
        FILE *file = fopen(str, "r");
        if (file)
        {
            flag = 1;
            break;
        }
    }
    if (flag == 0)
        backpointer = 0;
}

void jobs(char **args)
{
    char str[hsiz];
    int i = 0, count;
    FILE *file;
    checkallkill();
    if (args[1])
    {
        printf("Too many arguments\n");
        exst=1;
        // printf(":'(");
        return;
    }
    while ((backpointer - i) > 0)
    {
        sprintf(str, "/proc/%d/status", backarray[i].pid);
        file = fopen(str, "r");
        // printf("YEp %d\n",i);
        if (file == NULL)
        {
            i++;
            continue;
        }

        count = 0;
        char buff[150];
        int z_flag=0;
        while (fgets(buff, sizeof(buff), file))
        {
            if (count == 1)
            {
                int icount = 0;
                while (buff[icount] != ' ')
                    icount++;

                if(buff[icount-1]=='Z' && buff[0]=='S')
                    z_flag=1;
                
            }
            else if (count == 2 && z_flag==0)
            {
                printf("[%d] ", i);
                // Process Status
                int icount = 0;
                while (buff[icount] != ' ')
                    icount++;

                if (buff[icount - 1] == 'T')
                {
                    printf("Stopped ");
                }
                else
                {
                    printf("Running ");
                }
                break;
            }
            count++;
        }
        if(!z_flag)
        {
            printf("%s ", backarray[i].command);
            printf("[%d]\n", backarray[i].pid);
        }
        i++;
    }
    exst=0;
    // printf(":')");
}

void kjobs(char **args)
{
    if (args[1] == NULL)
    {
        printf("Too few arguments\n");
        exst=1;
        // printf(":'(");
    }
    else if (args[2] == NULL)
    {
        printf("Too few arguments\n");
        exst=1;
        // printf(":'(");
    }
    else if (args[3] == NULL)
    {
        int jobnumb = atoi(args[1]);
        int signl = atoi(args[2]);
        if ((jobnumb >= backpointer) || (backarray[jobnumb].status == 0))
        {
            printf("No such process exists\n");
            exst=1;
            // printf(":'(");
        }
        else
        {
            int procid = backarray[jobnumb].pid;
            printf("%d %d \n", procid, signl);
            int kil_err = kill(procid, signl);
            if (kil_err == -1)
            {
                perror("Error");
                exst=1;
                // printf(":'(");
            }
            else
            {
                exst=0;
                // printf(":')");
            }
        }
        checkallkill();
    }
    else
    {
        printf("Too many Arguments\n");
        exst=1;
        // printf(":'(");
    }
    return;
}

void fg(char **args)
{
    int status;
    int jobid;
    pid_t wpid;
    if (args[1] == NULL)
        jobid = backpointer - 1;
    else if (args[2] == NULL)
    {
        jobid = atoi(args[1]);
        if(jobid >= backpointer || jobid < 0 || backpointer==0)
        {
            printf("No such job exists\n");
            exst=1;
            return;
        }
    }
    else
    {
        printf("Too Many Arguments\n");
        exst=1;
        // printf(":'(");
        return;
    }
    setpgid(backarray[jobid].pid, getpgid(0));
    runproc.pid = backarray[jobid].pid;
    signal(SIGTTIN, SIG_IGN);
    signal(SIGTTOU, SIG_IGN);
    tcsetpgrp(STDIN_FILENO, runproc.pid);

    int stat;
    int kil_err = kill((runproc.pid), SIGCONT);
    if (kil_err == -1)
    {
        perror("Error");
        exst=1;
        // printf(":'(");
        return;
    }
    backarray[jobid].status = 3;

    waitpid(runproc.pid, &stat, WUNTRACED);
    tcsetpgrp(STDIN_FILENO, getpgrp());

    signal(SIGTTIN, SIG_DFL);
    signal(SIGTTOU, SIG_DFL);
    printf("%d\n", getpgrp());
    exst=0;
    // printf(":')");
}
