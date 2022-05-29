#include "../lib/include/Parser.h"
#include "catch.hpp"

TEST_CASE("Lexer") {
    SECTION("Complex test 1") {
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
    SECTION("Test 2") {
        REQUIRE(0 == 0);
    }
}