#include <string>
#include <utility>
#include "../include/Linda.h"
#include "../include/Utilities.h"

Linda::Linda(std::string dataFilePath, std::string sleepingProcessesPath, IParser* parser) {
    dataFile = new FileManager(std::move(dataFilePath));
    sleepingProcesses = new FileManager(std::move(sleepingProcessesPath));
    stringParser = parser;
}
Linda::~Linda() {
    delete dataFile;
    delete sleepingProcesses;
}

void Linda::output(Tuple& tuple) {
    dataFile->appendLine(tuple.toCSV());
    Tuple* result = getTuple(tuple, sleepingProcesses, true);
    if(result != nullptr){
        //    read semKey
        //    semId = semInit(read key)
        //    val = semPost()
    }

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
            //remove tupleTemplate from sleeping.csv
            return nullptr;
        }

    }
    return result;
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
            //remove tupleTemplate from sleeping.csv
            return nullptr;
        }

    }
    return result;
}

Tuple* Linda::getTuple(Tuple& tupleTemplate, FileManager* file, bool remove){
    std::vector<std::string> data = Utilities::splitString(file->readFile());
    Tuple* result = nullptr;
    int resultIndex = -1;

    for (int i=0;i<data.size();i++) {
        Tuple* tuple = stringParser->parse(data[i]);
        if (tupleTemplate.compare(*tuple)) {
            result = tuple;
            resultIndex = i;
            break;
        }
    }
    if(remove && resultIndex != -1){
        data.erase(data.begin()+resultIndex);
        dataFile->writeFile(data);
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