#include <iostream>
#include <fstream>
#include <vector>
#include <exception>
#include <algorithm>

std::vector<int> readChecked(const std::string& fileName);

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

void listTasks(const std::string& fileName) {
    int inputRowsCount = utilityInputRowCounter(fileName);
    std::string textRows;
    std::ifstream inputStream;
    inputStream.open(fileName);
    std::vector<int> checkedTasks = readChecked("vector.txt");

    if (inputRowsCount == 0) {
        std::cout << "No todos for today! :)";
    } else {
        for (int i = 0; i < inputRowsCount; ++i) {
            std::getline(inputStream, textRows);
            if (std::count(checkedTasks.begin(), checkedTasks.end(), i)) {
                std::cout << i + 1 << " - [X] " << textRows << std::endl;
            } else {
                std::cout << i + 1 << " - [ ] " << textRows << std::endl;
            }
        }
    }
    inputStream.close();
}

void addTask(const std::string& fileName, const std::string& taskName) {
    std::ofstream outputStream;
    outputStream.open(fileName, std::ios::app);
    outputStream << taskName << "\n";
    outputStream.close();
}

void removeTask(const std::string& fileName, int taskIndex) {
    std::ifstream inputStream;
    inputStream.open(fileName);
    std::vector<std::string> tempVec;

    while (!inputStream.eof()) {
        std::string tempStr;
        std::getline(inputStream, tempStr);
        tempVec.push_back(tempStr);
    }
    inputStream.close();

    std::ofstream outputStream;
    outputStream.open(fileName);
    tempVec.erase(tempVec.begin() + (taskIndex - 1));

    for (unsigned int i = 0; i < tempVec.size(); ++i) {
        if (i == tempVec.size() - 1) {
            outputStream << tempVec[i];
        } else {
            outputStream << tempVec[i] << std::endl;
        }
    }
    outputStream.close();
}

void checkTask(const std::string& outputFileName, int taskIndex) {
    std::ofstream outputStream;
    outputStream.open(outputFileName, std::ios::app);
    outputStream << taskIndex << " ";
    outputStream.close();
}

std::vector<int> readChecked(const std::string& fileName) {
    std::ifstream inputStream;
    inputStream.open(fileName);
    std::vector<int> output;

    int temp;
    while (inputStream >> temp) {
        output.push_back(temp);
    }

    inputStream.close();
    return output;
}

int main(int argc, char** argv) {

    if (argc == 1) {
        printUsage();
    } else if (std::string(argv[1]) == "-l") {
        listTasks("input.txt");
    } else if (std::string(argv[1]) == "-a") {
        if (argc == 2) {
            std::cout << "Unable to add: No task provided" << std::endl;
        } else {
            addTask("input.txt", std::string(argv[2]));
        }
    } else if (std::string(argv[1]) == "-r") {
        if (argc == 2) {
            std::cout << "Unable to remove: No index provided" << std::endl;
        } else {
            try {
                std::stoi(argv[2]);
            }
            catch(std::invalid_argument& e){
                std::cout << "Unable to remove: index is not a number" << std::endl;
            }
            if (std::stoi(argv[2]) > utilityInputRowCounter("input.txt") || std::stoi(argv[2]) < 1) {
                std::cout << "Unable to remove: Index is out of bound" << std::endl;
            } else {
                removeTask("input.txt", std::stoi(argv[2]));
            }
        }
    } else if (std::string(argv[1]) == "-c") {
        if (argc == 2) {
            std::cout << "Unable to check: No index provided" << std::endl;
        } else {
            try {
                std::stoi(argv[2]);
            }
            catch(std::invalid_argument& e){
                std::cout << "Unable to check: index is not a number" << std::endl;
            }
            if (std::stoi(argv[2]) > utilityInputRowCounter("input.txt") || std::stoi(argv[2]) < 1) {
                std::cout << "Unable to check: Index is out of bound" << std::endl;
            } else {
                checkTask("vector.txt",std::stoi(argv[2]) - 1);
                std::cout << "Task completed" << std::endl;
            }
        }
    } else {
        std::cout << "Unsupported argument" << std::endl;
        printUsage();
    }

    return 0;

}