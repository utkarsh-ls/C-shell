#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <pwd.h>
#include <limits.h>
#include <string.h>
#include <signal.h>

#include "headerfile.h"

void red()
{
    printf("\33[1;31m");
}
void yellow()
{
    printf("\33[1;33m");
}
void reset()
{
    printf("\33[0m");
}

void getdir()
{
    char currentdir[FILENAME_MAX];
    char pathexec[FILENAME_MAX];
    char temp[FILENAME_MAX];
    
    getcwd (currentdir,sizeof(currentdir));
    // if(check<0)
    //     perror("Error");

    int home_path_len = strlen(home);
    int curr_path_len = strlen(currentdir);


    int i,flag=0,pos=0;
    if (curr_path_len < home_path_len)
    {
        yellow();
        printf("%s",currentdir);
        reset();
    }
    else
    {
        for(i=0;i<home_path_len;i++,pos++)
        {
            if(home[i]!=currentdir[i])
            {
                pos=0;
                flag=1;
                break;
            }
        }
        yellow();
        if(flag==0)
            printf("~");
        printf("%s",currentdir+pos);
        reset();
    }
    printf("> ");
}

void print_prompt ()
{
    char host[100];
    char  username[100];
    while(1)
    {
        size_t cmdlength = 0;
        ssize_t line;
		char *takecommand;
        if(exst==0)
            printf(":')");
        else if(exst==1)
            printf(":'(");
        exst=2;
        getlogin_r (username,sizeof(username));
        // if (check<0)
        //     perror("Error");
        gethostname(host,sizeof(host));
        printf("<");
        red();
        printf("%s@%s",username,host);
        reset();
        printf(":");
        strcpy(name,"<");
        strcat(name,username);
        strcat(name,"@");
        strcat(name,host);
        strcat(name,":");
        getdir();
        line = getline(&takecommand,&cmdlength,stdin);
		if(line==EOF)
        {
            printf("\n");   
            break;  //take command as input
        }
        commandexec(takecommand);
    }
}

int main()
{
    inithist();
    mypid = getpgrp();
    backpointer=0;
    exst=2;
    getcwd(home,sizeof(home));
    signal(SIGTSTP,null);
    signal(SIGQUIT,null);
    signal(SIGINT,null);
    strcpy(prevdir,home);
    print_prompt();
    return 0;
}