extern RecordList* getRecordList(const int id, int *returnCode);
extern int setRecord(Record *record, const int id, const int tag);
extern int isIncome();
extern int getText(char *str, int length, int isMandatory, const char *text);
extern int setDate(Date *date, int withTime);
extern int setAmount(long *amount);