#include<stdio.h>

#include<definition.h>

Database* openFile(char *file_name)
{
    FILE *fp;
    fp = fopen(file_name,"r");
    if(fp == NULL) {
        /*---Error Message---*/
        fprintf(stdout,"\n\tError: Unable to open the file");
        return NULL;
    }
    fclose(fp);
    return NULL;
}