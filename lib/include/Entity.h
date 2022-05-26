#ifndef ENTITY
#define ENTITY

#include <string>

enum Operator {
    LESS, MORE, EQ_LESS, EQ_MORE, EQUAL, ANY
};

enum Type {
    INT=0, FLOAT=1, STR=2
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
    std::string toString() const;
    bool compare(const Entity& entity) const;
    bool compare(const Entity& entity, Operator _op) const;
private:
    Entity() = default;
    Type type = INT;
    Operator op = EQUAL;
    int intValue = 0;
    double doubleValue = 0;
    std::string stringValue;

    bool compareInt(const Entity& entity, Operator _op) const;
    bool compareDouble(const Entity& entity, Operator _op) const;
    bool compareString(const Entity& entity, Operator _op) const;
};
#endif /* ENTITY */