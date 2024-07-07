#include "Screens.h"
#include <SFML/Graphics.hpp>
#include <iostream>

// Main function that initializes and runs the game
int main() {
    try {
        Screens s;
        s.run();
    }
    catch (const std::exception& e) {
        std::cerr << "Unhandled exception: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    catch (...) {
        std::cerr << "Unhandled unknown exception" << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
