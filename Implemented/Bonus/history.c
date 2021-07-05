#include "../../headerfile.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <pwd.h>
#include <limits.h>
#include <string.h>
#include <signal.h>

void addhis(char* cmd)
{
    strcpy(his.history[(his.histins++)%20],cmd);
}

void exhis()
{
    FILE * hfile;
    hfile=fopen(his_path,"wb");
    fwrite(&his, hsiz, 1, hfile);
    fclose(hfile);
    exit(0);
}

void inithist()
{
    FILE * hfile;
    char currentdir[siz];

    getcwd(currentdir,sizeof(currentdir));
    strcat(currentdir,"/.history");
    strcpy(his_path,currentdir);
    hfile=fopen(his_path,"rb");
    if (hfile)
    {
        fread(&his, hsiz, 1, hfile);
        fclose(hfile);
    }
    else
    {
        his.histins=0;
        his.histed=0;
    }
}

void history(char** cmd)
{
    exst=0;
    int n=10,i;
    if (cmd[1])
        n = atoi(cmd[1]);
    if(n>20)
        n=20;
    if((cmd[1] != NULL) && (strcmp(cmd[1],"0")!=0) && (n==0))
    {
        exst=1;
        printf("Provide numeric arguments\n");
    }
    i=n+1;
    while ((i--)>1)
    {
        int k = (his.histins-i+20)%20;
        if (his.history[k] && strlen(his.history[k]))
        {
            printf("%s\n",his.history[k]);
        }
    }
}
