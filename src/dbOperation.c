#include <stdio.h>

#include "headers/definition.h"
#include "headers/customFunctions.h"
#include "headers/fileOperation.h"
#include "headers/recordFunctions.h"

int addRecordList(Database *db);
int saveDb(Database *db);
int isDbSaved(Database *db);

int addRecordList(Database *db) {
    RecordList *node = NULL;
    RecordList *tail = NULL;
    int returnCode = 0;

    if (db == NULL) {
        printErrorMessage(-2);
        return -2;
    }

    node = getRecordList(db->dbMetaData.fileMetaData.counter, &returnCode);
    if (returnCode < 0)
        return returnCode;

    if (node == NULL) 
        return -1;
    
    if (node->next != NULL) {
        printErrorMessage(-9);
        return -9;
    }

    if (db->recordList == NULL) {
        db->recordList = node;
    } else {
        tail = db->recordList;
        while (tail->next != NULL) {
            tail = tail->next;
        }
        tail->next = node;
    }

    db->dbMetaData.fileMetaData.counter++;    
    db->dbMetaData.fileMetaData.totalRecord++;  
    db->dbMetaData.metaData.isModified = 1;
                
    return 0;
}

int saveDb(Database *db) {
    int temp_isSaved;
    int temp_isModified;

    if (db == NULL) {
        printErrorMessage(-2);
        return -2;
    }

    if (isDbSaved(db) == 1) {
        fprintf(stdout,"\n\tMESSAGE: File is already saved!\n");
        return 1;
    }

    temp_isSaved = db->dbMetaData.metaData.isSaved;
    temp_isModified = db->dbMetaData.metaData.isModified;

    db->dbMetaData.metaData.isSaved = 1;
    db->dbMetaData.metaData.isModified = 0;

    if (saveFile(db) == 0) {
        fprintf(stdout,"\n\tMESSAGE: FILE saved successfully!\n");
        return 0;
    }

    db->dbMetaData.metaData.isSaved = temp_isSaved;
    db->dbMetaData.metaData.isModified = temp_isModified;
    fprintf(stdout,"\n\tERROR: Failed to save FILE\n");

    return -1;
}

int isDbSaved(Database *db) {
    if (db == NULL) {
        printErrorMessage(-2);
        return -2;
    }

    if (db->dbMetaData.metaData.isSaved == 1 
            && db->dbMetaData.metaData.isModified == 0) {
        return 1;
    }

    return 0;
}