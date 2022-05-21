#ifndef LINDA
#define LINDA
#include "tuple.h"
class Linda {
public:
    Linda();
    explicit Linda(const std::string& file_path);
    int input(TuplePattern tupleTemplate, int timeout);
    int read(TuplePattern tupleTemplate, int timeout);
    int output(Tuple tuple);
};
#endif /* LINDA */