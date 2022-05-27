#include "../include/Utilities.h"
#include <map>


const std::map<std::string, int> LINE_ENDINGS {
        {"\n", 0},
        {"\r", 0},
        {"\n\r", 0},
        {"\r\n", 0},
};


std::vector<std::string> Utilities::splitString(const std::string& input) {
    std::string temp;
    std::vector<std::string> result;

    for (const char character : input) {
        std::string string_character;
        string_character = character;
        if (!LINE_ENDINGS.contains(string_character)) {
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