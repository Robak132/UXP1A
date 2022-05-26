#include <string>
#include <sstream>
#include "../include/Entity.h"

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

bool Entity::compare(const Entity& entity) const {
    return compare(entity, op);
}
bool Entity::compare(const Entity& entity, Operator _op) const {
    if (type != entity.type) return false; // Wrong type -> false
    if (_op == ANY) return true;           // Any value & good type -> true

    switch (type) {
        case INT:
            return compareInt(entity, _op);
        case FLOAT:
            return compareDouble(entity, _op);
        case STR:
            return compareString(entity, _op);
    }
}
bool Entity::compareInt(const Entity &entity, Operator _op) const {
    switch (_op) {
        case EQ_MORE:
            return intValue >= entity.intValue;
        case EQUAL:
            return intValue == entity.intValue;
        case LESS:
            return intValue < entity.intValue;
        case MORE:
            return intValue > entity.intValue;
        case EQ_LESS:
            return intValue <= entity.intValue;
        case ANY:
            return true;
    }
}
bool Entity::compareDouble(const Entity &entity, Operator _op) const {
    switch (_op) {
        case EQ_MORE:
            return doubleValue >= entity.doubleValue;
        case EQUAL:
            return doubleValue == entity.doubleValue;
        case LESS:
            return doubleValue < entity.doubleValue;
        case MORE:
            return doubleValue > entity.doubleValue;
        case EQ_LESS:
            return doubleValue <= entity.doubleValue;
        case ANY:
            return true;
    }}
bool Entity::compareString(const Entity &entity, Operator _op) const {
    switch (_op) {
        case EQ_MORE:
            return stringValue >= entity.stringValue;
        case EQUAL:
            return stringValue == entity.stringValue;
        case LESS:
            return stringValue < entity.stringValue;
        case MORE:
            return stringValue > entity.stringValue;
        case EQ_LESS:
            return stringValue <= entity.stringValue;
        case ANY:
            return true;
    }}

std::string Entity::toString() const {
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
