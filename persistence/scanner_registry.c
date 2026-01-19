#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include "scanner_registry.h"
#include "utils.h"

typedef struct {
    HKEY hRoot;
    const wchar_t* subKey;
    const char* description;
} RegistryTarget;

RegistryTarget targets[] = {
    {HKEY_CURRENT_USER, L"Software\\Microsoft\\Windows\\CurrentVersion\\Run", "CU Run"},
    {HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", "LM Run"},
    {HKEY_CURRENT_USER, L"Software\\Microsoft\\Windows\\CurrentVersion\\RunOnce", "CU RunOnce"},
    {HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\RunOnce", "LM RunOnce"},
    {HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Winlogon", "Winlogon Shell/Userinit"},
    {HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options", "IFEO"}
};

void CheckRegistryKey(HKEY hRoot, const wchar_t* subKey, const char* desc) {
    HKEY hKey;
    if (RegOpenKeyExW(hRoot, subKey, 0, KEY_READ, &hKey) == ERROR_SUCCESS) {
        printf("[+] Checking: %s\n", desc);
        
        DWORD valueCount;
        DWORD maxNameLen;
        DWORD maxValueLen;
        
        if (RegQueryInfoKeyW(hKey, NULL, NULL, NULL, NULL, NULL, NULL, &valueCount, &maxNameLen, &maxValueLen, NULL, NULL) == ERROR_SUCCESS) {
            wchar_t* name = (wchar_t*)malloc((maxNameLen + 1) * sizeof(wchar_t));
            BYTE* data = (BYTE*)malloc(maxValueLen + 2); // Extra byte for safety/null terminator
            
            for (DWORD i = 0; i < valueCount; i++) {
                DWORD nameLen = maxNameLen + 1;
                DWORD dataLen = maxValueLen;
                DWORD type;
                
                if (RegEnumValueW(hKey, i, name, &nameLen, NULL, &type, data, &dataLen) == ERROR_SUCCESS) {
                    if (type == REG_SZ || type == REG_EXPAND_SZ) {
                        data[dataLen] = 0;
                        data[dataLen+1] = 0; // Ensure null terminator for wide strings too if needed
                        
                        char* utf8Name = WideToUtf8(name);
                        char* utf8Value = WideToUtf8((wchar_t*)data);
                        
                        printf("    - Name: %s\n      Value: %s\n", 
                               utf8Name ? utf8Name : "???", 
                               utf8Value ? utf8Value : "???");
                               
                        free(utf8Name);
                        free(utf8Value);
                    }
                }
            }
            free(name);
            free(data);
        }
        RegCloseKey(hKey);
    }
}

void ScanRegistryPersistence() {
    int numTargets = sizeof(targets) / sizeof(RegistryTarget);
    for (int i = 0; i < numTargets; i++) {
        CheckRegistryKey(targets[i].hRoot, targets[i].subKey, targets[i].description);
    }
}
