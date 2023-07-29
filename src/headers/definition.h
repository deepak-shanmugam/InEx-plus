typedef struct {
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;
} Date;

typedef struct {
    int isDeleted;
    int isSaved;
    int isModified;
    Date modifiedDate;
    Date createdDate;
} MetaData;

typedef struct {
    char fileName[64];
    int counter;
    int totalRecord;
} FileMetaData;

typedef struct {
    MetaData metaData;
    FileMetaData fileMetaData;
} DbMetaData;

typedef struct {
    int id;
    long amount;
    char toFrom[64];
    char comment[128];
    Date date;
    int tag;
} CoreData;

typedef struct {
    MetaData recordMetaData;
    CoreData coreData;
} Record;

typedef struct recordList {
    Record record;
    struct recordList *next;
} RecordList;

typedef struct {
    DbMetaData dbMetaData;
    RecordList *recordList;
} Database;