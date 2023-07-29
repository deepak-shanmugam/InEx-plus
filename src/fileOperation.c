#include<stdio.h>
#include<stdlib.h>

#include"headers/definition.h"

Database* openFile(char *file_name);
int saveFile(Database *db);

static int writeDatabase(Database *db, FILE *fp);
static Database* readDatabase(FILE *fp);

Database* openFile(char *file_name)
{
    Database *db = NULL;
    FILE *fp;

    fp = fopen(file_name,"rb");
    if (fp == NULL) {
        /*---Error Message---*/
        fprintf(stdout,"\n\tError: Unable to open the file\n");
        return NULL;
    }
    
    db = readDatabase(fp);

    fclose(fp);
    return db;
}

int saveFile(Database *db)
{
    FILE *fp;
    int flag = 0;

    if (db == NULL)
        return -1;

    fp = fopen(db->fileName,"wb");
    if (fp == NULL) {
        /*---Error Message---*/
        fprintf(stdout,"\t\nError: Unable to save\n");
        return -1;
    }

    if (writeDatabase(db,fp) == -1) {
        /*---Error Message---*/
        fprintf(stdout,"\t\nError: Error occured while saving file.\n");
        remove(db->fileName);
        flag = -1;
    }
    fclose(fp);
    return flag;
}

static int writeDatabase(Database *db, FILE *fp) 
{
    /*---Will Try to improve this function implementation later---*/
    List *ptr = NULL;

    if (db == NULL || fp == NULL) 
        return -1;

    if (fwrite(&db->fileName,sizeof(db->fileName),1,fp) == 0) 
        return -1;
    if (fwrite(&db->counter,sizeof(db->counter),1,fp) == 0) 
        return -1;
    if (fwrite(&db->totalRecord,sizeof(db->totalRecord),1,fp) == 0) 
        return -1;
    if (fwrite(&db->isDeleted,sizeof(db->isDeleted),1,fp) == 0) 
        return -1;
    if (fwrite(&db->isSaved,sizeof(db->isSaved),1,fp) == 0) 
        return -1;
    if (fwrite(&db->isModified,sizeof(db->isModified),1,fp) == 0) 
        return -1;
    if (fwrite(&db->createdDate,sizeof(db->createdDate),1,fp) == 0) 
        return -1;
    if (fwrite(&db->modifiedDate,sizeof(db->modifiedDate),1,fp) == 0) 
        return -1;

    ptr = db->records;
    while(ptr != NULL) {
        if (fwrite(&ptr->record,sizeof(ptr->record),1,fp) == 0) 
            return -1;
        ptr = ptr->next;
    }

    return 0;
}

static Database* readDatabase(FILE *fp) {
    /*---Will Try to improve this function implementation later---*/
    Database *db = NULL;
    Record currentRecord;
    List *currentList = NULL;

    db = (Database *)calloc(1,sizeof(*db));
    if (fread(db->fileName,sizeof(db->fileName),1,fp) == 0) 
        goto clear;
    if (fread(&db->counter,sizeof(db->counter),1,fp) == 0) 
        goto clear;
    if (fread(&db->totalRecord,sizeof(db->totalRecord),1,fp) == 0) 
        goto clear;
    if (fread(&db->isDeleted,sizeof(db->isDeleted),1,fp) == 0) 
        goto clear;
    if (fread(&db->isSaved,sizeof(db->isSaved),1,fp) == 0) 
        goto clear;
    if (fread(&db->isModified,sizeof(db->isModified),1,fp) == 0) 
        goto clear;
    if (fread(&db->createdDate,sizeof(db->createdDate),1,fp) == 0) 
        goto clear;
    if (fread(&db->modifiedDate,sizeof(db->modifiedDate),1,fp) == 0) 
        goto clear;
    
    while(fread(&currentRecord,sizeof(currentRecord),1,fp) > 0) {
        if(db->records == NULL) {
            db->records = (List *)calloc(1,sizeof(List));
            currentList = db->records;
        } else {
            currentList->next = (List *)calloc(1,sizeof(List));
            currentList = currentList->next;
        }
        currentList->record = currentRecord;
        currentList->next = NULL;
    }

    return db;

clear:
    free(db);
    db = NULL;
    return db;
}