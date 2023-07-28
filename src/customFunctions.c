#include<stdio.h>
#include<string.h>

int getStringInput();
void pauseNextStep();

int getStringInput(FILE *stream, char *str, int length) 
{
    if(str == NULL || length <= 1) {
        return -1;
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

void pauseNextStep() 
{
    char buffer[16];
    printf("\n\tpress 'ENTER' to continue: ");
    getStringInput(stdin,buffer,16);
}