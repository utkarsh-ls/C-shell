#include <termios.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <pwd.h>
#include <errno.h>
#include <string.h>
#include <dirent.h>
#include <fcntl.h>
#include <grp.h>
#include <time.h>
#include <locale.h>
#include <langinfo.h>
#include <stdint.h>
#include <signal.h>
#include <sys/time.h>
#include <unistd.h>
#include <signal.h>
#include <sys/ioctl.h>
#include "../../headerfile.h"

int keyDown()
{
    struct termios oldat, newat;
    int chb;

    int key = tcgetattr(0, &oldat);
    if (key)
    {
        exst=1;
        perror("in keyDown");
    }
    else
    {
        newat = oldat;
        newat.c_lflag &= ~(ICANON | ECHO);

        tcsetattr(0, TCSANOW, &newat);
        ioctl(0, FIONREAD, &chb);
        tcsetattr(0, TCSANOW, &oldat);

        return (chb > 0 ? 1 : 0);
    }
    return 0;
}

void newborn()
{
    char filname[siz];
    strcpy(filname, "/proc/loadavg");
    FILE *dirmem = fopen(filname, "r");
    if (dirmem)
    {
        char *str, buff[100];
        size_t f_siz;

        f_siz = fread(buff, 1, 50, dirmem);
        buff[f_siz] = '\0';
        // printf("%ld\n",f_siz);
        // printf("%s\n",buff);
        str = strtok(buff, " ");
        while (str != NULL)
        {
            strcpy(buff, str);
            str = strtok(NULL, " ");
        }
        printf("%s", buff);
    }
    else
    {
        printf("Error opening /proc/loadavg\n");
        exst=1;
    }
}

void interrupt()
{
    char filname[siz],buff[100];
    int count = 1;
    strcpy(filname, "/proc/interrupts");
    FILE *dirmem = fopen(filname, "r");
    if (dirmem)
    {
        while (fgets(buff, sizeof(buff), dirmem))
        {
            if (count == 1)
            {
                // CPU's
                buff[95] = '\0';
                printf("%s\n", buff + 6);
            }
            else if (count == 5)
            {
                // Interrupts
                buff[95] = '\0';
                printf("%s\n", buff + 6);
                break;
            }
            count++;
        }
    }
    else
    {
        exst=1;
        printf("Error opening /proc/interrupts\n");
    }
}

void nightswatch(char **args)
{
    int prev_time = 0;
    int f = 1;
    exst=0;
    if(args[1]==NULL || args[2]==NULL || args[3]==NULL)
    {
        exst=1;
        printf("incorrect number of argument\n");
        return;
    }
    if (strcmp(args[1], "-n"))
    {
        exst=1;
        printf("incorrect argument\n");
        return;
    }

    int n = atoi(args[2]);
    if (strcmp(args[3], "newborn") == 0)
        f = 0;
    else if (strcmp(args[3], "interrupt") != 0)
    {
        exst=1;
        printf("arguments are newborn or interrupt\n");
        return;
    }
    if(n==0)
    {
        exst=1;
        printf("Provide correct time interval\n");
        return;
    }
    time_t start = time(NULL);
    while (1)
    {
        if (((time(NULL) - start) / n) > prev_time)
        {
            prev_time++;
            if (f == 0)
                newborn();
            else
                interrupt();
        }
        if (keyDown() && (getchar() == 'q'))
            return;
    }
}
