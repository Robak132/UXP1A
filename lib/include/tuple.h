#ifndef TUPLE
#define TUPLE
#include <vector>

enum Operator {
    LESS, MORE, EQ_LESS, EQ_MORE, EQUAL, ANY
};
enum Type {
    INT, FLOAT, STR
};
class EntityPattern {
    Type type;
    int* value;
    int size;
    Operator op;
};
class TuplePattern {
    std::vector <EntityPattern> entities;
    int* semaphore;
};
class Entity {
    Type type;
    int* value;
    int size;
    int compare(EntityPattern other);
};
class Tuple {
    std::vector<Entity> entities;
    int compare(TuplePattern other);
};
#endif /* TUPLE */