#include "../lib/include/Parser.h"
#include "catch.hpp"

TEST_CASE("Lexer") {
    SECTION("Test for integers") {
        std::string inputLine = R"(1, 10, -20, 0, 3212432)";
        std::vector<Token> correctTokens = {
                Token(1, NUMERIC_LITERAL_TOKEN),
                Token(COMA_TOKEN),
                Token(10, NUMERIC_LITERAL_TOKEN),
                Token(COMA_TOKEN),
                Token(MINUS_TOKEN),
                Token(20, NUMERIC_LITERAL_TOKEN),
                Token(COMA_TOKEN),
                Token(0, NUMERIC_LITERAL_TOKEN),
                Token(COMA_TOKEN),
                Token(3212432, NUMERIC_LITERAL_TOKEN),
                Token(END_TOKEN),
        };
        std::vector<Token> resultTokens;

        Lexer lexer = Lexer(inputLine);
        Token tempToken = Token(UNKNOWN_TOKEN);

        while (tempToken.getType() != END_TOKEN) {
            tempToken = lexer.getNextToken();
            resultTokens.push_back(tempToken);
        }

        REQUIRE(resultTokens == correctTokens);
    }
    SECTION("Test for strings") {
        std::string inputLine = R"('Oklahoma', "Some escaping\"", "\"", "'''", "10.20", ",", '"""', '\'')";
        std::vector<Token> correctTokens = {
                Token("Oklahoma", STRING_LITERAL_TOKEN),
                Token(COMA_TOKEN),
                Token("Some escaping\"", STRING_LITERAL_TOKEN),
                Token(COMA_TOKEN),
                Token("\"", STRING_LITERAL_TOKEN),
                Token(COMA_TOKEN),
                Token("'''", STRING_LITERAL_TOKEN),
                Token(COMA_TOKEN),
                Token("10.20", STRING_LITERAL_TOKEN),
                Token(COMA_TOKEN),
                Token(",", STRING_LITERAL_TOKEN),
                Token(COMA_TOKEN),
                Token(R"(""")", STRING_LITERAL_TOKEN),
                Token(COMA_TOKEN),
                Token("'", STRING_LITERAL_TOKEN),
                Token(END_TOKEN),
        };
        std::vector<Token> resultTokens;

        Lexer lexer = Lexer(inputLine);
        Token tempToken = Token(UNKNOWN_TOKEN);

        while (tempToken.getType() != END_TOKEN) {
            tempToken = lexer.getNextToken();
            resultTokens.push_back(tempToken);
        }

        REQUIRE(resultTokens == correctTokens);
    }
    SECTION("Mixed input") {
        std::string inputLine = R"(1,"a'b'c",3,"d")";
        std::vector<Token> correctTokens = {
                Token(1, NUMERIC_LITERAL_TOKEN),
                Token(COMA_TOKEN),
                Token("a'b'c", STRING_LITERAL_TOKEN),
                Token(COMA_TOKEN),
                Token(3, NUMERIC_LITERAL_TOKEN),
                Token(COMA_TOKEN),
                Token("d", STRING_LITERAL_TOKEN),
                Token(END_TOKEN),
        };
        std::vector<Token> resultTokens;

        Lexer lexer = Lexer(inputLine);
        Token tempToken = Token(UNKNOWN_TOKEN);

        while (tempToken.getType() != END_TOKEN) {
            tempToken = lexer.getNextToken();
            resultTokens.push_back(tempToken);
        }

        REQUIRE(resultTokens == correctTokens);
    }
    SECTION("String limit exceeded") {
        std::string innerString = "Something";
        for (int i = 0; i < MAX_STRING_LENGTH; i++) innerString += "x";
        std::string inputLine = "'" + innerString + "'";

        bool exceptionOccurrence = false;
        try {
            Lexer lexer = Lexer(inputLine);
            Token tempToken = Token(UNKNOWN_TOKEN);

            while (tempToken.getType() != END_TOKEN) {
                tempToken = lexer.getNextToken();
            }
        } catch (const ExceededStringLimitException &message) {
            exceptionOccurrence = true;
        }

        REQUIRE(exceptionOccurrence);
    }
    SECTION("Unterminated string") {
        std::string inputLine = "'Something";

        bool exceptionOccurrence = false;
        try {
            Lexer lexer = Lexer(inputLine);
            Token tempToken = Token(UNKNOWN_TOKEN);

            while (tempToken.getType() != END_TOKEN) {
                tempToken = lexer.getNextToken();
            }
        } catch (const UnterminatedStringException &message) {
            exceptionOccurrence = true;
        }

        REQUIRE(exceptionOccurrence);
    }
}