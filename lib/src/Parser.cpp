#include "../include/Parser.h"

#include <cmath>
#include <utility>
#include <map>
#include <cctype>


const std::string END_OF_FILE = "\0";
const std::string BACKSLASH = "\\";

const std::map<std::string, int> WHITESPACES{
        {" ", 0},
        {"\t", 0},
        {"\n", 0},
        {"\v", 0},
        {"\f", 0},
        {"\r", 0},
};

const std::map<std::string, TokenType> SIMPLE_SINGLE_TOKENS{
        {"<", LESS_TOKEN},
        {">", MORE_TOKEN},
        {"=", EQUALS_TOKEN},
        {"*", UNSPECIFIED_RELATION_TOKEN},
        {"-", MINUS_TOKEN},
        {":", COLON_TOKEN},
        {",", COMA_TOKEN},
        {END_OF_FILE, END_TOKEN}
};

const std::vector<TokenType> SIMPLE_DOUBLE_TOKENS_PREFIXES {{LESS_TOKEN, MORE_TOKEN}};

const std::map<std::string, TokenType> SIMPLE_DOUBLE_TOKENS{
        {"<=", LESS_EQUAL_TOKEN},
        {">=", MORE_EQUAL_TOKEN},
};

const std::map<std::string, TokenType> KEYWORD_TOKENS{
        {"int", INT_KEYWORD_TOKEN},
        {"float", FLOAT_KEYWORD_TOKEN},
        {"string", STRING_KEYWORD_TOKEN},
};


std::map<std::string, std::string> ESCAPE_CHARACTERS = {
        {"n", "\n"},        // New line
        {"r", "\r"},        // Carriage return
        {"t", "\t"},        // Tab
        {"b", "\b"},        // Backspace
        {"f", "\f"},        // Form feed
        {"\\", BACKSLASH},  // Backslash
        {"0", END_OF_FILE}, // End of file
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



bool compare_float(double x, double y, double epsilon = 0.01f){
    if(fabs(x - y) < epsilon)
        return true;
    return false;
}



TokenType Token::getType() {
    return type;
}

Type Token::getValueType() {
    return valueType;
}

int Token::getIntegerValue() {
    return integerValue;
}

double Token::getDoubleValue() {
    return doubleValue;
}

std::string Token::getStringValue() {
    return stringValue;
}

bool operator== (const Token& left, const Token& right) {
    bool goodValues = left.stringValue == right.stringValue &&
                      left.integerValue == right.integerValue &&
                      compare_float(left.doubleValue, right.doubleValue);
    bool goodTypes = left.type == right.type &&
                     left.valueType == right.valueType;
    return goodValues && goodTypes;
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
        currentCharacterIndex += 1;
        currentCharacter = sourceText[currentCharacterIndex];
    } else {
        currentCharacter = END_OF_FILE;
    }
}

void Lexer::omitWhitespaces() {
    while (WHITESPACES.contains(currentCharacter)) {
        nextCharacter();
    }
}

Token* Lexer::getSimpleToken() {
    try {
        TokenType tokenType = SIMPLE_SINGLE_TOKENS.at(currentCharacter);
        for (TokenType doubleTokenPrefix : SIMPLE_DOUBLE_TOKENS_PREFIXES) {
            if (tokenType == doubleTokenPrefix) {
                //It is possible, that token is 2 signed
                std::string buffer = currentCharacter;
                nextCharacter();
                buffer += currentCharacter;
                try {
                    TokenType alternativeTokenType = SIMPLE_DOUBLE_TOKENS.at(buffer);
                    nextCharacter();
                    return new Token(alternativeTokenType);
                } catch (std::out_of_range& innerException) {
                    return new Token(tokenType);
                }
            }
        }
        // Single sign token
        nextCharacter();
        return new Token(tokenType);
    } catch (std::out_of_range& exception) {
        // No match with simple tokens
        return nullptr;
    }
}

Token* Lexer::getStringLiteral() {
    if (currentCharacter == "'" || currentCharacter == "\"") {
        std::string value = buildString();
        nextCharacter();
        return new Token(value, STRING_LITERAL_TOKEN);
    }
    return nullptr;
}

Token* Lexer::getNumberLiteral() {
    int integerValue = buildInteger();
    double resultValue = 0.;
    double fractionValue = buildFraction();

    if (integerValue >= 0) {
        if (fractionValue >= 0) {
            resultValue += integerValue + fractionValue;
            return new Token(resultValue, NUMERIC_LITERAL_TOKEN);
        }
        return new Token(integerValue, NUMERIC_LITERAL_TOKEN);
    }

    return nullptr;
}

std::string Lexer::buildString() {
    std::string usedQuoteSign = currentCharacter;
    std::string buffer;
    nextCharacter();
    while (currentCharacter != usedQuoteSign) {
        // String length exceeded
        if (buffer.length() >= MAX_STRING_LENGTH) {
            throw ExceededStringLimitException();
        }
            // EOF
        if (currentCharacter == END_OF_FILE) {
            throw UnterminatedStringException();
        }
        // Escape characters
        else if (currentCharacter == BACKSLASH) {
            nextCharacter();
            if (currentCharacter == usedQuoteSign) {
                buffer += usedQuoteSign;
            } else {
                try {
                    std::string newCharacter = ESCAPE_CHARACTERS.at(currentCharacter);
                    buffer += newCharacter;
                } catch (std::out_of_range& exception) {
                    throw UnexpectedCharacterException();
                }
            }
        } else {
            buffer += currentCharacter;
        }
        nextCharacter();
    }
    return buffer;
}

int Lexer::buildInteger() {
    int value;
    if (isDecimal(currentCharacter)) {
        if (currentCharacter == "0") {
            nextCharacter();
            return 0;
        }
        value = std::stoi(currentCharacter);
        nextCharacter();
        while (isDecimal(currentCharacter)) {
            value *= 10;
            value += std::stoi(currentCharacter);
            nextCharacter();
        }
        return value;
    }
    return -1;
}

double Lexer::buildFraction() {
    int value = 0;
    int fractionDigitsQuantity = 0;
    if (currentCharacter == ".") {
        nextCharacter();
        while (isDecimal(currentCharacter)) {
            value *= 10;
            value += std::stoi(currentCharacter);
            fractionDigitsQuantity += 1;
            nextCharacter();
        }
        double fractionalPart = value / pow(10, fractionDigitsQuantity);
        return fractionalPart;
    }
    return -1;
}

bool Lexer::isDecimal(const std::string& character) {
    if (character == "0" || character == "1" || character == "2" || character == "3" || character == "4" ||
        character == "5" || character == "6" || character == "7" || character == "8" || character == "9") {
        return true;
    }
    return false;
}

Token* Lexer::getKeyword() {
    std::string buffer;

    if (std::isalpha(currentCharacter[0])) {
        while (std::isalpha(currentCharacter[0])) {
            buffer += currentCharacter;
            nextCharacter();
        }
        try {
            TokenType tokenType = KEYWORD_TOKENS.at(buffer);
            return new Token(tokenType);
        } catch (std::out_of_range &exception) {
            throw ScanningException();
        }
    }
    return nullptr;
}

Token Lexer::getNextToken() {
    omitWhitespaces();
    Token* token;

    token = getSimpleToken();
    if (token) return *token;

    token = getNumberLiteral();
    if (token) return *token;

    token = getStringLiteral();
    if (token) return *token;

    token = getKeyword();
    if (token) return *token;

    return Token(UNKNOWN_TOKEN);
}



Tuple* Parser::parse(const std::string& text) {
    return nullptr;
}

void Parser::nextToken() {
    currentToken = lexer.getNextToken();
}

Token* Parser::consumeToken(TokenType tokenType, bool isStrict) {
    Token* token = &currentToken;
    if (token -> getType() == tokenType) {
        nextToken();
        return token;
    }
    if (isStrict) {
        throw UnexpectedTokenException();
    }
    return nullptr;
}

Token* Parser::consumeToken(const std::list<TokenType>& tokenTypes, bool isStrict) {
    for (TokenType tokenType : tokenTypes) {
        Token* token = consumeToken(tokenType, false);
        if (token) {
            return token;
        }
    }
    if (isStrict) {
        throw UnexpectedTokenException();
    }
    return nullptr;
}

Entity Parser::parseEntity() {
    Entity* entity;

    entity = parseNumber();
    if (entity) return *entity;

    entity = parseString();
    if (entity) return *entity;

    throw ParsingException();
}

Entity* Parser::parseString() {
    Token *token = consumeToken(STRING_LITERAL_TOKEN, false);
    if (token) {
        return new Entity(token -> getStringValue());
    }
    return nullptr;
}

Entity* Parser::parseNumber() {
    bool negationNeeded = false;
    Token* token = consumeToken(MINUS_TOKEN, false);

    if (token) negationNeeded = true;

    token = consumeToken(NUMERIC_LITERAL_TOKEN, false);
    if (token) {
        int integerValue;
        double doubleValue;
        switch(token -> getValueType()) {
            case INT:
                integerValue = token -> getIntegerValue();
                if (negationNeeded) integerValue *= -1;
                return new Entity(integerValue);
            case FLOAT:
                doubleValue = token -> getDoubleValue();
                if (negationNeeded) doubleValue *= -1;
                return new Entity(doubleValue);
            case STR: case NONE:
                return nullptr;
        }
    }
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