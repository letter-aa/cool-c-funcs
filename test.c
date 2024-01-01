/*
sort
reverse
substr
substrEx
find
findNth
splitByByte
numofstr
split
find_last_of
find_first_not_of
find_last_not_of
oldTrim
trim
itos
oldStoi
stoi
*/

#include <stdio.h>
#include "coolCFuncs.h"

int main() {
    char mainStr[] = "example example example";
    char findStr[] = "example";
    int sortTable[] = { 55,1,2,9,3,0,1,3,3,4 };
    int sizeOfResult = 0;
    int* sortTableRes = sort(sortTable, ARRLEN(sortTable), &sizeOfResult);
    for (int i = 0; i < sizeOfResult; i++) {
        printf("sort[%d]: %d\n", i, sortTableRes[i]);
    }
    printf("reverse: %s\n", reverse(mainStr));
    printf("substr: %s\n", substr(mainStr, 3));
    printf("substrEx: %s\n", substrEx(mainStr, 3, 7));
    printf("find: %d\n", find(mainStr, findStr));
    printf("findNth: %d\n", findNth(mainStr, findStr, 2));

    char** splitResult = splitByByte(mainStr, 8, &sizeOfResult);
    for (int i = 0; i < sizeOfResult; i++) {
        printf("splitByByte[%d]: %s\n", i, splitResult[i]);
    }

    printf("numofstr: %d\n", numofstr(mainStr, findStr));

    char** splitResult2 = split("abc", "", &sizeOfResult);
    for (int i = 0; i < sizeOfResult; i++) {
        printf("split[%d]: %s\n", i, splitResult2[i]);
    }

    printf("find_last_of: %d\n", find_last_of(mainStr, findStr));
    printf("find_first_not_of: %d\n", find_first_not_of(mainStr, findStr));
    printf("find_last_not_of: %d\n", find_last_not_of(mainStr, findStr));

    char trimmed[] = "   trim test   ";
    printf("oldTrim: %s\n", oldTrim(trimmed));
    printf("trim: %s\n", trim(trimmed));

    int num = 12345;
    printf("itos: %s\n", itos(num));

    char numStr[] = "  -6789  ";
    printf("oldStoi: %d\n", oldStoi(numStr));
    printf("stoi: %d\n", stoi(numStr));

    return 0;
}
