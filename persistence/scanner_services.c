#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include "scanner_services.h"
#include "utils.h"

void ScanServicesPersistence() {
    SC_HANDLE hSCM = OpenSCManagerW(NULL, NULL, SC_MANAGER_ENUMERATE_SERVICE);
    if (hSCM == NULL) {
        printf("[-] Failed to open SCManager (error: %lu)\n", GetLastError());
        return;
    }

    printf("[*] Enumerating Services & Drivers...\n");

    DWORD bytesNeeded, servicesCount, resumeHandle = 0;
    EnumServicesStatusExW(hSCM, SC_ENUM_PROCESS_INFO, SERVICE_TYPE_ALL, SERVICE_STATE_ALL, NULL, 0, &bytesNeeded, &servicesCount, &resumeHandle, NULL);

    BYTE* buffer = (BYTE*)malloc(bytesNeeded);
    if (EnumServicesStatusExW(hSCM, SC_ENUM_PROCESS_INFO, SERVICE_TYPE_ALL, SERVICE_STATE_ALL, buffer, bytesNeeded, &bytesNeeded, &servicesCount, &resumeHandle, NULL)) {
        ENUM_SERVICE_STATUS_PROCESSW* services = (ENUM_SERVICE_STATUS_PROCESSW*)buffer;
        int detectedCount = 0;

        for (DWORD i = 0; i < servicesCount; i++) {
            SC_HANDLE hService = OpenServiceW(hSCM, services[i].lpServiceName, SERVICE_QUERY_CONFIG);
            if (hService) {
                DWORD configBytesNeeded;
                QueryServiceConfigW(hService, NULL, 0, &configBytesNeeded);
                
                QUERY_SERVICE_CONFIGW* config = (QUERY_SERVICE_CONFIGW*)malloc(configBytesNeeded);
                if (QueryServiceConfigW(hService, config, configBytesNeeded, &configBytesNeeded)) {
                    // Filter heuristic: show services that start automatically and aren't in System32 (simplified)
                    if (config->dwStartType == SERVICE_AUTO_START && 
                        wcsstr(config->lpBinaryPathName, L"Windows\\System32") == NULL && 
                        wcsstr(config->lpBinaryPathName, L"WINDOWS\\system32") == NULL) {
                        
                        char* utf8Name = WideToUtf8(services[i].lpDisplayName);
                        char* utf8Path = WideToUtf8(config->lpBinaryPathName);
                        
                        printf("    [+] Service: %s\n", utf8Name ? utf8Name : "???");
                        printf("        Path: %s\n", utf8Path ? utf8Path : "???");
                        
                        free(utf8Name);
                        free(utf8Path);
                        detectedCount++;
                    }
                }
                free(config);
                CloseServiceHandle(hService);
            }
        }
        printf("[+] Analyzed %lu total, highlighted %d potential third-party auto-start entries.\n", servicesCount, detectedCount);
    }

    free(buffer);
    CloseServiceHandle(hSCM);
}
