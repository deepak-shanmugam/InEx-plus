#include<stdio.h>
#include<stdlib.h>

#include"headers/customFunctions.h"
#include"headers/interface.h"
#include"headers/menu.h"

#define ACTIVE 1
#define INACTIVE 0

static int loadHomeMenu();
static void show_about();
static void show_copyright();
static void show_license();
static void show_dev_contact();

int main(int argc, char *argv[]) 
{
    show_copyright();

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
        show_copyright();
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
                fprintf(stdout,"\n\tMESSAGE: This section is <UNDER DEVELOPMENT>\n");
                break;
            case 5:
                system("clear");
                show_about();
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

static void show_about() {
    show_copyright();
    show_license();
    show_dev_contact();
}

static void show_copyright() {
    static const char app_name_text[] = "InEx-plus";
    static const char version_text[] = "version 0.2";
    static const char copyRight_text[] = 
        "Copyright (C) 2023 Deepak Shanmugam";
    
    fprintf(stdout,"%s, %s\n", app_name_text, version_text);
    fprintf(stdout,"%s\n", copyRight_text);
}

static void show_license() {
    static const char license_text[] =
        "\nLICENSE: \n\nThis program is free software: "
        "you can redistribute it and/or modify it "
        "under the terms of the GNU General Public License "
        "as published by the Free Software Foundation, "
        "either version 3 of the License, or (at your option) any later version.\n"

        "\nThis program is distributed in the hope that it will be useful, "
        "but WITHOUT ANY WARRANTY; "
        "without even the implied warranty of MERCHANTABILITY "
        "or FITNESS FOR A PARTICULAR PURPOSE.  "
        "See the GNU General Public License for more details.\n"

        "\nYou should have received a copy of the "
        "GNU General Public License along with this program.  "
        "If not, see <http://www.gnu.org/licenses/>.\n";    
    
    fprintf(stdout,"%s", license_text);
    
}

static void show_dev_contact() {
    static const char contact_text[] =
        "\nDEVELOPER CONTACT: "
        "deepdeepdeepak@outlook.com\n";
    
    fprintf(stdout,"%s", contact_text);
}