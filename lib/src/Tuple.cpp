#include "../include/Tuple.h"
#include <iostream>


bool Tuple::compare(const Tuple& other) const {
    std::cout<<"comparing\n";
    if (entities.size() != other.entities.size()) {
        std::cout<<"wrong size\n";
        return false;
    }

    for (int i=0;i<entities.size();i++) {
        if(!entities[i].compare(other.entities[i])) {
            std::cout<<"wrong item\n";
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

std::string Tuple::toPattern() const {
    std::string outputString;
    unsigned long entitiesSize = entities.size();
    for (unsigned long i = 0; i < entitiesSize; i++) {
        outputString += entities[i].toPatternString();
        if (i != entitiesSize - 1) outputString += ",";
    }
    return outputString;
}

std::string Tuple::toFilePattern() const {
    std::string outputString;

    outputString += std::to_string(semKey) + ",";
    outputString += toPattern();

    return outputString;
}

void Tuple::setSemKey(key_t address) {
    semKey = address;
}

void Tuple::semCreate(){
    int sid = syscall(SYS_gettid);
	semKey = ftok(".", sid);
	semId = semget(semKey, 1, IPC_CREAT | IPC_EXCL | 0660);
}

void Tuple::semInit(){
    semId = semget(semKey, 1, 0660);
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

key_t Tuple::getSemKey(){
    return semKey;
}

bool operator== (const Tuple& left, const Tuple& right) {
    if (left.entities.size() != right.entities.size()) {
        return false;
    }
    if (left.semKey != right.semKey) {
        return false;
    }

    for (int i=0; i < left.entities.size(); i++) {
        if (left.entities[i] != right.entities[i]) {
            return false;
        }
    }
    return true;
}
