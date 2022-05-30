#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <iostream>
#include <vector>
#include <list>
#include "Tuple.h"
#include "Utilities.h"

const int MAX_STRING_LENGTH = 200;

class ScanningException : public std::exception {
    [[nodiscard]] const char * what () const noexcept override {
        return "Scanning exception.";
    }
};

class ExceededStringLimitException : ScanningException {
    [[nodiscard]] const char * what () const noexcept override {
        return "Exceeded the maximum length of the string in tuple.";
    }
};

class UnterminatedStringException : ScanningException {
    [[nodiscard]] const char * what () const noexcept override {
        return "The string seems to be terminated incorrectly.";
    }
};

class UnexpectedCharacterException : ScanningException {
    [[nodiscard]] const char * what () const noexcept override {
        return "Unexpected character during scanning.";
    }
};


class ParsingException : public std::exception {
    [[nodiscard]] const char * what () const noexcept override {
        return "Parsing exception.";
    }
};

class UnexpectedTokenException : ParsingException {
    [[nodiscard]] const char * what () const noexcept override {
        return "Unexpected token during parsing.";
    }
};

class NoSemaphoreAddressException : ParsingException {
    [[nodiscard]] const char * what () const noexcept override {
        return "No semaphore address provided.";
    }
};


enum TokenType {
    EQUALS_TOKEN, MORE_TOKEN, LESS_TOKEN, MORE_EQUAL_TOKEN, LESS_EQUAL_TOKEN,
    UNSPECIFIED_RELATION_TOKEN,
    NUMERIC_LITERAL_TOKEN, STRING_LITERAL_TOKEN,
    INT_KEYWORD_TOKEN, FLOAT_KEYWORD_TOKEN, STRING_KEYWORD_TOKEN,
    MINUS_TOKEN,
    COLON_TOKEN, COMA_TOKEN,
    UNKNOWN_TOKEN, END_TOKEN
};



class Token {
public:
    Token();
    explicit Token(TokenType tokenType);
    Token(Token const &other);
    Token(std::string value, TokenType tokenType);
    Token(int value, TokenType tokenType);
    Token(double value, TokenType tokenType);
    TokenType getType();
    Type getValueType();

    int getIntegerValue() const;
    double getDoubleValue() const;
    std::string* getStringValue();

    friend bool operator== (const Token& left, const Token& right);


private:
    TokenType type;
    Type valueType;
    int integerValue;
    double doubleValue;
    std::string stringValue;
};



class Lexer {
public:
    Lexer() = default;
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
    Token* getKeyword();
    std::string buildString();
    int buildInteger();
    static bool isDecimal(const std::string& character);
    double buildFraction();
};



class IParser {
public:
    virtual Tuple* parse(const std::string& text) = 0;
    virtual Tuple* parseCSV(const std::string& text) = 0;
    virtual Tuple* parsePattern(const std::string& text) = 0;
    virtual Tuple* parseFilePattern(const std::string& text) = 0;
};



class Parser : public IParser {
public:
    Parser() = default;
    Tuple* parse(const std::string& text) override;
    Tuple* parseCSV(const std::string& text) override;
    Tuple* parsePattern(const std::string& text) override;
    Tuple* parseFilePattern(const std::string& text) override;

private:
    Token currentToken = Token(UNKNOWN_TOKEN);
    Lexer lexer;

    void nextToken();
    Token* consumeToken(TokenType tokenType, bool isStrict = true);
    Token* consumeToken(const std::list<TokenType>& tokenTypes, bool isStrict = true);
    Entity* parseEntity();
    Entity* parseEntityPattern();
    Entity* parseString();
    Entity* parseNumber();
    Operator parseRelationOperator();
};




class MockParser : public IParser {
public:
    explicit MockParser(std::vector<Tuple> results_);
    Tuple* parse(const std::string& text) override;
    Tuple* parseCSV(const std::string& text) override;
    Tuple* parsePattern(const std::string& text) override;
    Tuple* parseFilePattern(const std::string& text) override;

private:
    std::vector<Tuple> results;
    int iterator = 0;
};
#endif /* PARSER_H */