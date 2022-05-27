#include "../include/parser.h"

#include <utility>


Parser::Parser() {

Token::Token(TokenType tokenType) {
    type = tokenType;
    valueType = NONE;
}

Token::Token(std::string value, TokenType tokenType) {
    type = tokenType;
    stringValue = value;
    valueType = STR;
}

Token::Token(int value, TokenType tokenType) {
    type = tokenType;
    integerValue = value;
    valueType = INT;
}

Token::Token(double value, TokenType tokenType) {
    type = tokenType;
    doubleValue = value;
    valueType = FLOAT;
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
