#include <windows.h>
#include <iostream>
#include <cstdlib>

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "rus");

    std::cout << "Дочерний процесс запущен!" << std::endl;

    if (argc < 2) {
        std::cerr << "Ошибка: Не передан дескриптор родительского процесса!" << std::endl;
        return 1;
    }

    // получаю дескриптор родительского процесса
    HANDLE hParentProcess = (HANDLE)_strtoui64(argv[1], NULL, 10);

    if (hParentProcess == NULL || hParentProcess == INVALID_HANDLE_VALUE) {
        std::cerr << "Ошибка: Неверный дескриптор родительского процесса!" << std::endl;
        return 1;
    }

    DWORD parentProcessID = GetProcessId(hParentProcess);
    DWORD childProcessID = GetCurrentProcessId();

    std::cout << "ID дочернего процесса: " << childProcessID << std::endl;
    std::cout << "ID родительского процесса: " << parentProcessID << std::endl;

    Sleep(2000);

    if (TerminateProcess(hParentProcess, 0)) {
        std::cout << "Родительский процесс завершён!" << std::endl;
    }
    else {
        std::cerr << "Ошибка завершения родительского процесса!" << std::endl;
    }

    Sleep(5000);

    return 0;
}
