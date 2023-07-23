#include<stdio.h>
#include<stdlib.h>
#include"headers/menu.h"
#include"headers/dataProcessing.h"

#define ACTIVE 1
#define INACTIVE 2

#define MAX_STR_LEN 3

int loadHomeMenu();

int main(int argc, char *argv[]) {
    fprintf(stdout,"Exit Return value: %d\n",loadHomeMenu());
    return 0;
}

int loadHomeMenu() {
    int choice = 0, exit = INACTIVE, inputStrCount = 0;
    char buffer[10];
    
    while(exit == INACTIVE) {
        system("clear");
        showHomeMenu(stdout);

        fprintf(stdout,"Enter your choice: ");
        inputStrCount = getCharInput(stdin,buffer,MAX_STR_LEN);

        if(inputStrCount < 0) {
            //Error Message
            fprintf(stdout,"\n\tUnable to get input\n");
            return -1;
        } 
        //To myself: This else if is needed, because if someone enters "01999" only "01" comes to str
        else if(inputStrCount >= MAX_STR_LEN) { 
            choice = -1;    
        } 
        else {
            if(sscanf(buffer,"%d",&choice) != 1) {
                choice = -1;
            }
        }

        system("clear");
        switch(choice) {
            case 0:
                exit = ACTIVE;
                fprintf(stdout,"\nExiting the application...\n");
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
                //Error Message
                fprintf(stdout,"\n\tPlease enter valid choice\n");
        }
        if(exit == INACTIVE) {
            pauseNextStep();
        }
    }

    return 0;
}