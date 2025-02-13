#include <windows.h>
#include <iostream>

int main() {
    setlocale(0, "rus");
    HANDLE hParentProcess = GetCurrentProcess();
    DWORD parentProcessID = GetProcessId(hParentProcess);

    std::cout << "ID дочернего процесса: " << GetCurrentProcessId() << std::endl;
    std::cout << "ID родительского процесса: " << parentProcessID << std::endl;
    std::cout << "Адрес псевдодескриптора родительского процесса: " << &hParentProcess << std::endl;

    return 0;
}
