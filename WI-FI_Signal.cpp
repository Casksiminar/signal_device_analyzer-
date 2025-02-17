#include <iostream>
#include <array>
#include <memory>
#include <stdexcept>
#include <string>

static std::string execCommand(const char* cmd) {
    std::array<char, 128> buffer{};
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}

int main() {
    try {
        std::string iwconfigOutput = execCommand("iwconfig wlan0");
        std::size_t pos = iwconfigOutput.find("Signal level=");
        if (pos != std::string::npos) {
            std::string signalLevel = iwconfigOutput.substr(pos + 13, 6);
            std::cout << "Wi-Fi Signal Strength: " << signalLevel << std::endl;
        }
        else {
            std::cout << "Could not find signal strength information." << std::endl;
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    return 0;
}
