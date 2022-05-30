#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <iostream>
#include <vector>
#include <list>
#include <map>
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

static const std::string END_OF_FILE = "\0";
static const std::string BACKSLASH = "\\";

static const std::map<std::string, int> WHITESPACES{
        {" ", 0},
        {"\t", 0},
        {"\n", 0},
        {"\v", 0},
        {"\f", 0},
        {"\r", 0},
};

static const std::map<std::string, TokenType> SIMPLE_SINGLE_TOKENS{
        {"<", LESS_TOKEN},
        {">", MORE_TOKEN},
        {"=", EQUALS_TOKEN},
        {"*", UNSPECIFIED_RELATION_TOKEN},
        {"-", MINUS_TOKEN},
        {":", COLON_TOKEN},
        {",", COMA_TOKEN},
        {END_OF_FILE, END_TOKEN}
};

static const std::vector<TokenType> SIMPLE_DOUBLE_TOKENS_PREFIXES {{LESS_TOKEN, MORE_TOKEN}};

static const std::map<std::string, TokenType> SIMPLE_DOUBLE_TOKENS{
        {"<=", LESS_EQUAL_TOKEN},
        {">=", MORE_EQUAL_TOKEN},
};

static const std::map<std::string, TokenType> KEYWORD_TOKENS{
        {"integer", INT_KEYWORD_TOKEN},
        {"float", FLOAT_KEYWORD_TOKEN},
        {"string", STRING_KEYWORD_TOKEN},
};


static std::map<std::string, std::string> ESCAPE_CHARACTERS = {
        {"n", "\n"},        // New line
        {"r", "\r"},        // Carriage return
        {"t", "\t"},        // Tab
        {"b", "\b"},        // Backspace
        {"f", "\f"},        // Form feed
        {"\\", BACKSLASH},  // Backslash
        {"0", END_OF_FILE}, // End of file
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

    [[nodiscard]] int getIntegerValue() const;
    [[nodiscard]] double getDoubleValue() const;
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
    int currentCharacterIndex = 0;

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
