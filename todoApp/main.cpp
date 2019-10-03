#include <iostream>

int main(int argc, char** argv) {
    if (argc == 1) {
        std::cout << "Command Line Todo application" << std::endl;
        std::cout << "=============================" << std::endl;
        std::cout << "\n" << "Command line arguments:" << std::endl;
        std::cout << "      -l      Lists all the tasks" << std::endl;
        std::cout << "      -a      Adds a new task" << std::endl;
        std::cout << "      -r      Removes a task" << std::endl;
        std::cout << "      -c      Completes a task" << std::endl;
    };
    return 0;
}