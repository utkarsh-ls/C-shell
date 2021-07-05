#include "../headerfile.h"
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

#define is filestat.st_mode &
#define sp printf(" ");
struct stat filestat;
struct tm *filetime;

int filter(const struct dirent *list)
{
    if (list->d_name[0] == '.')
        return 0;
    return 1;
}

void get_print_info(char *filename, char *file)
{
    char datestring[200];
    char type = ' ';
    stat(filename, &filestat);
    if (S_ISREG(filestat.st_mode))
        type = '-';
    if (S_ISSOCK(filestat.st_mode))
        type = 's';
    if (S_ISBLK(filestat.st_mode))
        type = 'b';
    if (S_ISDIR(filestat.st_mode))
        type = 'd';
    if (S_ISCHR(filestat.st_mode))
        type = 'c';
    if (S_ISLNK(filestat.st_mode))
        type = 'l';

    printf("%c", type);
    filetime = localtime(&(filestat.st_mtime));

    if (is S_IRUSR)
        printf("r");
    else
        printf("-");
    if (is S_IWUSR)
        printf("w");
    else
        printf("-");
    if (is S_IXUSR)
        printf("x");
    else
        printf("-");
    if (is S_IRGRP)
        printf("r");
    else
        printf("-");
    if (is S_IWGRP)
        printf("w");
    else
        printf("-");
    if (is S_IXGRP)
        printf("x");
    else
        printf("-");
    if (is S_IROTH)
        printf("r");
    else
        printf("-");
    if (is S_IWOTH)
        printf("w");
    else
        printf("-");
    if (is S_IXOTH)
        printf("x");
    else
        printf("-");

    sp printf("%2ld", filestat.st_nlink);
    sp printf("%16s", getpwuid(filestat.st_uid)->pw_name);
    sp printf("%16s", getgrgid(filestat.st_gid)->gr_name);
    sp printf("%15ld", filestat.st_size);
    sp strftime(datestring, sizeof(datestring), "%b %2d %H:%M", filetime);
    sp printf("%s", datestring);

    if (S_ISDIR(filestat.st_mode))
        yellow();
    else if (is S_IXUSR)
        red();

    sp printf("%s\n", file);
    reset();
}

void ls(char **cmdarg)
{
    int flag = 0;
    int fa, fl, fdir = fa = fl = 0;
    int k;
    int i = 1, j;
    struct dirent direntry;
    struct dirent **list;
    char directory[siz];
    while (cmdarg[i] != NULL)
    {
        if (strcmp(cmdarg[i], "-a") == 0)
        {
            fa++;
            i++;
            continue;
        }
        if (strcmp(cmdarg[i], "-l") == 0)
        {
            fl++;
            i++;
            continue;
        }
        if (strcmp(cmdarg[i], "-la") == 0 || strcmp(cmdarg[i], "-al") == 0)
        {
            fl++;
            fa++;
            i++;
            continue;
        }
        fdir++;
        i++;
    }
    if (fl == 0)
    {
        if (fdir == 0)
        {
            int count = 0;
            if (fa == 0)
                k = scandir(".", &list, filter, alphasort);
            if (fa)
                k = scandir(".", &list, NULL, alphasort);

            if (0 > k)
            {
                perror("ls directory");
                exst=1;
                // printf(":'(");
                return;
            }
            else
            {
                while ((k - count) > 0)
                {
                    stat(list[count]->d_name, &filestat);
                    if (S_ISDIR(filestat.st_mode))
                        yellow();
                    else if (is S_IXUSR)
                        red();

                    printf("%s\n", list[count]->d_name);
                    reset();
                    free(list[count]);
                    count++;
                }
                exst=0;
                // printf(":')");
                free(list);
            }
        }
        else
        {
            j = 1;
            int sflag=0;
            while (cmdarg[j] != NULL)
            {
                char temp[100];
                int count = 0;
                char filepath[siz];
                if (cmdarg[j][0] == '-')
                {
                    j++;
                    continue;
                }
                strcpy(temp,cmdarg[j]);
                if (cmdarg[j][0] == '~')
                {
                    strcpy(temp, home);
                    strcat(temp, cmdarg[j] + 1);
                    // strcpy(cmdarg[j], temp);
                }
                if (fa == 0)
                    k = scandir(temp, &list, filter, alphasort);
                if (fa)
                    k = scandir(temp, &list, NULL, alphasort);

                if (0 > k)
                {
                    perror("ls directory ");
                    sflag=1;
                    j++;
                    continue;
                }
                else
                {
                    while ((k - count) > 0)
                    {
                        strcpy(filepath, temp);
                        strcat(filepath, "/");
                        strcat(filepath, list[count]->d_name);
                        stat(filepath, &filestat);
                        if (S_ISDIR(filestat.st_mode))
                            yellow();
                        else if (is S_IXUSR)
                            red();

                        printf("%s\n", list[count]->d_name);
                        reset();
                        free(list[count]);
                        count++;
                    }
                    free(list);
                }
                ++j;
                printf("\n");
            }
            if(sflag==1)
                exst=1;
            else
                exst=0;
        }
    }
    else
    {
        if (fdir == 0)
        {
            int count = 0;
            int total = 0;
            if (fa == 0)
                k = scandir(".", &list, filter, alphasort);
            if (fa)
                k = scandir(".", &list, NULL, alphasort);

            if (0 > k)
            {
                perror("ls directory ");
                exst=1;
                // printf(":'(");
                return;
            }
            else
            {
                while ((k - count) > 0)
                {
                    stat(list[count]->d_name, &filestat);
                    total += filestat.st_blocks;
                    count++;
                }
                printf("total %3d\n", total / 2);
                count = 0;
                while ((k - count) > 0)
                {
                    get_print_info(list[count]->d_name, list[count]->d_name);
                    free(list[count]);
                    count++;
                }
                exst=0;
                // printf(":')");
                free(list);
            }
        }
        else
        {
            j = 1;
            int sflag=0;
            while (cmdarg[j] != NULL)
            {
                char temp[100];
                int count = 0;
                int total = 0;
                char filepath[siz];
                if (cmdarg[j][0] == '-')
                {
                    j++;
                    continue;
                }
                strcpy(temp,cmdarg[j]);
                if (cmdarg[j][0] == '~')
                {
                    strcpy(temp, home);
                    strcat(temp, cmdarg[j] + 1);
                }
                if (fa == 0)
                    k = scandir(temp, &list, filter, alphasort);
                if (fa)
                    k = scandir(temp, &list, NULL, alphasort);

                if (0 > k)
                {
                    perror("ls directory ");
                    sflag=1;
                    j++;
                    continue;
                }
                else
                {
                    while ((k - count) > 0)
                    {
                        strcpy(filepath, temp);
                        strcat(filepath, "/"), strcat(filepath, list[count]->d_name);
                        stat(filepath, &filestat);
                        total += filestat.st_blocks;
                        count++;
                    }
                    printf("Total %d\n", total / 2);
                    count = 0;
                    while ((k - count) > 0)
                    {
                        strcpy(filepath, temp);
                        strcat(filepath, "/"), strcat(filepath, list[count]->d_name);
                        get_print_info(filepath, list[count]->d_name);
                        free(list[count++]);
                        // count++;
                    }
                    free(list);
                }
                ++j;
                printf("\n");
            }
            if(sflag==1)
                exst=1;
            else
                exst=0;
        }
    }
}
