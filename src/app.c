#include <stdio.h>
#include <stdlib.h>

#include "headers/definition.h"
#include "headers/customFunctions.h"
#include "headers/databaseFunctions.h"
#include "headers/fileOperation.h"
#include "headers/menu.h"

#define ACTIVE 1
#define INACTIVE 0

int DBOperation(Database *db);

static int saveConfirmation();

int DBOperation(Database *db) 
{
    int choice;
    int validity;
    int exit = INACTIVE; 
    int returnCode = 0;

    if (db == NULL)
        return -1;

    while(exit == INACTIVE) {
        system("clear");
        showFileMenu(stdout,db->dbMetaData.fileMetaData.fileName,
            db->dbMetaData.metaData.isSaved);

        fprintf(stdout,"\n\tEnter your choice: ");
        validity = getIntInput(stdin, &choice);

        if (validity == -1) {
            choice = -1;
        }

        if (validity < -1) {
            printErrorMessage(-3);
            choice = 0;
        }

        switch (choice) {
            case 0:
                exit = ACTIVE;
                returnCode = -3;
                break;
            case 1:
                printf("\n\tMESSAGE: Income and expense management operation is "
                    "<UNDER DEVELOPEMENT>\n");
                break;
            case 2:
                printf("\n\tMESSAGE: Income and expense management operation is "
                    "<UNDER DEVELOPEMENT>\n");
                break;
            case 3:
                printRecordList(db->recordList);
                break;
            case 4:
                printf("\n\tMESSAGE: Income and expense management operation is "
                    "<UNDER DEVELOPEMENT>\n");
                break;
            case 5:
                if (db->dbMetaData.metaData.isSaved == 0) {
                    db->dbMetaData.metaData.isSaved = 1;
                    if (saveFile(db) == 0) {
                        fprintf(stdout,"\n\tMESSAGE: FILE saved successfully!\n");
                    } else {
                        db->dbMetaData.metaData.isSaved = 0;
                        fprintf(stdout,"\n\tMESSAGE: FILE not saved\n");
                    }
                    break;
                } 
                fprintf(stdout,"\n\tFile is already saved!\n");
                break;
            case 6:
                printDbMetaData(db->dbMetaData);
                break;
            case 7:
                exit = ACTIVE;
                returnCode = 0;
                break;
            default:
                printErrorMessage(-4);
        }

        if (exit == ACTIVE && db->dbMetaData.metaData.isSaved == 0) {
            validity = saveConfirmation();

            if (validity < 0) {
                returnCode = -3;
                validity = 1;
            }

            if (validity == 0) {
                db->dbMetaData.metaData.isSaved = 1;
                if (saveFile(db) == 0) {
                    fprintf(stdout,"\n\tMESSAGE: FILE saved successfully!\n");
                    break;
                } 
                validity = 1;
            }

            if (validity == 1) {
                fprintf(stdout,"\n\tMESSAGE: Trying to EXIT "
                    "Without saving the FILE\n");
            }

            if (validity == 2) {
                exit = INACTIVE;
            }
        }

        if (exit == INACTIVE) {
            if (pauseExecution() == -1) {
                printErrorMessage(-3);
                exit = ACTIVE;
            }
        }
    }

    return returnCode;
}

static int saveConfirmation() {
    char buffer[16];
    int validity = 0;
    int returnCode = 0;

    while (validity >= 0) {
        fprintf(stdout,"\n\tDo you want to save before exit? [y/n/c]: ");
        validity = getStringInput(stdin,buffer,16);

        if (validity < 0) {
            fprintf(stdout,"\n\n\tMESSAGE: Unable to get input\n");
            returnCode = validity;
            break;
        }

        if (buffer[0] == 'y' || buffer[0] == 'Y') {
            returnCode = 0;
            break;
        }

        if (buffer[0] == 'n' || buffer[0] == 'N') {
            returnCode = 1;
            break;
        }

        if (buffer[0] == 'c' || buffer[0] == 'C') {
            returnCode = 2;
            break;
        }
    }

    return returnCode;
}