#include <string>
#include "../include/linda.h"
#include "../include/file_manager.h"
#include "../include/parser.h"

Linda::Linda(const std::string &dataFilePath, const std::string &sleepingProcessesPath) :
    dataFile(FileManager(dataFilePath)), sleepingProcesses(FileManager(sleepingProcessesPath)) {
    Parser parser;
}

Linda::Linda() : Linda("../resources/tuples.csv", "../resources/sleeping.csv") {}