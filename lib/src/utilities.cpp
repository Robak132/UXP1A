#include "../include/utilities.h"
#include "string"

Utilities::Utilities() = default;
std::vector<std::string> Utilities::splitString(const std::string& input) {
    std::string temp;
    std::vector<std::string> result;

    for (char character : input) {
        if (character != '\n' && character != '\r') {
            temp += character;
        } else {
            if (!temp.empty()) {
                result.push_back(temp);
                temp = "";
            }
        }
    }
    if (!temp.empty()) {
        result.push_back(temp);
    }
    return result;
}