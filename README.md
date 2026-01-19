# Persistence Investigator (Auto-Audit)

[Russian Version Below | Русская версия ниже](#russian-version)

A standalone, lightweight Windows audit tool written in Pure C to identify common persistence mechanisms used by software (and malware).

## 🚀 Features

- **Registry Scanning**: 
    - `HKCU/HKLM\Software\Microsoft\Windows\CurrentVersion\Run`
    - `HKCU/HKLM\Software\Microsoft\Windows\CurrentVersion\RunOnce`
    - `Winlogon` Shell and Userinit values.
    - `Image File Execution Options` (IFEO) hijacking detection.
- **Startup Folders**:
    - Scans both User and System-wide Startup directories.
- **Service & Driver Audit**:
    - Enumerates all services and drivers.
    - Filters and highlights third-party auto-start entries not located in `System32`.
- **Full UTF-8 Support**: Correctly displays localized names (Cyrillic, etc.) in the Windows Console.

## 🛠️ Build Requirements

- Windows OS
- GCC (MinGW-w64)
- Libraries: `advapi32`, `shell32`

## 🔨 How to Build (GCC)

```bash
gcc main.c scanner_registry.c scanner_folders.c scanner_services.c utils.c -o persistence_investigator.exe -ladvapi32 -lshell32
```

## 📋 Usage

1. Open **CMD** or **PowerShell** as **Administrator**.
2. Run the executable:
```bash
.\persistence_investigator.exe
```

---


# Persistence Investigator (Auto-Audit) [RUS]

Автономная легковесная утилита на чистом C для аудита механизмов закрепления (persistence) в Windows, используемых легитимным ПО и вредоносными программами.

## 🚀 Возможности

- **Сканирование реестра**: 
    - Проверка веток `Run` и `RunOnce` (HKCU/HKLM).
    - Проверка параметров `Shell` и `Userinit` в Winlogon.
    - Детект подмены через `Image File Execution Options` (IFEO).
- **Папки автозагрузки**:
    - Сканирование пользовательской и общесистемной папок автозагрузки.
- **Аудит сервисов и драйверов**:
    - Перечисление всех служб и драйверов.
    - Автоматическая фильтрация и выделение сторонних записей (не из `System32`), настроенных на автозапуск.
- **Поддержка UTF-8**: Корректное отображение кириллицы и других локализованных символов в консоли Windows.

## 🛠️ Требования для сборки

- Windows OS
- Компилятор GCC (MinGW-w64)
- Библиотеки: `advapi32`, `shell32`

## 🔨 Инструкция по сборке (GCC)

```bash
gcc main.c scanner_registry.c scanner_folders.c scanner_services.c utils.c -o persistence_investigator.exe -ladvapi32 -lshell32
```

## 📋 Использование

1. Запустите **CMD** или **PowerShell** от имени **Администратора**.
2. Запустите скомпилированный файл:
```bash
.\persistence_investigator.exe
```

## 🛡️ Educational Purpose

