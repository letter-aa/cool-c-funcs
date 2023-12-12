#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>

#define ll long long

char* substr(char* main, int start, int length) {
    length++;
    char* res = malloc(length - start + 1);
    for (int i = start; i < length; i++) {
        res[i - start] = main[i];
    }
    res[length - start] = '\0';
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
    return substr(main, start, len);
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
    if (onlySpace == false){
        return substr(main, start, len);
    } else {
        return " ";
    }
}

char * itos(int i){
    char num[] = {'1','2','3','4','5','6','7','8','9','0'};
    char * str = malloc((int)((ceil(log10(i)) + 2) * sizeof(char)));
    sprintf(str, "%d", i);
    return str;
}

int oldStoi(char * c){
    c = trim(c);
    char num[] = {'1','2','3','4','5','6','7','8','9','0'};
    ll res = 0;
    bool isNum = true;
    bool isPos = false;
    bool isNeg = false;
    bool isZero = false;
    bool numPosFound = false;
    for (int i = 0; i < strlen(c) && c[i] != '\0'; i++){
        for (int x = 0; x < sizeof(num) / sizeof(char); x++){
            if (c[i] != num[x]){
                if (x == sizeof(num) / sizeof(char) - 1){
                    if (c[i] == '-'){
                        if (numPosFound == true){
                            isZero = true;
                        }
                        isNeg = true;
                    } else if (c[i] == '+'){
                        if (numPosFound == true){
                            isZero = true;
                        }
                        isPos = true;
                        break;
                    } else {
                        isNum = false;
                        break;
                    }
                }
            } else {
                numPosFound = true;
                int ex = c[i] - '0';
                if (((res * 10) + ex) > INT_MAX){
                    res = INT_MAX;
                    break;
                }
                if (((res * 10) + ex) < INT_MIN){
                    res = INT_MIN;
                    break;
                }
                res = (res * 10) + ex;
                break;
            }
        }
        if (isNum == false){
            break;
        }
    }
    if (isNeg == true){
        res = res * -1;
    }
    if (isZero == true || (isNeg == true && isPos == true)){
        res = 0;
    }
    return res;
}

int stoi(char * c){
    c = trim(c);
    char num[] = {'1','2','3','4','5','6','7','8','9','0'};
    ll res = 0;
    if (c == " "){
        return res;
    }
    bool isNum = true;
    bool isPos = false;
    bool isNeg = false;
    bool isZero = false;
    bool numPosFound = false;
    bool negPosFound = false;
    bool addPosFound = false;
    for (int i = 0; i < strlen(c) && c[i] != '\0'; i++){
        for (int x = 0; x < sizeof(num) / sizeof(char); x++){
            if (c[i] != num[x]){
                if (x == sizeof(num) / sizeof(char) - 1){
                    if (c[i] == '-'){
                        if (negPosFound == true){
                            isNum = false;
                            break;
                        }
                        negPosFound = true;
                        if (numPosFound == true){
                            isNum = false;
                            break;
                        }
                        isNeg = true;
                        break;
                    } else if (c[i] == '+'){
                        if (addPosFound == true){
                            isNum = false;
                            break;
                        }
                        addPosFound = true;
                        if (numPosFound == true){
                            isNum = false;
                            break;
                        }
                        isPos = true;
                        break;
                    } else {
                        isNum = false;
                        break;
                    }
                }
            } else {
                if (isPos == true && isNeg == true){
                    isNum = false;
                    break;
                } else if (isNeg == true){
                    res = -res;
                    numPosFound = true;
                    int ex = c[i] - '0';
                    ex = -ex;
                    printf("%ll",((-res * 10) + ex));
                    if (((-res * 10) + ex) < INT_MIN){
                        res = INT_MIN;
                        break;
                    }
                    res = (-res * 10) + ex;
                    break;                    
                } else if (isPos == true){
                    printf("isPos");
                    numPosFound = true;
                    int ex = c[i] - '0';
                    if (((res * 10) + ex) > INT_MAX){
                        res = INT_MAX;
                        break;
                    }
                    res = (res * 10) + ex;
                    break;
                } else if (isPos == false && isNeg == false){
                    numPosFound = true;
                    int ex = c[i] - '0';
                    if (((res * 10) + ex) > INT_MAX){
                        res = INT_MAX;
                        break;
                    }
                    if (((res * 10) + ex) < INT_MIN){
                        res = INT_MIN;
                        break;
                    }
                    res = (res * 10) + ex;
                    break;
                }
            }
        }
        if (isNum == false || isZero == true){
            break;
        }
    }
/*
if (isNeg == true){
    res = -res;
}*/
    if (isZero == true || (isNeg == true && isPos == true)){
        res = 0;
    }
    return res;
}

int main()
{
    printf("%d", stoi("-12"));
    return 0;
}