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
#include <limits.h>
#include "../headerfile.h"

#define no_change -1

char **splitpipe(char *command)
{
    char **ret = malloc(100 * sizeof(char *));
    if (ret == NULL)
    {
        printf("Malloc fails \n");
        exst=1;
    }
    else
    {
        int pt = 0, sz = sizeof(ret) / sizeof(char *);
        char *placeholder = strtok(command, "|");
        while (placeholder != NULL)
        {
            if (pt >= sz)
            {
                ret = realloc(ret, 100 * sizeof(char *));
                if (ret == NULL)
                {
                    printf("realloc fails again\n");
                    exst=1;
                }
            }
            ret[pt] = placeholder;
            placeholder = strtok(NULL, "|");
            ++pt;
        }
        ret[pt] = NULL;
    }
    return ret;
}

void pipeexec(char **args)
{

    char *execmd[1024];

    int j = 0, k = 0;
    while (args[k] != NULL)
    {
        if (strcmp(args[k], ">") && strcmp(args[k], ">>") && strcmp(args[k], "<"))
        {
            if(k>0)
            {
                if (strcmp(args[k-1], ">") && strcmp(args[k-1], ">>") && strcmp(args[k-1], "<"))
                {
                    execmd[j] = args[k];
                    j++;        
                }

            }
            else
            {
                execmd[j] = args[k];
                j++;
            }
            // printf("This is %s\n",args[k]);
        }
        k++;
    }
    execmd[j] = 0;
    int and_no = checkand(execmd);

    int i, flag = 0;
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

void tagpiper(char *args)
{
    int stdindup = dup(STDIN_FILENO);
    int stdoutdup = dup(STDOUT_FILENO);
    exst=0;
    char **cmds = splitpipe(args);

    int p = 0, cnt = 0;
    while (cmds[cnt])
    {
        cnt++;
    }

    while (cmds[p] != NULL)
    {
        char **args = splitargs(cmds[p]);
        int outpos, appos, inpos = outpos = appos = no_change;
        int i = 0;
        int pipearr[2];
        while (args[i] != NULL)
        {
            if (strcmp(args[i], "<") == 0)
                inpos = i;
            if (strcmp(args[i], ">") == 0)
                outpos = i;
            if (strcmp(args[i], ">>") == 0)
                appos = i;
            i++;
        }
        int fdin, fdout, fdapp;
        if (inpos != no_change)
        {
            fdin = open(args[inpos + 1], O_RDONLY);
            if (fdin == no_change)
            {
                perror("redirection");
                exst=1;
                return;
            }
            else
                dup2(fdin, STDIN_FILENO);
        }
        if (outpos != no_change)
        {
            fdout = open(args[outpos + 1], O_WRONLY | O_TRUNC | O_CREAT, 0644);
            if (fdout == no_change)
            {
                perror("redirection ");
                exst=1;
                return;
            }
            else if (appos == no_change)
                dup2(fdout, STDOUT_FILENO);
            else
            {
                printf("Invalid command , cannot have both > and >> \n");
                exst=1;
                break;
            }
        }
        else if (appos != no_change)
        {
            fdapp = open(args[appos + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
            if (fdapp == no_change)
            {
                perror("redirection");
                exst=1;
                return;
            }
            else
                dup2(fdapp, STDOUT_FILENO);
        }

        // printf("something %s oh\n", cmds[p]);
        if (p == cnt - 1)
            pipeexec(args);
        else
        {
            pipe(pipearr);
            dup2(pipearr[1], STDOUT_FILENO);
            pipeexec(args);
            dup2(pipearr[0], STDIN_FILENO);
            dup2(stdoutdup, STDOUT_FILENO);
            close(pipearr[1]);
        }
        p++;
    }

    dup2(stdindup, STDIN_FILENO);
    dup2(stdoutdup, STDOUT_FILENO);
    close(stdindup);
    close(stdoutdup);
}
