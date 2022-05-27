#include "../include/Parser.h"

#include <utility>
#include <map>


const std::map<std::string, int> WHITESPACES{
        {" ", 0},
        {"\t", 0},
        {"\n", 0},
        {"\v", 0},
        {"\f", 0},
        {"\r", 0},
};


Token::Token(TokenType tokenType) {
    type = tokenType;
    integerValue = 0;
    doubleValue = 0;
    valueType = NONE;
}

Token::Token(std::string value, TokenType tokenType) {
    type = tokenType;
    stringValue = std::move(value);
    integerValue = 0;
    doubleValue = 0;
    valueType = STR;
}

Token::Token(int value, TokenType tokenType) {
    type = tokenType;
    integerValue = value;
    doubleValue = 0;
    valueType = INT;
}

Token::Token(double value, TokenType tokenType) {
    type = tokenType;
    doubleValue = value;
    integerValue = 0;
    valueType = FLOAT;
}


TokenType Token::getType() {
    return type;
}

template<typename T>
T Token::getValue() {
    switch (valueType) {
        case INT:
            return integerValue;
        case FLOAT:
            return doubleValue;
        case STR:
            return stringValue;
        case NONE:
            return nullptr;
    }
}



Lexer::Lexer(const std::string &input) {
    sourceText = input;
    if (input.length() > 0) {
        currentCharacter = input[0];
        currentCharacterIndex = 0;
    }
}

void Lexer::nextCharacter() {
    if (currentCharacterIndex + 1 < sourceText.length()) {
        currentCharacter = sourceText[++currentCharacterIndex];
    }
}

void Lexer::omitWhitespaces() {
    while (WHITESPACES.contains(currentCharacter)) {
        nextCharacter();
    }
}

Token Lexer::getNextToken() {
    omitWhitespaces();
    Token *token;

    token = getSimpleToken();
    if (token) return *token;

    token = getNumberLiteral();
    if (token) return *token;

    token = getStringLiteral();
    if (token) return *token;

    return Token(UNKNOWN_TOKEN);
}



Tuple* Parser::parse(const std::string& text) {
    return nullptr;
}



MockParser::MockParser(std::vector<Tuple> results_) {
    results = std::move(results_);
}

Tuple* MockParser::parse(const std::string& text) {
    if (results.size() <= iterator) iterator=0;
    Tuple result = results[iterator++];
    return new Tuple(result);
}