#include<stdio.h>
#include<stdlib.h>

#include"headers/dataProcessing.h"
#include"headers/menu.h"

#define ACTIVE 1
#define INACTIVE 0
#define MAX_STR_LEN 3

static int loadHomeMenu();

int main(int argc, char *argv[]) 
{
    fprintf(stdout,"\n\tSuccessfully Exit with Return value: %d\n",loadHomeMenu());

    return 0;
}

static int loadHomeMenu() 
{
    int choice = 0, exit = INACTIVE, inputStrCount = 0;
    char buffer[10];
    
    while(exit == INACTIVE) {
        system("clear");
        showHomeMenu(stdout);

        fprintf(stdout,"Enter your choice: ");
        inputStrCount = getCharInput(stdin,buffer,MAX_STR_LEN);

        if(inputStrCount < 0) {
            /*---Error Message---*/
            fprintf(stdout,"\n\tError: Unable to get input\n");
            return -1;
        } else if(inputStrCount >= MAX_STR_LEN) { 
            choice = -1;    
        } else {
            if(sscanf(buffer,"%d",&choice) != 1) {
                choice = -1;
            }
        }

        system("clear");
        switch(choice) {
            case 0:
                exit = ACTIVE;
                fprintf(stdout,"\n\tTrying to Exit the application...\n");
                break;
            case 1:
                //Create New File
                fprintf(stdout,"\n\t<This function Under construction>\n");
                break;
            case 2:
                //Open Existing File
                fprintf(stdout,"\n\t<This function Under construction>\n");
                break;
            case 3:
                //List Existing File
                fprintf(stdout,"\n\t<This function Under construction>\n");
                break;
            default:
                /*---Error Message---*/
                fprintf(stdout,"\n\tError: Please enter valid choice\n");
        }

        if(exit == INACTIVE) {
            pauseNextStep();
        }
    }

    return 0;
}