#include "../include/Tuple.h"

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

std::string Tuple::toPattern() const {
    return "";
}

std::string Tuple::toFilePattern() const {
    std::string outputString;

    outputString += std::to_string(semaphoreAddress) + ", ";
    outputString += toPattern();

    return outputString;
}

void Tuple::setSemaphoreAddress(int address) {
    semaphoreAddress = address;
}

bool operator== (const Tuple& left, const Tuple& right) {
    if (left.entities.size() != right.entities.size()) {
        return false;
    }
    if (left.semaphoreAddress != right.semaphoreAddress) {
        return false;
    }

    for (int i=0; i < left.entities.size(); i++) {
        if (left.entities[i] != right.entities[i]) {
            return false;
        }
    }
    return true;
}
