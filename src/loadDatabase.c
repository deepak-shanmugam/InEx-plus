#include<stdio.h>
#include<stdlib.h>

#include"headers/definition.h"
#include"headers/databaseFunctions.h"
#include"headers/customFunctions.h"
#include"headers/fileOperation.h"

Database* createDatabase();                         
Database* openDatabase(const char *file_name);                 

Database* createDatabase() 
{
    Database *db = NULL;

    db = (Database *)calloc(1, sizeof(*db));
    if (db == NULL)
        return NULL;

    if (setDbMetaData(&db->dbMetaData) != 0) {
        free(db);
        return NULL;
    }
    
    db->recordList = NULL;

    return db;
}

Database* openDatabase(const char *file_name) 
{
    Database *db = NULL;

    db = openFile(file_name);

    return db;
}