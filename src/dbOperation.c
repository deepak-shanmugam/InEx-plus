#include <stdio.h>

#include "headers/definition.h"
#include "headers/customFunctions.h"
#include "headers/recordFunctions.h"

int addRecordList(Database *db);

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