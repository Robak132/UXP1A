#ifndef TUPLE_H
#define TUPLE_H

#include <vector>
#include <string>
#include <sys/sem.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <fcntl.h>
#include "Entity.h"
#include "Utilities.h"

class Tuple {
public:
    Tuple() = default;
    Tuple(Tuple const &other) {
        entities = other.entities;
        semKey = 0;
    }
    explicit Tuple(std::vector<Entity> _entities) : entities(std::move(_entities)) { semKey = 0;}
    [[nodiscard]] bool compare(const Tuple& other) const;
    [[nodiscard]] std::string toCSV() const;
    [[nodiscard]] std::string toPattern() const;
    [[nodiscard]] std::string toFilePattern() const;
    
    void setSemKey(key_t address);    
    int semWait(int timeout);
    int semPost();
    void semInit();
    void semCreate();
    void semDelete();
    key_t getSemKey();

    friend std::ostream& operator << (std::ostream& outs, const Tuple& tuple) {
        return outs << tuple.toCSV();
    }
    friend bool operator== (const Tuple& left, const Tuple& right);

private:

    std::vector<Entity> entities;
    key_t semKey = -1;
    int semId = -1;
};
#endif /* TUPLE_H */
