#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"headers/definition.h"
#include"headers/customFunctions.h"
#include"headers/databaseFunctions.h"
#include"headers/fileOperation.h"

Database* createDatabase(int *returnCode);                         
Database* openDatabase(int *returnCode);   
int deleteDatabase();

Database* createDatabase(int *returnCode) 
{
    Database *db = NULL;

    if (returnCode == NULL) {
        printErrorMessage(-2);
        return db;
    }

    db = (Database *)calloc(1, sizeof(*db));
    if (db == NULL) {
        printErrorMessage(-8);
        *returnCode = -1;
        return db;
    }

    if ((*returnCode = setDbMetaData(&db->dbMetaData)) != 0) {
        freeDatabase(db);
        return NULL;
    }

    db->dbMetaData.metaData.isSaved = 0;
    db->dbMetaData.metaData.isModified = 1;
    db->recordList = NULL;

    return db;
}

Database* openDatabase(int *returnCode) 
{
    Database *db = NULL;
    char file_name[64];
    int validity = 0;

    if (returnCode == NULL) {
        printErrorMessage(-2);
        return db;
    }

    validity = setFileName(file_name, FILE_NAME_LENGTH, 0);
    if (validity < 0) {
        *returnCode = validity;
        return NULL;
    }

    db = openFile(file_name);
    
    if (db == NULL) {
        *returnCode = -1;
    } else {
        *returnCode = 0;
        db->dbMetaData.metaData.isSaved = 1;
        db->dbMetaData.metaData.isModified = 0;
    }

    return db;
}

int deleteDatabase() 
{
    char file_name[64];
    int returnCode = 0;

    returnCode = setFileName(file_name, FILE_NAME_LENGTH, 0);
    if (returnCode < 0) 
        return returnCode;

    if (returnCode = removeFile(file_name) != 0) 
        printErrorMessage(-10);

    return returnCode;
}