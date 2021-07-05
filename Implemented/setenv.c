#include "../headerfile.h"
#include <stdio.h>
#include <stdlib.h>

void seten(char ** args)
{
    exst=0;
    if (args[1]==NULL)
    {
        printf("Specify variable to set\n");
        exst=1;
    }
    else if (args[2]==NULL) 
    {
        if (setenv(args[1],"",1)<0)
        {
            perror("setenv error");
            exst=1;
        }
    }
    else if (args[3]==NULL)
    {
        if (setenv (args[1],args[2],1)<0)
        {
            perror("setenv error");
            exst=1;
        }
    }
    else
    {
        printf("Too many arguments\n");
        exst=1;
    }
}

void unseten(char ** args)
{
    exst=0;
    if (args[1]!=NULL && args[2]==NULL)
    {
        if (unsetenv(args[1])<0)
        {
            perror("unsetenv error");
            exst=1;
        }
    }
    else
    {
        printf("Invalid input\n");
        exst=1;
    }
}
