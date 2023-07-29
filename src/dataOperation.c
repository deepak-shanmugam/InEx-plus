#include<stdio.h>
#include<string.h>

#include"headers/loadDatabase.h"

int loadDatabase(int isNew);

int loadDatabase(int isNew) 
{
    Database *db = NULL;    

    if (isNew != 0) {
        db = createDatabase();
    } else {
        db = openDatabase();
    }
    
    if(db == NULL) {
        return -1;
    }
    return 0;
}