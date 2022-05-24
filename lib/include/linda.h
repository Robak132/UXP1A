#ifndef LINDA
#define LINDA
#include "tuple.h"
class Linda {
public:
    Linda();
    explicit Linda(const std::string& file_path);
    int input(Tuple tupleTemplate, int timeout);
    int read(Tuple tupleTemplate, int timeout);
    int output(Tuple tuple);
};
#endif /* LINDA */