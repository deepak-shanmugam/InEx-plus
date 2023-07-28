#include<stdio.h>
#include<string.h>

#include"headers/loadDatabase.h"

int loadFile(int isNew);
void printDatabase(Database *db);

int loadFile(int isNew) {
    Database *db;    
    printf("Debug: loadFile()\n");
    if(isNew != 0) {
        db = createDatabase();
    } else {
        db = openDatabase();
    }

    printDatabase(db);

    return 0;
}

void printDatabase(Database *db) {
    if (db == NULL) {
        printf("\nDataBase is null\n");
        return;
    }
    printf("\n*****************\n");
    printf("record pointer: %p\n",db->records);
    printf("filename: %s, strlen: %lu\n",db->fileName,strlen(db->fileName));
    printf("counter: %d\n",db->counter);
    printf("totalRecord: %d\n",db->totalRecord);
    printf("isDeleted: %d\n",db->isDeleted);
    printf("isSaved: %d\n",db->isSaved);
    printf("isModified: %d\n",db->isModified);
    printf("Created year: %d, month: %d, day: %d\n"
        ,db->CreatedDate.year,db->CreatedDate.month,db->CreatedDate.day);
    printf("Modified year: %d, month: %d, day: %d\n"
        ,db->LastModifiedDate.year,db->LastModifiedDate.year,db->LastModifiedDate.year);
    printf("\n*****************\n");
}