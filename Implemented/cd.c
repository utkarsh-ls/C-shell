#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pwd.h>
#include <unistd.h>

#include "../headerfile.h"

int cd(char **args)
{
    char currdir[200];
    int err;
    getcwd(currdir, sizeof(currdir));
    if (args[1] == NULL || strcmp(args[1], "~") == 0 || strcmp(args[1], "~/") == 0)
        err = chdir(home);
    else if (strcmp(args[1], "-") != 0)
        err = chdir(args[1]);
    else if (strcmp(args[1], "-") == 0)
    {
        printf("%s\n", prevdir);
        err = chdir(prevdir);
    }
    strcpy(prevdir, currdir);
    if (err >= 0)
    {
        exst=0;
        // printf(":')");
        return 0;
    }
    perror("cd");
    exst=1;
    // printf(":'(");
    return -1;
}
