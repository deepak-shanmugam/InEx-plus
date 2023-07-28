typedef struct {
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;
} Date;

typedef struct {
    int id;
    Date date;
    long amount;
    char toFrom[64];
    char comment[128];
    int isDeleted;
    int isSaved;
    int isModified;
    Date CreatedDate;
    Date LastModifiedDate;
    int tag;
} Record;

typedef struct recordList {
    Record record;
    struct recordList *next;
} List;

typedef struct {
    List *records;
    char fileName[64];
    int counter;
    int totalRecord;
    int isDeleted;
    int isSaved;
    int isModified;
    Date CreatedDate;
    Date LastModifiedDate;
} Database;