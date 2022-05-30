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

    
    int semWait(int timeout, int semId);
    int semPost(int semId);
    int semInit(key_t key);
    void semCreate(key_t &semKey, int &semId);
    void semDelete(int semId);
    
    Tuple* input(const std::string& stringTemplate, int timeout=0);
    Tuple* input(const Tuple& tupleTemplate, int timeout=0);
    Tuple* read(const Tuple& tupleTemplate, int timeout=0);
    Tuple* read(const std::string& stringTemplate, int timeout=0);
    void output(const std::string& stringTemplate);
    void output(const Tuple& tuple);
private:
    FileManager* dataFile;
    FileManager* sleepingProcesses;
    IParser* stringParser;

    Tuple* getTuple(Tuple& tupleTemplate, FileManager* file, bool remove);
};
#endif /* LINDA_H */
