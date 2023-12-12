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
char* trim(char* main) {
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

char * itos(int i){
    char num[] = {'1','2','3','4','5','6','7','8','9','0'};
    char * str = malloc((int)((ceil(log10(i)) + 2) * sizeof(char)));
    sprintf(str, "%d", i);
    return str;
}

int stoi(char * c){
    c = trim(c);
    char num[] = {'1','2','3','4','5','6','7','8','9','0'};
    ll res = 0;
    bool isNum = true;
    bool isPos = false;
    bool isNeg = false;
    for (int i = 0; i < strlen(c) && c[i] != '\0'; i++){
        for (int x = 0; x < sizeof(num) / sizeof(char); x++){
            if (c[i] != num[x]){
                if (x == sizeof(num) / sizeof(char) - 1){
                    if (c[i] == '-'){
                        isNeg = true;
                        isPos = false;
                    } else if (c[i] == '+'){
                        break;
                    } else {
                        isNum = false;
                        break;
                    }
                }
            } else {
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
    return res;
}

int main()
{
    printf("%d", stoi("23847192384719238471923871324"));
    return 0;
}
