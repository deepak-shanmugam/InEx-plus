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

    if (returnCode == NULL) {
        printErrorMessage(-2);
        return db;
    }

    fprintf(stdout,"\n\tPlease Enter File name to OPEN: ");

    *returnCode = getStringInput(stdin,file_name,64);
    if (*returnCode <= 0) {
        if (*returnCode == -1) 
            *returnCode = -3;
        if (*returnCode == 0)
            *returnCode = -4;
        printErrorMessage(*returnCode);
        return NULL;
    }

    if (*returnCode >= 50) {
        /*---ERROR MESSAGE---*/
        fprintf(stdout,"\n\tERROR: Filename should not be more than 50 characters\n");
        *returnCode = -1;
        return NULL;
    }

    /*---UNSAFE FUNCTION---*/
    strcat(file_name,".inex");

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
    char file_name[64] = "test.bin";
    int returnCode = 0;

    fprintf(stdout,"\n\tPlease Enter File name to DELETE: ");

    returnCode = getStringInput(stdin,file_name,64);
    if (returnCode <= 0) {
        if (returnCode == -1) 
            returnCode = -3;
        if (returnCode == 0)
            returnCode = -4;
        printErrorMessage(returnCode);
        return returnCode;
    }

    if (returnCode > 50) {
        /*---ERROR MESSAGE---*/
        fprintf(stdout,"\n\tERROR: Filename should not be more than 50 characters\n");
        returnCode = -1;
        return returnCode;
    }

    /*---UNSAFE FUNCTION---*/
    strcat(file_name,".inex");

    if (returnCode = removeFile(file_name) != 0) 
        printErrorMessage(-10);

    return returnCode;
}