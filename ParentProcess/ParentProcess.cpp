#include <windows.h>
#include <iostream>
#include <sstream>

int main() {
    setlocale(0, "rus");

    DWORD parentProcessID = GetCurrentProcessId();
    HANDLE hParentProcess = GetCurrentProcess();
    HANDLE hDupProcess = NULL;

    std::wcout << L"ID родительского процесса: " << parentProcessID << std::endl;

    if (!DuplicateHandle(
        GetCurrentProcess(), hParentProcess,
        GetCurrentProcess(), &hDupProcess,
        PROCESS_TERMINATE, TRUE, DUPLICATE_SAME_ACCESS))
    {
        std::wcerr << L"Ошибка дублирования дескриптора. Код ошибки: " << GetLastError() << std::endl;
        return 1;
    }

    // создаю командную строку для дочернего процесса
    std::wstringstream commandLine;
    commandLine << L"ChildProcess.exe " << (uint64_t)hDupProcess;
    std::wstring commandStr = commandLine.str();

    STARTUPINFO si = { sizeof(STARTUPINFO) };
    PROCESS_INFORMATION pi;

    if (!CreateProcessW(
        NULL,
        &commandStr[0],
        NULL, NULL, TRUE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi))
    {
        std::wcerr << L"Ошибка при создании дочернего процесса. Код ошибки: " << GetLastError() << std::endl;
        return 1;
    }

    std::wcout << L"Дочерний процесс запущен с ID: " << pi.dwProcessId << std::endl;

    WaitForSingleObject(pi.hProcess, INFINITE);

    CloseHandle(hDupProcess);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    return 0;
}
