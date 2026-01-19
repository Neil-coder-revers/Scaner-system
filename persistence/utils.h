#ifndef UTILS_H
#define UTILS_H

#include <windows.h>

// Converts UTF-16 (Wide) string to UTF-8. 
// Result must be free()'d by the caller.
char* WideToUtf8(LPCWSTR wideStr);

#endif
