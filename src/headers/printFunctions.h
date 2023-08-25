extern void print_date(FILE *stream, Date *date, int withTime);
extern void print_metaData(FILE *stream, MetaData *md);
extern void print_fileMetaData(FILE *stream, FileMetaData *fmd);
extern void print_fileName(FILE *stream, char *str, int length, int isStarAdded);
extern void print_dbMetaData(FILE *stream, DbMetaData *dmd);