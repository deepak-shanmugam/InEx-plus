#define FILE_NAME_LENGTH 64
#define TOFROM_LENGTH 32
#define COMMENT_LENGTH 128

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
    char fileName[FILE_NAME_LENGTH];
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
    char toFrom[TOFROM_LENGTH];
    char comment[COMMENT_LENGTH];
    Date date;
    int tag;
    int isIncome;
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