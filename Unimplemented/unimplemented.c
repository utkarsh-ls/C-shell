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
#include <signal.h>
#include <wait.h>
#include "../headerfile.h"

void backquit1(int);
void unimplemented (char ** execmd ,int checkand)
{
    pid_t proccessid;
    int i=0,pt;
    proccessid=fork();
    // printf("process %d\n",proccessid);
    if (!proccessid)
    {
        setpgid(0, 0);
        pt = execvp(execmd[0],execmd);
        if(pt==-1)
        {
            perror("could not execute");
            // printf(":'(");
            exit(1);
        }
        else
        {
            // printf(":')");
            exit(0);
        }
    }
    else if (proccessid > 0)
    {
        // printf("\n%d\n",checkand);
        if (checkand)
        {
            signal(SIGCHLD, backquit);
            printf("process %s with pid %d started \n",execmd[0],proccessid);
            exst=0; // check here
            backarray[backpointer].status=1;
            backarray[backpointer].command=execmd[0];
            backarray[backpointer].index=backpointer;
            backarray[backpointer].pid=proccessid;
            backpointer++;
            setpgid(proccessid,0);
            tcsetpgrp(STDIN_FILENO,getpgrp());
        }
        else 
        {
            runproc.command=execmd[0];
            runproc.index=backpointer;
            runproc.pid=proccessid;

            //    printf("THERE IS NO & !! WAIT \n");
                
            signal(SIGTTIN,SIG_IGN);
            signal(SIGTTOU,SIG_IGN);
            
            signal(SIGCHLD, null);

            tcsetpgrp(0,proccessid);
            waitpid(proccessid,&i,WUNTRACED);
            if(i==0)
                exst=0;
            else
                exst=1;

            tcsetpgrp(0,getpgid(0));
            
            signal(SIGTTIN,SIG_DFL);
            signal(SIGTTOU,SIG_DFL);

            if (WIFSTOPPED(i)!=0)
            {
                backarray[backpointer].pid = runproc.pid;
                backarray[backpointer].command = runproc.command ;
                backarray[backpointer].status=2;
                exst=1;
                
                printf("process %d sent to background \n",backarray[backpointer].pid);
                backpointer++;

                runproc.pid=0;
            }
        }
    }
    else
    {
        exst=1;
        printf("Error in forking");
    }
}

void backquit(int somesig)
{
    int status,i;
    pid_t pid = waitpid (-1,&status,WNOHANG);
    if (pid)
    {
        for (i=0;i<backpointer;i++)
        {
            if (backarray[i].pid==pid && WIFEXITED(status))
            {
                if (WEXITSTATUS(status)==EXIT_FAILURE) 
                {
                    fprintf(stderr,"\033[35m \n%s ",backarray[i].command);
                    fprintf(stderr,"with pid %d exited abnormally\n\033[0m",pid);
                    // exst=1;
                }
                else
                {
                    fprintf(stderr,"\033[32m \n%s ",backarray[i].command);
                    fprintf(stderr,"with pid %d exited normally\n\033[0m",pid);
                    // exst=0;
                }
            }
        }      
    }
    fflush(stdout);
}
