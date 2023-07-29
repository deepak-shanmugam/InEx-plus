#include<stdio.h>
#include<string.h>

#include"headers/loadDatabase.h"

int loadDatabase(int isNew);

/*---For Testing purpose---*/
#include<stdlib.h>
#include"headers/fileOperation.h" 
void testFileSaveFunction(Database *db);
//void testFileOpenFunction(char *str);
void printDatabase(Database *db);
void printRecordList(List *list);
/*---End of Testing header---*/


int loadDatabase(int isNew) 
{
    Database *db;    

    if(isNew != 0) {
        db = createDatabase();
        testFileSaveFunction(db);
    } else {
        db = openDatabase();
        /*---Test Open---*/
        printf("\t\nOpening the file: \n");
        db = openFile("test_file.bin");
    }

    
    printDatabase(db);
    printRecordList(db->records);

    return 0;
}

/*---TEST FUNCTIONS---*/
void testFileSaveFunction(Database *db) {
    if (db == NULL) {
        printf("\n\tError: unable to test SAVE funtion. db is NULL\n");
        return;
    }

    Date d1 = { .year=2022, .month=12, .day=27, .hour=20, .minute=15, .second=0 };
    Date d2 = { .year=1999, .month=7, .day=5, .hour=19, .minute=30, .second=15 };
    
    Record r1 = {1,d1,500,"Amma","No comments",0,1,0,d1,d1};
    Record r2 = {2,d2,135,"Deepak","Nothing to do with",0,1,0,d1,d1};

    strcpy(db->fileName,"test_file.bin");
    db->counter = 2;
    db->totalRecord = 2;
    db->isDeleted = 0;
    db->isSaved = 1;
    db->isModified = 1;
    db->modifiedDate = d1;
    db->createdDate = d1;

    db->records = (List *) calloc (1,sizeof(List));
    List *l1 = db->records;

    l1->record = r1;
    l1->next = (List *) calloc (1,sizeof(List));
    l1 = l1->next;
    l1->record = r2;
    l1->next = NULL;

    if(saveFile(db) == 0) {
        printf("\t\nSuccessfully saved the file: %s\n",db->fileName);
    }
}

void printDatabase(Database *db) 
{
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
    printf("Modified year: %d, month: %d, day: %d\n"
        ,db->modifiedDate.year,db->modifiedDate.year,db->modifiedDate.year);
    printf("Created year: %d, month: %d, day: %d\n"
        ,db->createdDate.year,db->createdDate.month,db->createdDate.day);
    printf("\n*****************\n");
}

void printRecordList(List *list) {
    if (list == NULL) {
        printf("\t\nRecord List is empty\n");
        return;
    }       
    printf("\n\n*******Records********\n");
    while(list!=NULL) {
        Record temp = list->record;
        printf("Id: %d, Date: %04d-%02d-%02d, Amount: %ld, To/From: %s, Comment: %s\n",
            temp.id,temp.date.year,temp.date.month,temp.date.day,
            temp.amount,temp.toFrom,temp.comment);
        printf("isDeleted: %d, isSaved: %d, isModified: %d, tag: %d\n",
            temp.isDeleted,temp.isSaved,temp.isModified,temp.tag);
        printf("Modified Date: %04d-%02d-%02d, Created Date: %04d-%02d-%02d\n",
            temp.modifiedDate.year,temp.modifiedDate.month,temp.modifiedDate.day,
            temp.createdDate.year,temp.createdDate.month,temp.createdDate.day);
        printf("\n");
        list = list->next;
    }
    printf("*******End of Records********\n");
}