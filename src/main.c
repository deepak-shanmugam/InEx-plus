#include<stdio.h>
#include<stdlib.h>

#include"headers/customFunctions.h"
#include"headers/interface.h"
#include"headers/menu.h"

#define ACTIVE 1
#define INACTIVE 0

static int loadHomeMenu();

int main(int argc, char *argv[]) 
{
    fprintf(stdout,"\n\tSuccessfully 'Exit' with Return value: %d\n",loadHomeMenu());

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

        if (inputValidity == -1) 
            choice = -1;

        if (inputValidity < -1) {
            printErrorMessage(inputValidity);
            choice = 0;
        } 

        switch(choice) {
            case 0:
                exit = ACTIVE;
                break;
            case 1:
                /*---Go through---*/
            case 2:
                /*---Go through---*/
            case 3:
                if (loadDatabase(choice) == -3)
                    exit = ACTIVE;
                break;
            case 4:
                /*---Go through---*/
            case 5:
                fprintf(stdout,"\n\tMESSAGE: This section is <UNDER DEVELOPMENT>\n");
                break;
            default:
                printErrorMessage(-4);
        }

        if (exit == INACTIVE) {
            if (pauseExecution() == -1) {
                printErrorMessage(-3);
                exit = ACTIVE;
            }
        }
    }

    return 0;
}