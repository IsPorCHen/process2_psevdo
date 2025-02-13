#include <windows.h>
#include <iostream>

int main() {
    setlocale(0, "rus");
    DWORD currentProcessID = GetCurrentProcessId();

    std::cout << "ID родительского процесса: " << currentProcessID << std::endl;

    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    ZeroMemory(&si, sizeof(si));
    ZeroMemory(&pi, sizeof(pi));

    si.cb = sizeof(si);

    HANDLE hProcess = GetCurrentProcess();

    if (!CreateProcess(
        L"C:\\Users\\ipch\\source\\repos\\ParentProcess\\x64\\Debug\\ChildProcess.exe",
        NULL,
        NULL,
        NULL,
        TRUE,
        0,
        NULL,
        NULL,
        &si,
        &pi
    )) {
        std::cerr << "Ошибка при создании дочернего процесса. Код ошибки: " << GetLastError() << std::endl;
        return 1;
    }

    std::cout << "Дочерний процесс запущен с ID: " << pi.dwProcessId << std::endl;
    std::cout << "Данные переданы в дочерний процесс." << std::endl;

    WaitForSingleObject(pi.hProcess, INFINITE);

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    return 0;
}
