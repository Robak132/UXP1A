#ifndef LINDA_H
#define LINDA_H
#include "Tuple.h"
#include "FileManager.h"
#include "Parser.h"

class Linda {
public:
    ~Linda();
    explicit Linda(std::string dataFilePath = "../resources/linda_test_data.csv",
                   std::string sleepingProcessesPath = "../resources/sleeping.csv",
                   IParser* parser = new Parser());
    Tuple* input(const Tuple& tupleTemplate, int timeout=0);
    Tuple* read(const Tuple& tupleTemplate, int timeout=0);
    void output(Tuple tuple);
private:
    FileManager* dataFile;
    FileManager* sleepingProcesses;
    IParser* stringParser;
};
#endif /* LINDA_H */