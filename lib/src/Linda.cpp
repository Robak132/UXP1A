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
    struct flock lock;
    lock.l_type    = F_WRLCK;  
    lock.l_start   = 0;
    lock.l_whence  = SEEK_SET;
    lock.l_len     = 0;
    dataFile ->lockFile(lock);
    dataFile->appendLine(tuple.toCSV());
    Tuple* result = getTuple(tuple, sleepingProcesses, true);
    if(result != nullptr){
        //    read semKey
        //    semId = semInit(read key)
        //    val = semPost()
    }
    dataFile->unlockFile();

}
Tuple* Linda::input(Tuple& tupleTemplate, int timeout) {
    
    Tuple* result = getTuple(tupleTemplate, dataFile, true);
    if (result == nullptr) {
        int semId;
        key_t semKey;
        semCreate(semKey, semId);
        // save semKey and tupleTemplate to sleepingProcess
        if(semWait(timeout, semId) == 0){
            result = getTuple(tupleTemplate, dataFile, true);
        }
        else{
            Tuple* result = getTuple(tupleTemplate, sleepingProcesses, true);
            return nullptr;
        }
    }
    return result;
}
Tuple* Linda::input(const std::string& stringTemplate, int timeout) {
    return input(*stringParser->parsePattern(stringTemplate), timeout);
}


Tuple* Linda::getTuple(Tuple& tuple, FileManager* file, bool remove){
    struct flock lock;
    if(remove)
        lock.l_type    = F_WRLCK;
    else 
        lock.l_type    = F_RDLCK;
    lock.l_start   = 0;
    lock.l_whence  = SEEK_SET;
    lock.l_len     = 0;
    file ->lockFile(lock);
    std::vector<std::string> data = Utilities::splitString(file->readFile());
    Tuple* result = nullptr;
    int resultIndex = -1;

    for (int i=0;i<data.size();i++) {
        Tuple* tuple = stringParser->parse(data[i]);
        if (tuple->compare(*tuple)) {
            result = tuple;
            resultIndex = i;
            break;
        }
    }
    if(remove && resultIndex != -1){
        data.erase(data.begin()+resultIndex);
        file->writeFile(data);
    }
    file->unlockFile();
    return result;
}
Tuple* Linda::read(const std::string& stringTemplate, int timeout) {
    return read(*stringParser->parsePattern(stringTemplate), timeout);
}

Tuple* Linda::read(Tuple& tupleTemplate, int timeout) {
   

    Tuple* result = getTuple(tupleTemplate, dataFile, false);

    if (result == nullptr){
        int semId;
        key_t semKey;
        semCreate(semKey, semId);
        // save semKey and tupleTemplate to sleepingProcess
        if(semWait(timeout, semId) == 0){
            result = getTuple(tupleTemplate, dataFile, false);
        }
        else{
            Tuple* result = getTuple(tupleTemplate, sleepingProcesses, true);
            return nullptr;
        }

    }
    return result;
}

void Linda::semCreate(key_t &semKey, int &semId){
    int sid = syscall(SYS_gettid);
	semKey = ftok(".", sid);
	semId = semget(semKey, 1, IPC_CREAT | IPC_EXCL | 0660);
}

int Linda::semInit(key_t key){
    return semget(key, 1, 0660);
}

void Linda::semDelete(int semId){
    semctl(semId, 0, IPC_RMID);
}

int Linda::semWait(int timeout, int semId){
    struct sembuf lock = {0, -1, 0};
    timespec time;
    time.tv_sec = timeout;
    time.tv_nsec = 0;
    int value = semtimedop(semId, &lock, 1, &time);
    semDelete(semId);
    return value;
}

int Linda::semPost(int semId){
    struct sembuf unlock = {0, 1, 0};
    int value = semop(semId, &unlock, 1);
    return value;
}