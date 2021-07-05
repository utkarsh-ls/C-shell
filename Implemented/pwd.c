#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "../headerfile.h"

void pwd()
{
    char currentdir[siz];
    getcwd(currentdir,siz);
    printf("%s\n",currentdir);
    exst=0;
}
