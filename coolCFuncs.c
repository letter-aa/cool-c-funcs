#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include <limits.h>
#include "coolCFuncs.h"

typedef long long ll;

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
