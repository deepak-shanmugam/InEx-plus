#include<stdio.h>

int loadHome();
void printHomeFunctions();

enum status {ACTIVE = 1, INACTIVE = 0};

int main(int argc, char *argv[]) {
    loadHome();
    return 0;
}

int loadHome() {
    int exit = INACTIVE, choice = 0, redoInput = INACTIVE;

    while(exit != ACTIVE) {
        if(redoInput != ACTIVE) {
            printHomeFunctions();
        }
        redoInput = INACTIVE;

        //add function: alternate way to get input
        printf("Enter your chice: ");
        scanf("%d",&choice);
        
        switch(choice) {
            case -1:
                printf("Invalid input entered\n");
                redoInput = ACTIVE;
                break;
            case 0:
                printf("Choosed to exit\n");
                exit = ACTIVE;
                break;
            case 1:
                //add function for new file
                break;
            case 2:
                //add function for open file
                break;
            case 3:
                //add function to list files
                break;
            default:
                printf("Entered choice is not exist\n");
        }
    }

    return 0;
}

void printHomeFunctions() {
    printf("\nHome page:\n");
    printf("1. Create new file\n");
    printf("2. Open existing file\n");
    printf("3. List existing files\n");
    printf("end\n\n");
}