#include <iostream>
#include "SchoolManagerSystem.h"

int main() {
    PA3::SchoolManagerSystem system;

    int choice;
    do {
        system.displayMenu();
        std::cout << ">> ";
        std::cin >> choice;
        system.executeMenuChoice(choice);
    } while (choice != 0);

    return 0;
}
