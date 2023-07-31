#include<stdio.h>
#include<string.h>

int getStringInput(FILE *stream, char *str, const int length);
int getIntInput(FILE *stream, int *num);
int getLongInput(FILE *stream, long *num);
int isNumberString(const char *str, const int length);
int pauseNextStep();

int getStringInput(FILE *stream, char *str, const int length) 
{
    if(str == NULL || length <= 1) {
        return -2;
    }
    if(fgets(str,length,stream) == NULL) {
        return -1;
    }

    int pos, count = 0;
    char ch = 0;

    pos = strcspn(str,"\n");
    str[pos] = '\0';
    count = pos;

    if(pos >= length-1) {
        while(ch = fgetc(stream) != '\n' && ch != EOF) {
            count++;
        }
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

    if (validity < 0)
        return validity;

    if (isNumberString(buffer, sizeof(buffer)) != 0 || validity == 0)
        return -3;

    if (sscanf(buffer, "%d", num) != 1)
        return -4;
    
    return 0;
}

int getLongInput(FILE *stream, long *num)
{
    char buffer[32];
    int validity;

    if (num == NULL || stream == NULL)
        return -2;

    validity = getStringInput(stream, buffer, sizeof(buffer));

    if (validity < 0)
        return validity;

    if (isNumberString(buffer, sizeof(buffer)) != 0 || validity == 0)
        return -3;

    if (sscanf(buffer, "%ld", num) != 1)
        return -4;
    
    return 0;
}

int isNumberString(const char *str, const int length)
{
    int i;

    if (str == NULL)
        return -2;

    for(i = 0; (i < length) && (str[i] != '\0'); i++) {
        if (str[i] >= '0' && str[i] <= '9')
            continue;
        return -3;
    }

    return 0;
}

int pauseNextStep() 
{
    char buffer[16];

    printf("\n\tpress 'ENTER' to continue: ");
    
    return getStringInput(stdin,buffer,16);
}