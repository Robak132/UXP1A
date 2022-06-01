#include <string>
#include <utility>
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
    struct flock lock{};
    lock.l_type    = F_WRLCK;  
    lock.l_start   = 0;
    lock.l_whence  = SEEK_SET;
    lock.l_len     = 0;
    dataFile ->lockFile(lock);
    std::cout << "Output process locked dataFile"<<std::endl;
    dataFile->appendLine(tuple.toCSV());
    std::cout << "Output process now is browsing sleepingProcesses file"<<std::endl;
    Tuple* result = getTupleTemplate(tuple, true);
    if(result != nullptr){
        std::cout << "Output process found matching template"<<std::endl;
        result -> semInit();
        result -> semPost();
        std::cout << "Output process did sempost operation\n";
    }
    dataFile->unlockFile();

}

Tuple* Linda::input(const std::string& stringTemplate, int timeout) {
    return input(*stringParser->parsePattern(stringTemplate), timeout);
}

Tuple* Linda::input(Tuple& tupleTemplate, int timeout) {
    
    Tuple* result = getTuple(tupleTemplate, true);
    if (result == nullptr) {
        std::cout << "Input process did not find matching tuple"<<std::endl;
        tupleTemplate.semCreate();
        struct flock lock{};
        lock.l_type    = F_WRLCK;  
        lock.l_start   = 0;
        lock.l_whence  = SEEK_SET;
        lock.l_len     = 0;
        sleepingProcesses -> lockFile(lock);
        std::cout << "Input process locked sleepingFile"<<std::endl;
        sleepingProcesses -> appendLine(tupleTemplate.toFilePattern());
        std::cout << "Input process saved it's pattern"<<std::endl;
        sleepingProcesses -> unlockFile();
        std::cout << "Input process unlocked sleepingFile"<<std::endl;
        if(tupleTemplate.semWait(timeout) == 0){
            std::cout << "Input process has been awaken by output process"<<std::endl;
            return getTuple(tupleTemplate, true);
        }
        else{
            getTupleTemplate(tupleTemplate, false);
            std::cout << "Input process waited too long"<<std::endl;
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
        std::cout << "Read process did not find matching tuple"<<std::endl;
        tupleTemplate.semCreate();
        struct flock lock{};
        lock.l_type    = F_WRLCK;  
        lock.l_start   = 0;
        lock.l_whence  = SEEK_SET;
        lock.l_len     = 0;
        sleepingProcesses -> lockFile(lock);
        std::cout << "Read process locked sleepingProcess File"<<std::endl;
        sleepingProcesses -> appendLine(tupleTemplate.toFilePattern());
        std::cout << "Read process saved it's pattern"<<std::endl;
        sleepingProcesses -> unlockFile();
        std::cout << "Read process unlocked sleepingFile"<<std::endl;
        if(tupleTemplate.semWait(timeout) == 0){
            std::cout << "Read process has been awaken by output process"<<std::endl;
            result = getTuple(tupleTemplate, false);
        }
        else{
            getTupleTemplate(tupleTemplate, false);
            tupleTemplate.semDelete();
            std::cout << "Read process waited too long"<<std::endl;
            return nullptr;
        }

    }
    return result;
}

Tuple* Linda::getTuple(Tuple& tuplePattern,  bool remove){
    struct flock lock{};
    if(remove)
        lock.l_type    = F_WRLCK;
    else 
        lock.l_type    = F_RDLCK;
    lock.l_start   = 0;
    lock.l_whence  = SEEK_SET;
    lock.l_len     = 0;
    dataFile ->lockFile(lock);
    std::cout << "Input/Read process locked dataFile"<<std::endl;
    std::vector<std::string> data = Utilities::splitString(dataFile->readFile());
    Tuple* result = nullptr;
    int resultIndex = -1;
    for (int i=0;i<data.size();i++) {
        Tuple* tupleFound = stringParser->parseCSV(data[i]);
        if (tuplePattern.compare(*tupleFound)) {
            std::cout <<"Input/Read process found matching tuple\n";
            result = tupleFound;
            resultIndex = i;
            break;
        }
    }
    if(remove && resultIndex != -1){
        data.erase(data.begin()+resultIndex);
        dataFile->writeFile(data);
        std::cout <<"Input process removed matching tuple\n";
    }
    dataFile->unlockFile();
    std::cout << "Input/Read Process unlocked dataFile"<<std::endl;
    return result;
}

Tuple* Linda::getTupleTemplate(Tuple& tuple, bool isOutput){
    struct flock lock{};
    lock.l_type    = F_WRLCK;
    lock.l_start   = 0;
    lock.l_whence  = SEEK_SET;
    lock.l_len     = 0;
    sleepingProcesses ->lockFile(lock);
    std::cout << "Output process locked sleepingProcess file"<<std::endl;
    std::vector<std::string> data = Utilities::splitString(sleepingProcesses->readFile());
    Tuple* result = nullptr;
    int resultIndex = -1;
    for (int i=0;i<data.size();i++) {
        Tuple* templateFound = stringParser->parseFilePattern(data[i]);
        if (isOutput) {
            if (templateFound->compare(tuple)) {
                std::cout <<"Output process found matching template\n";
                result = templateFound;
                resultIndex = i;
                break;
            }
        }
        else if (*templateFound == tuple){
                std::cout <<"Read/Input process found  it's semKey\n";
                result = templateFound;
                resultIndex = i;
                break;
        }
    }
    if(resultIndex != -1){
        data.erase(data.begin()+resultIndex);
        sleepingProcesses->writeFile(data);
        std::cout << "Process removed template"<<std::endl;
    }
    sleepingProcesses->unlockFile();
    std::cout << "Process unlocked sleepingProcess file"<<std::endl;
    return result;
}