#ifndef coolCFuncs
#define coolCFuncs
#define FUNCTION(NAME, TYPE, ...) TYPE(*NAME)(__VA_ARGS__)
#define ARRLEN(ARRAY) sizeof(ARRAY) / sizeof(ARRAY[0])
#define newline printf("\n")
#define DEBUG_NULL 0xcdcdcdcdcdcdcdcd


#ifdef _WIN32
typedef int(__cdecl* any)();
#endif

typedef const char* string;

typedef struct Node {
	char c; //characters
	int f; //frequencies
	struct Node* left;
	struct Node* right;
} Node;

typedef struct frequency {
	char character;
	int frequency;
} frequency;

typedef struct frequencies {
	int size;
	frequency* freqs;
} frequencies;

string getarch();
void swap(int* pFirst, int* pSecond);
void swapf(frequency* pFirst, frequency* pSecond);
void sort(int* array, int arrayLen);
int* sort1(int* array, int arrayLen, int* sizeOfResult);
char* input();
frequencies getfrequencies(char* string);
void sortfrequencies(frequencies* pFreqs);
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
char* replace(char* main, char* toReplace, char* replaceWith, int nth);
char* replaceall(char* main, char* toReplace, char* replaceWith);
char* oldTrim(char* main);
char* trim(char* main);
char* itos(int i);
int oldStoi(char* c);
int stoi(char* c);
int clen(int c);
int stoc(char* str, bool enablewarnings);
char* ctos(int mcl, bool enablewarnings);


//huffman algorithm functions
void ppn(Node node, int nth);
void ppq(Node* priQuene, int size);
void asf(Node* pMain);
void asl(Node* pMain, Node* l);
void asr(Node* pMain, Node* r);
void sortnodes(Node* nodes, int size, bool enabled);
Node* newnode(char c, int f);
Node* fton(frequency freq);
Node build(frequencies freq, bool type);
int gethuffmancode(Node* tree, char c, char code[]);
long* treetostring(Node* tree, frequencies freqs, int* size);
char* encrypt(char* text);
char* decrypt(long* treestring, char* encoded, int treestringSize);

#else

#error "coolCFuncs.h can only be included once!"

#endif // coolCFuncs
