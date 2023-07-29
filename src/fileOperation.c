#include<stdio.h>
#include<stdlib.h>

#include"headers/definition.h"

Database* openFile(char *file_name);
int saveFile(Database *db);
static int writeDatabase(Database *db, FILE *fp);
static Database* readDatabase(FILE *fp);
static void freeDataBase(Database *db);

Database* openFile(char *file_name)
{
    Database *db = NULL;
    FILE *fp;

    if (file_name == NULL) {
        /*---Error Message---*/
        fprintf(stdout,"\n\tError: FileName cannot be <NULL>\n");
        return NULL;
    }

    fp = fopen(file_name,"rb");
    if (fp == NULL) {
        /*---Error Message---*/
        fprintf(stdout,"\n\tError: Unable to open the file\n");
        return NULL;
    }
    
    db = readDatabase(fp);
    if (db == NULL) {
        /*---Error Message---*/
        fprintf(stdout,"\n\tError: Unable to read the file\n");
    }

    fclose(fp);
    return db;
}

int saveFile(Database *db)
{
    FILE *fp;
    int validity = 0;

    if (db == NULL) {
        /*---Error Message---*/
        fprintf(stdout,"\n\tError: Database cannot be <NULL> while saving\n");
        return -1;
    }

    fp = fopen(db->dbMetaData.fileMetaData.fileName,"wb");
    if (fp == NULL) {
        /*---Error Message---*/
        fprintf(stdout,"\t\nError: Unable to save file\n");
        return -1;
    }

    if (writeDatabase(db,fp) != 0) {
        /*---Error Message---*/
        fprintf(stdout,"\t\nError: Error occured while writing file\n");
        //remove(db->fileName);
        validity = -1;
    }

    fclose(fp);
    return validity;
}

static int writeDatabase(Database *db, FILE *fp) 
{
    RecordList *ptr = NULL;

    if (db == NULL || fp == NULL) 
        return -1;

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
    Record currentRecord;
    RecordList *currentRecordList = NULL;

    db = (Database *)calloc(1, sizeof(*db));

    if (fread(&db->dbMetaData, sizeof(db->dbMetaData), 1, fp) <= 0)
        goto clearDB;
    
    while (fread(&currentRecord, sizeof(currentRecord), 1, fp) > 0) {
        if (db->recordList == NULL) {
            db->recordList = (RecordList *)calloc(1, sizeof(RecordList));
            currentRecordList = db->recordList;
        } else {
            currentRecordList->next = (RecordList *)calloc(1, sizeof(RecordList));
            currentRecordList = currentRecordList->next;
        }
        currentRecordList->record = currentRecord;
        currentRecordList->next = NULL;
    }

    return db;

clearDB:
    freeDataBase(db);
    db = NULL;
    return db;
}

static void freeDataBase(Database *db) 
{
    RecordList *currentRecordList = NULL;
    RecordList *previousRecordList = NULL;

    if(db == NULL)
        return;

    currentRecordList = db->recordList;
    while (currentRecordList != NULL) {
        previousRecordList = currentRecordList;
        currentRecordList = currentRecordList->next;
        free(previousRecordList);
    }

    free(db);
    return;
}