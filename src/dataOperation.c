#include<stdio.h>
#include<string.h>

#include"headers/loadDatabase.h"

int loadDatabase(int isNew);

/*---For Testing purpose---*/
#include<stdlib.h>
#include"headers/fileOperation.h" 
void testFileSaveFunction(Database *db);
void printDbMetaData(DbMetaData md);
void printRecordList(RecordList *list);
/*---End of Testing header---*/

int loadDatabase(int isNew) 
{
    Database *db = NULL;    

    if (isNew != 0) {
        db = createDatabase();
        testFileSaveFunction(db);
    } else {
        db = openDatabase();
        printf("\t\nOpening the file: \n");
        db = openFile("test_file.bin");
    }
    
    if(db == NULL) {
        return -1;
    }
    printDbMetaData(db->dbMetaData);
    printRecordList(db->recordList);

    return 0;
}

/*---TEST FUNCTIONS---*/
void testFileSaveFunction(Database *db) 
{
    if (db == NULL) {
        printf("\n\tError: unable to test SAVE funtion. db is NULL\n");
        return;
    }

    Date d1 = { .year=2022, .month=12, .day=27, .hour=20, .minute=15, .second=0 };
    Date d2 = { .year=1999, .month=7, .day=5, .hour=19, .minute=30, .second=15 };

    MetaData md1 = {0, 1, 0, d1, d1};

    CoreData cd1 = {1, 5000, "Deepak", "No comments", d2, 20};
    CoreData cd2 = {2, 125, "Amazon", "Cash back", d1, 150};

    FileMetaData fmd1 = {"test_file.bin", 2, 2};
    
    DbMetaData dmd1 = {md1, fmd1};

    Record r1 = {md1, cd1};
    Record r2 = {md1, cd2};

    db->dbMetaData = dmd1;
    db->recordList = (RecordList *) calloc (1, sizeof(RecordList));

    RecordList *currentRecordList = db->recordList;

    currentRecordList->record = r1;
    currentRecordList->next = (RecordList *) calloc (1, sizeof(RecordList));
    currentRecordList = currentRecordList->next;
    currentRecordList->record = r2;
    currentRecordList->next = NULL;

    if(saveFile(db) == 0) {
        printf("\t\nSuccessfully saved the file: %s\n",db->dbMetaData.fileMetaData.fileName);
    }
}

void printDbMetaData(DbMetaData md) 
{
    printf("\t\n*********META DATA********\n");
    printf("Filename: %s, length: %lu (Excluding the file format)\n"
        ,md.fileMetaData.fileName, strlen(md.fileMetaData.fileName) - 4);
    printf("Active counter: %d\n",md.fileMetaData.counter);
    printf("Total number of Records: %d\n",md.fileMetaData.totalRecord);
    printf("isDeleted: %d\n",md.metaData.isDeleted);
    printf("isSaved: %d\n",md.metaData.isSaved);
    printf("isModified: %d\n",md.metaData.isModified);
    printf("Modified Date: %04d-%02d-%02d %02d:%02d:%02d\n",
        md.metaData.modifiedDate.year, md.metaData.modifiedDate.month, md.metaData.modifiedDate.day,
        md.metaData.modifiedDate.hour, md.metaData.modifiedDate.minute, md.metaData.modifiedDate.second);
    printf("Created Date: %04d-%02d-%02d %02d:%02d:%02d\n",
        md.metaData.createdDate.year, md.metaData.createdDate.month, md.metaData.createdDate.day,
        md.metaData.createdDate.hour, md.metaData.createdDate.minute, md.metaData.createdDate.second);
    printf("\t\n**************************\n");
}

void printRecordList(RecordList *list) 
{
    Record temp;

    if (list == NULL) {
        printf("\n\t<Empty Records>\n");
        return;
    }       

    printf("\n\n********Beginning********\n");
    while (list != NULL) {
        Record temp = list->record;
        printf("Id: %d, Date: %04d-%02d-%02d, Amount: %ld, To/From: %s, Comment: %s\n",
            temp.coreData.id,
            temp.coreData.date.year, temp.coreData.date.month, temp.coreData.date.day,
            temp.coreData.amount, temp.coreData.toFrom, temp.coreData.comment);
        printf("isDeleted: %d, isSaved: %d, isModified: %d, tag: %d\n",
            temp.recordMetaData.isDeleted, temp.recordMetaData.isSaved,
            temp.recordMetaData.isModified, temp.coreData.tag);
        printf("Modified Date: %04d-%02d-%02d %02d:%02d:%02d, ",
            temp.recordMetaData.modifiedDate.year, temp.recordMetaData.modifiedDate.month,
            temp.recordMetaData.modifiedDate.day, temp.recordMetaData.modifiedDate.hour,
            temp.recordMetaData.modifiedDate.minute, temp.recordMetaData.modifiedDate.second);
        printf("Created Date: %04d-%02d-%02d %02d:%02d:%02d\n",
            temp.recordMetaData.createdDate.year, temp.recordMetaData.createdDate.month,
            temp.recordMetaData.createdDate.day, temp.recordMetaData.createdDate.hour,
            temp.recordMetaData.createdDate.minute, temp.recordMetaData.createdDate.second);
        printf("\n");
        list = list->next;
    }
    printf("********End of Records********\n");
}