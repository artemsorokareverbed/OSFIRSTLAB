#include <windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include "employee.h"

bool runProcess(std::string cmd) {
    STARTUPINFOA si{};
    PROCESS_INFORMATION pi{};
    si.cb = sizeof(si);

    if (!CreateProcessA(nullptr, cmd.data(), nullptr, nullptr, FALSE, 0, nullptr, nullptr, &si, &pi)) {
        std::cerr << "Error: CreateProcess failed for: " << cmd << " (" << GetLastError() << ")\n";
        return false;
    }

    WaitForSingleObject(pi.hProcess, INFINITE);

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
    return true;
}

void printBinaryFile(const std::string& filename) {
    std::ifstream in(filename, std::ios::binary);
    if (!in.is_open()) {
        std::cerr << "Error: cannot open " << filename << "\n";
        return;
    }

    std::cout << "\n=== Binary file: " << filename << " ===\n";
    employee emp{};
    while (in.read(reinterpret_cast<char*>(&emp), sizeof(employee))) {
        std::cout << "ID: " << emp.num 
                  << " | Name: " << emp.name 
                  << " | Hours: " << emp.hours << "\n";
    }
    std::cout << "=================================\n";
}

void printTextFile(const std::string& filename) {
    std::ifstream in(filename);
    if (!in.is_open()) {
        std::cerr << "Error: cannot open " << filename << "\n";
        return;
    }

    std::cout << "\n=== Text report: " << filename << " ===\n";
    std::string line;
    while (std::getline(in, line)) {
        std::cout << line << "\n";
    }
    std::cout << "================================\n";
}

int main() {
    std::string binFile;
    int count = 0;

    std::cout << "Binary filename: ";
    std::cin >> binFile;
    std::cout << "Record count: ";
    std::cin >> count;

    std::string creatorCmd = "Creator.exe " + binFile + " " + std::to_string(count);
    if (!runProcess(creatorCmd)) return 1;

    printBinaryFile(binFile);

    std::string reportFile;
    double rate = 0.0;

    std::cout << "\nReport filename: ";
    std::cin >> reportFile;
    std::cout << "Hourly rate: ";
    std::cin >> rate;

    std::string reporterCmd = "Reporter.exe " + binFile + " " + reportFile + " " + std::to_string(rate);
    if (!runProcess(reporterCmd)) return 1;

    printTextFile(reportFile);

    return 0;
}