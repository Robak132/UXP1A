#include "../include/parser.h"

#include <utility>


Parser::Parser() {

}

Tuple Parser::parse(const std::string& text) {
    std::vector<std::string> splitText = this -> splitText(text);
}

std::string Parser::toCSV(Tuple tuple) {
    return "";
}

int Parser::parseInt(std::string text) {
    return 0;
}

float Parser::parseFloat(std::string text) {
    return 0.0;
}

std::string Parser::parseString(std::string text) {
    return "";
}

std::vector<std::string> Parser::splitText(std::string text) {
    std::vector<std::string> elements;

    return elements;
}

MockParser::MockParser(std::vector<Tuple> results_) {
    results = std::move(results_);
}

Tuple MockParser::parse(const std::string& text) {
    if (results.size() <= iterator) iterator=0;
    return results[iterator++];
}