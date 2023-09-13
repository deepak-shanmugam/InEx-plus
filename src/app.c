#include <stdio.h>
#include <stdlib.h>

#include "headers/definition.h"
#include "headers/customFunctions.h"
#include "headers/fileOperation.h"
#include "headers/menu.h"
#include "headers/printFunctions.h"
#include "headers/dbOperation.h"

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
        return -2;

    while(exit == INACTIVE) {
        system("clear");
        returnCode = 0;
        
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
            printErrorMessage(validity);
            if (isDbSaved(db) == 0) {
                fprintf(stdout,"\n\tMESSAGE: All unsaved data will be lost\n");
            }
            return validity;
        }

        switch (choice) {
            case 0:
                exit = ACTIVE;
                returnCode = -3;
                break;
            case 1:
                returnCode = addRecordList(db);
                if (returnCode == -3) {
                    fprintf(stdout,"\n\tMESSAGE: All modified data will be lost\n");
                    return returnCode;
                }   
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
                returnCode = saveDb(db);
                if (returnCode < -1) 
                    printErrorMessage(-9);
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

        if (exit == ACTIVE && isDbSaved(db) == 0) {
            validity = saveConfirmation();

            if (validity < 0) {
                returnCode = -3;
            }

            if (validity == 0) {
                if (saveDb(db) >= 0) {
                    break;
                } 
            }

            if (validity == 2) {
                exit = INACTIVE;
            }

            if (exit == ACTIVE) {
                fprintf(stdout,"\n\tMESSAGE: Trying to CLOSE "
                    "Without saving the FILE\n");
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