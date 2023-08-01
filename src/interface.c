#include<stdio.h>
#include<string.h>

#include"headers/definition.h"
#include"headers/databaseFunctions.h"
#include"headers/loadDatabase.h"

int loadDatabase(int choice);

int loadDatabase(int choice) 
{
    Database *db = NULL;  
    int returnCode = 0;

    switch (choice) {
        case 1:
            db = createDatabase(&returnCode);
            if (returnCode == 0) {
                fprintf(stdout,"\n\tFile created successfully\n");
            }
            break;
        case 2:
            db = openDatabase(&returnCode);
            if (returnCode == 0) {
                fprintf(stdout,"\n\tFile opened successfully\n");
            }
            break;
        case 3:
            returnCode = deleteDatabase();
            if (returnCode == 0) {
                fprintf(stdout,"\n\tFile deleted successfully\n");
            }
            break;
        default:
            return -2;
    } 

    if (returnCode != 0) 
        return returnCode;

    if (db == NULL) 
        return -1;

    /*---CALL DATA OPERATION FUNCTIONS---*/

    freeDatabase(db);

    return 0;
}