#include "../../headerfile.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int logicalexec(char *cmd)
{
    int flag = 0, i;
    char cmdcpy[1024];
    char **execmd;
    cmdcpy[0] = 0;

    strcpy(cmdcpy, cmd);
    int pipeflag = 0;
    int pipcheck = 0;
    execmd = splitargs(cmd);
    int check1,check2,check3,check4;
    // if (execmd[0] == NULL)
    //     return;
    while (execmd[pipcheck])
    {
        check1 = strcmp(execmd[pipcheck], ">>");
        check2 = strcmp(execmd[pipcheck], ">");
        check3 = strcmp(execmd[pipcheck], "|");
        check4 = strcmp(execmd[pipcheck], "<");
        if ((check1 == 0) || (check2 == 0) || (check3 == 0) || (check4 == 0))
        {
            pipeflag++;
            tagpiper(cmdcpy);
            break;
        }
        pipcheck++;
    }
    // printf("%d\n",and_no);
    if (pipeflag == 0)
    {
        flag = 0;
        int and_no = checkand(execmd);

        // printf("%d\n",and_no);
        if (!strcmp(execmd[0], "exit") || !strcmp(execmd[0], "quit"))
        {
            exhis();
            exit(0);
        }
        else
        {
            for (i = 0; i < 14; i++)
            {
                if (strcmp(execmd[0], cmdlist[i]) == 0)
                {
                    switch (i)
                    {
                    case 0:
                        cd(execmd);
                        break;
                    case 1:
                        pwd();
                        break;
                    case 2:
                        echo(execmd);
                        break;
                    case 3:
                        ls(execmd);
                        break;
                    case 4:
                        pinfo(execmd);
                        break;
                    case 5:
                        nightswatch(execmd);
                        break;
                    case 6:
                        history(execmd);
                        break;
                    case 7:
                        seten(execmd);
                        break;
                    case 8:
                        unseten(execmd);
                        break;
                    case 9:
                        bghand(execmd);
                        break;
                    case 10:
                        jobs(execmd);
                        break;
                    case 11:
                        killemall(execmd);
                        break;
                    case 12:
                        kjobs(execmd);
                        break;
                    case 13:
                        fg(execmd);
                        break;
                    default:
                        break;
                    }
                    flag = 1;
                }
            }
            if (flag == 0)
                unimplemented(execmd, and_no);
        }
    }
    return exst;
}

void logical(char *cmd) // cmd1 @ cmd2 $ cmd3 @ cmd4
{
    int arr[siz];
    memset(arr,-1,sizeof(arr));
    int i = 0, j = 0, val;
    char *str[200];

    char **execmd;
    char cmdcpy[1024];
    strcpy(cmdcpy, cmd);
    execmd = splitargs(cmd);
    
    while (execmd[j])
    {
        if (strcmp(execmd[j], "$") == 0)
        {
            //operators[i] = '$';
            arr[i] = 1;
            i++;
        }
        else if (strcmp(execmd[j], "@") == 0)
        {
            //operators[i] = '@';
            arr[i] = 0;
            i++;
        }
        // printf("%s\n", execmd[j]);
        j++;
    }

    int operator_number = i; // 3 here
    char *token = strtok(cmdcpy, "@$");
    i = 0;

    while (token != NULL)
    {
        str[i] = token;
        token = strtok(NULL, "@$");
        i++;
    }
    i = 1;
    val = logicalexec(str[0]); //tokenize and implement command and strore exit status of 1st cmd in val
    val = 1-val;
    // printf("nonoo %d\n",operator_number);
    while(i<=operator_number)
    {
        if(arr[i-1]==1 && val==1)
            break;
        int temp_val;
        int cmp1,cmp2,cmp3;
        cmp1=strcmp(str[i], "");
        cmp2=strcmp(str[i], " ");
        cmp3=strcmp(str[i], "\t");
        if ((cmp1== 0) || (cmp2== 0) || (cmp3== 0))
        {
            temp_val = 1;
            printf("Syntax is not correct\n");
            // continue;
        }
        else
            temp_val = logicalexec(str[i]);
        // printf("ok this is %d\n", temp_val);
        if (arr[i - 1]) // OR
        {
            val = val | (1-temp_val);
        }
        else
        {
            val = val & (1-temp_val);
            //printf("------------%d\n", val);
        }
        i++;
    }
    exst = 1-val;
}