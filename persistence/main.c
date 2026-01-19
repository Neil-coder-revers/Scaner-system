#include <windows.h>
#include <stdio.h>
#include "scanner_registry.h"
#include "scanner_folders.h"
#include "scanner_services.h"

void PrintBanner() {
    printf("========================================\n");
    printf("     Persistence Investigator v0.1      \n");
    printf("        System Audit Tool (C)           \n");
    printf("========================================\n\n");
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    PrintBanner();

    printf("[*] Starting Registry Scan...\n");
    ScanRegistryPersistence();

    printf("\n[*] Starting Folder Scan...\n");
    ScanFolderPersistence();

    printf("\n[*] Starting Services Scan...\n");
    ScanServicesPersistence();

    printf("\n[*] Scan Complete.\n");
    return 0;
}
