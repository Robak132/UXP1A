#ifndef LINDA
#define LINDA
#include "Tuple.h"
#include "file_manager.h"
#include "parser.h"

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
#endif /* LINDA */