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

    
    Tuple* input(const std::string& stringTemplate, int timeout=0);
    Tuple* input(Tuple& tupleTemplate, int timeout=0);
    Tuple* read(Tuple& tupleTemplate, int timeout=0);
    Tuple* read(const std::string& stringTemplate, int timeout=0);
    void output(const std::string& stringTemplate);
    void output(Tuple& tuple);
private:
    FileManager* dataFile;
    FileManager* sleepingProcesses;
    IParser* stringParser;

    Tuple* getTuple(Tuple& tupleTemplate,  bool remove);
    Tuple* getTupleTemplate(Tuple& tuple);
    void removeTupleTemplate(Tuple& tupleTemplate);
};
#endif /* LINDA_H */
