#ifndef LINDA
#define LINDA
#include "tuple.h"
#include "file_manager.h"

class Linda {
public:
    Linda();
    Linda(const std::string& dataFilePath, const std::string& sleepingProcessesPath);
    int input(Tuple tupleTemplate, int timeout);
    int read(Tuple tupleTemplate, int timeout);
    int output(Tuple tuple);
private:
    FileManager dataFile;
    FileManager sleepingProcesses;
};
#endif /* LINDA */