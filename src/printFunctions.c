#include <stdio.h>

#include "headers/definition.h"
#include "headers/customFunctions.h"

void print_date(FILE *stream, Date *date, int withTime);
void print_metaData(FILE *stream, MetaData *md);
void print_fileMetaData(FILE *stream, FileMetaData *fmd);
void print_fileName(FILE *stream, char *str, int length, int isStarAdded);
void print_dbMetaData(FILE *stream, DbMetaData *dmd);

void print_date(FILE *stream, Date *date, int withTime) {
    if (date == NULL || stream == NULL) {
        printErrorMessage(-2);
        return;
    }
    fprintf(stream,"%04d-%02d-%02d", date->year, date->month, date->day);

    if (withTime != 0) {
        fprintf(stream," %02d:%02d:%02d", date->hour, date->minute, date->second);
    }
}

void print_metaData(FILE *stream, MetaData *md) {
    static const char status_text[] = "STATUS";
    static const char colon_text[] = ": ";
    static const char created_date_text[] = "CREATED DATE";
    static const char modified_date_text[] = "MODIFIED DATE";

    if (md == NULL || stream == NULL) {
        printErrorMessage(-2);
        return;
    }

    fprintf(stream,"%-20s%s", status_text, colon_text);
    if ((md->isSaved) == 0) {
        fprintf(stream,"%s","Not Saved");
    } else {
        if ((md->isModified) != 0) {
            fprintf(stream,"%s","Modified");
        } else {
            fprintf(stream,"%s","Saved");
        }
    }
    
    fprintf(stream,"\n");

    fprintf(stream,"%-20s%s", created_date_text, colon_text);
    print_date(stream,&md->createdDate,1);
    fprintf(stream,"\n");

    fprintf(stream,"%-20s%s", modified_date_text, colon_text);
    print_date(stream,&md->modifiedDate,1);
}

void print_fileMetaData(FILE *stream, FileMetaData *fmd) {
    static const char file_name_text[] = "FILE NAME";
    static const char colon_text[] = ": ";
    static const char no_of_record_text[] = "NO OF RECORDS";

    if (fmd == NULL || stream == NULL) {
        printErrorMessage(-2);
        return;
    }
    fprintf(stream,"%-20s%s", file_name_text, colon_text);
    print_fileName(stdout,fmd->fileName,FILE_NAME_LENGTH,0);
    fprintf(stream,"\n");

    fprintf(stream,"%-20s%s", no_of_record_text, colon_text);
    fprintf(stream,"%d",fmd->totalRecord);
    /*
    fprintf(stream,"\n");
    fprintf(stream,"COUNTER: ");
    fprintf(stream,"%d",fmd->counter);
    */
}

void print_fileName(FILE *stream, char *str, int length, int isStarAdded) {
    if (str == NULL || stream == NULL) {
        printErrorMessage(-2);
        return;
    }

    if (isStarAdded != 0) {
        fprintf(stream,"%c",'*');
    }
    print_string(stream,str,length);
}

void print_dbMetaData(FILE *stream, DbMetaData *dmd) {
    static const char header_text[] = "\n**********************FILE METADATA**********************\n";
    static const char footer_text[] = "\n***************************END***************************\n";

    if (stream == NULL || dmd == NULL) {
        printErrorMessage(-2);
        return;
    }

    fputs(header_text, stream);
    print_fileMetaData(stream,&dmd->fileMetaData);
    fprintf(stream,"\n");
    print_metaData(stream,&dmd->metaData);
    fputs(footer_text, stream);
}

/*
void print_coreData(FILE *stream, CoreData *data) {
    if (data == NULL || stream == NULL) {
        printErrorMessage(-2);
        return;
    }
    fprintf("")
}

void print_record(FILE *stream, Record *rec, int withMetaData) {

}

void print_recordList(FILE *stream, RecordList *list, int withMetaData) {

}

void print_database(FILE *stream, Database &db) {
    
}
*/