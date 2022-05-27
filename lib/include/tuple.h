#ifndef TUPLE
#define TUPLE
#include <utility>
#include <vector>
#include <cstddef>
#include <string>

enum Operator {
    LESS, MORE, EQ_LESS, EQ_MORE, EQUAL, ANY
};

enum Type {
    INT=0, FLOAT=1, STR=2, NONE=3
};

class Entity {
public:
    static Entity createIntEntity(int value, Operator anOperator=EQUAL);
    static Entity createDoubleEntity(double value, Operator anOperator=EQUAL);
    static Entity createStringEntity(const std::string& value, Operator anOperator=EQUAL);

    Type getType() {
        return type;
    };
    int getIntValue() const {
        return intValue;
    }
    void setIntValue(int _intValue) {
        intValue = _intValue;
        type = INT;
    }
    double getDoubleValue() const {
        return doubleValue;
    }
    void setDoubleValue(double _doubleValue) {
        doubleValue = _doubleValue;
        type = FLOAT;
    }
    const std::string &getStringValue() const {
        return stringValue;
    }
    void setStringValue(const std::string &_stringValue) {
        stringValue = _stringValue;
        type = STR;
    }
    Operator getOperator() const {
        return op;
    }
    void setOperator(Operator _op) {
        op = _op;
    }
    std::string toString();
    bool compare(const Entity& entity, Operator _op = EQUAL);
private:
    Entity() = default;
    Type type = INT;
    Operator op = EQUAL;
    int intValue = 0;
    double doubleValue = 0;
    std::string stringValue;
};

class Tuple {
public:
    explicit Tuple(std::vector<Entity> _entities) : entities(std::move(_entities)) {}
    bool compare(Tuple other);
    std::string toCSV();
private:
    std::vector<Entity> entities;
};
#endif /* TUPLE */