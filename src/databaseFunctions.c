#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"headers/definition.h"
#include"headers/customFunctions.h"

#define MAX_FILENAME_LENGTH 50

int setDbMetaData(DbMetaData *ptr);
int setMetaData(MetaData *ptr, int isDeleted, int isSaved, int isModified);
int setFileName(char *str, int length, int checkExist);  
int isFileExist(const char *file_name);
int freeDatabase(Database *db);

static int setCurrentDate(Date *ptr);
static int setFileMetaData(FileMetaData *ptr, int counter, int totalRecord);     
static int isValidFileName(const char *str, int length, int checkExist);

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

int setMetaData(MetaData *ptr, int isDeleted, int isSaved, int isModified) 
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
    ptr->month = 0;
    ptr->day = 0;
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
    
    if ((returnCode = setFileName(ptr->fileName, sizeof(ptr->fileName), 1)) != 0) {
        return returnCode;
    }
    
    ptr->counter = counter;
    ptr->totalRecord = totalRecord;

    return 0;
}

int setFileName(char *str, int length, int checkExist) 
{
    int validity = 0;
    int counter = 3;

    if (str == NULL || length <= MAX_FILENAME_LENGTH) {
        printErrorMessage(-2);
        return -2;
    }

    while (validity == 0 && counter > 0) {
        fprintf(stdout,"\n\tEnter FILENAME: ");

        validity = getStringInput(stdin, str, length);

        if (validity == 0) {
            validity = -4;
        }

        if (validity == -1) {
            printErrorMessage(-3);
            return -3;
        }

        if (validity == -2) {
            printErrorMessage(-2);
            return -2;
        }

        if (validity > MAX_FILENAME_LENGTH) {
            /*---Error Message---*/
            fprintf(stdout,"\n\tERROR: only upto %d characters allowed\n"
                , MAX_FILENAME_LENGTH);
            validity = 0;
        }

        if (validity > 0 && validity <= MAX_FILENAME_LENGTH) {
            validity = isValidFileName(str, length, checkExist);

            if (validity == 0) {
                /*---UNSAFE FUNCTIONS will be replaced---*/
                strcat(str,".inex");
                return 0;
            }

            if (validity == -1) {
                /*---Error Message---*/
                fprintf(stdout,"\n\tERROR: File name can only contains "
                    "'AlphaNumerics' or '-' or '_'\n");
                validity = 0;
            }

            if (validity == -2) {
                printErrorMessage(-9);
                return -2;
            }

            if (validity == -4) {
                /*---Error Message---*/
                fprintf(stdout,"\n\tERROR: FILE is already existing\n");
                validity = 0;
            }
        }

        if (validity != 0) {
            printErrorMessage(-4);
            return -1;
        }

        counter--;
    }

    //fprintf(stdout,"\n\tMESSAGE: Too many attemps!\n");

    return -1;
}

static int isValidFileName(const char *str, int length, int checkExist) 
{
    int i;
    char buffer[FILE_NAME_LENGTH];

    if (str == NULL || length <= MAX_FILENAME_LENGTH) {
        printErrorMessage(-2);
        return -2;
    }

    for (i = 0; (i < length) && (str[i] != '\0'); i++) {
        if (i == length-1) {
            return -2;
        }
        if ((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z') ||
            (str[i] >= '0' && str[i] <= '9') || (str[i] == '-') || (str[i] == '_')) {
                continue;
        }
        return -1;
    }

    /*---UNSAFE FUNCTION will be replaced---*/
    strncpy(buffer,str,64);
    strcat(buffer,".inex");

    if (checkExist != 0) {
        if (isFileExist(buffer) != 0) {
            return -4;
        }
    }

    return 0;
}

int isFileExist(const char *file_name) 
{
    FILE *fp;

    if (file_name == NULL) {
        printErrorMessage(-2);
        return -2;
    }

    fp = fopen(file_name,"rb");

    if (fp == NULL) 
        return 0;

    fclose(fp);

    return -1;
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

    printf("\n\tDEBUG: Successfully cleared the data from memory\n");

    return 0;
}