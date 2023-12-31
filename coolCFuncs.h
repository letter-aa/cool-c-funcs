#ifndef coolCFuncs
#define coolCFuncs
#define FUNCTION(NAME, TYPE, ...) TYPE(*NAME)(__VA_ARGS__)
#define ARRLEN(ARRAY) sizeof(ARRAY) / sizeof(ARRAY[0])

#ifdef _WIN32
typedef int(__cdecl* any)();
#endif

typedef const char* string;

typedef struct frequency {
	int size;
	char* characters;
	int* frequencies;
} frequency;

typedef struct sortExRet {
	int* sorted;
	int* prevPos;
} sortExRet;

string getarch();
int* sort(int* array, int arrayLen, int* sizeOfResult);
sortExRet sortEx(int* array, int arrayLen, int* sizeOfResult);
char* input();
frequency frequencies(char* string);
//frequency sortFrequency(frequency freq);
char* reverse(char* main);
char* substr(char* main, int start);
char* substrEx(char* main, int start, int length);
int find(char* main, char* find);
int findNth(char* main, char* findStr, int nth);
char** splitByByte(char* main, int splitBy, int* sizeOfResult);
int numofstr(char* main, char* lookfor);
char** split(char* main, char* splitBy, int* sizeOfResult);
int find_last_of(char* main, char* find);
int find_first_not_of(char* main, char* find);
int find_last_not_of(char* main, char* find);
char* oldTrim(char* main);
char* trim(char* main);
char* itos(int i);
int oldStoi(char* c);
int stoi(char* c);

#else

#error "coolCFuncs.h can only be included once!"

#endif // coolCFuncs
