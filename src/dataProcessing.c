#include<stdio.h>
#include<string.h>

int getCharInput();
void pauseNextStep();

int getCharInput(FILE *stream, char *str, int length) {
    if(str == NULL || length <= 1) {
        return -1;
    }
    if(fgets(str,length,stream) == NULL) {
        return -1;
    }

    int pos, count = 0;
    pos = strcspn(str,"\n");
    str[pos] = '\0';
    
    count = pos;
    if(pos >= length-1) {
        char ch = 0;
        while(ch = fgetc(stream) != '\n' && ch != EOF) {
            count++;
        }
    }
    return count;
}

void pauseNextStep() {
    char buffer[10];
    printf("\n\tpress 'ENTER' to continue: ");
    getCharInput(stdin,buffer,10);
}