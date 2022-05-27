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
Tuple Linda::input(const Tuple& tupleTemplate, int timeout) {
    std::vector<std::string> data = Utilities::splitString(dataFile->readFile());
    Tuple result;
    int resultIndex;

    if ((resultIndex = findTuple(data, tupleTemplate, result, timeout)) == -1) {
        //TODO Go to sleep
    }
    if (resultIndex != -1) {
        data.erase(data.begin()+resultIndex);
        dataFile->writeFile(data);
    }
    return result;
}
Tuple Linda::read(const Tuple& tupleTemplate, int timeout) {
    std::vector<std::string> data = Utilities::splitString(dataFile->readFile());
    Tuple result;
    int resultIndex;

    if ((resultIndex = findTuple(data, tupleTemplate, result, timeout)) == -1) {
        //TODO Go to sleep
    }
    return result;
}
int Linda::findTuple(std::vector<std::string> data, const Tuple& tupleTemplate, Tuple& result, int timeout) {
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