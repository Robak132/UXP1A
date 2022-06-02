#include "../../lib/include/Tuple.h"
#include "../../lib/include/Linda.h"

int main(int argc, char * argv[] ) {
    int timeout = 0;
    if(argc ==3) {
        if(std::stoi(argv[2])>=0) timeout = std::stoi(argv[2]);
        else throw std::invalid_argument("Timeout must be bigger or equal zero.");
    }
    else if(argc == 1) throw std::invalid_argument("Specifify as argument what string to write in test tuple.");
    else if(argc > 3) throw std::invalid_argument("Unable to interpret that many arguments.");
    Linda linda = Linda("../tests/workers/data.csv", "../tests/workers/processes.csv");

    Tuple tuple = Tuple(std::vector<Entity>{
            Entity::createStringEntity(std::string(argv[1])),
    });

    linda.read(tuple, timeout);
    
    return 0;
}