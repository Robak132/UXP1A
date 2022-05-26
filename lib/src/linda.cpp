#include <string>
#include <utility>
#include "../include/linda.h"
#include "../include/utilities.h"

Linda::Linda(std::string dataFilePath, std::string sleepingProcessesPath, IParser* parser) {
    dataFile = new FileManager(std::move(dataFilePath));
    sleepingProcesses = new FileManager(std::move(sleepingProcessesPath));
    stringParser = parser;
}
Linda::~Linda() {
    delete dataFile;
    delete sleepingProcesses;
}

void Linda::output(Tuple tuple) {
    dataFile->appendLine(tuple.toCSV());
}
Tuple* Linda::input(const Tuple& tupleTemplate, int timeout) {
    std::vector<std::string> data = Utilities::splitString(dataFile->readFile());
    int resultIndex = -1;
    Tuple result;

    for (int i=0;i<data.size();i++) {
        Tuple tuple = stringParser->parse(data[i]);
        if (tupleTemplate.compare(tuple)) {
            result = tuple;
            resultIndex = i;
            break;
        }
    }
    if (resultIndex != -1) {
        data.erase(data.begin()+resultIndex);
        dataFile->writeFile(data);
        return new Tuple(result);
    }
    //TODO Go to sleep
    return nullptr;
}
Tuple* Linda::read(const Tuple& tupleTemplate, int timeout) {
    std::vector<std::string> data = Utilities::splitString(dataFile->readFile());
    int resultIndex = -1;
    Tuple result;

    for (int i=0;i<data.size();i++) {
        Tuple tuple = stringParser->parse(data[i]);
        if (tupleTemplate.compare(tuple)) {
            result = tuple;
            resultIndex = i;
            break;
        }
    }
    if (resultIndex != -1) {
        return new Tuple(result);
    }
    //TODO Go to sleep
    return nullptr;
}
