#include <string>
#include <utility>
#include "../include/Linda.h"

Linda::Linda(std::string dataFilePath, std::string sleepingProcessesPath, IParser* parser) {
    dataFile = new FileManager(std::move(dataFilePath));
    sleepingProcesses = new FileManager(std::move(sleepingProcessesPath));
    stringParser = parser;
}
Linda::~Linda() {
    delete dataFile;
    delete sleepingProcesses;
}

void Linda::output(const std::string& stringTemplate) {
    return output(*stringParser->parseCSV(stringTemplate));
}
void Linda::output(const Tuple& tuple) {
    dataFile->appendLine(tuple.toCSV());
}
Tuple* Linda::input(const std::string& stringTemplate, int timeout) {
    return input(*stringParser->parsePattern(stringTemplate), timeout);
}
Tuple* Linda::input(const Tuple& tupleTemplate, int timeout) {
    std::vector<std::string> data = Utilities::splitString(dataFile->readFile());
    int resultIndex = -1;
    Tuple* result = nullptr;

    for (int i=0;i<data.size();i++) {
        Tuple* tuple = stringParser->parseCSV(data[i]);
        if (tupleTemplate.compare(*tuple)) {
            result = tuple;
            resultIndex = i;
            break;
        }
    }
    if (resultIndex != -1) {
        data.erase(data.begin()+resultIndex);
        dataFile->writeFile(data);
    }
    //TODO Go to sleep
    return result;
}
Tuple* Linda::read(const std::string& stringTemplate, int timeout) {
    return read(*stringParser->parsePattern(stringTemplate), timeout);
}
Tuple* Linda::read(const Tuple& tupleTemplate, int timeout) {
    std::vector<std::string> data = Utilities::splitString(dataFile->readFile());
    int resultIndex = -1;
    Tuple* result = nullptr;

    for (int i=0;i<data.size();i++) {
        Tuple* tuple = stringParser->parseCSV(data[i]);
        if (tupleTemplate.compare(*tuple)) {
            result = tuple;
            resultIndex = i;
            break;
        }
    }
    //TODO Go to sleep
    return result;
}
