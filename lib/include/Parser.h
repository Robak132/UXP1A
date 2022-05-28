#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <iostream>
#include <vector>
#include "Tuple.h"


enum TokenType {
    EQUALS_TOKEN, MORE_TOKEN, LESS_TOKEN, MORE_EQUAL_TOKEN, LESS_EQUAL_TOKEN,
    UNSPECIFIED_RELATION_TOKEN,
    NUMERIC_LITERAL_TOKEN, STRING_LITERAL_TOKEN,
    COLON_TOKEN, COMA_TOKEN,
    UNKNOWN_TOKEN
};



class Token {
public:
    explicit Token(TokenType tokenType);
    Token(std::string value, TokenType tokenType);
    Token(int value, TokenType tokenType);
    Token(double value, TokenType tokenType);
    TokenType getType();

    template <typename T>
    T getValue();

private:
    TokenType type;
    Type valueType;
    int integerValue;
    double doubleValue;
    std::string stringValue;
};



class Lexer {
public:
    explicit Lexer(const std::string& input);
    Token getNextToken();

private:
    std::string sourceText;
    std::string currentCharacter;
    int currentCharacterIndex;

    void nextCharacter();
    void omitWhitespaces();
    Token* getSimpleToken();
    Token* getStringLiteral();
    Token* getNumberLiteral();
    std::string buildString();
    int buildInteger();
    static bool isDecimal(const std::string& character);
    double buildFraction();
};



class IParser {
public:
    virtual Tuple* parse(const std::string& text) = 0;
};



class Parser : public IParser {
public:
    Parser() = default;
    Tuple* parse(const std::string& text) override;

private:
    Token consumeToken(TokenType);
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