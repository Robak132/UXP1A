#include <string>
#include <sstream>
#include "../include/Entity.h"

Entity::Entity(Type entityType) {
    intValue = 0;
    doubleValue = 0;
    compareOperator = ANY;
    type = entityType;
}

Entity::Entity(int value, Operator anOperator) {
    intValue = value;
    doubleValue = 0;
    compareOperator = anOperator;
    type = INT;
}

Entity::Entity(double value, Operator anOperator) {
    doubleValue = value;
    intValue = 0;
    compareOperator = anOperator;
    type = FLOAT;
}

Entity::Entity(const std::string& value, Operator anOperator) {
    stringValue = value;
    intValue = 0;
    doubleValue = 0;
    compareOperator = anOperator;
    type = STR;
}

Entity Entity::createIntEntity() {
    return createIntEntity(0, ANY);
}

Entity Entity::createDoubleEntity() {
    return createDoubleEntity(0, ANY);
}

Entity Entity::createStringEntity() {
    return createStringEntity("", ANY);
}

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

Type Entity::getType() {
    return type;
}

int Entity::getIntValue() const {
    return intValue;
}

void Entity::setIntValue(int _intValue) {
    intValue = _intValue;
    type = INT;
}

double Entity::getDoubleValue() const {
    return doubleValue;
}

void Entity::setDoubleValue(double _doubleValue) {
    doubleValue = _doubleValue;
    type = FLOAT;
}

const std::string& Entity::getStringValue() const {
    return stringValue;
}

void Entity::setStringValue(const std::string &_stringValue) {
    stringValue = _stringValue;
    type = STR;
}

Operator Entity::getOperator() const {
    return compareOperator;
}

void Entity::setOperator(Operator _op) {
    compareOperator = _op;
}

bool Entity::compare(const Entity& entity) const {
    return compare(entity, compareOperator);
}

bool Entity::compare(const Entity& entity, Operator _operator) const {
    if (type != entity.type) return false; // Wrong type -> false
    if (_operator == ANY) return true;           // Any value & good type -> true

    switch (type) {
        case INT:
            return compareInt(entity, _operator);
        case FLOAT:
            return compareDouble(entity, _operator);
        case STR:
            return compareString(entity, _operator);
        case NONE:
        default:
            return false;
    }
}

bool Entity::compareInt(const Entity &entity, Operator _operator) const {
    switch (_operator) {
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
        default:
            return true;
    }
}

bool Entity::compareDouble(const Entity &entity, Operator _operator) const {
    switch (_operator) {
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
        default:
            return true;
    }}
bool Entity::compareString(const Entity &entity, Operator _operator) const {
    switch (_operator) {
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
        default:
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
        case NONE:
        default:
            return "";
    }
}

std::string Entity::toPatternString() const {
    std::ostringstream stream;
    switch (type) {
        case INT:
            if (compareOperator == ANY) return "integer:" + operatorToString();
            stream << "integer:" << operatorToString() << intValue;
            return stream.str();
        case FLOAT:
            if (compareOperator == ANY) return "float:" + operatorToString();
            stream << "float:" << operatorToString() << doubleValue;
            return stream.str();
        case STR:
            if (compareOperator == ANY) return "string:" + operatorToString();
            return "string:" + operatorToString() + '"' + stringValue + '"';
        case NONE:
        default:
            return "";
    }
}

std::string Entity::operatorToString() const {
    switch (compareOperator) {
        case LESS:
            return "<";
        case MORE:
            return ">";
        case EQ_LESS:
            return "<=";
        case EQ_MORE:
            return ">=";
        case EQUAL:
            return "=";
        case ANY:
            return "*";
    }
}

bool operator== (const Entity& left, const Entity& right) {
    if (left.type == right.type and left.compareOperator == right.compareOperator) {
        switch (left.type) {
            case INT:
                return left.intValue == right.intValue;
            case FLOAT:
                return Utilities::compare_float(left.doubleValue, right.doubleValue);
            case STR:
                return left.stringValue == right.stringValue;
            case NONE:
                return true;
        }
    } else return false;
}

bool operator!= (const Entity& left, const Entity& right) {
    return !(left == right);
}
