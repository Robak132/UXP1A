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
    SECTION("Omitting whitespaces") {
        std::string inputLine = "\n10,       \r\n-20,             \t3212432";
        std::vector<Token> correctTokens = {
                Token(10, NUMERIC_LITERAL_TOKEN),
                Token(COMA_TOKEN),
                Token(MINUS_TOKEN),
                Token(20, NUMERIC_LITERAL_TOKEN),
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
    SECTION("Test for doubles") {
        std::string inputLine = R"(1.512, 10.1, -20.4567, 0, 3212432.28378273)";
        std::vector<Token> correctTokens = {
                Token(1.512, NUMERIC_LITERAL_TOKEN),
                Token(COMA_TOKEN),
                Token(10.1, NUMERIC_LITERAL_TOKEN),
                Token(COMA_TOKEN),
                Token(MINUS_TOKEN),
                Token(20.4567, NUMERIC_LITERAL_TOKEN),
                Token(COMA_TOKEN),
                Token(0, NUMERIC_LITERAL_TOKEN),
                Token(COMA_TOKEN),
                Token(3212432.28378273, NUMERIC_LITERAL_TOKEN),
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
    SECTION("Test for keywords") {
        std::string inputLine = R"(integer string float string    string integer)";
        std::vector<Token> correctTokens = {
                Token(INT_KEYWORD_TOKEN),
                Token(STRING_KEYWORD_TOKEN),
                Token(FLOAT_KEYWORD_TOKEN),
                Token(STRING_KEYWORD_TOKEN),
                Token(STRING_KEYWORD_TOKEN),
                Token(INT_KEYWORD_TOKEN),
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
    SECTION("Keyword exception") {
        std::string inputLine = "definitelyNotAKeyword";

        bool exceptionOccurrence = false;
        try {
            Lexer lexer = Lexer(inputLine);
            Token tempToken = Token(UNKNOWN_TOKEN);

            while (tempToken.getType() != END_TOKEN) {
                tempToken = lexer.getNextToken();
            }
        } catch (const ScanningException &message) {
            exceptionOccurrence = true;
        }

        REQUIRE(exceptionOccurrence);
    }
}

TEST_CASE("Parser") {
    SECTION("Test CSV") {
        std::string inputLine = R"(1,"a'b'c",3.14159,"d")";
        Tuple correctTuple = Tuple(std::vector<Entity> {
                Entity(1),
                Entity("a'b'c"),
                Entity(3.14159),
                Entity("d"),
        });
        Parser parser = Parser();
        Tuple* resultTuple = parser.parseCSV(inputLine);

        REQUIRE(*resultTuple == correctTuple);
    }
    SECTION("Test pattern") {
        std::string inputLine = R"(integer:600, float:*, string:"Simba", float:<3.14)";
        Tuple correctTuple = Tuple(std::vector<Entity> {
                Entity(600, EQUAL),
                Entity(FLOAT),
                Entity("Simba", EQUAL),
                Entity(3.14, LESS),
        });
        Parser parser = Parser();
        Tuple* resultTuple = parser.parsePattern(inputLine);

        REQUIRE(*resultTuple == correctTuple);
    }
    SECTION("Test file pattern") {
        std::string inputLine = R"(123456, integer:600, float:*, string:"Simba", float:<3.14)";
        Tuple correctTuple = Tuple(std::vector<Entity> {
                Entity(600, EQUAL),
                Entity(FLOAT),
                Entity("Simba", EQUAL),
                Entity(3.14, LESS),
        });
        correctTuple.setSemaphoreAddress(123456);
        Parser parser = Parser();
        Tuple* resultTuple = parser.parseFilePattern(inputLine);

        REQUIRE(*resultTuple == correctTuple);
    }
    SECTION("Test file pattern exception") {
        std::string inputLine = R"(123456.11, integer:600, float:*, string:"Simba", float:<3.14)";
        Parser parser = Parser();
        bool exceptionOccurrence = false;

        try {
            parser.parseFilePattern(inputLine);
        } catch (NoSemaphoreAddressException& exception) {
            exceptionOccurrence = true;
        }

        REQUIRE(exceptionOccurrence);
    }
}