#include <string>
#include <utility>
#include "../include/Linda.h"
#include "../include/Utilities.h"

Linda::Linda(std::string dataFilePath, std::string sleepingProcessesPath, IParser* parser) {
    dataFile = new FileManager(std::move(dataFilePath));
    sleepingProcesses = new FileManager(std::move(sleepingProcessesPath));
    stringParser = parser;
}
Linda::~Linda() {
    delete dataFile;
    delete sleepingProcesses;
}

void Linda::output(const Tuple& tuple) {
    dataFile->appendLine(tuple.toCSV());
}
Tuple* Linda::input(const Tuple& tupleTemplate, int timeout) {
    std::vector<std::string> data = Utilities::splitString(dataFile->readFile());
    int resultIndex = -1;
    Tuple* result = nullptr;

    for (int i=0;i<data.size();i++) {
        Tuple* tuple = stringParser->parse(data[i]);
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
Tuple* Linda::read(const Tuple& tupleTemplate, int timeout) {
    Tuple result;
    findTuple(tupleTemplate, result, timeout);
    return new Tuple(result);
}
int Linda::findTuple(const Tuple& tupleTemplate, Tuple& result, int timeout) {
    std::vector<std::string> data = Utilities::splitString(dataFile->readFile());
    int resultIndex = -1;

    for (int i=0;i<data.size();i++) {
        Tuple* tuple = stringParser->parse(data[i]);
        if (tupleTemplate.compare(*tuple)) {
            result = *tuple;
            resultIndex = i;
            delete tuple;
            break;
        }
    }
    return resultIndex;
}