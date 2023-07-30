#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"headers/definition.h"      //definition.h should always comes first
#include"headers/customFunctions.h"
#include"headers/fileOperation.h"

#define MAX_FILENAME_LENGTH 50

Database* createDatabase();                         
Database* openDatabase();   
static int setDbMetaData(DbMetaData *ptr);
static int setMetaData(MetaData *ptr);
static int setCurrentDate(Date *ptr);
static int setFileMetaData(FileMetaData *ptr);       
static int setFileName(char *str, int length); 
static int isValidFileName(char *str, int length);              
static char* selectFileToOpen();                    //pending

Database* createDatabase() 
{
    Database *db = NULL;

    db = (Database *)calloc(1, sizeof(*db));
    if (db == NULL)
        return NULL;

    if(setDbMetaData(&db->dbMetaData) != 0) {
        free(db);
        return NULL;
    }
    
    db->recordList = NULL;

    return db;
}

Database* openDatabase() 
{
    Database *db = NULL;

    return db;
}

static int setDbMetaData(DbMetaData *ptr)
{
    if (ptr == NULL) 
        return -1;

    if (setMetaData(&ptr->metaData) != 0)
        return -1;

    if (setFileMetaData(&ptr->fileMetaData) != 0) 
        return -1;

    return 0;
}

static int setMetaData(MetaData *ptr) 
{
    if (ptr == NULL)
        return -1;

    if (setCurrentDate(&ptr->createdDate) != 0) 
        return -1;

    if (setCurrentDate(&ptr->modifiedDate) != 0)
        return -1;

    ptr->isDeleted = 0;
    ptr->isSaved = 0;
    ptr->isModified = 0;

    return 0;
}

static int setCurrentDate(Date *ptr) 
{
    if (ptr == NULL)
        return -1;

    /*---IMPLEMENT THE FUNCTION TO ASSIGN THE EXACT CURRENT DATE LATER---*/
    ptr->year = 0;
    ptr->month = 1;
    ptr->day = 1;
    ptr->hour = 0;
    ptr->minute = 0;
    ptr->second = 0;

    return 0;
}  

static int setFileMetaData(FileMetaData *ptr) 
{
    if (ptr == NULL)
        return -1;
    
    if (setFileName(ptr->fileName, sizeof(ptr->fileName)) != 0)
        return -1;

    strcat(ptr->fileName, ".bin");
    ptr->counter = 1;
    ptr->totalRecord = 0;

    return 0;
}

static int setFileName(char *str, int length) 
{
    int validity = 0;
    int check;

    if(str == NULL || length <= MAX_FILENAME_LENGTH) {
        /*---Error Message---*/
        fprintf(stdout,"\n\tError: Something went wrong\n");
        return -1;
    }

    while(validity == 0) {
        fprintf(stdout,"\nplease enter New FileName: ");

        validity = getStringInput(stdin, str, length);
        if (validity == -1) {
            /*---Error Message---*/
            fprintf(stdout,"\n\tError: Unable to get input\n");
            return validity;
        }
        if (validity == 0) {
            /*---Error Message---*/
            fprintf(stdout,"\n\tError: Enter atleast 1 character\n");
            continue;
        } 
        if (validity > MAX_FILENAME_LENGTH) {
            /*---Error Message---*/
            fprintf(stdout,"\n\tError: only upto %d characters allowed\n",MAX_FILENAME_LENGTH);
            validity = 0;
            continue;
        }

        check = isValidFileName(str, MAX_FILENAME_LENGTH);
        if (check == -1) {
            /*---Error Message---*/
            fprintf(stdout,"\n\tError: File name can only contains 'AlphaNumerics' or '-' or '_'\n");
            validity = 0;
        }
        if (check == -2) {
            /*---Error Message---*/
            fprintf(stdout,"\n\tError: File name already existing. please give another\n");
            validity = 0;
        }
    }

    return 0;
}

static int isValidFileName(char *str, int length) 
{
    int i = 0;

    if(str == NULL || length < MAX_FILENAME_LENGTH) {
        return -1;
    }

    for( ; (i <= length) && (str[i] != '\0'); i++) {
        if((str[i]>='a' && str[i]<='z') || (str[i]>='A' && str[i]<='Z') ||
            (str[i]>='0' && str[i]<='9') || (str[i]=='-') || (str[i]=='_')) {
                continue;
        }
        return -1;
    }
    /*
        IMPLEMENT VALIDATION AGAINST EXISTING FILE NAMES
    */
    return 0;
}