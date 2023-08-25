#include <stdio.h>
#include <stdlib.h>

#include "headers/definition.h"
#include "headers/customFunctions.h"
#include "headers/fileOperation.h"
#include "headers/menu.h"
#include "headers/printFunctions.h"

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
        
        print_fileName(stdout, db->dbMetaData.fileMetaData.fileName
            , FILE_NAME_LENGTH, db->dbMetaData.metaData.isModified);
        fprintf(stdout,"\n");
        showFileMenu(stdout);

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
                fprintf(stdout,"\n\tMESSAGE: This section is <UNDER DEVELOPMENT>\n");
                break;
            case 2:
                fprintf(stdout,"\n\tMESSAGE: This section is <UNDER DEVELOPMENT>\n");
                break;
            case 3:
                print_recordList(stdout, db->recordList, 0, 0, 10);
                break;
            case 4:
                fprintf(stdout,"\n\tMESSAGE: This section is <UNDER DEVELOPMENT>\n");
                break;
            case 5:
                if (db->dbMetaData.metaData.isSaved == 1 
                        && db->dbMetaData.metaData.isModified == 0) {
                    fprintf(stdout,"\n\tFile is already saved!\n");
                    break;
                }
                if (saveFile(db) == 0) {
                    fprintf(stdout,"\n\tMESSAGE: FILE saved successfully!\n");
                    db->dbMetaData.metaData.isSaved = 1;
                    db->dbMetaData.metaData.isModified = 0;
                } else {
                    fprintf(stdout,"\n\tMESSAGE: FILE not saved\n");
                }
                break;
            case 6:
                print_dbMetaData(stdout, &db->dbMetaData);
                break;
            case 7:
                exit = ACTIVE;
                returnCode = 0;
                break;
            default:
                printErrorMessage(-4);
        }

        /*---While Exit, if db is not saved, ask user to choose what to do---*/
        if (exit == ACTIVE && db->dbMetaData.metaData.isSaved == 0) {
            validity = saveConfirmation();

            if (validity < 0) {
                returnCode = -3;
                validity = 1;
            }

            if (validity == 0) {
                if (saveFile(db) == 0) {
                    fprintf(stdout,"\n\tMESSAGE: FILE saved successfully!\n");
                    db->dbMetaData.metaData.isSaved = 1;
                    db->dbMetaData.metaData.isModified = 0;
                    break;
                } 
                validity = 1;
            }

            if (validity == 1) {
                fprintf(stdout,"\n\tMESSAGE: Trying to CLOSE "
                    "Without saving the FILE\n");
            }

            if (validity == 2) {
                exit = INACTIVE;
            }
        }

        if (exit == INACTIVE) {
            if (pauseExecution() == -1) {
                printErrorMessage(-3);
                returnCode = -3;
                exit = ACTIVE;
            }
        }
    }

    return returnCode;
}

static int saveConfirmation() 
{
    char buffer[16];
    int validity = 0;
    int returnCode = 0;

    while (validity >= 0) {
        fprintf(stdout,"\n\tDo you want to save before closing? [y/n/c]: ");
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