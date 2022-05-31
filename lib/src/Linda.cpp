#include <string>
#include <utility>
#include <typeinfo>
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

void Linda::output(Tuple& tuple) {
    struct flock lock;
    lock.l_type    = F_WRLCK;  
    lock.l_start   = 0;
    lock.l_whence  = SEEK_SET;
    lock.l_len     = 0;
    std::cout << "output lock dataFile"<<std::endl;
    dataFile ->lockFile(lock);
    dataFile->appendLine(tuple.toCSV());
    std::cout << "output get sleeping"<<std::endl;
    Tuple* result = getTupleTemplate(tuple);
    if(result != nullptr){
        result -> semInit();
        result -> semPost();
    }
    dataFile->unlockFile();

}

Tuple* Linda::input(const std::string& stringTemplate, int timeout) {
    return input(*stringParser->parsePattern(stringTemplate), timeout);
}

Tuple* Linda::input(Tuple& tupleTemplate, int timeout) {
    
    Tuple* result = getTuple(tupleTemplate, true);
    if (result == nullptr) {
        tupleTemplate.semCreate();
        // save semKey and tupleTemplate to sleepingProcess
        struct flock lock;
        lock.l_type    = F_WRLCK;  
        lock.l_start   = 0;
        lock.l_whence  = SEEK_SET;
        lock.l_len     = 0;
        std::cout << "input lock sleeping"<<std::endl;
        sleepingProcesses -> lockFile(lock);
        sleepingProcesses -> appendLine(tupleTemplate.toFilePattern());
        sleepingProcesses -> unlockFile();
        if(tupleTemplate.semWait(timeout) == 0){
            return getTuple(tupleTemplate, true);
        }
        else{
            Tuple* removed = getTupleTemplate(tupleTemplate);
            std::cout << "got nullptr"<<std::endl;
            return nullptr;
        }
    }
    return result;
}


Tuple* Linda::read(const std::string& stringTemplate, int timeout) {
    return read(*stringParser->parsePattern(stringTemplate), timeout);
}

Tuple* Linda::read(Tuple& tupleTemplate, int timeout) {
   

    Tuple* result = getTuple(tupleTemplate, false);

    if (result == nullptr){
        tupleTemplate.semCreate();
        // save semKey and tupleTemplate to sleepingProcess
        struct flock lock;
        lock.l_type    = F_WRLCK;  
        lock.l_start   = 0;
        lock.l_whence  = SEEK_SET;
        lock.l_len     = 0;
        std::cout << "read lock sleeping"<<std::endl;
        sleepingProcesses -> lockFile(lock);
        sleepingProcesses -> appendLine(tupleTemplate.toFilePattern());
        sleepingProcesses -> unlockFile();
        if(tupleTemplate.semWait(timeout) == 0){
            result = getTuple(tupleTemplate, false);
        }
        else{
            Tuple* result = getTupleTemplate(tupleTemplate);
            std::cout << "got nullptr"<<std::endl;
            return nullptr;
        }

    }
    return result;
}

Tuple* Linda::getTuple(Tuple& tuplePattern,  bool remove){
    struct flock lock;
    if(remove)
        lock.l_type    = F_WRLCK;
    else 
        lock.l_type    = F_RDLCK;
    lock.l_start   = 0;
    lock.l_whence  = SEEK_SET;
    lock.l_len     = 0;
    std::cout << "input/read lock dataFile"<<std::endl;
    dataFile ->lockFile(lock);
    std::vector<std::string> data = Utilities::splitString(dataFile->readFile());
    Tuple* result = nullptr;
    int resultIndex = -1;
    std::cout << "looping over data\n";
    for (int i=0;i<data.size();i++) {
        Tuple* tupleFound = stringParser->parseCSV(data[i]);
        std::cout <<typeid(tupleFound).name()<<"\n";
        std::cout << "got one of tuples\n";
        if (tuplePattern.compare(*tupleFound)) {
            std::cout <<"found proper tuple\n";
            result = tupleFound;
            resultIndex = i;
            break;
        }
    }
    if(remove && resultIndex != -1){
        data.erase(data.begin()+resultIndex);
        dataFile->writeFile(data);
    }
    dataFile->unlockFile();
    return result;
}

Tuple* Linda::getTupleTemplate(Tuple& tuple){
    struct flock lock;
    lock.l_type    = F_WRLCK;
    lock.l_start   = 0;
    lock.l_whence  = SEEK_SET;
    lock.l_len     = 0;
    std::cout << "lock sleeping"<<std::endl;
    sleepingProcesses ->lockFile(lock);
    std::vector<std::string> data = Utilities::splitString(sleepingProcesses->readFile());
    Tuple* result = nullptr;
    int resultIndex = -1;
    std::cout << "looping over data\n";
    for (int i=0;i<data.size();i++) {
        Tuple* templateFound = stringParser->parseFilePattern(data[i]);
        std::cout << "got one of templates\n";
        if (tuple.compare(*templateFound)) {
            std::cout <<"found proper template\n";
            result = templateFound;
            resultIndex = i;
            break;
        }
    }
    if(resultIndex != -1){
        data.erase(data.begin()+resultIndex);
        sleepingProcesses->writeFile(data);
    }
    std::cout << "unlock sleeping\n";
    sleepingProcesses->unlockFile();
    std::cout << resultIndex << "\n";
    return result;
}