#include <iostream>
#include <array>
#include <memory>
#include <stdexcept>
#include <string>

std::string execCommand(const char* cmd);

int main() {
    try {
        std::string ipAddress = execCommand("hostname -I");
        std::cout << "IP Address: " << ipAddress << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    return 0;
}
