#include<stdio.h>
#include<string.h>

#include"headers/loadDatabase.h"

int loadDatabase(int open);
static char* chooseFileToOpen();

int loadDatabase(int open) 
{
    Database *db = NULL;    
    char file_name[64];

    if (open) {
        db = openDatabase(chooseFileToOpen());
    } else {
        db = createDatabase();
    }
    
    if(db == NULL) {
        return -1;
    }

    return 0;
}

static char* chooseFileToOpen() {
    char file_name[64] = "test.bin";

    return file_name;
}