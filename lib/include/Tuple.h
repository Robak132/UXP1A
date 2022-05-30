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
        semaphoreAddress = 0;
    }
    explicit Tuple(std::vector<Entity> _entities) : entities(std::move(_entities)) { semaphoreAddress = 0;}
    bool compare(const Tuple& other) const;
    std::string toCSV() const;
    void addSemaphoreAddress(int address);

    friend std::ostream& operator << (std::ostream& outs, const Tuple& tuple) {
        return outs << tuple.toCSV();
    }
    friend bool operator== (const Tuple& left, const Tuple& right);

private:

    std::vector<Entity> entities;
    int semaphoreAddress = 0;
};
#endif /* TUPLE_H */