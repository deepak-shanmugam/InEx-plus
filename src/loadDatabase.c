#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"headers/definition.h"
#include"headers/customFunctions.h"

Database* createDatabase();                         
Database* openDatabase();                           

static int setFileName(char *str, int length); 
static int isValidFileName(char *str, int length);              
static char * selectFileToOpen();                   //pending

Database* createDatabase() {
    int validity;
    Database *db;

    //printf("Debug: createDatabase()\n");
    db = (Database *)calloc(1,sizeof(*db));

    validity = setFileName(db->fileName,sizeof(db->fileName));
    if(validity == -1) {
        free(db);
        return NULL;
    }

    return db;
}

Database* openDatabase() {
    Database *db;
    return NULL;
}

static int setFileName(char *str, int length) {
    int validity = 0, check = 0;

    while(validity == 0) {
        fprintf(stdout,"\nplease enter New FileName: ");

        validity = getStringInput(stdin,str,length);
        if(validity == -1) {
            /*---Error Message---*/
            fprintf(stdout,"\n\tError: Unable to get input\n");
            return validity;
        }
        if(validity == 0) {
            /*---Error Message---*/
            fprintf(stdout,"\n\tError: Enter atleast 1 character\n");
            continue;
        } 
        if(validity >= length) {
            /*---Error Message---*/
            fprintf(stdout,"\n\tError: only a maximum of %d characters allowed\n",length-1);
            validity = 0;
            continue;
        }

        check = isValidFileName(str,length);
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

static int isValidFileName(char *str, int length) {
    int i = 0;
    for( ; i<length && str[i] != '\0'; i++) {
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