#include <windows.h>
#include <shlobj.h>
#include <stdio.h>
#include <stdlib.h>
#include "scanner_folders.h"
#include "utils.h"

void CheckStartupFolder(int csidl, const char* desc) {
    wchar_t path[MAX_PATH];
    if (SHGetSpecialFolderPathW(NULL, path, csidl, FALSE)) {
        char* utf8Path = WideToUtf8(path);
        printf("[+] Checking: %s (%s)\n", desc, utf8Path ? utf8Path : "???");
        free(utf8Path);
        
        wchar_t searchPath[MAX_PATH];
        swprintf(searchPath, MAX_PATH, L"%s\\*", path);
        
        WIN32_FIND_DATAW findData;
        HANDLE hFind = FindFirstFileW(searchPath, &findData);
        
        if (hFind != INVALID_HANDLE_VALUE) {
            do {
                if (!(findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
                    char* utf8FileName = WideToUtf8(findData.cFileName);
                    printf("    - File: %s\n", utf8FileName ? utf8FileName : "???");
                    free(utf8FileName);
                }
            } while (FindNextFileW(hFind, &findData));
            FindClose(hFind);
        }
    }
}

void ScanFolderPersistence() {
    CheckStartupFolder(CSIDL_STARTUP, "User Startup Folder");
    CheckStartupFolder(CSIDL_COMMON_STARTUP, "Common Startup Folder");
}
