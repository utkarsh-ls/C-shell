#include "headerfile.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include <sys/utsname.h>
#include <string.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <pwd.h>
#include <limits.h>

char **splitcmd(char *takecommand)
{
    char **cmdarray = malloc((sizeof(char *)) * siz);
    if (cmdarray == NULL)
    {
        exst = 1;
        printf("Malloc fails\n");
    }
    else
    {
        int pt = 0, sz = sizeof(cmdarray) / sizeof(char *);
        char *placeholder = strtok(takecommand, ";\n");
        while (placeholder != NULL)
        {
            if (pt >= sz)
            {
                cmdarray = realloc(cmdarray, siz * sizeof(char *));
                if (cmdarray == NULL)
                {
                    exst = 1;
                    printf("Realloc fails\n");
                }
            }
            cmdarray[pt] = placeholder;
            placeholder = strtok(NULL, ";\n");
            ++pt;
        }
        cmdarray[pt] = 0;
    }

    return cmdarray;
}

char **splitargs(char *command)
{
    char **argarray = malloc((sizeof(char *)) * siz);
    if (argarray == NULL)
    {
        exst = 1;
        printf("Malloc fails\n");
    }
    else
    {
        int pt = 0, sz = sizeof(argarray) / sizeof(char *);
        char *placeholder = strtok(command, " \t");
        while (placeholder != NULL)
        {
            if (pt >= sz)
            {
                argarray = realloc(argarray, siz * sizeof(char *));
                if (argarray == NULL)
                {
                    exst = 1;
                    printf("Realloc fails\n");
                }
            }
            argarray[pt] = placeholder;
            placeholder = strtok(NULL, " ");
            ++pt;
        }
        argarray[pt] = 0;
    }
    return argarray;
}

int checkand(char **execmd)
{
    int retflag = 0, i = 1;
    int k = strlen(execmd[0]);
    if (execmd[0][k - 1] == '&')
        retflag = 1;
    while (execmd[i])
    {
        if (!strcmp(execmd[i], "&"))
        {
            execmd[i] = NULL;
            retflag++;
        }
        i++;
    }
    return retflag;
}

int checklogical(char **execmd)
{
    int retflag = 0, i = 1;
    int k = strlen(execmd[0]);
    if ((execmd[0][k - 1] == '@') || (execmd[0][k - 1] == '$'))
        retflag = 1;
    while (execmd[i])
    {
        if (!strcmp(execmd[i], "@") || !strcmp(execmd[i], "$"))
        {
            execmd[i] = NULL;
            retflag++;
        }
        i++;
    }
    return retflag;
}

void execute(char *cmd)
{
    int flag = 0, i;
    char cmdcpy[1024];
    char **execmd;
    cmdcpy[0] = 0;
    if (cmd[0] != ' ' && cmd[0] != '\0')
        addhis(cmd);

    strcpy(cmdcpy, cmd);
    int pipeflag = 0;
    int pipcheck = 0;
    execmd = splitargs(cmd);
    if (execmd[0] == NULL)
        return;
    // printf("This is %s\n",cmdcpy);
    // i=0;
    // while(execmd[i] != NULL)
    //     printf("here %s\n",execmd[i++]);
    int logical_no = checklogical(execmd);
    if(logical_no)
    {
        logical(cmdcpy);
        return;
    }
    
    int check1,check2,check3,check4;

    while (execmd[pipcheck])
    {
        check1 = strcmp(execmd[pipcheck], ">>");
        check2 = strcmp(execmd[pipcheck], ">");
        check3 = strcmp(execmd[pipcheck], "|");
        check4 = strcmp(execmd[pipcheck], "<");
        if ((check1 == 0) || (check2 == 0) || (check3 == 0) || (check4 == 0))
        {
            pipeflag++;
            tagpiper(cmdcpy);
            break;
        }
        pipcheck++;
    }
    // printf("%d\n",and_no);
    if (pipeflag == 0)
    {
        flag = 0;
        int and_no = checkand(execmd);

        // printf("%d\n",and_no);
        if (!strcmp(execmd[0], "exit") || !strcmp(execmd[0], "quit"))
        {
            exhis();
            exit(0);
        }
        else
        {
            for (i = 0; i < 14; i++)
            {
                if (strcmp(execmd[0], cmdlist[i]) == 0)
                {
                    switch (i)
                    {
                    case 0:
                        cd(execmd);
                        break;
                    case 1:
                        pwd();
                        break;
                    case 2:
                        echo(execmd);
                        break;
                    case 3:
                        ls(execmd);
                        break;
                    case 4:
                        pinfo(execmd);
                        break;
                    case 5:
                        nightswatch(execmd);
                        break;
                    case 6:
                        history(execmd);
                        break;
                    case 7:
                        seten(execmd);
                        break;
                    case 8:
                        unseten(execmd);
                        break;
                    case 9:
                        bghand(execmd);
                        break;
                    case 10:
                        jobs(execmd);
                        break;
                    case 11:
                        killemall(execmd);
                        break;
                    case 12:
                        kjobs(execmd);
                        break;
                    case 13:
                        fg(execmd);
                        break;
                    default:
                        break;
                    }
                    flag = 1;
                }
            }
            if (flag == 0)
                unimplemented(execmd, and_no);
        }
    }
}

void init()
{
    for (int i = 0; i < 14; i++)
    {
        switch (i)
        {
        case 0:
            strcpy(cmdlist[i], "cd");
            break;
        case 1:
            strcpy(cmdlist[i], "pwd");
            break;
        case 2:
            strcpy(cmdlist[i], "echo");
            break;
        case 3:
            strcpy(cmdlist[i], "ls");
            break;
        case 4:
            strcpy(cmdlist[i], "pinfo");
            break;
        case 5:
            strcpy(cmdlist[i], "nightswatch");
            break;
        case 6:
            strcpy(cmdlist[i], "history");
            break;
        case 7:
            strcpy(cmdlist[i], "setenv");
            break;
        case 8:
            strcpy(cmdlist[i], "unsetenv");
            break;
        case 9:
            strcpy(cmdlist[i], "bg");
            break;
        case 10:
            strcpy(cmdlist[i], "jobs");
            break;
        case 11:
            strcpy(cmdlist[i], "overkill");
            break;
        case 12:
            strcpy(cmdlist[i], "kjob");
            break;
        case 13:
            strcpy(cmdlist[i], "fg");
            break;
        default:
            break;
        }
    }
}

char *commandexec(char *takecommad)
{
    char **cmdarray;
    int i = 0;

    init();
    cmdarray = splitcmd(takecommad);
    while (cmdarray[i] != NULL)
    {
        if (strcmp(cmdarray[0], " ") == 0 || strcmp(cmdarray[0], "\t") == 0)
            return 0;
        // printf("Here we go %s\n",cmdarray[i]);
        execute(cmdarray[i]);
        i++;
    }
}
