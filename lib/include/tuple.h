#ifndef TUPLE
#define TUPLE
#include <utility>
#include <vector>
#include <cstddef>

enum Operator {
    LESS, MORE, EQ_LESS, EQ_MORE, EQUAL, ANY, NONE
};

enum Type {
    INT=0, FLOAT=1, STR=2
};

class Entity {
public:
    virtual ~Entity() = default;
    Type getType() {
        return type;
    };
protected:
    explicit Entity(Type _type) : type(_type) {}
    Type type;
};

template <typename T>
class TypedEntity : public Entity {
public:
    TypedEntity(const T& val, Operator _op) : Entity(INT), value(val), op(_op) {}
    explicit TypedEntity(const T& val) : Entity(INT), value(val), op(NONE) {}

    const T& getValue() const {
        return value;
    };
    void setValue(const T& val) {
        value = val;
    }
    const Operator& getOperator() const {
        return op;
    };
    void setOperator(const Operator& _op) {
        op = _op;
    }
    template<typename S>
    bool compare(TypedEntity<S> entity) {
        return compare(entity, op);
    }
    template<typename S>
    bool compare(TypedEntity<S> entity, Operator _op) {
        if (typeid(T) != typeid(S)) {
            return false;
        }
        return true;
    }
private:
    T value;
    Operator op;
};

class Tuple {
public:
    explicit Tuple(std::vector<Entity*> _entities) : entities(std::move(_entities)) {}
    ~Tuple(){
        for(auto & entity : entities)
            delete entity;
    }
private:
    std::vector<Entity*> entities;
    int compare(Tuple other);
};
#endif /* TUPLE */