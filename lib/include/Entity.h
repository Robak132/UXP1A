#ifndef ENTITY_H
#define ENTITY_H

#include "Utilities.h"
#include <string>

enum Operator {
    LESS, MORE, EQ_LESS, EQ_MORE, EQUAL, ANY
};

enum Type {
    INT=0, FLOAT=1, STR=2, NONE=3
};

class Entity {
public:
    explicit Entity(Type entityType);
    explicit Entity(int value, Operator anOperator=EQUAL);
    explicit Entity(double value, Operator anOperator=EQUAL);
    explicit Entity(const std::string& value, Operator anOperator=EQUAL);

    static Entity createIntEntity();
    static Entity createDoubleEntity();
    static Entity createStringEntity();
    static Entity createIntEntity(int value, Operator anOperator=EQUAL);
    static Entity createDoubleEntity(double value, Operator anOperator=EQUAL);
    static Entity createStringEntity(const std::string& value, Operator anOperator=EQUAL);

    Type getType();
    [[nodiscard]] int getIntValue() const;
    void setIntValue(int _intValue);
    [[nodiscard]] double getDoubleValue() const;
    void setDoubleValue(double _doubleValue);
    [[nodiscard]] const std::string &getStringValue() const;
    void setStringValue(const std::string &_stringValue);
    [[nodiscard]] Operator getOperator() const;
    void setOperator(Operator _op);
    [[nodiscard]] std::string toString() const;
    [[nodiscard]] std::string toPatternString() const;
    [[nodiscard]] std::string operatorToString() const;
    [[nodiscard]] bool compare(const Entity& entity) const;
    [[nodiscard]] bool compare(const Entity& entity, Operator _operator) const;

    friend bool operator== (const Entity& left, const Entity& right);
    friend bool operator!= (const Entity& left, const Entity& right);

private:
    Entity() = default;
    Type type = INT;
    Operator compareOperator = EQUAL;
    int intValue = 0;
    double doubleValue = 0;
    std::string stringValue;

    [[nodiscard]] bool compareInt(const Entity& entity, Operator _operator) const;
    [[nodiscard]] bool compareDouble(const Entity& entity, Operator _operator) const;
    [[nodiscard]] bool compareString(const Entity& entity, Operator _operator) const;
};
#endif /* ENTITY_H */
