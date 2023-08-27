#include<stdio.h>
#include<string.h>

int getStringInput(FILE *stream, char *str, const int length);
int getIntInput(FILE *stream, int *num);
int getLongInput(FILE *stream, long *num);
int isNumberString(const char *str, const int length);
int pauseExecution();
int printErrorMessage(int errorCode);
void print_string(FILE *stream, char *str, int length);

int getStringInput(FILE *stream, char *str, const int length) 
{
    int pos = 0;
    int count = 0;
    char ch = 0;

    if (str == NULL || length <= 1) 
        return -2;
    
    if (fgets(str,length,stream) == NULL) 
        return -1;

    pos = strcspn(str,"\n");
    str[pos] = '\0';
    count = pos;

    if(pos >= length-1) {
        while(ch = fgetc(stream) != '\n' && ch != EOF) 
            count++;
    }
    
    return count;
}

int getIntInput(FILE *stream, int *num)
{
    char buffer[32];
    int validity;

    if (num == NULL || stream == NULL)
        return -2;

    validity = getStringInput(stream, buffer, sizeof(buffer));

    if (validity == -1)
        return -3;
    
    if (validity < -1)
        return -2;

    if (isNumberString(buffer, sizeof(buffer)) != 0 || validity == 0 || validity > 9)
        return -1;

    if (sscanf(buffer, "%d", num) != 1)
        return -1;
    
    return validity;
}

int getLongInput(FILE *stream, long *num)
{
    char buffer[32];
    int validity;

    if (num == NULL || stream == NULL)
        return -2;

    validity = getStringInput(stream, buffer, sizeof(buffer));

    if (validity == -1)
        return -3;
    
    if (validity < -1)
        return -2;

    if (isNumberString(buffer, sizeof(buffer)) != 0 || validity == 0 || validity > 18)
        return -1;

    if (sscanf(buffer, "%ld", num) != 1)
        return -1;
    
    return validity;
}

int isNumberString(const char *str, const int length)
{
    int i;

    if (str == NULL)
        return -2;

    for(i = 0; (i < length) && (str[i] != '\0'); i++) {
        if (str[i] >= '0' && str[i] <= '9')
            continue;
        return -1;
    }

    return 0;
}

int pauseExecution() 
{
    char buffer[16];

    printf("\n\t\tPress 'ENTER' to continue: ");
    
    return getStringInput(stdin,buffer,16);
}

int printErrorMessage(int errorCode) 
{
    switch (errorCode) {
        case -1:
            fprintf(stdout,"\n\tERROR: FAILED\n");
            break;
        case -2:
            fprintf(stdout,"\n\tERROR: Argument issue OR <NULL> passed as argument\n");
            break;
        case -3:
            fprintf(stdout,"\n\n\tERROR: <EOF> Reached. Trying to EXIT the application safely\n");
            break;
        case -4:
            fprintf(stdout,"\n\tERROR: Invalid Input\n");
            break;
        case -5:
            fprintf(stdout,"\n\tERROR: Unable to open FILE in read/write mode OR FILE doesn't exist\n");
            break;
        case -6:
            fprintf(stdout,"\n\tERROR: Error occured while 'READING' FILE\n");
            break;
        case -7:
            fprintf(stdout,"\n\tERROR: Error occured while 'WRITING' FILE\n");
            break;
        case -8:
            fprintf(stdout,"\n\tERROR: Unable to allocate MEMORY\n");
            break;
        case -9:
            fprintf(stdout,"\n\tERROR: Something went wrong\n");
            break;
        case -10:
            fprintf(stdout,"\n\tERROR: Unable to 'DELETE' FILE OR FILE doesn't exist\n");
            break;
        default:
            fprintf(stdout,"\n\n\tERROR CODE UNDEFINED\n");
            return -2;
    }

    return 0;
}

void print_string(FILE *stream, char *str, int length) {
    int i;

    if (str == NULL || stream == NULL) {
        printErrorMessage(-2);
        return;
    }

    for (i = 0; i < length; i++) {
        if (str[i] == '\0')
            break;
        fprintf(stream,"%c",str[i]);
    }
}