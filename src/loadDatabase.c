#include<stdio.h>
#include<stdlib.h>

#include"headers/definition.h"
#include"headers/databaseFunctions.h"
#include"headers/customFunctions.h"
#include"headers/fileOperation.h"

Database* createDatabase(int *returnCode);                         
Database* openDatabase(int *returnCode);   
int deleteDatabase();

Database* createDatabase(int *returnCode) 
{
    Database *db = NULL;

    db = (Database *)calloc(1, sizeof(*db));
    if (db == NULL) {
        *returnCode = -1;
        return db;
    }

    if ((*returnCode = setDbMetaData(&db->dbMetaData)) != 0) {
        //printf("\n\tDebug: setDbMetaData returncode: %d\n",*returnCode);
        freeDatabase(db);
        return NULL;
    }
    
    db->recordList = NULL;

    return db;
}

Database* openDatabase(int *returnCode) 
{
    Database *db = NULL;
    char file_name[64] = "test.bin";

    /*---INPUT FUNCTION CALL FOR FILENAME WILL OCCUR LATER---*/

    *returnCode = 0;

    db = openFile(file_name);
    
    if (db == NULL)
        *returnCode = -1;

    return db;
}

int deleteDatabase() 
{
    char file_name[64] = "test.bin";

    /*---ADD CONFIRMATION AND OTHER IMPLEMENTATION LATER---*/

    return removeFile(file_name);
}