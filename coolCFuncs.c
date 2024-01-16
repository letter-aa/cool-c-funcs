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

int* sort(int* array, int arrayLen, int* sizeOfResult) {
    int* res = malloc(arrayLen * sizeof(int*));
    memcpy(res, array, arrayLen * sizeof(int*));
    for (int i = 0; i < arrayLen; i++) {
        for (int j = 0; j < arrayLen; j++) {
            if (array[j] < array[i]) {
                swap(&res[j], &res[i]);
            }
        }
    }
    if (sizeOfResult != NULL) *sizeOfResult = arrayLen;
    return res;
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
    char* input;
    input = malloc(sizeof(char*));
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
            if (pFreqs->freqs[j].frequency < pFreqs->freqs[i].frequency) {
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
    *sizeOfResult = j;
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
