#include "../../lib/include/Tuple.h"
#include "../../lib/include/Linda.h"

int main(int argc, char * argv[] ) {
    if(argc == 1) throw std::invalid_argument("Specifify as argument what string to write in test tuple.");
    else if(argc > 2) throw std::invalid_argument("Unable to interpret that many arguments.");

    Linda linda = Linda("../tests/workers/data.csv", "../tests/workers/processes.csv");

    Tuple tuple = Tuple(std::vector<Entity>{
            Entity::createStringEntity(std::string(argv[1])),
    });

    linda.output(tuple);
    
    return 0;
}