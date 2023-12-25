#ifndef coolCFuncs
#define coolCFuncs
#define FUNCTION(NAME, TYPE, ...) TYPE(*NAME)(__VA_ARGS__)
#define ARRLEN(ARRAY) sizeof(ARRAY) / sizeof(ARRAY[0])

char* reverse(char* main);
char* substr(char* main, int start, int length);
char** splitByByte(char* main, int splitBy);
int numofstr(char* main, char* lookfor);
int find(char* main, char* find);
int find_last_of(char* main, char* find);
int find_first_not_of(char* main, char* find);
int find_last_not_of(char* main, char* find);
char** split(char* main, char* splitBy);
char* oldTrim(char* main);
char* trim(char* main);
char* itos(int i);
int oldStoi(char* c);
int stoi(char* c);

#else

#error "coolCFuncs.h can only be included once!"

#endif // coolCFuncs
