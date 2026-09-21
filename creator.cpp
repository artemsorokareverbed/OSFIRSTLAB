#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cstdlib>
#include "employee.h"

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cerr << "Error: Creator <filename> <count>\n";
        return 1;
    }

    const char* filename = argv[1];
    int count = std::atoi(argv[2]);

    if (count <= 0) {
        std::cerr << "Error: count must be positive\n";
        return 1;
    }

    std::ofstream out(filename, std::ios::binary);
    if (!out.is_open()) {
        std::cerr << "Error: failed to open " << filename << " for writing\n";
        return 1;
    }

    for (int i = 0; i < count; ++i) {
        employee emp{};
        std::string nameBuffer;

        std::cout << "\n--- Record " << (i + 1) << " / " << count << " ---\n";
        std::cout << "ID: ";
        std::cin >> emp.num;

        std::cout << "Name (max 9 chars): ";
        std::cin >> nameBuffer;
        
        std::strncpy(emp.name, nameBuffer.c_str(), sizeof(emp.name) - 1);
        emp.name[sizeof(emp.name) - 1] = '\0';

        std::cout << "Hours: ";
        std::cin >> emp.hours;

        out.write(reinterpret_cast<const char*>(&emp), sizeof(employee));
    }

    out.close();
    std::cout << "\n[Creator] Finished creating " << count << " records.\n";
    return 0;
}