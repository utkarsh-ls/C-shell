#include "../headerfile.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void echo(char **args)
{
    int n=0,i=0;
	if(args[1] == NULL)
	{
		printf("\n");
        exst=0;
        // printf(":')");
		return;
	}
    // if (n && args[2]==NULL)
    //     return;
    i=1;
    while(args[i]!=NULL)
    {
        char* str;
        str = strtok(args[i], " \t");
        while (str != NULL)
        {
            printf("%s ",str);
            str = strtok(NULL, " \t");
        }
        // printf("%s ",args[i]);
        i++;
    }
    printf("\n");
    exst=0;
    // printf(":')");
	return;
}
