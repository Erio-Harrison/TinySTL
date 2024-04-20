#include <iostream>
#define DEBUG

int main() {
#ifdef DEBUG
    // This code block will only compile if DEBUG is defined
    std::cout << "Debugging is enabled." << std::endl;
#endif

    std::cout << "Program running." << std::endl;
    return 0;
}

