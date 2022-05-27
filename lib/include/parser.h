#include "tuple.h"
#include <string>
#include <iostream>


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
    Lexer();
    Token getNextToken();
private:
    std::string sourceText;
    std::string currentCharacter;
    int currentCharacterIndex;
    void nextCharacter();
    void omitWhitespaces();
    Token getSimpleToken();
    Token getStringLiteral();
    Token getNumberLiteral();
    std::string buildString();
    int buildInteger();
    double buildFraction();
};


class Parser {
public:
    Parser();
    Tuple parse(const std::string& text);
private:
    Token consumeToken(TokenType);

};
