#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <fcntl.h>
#include <limits.h>
#include <stddef.h>
#include "../headerfile.h"
#include <signal.h>
#include <pwd.h>
#include <limits.h>

void pinfo(char **args)
{
    int pid;

    if (args[1] == NULL)
        pid = getpid();
    else if (strcmp(args[1], "&"))
        pid = atoi(args[1]);
    else
        pid = atoi(args[2]);

    char str[1000], buff[400];
    int count = 0;
    if (pid == 0)
    {
        printf("Invalid PID\n");
        exst=1;
        return;
    }

    else
    {
        printf("pid -- ");
        printf("%d\n", pid);
        sprintf(str, "/proc/%d/status", pid);
        FILE *file = fopen(str, "r");
        if (file == NULL)
        {
            perror("Error opening file");
            exst=1;
            return;
        }
        char* var=fgets(buff, sizeof(buff), file);
        while (var!=NULL)
        {
            count++;
            if (count == 3)
            {
                printf("Process Status -- ");
                printf("%.*s\n", 2, buff + 7);
                break;
            }
            var=fgets(buff, sizeof(buff), file);
        }
        fclose(file);

        sprintf(str, "/proc/%d/statm", pid);
        file = fopen(str, "r");
        if (file == NULL)
        {
            perror("Error opening file");
            exst=1;
            return;
        }
        size_t var1 = fread(buff, 1, 100, file);
        buff[(int) var1] = '\0';
        char *str = strtok(buff, " ");
        long long int vmem = atoi(str);
        printf("memory -- ");
        printf("%lld\n",(vmem*4096));

        sprintf(str, "/proc/%d/exe", pid);
        char path[1000];
        int rd = readlink(str, path, 1000);
        if(rd < 0)
        {
            perror("Error opening file");
            exst=1;
        }
        else
        {
            printf("Executable Path -- %.*s\n", (int) strlen(home)+8, path);
            exst=0;
        }
        fclose(file);
    }
}
