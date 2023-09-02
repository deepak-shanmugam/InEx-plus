extern int setDbMetaData(DbMetaData *ptr);
extern int setMetaData(MetaData *ptr, int isDeleted, int isSaved, int isModified);
extern int setFileName(char *str, int length, int checkExist);
extern int isFileExist(const char *file_name);
extern int freeDatabase(Database *db);