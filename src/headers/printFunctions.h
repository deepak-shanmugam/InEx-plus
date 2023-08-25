
extern void print_database(FILE *stream, Database *db);

extern void print_dbMetaData(FILE *stream, DbMetaData *dmd);

extern void print_recordList(FILE *stream, RecordList *list
    , int withMetaData, int withComment, int count);

extern void print_date(FILE *stream, Date *date, int withTime);

extern void print_fileName(FILE *stream, char *str, int length, int isStarAdded);