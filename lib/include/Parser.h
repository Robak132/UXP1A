#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <iostream>
#include <vector>
#include "Tuple.h"

class IParser {
public:
    virtual Tuple* parse(const std::string& text) = 0;
};

class Parser : public IParser {
public:
    Parser() = default;

    Tuple* parse(const std::string& text) override;
    std::string toCSV(Tuple tuple);

private:
    std::vector<std::string> string_elements;

    int parseInt(std::string text);
    float parseFloat(std::string text);
    std::string parseString(std::string text);
    std::vector<std::string> splitText(std::string text);
};

class MockParser : public IParser {
public:
    explicit MockParser(std::vector<Tuple> results_);
    Tuple* parse(const std::string& text) override;
private:
    std::vector<Tuple> results;
    int iterator = 0;
};
#endif /* PARSER_H */