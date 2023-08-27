#include<stdio.h>
#include<stdlib.h>

#include"headers/definition.h"
#include"headers/app.h"
#include"headers/customFunctions.h"
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
            break;
        case 2:
            db = openDatabase(&returnCode);
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

    returnCode = DBOperation(db);
        
    if (freeDatabase(db) == 0) {
        fprintf(stdout,"\n\tMESSAGE: Successfully closed the FILE\n");
    } else {
        /*---ERROR MESSAGE---*/
        fprintf(stdout,"\n\tERROR: Unable to clear the data from memory\n");
    }

    return returnCode;
}