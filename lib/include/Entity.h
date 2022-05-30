#ifndef ENTITY_H
#define ENTITY_H

#include <string>

enum Operator {
    LESS, MORE, EQ_LESS, EQ_MORE, EQUAL, ANY
};

enum Type {
    INT=0, FLOAT=1, STR=2, NONE=3
};

class Entity {
public:
    Entity(int value, Operator anOperator=EQUAL);
    Entity(double value, Operator anOperator=EQUAL);
    Entity(const std::string& value, Operator anOperator=EQUAL);

    static Entity createIntEntity() {return createIntEntity(0, ANY);}
    static Entity createDoubleEntity() {return createDoubleEntity(0, ANY);}
    static Entity createStringEntity() {return createStringEntity("", ANY);}

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
        return compareOperator;
    }
    void setOperator(Operator _op) {
        compareOperator = _op;
    }
    std::string toString() const;
    bool compare(const Entity& entity) const;
    bool compare(const Entity& entity, Operator _operator) const;

    friend bool operator== (const Entity& left, const Entity& right);
    friend bool operator!= (const Entity& left, const Entity& right);

private:
    Entity() = default;
    Type type = INT;
    Operator compareOperator = EQUAL;
    int intValue = 0;
    double doubleValue = 0;
    std::string stringValue;

    bool compareInt(const Entity& entity, Operator _operator) const;
    bool compareDouble(const Entity& entity, Operator _operator) const;
    bool compareString(const Entity& entity, Operator _operator) const;
};
#endif /* ENTITY_H */