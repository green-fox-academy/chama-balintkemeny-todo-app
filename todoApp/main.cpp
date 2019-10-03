#include <iostream>
#include <fstream>

void printUsage() {
    std::cout << "Command Line Todo application" << std::endl;
    std::cout << "=============================" << std::endl;
    std::cout << "\n" << "Command line arguments:" << std::endl;
    std::cout << "      -l      Lists all the tasks" << std::endl;
    std::cout << "      -a      Adds a new task" << std::endl;
    std::cout << "      -r      Removes a task" << std::endl;
    std::cout << "      -c      Completes a task" << std::endl;
}

int utilityInputRowCounter(const std::string& fileName) {

    std::ifstream inputStream;
    inputStream.open(fileName);

    int numLines = 0;
    std::string temp;
    while (std::getline(inputStream, temp)) {
        ++numLines;
    }
    inputStream.close();
    return numLines;
}

void listTasks() {

    int inputRowsCount = utilityInputRowCounter("input.txt");
    std::string textRows;

    std::ifstream inputFile;
    inputFile.open("input.txt");

    if (inputRowsCount == 0) {
        std::cout << "No todos for today! :)";
    } else {
        for (int i = 0; i < inputRowsCount; ++i) {
            std::getline(inputFile, textRows);
            std::cout << i + 1 << " - " << textRows << std::endl;
        }
    }
    inputFile.close();
    
}

int main(int argc, char** argv) {

    if (argc == 1) {
        printUsage();
    } else if (std::string(argv[1]) == "-l") {
        listTasks();
    }

    return 0;
}