#include "../include/tuple.h"
#include <sstream>

Entity Entity::createIntEntity(int value, Operator anOperator) {
    Entity entity = Entity();
    entity.setIntValue(value);
    entity.setOperator(anOperator);
    return entity;
}

Entity Entity::createDoubleEntity(double value, Operator anOperator) {
    Entity entity = Entity();
    entity.setDoubleValue(value);
    entity.setOperator(anOperator);
    return entity;
}

Entity Entity::createStringEntity(const std::string& value, Operator anOperator) {
    Entity entity = Entity();
    entity.setStringValue(value);
    entity.setOperator(anOperator);
    return entity;
}

bool Entity::compare(const Entity& entity, Operator _op) {
    if (type != entity.type) {
        return false;
    }
    return true;
}

std::string Entity::toString() {
    std::ostringstream stream;
    switch (type) {
        case INT:
            stream << intValue;
            return stream.str();
        case FLOAT:
            stream << doubleValue;
            return stream.str();
        case STR:
            return '"' + stringValue + '"';
    }
}

bool Tuple::compare(Tuple other) {
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

std::string Tuple::toCSV() {
    std::string outputString;
    unsigned long entitiesSize = entities.size();
    for (unsigned long i = 0; i < entitiesSize; i++) {
        outputString += entities[i].toString();
        if (i != entitiesSize - 1) outputString += ",";
    }
    return outputString;
}
