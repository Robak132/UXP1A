#ifndef TUPLE_H
#define TUPLE_H

#include <vector>
#include <string>
#include <sys/sem.h>
#include <sys/syscall.h>
#include <unistd.h>
#include "Entity.h"
#include "Utilities.h"

class Tuple {
public:
    Tuple() = default;
    Tuple(Tuple const &other) {
        entities = other.entities;
    }
    explicit Tuple(std::vector<Entity> _entities) : entities(std::move(_entities)) {}
    bool compare(const Tuple& other) const;
    std::string toCSV() const;

    friend std::ostream& operator << (std::ostream& outs, const Tuple& tuple) {
        return outs << tuple.toCSV();
    }

    int semWait(int timeout);
    int semPost();

private:

    void semInit(key_t key);
    void semCreate();
    void semDelete();

    std::vector<Entity> entities;
    int semId;
    key_t semKey;


};
#endif /* TUPLE_H */