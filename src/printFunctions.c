#include <stdio.h>

#include "headers/definition.h"
#include "headers/customFunctions.h"

void print_database(FILE *stream, Database *db);
void print_dbMetaData(FILE *stream, DbMetaData *dmd);
void print_recordList(FILE *stream, RecordList *list
    , int withComment, int withMetaData, int count);
void print_date(FILE *stream, Date *date, int withTime);
void print_fileName(FILE *stream, char *str, int length, int isStarAdded);

static void print_record(FILE *stream, Record *rec, int withComment, int withMetaData);
static void print_coreData(FILE *stream, CoreData *data, int withComment);
static void print_fileMetaData(FILE *stream, FileMetaData *fmd);
static void print_metaData(FILE *stream, MetaData *md, int withStatus);

void print_database(FILE *stream, Database *db) 
{
    print_dbMetaData(stream, &db->dbMetaData);
    print_recordList(stream, db->recordList, 1, 1, -1);
}

void print_dbMetaData(FILE *stream, DbMetaData *dmd) 
{
    static const char header_text[] = 
        "\n**********************FILE METADATA**********************\n";
    static const char footer_text[] = 
        "\n***************************END***************************\n";

    if (stream == NULL || dmd == NULL) {
        printErrorMessage(-2);
        return;
    }

    fputs(header_text, stream);
    print_fileMetaData(stream,&dmd->fileMetaData);

    fprintf(stream,"\n");

    print_metaData(stream,&dmd->metaData, 1);
    fputs(footer_text, stream);
}

void print_recordList(FILE *stream, RecordList *list
            , int withComment, int withMetaData, int count) 
{
    static const char header_id[] = "ID";
    static const char header_amount[] = "AMOUNT";
    static const char header_date[] = "DATE";
    static const char header_toFrom[] = "TO/FROM";
    static const char header_underline[] = 
        "---------|"
        "---------------------|"
        "------------|"
        "-------------------------------|";
    static const char header_intendation[] = "         ";
    int i = 1;

    if (stream == NULL) {
        printErrorMessage(-3);
        return;
    }

    /*---HEADER---*/
    fprintf(stream, "\n%s\n",header_underline);
    fprintf(stream,"%8s | %19s | %10s | %-32s "
        , header_id, header_amount, header_date, header_toFrom);
    fprintf(stream, "\n%s\n",header_underline);

    if (list == NULL) {
        fprintf(stream,"\n\t<EMPTY RECORDS>\n");
        return;
    }

    while (list != NULL && (i <= count || count < 0)) {
        print_record(stream, &list->record, withComment, withMetaData);

        /*---If Any extra data needs to be printed---*/
        if (withMetaData != 0 || withComment != 0) {
            fprintf(stream, "%s\n",header_underline);
        }

        if (i == count && list->next != NULL) {
            fprintf(stream,"\n%s<--------LAST (%d) RECORDS-------->\n"
                , header_intendation, i);
            break;
        }

        list = list->next;
        i++;
    }

    if (list == NULL) {
        fprintf(stream,"\n%s|--------END OF RECORDS--------|\n"
            , header_intendation);
    }
}

void print_date(FILE *stream, Date *date, int withTime) 
{
    if (date == NULL || stream == NULL) {
        printErrorMessage(-2);
        return;
    }

    fprintf(stream,"%04d-%02d-%02d", date->year, date->month, date->day);

    if (withTime != 0) {
        fprintf(stream," %02d:%02d:%02d", date->hour, date->minute, date->second);
    }
}

void print_fileName(FILE *stream, char *str, int length, int isStarAdded) 
{
    if (str == NULL || stream == NULL) {
        printErrorMessage(-2);
        return;
    }

    if (isStarAdded != 0) {
        fprintf(stream,"%c",'*');
    }

    print_string(stream,str,length);
}

static void print_record(FILE *stream, Record *rec, int withComment, int withMetaData) 
{
    if (rec == NULL || stream == NULL) {
        printErrorMessage(-2);
        return;
    }

    print_coreData(stream, &rec->coreData, withComment);

    if (withMetaData != 0) {
        //if there is no comment included, add <blank> line
        if (withComment == 0) {
            fprintf(stream,"\n");
        }
        print_metaData(stream, &rec->recordMetaData, 0);
        fprintf(stream,"\n");
    }
}

static void print_coreData(FILE *stream, CoreData *data, int withComment) 
{
    static char sign = ' ';
    static const char header_comment[] = "COMMENT";

    if (data == NULL || stream == NULL) {
        printErrorMessage(-2);
        return;
    }
    
    if (data->isIncome == 0) {
        sign = '-';
    } else {
        sign = '+';
    }

    fprintf(stream,"%8d | %c%15ld.%02ld | ", data->id, sign, (data->amount)/100,(data->amount)%100);
    print_date(stream, &data->date, 0);
    fprintf(stream," | %-32s ", data->toFrom);

    if (withComment != 0) {
        fprintf(stream,"\n\n%-20s: %-s", header_comment, data->comment);
    }
    
    fprintf(stream,"\n");
}

static void print_fileMetaData(FILE *stream, FileMetaData *fmd) 
{
    static const char file_name_text[] = "FILE NAME";
    static const char no_of_record_text[] = "NO OF RECORDS";
    static const char counter_text[] = "COUNTER";

    if (fmd == NULL || stream == NULL) {
        printErrorMessage(-2);
        return;
    }

    fprintf(stream,"%-20s: ", file_name_text);
    print_fileName(stdout,fmd->fileName,FILE_NAME_LENGTH,0);
    fprintf(stream,"\n");

    fprintf(stream,"%-20s: ", no_of_record_text);
    fprintf(stream,"%d",fmd->totalRecord);

    fprintf(stream,"\n");
    fprintf(stream,"%-20s: ", counter_text);
    fprintf(stream,"%d",fmd->counter);
}

static void print_metaData(FILE *stream, MetaData *md, int withStatus) 
{
    static const char status_text[] = "STATUS";
    static const char created_date_text[] = "CREATED DATE";
    static const char modified_date_text[] = "MODIFIED DATE";

    if (md == NULL || stream == NULL) {
        printErrorMessage(-2);
        return;
    }

    if (withStatus != 0) {
        fprintf(stream,"%-20s: ", status_text);

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
    }

    fprintf(stream,"%-20s: ", created_date_text);
    print_date(stream,&md->createdDate,1);
    
    fprintf(stream,"\n");

    fprintf(stream,"%-20s: ", modified_date_text);
    print_date(stream,&md->modifiedDate,1);
}