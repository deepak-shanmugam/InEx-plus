#include <stdio.h>
#include <stdlib.h>

#include "headers/definition.h"
#include "headers/customFunctions.h"
#include "headers/menu.h"

RecordList* getRecordList(const int id, int *returnCode);
int setRecord(Record *record, const int id, const int tag);
int isIncome();
int setText(char *str, int length, int isMandatory, const char *text);
int setDate(Date *date, int withTime);
int setAmount(long *amount);

static int setInt(int *num, const char *str, int min, int max);
static int convertStringToAmount(char *str, int length, long *amount);
static int isValidAmount(char *str, int length);

RecordList* getRecordList(const int id, int *returnCode) {
    RecordList *recordList = NULL;

    if (returnCode == NULL) {
        printErrorMessage(-2);
        return NULL;
    }

    recordList = (RecordList *)calloc(1, sizeof(*recordList));
    if (recordList == NULL) {
        printErrorMessage(-8);
        *returnCode = -1;
        return NULL;
    } 

    *returnCode = setRecord(&recordList->record, id, 0);
    recordList->next = NULL;

    if (*returnCode < 0) {
        free(recordList);
        recordList = NULL;
    }

    return recordList;
}

int setRecord(Record *record, const int id, const int tag) {
    int validity = 0;
    static const char toFrom_text[] = 
        "TO/FROM";
    static const char comment_text[] = 
        "COMMENT";

    if (record == NULL) {
        printErrorMessage(-2);
        return -2;
    }

    validity = isIncome();
    if (validity == -3) {
        return -3;
    }
    if (validity <= 0) {
        return -1;
    }
    if (validity > 0) {
        if (validity == 1) {
            record->coreData.isIncome = 1;
        } else {
            record->coreData.isIncome = 0;
        }       
    }

    record->coreData.id = id;
    record->coreData.tag = tag;

    validity = setAmount(&record->coreData.amount);
    if (validity == -3) {
        return -3;
    }
    if (validity <= 0) {
        return -1;
    }

    validity = setDate(&record->coreData.date, 0);
    if (validity == -3) {
        return -3;
    }
    if (validity < 0) {
        return -1;
    }

    validity = setText(record->coreData.toFrom, TOFROM_LENGTH, 1, toFrom_text);
    if (validity == -3) {
        return -3;
    }
    if (validity <= 0) {
        return -1;
    }

    validity = setText(record->coreData.comment, COMMENT_LENGTH, 0, comment_text);
    if (validity == -3) {
        return -3;
    }
    if (validity < 0) {
        return -1;
    }

    return 0;
}

int isIncome() {
    int validity = 0;
    int counter = 0;
    int choice = 0;

    system("clear");
    showAddOperationMenu(stdout);

    while (validity == 0 && (counter >= 0 && counter < 3)) {
        fprintf(stdout,"\nEnter your choice: ");

        validity = getIntInput(stdin, &choice);

        if (validity <= 0) {
            if (validity == -2 || validity == -3) {
                printErrorMessage(validity);
                return validity;
            }
            printErrorMessage(-4);
            validity = 0;
        }

        if (validity > 0) {
            if (choice >= 0 && choice <= 2) {
                return choice;
            }
            printErrorMessage(-4);
            validity = 0;
        }
        
        counter++;
    }

    fprintf(stdout,"\n\tMESSAGE: Too many attempts! selecting to <CANCEL>\n");

    return 0;
}

int setText(char *str, int length, int isMandatory, const char *text) {
    int validity = 0;
    int counter = 0;

    if (str == NULL || length <= 1) {
        printErrorMessage(-2);
        return -2;
    }

    while (validity == 0 && (counter >= 0 && counter < 3)) {
        fprintf(stdout,"\nEnter %-8s: ",text);
        validity = getStringInput(stdin, str, length);

        if (validity <= 0) {
            if (validity == 0 && isMandatory == 0) {
                return validity;
            }
            if (validity == -1) {
                printErrorMessage(-3);
                return -3;
            }
            if (validity == -2) {
                printErrorMessage(-2);
                return -2;
            }
            printErrorMessage(-4);
            validity = 0;
        }

        if (validity >= length) {
            /*---ERROR MESSAGE---*/
            fprintf(stdout,"\n\tERROR: only upto %d characters allowed\n",length-1);
            validity = 0;
        }

        if (validity > 0 && validity < length) {
            return validity;
        }

        counter++;
    }

    fprintf(stdout,"\n\tMESSAGE: Too many attempts!\n");

    return -1;
}

int setDate(Date *date, int withTime) {
    int validity = 0;
    int max_day = 0;
    static const int month_day[12] = 
        {31,28,31,30,31,30,31,31,30,31,30,31};
    static const char year_text[] = 
        "YEAR";
    static const char month_text[] = 
        "MONTH";
    static const char date_text[] = 
        "DAY";
    static const char hour_text[] = 
        "HOUR";
    static const char minute_text[] = 
        "MINUTE";
    static const char second_text[] = 
        "SECOND";

    if (date == NULL) {
        printErrorMessage(-2);
        return -2;
    }

    validity = setInt(&date->year, year_text, 1000, 9999);
    if (validity < 0) {
        return validity;
    }

    validity = setInt(&date->month, month_text, 1, 12);
    if (validity < 0) {
        return validity;
    }

    if (date->month >= 1 && date->month <= 12) {
        max_day = month_day[date->month - 1];

        if (date->month == 2) {
            if ((date->year % 4 == 0 && date->year % 100 != 0)
                    || (date->year % 400 == 0)) {
                max_day++;
            } 
        }

        validity = setInt(&date->day, date_text, 1, max_day);
        if (validity < 0) {
            return validity;
        }
    } else {
        printErrorMessage(-9);
        return -9;
    }

    if (withTime == 0) {
        date->hour = 0;
        date->minute = 0;
        date->second = 0;
    } else {
        validity = setInt(&date->hour, hour_text, 0, 23);
        if (validity < 0) {
            return validity;
        }

        validity = setInt(&date->minute, minute_text, 0, 59);
        if (validity < 0) {
            return validity;
        }

        validity = setInt(&date->second, second_text, 0, 59);
        if (validity < 0) {
            return validity;
        }
    }

    return 0;
}

static int setInt(int *num, const char *str, int min, int max) {
    int validity = 0;
    int counter = 0;

    if (num == NULL || str == NULL) {
        printErrorMessage(-2);
        return -2;
    }

    while (validity == 0 && (counter >=0 && counter < 3)) {
        fprintf(stdout,"\nEnter %-8s: ", str);
        validity = getIntInput(stdin, num);

        if (validity == -2 || validity == -3) {
            printErrorMessage(validity);
            return validity;
        }

        if (validity > 0) {
            if (min < max) {
                if ((*num) >= min && (*num) <= max) {
                    return validity;
                }
            } else {
                return validity;
            }
        }

        printErrorMessage(-4);
        validity = 0;
        counter++;
    }

    fprintf(stdout,"\n\tMESSAGE: Too many attempts!\n");

    return -1;
}

int setAmount(long *amount) {
    char buffer[32];
    int validity = 0;
    int counter = 0;
    static const char amount_text[] = 
        "AMOUNT";

    if (amount == NULL) {
        printErrorMessage(-2);
        return -2;
    }

    while (validity == 0 && (counter >= 0 && counter < 3)) {
        fprintf(stdout,"\nEnter %-8s: ", amount_text);
        validity = getStringInput(stdin, buffer, 32);
        if (validity == -1) {
            printErrorMessage(-3);
            return -3;
        }
        if (validity == -2) {
            printErrorMessage(-2);
            return -2;
        }
        if (validity > 0) {
            validity = convertStringToAmount(buffer, 32, amount);
            if (validity > 0) {
                return validity;
            }
            if (validity == 0) {
                fprintf(stdout,"\n\tMESSAGE: Value is too big!\n");
            }
        }

        printErrorMessage(-4);
        validity = 0;
        counter++;
    }
    
    fprintf(stdout,"\n\tMESSAGE: Too many attempts!\n");

    return -1;
}

static int convertStringToAmount(char *str, int length, long *amount) {
    int validity = 0;
    long value = 0;
    int i;

    if (str == NULL && length <= 1) {
        printErrorMessage(-2);
        return -2;
    }

    validity = isValidAmount(str, length);
    if (validity < 0) {
        return validity;
    }
    if (validity > 12) {
        return 0;
    }

    for (i = 0; i < length; i++) {
        if (str[i] == '\0') {
            break;
        }
        if (str[i] >= '0' && str[i] <= '9') {
            value = (value * 10) + (str[i] - 48);
        }
    }

    *amount = value;

    return validity;
}

static int isValidAmount(char *str, int length) {
    int i;
    int decimalPoint = 0;
    int decimal = 0;

    if (str == NULL && length <= 1) {
        printErrorMessage(-2);
        return -2;
    }

    for (i = 0; i < length; i++) {
        if (str[i] == '\0') {
            if (i == 0) 
                return -1;
            break;
        }
        if (str[i] == '.' && decimalPoint == 0 && i > 0) {
            decimalPoint++;
            continue;
        } 
        if (str[i] >= '0' && str[i] <= '9') {
            if (decimalPoint != 0)
                decimal++;
            continue;
        }

        return -1;
    }

    if (i < length) {
        if (decimalPoint != 0 && decimal != 2) {
            return -1;
        }
        return (i - (decimalPoint + decimal));
    }

    return -1;
}