#ifndef UTILITIES
#define UTILITIES
#include "tuple.h"
#include "string"

class Utilities {
public:
    static std::vector<std::string> splitString(const std::string& input);
private:
    Utilities();
};
#endif /* UTILITIES */