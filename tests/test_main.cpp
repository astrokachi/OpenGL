// tests/test_main.cpp
#include <iostream>

// declare the function from test_orbit.cpp
bool runOrbitTest();

int main() {
    std::cout << "Running dummy test..." << std::endl;
    // Dummy "always pass" check
    std::cout << "Dummy Test Passed!\n";

    std::cout << "Running Orbit Test..." << std::endl;
    if (runOrbitTest()) {
        std::cout << "Orbit Test Passed!" << std::endl;
        return 0;
    } else {
        std::cout << "Orbit Test Failed!" << std::endl;
        return 1;
    }
}
