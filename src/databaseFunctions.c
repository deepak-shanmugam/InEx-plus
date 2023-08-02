#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"headers/definition.h"
#include"headers/customFunctions.h"

#define MAX_FILENAME_LENGTH 50

int setDbMetaData(DbMetaData *ptr);
int freeDatabase(Database *db);

static int setMetaData(MetaData *ptr, int isDeleted, int isSaved, int isModified);
static int setCurrentDate(Date *ptr);
static int setFileMetaData(FileMetaData *ptr, int counter, int totalRecord);       
static int setFileName(char *str, int length);
static int isValidFileName(const char *str, int length);

int setDbMetaData(DbMetaData *ptr)
{
    int returnCode = 0;

    if (ptr == NULL) {
        printErrorMessage(-2);
        return -1;
    }

    if (setMetaData(&ptr->metaData, 0, 0, 0) != 0)
        return -1;

    if ((returnCode = setFileMetaData(&ptr->fileMetaData, 1, 0)) != 0) 
        return returnCode;

    return 0;
}

static int setMetaData(MetaData *ptr, int isDeleted, int isSaved, int isModified) 
{
    if (ptr == NULL) {
        printErrorMessage(-2);
        return -1;
    }

    if (setCurrentDate(&ptr->createdDate) != 0) 
        return -1;

    if (setCurrentDate(&ptr->modifiedDate) != 0)
        return -1;

    ptr->isDeleted = isDeleted;
    ptr->isSaved = isSaved;
    ptr->isModified = isModified;

    return 0;
}

static int setCurrentDate(Date *ptr) 
{
    if (ptr == NULL) {
        printErrorMessage(-2);
        return -1;
    }

    /*---IMPLEMENT THE FUNCTION TO ASSIGN THE EXACT CURRENT DATE LATER---*/

    ptr->year = 0;
    ptr->month = 1;
    ptr->day = 1;
    ptr->hour = 0;
    ptr->minute = 0;
    ptr->second = 0;

    return 0;
}  

static int setFileMetaData(FileMetaData *ptr, int counter, int totalRecord) 
{
    int returnCode = 0;

    if (ptr == NULL) {
        printErrorMessage(-2);
        return -1;
    }
    
    if ((returnCode = setFileName(ptr->fileName, sizeof(ptr->fileName))) != 0) {
        if (returnCode == -1)
            return -3;
        return -1;
    }
    
    strcat(ptr->fileName, ".bin");
    ptr->counter = counter;
    ptr->totalRecord = totalRecord;

    return 0;
}

static int setFileName(char *str, int length) 
{
    int validity = 0;
    int check;

    if (str == NULL || length <= MAX_FILENAME_LENGTH) {
        printErrorMessage(-2);
        return -2;
    }

    while (validity == 0) {
        fprintf(stdout,"\nPlease enter 'New' FileName: ");

        validity = getStringInput(stdin, str, length);

        if (validity < -1) {
            printErrorMessage(-2);
            return validity;
        }
        if (validity == -1) {
            printErrorMessage(-3);
            return validity;
        }
        if (validity == 0) {
            /*---Error Message---*/
            fprintf(stdout,"\n\tERROR: please enter atleast 1 character\n");
            continue;
        } 
        if (validity > MAX_FILENAME_LENGTH) {
            /*---Error Message---*/
            fprintf(stdout,"\n\tERROR: only upto %d characters allowed\n",MAX_FILENAME_LENGTH);
            validity = 0;
            continue;
        }

        check = isValidFileName(str, length);
        if (check == -1) {
            /*---Error Message---*/
            fprintf(stdout,"\n\tERROR: File name can only contains 'AlphaNumerics' or '-' or '_'\n");
            validity = 0;
        }
        if (check == -2) {
            printErrorMessage(-9);
            return check;
        }
        if (check == -3) {
            /*---Error Message---*/
            fprintf(stdout,"\n\tERROR: File name already existing\n");
            validity = 0;
        }
    }

    return 0;
}

static int isValidFileName(const char *str, int length) 
{
    int i = 0;

    if (str == NULL || length <= MAX_FILENAME_LENGTH) {
        printErrorMessage(-2);
        return -2;
    }

    for ( ; (i < length) && (str[i] != '\0'); i++) {
        if (i == length-1) {
            return -2;
        }
        if ((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z') ||
            (str[i] >= '0' && str[i] <= '9') || (str[i] == '-') || (str[i] == '_')) {
                continue;
        }
        return -1;
    }
    /*
        IMPLEMENT VALIDATION AGAINST EXISTING FILE NAMES
    */
    return 0;
}

int freeDatabase(Database *db) 
{
    RecordList *currentRecordList = NULL;
    RecordList *previousRecordList = NULL;

    if (db == NULL) {
        printErrorMessage(-2);
        return -1;
    }

    currentRecordList = db->recordList;
    while (currentRecordList != NULL) {
        previousRecordList = currentRecordList;
        currentRecordList = currentRecordList->next;
        free(previousRecordList);
    }

    free(db);

    printf("\n\tMESSAGE: Successfully cleared the data from memory\n");

    return 0;
}