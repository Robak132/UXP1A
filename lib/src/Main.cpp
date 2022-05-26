#include <iostream>
#include <cstring>
#include <string>
#include "../include/Linda.h"
#include "../include/Parser.h"

int main(int argc, char *argv[]) {
    Linda linda = Linda();

    switch(argc) {
        case 3:
            if (strcmp(argv[1], "-o") == 0) {
                std::string stringToParse = argv[2];
                //TODO Output
            } else {
                std::cout << "Wrong syntax" << std::endl;
                exit(0);
            }
            break;
        case 5:
            if (strcmp(argv[1], "-i") == 0 && strcmp(argv[1], "-t") == 0) {
                std::string stringToParse = argv[2];
                int timeout = std::stoi(argv[4]);
                //TODO Input
            } else if (strcmp(argv[1], "-r") == 0 && strcmp(argv[1], "-t") == 0) {
                std::string stringToParse = argv[2];
                int timeout = std::stoi(argv[4]);
                //TODO Read
            } else {
                std::cout << "Wrong syntax" << std::endl;
                exit(0);
            }
            break;
        default:
            std::cout << "Wrong syntax" << std::endl;
            exit(0);
    }
}