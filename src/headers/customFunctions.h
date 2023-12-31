extern int getStringInput(FILE *stream, char *str, const int length);
extern int getIntInput(FILE *stream, int *num);
extern int getLongInput(FILE *stream, long *num);
extern int isNumberString(const char *str, const int length);
extern int pauseExecution();
extern int printErrorMessage(int errorCode);
extern void print_string(FILE *stream, char *str, int length);