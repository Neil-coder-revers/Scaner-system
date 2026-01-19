#include "utils.h"
#include <stdlib.h>

char* WideToUtf8(LPCWSTR wideStr) {
    if (wideStr == NULL) return NULL;
    
    int sizeNeeded = WideCharToMultiByte(CP_UTF8, 0, wideStr, -1, NULL, 0, NULL, NULL);
    char* utf8Str = (char*)malloc(sizeNeeded);
    if (utf8Str) {
        WideCharToMultiByte(CP_UTF8, 0, wideStr, -1, utf8Str, sizeNeeded, NULL, NULL);
    }
    return utf8Str;
}
