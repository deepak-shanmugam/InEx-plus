#include<stdio.h>
#include<stdlib.h>

#include"headers/definition.h"
#include"headers/customFunctions.h"
#include"headers/databaseFunctions.h"
#include"headers/loadDatabase.h"

/*---Local Testing header---*/
//#include"headers/testDatabase.h"

int loadDatabase(int choice);

int loadDatabase(int choice) 
{
    Database *db = NULL;  
    int returnCode = 0;

    switch (choice) {
        case 1:
            db = createDatabase(&returnCode);
            if (returnCode == 0) {
                fprintf(stdout,"\n\tMESSAGE: New File 'CREATED' successfully\n");
            }
            break;
        case 2:
            db = openDatabase(&returnCode);
            if (returnCode == 0) {
                fprintf(stdout,"\n\tMESSAGE: File 'OPENED' successfully\n");
            }
            break;
        case 3:
            returnCode = deleteDatabase();
            if (returnCode == 0) {
                fprintf(stdout,"\n\tMESSAGE: File 'DELETED' successfully\n");
                return 0;
            }
            break;
        default:
            printErrorMessage(-2);
            return -2;
    } 

    if (returnCode != 0) 
        return returnCode;

    if (db == NULL) 
        return -1;

    if (pauseExecution() == -1) {
        printErrorMessage(-3);
        freeDatabase(db);
        return -3;
    }

    system("clear");
    printf("\n\tMESSAGE: Income and expense management operation is <UNDER DEVELOPEMENT>\n");

    /*---Local Testign functions---*/
    //printDbMetaData(db->dbMetaData);
    //printRecordList(db->recordList);

    freeDatabase(db);

    return 0;
}