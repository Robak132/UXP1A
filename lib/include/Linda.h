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
    Tuple* input(Tuple& tupleTemplate, int timeout=0);
    Tuple* read(Tuple& tupleTemplate, int timeout=0);
    void output(Tuple tuple);
    int semWait(int timeout, int semId);
    int semPost(int semId);

    int semInit(key_t key);
    void semCreate(key_t &semKey, int &semId);
    void semDelete(int semId);
private:
    FileManager* dataFile;
    FileManager* sleepingProcesses;
    IParser* stringParser;

    Tuple* getTuple(Tuple& tupleTemplate, FileManager* file, bool remove);
};
#endif /* LINDA_H */