#include<stdio.h>
#include<stdlib.h>

#include"headers/customFunctions.h"
#include"headers/menu.h"

#define ACTIVE 1
#define INACTIVE 0

static int loadHomeMenu();

int main(int argc, char *argv[]) 
{
    fprintf(stdout,"\n\tSuccessfully Exit with Return value: %d\n",loadHomeMenu());

    return 0;
}

static int loadHomeMenu() 
{
    int choice;
    int inputValidity;
    int exit = INACTIVE; 
    
    while(exit == INACTIVE) {
        system("clear");
        showHomeMenu(stdout);

        fprintf(stdout,"\nEnter your choice: ");
        inputValidity = getIntInput(stdin, &choice);

        if (inputValidity == -1) {
            /*---Error Message---*/
            fprintf(stdout,"\n\n\tError: <EOF> reached, Trying to exit safely\n");
            choice = 0;
        }

        if (inputValidity < -1)
            choice = -1;

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
            if(pauseNextStep() == -1) {
                /*---Error Message---*/
                fprintf(stdout,"\n\n\tError: <EOF> reached, Trying to exit safely\n");
                exit = ACTIVE;
            }
        }
    }

    return 0;
}