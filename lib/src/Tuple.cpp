#include "../include/Tuple.h"
#include <sstream>

bool Tuple::compare(const Tuple& other) const {
    if (entities.size() != other.entities.size()) {
        return false;
    }

    for (int i=0;i<entities.size();i++) {
        if(!entities[i].compare(other.entities[i])) {
            return false;
        }
    }
    return true;
}
std::string Tuple::toCSV() const {
    std::string outputString;
    unsigned long entitiesSize = entities.size();
    for (unsigned long i = 0; i < entitiesSize; i++) {
        outputString += entities[i].toString();
        if (i != entitiesSize - 1) outputString += ",";
    }
    return outputString;
}

void Tuple::semCreate(){
    int sid = syscall(SYS_gettid);
	semKey = ftok(".", sid);
	semId = semget(semKey, 1, IPC_CREAT | IPC_EXCL | 0660);
}

void Tuple::semInit(key_t key){
    semKey = key;
    semId = semget(key, 1, 0660);
}

void Tuple::semDelete(){
    semctl(semId, 0, IPC_RMID);
	semKey = -1;
}

int Tuple::semWait(int timeout){
    struct sembuf lock = {0, -1, 0};
    timespec time;
    time.tv_sec = timeout;
    time.tv_nsec = 0;
    int value = semtimedop(semId, &lock, 1, &time);
    semDelete();
    return value;
}

int Tuple::semPost(){
    struct sembuf unlock = {0, 1, 0};
    int value = semop(semId, &unlock, 1);
    return value;
}

