#include "tuple.h"
#include <string>
#include <iostream>

class Parser {
public:
    Parser();
    Tuple parse(std::string text);
    std::string toCSV(Tuple tuple);

private:
    std::vector<std::string> string_elements;

    int parseInt(std::string text);
    float parseFloat(std::string text);
    std::string parseString(std::string text);
    std::vector<std::string> splitText(std::string text);
};
