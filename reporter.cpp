#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include "employee.h"

int main(int argc, char* argv[]) {
    if (argc < 4) {
        std::cerr << "Error: Reporter <bin_file> <report_file> <rate>\n";
        return 1;
    }

    const char* binFile = argv[1];
    const char* reportFile = argv[2];
    double rate = std::stod(argv[3]);

    std::ifstream in(binFile, std::ios::binary);
    if (!in.is_open()) {
        std::cerr << "Error: failed to open " << binFile << "\n";
        return 1;
    }

    std::ofstream out(reportFile);
    if (!out.is_open()) { 
        std::cerr << "Error: failed to open " << reportFile << "\n";
        return 1;
    }

    out << "Report for file \"" << binFile << "\"\n";
    out << std::left
        << std::setw(10) << "ID"
        << std::setw(12) << "Name"
        << std::setw(10) << "Hours"
        << std::setw(12) << "Salary" << "\n";

    employee emp{};
    while (in.read(reinterpret_cast<char*>(&emp), sizeof(employee))) {
        double salary = emp.hours * rate;
        out << std::left
            << std::setw(10) << emp.num
            << std::setw(12) << emp.name
            << std::setw(10) << std::fixed << std::setprecision(2) << emp.hours
            << std::setw(12) << std::fixed << std::setprecision(2) << salary << "\n";
    }

    in.close();
    out.close();

    std::cout << "[Reporter] Report generated: " << reportFile << "\n";
    return 0;
}