#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include <limits.h>
#include "coolCFuncs.h"

typedef long long ll;

// thank you to FreakAnon for making getarch()
// i couldnt make this cuz i dont rlly know that much about architectures lmao
string getarch() {
#if defined(__x86_64__) || defined(_M_X64)
    return "x86_64";
#elif defined(i386) || defined(__i386__) || defined(__i386) || defined(_M_IX86)
    return "x86_32";
#elif defined(__ARM_ARCH_2__)
    return "ARM2";
#elif defined(__ARM_ARCH_3__) || defined(__ARM_ARCH_3M__)
    return "ARM3";
#elif defined(__ARM_ARCH_4T__) || defined(__TARGET_ARM_4T)
    return "ARM4T";
#elif defined(__ARM_ARCH_5_) || defined(__ARM_ARCH_5E_)
    return "ARM5"
#elif defined(__ARM_ARCH_6T2_) || defined(__ARM_ARCH_6T2_)
    return "ARM6T2";
#elif defined(__ARM_ARCH_6__) || defined(__ARM_ARCH_6J__) || defined(__ARM_ARCH_6K__) || defined(__ARM_ARCH_6Z__) || defined(__ARM_ARCH_6ZK__)
    return "ARM6";
#elif defined(__ARM_ARCH_7__) || defined(__ARM_ARCH_7A__) || defined(__ARM_ARCH_7R__) || defined(__ARM_ARCH_7M__) || defined(__ARM_ARCH_7S__)
    return "ARM7";
#elif defined(__ARM_ARCH_7A__) || defined(__ARM_ARCH_7R__) || defined(__ARM_ARCH_7M__) || defined(__ARM_ARCH_7S__)
    return "ARM7A";
#elif defined(__ARM_ARCH_7R__) || defined(__ARM_ARCH_7M__) || defined(__ARM_ARCH_7S__)
    return "ARM7R";
#elif defined(__ARM_ARCH_7M__)
    return "ARM7M";
#elif defined(__ARM_ARCH_7S__)
    return "ARM7S";
#elif defined(__aarch64__) || defined(_M_ARM64)
    return "ARM64";
#elif defined(mips) || defined(__mips__) || defined(__mips)
    return "MIPS";
#elif defined(__sh__)
    return "SUPERH";
#elif defined(__powerpc) || defined(__powerpc__) || defined(__powerpc64__) || defined(__POWERPC__) || defined(__ppc__) || defined(__PPC__) || defined(_ARCH_PPC)
    return "POWERPC";
#elif defined(__PPC64__) || defined(__ppc64__) || defined(_ARCH_PPC64)
    return "POWERPC64";
#elif defined(__sparc__) || defined(__sparc)
    return "SPARC";
#elif defined(__m68k__)
    return "M68K";
#else
    return "UNKNOWN";
#endif
}

void swap(int* pFirst, int* pSecond) {
    int old = *pFirst;
    *pFirst = *pSecond;
    *pSecond = old;
}

void swapf(frequency* pFirst, frequency* pSecond) {
    frequency old = *pFirst;
    *pFirst = *pSecond;
    *pSecond = old;
}

void sort(int* array, int arrayLen) {
    for (int i = 0; i < arrayLen; i++)
        for (int j = 0; j < arrayLen; j++)
            if (array[j] > array[i])
                swap(&array[j], &array[i]);
}

int* sort1(int* array, int arrayLen, int* sizeOfResult) {
    int* arr = malloc(arrayLen * sizeof(int*));
    memcpy(arr, array, arrayLen * sizeof(int*));
    int* res = malloc(arrayLen * sizeof(int*));
    int ex1 = -1;
    int j = 0;
    while (arrayLen > 0) {
        // set ex1 to -1 to set to arr[i]
        ex1 = arr[0];
        int f = 0;
        for (int i = 0; i < arrayLen; i++) {
            if (arr[i] < ex1) {
                ex1 = arr[i];
                f = i;
            }
        }
        //first get j and set res[j] to ex1 then increment j
        res[j] = ex1;

        //shorten arr table so we skip already scanned numbers
        for (int x = f; x < arrayLen - 1; x++) {
            arr[x] = arr[x + 1];
        }

        //increment j
        j++;

        //subtract arrayLen so when we have scanned all numbers arrayLen will = 0 and while loop will end
        arrayLen--;
    }
    if (sizeOfResult != NULL) *sizeOfResult = j;
    free(arr);
    return res;
}

char* input() {
    char* input = malloc(sizeof(char*));
    char c = getchar();
    int j = 0;
    while (c != '\n') {
        input = (char*)realloc(input, strlen(input) + 1);
        if (input == NULL) {
            printf("\n%s\n", "realloc failed lmao skill issue");
            free(input);
            return 1;
        }
        input[j++] = c;
        c = getchar();
    }
    input[j] = '\0';
    return input;
}

/*
frequency frequencies(char* string) {
    int size = strlen(string); //size of input
    int* freq = malloc(size * sizeof(int*)); //num of frequencies
    char* str = malloc(size * sizeof(char*)); //characters associated with the number of frequencies in the freq array
    int j = 0; bool found = false;
    for (int i = 0; i < size; i++) { //initialize both freq and str arrays
        freq[i] = 0; str[i] = 0;
    }

    for (int i = 0; i < size; i++) { //go through each character in str array every character in ipt array to check if it is already an element in the str array
        for (int x = 0; x < size; x++) {
            if (string[i] == str[x]) {
                freq[x]++; found = true;
                break;
            }
        } //if character does not exist in str array, we will create it
        if (!found) {
            str[j] = string[i];
            freq[j] = 1;
            j++;
        } //reset found to false so that we can repeat this process for each character
        found = false;
    }
    size = j;
    frequency ret;
    ret.characters = str;
    ret.size = size;
    ret.frequencies = freq;
    return ret;
};*/

frequencies getfrequencies(char* string) {
    int size = strlen(string);
    frequencies res;
    res.freqs = malloc(size * sizeof(frequency));
    bool found = false;
    int f = 0;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (string[i] == res.freqs[j].character) {
                res.freqs[j].frequency++;
                found = true;
                break;
            }
        }
        if (found == false) {
            res.freqs[f].character = string[i];
            res.freqs[f].frequency = 1;
            f++;
        }
        found = false;
    }
    res.size = f;
    return res;
}

void sortfrequencies(frequencies* pFreqs) {
    for (int i = 0; i < pFreqs->size; i++) {
        for (int j = 0; j < pFreqs->size; j++) {
            if (pFreqs->freqs[j].frequency > pFreqs->freqs[i].frequency) {
                frequency old = pFreqs->freqs[j];
                pFreqs->freqs[j] = pFreqs->freqs[i];
                pFreqs->freqs[i] = old;
            }
        }
    }
}

char* reverse(char* main) {
    char* res = malloc(strlen(main) * sizeof(char*));
    for (int i = 0; i <= strlen(main); i++) {
        res[i] = main[strlen(main) - i - 1];
    }
    res[strlen(main)] = '\0';
    return res;
}

char* substr(char* main, int start) {
    if (start < 0) {
        start = 0;
    }
    if (strlen(main) < start) {
        return "";
    }
    char* res = malloc(strlen(main) * sizeof(char*));
    for (int i = start; i <= strlen(main); i++) {
        res[i - start] = main[i];
    }
    res[strlen(res)] = '\0';
    return res;
}

char* substrEx(char* main, int start, int length) {
    if (start < 0) {
        start = 0;
    }
    if (strlen(main) < start) {
        return "";
    }
    if (length >= 0) {
        length = length + start;
        char* res = malloc(length - start + 1);
        for (int i = start; i < length; i++) {
            res[i - start] = main[i];
        }
        res[length - start] = '\0';
        return res;
    }
    else {
        char* res = malloc(strlen(main) * sizeof(char*));
        for (int i = start; i <= strlen(main); i++) {
            res[i - start] = main[i];
        }
        res[strlen(res)] = '\0';
        return res;
    }
}

int find(char* main, char* findStr) {
    for (int i = 0; i < strlen(main); i++) {
        if (strcmp(substrEx(main, i, strlen(findStr)), findStr) == 0) {
            return i;
        }
    }
    return -1;
}

int findNth(char* main, char* findStr, int nth) {
    char* mainEx = substr(main, nth);
    for (int i = 0; i < strlen(mainEx); i++) {
        if (strcmp(substrEx(mainEx, i, strlen(findStr)), findStr) == 0) {
            return i + nth;
        }
    }
    return -1;
}

char** splitByByte(char* main, int splitBy, int* sizeOfResult) {
    int intEx = floor(splitBy);
    char** res = malloc(strlen(main) / intEx * sizeof(char*));
    int j = 0;
    for (int i = 0; i < strlen(main); i += intEx) {
        res[j] = substrEx(main, i, intEx);
        j++;
    }
    *sizeOfResult = j;
    return res;
}

int numofstr(char* main, char* lookfor) {
    int sizeOfResult = 0;
    char** res = splitByByte(main, strlen(lookfor), &sizeOfResult);
    int inc = 0;
    for (int i = 0; i < ARRLEN(res); i++) {
        if (strcmp(res[i], lookfor) == 0) {
            inc = inc + 1;
        }
    }
    return inc;
}

char** split(char* main, char* splitBy, int* sizeOfResult) {
    char** res = malloc(strlen(main) * sizeof(char*));
    int j = 0;
    int inc = find(main, splitBy);
    int incEx = -1;
    if (strcmp(splitBy, "") != 0) {
        while (inc != -1) {
            if (incEx == -1 && j == 0) {
                res[j] = substrEx(main, 0, inc);
            }
            else if (incEx == -1 && j != 0) {
                res[j] = substr(main, inc + strlen(splitBy));
                j = j + 1;
                break;
            }
            else {
                res[j] = substrEx(main, inc + strlen(splitBy), inc + find(substr(main, inc), " "));
                inc = findNth(main, splitBy, inc + 1);
            }
            j = j + 1;
            incEx = findNth(main, splitBy, inc + 1);
        }
    }
    else {
        while (j + 1 <= strlen(main)) {
            res[j] = substrEx(main, j, 1);
            j = j + 1;
        }
    }
    if (sizeOfResult != NULL) *sizeOfResult = j;
    return res;
}

int find_last_of(char* main, char* findStr) {
    char* rmain = reverse(main);
    char* rfind = reverse(findStr);
    if (numofstr(rmain, rfind) > 0) {
        return strlen(main) - find(rmain, rfind) - 1;
    }
    return -1;
}

int find_first_not_of(char* main, char* findStr) {
    if (strcmp(main, findStr) == 0) {
        return -1;
    }
    for (int i = 0; i < strlen(main); i++) {
        if (strcmp(substrEx(main, i, strlen(findStr)), findStr) != 0) {
            return i;
        }
    }
    return -1;
}

int find_last_not_of(char* main, char* findStr) {
    char* rmain = reverse(main);
    char* rfind = reverse(findStr);
    if (strcmp(main, findStr) != 0) {
        return strlen(main) - find_first_not_of(rmain, rfind) - 1;
    }
    else {
        return -1;
    }
}

char* replace(char* main, char* toReplace, char* replaceWith, int nth) {
    char* res = malloc(strlen(main) * sizeof(char*));
    strcpy(res, main);
    int f = findNth(res, toReplace, nth);
    if (f != -1) {
        char* ex = substrEx(res, 0, f);
        char* ex1 = substr(res, f + strlen(toReplace));
        strcat(ex, replaceWith);
        strcat(ex, ex1);
        res = _strdup(ex);
    }
    return res;
}

char* replaceall(char* main, char* toReplace, char* replaceWith) {
    char* res = malloc(strlen(main) * sizeof(char*));
    strcpy(res, main);
    int f = find(res, toReplace);
    while (f != -1) {
        char* ex = substrEx(res, 0, f);
        char* ex1 = substr(res, f + strlen(toReplace));
        strcat(ex, replaceWith);
        strcat(ex, ex1);
        res = _strdup(ex);
        f = findNth(res, toReplace, f + strlen(toReplace) + 1);
    }
    return res;
}

char* oldTrim(char* main) {
    int start = 0;
    int len = strlen(main) - 1;
    for (int i = strlen(main) - 1; i > 0; i--) {
        if (main[i] != ' ') {
            break;
        }
        len--;
    }
    for (int i = 0; i < strlen(main); i++) {
        if (main[i] != ' ') {
            break;
        }
        start++;
    }
    return substrEx(main, start, len);
}

char* trim(char* main) {
    int start = 0;
    int len = strlen(main) - 1;
    bool onlySpace = true;
    for (int i = strlen(main) - 1; i > 0; i--) {
        if (main[i] != ' ') {
            onlySpace = false;
            break;
        }
        len--;
    }
    for (int i = 0; i < strlen(main); i++) {
        if (main[i] != ' ') {
            onlySpace = false;
            break;
        }
        start++;
    }
    if (onlySpace == false) {
        return substrEx(main, start, len);
    }
    else {
        return " ";
    }
}

char* itos(int i) {
    char num[] = { '1','2','3','4','5','6','7','8','9','0' };
    char* str = malloc((int)((ceil(log10(i)) + 2) * sizeof(char)));
    sprintf(str, "%d", i);
    return str;
}

int oldStoi(char* c) {
    c = trim(c);
    char num[] = { '1','2','3','4','5','6','7','8','9','0' };
    ll res = 0;
    bool isNum = true;
    bool isPos = false;
    bool isNeg = false;
    bool isZero = false;
    bool numPosFound = false;
    for (int i = 0; i < strlen(c) && c[i] != '\0'; i++) {
        for (int x = 0; x < sizeof(num) / sizeof(char); x++) {
            if (c[i] != num[x]) {
                if (x == sizeof(num) / sizeof(char) - 1) {
                    if (c[i] == '-') {
                        if (numPosFound == true) {
                            isZero = true;
                        }
                        isNeg = true;
                    }
                    else if (c[i] == '+') {
                        if (numPosFound == true) {
                            isZero = true;
                        }
                        isPos = true;
                        break;
                    }
                    else {
                        isNum = false;
                        break;
                    }
                }
            }
            else {
                numPosFound = true;
                int ex = c[i] - '0';
                if (((res * 10) + ex) > INT_MAX) {
                    res = INT_MAX;
                    break;
                }
                if (((res * 10) + ex) < INT_MIN) {
                    res = INT_MIN;
                    break;
                }
                res = (res * 10) + ex;
                break;
            }
        }
        if (isNum == false) {
            break;
        }
    }
    if (isNeg == true) {
        res = res * -1;
    }
    if (isZero == true || (isNeg == true && isPos == true)) {
        res = 0;
    }
    return res;
}

int stoi(char* c) {
    c = trim(c);
    char num[] = { '1','2','3','4','5','6','7','8','9','0' };
    ll res = 0;
    if (strcmp(c, " ") == 0) {
        return res;
    }
    bool isNum = true;
    bool isPos = false;
    bool isNeg = false;
    bool isZero = false;
    bool numPosFound = false;
    bool negPosFound = false;
    bool addPosFound = false;
    for (int i = 0; i < strlen(c) && c[i] != '\0'; i++) {
        for (int x = 0; x < sizeof(num) / sizeof(char); x++) {
            if (c[i] != num[x]) {
                if (x == sizeof(num) / sizeof(char) - 1) {
                    if (c[i] == '-') {
                        if (negPosFound == true) {
                            isNum = false;
                            break;
                        }
                        negPosFound = true;
                        if (numPosFound == true) {
                            isNum = false;
                            break;
                        }
                        isNeg = true;
                        break;
                    }
                    else if (c[i] == '+') {
                        if (addPosFound == true) {
                            isNum = false;
                            break;
                        }
                        addPosFound = true;
                        if (numPosFound == true) {
                            isNum = false;
                            break;
                        }
                        isPos = true;
                        break;
                    }
                    else {
                        isNum = false;
                        break;
                    }
                }
            }
            else {
                if (isPos == true && isNeg == true) {
                    isNum = false;
                    break;
                }
                else if (isNeg == true) {
                    res = -res;
                    numPosFound = true;
                    int ex = c[i] - '0';
                    ex = -ex;
                    if (((-res * 10) + ex) < INT_MIN) {
                        res = INT_MIN;
                        break;
                    }
                    res = (-res * 10) + ex;
                    break;
                }
                else if (isPos == true) {
                    numPosFound = true;
                    int ex = c[i] - '0';
                    if (((res * 10) + ex) > INT_MAX) {
                        res = INT_MAX;
                        break;
                    }
                    res = (res * 10) + ex;
                    break;
                }
                else if (isPos == false && isNeg == false) {
                    numPosFound = true;
                    int ex = c[i] - '0';
                    if (((res * 10) + ex) > INT_MAX) {
                        res = INT_MAX;
                        break;
                    }
                    if (((res * 10) + ex) < INT_MIN) {
                        res = INT_MIN;
                        break;
                    }
                    res = (res * 10) + ex;
                    break;
                }
            }
        }
        if (isNum == false || isZero == true) {
            break;
        }
    }
    /*
    if (isNeg == true){
        res = -res;
    }*/
    if (isZero == true || (isNeg == true && isPos == true)) {
        res = 0;
    }
    return res;
}

//huffman algorithm functions

void ppn(Node node, int nth) {
    printf("Node %d:\n", nth);
    printf("  Character: %c\n", node.c);
    printf("  Frequency: %d\n", node.f);
    if (node.left != NULL && node.left != DEBUG_NULL) { // 0xcdcdcdcdcdcdcdcd
        printf("  Left Child:\n");
        printf("    Character: %c\n", node.left->c);
        printf("    Frequency: %d\n", node.left->f);
    }
    if (node.right != NULL && node.right != DEBUG_NULL) { // 0xcdcdcdcdcdcdcdcd
        printf("  Right Child:\n");
        printf("    Character: %c\n", node.right->c);
        printf("    Frequency: %d\n", node.right->f);
    }
    newline;
}

void ppq(Node* priQuene, int size) { // print priority quene
    for (int i = 0; i < size; i++) {
        ppn(priQuene[i], i + 1);
    }
}

void asf(Node* pMain) { // Node* l, Node* r
    pMain->f = pMain->right->f + pMain->left->f; // pMain->f = l->f + r->f;
}

void asl(Node* pMain, Node* l) {
    pMain->left = l;
}

void asr(Node* pMain, Node* r) {
    pMain->right = r;
} //assign left & right

void sortnodes(Node* nodes, int size, bool enable) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if ((enable == true) ? nodes[j].f > nodes[i].f : nodes[j].f < nodes[i].f) { // > if least to greatest, < if vice versa
                Node old = nodes[j];
                nodes[j] = nodes[i];
                nodes[i] = old;
            }
        }
    }
}

Node* newnode(char c, int f) {
    Node* new = malloc(sizeof(Node));
    new->c = c;
    new->f = f;
    new->left = NULL;
    new->right = NULL;
    return new;
}

Node* fton(frequency freq) { // frequency to node
    return newnode(freq.character, freq.frequency);
}

/*
type 0 (NOT RECOMMENDED):
if there more than 4 nodes, it will turn the extra nodes to a small binary tree and set
that small tree as the right / left of the bigger tree(the other 4 nodes)

type 1 (RECOMMENDED):
sets each node (not including leafs) to have usually an equal amount of children
*/
Node build(frequencies freq, bool type) {
    sortfrequencies(&freq);
    int j = 0;
    Node* priQuene = malloc(freq.size * sizeof(Node)); //priority quene
    /*
    for (int i = 0; i < aa.size; i++) {
        priQuene[i] = *newnode(aa.freqs[i].character, aa.freqs[i].frequency);
    }
    */
    Node main = { 0 };

    for (int i = 0; i < freq.size; i += 2) {
        Node* new = newnode('\0', 0);
        if (i + 1 < freq.size) {
            asl(new, fton(freq.freqs[i]));
            asr(new, fton(freq.freqs[i + 1]));
            asf(new);
        }
        else {
            new = fton(freq.freqs[i]);
        }
        priQuene[j] = *new;
        j++;
    }

    while (j > 1) {
        sortnodes(priQuene, j, type);
        Node* new = newnode('\0', 0);
        Node* ex = newnode(priQuene[0].c, priQuene[0].f);
        Node* ex1 = newnode(priQuene[1].c, priQuene[1].f);
        asl(ex, priQuene[0].left);
        asr(ex, priQuene[0].right);
        asl(ex1, priQuene[1].left);
        asr(ex1, priQuene[1].right);
        asl(new, ex);
        asr(new, ex1);
        asf(new);
        priQuene[0] = *new;
        for (int i = 1; i < j - 1; i++) {
            priQuene[i] = priQuene[i + 1];
        }
        j--;
    }
    sortnodes(priQuene, j, type);
    return priQuene[0];
}

int gethuffmancode(Node* tree, char c, char code[]) {
    if (tree == NULL) {
        code = substrEx(code, 0, strlen(code) - 1);
        return NULL;
    }

    if (tree->c == c) {
        code = substrEx(code, 0, strlen(code) - 1);
        return 1;
    }

    char* oldc = _strdup(code); //oldCode
    strcat(code, "0");
    int left = gethuffmancode(tree->left, c, code);
    if (left != NULL) return 1;

    strcpy(code, oldc);
    strcat(code, "1");
    int right = gethuffmancode(tree->right, c, code);
    return right != NULL;
}

/*
Node pntn(Node* node) { //pointer node to node
    Node new = *newnode(node->c, node->f);
    asl(&new, node->left);
    asr(&new, node->right);
    return new;
}
Node* ntpn(Node node) { //node to pointer node
    Node* new = newnode(node.c, node.f);
    asl(new, node.left);
    asr(new, node.right);
    return new;
}
*/

char* treetostring(Node* tree, frequencies freqs) {
    char* res = malloc(freqs.size * sizeof(char*));
    strcpy(res, "");
    for (int i = 0; i < freqs.size; i++) {
        char code[256] = { '\0' };
        frequency ex = freqs.freqs[i];
        int ghc = gethuffmancode(tree, ex.character, code);
        if (ghc != NULL) {
            strncat(res, &ex.character, 1);
            strcat(res, code);
        }
    }
    return res;
}

char* encrypt(char* text) {
    frequencies freqs = getfrequencies(text);
    Node tree = build(freqs, true);
    char* res = malloc(strlen(text) * sizeof(char*)); // freqs.size * 
    strcpy(res, "");
    for (int i = 0; i < strlen(text); i++) {
        char* code[256] = { '\0' };
        int ghc = gethuffmancode(&tree, text[i], code);
        //code = realloc(code, strlen(code) + 1);
        if (ghc != NULL) {
            strcat(res, code);
            //res = realloc(str1, strlen(str1) + 1); // sizeof or strlen
        }
    }
    return res;
}

char* decrypt(char* treestring, char* encoded) {
    //int i = 0;
    //int e = 1;
    int sizeOfCodes = 0;
    int f = 0;
    char* res = malloc(sizeof(char)); // strlen(encoded) + 1
    char* chars = malloc(strlen(treestring));
    char** codes = malloc(strlen(treestring));
    strcpy(chars, "");
    strcpy(res, "");
    codes[0] = treestring;
    for (int i = 0; i < strlen(treestring) - 1; i++) {
        if (treestring[i] != '1' && treestring[i] != '0') {
            strncat(chars, &treestring[i], 1);
            char** ex = split(codes[sizeOfCodes], (char[2]) { treestring[i], '\0' }, NULL);
            if (strcmp(trim(ex[0]), " ") != 0) {
                codes[sizeOfCodes] = ex[0];
                codes[++sizeOfCodes] = ex[1];
            }
            else {
                codes[sizeOfCodes] = ex[1];
            }
            free(ex);
        }
        //s1 = substrEx(treestring, ++z, 1);
    }
    sizeOfCodes++;
    int sizeEx = 0;
    while (f < strlen(encoded)) {
        for (int i = 0; i < sizeOfCodes; i++) {
            //printf("%s: %d,%s\n", codes[i], strlen(codes[i]), substrEx(encoded, f, strlen(codes[i])));
            if (strcmp(substrEx(encoded, f, strlen(codes[i])), codes[i]) == 0) {
                char* old = _strdup(res);
                res = realloc(res, strlen(res) + 1);
                strcpy(res, old);
                strncat(res, &chars[i], 1);
                //res = replace(res, codes[i], (char[2]) { chars[i], '\0' }, f);
                f = f + strlen(codes[i]);
                break;
            }
        }
    }
    //free(chars);
    //free(codes);
    // res = realloc(res, strlen(res) + 1);
    return res;
}
