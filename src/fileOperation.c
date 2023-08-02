#include<stdio.h>
#include<stdlib.h>

#include"headers/definition.h"
#include"headers/customFunctions.h"
#include"headers/databaseFunctions.h"

Database* openFile(const char *file_name);
int saveFile(Database *db);
int removeFile(const char *file_name);

static int writeDatabase(Database *db, FILE *fp);
static Database* readDatabase(FILE *fp);

Database* openFile(const char *file_name)
{
    Database *db = NULL;
    FILE *fp;

    if (file_name == NULL) {
        printErrorMessage(-2);
        return NULL;
    }

    fp = fopen(file_name,"rb");
    if (fp == NULL) {
        printErrorMessage(-5);
        return NULL;
    }
    
    db = readDatabase(fp);
    if (db == NULL) {
        printErrorMessage(-6);
    }

    fclose(fp);
    return db;
}

int saveFile(Database *db)
{
    FILE *fp;
    int returnCode = 0;

    if (db == NULL) {
        printErrorMessage(-2);
        return -1;
    }

    fp = fopen(db->dbMetaData.fileMetaData.fileName,"wb");
    if (fp == NULL) {
        printErrorMessage(-5);
        return -1;
    }

    if (writeDatabase(db,fp) != 0) {
        printErrorMessage(-7);
        returnCode = -1;
    }

    fclose(fp);
    return returnCode;
}

int removeFile(const char *file_name) 
{
    if (file_name == NULL) {
        printErrorMessage(-2);
        return -1;
    }

    return remove(file_name);
}

static int writeDatabase(Database *db, FILE *fp) 
{
    RecordList *ptr = NULL;

    if (db == NULL || fp == NULL) {
        printErrorMessage(-2);
        return -1;
    }

    if (fwrite(&db->dbMetaData, sizeof(db->dbMetaData), 1, fp) <= 0) 
        return -1;

    ptr = db->recordList;
    while (ptr != NULL) {
        if (fwrite(&ptr->record, sizeof(ptr->record), 1, fp) <= 0) 
            return -1;
        ptr = ptr->next;
    }

    return 0;
}

static Database* readDatabase(FILE *fp) 
{
    Database *db = NULL;
    RecordList *currentRecordList = NULL;
    Record currentRecord;

    if (fp == NULL) {
        printErrorMessage(-2);
        return NULL;
    }

    db = (Database *)calloc(1, sizeof(*db));
    if (db == NULL) {
        printErrorMessage(-8);
        return NULL;
    }
        
    if (fread(&db->dbMetaData, sizeof(db->dbMetaData), 1, fp) <= 0)
        goto clearDB;
    
    while (fread(&currentRecord, sizeof(currentRecord), 1, fp) > 0) {
        if (db->recordList == NULL) {
            db->recordList = (RecordList *)calloc(1, sizeof(RecordList));
            if (db->recordList == NULL) {
                printErrorMessage(-8);
                goto clearDB;
            }
            currentRecordList = db->recordList;
        } else {
            currentRecordList->next = (RecordList *)calloc(1, sizeof(RecordList));
            if (currentRecordList->next == NULL) {
                printErrorMessage(-8);
                goto clearDB;
            }
            currentRecordList = currentRecordList->next;
        }
        currentRecordList->record = currentRecord;
        currentRecordList->next = NULL;
    }

    return db;

clearDB:
    freeDatabase(db);
    db = NULL;
    return db;
}